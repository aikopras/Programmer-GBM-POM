//
//  SensitivityTab.h
//  Programmer GBM-POM (Qt)
//
//  Created by Aiko Pras on 21-11-2026.
//  Copyright (c) 2026 by Aiko Pras. All rights reserved.
//
//  See SensitivityTab.cpp
//

#ifndef SENSITIVITYTAB_H
#define SENSITIVITYTAB_H

#include "DecoderTab.h"

namespace Ui { class SensitivityTab; }

class SensitivityTab : public DecoderTab
{
  Q_OBJECT

public:
  explicit SensitivityTab(MainWindow *mainWindow, QWidget *parent = nullptr);
  ~SensitivityTab() override;
  void updateTab() override;
  void colorSetButton(bool red) override;

private:
  Ui::SensitivityTab *ui;
  void selectedMinSamples();
  void selectedThreshold(int cvNumber, double mA);
  static QString sensitivityToString(uint8_t cvValue);
  void pushedDefaults();
  void pushedGet();
  void pushedSet();
};

#endif // SENSITIVITYTAB_H
