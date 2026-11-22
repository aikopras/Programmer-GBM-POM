//
//  ControlTab.cpp
//  Programmer GBM-POM (Qt)
//
//  Created by Aiko Pras on 21-11-2026.
//  Copyright (c) 2026 by Aiko Pras. All rights reserved.
//
//  CONTROL tab: RSRetry (CV20), CmdStation (CV19) and DecType (CV27, the decoder mode).
//  Same as the CONTROL tab of the macOS version (AppDelegate.m). The combo boxes react on a choice of the user
//  (signal activated), not on updateTab.
//

#include "ControlTab.h"
#include "ui_controltab.h"
#include "MainWindow.h"
#include "DccDecoder.h"
#include "PomConnection.h"
#include "CvNames.h"

// The texts of the DecType combo box, with their CV27 values
static const struct {const char *name; int value;} decTypes[] = {
  {"normal", DecTypes::Normal}, {"reverser", DecTypes::Reverser}, {"relay", DecTypes::Relays}, {"speed", DecTypes::Speed}
};

ControlTab::ControlTab(MainWindow *mainWindow, QWidget *parent) : DecoderTab(mainWindow, parent), ui(new Ui::ControlTab)
{
  ui->setupUi(this);
  connect(ui->comboRsRetry, &QComboBox::activated, this, &ControlTab::selectedRsRetry);
  connect(ui->comboCmdSystem, &QComboBox::activated, this, &ControlTab::selectedCmdSystem);
  connect(ui->comboDecType, &QComboBox::activated, this, &ControlTab::selectedDecType);
  connect(ui->buttonControlTabDefaults, &QPushButton::clicked, this, &ControlTab::pushedDefaults);
  connect(ui->buttonControlTabGet, &QPushButton::clicked, this, &ControlTab::pushedGet);
  connect(ui->buttonControlTabSet, &QPushButton::clicked, this, &ControlTab::pushedSet);
}

ControlTab::~ControlTab()
{
  delete ui;
}

void ControlTab::selectedRsRetry()
{
  decoder->setCv(CV::RSRetry, ui->comboRsRetry->currentText().toInt());
  colorSetButton(true);
}

void ControlTab::selectedCmdSystem()
{
  QString newString = ui->comboCmdSystem->currentText();
  uint8_t newValue = 1;                                   // Lenz is the default
  if (newString == "standard") newValue = 0;
  decoder->setCv(CV::CmdStation, newValue);
  colorSetButton(true);
}

void ControlTab::selectedDecType()
{
  QString newString = ui->comboDecType->currentText();
  uint8_t newValue = DecTypes::Normal;                    // Select the default value 0b00110000 (= normal)
  for (const auto &decType : decTypes) if (newString == decType.name) newValue = decType.value;
  decoder->setCv(CV::DecType, newValue);
  colorSetButton(true);
  mainWindow->updateTabs();
}

void ControlTab::pushedDefaults()
{
  decoder->setCv(CV::RSRetry, 0);
  decoder->setCv(CV::CmdStation, 1);
  decoder->setCv(CV::DecType, DecTypes::Normal);
  colorSetButton(true);
  mainWindow->updateTabs();
}

void ControlTab::pushedGet()
{
  pom->verifyCv(CV::RSRetry);
  pom->verifyCv(CV::CmdStation);
  pom->verifyCv(CV::DecType);
  colorSetButton(false);
}

void ControlTab::pushedSet()
{
  pom->writeCv(CV::RSRetry);
  pom->writeCv(CV::CmdStation);
  pom->writeCv(CV::DecType);
  colorSetButton(false);
}

void ControlTab::updateTab()
{
  // RSRetry
  ui->comboRsRetry->setCurrentText(QString::number(decoder->getCv(CV::RSRetry)));
  // Command System
  ui->comboCmdSystem->setCurrentText((decoder->getCv(CV::CmdStation) == 0) ? "standard" : "Lenz");
  // DecType
  QString newString = "normal";                           // default
  for (const auto &decType : decTypes) if (decoder->getCv(CV::DecType) == decType.value) newString = decType.name;
  ui->comboDecType->setCurrentText(newString);
}

void ControlTab::colorSetButton(bool red)
{
  setButtonRed(ui->buttonControlTabSet, red);
}
