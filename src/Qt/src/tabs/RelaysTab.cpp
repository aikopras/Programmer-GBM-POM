//
//  RelaysTab.cpp
//  Programmer GBM-POM (Qt)
//
//  Created by Aiko Pras on 21-11-2026.
//  Copyright (c) 2026 by Aiko Pras. All rights reserved.
//
//  RELAYS tab: the accessory decoder address of the relays extension board (myAddrL, CV1 and myAddrH, CV9).
//  Same as the RELAYS tab of the macOS version (AppDelegate.m). The field shows the first relays (switch) address
//  of the block of four: 1, 5, 9, ... The range is 1..1024 or 1..2048, depending on the command station.
//

#include "RelaysTab.h"
#include "ui_relaystab.h"
#include "MainWindow.h"
#include "DccDecoder.h"
#include "PomConnection.h"
#include "CvNames.h"
#include <QIntValidator>

RelaysTab::RelaysTab(MainWindow *mainWindow, QWidget *parent) : DecoderTab(mainWindow, parent), ui(new Ui::RelaysTab)
{
  ui->setupUi(this);
  explanation = ui->relaysExplanation->text();
  setMaxSwitchAddress(1024);                              // Until the command station reports its version
  connect(ui->relaysAddress, &QLineEdit::editingFinished, this, &RelaysTab::enteredRelaysAddress);
  connect(ui->buttonRelaysTabGet, &QPushButton::clicked, this, &RelaysTab::pushedGet);
  connect(ui->buttonRelaysTabSet, &QPushButton::clicked, this, &RelaysTab::pushedSet);
}

RelaysTab::~RelaysTab()
{
  delete ui;
}

void RelaysTab::setMaxSwitchAddress(int address)
{
  maxSwitchAddress = address;
  ui->relaysAddress->setValidator(new QIntValidator(1, address, ui->relaysAddress));
  QString text = explanation;
  text.replace("1..1024", QString("1..%1").arg(address));
  text.replace("..., 1021", QString("..., %1").arg(address - 3));
  ui->relaysExplanation->setText(text);
}

void RelaysTab::enteredRelaysAddress()
{
  int newValue = ui->relaysAddress->text().toInt();
  if (newValue < 1) {newValue = 1;}
  if (newValue > maxSwitchAddress) {newValue = maxSwitchAddress;}
  newValue = newValue - 1;                                // entering is 1..1024 (or 1..2048) <-> storing is 0..1023 (or 0..2047)
  newValue = newValue >> 2;                               // decoder address = relays address DIV 4
  decoder->setCv(CV::myAddrL, (newValue + 1) & 0b00111111);
  decoder->setCv(CV::myAddrH, ((newValue + 1) >> 6) & 0b00000111);
  updateTab();
  colorSetButton(true);
}

void RelaysTab::pushedGet()
{
  pom->verifyCv(CV::myAddrL);
  pom->verifyCv(CV::myAddrH);
  colorSetButton(false);
}

void RelaysTab::pushedSet()
{
  // Takes also a value that is typed, but not yet entered (but not the text "Undefined")
  if (ui->relaysAddress->hasAcceptableInput()) enteredRelaysAddress();
  pom->writeCv(CV::myAddrL);
  pom->writeCv(CV::myAddrH);
  colorSetButton(false);
}

void RelaysTab::updateTab()
{
  int cv1 = decoder->getCv(CV::myAddrL);
  int cv9 = decoder->getCv(CV::myAddrH);
  // Only fill the field if CV9 indicates a valid relays address (128 = 0x80 means: address not set)
  if (cv9 < 8) {
    int myAddr = (((cv9 & 0x7F) << 6) | cv1) - 1;         // 3 bits from cv9 (the high bits) plus 6 bits from cv1
    myAddr = myAddr * 4 + 1;                              // Compensate since we store blocks of four and 0..1023 instead of 1..1024
    ui->relaysAddress->setText(QString::number(myAddr));
  }
  else ui->relaysAddress->setText("Undefined");
}

void RelaysTab::colorSetButton(bool red)
{
  setButtonRed(ui->buttonRelaysTabSet, red);
}
