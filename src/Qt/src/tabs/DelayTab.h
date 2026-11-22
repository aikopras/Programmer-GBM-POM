//
//  DelayTab.h
//  Programmer GBM-POM (Qt)
//
//  Created by Aiko Pras on 21-11-2026.
//  Copyright (c) 2026 by Aiko Pras. All rights reserved.
//
//  See DelayTab.cpp
//

#ifndef DELAYTAB_H
#define DELAYTAB_H

#include "DecoderTab.h"

namespace Ui { class DelayTab; }
class QSlider;
class QDoubleSpinBox;

class DelayTab : public DecoderTab
{
  Q_OBJECT

public:
  explicit DelayTab(MainWindow *mainWindow, QWidget *parent = nullptr);
  ~DelayTab() override;
  void updateTab() override;
  void colorSetButton(bool red) override;

private:
  Ui::DelayTab *ui;
  void connectDelay(int cvNumber, QSlider *slider, QDoubleSpinBox *field, double unit);
  void storeDelayCv(int cvNumber, int cvValue);
  void pushedDefaults();
  void pushedGet();
  void pushedSet();
};

#endif // DELAYTAB_H
