//
//  SensitivityTab.cpp
//  Programmer GBM-POM (Qt)
//
//  Created by Aiko Pras on 21-11-2026.
//  Copyright (c) 2026 by Aiko Pras. All rights reserved.
//
//  SENSITIVITY tab: Min_Samples (CV33), Threshold_on (CV35) and Threshold_of (CV36).
//  Same as the SENSITIVITY tab of the macOS version (AppDelegate.m). The thresholds are shown in mA (CV value / 40),
//  together with the corresponding resistance (600 / CV value, in KOhm).
//

#include "SensitivityTab.h"
#include "ui_sensitivitytab.h"
#include "MainWindow.h"
#include "DccDecoder.h"
#include "PomConnection.h"
#include "CvNames.h"
#include <QSignalBlocker>

SensitivityTab::SensitivityTab(MainWindow *mainWindow, QWidget *parent) : DecoderTab(mainWindow, parent), ui(new Ui::SensitivityTab)
{
  ui->setupUi(this);
  // The fields react on Return / leaving the field, not on every typed character
  ui->minSamples->setKeyboardTracking(false);
  ui->tresholdOn->setKeyboardTracking(false);
  ui->tresholdOff->setKeyboardTracking(false);
  connect(ui->minSamples, &QSpinBox::valueChanged, this, &SensitivityTab::selectedMinSamples);
  connect(ui->tresholdOn, &QDoubleSpinBox::valueChanged, this, [this](double mA) {selectedThreshold(CV::Threshold_on, mA);});
  connect(ui->tresholdOff, &QDoubleSpinBox::valueChanged, this, [this](double mA) {selectedThreshold(CV::Threshold_of, mA);});
  connect(ui->buttonSensitivityTabDefaults, &QPushButton::clicked, this, &SensitivityTab::pushedDefaults);
  connect(ui->buttonSensitivityTabGet, &QPushButton::clicked, this, &SensitivityTab::pushedGet);
  connect(ui->buttonSensitivityTabSet, &QPushButton::clicked, this, &SensitivityTab::pushedSet);
}

SensitivityTab::~SensitivityTab()
{
  delete ui;
}

void SensitivityTab::selectedMinSamples()
{
  int receivedInt = ui->minSamples->value();
  if (receivedInt < 1) {receivedInt = 1;}
  if (receivedInt > 8) {receivedInt = 8;}                 // The decoder accepts 1..8
  decoder->setCv(CV::Min_Samples, receivedInt);
  colorSetButton(true);
  updateTab();
}

void SensitivityTab::selectedThreshold(int cvNumber, double mA)
{
  if (mA > 2.5) {mA = 2.5;}
  if (mA < 0.2) {mA = 0.2;}
  uint8_t cvValue = qRound(mA * 40);
  decoder->setCv(cvNumber, cvValue);
  colorSetButton(true);
  updateTab();
}

void SensitivityTab::pushedDefaults()
{
  decoder->setCv(CV::Min_Samples, 3);
  decoder->setCv(CV::Threshold_on, 20);
  decoder->setCv(CV::Threshold_of, 15);
  colorSetButton(true);
  updateTab();
}

void SensitivityTab::pushedGet()
{
  pom->verifyCv(CV::Min_Samples);
  pom->verifyCv(CV::Threshold_on);
  pom->verifyCv(CV::Threshold_of);
  colorSetButton(false);
}

void SensitivityTab::pushedSet()
{
  pom->writeCv(CV::Min_Samples);
  pom->writeCv(CV::Threshold_on);
  pom->writeCv(CV::Threshold_of);
  colorSetButton(false);
}

void SensitivityTab::updateTab()
{
  // The fields are set without calling selectedMinSamples / selectedThreshold
  QSignalBlocker blockSamples(ui->minSamples);
  QSignalBlocker blockOn(ui->tresholdOn);
  QSignalBlocker blockOff(ui->tresholdOff);
  ui->minSamples->setValue(decoder->getCv(CV::Min_Samples));
  ui->tresholdOn->setValue(decoder->getCv(CV::Threshold_on) / 40.0);
  ui->tresholdOff->setValue(decoder->getCv(CV::Threshold_of) / 40.0);
  ui->tresholdOnText->setText(sensitivityToString(decoder->getCv(CV::Threshold_on)));
  ui->tresholdOffText->setText(sensitivityToString(decoder->getCv(CV::Threshold_of)));
}

QString SensitivityTab::sensitivityToString(uint8_t cvValue)
{
  if (cvValue == 0) return "(mA)";
  int kOhm = 600 / cvValue;
  return QString("mA   (%1 KOhm)").arg(kOhm);
}

void SensitivityTab::colorSetButton(bool red)
{
  setButtonRed(ui->buttonSensitivityTabSet, red);
}
