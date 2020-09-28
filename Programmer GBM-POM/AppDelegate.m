//
//  AppDelegate.m
//  CV Editor for Feedback decoder
//
//  Created by Aiko Pras on 26-02-12 / 20-03-2013
//  Copyright (c) 2013 by Aiko Pras. All rights reserved.
//

#import "AppDelegate.h"
#import "DCCDecoder.h"
#import "TCPConnection.h"
#import "PreferencesController.h"

@implementation AppDelegate

// Main objects
@synthesize dccDecoderObject             = _dccDecoderObject;
@synthesize tcpConnectionsObject         = _tcpConnectionsObject;
@synthesize preferencesController        = _preferencesController;
// Main user interface window plus tab part
@synthesize window                       = _window;
@synthesize windowTabs                   = _windowTabs;
// General properties common to all decoders
@synthesize address                      = _address;
@synthesize DecoderVendor                = _DecoderVendor;
@synthesize DecoderVersion               = _DecoderVersion;
@synthesize DecoderType                  = _DecoderType;
@synthesize DecoderSubType               = _DecoderSubType;
@synthesize DecoderErrors                = _DecoderErrors;
@synthesize ledOn                        = _ledOn;
//
// Control tab properties
@synthesize comboRsRetry                 = _comboRsRetry;
@synthesize comboCmdSystem               = _comboCmdSystem;
@synthesize comboDecType                 = _comboDecType;
@synthesize buttonControlTabDefaults     = _buttonControlTabDefaults;
@synthesize buttonControlTabGet          = _buttonControlTabGet;
@synthesize buttonControlTabSet          = _buttonControlTabSet;
//
// GBM Delay tab properties
@synthesize cv11Text                     = _cv11Text;
@synthesize cv12Text                     = _cv12Text;
@synthesize cv13Text                     = _cv13Text;
@synthesize cv14Text                     = _cv14Text;
@synthesize cv15Text                     = _cv15Text;
@synthesize cv16Text                     = _cv16Text;
@synthesize cv17Text                     = _cv17Text;
@synthesize cv18Text                     = _cv18Text;
@synthesize cv34Text                     = _cv34Text;
@synthesize cv11Slider                   = _cv11Slider;
@synthesize cv12Slider                   = _cv12Slider;
@synthesize cv13Slider                   = _cv13Slider;
@synthesize cv14Slider                   = _cv14Slider;
@synthesize cv15Slider                   = _cv15Slider;
@synthesize cv16Slider                   = _cv16Slider;
@synthesize cv17Slider                   = _cv17Slider;
@synthesize cv18Slider                   = _cv18Slider;
@synthesize cv34Slider                   = _cv34Slider;
@synthesize buttonGBMDelayTabDefaults    = _buttonGBMDelayTabDefaults;
@synthesize buttonGBMDelayTabGet         = _buttonGBMDelayTabGet;
@synthesize buttonGBMDelayTabSet         = _buttonGBMDelayTabSet;
//
// Sensitivity tab properties
@synthesize minSamples                   = _minSamples;
@synthesize tresholdOn                   = _tresholdOn;
@synthesize tresholdOff                  = _tresholdOff;
@synthesize tresholdOnText               = _tresholdOnText;
@synthesize tresholdOffText              = _tresholdOffText;
@synthesize buttonSensitivityTabDefaults = _buttonSensitivityTabDefaults;
@synthesize buttonSensitivityTabGet      = _buttonSensitivityTabGet;
@synthesize buttonSensitivityTabSet      = _buttonSensitivityTabSet;
//
// Reverser tab properties
@synthesize comboReverserA               = _comboReverserA;
@synthesize comboReverserB               = _comboReverserB;
@synthesize comboReverserC               = _comboReverserC;
@synthesize comboReverserD               = _comboReverserD;
@synthesize comboReverserS1              = _comboReverserS1;
@synthesize comboReverserS2              = _comboReverserS2;
@synthesize comboReverserS3              = _comboReverserS3;
@synthesize comboReverserS4              = _comboReverserS4;
@synthesize comboReverserPolarization    = _comboReverserPolarization;
@synthesize buttonReverserTabDefaults    = _buttonReverserTabDefaults;
@synthesize buttonReverserTabGet         = _buttonReverserTabGet;
@synthesize buttonReverserTabSet         = _buttonReverserTabSet;
//
// Relays tab properties
@synthesize relaysAddress                = _relaysAddress;
@synthesize buttonRelaysTabGet           = _buttonRelaysTabGet;
@synthesize buttonRelaysTabSet           = _buttonRelaysTabSet;
//
// Speed Measurement tab properties
@synthesize comboSpeedFeedback1          = _comboSpeedFeedback1;
@synthesize comboSpeedFeedback2          = _comboSpeedFeedback2;
@synthesize speedLengthTrack1            = _speedLengthTrack1;
@synthesize speedLengthTrack2            = _speedLengthTrack2;
@synthesize buttonSpeedTabDefaults       = _buttonSpeedTabDefaults;
@synthesize buttonSpeedTabGet            = _buttonSpeedTabGet;
@synthesize buttonSpeedTabSet            = _buttonSpeedTabSet;
//
// Initialise tab properties
@synthesize rsAddressNew                 = _rsAddressNew;
@synthesize buttonIniTabSet              = _buttonIniTabSet;
//
// Status bar properties
@synthesize connectionStatus             = _connectionStatus;
@synthesize sendStatus                   = _sendStatus;
@synthesize receiveStatus                = _receiveStatus;
@synthesize progressIndicator            = _progressIndicator;

// ************************************************************************************************************
// ******************************************** DEFINE CV MAPPINGS ********************************************
// ************************************************************************************************************
#define myAddrL        1
#define version        7
#define VID            8
#define myAddrH        9
#define myRSAddr      10
#define DelayIn1      11
#define DelayIn2      12
#define DelayIn3      13
#define DelayIn4      14
#define DelayIn5      15
#define DelayIn6      16
#define DelayIn7      17
#define DelayIn8      18
#define CmdStation    19
#define RSRetry       20
#define Search        23
#define PoMStart      24
#define Restart       25
#define DccQuality    26
#define DecType       27
#define BiDi          28
#define Config        29
#define VID_2         30
#define Min_Samples   33
#define Delay_off     34
#define Threshold_on  35
#define Threshold_of  36
#define Speed1_Out    37
#define Speed1_LL     38
#define Speed1_LH     39
#define Speed2_Out    40
#define Speed2_LL     41
#define Speed2_LH     42
#define FB_A          43
#define FB_B          44
#define FB_C          45
#define FB_D          46
#define FB_S1         47
#define FB_S2         48
#define FB_S3         49
#define FB_S4         50
#define Polarization  51


// ************************************************************************************************************
// ********************************************** INITIALIZATION **********************************************
// ************************************************************************************************************
- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
  // Step 1: dccDecoderObject
  // Allocate memory and initialise a new instance of the DCCDecoder class
  _dccDecoderObject = [[DCCDecoderClass alloc] init];
  [_dccDecoderObject initialise];
  // Step 2: preferences
  // Check if the preferences file exists. If not, create it
  [self checkPreferences];
  // Step 3: tcpConnectionsObject
  // Allocate memory and initialise a new instance of the TCPConnection class
  _tcpConnectionsObject = [[TCPConnectionsClass alloc] init];
  // Now open the TCP connection
  [_tcpConnectionsObject openTcp];
// TEST ONLY
  [_dccDecoderObject setDecoderAddress:100];
  [self.address setIntValue:_dccDecoderObject.decoderAddress];
  //
  // Step 4: UI tabs
  [self hideOptionalTabs];
  [self updateTabs];
  // Step 5: initialise progress indicator
  [_progressIndicator setDisplayedWhenStopped: NO];
}

- (void) updateTabs {
  [self updateMainWindow];
  [self updateControlTab];
  [self updateGBMDelayTab];
  [self updateSensitivityTab];
  [self updateIniTab];
  [self updateCvTab];
  if ([_dccDecoderObject getCv:DecType] != 49) [self hideReverserTab];
  if ([_dccDecoderObject getCv:DecType] != 50) [self hideRelaysTab];
  if ([_dccDecoderObject getCv:DecType] != 52) [self hideSpeedTab];
  if ([_dccDecoderObject getCv:DecType] == 49) {[self showReverserTab]; [self updateReverserTab];}
  if ([_dccDecoderObject getCv:DecType] == 50) {[self showRelaysTab];[self updateRelaysTab];}
  if ([_dccDecoderObject getCv:DecType] == 52) {[self showSpeedTab];[self updateSpeedTab];}
}

// ************************************************************************************************************
// ********************************** FEEDBACK MESSAGE RECEIVED BY THE TCP OBJECT *****************************
// ************************************************************************************************************
- (void)feedbackPacketReceivedForAddress:(int)decoderAddress withCV:(int)cvNumber withValue:(u_int8_t)cvValue {
  NSLog(@"Feedback received. Address:%d CV:%d Value:%d", decoderAddress, cvNumber, cvValue);
  [_dccDecoderObject setCv:cvNumber withValue:cvValue];
  [self updateTabs];
}

- (void)sendNextPomVerifyPacketFromQueueCompleted{
  // NSLog(@"All PoM verify packets are send");
}

- (void)sendNextPomWritePacketFromQueueCompleted{
  // NSLog(@"All PoM write packets are send");
}

// ************************************************************************************************************
// ************************************* USER INTERFACE METHODS - MAIN WINDOW *********************************
// ************************************************************************************************************
- (IBAction)takeDecoderAddressFrom:(id)sender {
  // NSLog(@"User input - Decoder address: %i", [sender intValue]);
  int newValue = [sender intValue];  
  if (newValue < 1) {newValue = 1;}
  if (newValue > 128) {newValue = 128;}
  [_dccDecoderObject setDecoderAddress:newValue];
}

- (IBAction)selectAddressPushed:(id)sender {
  [self readLastInputFromTextFields];
  [self readAllCvs];
}

- (IBAction)ledOnPushed:(id)sender {
  [self readLastInputFromTextFields];
  if ([_ledOn state]) {
    [_dccDecoderObject setCv:Search withValue:1];
    [_tcpConnectionsObject queuePomWritePacketForCV:Search];
    [_tcpConnectionsObject sendNextPomWritePacketFromQueue];
    [self setButtonTitleFor:_ledOn toString:@"LED ON" withColor:[NSColor redColor]];
  }
  else {
    [_dccDecoderObject setCv:Search withValue:0];
    [_tcpConnectionsObject queuePomWritePacketForCV:Search];
    [_tcpConnectionsObject sendNextPomWritePacketFromQueue];
    [self setButtonTitleFor:_ledOn toString:@"LED ON" withColor:[NSColor blackColor]];
  }
}

- (IBAction)restartPushed:(id)sender {
  [self readLastInputFromTextFields];
  [_dccDecoderObject setCv:Restart withValue:0x0D];
  [_tcpConnectionsObject queuePomWritePacketForCV:Restart];
  [_tcpConnectionsObject sendNextPomWritePacketFromQueue];
  // Read all CVs again, after a delay of 0.3 seconds
  [self performSelector:@selector(readAllCvs) withObject:nil afterDelay:0.3];
}

- (void)readAllCvs{
  uint8_t cvNumber;
  [_tcpConnectionsObject queuePomVerifyPacketForCV:1];
  for (cvNumber= 7; cvNumber <= 20; cvNumber++) [_tcpConnectionsObject queuePomVerifyPacketForCV:cvNumber];
  for (cvNumber=23; cvNumber <= 24; cvNumber++) [_tcpConnectionsObject queuePomVerifyPacketForCV:cvNumber];
  for (cvNumber=26; cvNumber <= 30; cvNumber++) [_tcpConnectionsObject queuePomVerifyPacketForCV:cvNumber];
  for (cvNumber=33; cvNumber <= 51; cvNumber++) [_tcpConnectionsObject queuePomVerifyPacketForCV:cvNumber];
  [_tcpConnectionsObject sendNextPomVerifyPacketFromQueue];
  // Remove possible red color from SET buttons
  [self colorGetButtonControlTab:0];
  [self colorGetButtonGBMDelayTab:0];
  [self colorGetButtonIniTab:0];
  [self colorGetButtonRelaysTab:0];
  [self colorGetButtonReverserTab:0];
  [self colorGetButtonSensitivityTab:0];
  [self colorGetButtonSpeedTab:0];
}

- (void) updateMainWindow {
  [_DecoderVendor  setObjectValue:[_dccDecoderObject DecoderVendor]];
  [_DecoderVersion setObjectValue:[_dccDecoderObject DecoderVersion]];
  [_DecoderType    setObjectValue:[_dccDecoderObject DecoderType]];
  [_DecoderSubType setObjectValue:[_dccDecoderObject DecoderSubType]];
  [_DecoderErrors  setObjectValue:[_dccDecoderObject DecoderErrors]];
  if ([_dccDecoderObject getCv:Search]) [self setButtonTitleFor:_ledOn toString:@"LED ON" withColor:[NSColor redColor]];
  else                                  [self setButtonTitleFor:_ledOn toString:@"LED ON" withColor:[NSColor blackColor]];
}


// ************************************************************************************************************
// ************************** METHODS FOR STATUS LINE AND PROGRESS INDICATOR **********************************
// ************************************************************************************************************
- (void)showGeneralStatus:(NSString *) statustext {[_connectionStatus setObjectValue:statustext];}
- (void)showSendStatus:   (NSString *) statustext {[_sendStatus       setObjectValue:statustext];}
- (void)showReceiveStatus:(NSString *) statustext {[_receiveStatus    setObjectValue:statustext];}


- (void)progressIndicator:(BOOL) activity {
  if (activity == YES) [_progressIndicator startAnimation: self];
  if (activity == NO)  [_progressIndicator stopAnimation: self];
}

- (void)showStatusLineForCV:(int)cvNumber withValue:(float)cvValue {
  // NOTE: FUNCTION IS CURRENTLY NOT BEING USED
  int adrInt = [_dccDecoderObject decoderAddress];
  int cvIntValue = cvValue;
  NSString * message = @"RSbus address = ";
  message = [message stringByAppendingString:[NSString stringWithFormat:@"%d", adrInt]];
  message = [message stringByAppendingString:[NSString stringWithFormat:@" / CV "]];
  message = [message stringByAppendingString:[NSString stringWithFormat:@"%d", cvNumber]];
  message = [message stringByAppendingString:[NSString stringWithFormat:@" = "]];
  message = [message stringByAppendingString:[NSString stringWithFormat:@"%d", cvIntValue]];
  [self showGeneralStatus:message];
}


// ************************************************************************************************************
// ************************************* USER INTERFACE METHODS - CONTROL TAB *********************************
// ************************************************************************************************************
- (IBAction)selectedRsRetry:(id)sender {
  uint8_t newValue = [sender intValue];
  if (newValue < 0) {newValue = 0;}
  if (newValue > 2) {newValue = 2;}
  [_dccDecoderObject setCv:RSRetry withValue:newValue];
  [self colorGetButtonControlTab:1];
}

- (IBAction)selectedCmdSystem:(id)sender {
  NSString *newString = [sender stringValue];
  uint8_t newValue = 1; // Select the default value
  if ([newString isEqualToString:@"standard"]) {newValue = 0;} // so not the default
  if ([newString isEqualToString:@"Lenz"])     {newValue = 1;} // Lenz is the default
  [_dccDecoderObject setCv:CmdStation withValue:newValue];
  [self colorGetButtonControlTab:1];
}

- (IBAction)selectedDecType:(id)sender {
  NSString *newString = [sender stringValue];
  uint8_t newValue = 48; // Select the default value 0x00110000 (=normal)
  if ([newString isEqualToString:@"reverser"]) {newValue = 49;}
  if ([newString isEqualToString:@"relay"])    {newValue = 50;}
  if ([newString isEqualToString:@"speed"])    {newValue = 52;}
  [_dccDecoderObject setCv:DecType withValue:newValue];
  [self colorGetButtonControlTab:1];
  [self updateTabs];
}

- (IBAction)pushedControlTabDefaults:(id)sender {
  [self readLastInputFromTextFields];
  [_dccDecoderObject setCv:RSRetry    withValue:0];
  [_dccDecoderObject setCv:CmdStation withValue:1];
  [_dccDecoderObject setCv:DecType    withValue:48];
  [self colorGetButtonControlTab:1];
  [self updateTabs];
}

- (IBAction)pushedControlTabGet:(id)sender {
  [self readLastInputFromTextFields];
  [_tcpConnectionsObject queuePomVerifyPacketForCV:RSRetry];
  [_tcpConnectionsObject queuePomVerifyPacketForCV:CmdStation];
  [_tcpConnectionsObject queuePomVerifyPacketForCV:DecType];
  [_tcpConnectionsObject sendNextPomVerifyPacketFromQueue];
  [self colorGetButtonControlTab:0];
}

- (IBAction)pushedControlTabSet:(id)sender {
  [self readLastInputFromTextFields];
  [_tcpConnectionsObject queuePomWritePacketForCV:RSRetry];
  [_tcpConnectionsObject queuePomWritePacketForCV:CmdStation];
  [_tcpConnectionsObject queuePomWritePacketForCV:DecType];
  [_tcpConnectionsObject sendNextPomWritePacketFromQueue];
  [self colorGetButtonControlTab:0];
}

- (void) updateControlTab {
  NSString *newString;
  // RsRetry
  [_comboRsRetry setIntValue:[_dccDecoderObject getCv:RSRetry]];
  // Command System
  newString = @"Lenz";      // default
  if ([_dccDecoderObject getCv:CmdStation] == 0) newString = @"standard";
  if ([_dccDecoderObject getCv:CmdStation] == 1) newString = @"Lenz";
  [_comboCmdSystem selectItemWithObjectValue: newString];
  // DecType
  newString = @"normal";   // default
  if ([_dccDecoderObject getCv:DecType] == 49) newString = @"reverser";
  if ([_dccDecoderObject getCv:DecType] == 50) newString = @"relay";
  if ([_dccDecoderObject getCv:DecType] == 52) newString = @"speed";
  [_comboDecType selectItemWithObjectValue: newString];
}

- (void)colorGetButtonControlTab:(int)isRed {
  if (isRed) [self setButtonTitleFor:_buttonControlTabSet toString:@"SET" withColor:[NSColor redColor]];
    else     [self setButtonTitleFor:_buttonControlTabSet toString:@"SET" withColor:[NSColor blackColor]];
}


// ************************************************************************************************************
// ************************************ USER INTERFACE METHODS - GBM DELAY TAB ********************************
// ************************************************************************************************************
// The names of the IBActions have not been updated to reflect the latest coding conventions
- (IBAction)selectedCv11:(id)sender {[self storeGBMDelayCv:DelayIn1  with:[sender floatValue]];}
- (IBAction)selectedCv12:(id)sender {[self storeGBMDelayCv:DelayIn2  with:[sender floatValue]];}
- (IBAction)selectedCv13:(id)sender {[self storeGBMDelayCv:DelayIn3  with:[sender floatValue]];}
- (IBAction)selectedCv14:(id)sender {[self storeGBMDelayCv:DelayIn4  with:[sender floatValue]];}
- (IBAction)selectedCv15:(id)sender {[self storeGBMDelayCv:DelayIn5  with:[sender floatValue]];}
- (IBAction)selectedCv16:(id)sender {[self storeGBMDelayCv:DelayIn6  with:[sender floatValue]];}
- (IBAction)selectedCv17:(id)sender {[self storeGBMDelayCv:DelayIn7  with:[sender floatValue]];}
- (IBAction)selectedCv18:(id)sender {[self storeGBMDelayCv:DelayIn8  with:[sender floatValue]];}
- (IBAction)selectedCv34:(id)sender {[self storeGBMDelayCv:Delay_off with:[sender floatValue]];}

- (IBAction)pushedGBMDelayTabDefaults:(id)sender {
  [self readLastInputFromTextFields];
  [_dccDecoderObject setCv:DelayIn1  withValue:0];
  [_dccDecoderObject setCv:DelayIn2  withValue:0];
  [_dccDecoderObject setCv:DelayIn3  withValue:0];
  [_dccDecoderObject setCv:DelayIn4  withValue:0];
  [_dccDecoderObject setCv:DelayIn5  withValue:0];
  [_dccDecoderObject setCv:DelayIn6  withValue:0];
  [_dccDecoderObject setCv:DelayIn7  withValue:0];
  [_dccDecoderObject setCv:DelayIn8  withValue:0];
  [_dccDecoderObject setCv:Delay_off withValue:15]; // Delay all: 150 msec
  [self colorGetButtonGBMDelayTab:1];
  [self updateGBMDelayTab];
}

- (IBAction)pushedGBMDelayTabGet:(id)sender {
  [self readLastInputFromTextFields];
  [_tcpConnectionsObject queuePomVerifyPacketForCV:DelayIn1];
  [_tcpConnectionsObject queuePomVerifyPacketForCV:DelayIn2];
  [_tcpConnectionsObject queuePomVerifyPacketForCV:DelayIn3];
  [_tcpConnectionsObject queuePomVerifyPacketForCV:DelayIn4];
  [_tcpConnectionsObject queuePomVerifyPacketForCV:DelayIn5];
  [_tcpConnectionsObject queuePomVerifyPacketForCV:DelayIn6];
  [_tcpConnectionsObject queuePomVerifyPacketForCV:DelayIn7];
  [_tcpConnectionsObject queuePomVerifyPacketForCV:DelayIn8];
  [_tcpConnectionsObject queuePomVerifyPacketForCV:Delay_off];
  [_tcpConnectionsObject sendNextPomVerifyPacketFromQueue];
  [self colorGetButtonGBMDelayTab:0];
}

- (IBAction)pushedGBMDelayTabSet:(id)sender {
  [self readLastInputFromTextFields];
  [_tcpConnectionsObject queuePomWritePacketForCV:DelayIn1];
  [_tcpConnectionsObject queuePomWritePacketForCV:DelayIn2];
  [_tcpConnectionsObject queuePomWritePacketForCV:DelayIn3];
  [_tcpConnectionsObject queuePomWritePacketForCV:DelayIn4];
  [_tcpConnectionsObject queuePomWritePacketForCV:DelayIn5];
  [_tcpConnectionsObject queuePomWritePacketForCV:DelayIn6];
  [_tcpConnectionsObject queuePomWritePacketForCV:DelayIn7];
  [_tcpConnectionsObject queuePomWritePacketForCV:DelayIn8];
  [_tcpConnectionsObject queuePomWritePacketForCV:Delay_off];
  [_tcpConnectionsObject sendNextPomWritePacketFromQueue];
  [self colorGetButtonGBMDelayTab:0];
}


- (void) updateGBMDelayTab {
  [_cv11Text   setFloatValue:([self cvValueFloat:DelayIn1] / 100)]; // in 10 mseconds
  [_cv12Text   setFloatValue:([self cvValueFloat:DelayIn2] / 100)];
  [_cv13Text   setFloatValue:([self cvValueFloat:DelayIn3] / 100)];
  [_cv14Text   setFloatValue:([self cvValueFloat:DelayIn4] / 100)];
  [_cv15Text   setFloatValue:([self cvValueFloat:DelayIn5] / 100)];
  [_cv16Text   setFloatValue:([self cvValueFloat:DelayIn6] / 100)];
  [_cv17Text   setFloatValue:([self cvValueFloat:DelayIn7] / 100)];
  [_cv18Text   setFloatValue:([self cvValueFloat:DelayIn8] / 100)];
  [_cv34Text   setFloatValue:([self cvValueFloat:Delay_off] / 10)];  // in 100 mseconds
  [_cv11Slider setFloatValue:([self cvValueFloat:DelayIn1] / 100)];
  [_cv12Slider setFloatValue:([self cvValueFloat:DelayIn2] / 100)];
  [_cv13Slider setFloatValue:([self cvValueFloat:DelayIn3] / 100)];
  [_cv14Slider setFloatValue:([self cvValueFloat:DelayIn4] / 100)];
  [_cv15Slider setFloatValue:([self cvValueFloat:DelayIn5] / 100)];
  [_cv16Slider setFloatValue:([self cvValueFloat:DelayIn6] / 100)];
  [_cv17Slider setFloatValue:([self cvValueFloat:DelayIn7] / 100)];
  [_cv18Slider setFloatValue:([self cvValueFloat:DelayIn8] / 100)];
  [_cv34Slider setFloatValue:([self cvValueFloat:Delay_off] / 10)];
}

- (void)storeGBMDelayCv:(uint8_t)cvNumber with:(float)cvFloatValue {
  if (cvNumber == Delay_off) cvFloatValue = cvFloatValue / 10; // Time is in 10 msec, not 100
  if (cvFloatValue > 2.55) {cvFloatValue = 2.55;}
  if (cvFloatValue < 0.00) {cvFloatValue = 0;}
  uint8_t intValue = cvFloatValue * 100;
  [_dccDecoderObject setCv:cvNumber withValue:intValue];
  [self updateTabs];
  [self colorGetButtonGBMDelayTab:1];
}

-(float)cvValueFloat:(int)number {
  // Used to transform the CV value (0..255) into a float (0,00 .. 2,55)
  // Note: we have to add a very small margin to cope with rounding errors in the TextField
  float margin = 0.0001;
  float temp = [[NSNumber numberWithInt:[_dccDecoderObject getCv:number]]floatValue];
  return (temp + margin);
}

- (void)colorGetButtonGBMDelayTab:(int)isRed {
  if (isRed) [self setButtonTitleFor:_buttonGBMDelayTabSet toString:@"SET" withColor:[NSColor redColor]];
    else     [self setButtonTitleFor:_buttonGBMDelayTabSet toString:@"SET" withColor:[NSColor blackColor]];
}


// ************************************************************************************************************
// ********************************* USER INTERFACE METHODS - SENSITIVITY TAB *********************************
// ************************************************************************************************************
- (IBAction)selectedMinSamples:(id)sender {
  uint8_t receivedInt = [sender intValue];
  if (receivedInt < 1) {receivedInt = 1;}
  if (receivedInt > 7) {receivedInt = 7;}
  [_dccDecoderObject setCv:Min_Samples withValue:receivedInt];
  [self colorGetButtonSensitivityTab:1];
  [self updateTabs];
}

- (IBAction)selectedTresholdOn:(id)sender {
  float receivedFloat = [sender floatValue];
  if (receivedFloat > 2.5) {receivedFloat = 2.5;}
  if (receivedFloat < 0.2) {receivedFloat = 0.2;}
  uint8_t cvValue = receivedFloat * 40;
  [_dccDecoderObject setCv:Threshold_on withValue:cvValue];
  [self colorGetButtonSensitivityTab:1];
  [self updateTabs];
}

- (IBAction)selectedTresholdOff:(id)sender {
  float receivedFloat = [sender floatValue];
  if (receivedFloat > 2.5) {receivedFloat = 2.5;}
  if (receivedFloat < 0.2) {receivedFloat = 0.2;}
  uint8_t cvValue = receivedFloat * 40;
  [_dccDecoderObject setCv:Threshold_of withValue:cvValue];
  [self colorGetButtonSensitivityTab:1];
  [self updateTabs];
}

- (IBAction)pushedSensitivityTabDefaults:(id)sender {
  [self readLastInputFromTextFields];
  [_dccDecoderObject setCv:Min_Samples withValue:3];
  [_dccDecoderObject setCv:Threshold_on withValue:20];
  [_dccDecoderObject setCv:Threshold_of withValue:15];
  [self colorGetButtonSensitivityTab:1];
  [self updateTabs];
}

- (IBAction)pushedSensitivityTabGet:(id)sender {
  [self readLastInputFromTextFields];
  [_tcpConnectionsObject queuePomVerifyPacketForCV:Min_Samples];
  [_tcpConnectionsObject queuePomVerifyPacketForCV:Threshold_on];
  [_tcpConnectionsObject queuePomVerifyPacketForCV:Threshold_of];
  [_tcpConnectionsObject sendNextPomVerifyPacketFromQueue];
  [self colorGetButtonSensitivityTab:0];
}

- (IBAction)pushedSensitivityTabSet:(id)sender {
  [self readLastInputFromTextFields];
  [_tcpConnectionsObject queuePomWritePacketForCV:Min_Samples];
  [_tcpConnectionsObject queuePomWritePacketForCV:Threshold_on];
  [_tcpConnectionsObject queuePomWritePacketForCV:Threshold_of];
  [_tcpConnectionsObject sendNextPomWritePacketFromQueue];
  [self colorGetButtonControlTab:0];
}

- (void) updateSensitivityTab {
  // MinSamples
  uint8_t samples = [_dccDecoderObject getCv:Min_Samples];
  [_minSamples setIntValue: samples];
  // Treshold0n
  float treshold0n = [_dccDecoderObject getCv:Threshold_on];
  [_tresholdOn setFloatValue: treshold0n / 40];
  // Treshold0ff
  float treshold0ff = [_dccDecoderObject getCv:Threshold_of];
  [_tresholdOff setFloatValue: treshold0ff / 40];
  // Text fields
  [_tresholdOnText  setStringValue:[self cvValueGbmSensitivityToString:[_dccDecoderObject getCv:Threshold_on]]];
  [_tresholdOffText setStringValue:[self cvValueGbmSensitivityToString:[_dccDecoderObject getCv:Threshold_of]]];

}

- (NSString*)cvValueGbmSensitivityToString:(uint8_t)cvValue {
  if (cvValue == 0) return @"(mA)";
  uint8_t kOhm = 600 / cvValue;
  NSString *message = @"mA   (" ;
  message = [message stringByAppendingString:[NSString stringWithFormat:@"%d KOhm)", kOhm]];
  return message;
}

- (void)colorGetButtonSensitivityTab:(int)isRed {
  if (isRed) [self setButtonTitleFor:_buttonSensitivityTabSet toString:@"SET" withColor:[NSColor redColor]];
    else     [self setButtonTitleFor:_buttonSensitivityTabSet toString:@"SET" withColor:[NSColor blackColor]];
}


// ************************************************************************************************************
// *********************************** USER INTERFACE METHODS - REVERSER TAB **********************************
// ************************************************************************************************************
- (IBAction)selectedReverserA :(id)sender {[self storeReverserCv:FB_A with:[sender stringValue]];}
- (IBAction)selectedReverserB :(id)sender {[self storeReverserCv:FB_B with:[sender stringValue]];}
- (IBAction)selectedReverserC :(id)sender {[self storeReverserCv:FB_C with:[sender stringValue]];}
- (IBAction)selectedReverserD :(id)sender {[self storeReverserCv:FB_D with:[sender stringValue]];}
- (IBAction)selectedReverserS1:(id)sender {[self storeReverserCv:FB_S1 with:[sender stringValue]];}
- (IBAction)selectedReverserS2:(id)sender {[self storeReverserCv:FB_S2 with:[sender stringValue]];}
- (IBAction)selectedReverserS3:(id)sender {[self storeReverserCv:FB_S3 with:[sender stringValue]];}
- (IBAction)selectedReverserS4:(id)sender {[self storeReverserCv:FB_S4 with:[sender stringValue]];}

- (IBAction)selectedReverserPolarization:(id)sender {
  NSString *newString = [sender stringValue];
  uint8_t newValue = 0; // Select the default value (=normal)
  if ([newString isEqualToString:@"Inverted"])    {newValue = 1;}
  [_dccDecoderObject setCv:Polarization withValue:newValue];
  [self updateTabs];
  [self colorGetButtonReverserTab:1];
}

- (IBAction)pushedReverserTabDefaults:(id)sender {
  [self readLastInputFromTextFields];
  [_dccDecoderObject setCv:FB_A withValue:0];  // Feedback section A => Feedback bit 1
  [_dccDecoderObject setCv:FB_B withValue:1];  // Feedback section B => Feedback bit 2
  [_dccDecoderObject setCv:FB_C withValue:2];  // Feedback section C => Feedback bit 3
  [_dccDecoderObject setCv:FB_D withValue:3];  // Feedback section D => Feedback bit 4
  [_dccDecoderObject setCv:FB_S1 withValue:0];  // Sensor track 1 => Feedback bit 1
  [_dccDecoderObject setCv:FB_S2 withValue:1];  // Sensor track 2 => Feedback bit 2
  [_dccDecoderObject setCv:FB_S3 withValue:1];  // Sensor track 3 => Feedback bit 2
  [_dccDecoderObject setCv:FB_S4 withValue:2];  // Sensor track 4 => Feedback bit 3
  [_dccDecoderObject setCv:Polarization withValue:0];  // J&K polarization on relays => normal
  [self updateTabs];
  [self colorGetButtonReverserTab:1];
}

- (IBAction)pushedReverserTabGet:(id)sender {
  [self readLastInputFromTextFields];
  [_tcpConnectionsObject queuePomVerifyPacketForCV:FB_A];
  [_tcpConnectionsObject queuePomVerifyPacketForCV:FB_B];
  [_tcpConnectionsObject queuePomVerifyPacketForCV:FB_C];
  [_tcpConnectionsObject queuePomVerifyPacketForCV:FB_D];
  [_tcpConnectionsObject queuePomVerifyPacketForCV:FB_S1];
  [_tcpConnectionsObject queuePomVerifyPacketForCV:FB_S2];
  [_tcpConnectionsObject queuePomVerifyPacketForCV:FB_S3];
  [_tcpConnectionsObject queuePomVerifyPacketForCV:FB_S4];
  [_tcpConnectionsObject queuePomVerifyPacketForCV:Polarization];
  [_tcpConnectionsObject sendNextPomVerifyPacketFromQueue];
  [self colorGetButtonReverserTab:0];
}

- (IBAction)pushedReverserTabSet:(id)sender {
  [self readLastInputFromTextFields];
  [_tcpConnectionsObject queuePomWritePacketForCV:FB_A];
  [_tcpConnectionsObject queuePomWritePacketForCV:FB_B];
  [_tcpConnectionsObject queuePomWritePacketForCV:FB_C];
  [_tcpConnectionsObject queuePomWritePacketForCV:FB_D];
  [_tcpConnectionsObject queuePomWritePacketForCV:FB_S1];
  [_tcpConnectionsObject queuePomWritePacketForCV:FB_S2];
  [_tcpConnectionsObject queuePomWritePacketForCV:FB_S3];
  [_tcpConnectionsObject queuePomWritePacketForCV:FB_S4];
  [_tcpConnectionsObject queuePomWritePacketForCV:Polarization];
  [_tcpConnectionsObject sendNextPomWritePacketFromQueue];
  [self colorGetButtonReverserTab:0];
}

- (void) updateReverserTab {
  [_comboReverserA  setIntValue:[_dccDecoderObject getCv:FB_A]];
  [_comboReverserB  setIntValue:[_dccDecoderObject getCv:FB_B]];
  [_comboReverserC  setIntValue:[_dccDecoderObject getCv:FB_C]];
  [_comboReverserD  setIntValue:[_dccDecoderObject getCv:FB_D]];
  [_comboReverserS1 setIntValue:[_dccDecoderObject getCv:FB_S1]];
  [_comboReverserS2 setIntValue:[_dccDecoderObject getCv:FB_S2]];
  [_comboReverserS3 setIntValue:[_dccDecoderObject getCv:FB_S3]];
  [_comboReverserS4 setIntValue:[_dccDecoderObject getCv:FB_S4]];
  // J&K polarization on relays
  if ([_dccDecoderObject getCv:Polarization] == 1) [_comboReverserPolarization selectItemWithObjectValue: @"Inverted"];
  else [_comboReverserPolarization selectItemWithObjectValue: @"Normal"];
}

- (void)storeReverserCv:(uint8_t)cvNumber with:(NSString*)newString {
  uint8_t newValue;
  if ([newString isEqualToString:@"1"]) {newValue = 1;}
  if ([newString isEqualToString:@"2"]) {newValue = 2;}
  if ([newString isEqualToString:@"3"]) {newValue = 3;}
  if ([newString isEqualToString:@"4"]) {newValue = 4;}
  if ([newString isEqualToString:@"5"]) {newValue = 5;}
  if ([newString isEqualToString:@"6"]) {newValue = 6;}
  if ([newString isEqualToString:@"7"]) {newValue = 7;}
  if ([newString isEqualToString:@"8"]) {newValue = 8;}
  if ((newValue >= 1) && (newValue <=8)) {
    [_dccDecoderObject setCv:cvNumber withValue:newValue];
    [self updateTabs];
    [self colorGetButtonReverserTab:1];
  }
}

- (void)colorGetButtonReverserTab:(int)isRed {
  if (isRed) [self setButtonTitleFor:_buttonReverserTabSet toString:@"SET" withColor:[NSColor redColor]];
  else       [self setButtonTitleFor:_buttonReverserTabSet toString:@"SET" withColor:[NSColor blackColor]];
}


// ************************************************************************************************************
// ************************************ USER INTERFACE METHODS - RELAYS TAB ***********************************
// ************************************************************************************************************
- (IBAction)enteredRelaysAddress:(id)sender {
  int newValue = [sender intValue];
  if (newValue < 1) {newValue = 1;}
  if (newValue > 1024) {newValue = 1024;}
  newValue = newValue -1;     // entering is 1..1024 <-> storing is 0..1023
  newValue = newValue >> 2;   // decoder address = relays address DIV 4
  [_dccDecoderObject setCv:myAddrL withValue:((newValue & 0b00111111)+1)];
  [_dccDecoderObject setCv:myAddrH withValue:((newValue >> 6) & 0b00000111)];
  [self updateTabs];
  [self colorGetButtonRelaysTab:1];
}

- (IBAction)pushedRelaysTabGet:(id)sender {
  [self readLastInputFromTextFields];
  [_tcpConnectionsObject queuePomVerifyPacketForCV:myAddrL];
  [_tcpConnectionsObject queuePomVerifyPacketForCV:myAddrH];
  [_tcpConnectionsObject sendNextPomVerifyPacketFromQueue];
  [self colorGetButtonRelaysTab:0];
}

- (IBAction)pushedRelaysTabSet:(id)sender {
  [self readLastInputFromTextFields];
  [_tcpConnectionsObject queuePomWritePacketForCV:myAddrL];
  [_tcpConnectionsObject queuePomWritePacketForCV:myAddrH];
  [_tcpConnectionsObject sendNextPomWritePacketFromQueue];
  [self colorGetButtonRelaysTab:0];
}

- (void) updateRelaysTab {
  int cv1 = [_dccDecoderObject getCv:myAddrL];
  int cv9 = [_dccDecoderObject getCv:myAddrH];
  int MyAddr = (((cv9 & 0x7F) << 6) | (cv1)) - 1; // 3 bits from cv9 (the high bits) plus 6 bits from cv1
  MyAddr = MyAddr * 4 + 1;  // Compensate since we store blocks of four and 0..1023 instead of 1.1024
  [_relaysAddress setIntValue:MyAddr];
}

- (void)colorGetButtonRelaysTab:(int)isRed {
  if (isRed) [self setButtonTitleFor:_buttonRelaysTabSet toString:@"SET" withColor:[NSColor redColor]];
    else     [self setButtonTitleFor:_buttonRelaysTabSet toString:@"SET" withColor:[NSColor blackColor]];
}


// ************************************************************************************************************
// ******************************* USER INTERFACE METHODS - SPEED MEASUREMENT TAB *****************************
// ************************************************************************************************************
- (IBAction)selectedSpeedFeedback1:(id)sender {[self storeSpeedCv:Speed1_Out with:[sender stringValue]];}
- (IBAction)selectedSpeedFeedback2:(id)sender {[self storeSpeedCv:Speed2_Out with:[sender stringValue]];}

- (IBAction)selectedSpeedLengthTrack1:(id)sender {
  int newValue = [sender intValue];
  if (newValue < 100) {newValue = 0;}
  if (newValue > 5000) {newValue = 5000;}
  [_dccDecoderObject setCv:Speed1_LL withValue:(newValue & 0b11111111)];
  [_dccDecoderObject setCv:Speed1_LH withValue:((newValue >> 8) & 0b11111111)];
  [self updateTabs];
  [self colorGetButtonSpeedTab:1];
}

- (IBAction)selectedSpeedLengthTrack2:(id)sender {
  int newValue = [sender intValue];
  if (newValue < 100) {newValue = 0;}
  if (newValue > 5000) {newValue = 5000;}
  [_dccDecoderObject setCv:Speed2_LL withValue:(newValue & 0b11111111)];
  [_dccDecoderObject setCv:Speed2_LH withValue:((newValue >> 8) & 0b11111111)];
  [self updateTabs];
  [self colorGetButtonSpeedTab:1];
}

- (IBAction)pushedSpeedTabDefauls:(id)sender {
  [self readLastInputFromTextFields];
  [_dccDecoderObject setCv:Speed1_Out withValue:0];
  [_dccDecoderObject setCv:Speed1_LL  withValue:0];
  [_dccDecoderObject setCv:Speed1_LH  withValue:0];
  [_dccDecoderObject setCv:Speed2_Out withValue:0];
  [_dccDecoderObject setCv:Speed2_LL  withValue:0];
  [_dccDecoderObject setCv:Speed2_LH  withValue:0];
  [self updateTabs];
  [self colorGetButtonSpeedTab:1];
}

- (IBAction)pushedSpeedTabGet:(id)sender {
  [self readLastInputFromTextFields];
  [_tcpConnectionsObject queuePomVerifyPacketForCV:Speed1_Out];
  [_tcpConnectionsObject queuePomVerifyPacketForCV:Speed1_LL];
  [_tcpConnectionsObject queuePomVerifyPacketForCV:Speed1_LH];
  [_tcpConnectionsObject queuePomVerifyPacketForCV:Speed2_Out];
  [_tcpConnectionsObject queuePomVerifyPacketForCV:Speed2_LL];
  [_tcpConnectionsObject queuePomVerifyPacketForCV:Speed2_LH];
  [_tcpConnectionsObject sendNextPomVerifyPacketFromQueue];
  [self colorGetButtonSpeedTab:0];
}

- (IBAction)pushedSpeedTabSet:(id)sender {
  [self readLastInputFromTextFields];
  [_tcpConnectionsObject queuePomWritePacketForCV:Speed1_Out];
  [_tcpConnectionsObject queuePomWritePacketForCV:Speed1_LL];
  [_tcpConnectionsObject queuePomWritePacketForCV:Speed1_LH];
  [_tcpConnectionsObject queuePomWritePacketForCV:Speed2_Out];
  [_tcpConnectionsObject queuePomWritePacketForCV:Speed2_LL];
  [_tcpConnectionsObject queuePomWritePacketForCV:Speed2_LH];
  [_tcpConnectionsObject sendNextPomWritePacketFromQueue];
  [self colorGetButtonSpeedTab:0];
}

- (void) updateSpeedTab {
  int length;
  [_comboSpeedFeedback1  setIntValue:[_dccDecoderObject getCv:Speed1_Out]];
  [_comboSpeedFeedback2  setIntValue:[_dccDecoderObject getCv:Speed2_Out]];
  length = [_dccDecoderObject getCv:Speed1_LH] * 256 + [_dccDecoderObject getCv:Speed1_LL];
  [_speedLengthTrack1 setIntValue:length];
  length = [_dccDecoderObject getCv:Speed2_LH] * 256 + [_dccDecoderObject getCv:Speed2_LL];
  [_speedLengthTrack2 setIntValue:length];

}

- (void)storeSpeedCv:(uint8_t)cvNumber with:(NSString*)newString {
  uint8_t newValue;
  if ([newString isEqualToString:@"0"]) {newValue = 0;}
  if ([newString isEqualToString:@"1"]) {newValue = 1;}
  if ([newString isEqualToString:@"2"]) {newValue = 2;}
  if ([newString isEqualToString:@"3"]) {newValue = 3;}
  if ([newString isEqualToString:@"4"]) {newValue = 4;}
  if ([newString isEqualToString:@"5"]) {newValue = 5;}
  if ([newString isEqualToString:@"6"]) {newValue = 6;}
  if ([newString isEqualToString:@"7"]) {newValue = 7;}
  if ([newString isEqualToString:@"8"]) {newValue = 8;}
  if ((newValue >= 0) && (newValue <=8)) {
    [_dccDecoderObject setCv:cvNumber withValue:newValue];
    [self updateTabs];
    [self colorGetButtonSpeedTab:1];
  }
}

- (void)colorGetButtonSpeedTab:(int)isRed {
  if (isRed) [self setButtonTitleFor:_buttonSpeedTabSet toString:@"SET" withColor:[NSColor redColor]];
    else     [self setButtonTitleFor:_buttonSpeedTabSet toString:@"SET" withColor:[NSColor blackColor]];
}


// ************************************************************************************************************
// ********************************** USER INTERFACE METHODS - INITIALISE TAB **********************************
// ************************************************************************************************************
- (IBAction)enteredNewRsAddress:(id)sender {
  // NSLog(@"User input - New RS-bus address: %i", [sender intValue]);
  int newValue = [sender intValue];
  if ((newValue >= 1) && (newValue <= 128)) {
    [_dccDecoderObject setCv:myRSAddr withValue:newValue];
    [self colorGetButtonIniTab:1];
  }
}

- (IBAction)pushedIniTabSet:(id)sender {
  [self readLastInputFromTextFields];
  // Set the address of the uninitilised decoder to 0, which will result in a PoM message with address 6000
  [_dccDecoderObject setDecoderAddress:0];
  [_address setIntValue:_dccDecoderObject.decoderAddress];
  // Since a wrong value in myRSAddr can make the decoder inaccessable, check myRSAddr again!
  uint8_t newAddress = [_dccDecoderObject getCv:myRSAddr];
  if ((newAddress >= 1) && (newAddress <= 128)) {
    // NSLog(@"New RS-Bus address: %i", newAddress);
    [_tcpConnectionsObject queuePomWritePacketForCV:myRSAddr];
    [_tcpConnectionsObject sendNextPomWritePacketFromQueue];
    // Change decoder's address to this new adres
    [_dccDecoderObject setDecoderAddress:newAddress];
    [_address setIntValue:_dccDecoderObject.decoderAddress];
    [self colorGetButtonIniTab:0];
  }
  [self updateTabs];
}

- (void)updateIniTab {
  [_rsAddressNew setIntValue:[_dccDecoderObject getCv:myRSAddr]];
}

- (void)colorGetButtonIniTab:(int)isRed {
  if (isRed) [self setButtonTitleFor:_buttonIniTabSet toString:@"SET" withColor:[NSColor redColor]];
    else     [self setButtonTitleFor:_buttonIniTabSet toString:@"SET" withColor:[NSColor blackColor]];
}


// ************************************************************************************************************
// ************************************ USER INTERFACE METHODS - CV TAB ***************************************
// ************************************************************************************************************
- (IBAction)enteredCvNumber:(id)sender {
  int newValue = [sender intValue];  
  _dccDecoderObject.cvNumber = newValue;
}

- (IBAction)enteredCvValue:(id)sender {
  uint8_t newValue = [sender intValue];
  _dccDecoderObject.cvValue = newValue;
}

- (IBAction)pushedCvTabGet:(id)sender {
  [self readLastInputFromTextFields];
  int cvNumber = [_dccDecoderObject cvNumber];
  [_tcpConnectionsObject queuePomVerifyPacketForCV:cvNumber];
  [_tcpConnectionsObject sendNextPomVerifyPacketFromQueue];
}


- (IBAction)pushedCvTabSet:(id)sender {
  [self readLastInputFromTextFields];
  [_window makeFirstResponder:sender];
  int cvNumber = [_dccDecoderObject cvNumber];
  uint8_t cvValue =  [_dccDecoderObject cvValue];
  if (cvNumber > 0) {
    [_dccDecoderObject setCv:cvNumber withValue:cvValue];
    [_tcpConnectionsObject queuePomWritePacketForCV:cvNumber];
    [_tcpConnectionsObject sendNextPomWritePacketFromQueue];
  }
}

- (IBAction)pushedCvTabResetCvs:(id)sender {
  [_dccDecoderObject setCv:VID withValue:13];
  [_tcpConnectionsObject queuePomWritePacketForCV:VID];
  [_tcpConnectionsObject sendNextPomWritePacketFromQueue];
  // Read all CVs again, after a delay of 0.3 seconds
  [self performSelector:@selector(readAllCvs) withObject:nil afterDelay:0.3];
}

- (void)updateCvTab {
  if ((_dccDecoderObject.cvNumber > 0) && (_dccDecoderObject.cvNumber <=256)) 
    [_cvValue setIntValue:[_dccDecoderObject getCv:_dccDecoderObject.cvNumber]];
}


// ************************************************************************************************************
// *************************************** Support function for all buttons ***********************************
// ************************************************************************************************************
- (void)setButtonTitleFor:(NSButton*)button toString:(NSString*)title withColor:(NSColor*)color {
  NSMutableParagraphStyle *style = [[NSMutableParagraphStyle alloc] init];
  [style setAlignment:NSCenterTextAlignment];
  NSDictionary *attrsDictionary = [NSDictionary dictionaryWithObjectsAndKeys:
                                   color, NSForegroundColorAttributeName, style, NSParagraphStyleAttributeName, nil];
  NSAttributedString *attrString = [[NSAttributedString alloc]
                                    initWithString:title attributes:attrsDictionary];
  [button setAttributedTitle:attrString];
  [style release];
  [attrString release]; 
}

- (void) readLastInputFromTextFields{
  // Trick in which we move focus away from TextFields (and others)
  // This ensures the value in the "current" textfield (thus the one that has focus) gets read
  // Should be called from all IBActions associated with buttons
  [_window makeFirstResponder:nil];
}


// ************************************************************************************************************
// **************************************** CODE FOR HIDING / REMOVING TABS ***********************************
// ************************************************************************************************************
NSTabViewItem *holderForTabReverser;
NSTabViewItem *holderForTabRelays;
NSTabViewItem *holderForTabSpeed;


- (void)hideOptionalTabs{
  // Should be called once, at program start
  // Note that, at program start, reverser is in tab 3, relays in 4 etc.
  // After removing reverser, relays gets 3 etc.
  [self hideReverserTab];
}

- (void)hideReverserTab{
  if (holderForTabReverser == nil) {
    holderForTabReverser = [[_windowTabs tabViewItemAtIndex:3] retain];
    [_windowTabs removeTabViewItem:holderForTabReverser];
  }
}

- (void)hideRelaysTab{
  if (holderForTabRelays == nil) {
    holderForTabRelays = [[_windowTabs tabViewItemAtIndex:3] retain];
    [_windowTabs removeTabViewItem:holderForTabRelays];
  }
}

- (void)hideSpeedTab{
  if (holderForTabSpeed == nil) {
    holderForTabSpeed = [[_windowTabs tabViewItemAtIndex:3] retain];
    [_windowTabs removeTabViewItem:holderForTabSpeed];
  }
}

- (void)showReverserTab{
  if (holderForTabReverser != nil) {
    [_windowTabs insertTabViewItem:holderForTabReverser atIndex:3];
    holderForTabReverser = nil;
  }
}

- (void)showRelaysTab{
  if (holderForTabRelays != nil) {
    [_windowTabs insertTabViewItem:holderForTabRelays atIndex:3];
    holderForTabRelays = nil;
  }
}

- (void)showSpeedTab{
  if (holderForTabSpeed != nil) {
    [_windowTabs insertTabViewItem:holderForTabSpeed atIndex:3];
    holderForTabSpeed = nil;
  }
}


// ************************************************************************************************************
// ***************************************** PREFERENCES WINDOW ***********************************************
// ************************************************************************************************************
-(IBAction)showPreferences:(id)sender { 
  if (_preferencesController == nil)
    _preferencesController = [[PreferencesController alloc] initWithWindowNibName:@"PreferencesController"];
  [_preferencesController showWindow:self]; 
}

- (void)checkPreferences{
  // Test if we can read the Preferences
  NSString *test1 = [[NSUserDefaults standardUserDefaults] objectForKey:@"defaultIpAddressForSending"];
  NSString *test2 = [[NSUserDefaults standardUserDefaults] objectForKey:@"defaultIpAddressForReceiving"];
  NSString *test3 = [[NSUserDefaults standardUserDefaults] objectForKey:@"defaultIpAddressForReceivingIsActive"];
  // Check if all preferences exist
  if ((test1 == nil) || (test2 == nil) || (test3 == nil)) [self initialisePreferences];
}


- (void)initialisePreferences{
  // Create a new preferences file
  [[NSUserDefaults standardUserDefaults] setObject:@"192.168.1.211"        forKey:@"defaultIpAddressForSending"];
  [[NSUserDefaults standardUserDefaults] setObject:@"192.168.1.213"        forKey:@"defaultIpAddressForReceiving"];
  [[NSUserDefaults standardUserDefaults] setBool:1                         forKey:@"defaultIpAddressForReceivingIsActive"];
}

// ************************************************************************************************************
// *************************************** dealloc and closing procedures *************************************
// ************************************************************************************************************
- (void)dealloc {[super dealloc];}

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)theApplication {return YES;}


- (NSApplicationTerminateReply)applicationShouldTerminate:(NSApplication *)sender {
  [_tcpConnectionsObject closeTcp];
  return NSTerminateNow;
}




@end
