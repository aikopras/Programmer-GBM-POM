//
//  ReverserTab.cpp
//  Programmer GBM-POM (Qt)
//
//  Created by Aiko Pras on 21-11-2026.
//  Copyright (c) 2026 by Aiko Pras. All rights reserved.
//
//  REVERSER tab: the feedback bits for the tracks A..D (FB_A..FB_D, CV43..46) and the sensors 1..4
//  (FB_S1..FB_S4, CV47..50), and the J&K polarization of the relays (Polarization, CV51).
//  Same as the REVERSER tab of the macOS version (AppDelegate.m).
//  The CVs hold the feedback bit (0..7); the combo boxes show the RS-Bus input (1..8).
//

#include "ReverserTab.h"
#include "ui_reversertab.h"
#include "MainWindow.h"
#include "DccDecoder.h"
#include "PomConnection.h"
#include "CvNames.h"

ReverserTab::ReverserTab(MainWindow *mainWindow, QWidget *parent) : DecoderTab(mainWindow, parent), ui(new Ui::ReverserTab)
{
  ui->setupUi(this);
  feedbackCombos = {{CV::FB_A, ui->comboReverserA}, {CV::FB_B, ui->comboReverserB}, {CV::FB_C, ui->comboReverserC},
                    {CV::FB_D, ui->comboReverserD}, {CV::FB_S1, ui->comboReverserS1}, {CV::FB_S2, ui->comboReverserS2},
                    {CV::FB_S3, ui->comboReverserS3}, {CV::FB_S4, ui->comboReverserS4}};
  for (const auto &combo : feedbackCombos) {
    int cvNumber = combo.first;
    connect(combo.second, &QComboBox::textActivated, this, [this, cvNumber](const QString &text) {storeReverserCv(cvNumber, text);});
  }
  connect(ui->comboReverserPolarization, &QComboBox::activated, this, &ReverserTab::selectedPolarization);
  connect(ui->buttonReverserTabDefaults, &QPushButton::clicked, this, &ReverserTab::pushedDefaults);
  connect(ui->buttonReverserTabGet, &QPushButton::clicked, this, &ReverserTab::pushedGet);
  connect(ui->buttonReverserTabSet, &QPushButton::clicked, this, &ReverserTab::pushedSet);
}

ReverserTab::~ReverserTab()
{
  delete ui;
}

void ReverserTab::storeReverserCv(int cvNumber, const QString &text)
{
  int newValue = text.toInt();                            // RS-Bus input 1..8
  if ((newValue >= 1) && (newValue <= 8)) {
    decoder->setCv(cvNumber, newValue - 1);               // CVs: 0..7
    colorSetButton(true);
  }
}

void ReverserTab::selectedPolarization()
{
  decoder->setCv(CV::Polarization, (ui->comboReverserPolarization->currentText() == "Inverted") ? 1 : 0);   // Normal is the default
  colorSetButton(true);
}

void ReverserTab::pushedDefaults()
{
  decoder->setCv(CV::FB_A, 0);                            // Feedback section A => Feedback bit 1
  decoder->setCv(CV::FB_B, 1);                            // Feedback section B => Feedback bit 2
  decoder->setCv(CV::FB_C, 2);                            // Feedback section C => Feedback bit 3
  decoder->setCv(CV::FB_D, 3);                            // Feedback section D => Feedback bit 4
  decoder->setCv(CV::FB_S1, 0);                           // Sensor track 1 => Feedback bit 1
  decoder->setCv(CV::FB_S2, 1);                           // Sensor track 2 => Feedback bit 2
  decoder->setCv(CV::FB_S3, 1);                           // Sensor track 3 => Feedback bit 2
  decoder->setCv(CV::FB_S4, 2);                           // Sensor track 4 => Feedback bit 3
  decoder->setCv(CV::Polarization, 0);                    // J&K polarization on relays => normal
  colorSetButton(true);
  updateTab();
}

void ReverserTab::pushedGet()
{
  for (const auto &combo : feedbackCombos) pom->verifyCv(combo.first);
  pom->verifyCv(CV::Polarization);
  colorSetButton(false);
}

void ReverserTab::pushedSet()
{
  for (const auto &combo : feedbackCombos) pom->writeCv(combo.first);
  pom->writeCv(CV::Polarization);
  colorSetButton(false);
}

void ReverserTab::updateTab()
{
  for (const auto &combo : feedbackCombos) showComboText(combo.second, QString::number(decoder->getCv(combo.first) + 1));
  ui->comboReverserPolarization->setCurrentText((decoder->getCv(CV::Polarization) == 1) ? "Inverted" : "Normal");
}

void ReverserTab::colorSetButton(bool red)
{
  setButtonRed(ui->buttonReverserTabSet, red);
}
