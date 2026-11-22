//
//  RelaysTab.h
//  Programmer GBM-POM (Qt)
//
//  Created by Aiko Pras on 21-11-2026.
//  Copyright (c) 2026 by Aiko Pras. All rights reserved.
//
//  See RelaysTab.cpp
//

#ifndef RELAYSTAB_H
#define RELAYSTAB_H

#include "DecoderTab.h"

namespace Ui { class RelaysTab; }

class RelaysTab : public DecoderTab
{
  Q_OBJECT

public:
  explicit RelaysTab(MainWindow *mainWindow, QWidget *parent = nullptr);
  ~RelaysTab() override;
  void updateTab() override;
  void colorSetButton(bool red) override;
  void setMaxSwitchAddress(int address);

private:
  Ui::RelaysTab *ui;
  int maxSwitchAddress;                   // 1024 or 2048, depending on the command station
  QString explanation;                    // The text of the .ui file, with 1024 as maximum relays address
  void enteredRelaysAddress();
  void pushedGet();
  void pushedSet();
};

#endif // RELAYSTAB_H
