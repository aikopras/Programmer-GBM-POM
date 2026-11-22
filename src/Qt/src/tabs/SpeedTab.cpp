//
//  SpeedTab.cpp
//  Programmer GBM-POM (Qt)
//
//  Created by Aiko Pras on 21-11-2026.
//  Copyright (c) 2026 by Aiko Pras. All rights reserved.
//
//  SPEED tab: the two speed measurement tracks. Per track the input (Speed1_Out, CV37 / Speed2_Out, CV40)
//  and the length in mm (Speed1_LL + 256 * Speed1_LH, CV38 + CV39 / Speed2_LL + 256 * Speed2_LH, CV41 + CV42).
//  Same as the SPEED tab of the macOS version (AppDelegate.m). The decoder accepts the inputs 2..7 (0 = none)
//  and lengths of 100..5000 mm (see speed.c of the firmware).
//

#include "SpeedTab.h"
#include "ui_speedtab.h"
#include "MainWindow.h"
#include "DccDecoder.h"
#include "PomConnection.h"
#include "CvNames.h"
#include <QSignalBlocker>

SpeedTab::SpeedTab(MainWindow *mainWindow, QWidget *parent) : DecoderTab(mainWindow, parent), ui(new Ui::SpeedTab)
{
  ui->setupUi(this);
  connect(ui->comboSpeedFeedback1, &QComboBox::textActivated, this, [this](const QString &text) {storeSpeedCv(CV::Speed1_Out, text);});
  connect(ui->comboSpeedFeedback2, &QComboBox::textActivated, this, [this](const QString &text) {storeSpeedCv(CV::Speed2_Out, text);});
  // The fields react on Return / leaving the field, not on every typed character
  ui->speedLengthTrack1->setKeyboardTracking(false);
  ui->speedLengthTrack2->setKeyboardTracking(false);
  connect(ui->speedLengthTrack1, &QSpinBox::valueChanged, this, [this](int length) {storeLength(CV::Speed1_LL, CV::Speed1_LH, length);});
  connect(ui->speedLengthTrack2, &QSpinBox::valueChanged, this, [this](int length) {storeLength(CV::Speed2_LL, CV::Speed2_LH, length);});
  connect(ui->buttonSpeedTabDefaults, &QPushButton::clicked, this, &SpeedTab::pushedDefaults);
  connect(ui->buttonSpeedTabGet, &QPushButton::clicked, this, &SpeedTab::pushedGet);
  connect(ui->buttonSpeedTabSet, &QPushButton::clicked, this, &SpeedTab::pushedSet);
}

SpeedTab::~SpeedTab()
{
  delete ui;
}

void SpeedTab::storeSpeedCv(int cvNumber, const QString &text)
{
  // The combo boxes contain 0 and 2..7
  decoder->setCv(cvNumber, text.toInt());
  colorSetButton(true);
}

void SpeedTab::storeLength(int cvLow, int cvHigh, int length)
{
  if (length < 100) {length = 0;}
  if (length > 5000) {length = 5000;}
  decoder->setCv(cvLow, length & 0b11111111);
  decoder->setCv(cvHigh, (length >> 8) & 0b11111111);
  updateTab();
  colorSetButton(true);
}

void SpeedTab::pushedDefaults()
{
  for (int cvNumber = CV::Speed1_Out; cvNumber <= CV::Speed2_LH; cvNumber++) decoder->setCv(cvNumber, 0);
  colorSetButton(true);
  updateTab();
}

void SpeedTab::pushedGet()
{
  for (int cvNumber = CV::Speed1_Out; cvNumber <= CV::Speed2_LH; cvNumber++) pom->verifyCv(cvNumber);
  colorSetButton(false);
}

void SpeedTab::pushedSet()
{
  for (int cvNumber = CV::Speed1_Out; cvNumber <= CV::Speed2_LH; cvNumber++) pom->writeCv(cvNumber);
  colorSetButton(false);
}

void SpeedTab::updateTab()
{
  showComboText(ui->comboSpeedFeedback1, QString::number(decoder->getCv(CV::Speed1_Out)));
  showComboText(ui->comboSpeedFeedback2, QString::number(decoder->getCv(CV::Speed2_Out)));
  // The fields are set without calling storeLength
  QSignalBlocker block1(ui->speedLengthTrack1);
  QSignalBlocker block2(ui->speedLengthTrack2);
  ui->speedLengthTrack1->setValue(decoder->getCv(CV::Speed1_LH) * 256 + decoder->getCv(CV::Speed1_LL));
  ui->speedLengthTrack2->setValue(decoder->getCv(CV::Speed2_LH) * 256 + decoder->getCv(CV::Speed2_LL));
}

void SpeedTab::colorSetButton(bool red)
{
  setButtonRed(ui->buttonSpeedTabSet, red);
}
