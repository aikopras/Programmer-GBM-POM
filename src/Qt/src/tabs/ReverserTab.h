//
//  ReverserTab.h
//  Programmer GBM-POM (Qt)
//
//  Created by Aiko Pras on 21-11-2026.
//  Copyright (c) 2026 by Aiko Pras. All rights reserved.
//
//  See ReverserTab.cpp
//

#ifndef REVERSERTAB_H
#define REVERSERTAB_H

#include "DecoderTab.h"
#include <QList>
#include <QPair>

namespace Ui { class ReverserTab; }
class QComboBox;

class ReverserTab : public DecoderTab
{
  Q_OBJECT

public:
  explicit ReverserTab(MainWindow *mainWindow, QWidget *parent = nullptr);
  ~ReverserTab() override;
  void updateTab() override;
  void colorSetButton(bool red) override;

private:
  Ui::ReverserTab *ui;
  QList<QPair<int, QComboBox *>> feedbackCombos;   // CV and combo box of the tracks A..D and the sensors 1..4
  void storeReverserCv(int cvNumber, const QString &text);
  void selectedPolarization();
  void pushedDefaults();
  void pushedGet();
  void pushedSet();
};

#endif // REVERSERTAB_H
