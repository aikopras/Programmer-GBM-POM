//
//  DelayTab.cpp
//  Programmer GBM-POM (Qt)
//
//  Created by Aiko Pras on 21-11-2026.
//  Copyright (c) 2026 by Aiko Pras. All rights reserved.
//
//  DELAY tab: the delays before an input sends its OFF signal, per input DelayIn1..8 (CV11..18, in 10 ms steps)
//  and for all inputs Delay_off (CV34, in 100 ms steps; used for the inputs whose CV11..18 is 0).
//  Same as the GBM DELAY tab of the macOS version (AppDelegate.m). The fields show seconds;
//  the sliders hold the CV value itself (0..255).
//

#include "DelayTab.h"
#include "ui_delaytab.h"
#include "MainWindow.h"
#include "DccDecoder.h"
#include "PomConnection.h"
#include "CvNames.h"
#include <QSignalBlocker>

DelayTab::DelayTab(MainWindow *mainWindow, QWidget *parent) : DecoderTab(mainWindow, parent), ui(new Ui::DelayTab)
{
  ui->setupUi(this);
  connectDelay(CV::DelayIn1, ui->cv11Slider, ui->cv11Text, 0.01);
  connectDelay(CV::DelayIn2, ui->cv12Slider, ui->cv12Text, 0.01);
  connectDelay(CV::DelayIn3, ui->cv13Slider, ui->cv13Text, 0.01);
  connectDelay(CV::DelayIn4, ui->cv14Slider, ui->cv14Text, 0.01);
  connectDelay(CV::DelayIn5, ui->cv15Slider, ui->cv15Text, 0.01);
  connectDelay(CV::DelayIn6, ui->cv16Slider, ui->cv16Text, 0.01);
  connectDelay(CV::DelayIn7, ui->cv17Slider, ui->cv17Text, 0.01);
  connectDelay(CV::DelayIn8, ui->cv18Slider, ui->cv18Text, 0.01);
  connectDelay(CV::Delay_off, ui->cv34Slider, ui->cv34Text, 0.1);
  connect(ui->buttonGBMDelayTabDefaults, &QPushButton::clicked, this, &DelayTab::pushedDefaults);
  connect(ui->buttonGBMDelayTabGet, &QPushButton::clicked, this, &DelayTab::pushedGet);
  connect(ui->buttonGBMDelayTabSet, &QPushButton::clicked, this, &DelayTab::pushedSet);
}

DelayTab::~DelayTab()
{
  delete ui;
}

void DelayTab::connectDelay(int cvNumber, QSlider *slider, QDoubleSpinBox *field, double unit)
{
  // unit: the number of seconds of one CV step (0.01 for CV11..18, 0.1 for CV34)
  // The field reacts on Return / leaving the field and on the arrows, not on every typed character
  field->setKeyboardTracking(false);
  connect(slider, &QSlider::valueChanged, this, [this, cvNumber](int value) {storeDelayCv(cvNumber, value);});
  connect(field, &QDoubleSpinBox::valueChanged, this, [this, cvNumber, unit](double value) {storeDelayCv(cvNumber, qRound(value / unit));});
}

void DelayTab::storeDelayCv(int cvNumber, int cvValue)
{
  if (cvValue > 255) cvValue = 255;
  if (cvValue < 0) cvValue = 0;
  decoder->setCv(cvNumber, cvValue);
  updateTab();
  colorSetButton(true);
}

void DelayTab::pushedDefaults()
{
  for (int cvNumber = CV::DelayIn1; cvNumber <= CV::DelayIn8; cvNumber++) decoder->setCv(cvNumber, 0);
  decoder->setCv(CV::Delay_off, 15);                      // Delay all: 1.5 seconds
  colorSetButton(true);
  updateTab();
}

void DelayTab::pushedGet()
{
  for (int cvNumber = CV::DelayIn1; cvNumber <= CV::DelayIn8; cvNumber++) pom->verifyCv(cvNumber);
  pom->verifyCv(CV::Delay_off);
  colorSetButton(false);
}

void DelayTab::pushedSet()
{
  for (int cvNumber = CV::DelayIn1; cvNumber <= CV::DelayIn8; cvNumber++) pom->writeCv(cvNumber);
  pom->writeCv(CV::Delay_off);
  colorSetButton(false);
}

void DelayTab::updateTab()
{
  // The fields and sliders are set without calling storeDelayCv
  const struct {int cv; QSlider *slider; QDoubleSpinBox *field; double unit;} delays[] = {
    {CV::DelayIn1, ui->cv11Slider, ui->cv11Text, 0.01}, {CV::DelayIn2, ui->cv12Slider, ui->cv12Text, 0.01},
    {CV::DelayIn3, ui->cv13Slider, ui->cv13Text, 0.01}, {CV::DelayIn4, ui->cv14Slider, ui->cv14Text, 0.01},
    {CV::DelayIn5, ui->cv15Slider, ui->cv15Text, 0.01}, {CV::DelayIn6, ui->cv16Slider, ui->cv16Text, 0.01},
    {CV::DelayIn7, ui->cv17Slider, ui->cv17Text, 0.01}, {CV::DelayIn8, ui->cv18Slider, ui->cv18Text, 0.01},
    {CV::Delay_off, ui->cv34Slider, ui->cv34Text, 0.1}
  };
  for (const auto &delay : delays) {
    QSignalBlocker blockSlider(delay.slider);
    QSignalBlocker blockField(delay.field);
    delay.slider->setValue(decoder->getCv(delay.cv));
    delay.field->setValue(decoder->getCv(delay.cv) * delay.unit);
  }
}

void DelayTab::colorSetButton(bool red)
{
  setButtonRed(ui->buttonGBMDelayTabSet, red);
}
