//
//  InitialiseTab.h
//  Programmer GBM-POM (Qt)
//
//  Created by Aiko Pras on 21-11-2026.
//  Copyright (c) 2026 by Aiko Pras. All rights reserved.
//
//  See InitialiseTab.cpp
//

#ifndef INITIALISETAB_H
#define INITIALISETAB_H

#include "DecoderTab.h"

namespace Ui { class InitialiseTab; }

class InitialiseTab : public DecoderTab
{
  Q_OBJECT

public:
  explicit InitialiseTab(MainWindow *mainWindow, QWidget *parent = nullptr);
  ~InitialiseTab() override;
  void updateTab() override;
  void colorSetButton(bool red) override;

private:
  Ui::InitialiseTab *ui;
  void enteredNewRsAddress();
  void pushedSet();
  void updateDecoderAddress();
};

#endif // INITIALISETAB_H
