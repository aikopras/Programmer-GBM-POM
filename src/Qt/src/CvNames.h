//
//  CvNames.h
//  Programmer GBM-POM (Qt)
//
//  Created by Aiko Pras on 21-11-2026.
//  Copyright (c) 2026 by Aiko Pras. All rights reserved.
//
//  The CV numbers, with the names of the GBM decoder firmware (OPENDECODER22GBM, cv_define.h).
//  Same as the defines at the top of AppDelegate.m of the macOS version.
//

#ifndef CVNAMES_H
#define CVNAMES_H

namespace CV
{
  // CVs used by all decoders
  constexpr int myAddrL       = 1;    // Accessory (relays) address, low order bits
  constexpr int version       = 7;
  constexpr int VID           = 8;    // Writing 13 resets all CVs to their default values
  constexpr int myAddrH       = 9;    // Accessory (relays) address, high order bits
  constexpr int myRSAddr      = 10;   // RS-Bus address of the decoder
  constexpr int DelayIn1      = 11;
  constexpr int DelayIn2      = 12;
  constexpr int DelayIn3      = 13;
  constexpr int DelayIn4      = 14;
  constexpr int DelayIn5      = 15;
  constexpr int DelayIn6      = 16;
  constexpr int DelayIn7      = 17;
  constexpr int DelayIn8      = 18;
  constexpr int CmdStation    = 19;
  constexpr int RSRetry       = 20;
  constexpr int Search        = 23;
  constexpr int Restart       = 25;
  constexpr int DccQuality    = 26;
  constexpr int DecType       = 27;
  constexpr int BiDi          = 28;
  constexpr int Config        = 29;
  constexpr int VID_2         = 30;
  // CVs used by all variants of the track occupancy decoder
  constexpr int Min_Samples   = 33;
  constexpr int Delay_off     = 34;
  constexpr int Threshold_on  = 35;
  constexpr int Threshold_of  = 36;
  // Speed measurement variant
  constexpr int Speed1_Out    = 37;
  constexpr int Speed1_LL     = 38;
  constexpr int Speed1_LH     = 39;
  constexpr int Speed2_Out    = 40;
  constexpr int Speed2_LL     = 41;
  constexpr int Speed2_LH     = 42;
  // Reverser variant
  constexpr int FB_A          = 43;
  constexpr int FB_B          = 44;
  constexpr int FB_C          = 45;
  constexpr int FB_D          = 46;
  constexpr int FB_S1         = 47;
  constexpr int FB_S2         = 48;
  constexpr int FB_S3         = 49;
  constexpr int FB_S4         = 50;
  constexpr int Polarization  = 51;
}

// The values of DecType (CV27) for the track occupancy decoder (global.h of the firmware)
namespace DecTypes
{
  constexpr int Normal        = 48;
  constexpr int Reverser      = 49;
  constexpr int Relays        = 50;
  constexpr int Speed         = 52;
}

#endif // CVNAMES_H
