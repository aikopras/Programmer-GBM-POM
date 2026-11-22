//
//  MainWindow.cpp
//  Programmer GBM-POM (Qt)
//
//  Created by Aiko Pras on 21-11-2026.
//  Copyright (c) 2026 by Aiko Pras. All rights reserved.
//
//  Qt version of the main window part of AppDelegate.m: the RS-Bus address, SELECT, LED ON and RESTART,
//  the decoder information, the status lines and the tabs.
//  Differences with the macOS version:
//  - Each tab is a separate class (see src/tabs).
//  - The decoder specific tabs are hidden with setTabVisible, instead of being removed and inserted.
//  - Buttons take the values from the fields when they are pushed (macOS: readLastInputFromTextFields).
//

#include "MainWindow.h"
#include "ui_mainwindow.h"
#include "PomConnection.h"
#include "PreferencesDialog.h"
#include "HelpWindow.h"
#include "CvNames.h"
#include "ControlTab.h"
#include "DelayTab.h"
#include "SensitivityTab.h"
#include "ReverserTab.h"
#include "RelaysTab.h"
#include "SpeedTab.h"
#include "InitialiseTab.h"
#include "CvTab.h"
#include <QMenuBar>
#include <QMessageBox>
#include <QTimer>
#include <QTabBar>
#include <QIntValidator>

// ****************************************************************************************************************************************************
// ****************************************************************** INITIALISATION ******************************************************************
// ****************************************************************************************************************************************************
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  setWindowTitle("Programmer GBM-POM");
  preferencesDialog = nullptr;
  helpWindow = nullptr;
  // Step 1: dccDecoder
  dccDecoder.initialise();
  // Step 2: preferences. Create them if they do not exist
  PreferencesDialog::checkPreferences();
  // Step 3: pomConnection
  pomConnection = new PomConnection(&dccDecoder, this);
  connect(pomConnection, &PomConnection::cvReceived, this, &MainWindow::cvReceived);
  connect(pomConnection, &PomConnection::generalStatus, ui->connectionStatus, &QLabel::setText);
  connect(pomConnection, &PomConnection::sendStatus, ui->sendStatus, &QLabel::setText);
  connect(pomConnection, &PomConnection::receiveStatus, ui->receiveStatus, &QLabel::setText);
  connect(pomConnection, &PomConnection::busy, ui->progressIndicator, &QProgressBar::setVisible);
  connect(pomConnection, &PomConnection::idle, this, [this]() {
    // The end of a run clears the status line; show the message about a non-initialised decoder again
    if (!nonInitialisedMessage.isEmpty()) ui->connectionStatus->setText(nonInitialisedMessage);
    nonInitialisedMessage.clear();
  });
  ui->progressIndicator->setVisible(false);
  ui->connectionStatus->clear();                          // Remove the texts of the .ui file
  ui->sendStatus->clear();
  ui->receiveStatus->clear();
  // Step 4: UI
  // The address field is empty at startup (as in the macOS version); empty means: non-initialised decoder
  ui->address->setValidator(new QIntValidator(1, 128, ui->address));
  ui->ledOn->setCheckable(true);
  connect(ui->address, &QLineEdit::editingFinished, this, &MainWindow::takeDecoderAddress);
  connect(ui->buttonSelect, &QPushButton::clicked, this, &MainWindow::selectAddressPushed);
  connect(ui->ledOn, &QPushButton::clicked, this, &MainWindow::ledOnPushed);
  connect(ui->buttonRestart, &QPushButton::clicked, this, &MainWindow::restartPushed);
  createMenus();
  addTabs();
  // Command stations with software version 3.8 or higher support relays addresses up to 2048, older ones up to 1024
  connect(pomConnection, &PomConnection::maxSwitchAddress, relaysTab, &RelaysTab::setMaxSwitchAddress);
  setFixedSize(width(), height() + menuBar()->sizeHint().height());   // The .ui size excludes the menu bar
  // Step 5: open the TCP connection(s)
  pomConnection->open();
  updateTabs();
  // Step 6: look for a non-initialised decoder (see searchNonInitialisedDecoder)
  searchNonInitialisedDecoder();
}

void MainWindow::searchNonInitialisedDecoder()
{
  // Non-initialised decoders have RS-Bus address 0, and listen to loco address 6000.
  // Since reading CV values take time, we first read the "version" CV.
  // Added in November 2026: called at startup, and by SELECT with an empty address field. If a decoder answers,
  // cvReceived reports this and shows the INITIALISE tab.
  dccDecoder.initialise();                                // Do not show the CVs of the previous decoder
  dccDecoder.decoderAddress = 0;
  pomConnection->openIfClosed();
  pomConnection->verifyCv(CV::version);
  // But in addition we read all other CVs to allow the appropriate TABs (reverser, relays, speed) to be displayed.
  readAllCvs();
  updateTabs();
}

MainWindow::~MainWindow()
{
  pomConnection->close();
  delete ui;
}

void MainWindow::createMenus()
{
  // On macOS Qt moves Preferences, Quit and About to the application menu
  QMenu *fileMenu = menuBar()->addMenu("&File");
  QAction *preferencesAction = fileMenu->addAction("Preferences...", this, &MainWindow::showPreferences);
  preferencesAction->setMenuRole(QAction::PreferencesRole);
  preferencesAction->setShortcut(QKeySequence::Preferences);
  fileMenu->addSeparator();
  QAction *quitAction = fileMenu->addAction("Quit", this, &QWidget::close);
  quitAction->setMenuRole(QAction::QuitRole);
  quitAction->setShortcut(QKeySequence::Quit);
  QMenu *helpMenu = menuBar()->addMenu("&Help");
  QAction *helpAction = helpMenu->addAction("Programmer GBM-POM Help", this, &MainWindow::showHelp);
  helpAction->setShortcut(QKeySequence::HelpContents);
  QAction *aboutAction = helpMenu->addAction("About Programmer GBM-POM", this, &MainWindow::showAbout);
  aboutAction->setMenuRole(QAction::AboutRole);
}

void MainWindow::addTabs()
{
  // Same order as TabIndex
  tabs.append(new ControlTab(this));
  tabs.append(new DelayTab(this));
  tabs.append(new SensitivityTab(this));
  tabs.append(new ReverserTab(this));
  relaysTab = new RelaysTab(this);
  tabs.append(relaysTab);
  tabs.append(new SpeedTab(this));
  tabs.append(new InitialiseTab(this));
  tabs.append(new CvTab(this));
  const char *names[] = {"Control", "Delay", "Sensitivity", "Reverser", "Relays", "Speed", "Initialise", "CV"};
  for (int i = 0; i < tabs.size(); i++) ui->windowTabs->addTab(tabs[i], names[i]);
  // Bold texts for the tab names and all buttons (the standard Windows font looks rather thin)
  QFont font = ui->windowTabs->tabBar()->font();
  font.setBold(true);
  ui->windowTabs->tabBar()->setFont(font);
  for (QPushButton *button : findChildren<QPushButton *>()) {
    font = button->font();
    font.setBold(true);
    button->setFont(font);
  }
}

void MainWindow::updateTabs()
{
  updateMainWindow();
  for (DecoderTab *tab : tabs) tab->updateTab();
  // Depending on the decoder type (CV27), show the REVERSER, RELAYS or SPEED tab
  uint8_t decType = dccDecoder.getCv(CV::DecType);
  ui->windowTabs->setTabVisible(ReverserIndex, decType == DecTypes::Reverser);
  ui->windowTabs->setTabVisible(RelaysIndex, decType == DecTypes::Relays);
  ui->windowTabs->setTabVisible(SpeedIndex, decType == DecTypes::Speed);
}


// ****************************************************************************************************************************************************
// ****************************************************** FEEDBACK MESSAGE RECEIVED BY THE POM OBJECT *************************************************
// ****************************************************************************************************************************************************
void MainWindow::cvReceived(int cvNumber, uint8_t cvValue)
{
  dccDecoder.setCv(cvNumber, cvValue);
  // A non-initialised decoder answered (PoM address 6000): report this and go to the INITIALISE tab
  if ((cvNumber == CV::version) && (dccDecoder.decoderAddress == 0)) {
    nonInitialisedMessage = QString("Non-initialised decoder found (software version %1)").arg(cvValue);
    ui->connectionStatus->setText(nonInitialisedMessage);
    ui->windowTabs->setCurrentIndex(InitialiseIndex);
  }
  updateTabs();
}


// ****************************************************************************************************************************************************
// ********************************************************* USER INTERFACE METHODS - MAIN WINDOW *****************************************************
// ****************************************************************************************************************************************************
void MainWindow::takeDecoderAddress()
{
  int newValue = ui->address->text().toInt();           // 0 if the field is empty
  if (newValue < 1) {                                     // Empty field: non-initialised decoder (PoM address 6000)
    dccDecoder.decoderAddress = 0;
    pomConnection->openIfClosed();
    return;
  }
  if (newValue > 128) {newValue = 128;}
  dccDecoder.decoderAddress = newValue;
  pomConnection->openIfClosed();                          // reconnect if the Lenz interface(s) were not available before
}

void MainWindow::selectAddressPushed()
{
  // SELECT with an empty address field searches for a non-initialised decoder
  if (ui->address->text().toInt() < 1) {searchNonInitialisedDecoder(); return;}
  takeDecoderAddress();                                   // Takes also a value that is typed, but not yet entered
  readAllCvs();
}

void MainWindow::ledOnPushed(bool checked)
{
  dccDecoder.setCv(CV::Search, checked ? 1 : 0);
  pomConnection->writeCv(CV::Search);
  updateMainWindow();
}

void MainWindow::restartPushed()
{
  dccDecoder.setCv(CV::Restart, 0x0D);
  pomConnection->writeCv(CV::Restart);
  // Read all CVs again, after a delay of 0.3 seconds
  QTimer::singleShot(300, this, &MainWindow::readAllCvs);
}

void MainWindow::readAllCvs()
{
  pomConnection->verifyCv(1);
  for (int cvNumber = 7; cvNumber <= 20; cvNumber++) pomConnection->verifyCv(cvNumber);
  for (int cvNumber = 23; cvNumber <= 24; cvNumber++) pomConnection->verifyCv(cvNumber);
  for (int cvNumber = 26; cvNumber <= 30; cvNumber++) pomConnection->verifyCv(cvNumber);
  for (int cvNumber = 33; cvNumber <= 51; cvNumber++) pomConnection->verifyCv(cvNumber);
  // Remove possible red color from SET buttons
  for (DecoderTab *tab : tabs) tab->colorSetButton(false);
}

void MainWindow::setAddressField(int rsAddress)
{
  // 0 (after initialising a decoder) is shown as an empty field
  ui->address->setText((rsAddress > 0) ? QString::number(rsAddress) : QString());
}

void MainWindow::showGeneralStatus(const QString &text)
{
  ui->connectionStatus->setText(text);
}

void MainWindow::updateMainWindow()
{
  ui->DecoderVendor->setText(dccDecoder.decoderVendor());
  ui->DecoderVersion->setText(dccDecoder.decoderVersion());
  ui->DecoderType->setText(dccDecoder.decoderType());
  ui->DecoderSubType->setText(dccDecoder.decoderSubType());
  ui->DecoderErrors->setText(dccDecoder.decoderErrors());
  bool ledIsOn = (dccDecoder.getCv(CV::Search) != 0);
  ui->ledOn->setChecked(ledIsOn);
  ui->ledOn->setStyleSheet(ledIsOn ? "color: red" : "");
}


// ****************************************************************************************************************************************************
// ******************************************************************** MENUS *************************************************************************
// ****************************************************************************************************************************************************
void MainWindow::showPreferences()
{
  if (preferencesDialog == nullptr) preferencesDialog = new PreferencesDialog(this);
  preferencesDialog->show();
  preferencesDialog->raise();
}

void MainWindow::showHelp()
{
  if (helpWindow == nullptr) helpWindow = new HelpWindow(this);
  helpWindow->show();
  helpWindow->raise();
}

void MainWindow::showAbout()
{
  QMessageBox::about(this, "About Programmer GBM-POM",
    "<b>Programmer GBM-POM</b><br>Version " APP_VERSION "<br><br>"
    "Programs the CVs of my GBM (track occupancy) decoders via PoM, using a Lenz LAN/USB interface (23151).<br><br>"
    "Qt version: " + QString(qVersion()) + "<br><br>"
    "Copyright (c) 2026 by Aiko Pras");
}
