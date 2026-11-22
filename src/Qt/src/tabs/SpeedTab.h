//
//  SpeedTab.h
//  Programmer GBM-POM (Qt)
//
//  Created by Aiko Pras on 21-11-2026.
//  Copyright (c) 2026 by Aiko Pras. All rights reserved.
//
//  See SpeedTab.cpp
//

#ifndef SPEEDTAB_H
#define SPEEDTAB_H

#include "DecoderTab.h"

namespace Ui { class SpeedTab; }

class SpeedTab : public DecoderTab
{
  Q_OBJECT

public:
  explicit SpeedTab(MainWindow *mainWindow, QWidget *parent = nullptr);
  ~SpeedTab() override;
  void updateTab() override;
  void colorSetButton(bool red) override;

private:
  Ui::SpeedTab *ui;
  void storeSpeedCv(int cvNumber, const QString &text);
  void storeLength(int cvLow, int cvHigh, int length);
  void pushedDefaults();
  void pushedGet();
  void pushedSet();
};

#endif // SPEEDTAB_H
