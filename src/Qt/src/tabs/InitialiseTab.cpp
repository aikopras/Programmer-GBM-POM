//
//  InitialiseTab.cpp
//  Programmer GBM-POM (Qt)
//
//  Created by Aiko Pras on 21-11-2026.
//  Copyright (c) 2026 by Aiko Pras. All rights reserved.
//
//  INITIALISE tab: gives a non-initialised decoder (RS-Bus address 0, which listens to loco address 6000)
//  its RS-Bus address (myRSAddr, CV10). Same as the INITIALISE tab of the macOS version (AppDelegate.m).
//

#include "InitialiseTab.h"
#include "ui_initialisetab.h"
#include "MainWindow.h"
#include "DccDecoder.h"
#include "PomConnection.h"
#include "CvNames.h"
#include <QTimer>
#include <QIntValidator>

InitialiseTab::InitialiseTab(MainWindow *mainWindow, QWidget *parent) : DecoderTab(mainWindow, parent), ui(new Ui::InitialiseTab)
{
  ui->setupUi(this);
  ui->rsAddressNew->setValidator(new QIntValidator(1, 128, ui->rsAddressNew));
  connect(ui->rsAddressNew, &QLineEdit::editingFinished, this, &InitialiseTab::enteredNewRsAddress);
  connect(ui->buttonIniTabSet, &QPushButton::clicked, this, &InitialiseTab::pushedSet);
}

InitialiseTab::~InitialiseTab()
{
  delete ui;
}

void InitialiseTab::enteredNewRsAddress()
{
  int newValue = ui->rsAddressNew->text().toInt();
  if ((newValue >= 1) && (newValue <= 128)) {
    decoder->setCv(CV::myRSAddr, newValue);
    colorSetButton(true);
  }
}

void InitialiseTab::pushedSet()
{
  enteredNewRsAddress();                                  // Takes also a value that is typed, but not yet entered
  // Set the address of the uninitilised decoder to 0, which will result in a PoM message with address 6000
  decoder->decoderAddress = 0;
  // Modified July 2021, to ensure a restart is performed
  decoder->setCv(CV::Restart, 1);
  mainWindow->setAddressField(0);
  // Since a wrong value in myRSAddr can make the decoder inaccessable, check myRSAddr again!
  int newAddress = decoder->getCv(CV::myRSAddr);
  if ((newAddress >= 1) && (newAddress <= 128)) {
    pom->writeCv(CV::myRSAddr);
    pom->writeCv(CV::Restart);
    // Update the decoder address, but wait one second to allow all PoM messages to be send using the "old" address for non-initialised decoders
    QTimer::singleShot(1000, this, &InitialiseTab::updateDecoderAddress);
    colorSetButton(false);
  }
  mainWindow->updateTabs();
}

void InitialiseTab::updateDecoderAddress()
{
  decoder->decoderAddress = decoder->getCv(CV::myRSAddr);
  mainWindow->setAddressField(decoder->decoderAddress);
}

void InitialiseTab::updateTab()
{
  ui->rsAddressNew->setText(QString::number(decoder->getCv(CV::myRSAddr)));
}

void InitialiseTab::colorSetButton(bool red)
{
  setButtonRed(ui->buttonIniTabSet, red);
}
