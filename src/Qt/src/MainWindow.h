//
//  MainWindow.h
//  Programmer GBM-POM (Qt)
//
//  Created by Aiko Pras on 21-11-2026.
//  Copyright (c) 2026 by Aiko Pras. All rights reserved.
//
//  See MainWindow.cpp
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include "DccDecoder.h"

namespace Ui { class MainWindow; }
class PomConnection;
class DecoderTab;
class PreferencesDialog;
class HelpWindow;
class RelaysTab;

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow() override;

  DccDecoder *decoder() {return &dccDecoder;}
  PomConnection *pom() {return pomConnection;}
  void updateTabs();                      // Shows the current CV values on the main window and all tabs
  void readAllCvs();
  void setAddressField(int rsAddress);
  void showGeneralStatus(const QString &text);

private:
  Ui::MainWindow *ui;
  DccDecoder dccDecoder;
  PomConnection *pomConnection;
  PreferencesDialog *preferencesDialog;
  HelpWindow *helpWindow;
  // The tabs, in the same order as on the window. The REVERSER, RELAYS and SPEED tabs are only visible for that decoder type
  enum TabIndex {ControlIndex, DelayIndex, SensitivityIndex, ReverserIndex, RelaysIndex, SpeedIndex, InitialiseIndex, CvIndex};
  QList<DecoderTab *> tabs;
  RelaysTab *relaysTab;
  QString nonInitialisedMessage;          // Shown again at the end of the run that found a non-initialised decoder

  void createMenus();
  void addTabs();
  void takeDecoderAddress();
  void selectAddressPushed();
  void searchNonInitialisedDecoder();
  void ledOnPushed(bool checked);
  void restartPushed();
  void cvReceived(int cvNumber, uint8_t cvValue);
  void updateMainWindow();
  void showPreferences();
  void showHelp();
  void showAbout();
};

#endif // MAINWINDOW_H
