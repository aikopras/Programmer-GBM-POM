//
//  AppDelegate.h
//  CV Editor for Feedback decoder
//
//  Created by Aiko Pras on 26-02-12 / 11-03-2013
//  Copyright (c) 2013 by Aiko Pras. All rights reserved.
//

#import <Cocoa/Cocoa.h>
@class PreferencesController;
@class DCCDecoderClass;
@class TCPConnectionsClass;

@interface AppDelegate : NSObject <NSApplicationDelegate>


// ************************************************************************************************************
// *************************************  METHODS THAT OTHER OBJECTS MAY USE **********************************
// ************************************************************************************************************
// Methods used by the TCP object to signal sending is ready or a (RS-bus) feedback message is received
- (void)sendNextPomVerifyPacketFromQueueCompleted;
- (void)sendNextPomWritePacketFromQueueCompleted;
- (void)feedbackPacketReceivedForAddress:(int)decoderAddress withCV:(int)cvNumber withValue:(u_int8_t)cvValue;
// Methods used by the AppDelegate and TCP object to signal status
- (void)showGeneralStatus:(NSString *) statustext;
- (void)showSendStatus:(NSString *) statustext;
- (void)showReceiveStatus:(NSString *) statustext;
- (void)progressIndicator:(BOOL) activity;


// ************************************************************************************************************
// ************************************************* GENERAL **************************************************
// ************************************************************************************************************
// Declare properties for the various main objects
@property (retain) DCCDecoderClass *dccDecoderObject;
@property (retain) TCPConnectionsClass *tcpConnectionsObject;
@property (retain) PreferencesController *preferencesController;

// Declare the properties for the main user interface window plus tab part
@property (retain) IBOutlet NSWindow *window;
@property (assign) IBOutlet NSTabView *windowTabs;

// Declare the properties/methods common to all decoders
@property (assign) IBOutlet NSTextField *address;
@property (assign) IBOutlet NSTextField *DecoderVendor;
@property (assign) IBOutlet NSTextField *DecoderVersion;
@property (assign) IBOutlet NSTextField *DecoderType;
@property (assign) IBOutlet NSTextField *DecoderSubType;
@property (assign) IBOutlet NSTextField *DecoderErrors;

@property (assign) IBOutlet NSButton *ledOn;

- (IBAction)takeDecoderAddressFrom:(id)sender;
- (IBAction)selectAddressPushed:(id)sender;
- (IBAction)ledOnPushed:(id)sender;
- (IBAction)restartPushed:(id)sender;

// Status bar (bottom part of window) 
@property (assign) IBOutlet NSTextField *connectionStatus;
@property (assign) IBOutlet NSTextField *sendStatus;
@property (assign) IBOutlet NSTextField *receiveStatus;
@property (assign) IBOutlet NSProgressIndicator *progressIndicator;


// ************************************************************************************************************
// ************************************************ CONTROL TAB ***********************************************
// ************************************************************************************************************
@property (assign) IBOutlet NSComboBox *comboRsRetry;
@property (assign) IBOutlet NSComboBox *comboCmdSystem;
@property (assign) IBOutlet NSComboBox *comboDecType;
- (IBAction)selectedRsRetry:(id)sender;
- (IBAction)selectedCmdSystem:(id)sender;
- (IBAction)selectedDecType:(id)sender;

@property (assign) IBOutlet NSButton *buttonControlTabDefaults;
@property (assign) IBOutlet NSButton *buttonControlTabGet;
@property (assign) IBOutlet NSButton *buttonControlTabSet;
- (IBAction)pushedControlTabDefaults:(id)sender;
- (IBAction)pushedControlTabGet:(id)sender;
- (IBAction)pushedControlTabSet:(id)sender;

// ************************************************************************************************************
// ************************************************* DELAY TAB ************************************************
// ************************************************************************************************************
@property (assign) IBOutlet NSTextField *cv11Text;
@property (assign) IBOutlet NSTextField *cv12Text;
@property (assign) IBOutlet NSTextField *cv13Text;
@property (assign) IBOutlet NSTextField *cv14Text;
@property (assign) IBOutlet NSTextField *cv15Text;
@property (assign) IBOutlet NSTextField *cv16Text;
@property (assign) IBOutlet NSTextField *cv17Text;
@property (assign) IBOutlet NSTextField *cv18Text;
@property (assign) IBOutlet NSTextField *cv34Text;

@property (assign) IBOutlet NSSlider *cv11Slider;
@property (assign) IBOutlet NSSlider *cv12Slider;
@property (assign) IBOutlet NSSlider *cv13Slider;
@property (assign) IBOutlet NSSlider *cv14Slider;
@property (assign) IBOutlet NSSlider *cv15Slider;
@property (assign) IBOutlet NSSlider *cv16Slider;
@property (assign) IBOutlet NSSlider *cv17Slider;
@property (assign) IBOutlet NSSlider *cv18Slider;
@property (assign) IBOutlet NSSlider *cv34Slider;

@property (assign) IBOutlet NSButton *buttonGBMDelayTabDefaults;
@property (assign) IBOutlet NSButton *buttonGBMDelayTabGet;
@property (assign) IBOutlet NSButton *buttonGBMDelayTabSet;

- (IBAction)selectedCv11:(id)sender;
- (IBAction)selectedCv12:(id)sender;
- (IBAction)selectedCv13:(id)sender;
- (IBAction)selectedCv14:(id)sender;
- (IBAction)selectedCv15:(id)sender;
- (IBAction)selectedCv16:(id)sender;
- (IBAction)selectedCv17:(id)sender;
- (IBAction)selectedCv18:(id)sender;
- (IBAction)selectedCv34:(id)sender;

- (IBAction)pushedGBMDelayTabDefaults:(id)sender;
- (IBAction)pushedGBMDelayTabGet:(id)sender;
- (IBAction)pushedGBMDelayTabSet:(id)sender;


// ************************************************************************************************************
// ******************************************* GBM SENSITIVITY TAB *********************************************
// ************************************************************************************************************
@property (assign) IBOutlet NSTextField *minSamples;
@property (assign) IBOutlet NSTextField *tresholdOn;
@property (assign) IBOutlet NSTextField *tresholdOnText;
@property (assign) IBOutlet NSTextField *tresholdOff;
@property (assign) IBOutlet NSTextField *tresholdOffText;

@property (assign) IBOutlet NSButton *buttonSensitivityTabDefaults;
@property (assign) IBOutlet NSButton *buttonSensitivityTabGet;
@property (assign) IBOutlet NSButton *buttonSensitivityTabSet;
- (IBAction)selectedMinSamples:(id)sender;
- (IBAction)selectedTresholdOn:(id)sender;
- (IBAction)selectedTresholdOff:(id)sender;
- (IBAction)pushedSensitivityTabDefaults:(id)sender;
- (IBAction)pushedSensitivityTabGet:(id)sender;
- (IBAction)pushedSensitivityTabSet:(id)sender;


// ************************************************************************************************************
// *********************************************** REVERSER TAB ***********************************************
// ************************************************************************************************************
@property (assign) IBOutlet NSComboBox *comboReverserA;
@property (assign) IBOutlet NSComboBox *comboReverserB;
@property (assign) IBOutlet NSComboBox *comboReverserC;
@property (assign) IBOutlet NSComboBox *comboReverserD;
@property (assign) IBOutlet NSComboBox *comboReverserS1;
@property (assign) IBOutlet NSComboBox *comboReverserS2;
@property (assign) IBOutlet NSComboBox *comboReverserS3;
@property (assign) IBOutlet NSComboBox *comboReverserS4;
@property (assign) IBOutlet NSComboBox *comboReverserPolarization;

- (IBAction)selectedReverserA:(id)sender;
- (IBAction)selectedReverserB:(id)sender;
- (IBAction)selectedReverserC:(id)sender;
- (IBAction)selectedReverserD:(id)sender;
- (IBAction)selectedReverserS1:(id)sender;
- (IBAction)selectedReverserS2:(id)sender;
- (IBAction)selectedReverserS3:(id)sender;
- (IBAction)selectedReverserS4:(id)sender;
- (IBAction)selectedReverserPolarization:(id)sender;

@property (assign) IBOutlet NSWindow *buttonReverserTabDefaults;
@property (assign) IBOutlet NSButton *buttonReverserTabGet;
@property (assign) IBOutlet NSButton *buttonReverserTabSet;
- (IBAction)pushedReverserTabDefaults:(id)sender;
- (IBAction)pushedReverserTabGet:(id)sender;
- (IBAction)pushedReverserTabSet:(id)sender;


// ************************************************************************************************************
// ************************************************ RELAYS TAB ************************************************
// ************************************************************************************************************
@property (assign) IBOutlet NSTextField *relaysAddress;
- (IBAction)enteredRelaysAddress:(id)sender;

@property (assign) IBOutlet NSButton *buttonRelaysTabGet;
@property (assign) IBOutlet NSButton *buttonRelaysTabSet;
- (IBAction)pushedRelaysTabGet:(id)sender;
- (IBAction)pushedRelaysTabSet:(id)sender;


// ************************************************************************************************************
// ******************************************** SPEED MEASUREMENT TAB *****************************************
// ************************************************************************************************************
@property (assign) IBOutlet NSComboBox *comboSpeedFeedback1;
@property (assign) IBOutlet NSComboBox *comboSpeedFeedback2;
@property (assign) IBOutlet NSTextField *speedLengthTrack1;
@property (assign) IBOutlet NSTextField *speedLengthTrack2;

- (IBAction)selectedSpeedFeedback1:(id)sender;
- (IBAction)selectedSpeedFeedback2:(id)sender;
- (IBAction)selectedSpeedLengthTrack1:(id)sender;
- (IBAction)selectedSpeedLengthTrack2:(id)sender;

@property (assign) IBOutlet NSButton *buttonSpeedTabDefaults;
@property (assign) IBOutlet NSButton *buttonSpeedTabGet;
@property (assign) IBOutlet NSButton *buttonSpeedTabSet;
- (IBAction)pushedSpeedTabDefauls:(id)sender;
- (IBAction)pushedSpeedTabGet:(id)sender;
- (IBAction)pushedSpeedTabSet:(id)sender;


// ************************************************************************************************************
// ********************************************** INITIALISE TAB **********************************************
// ************************************************************************************************************
@property (assign) IBOutlet NSTextField *rsAddressNew;
- (IBAction)enteredNewRsAddress:(id)sender;

@property (assign) IBOutlet NSButton *buttonIniTabSet;
- (IBAction)pushedIniTabSet:(id)sender;


// ************************************************************************************************************
// ************************************************** CV TAB **************************************************
// ************************************************************************************************************
@property (assign) IBOutlet NSTextField *cvNumber;
@property (assign) IBOutlet NSTextField *cvValue;
- (IBAction)enteredCvNumber:(id)sender;
- (IBAction)enteredCvValue:(id)sender;
- (IBAction)pushedCvTabGet:(id)sender;
- (IBAction)pushedCvTabSet:(id)sender;
- (IBAction)pushedCvTabResetCvs:(id)sender;

// ************************************************************************************************************
// ******************************************** PREFERENCES WINDOW ********************************************
// ************************************************************************************************************
- (IBAction)showPreferences:(id)sender;


@end
