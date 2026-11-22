//
//  DccDecoder.h
//  Programmer GBM-POM (Qt)
//
//  Created by Aiko Pras on 21-11-2026.
//  Copyright (c) 2026 by Aiko Pras. All rights reserved.
//
//  See DccDecoder.cpp
//

#ifndef DCCDECODER_H
#define DCCDECODER_H

#include <QString>
#include <cstdint>

class DccDecoder
{
public:
  static constexpr int MAX_CVS = 256;     // Number of CVs we support. Note that we map 257->1, 513->1 etc.

  DccDecoder();
  void initialise();
  void setCv(int number, uint8_t value);
  uint8_t getCv(int number) const;

  // The RS-Bus address (1..128) used for PoM messages. 0 is used for non-initialised decoders
  int decoderAddress;

  QString decoderVendor() const;
  QString decoderVersion() const;
  QString decoderType() const;
  QString decoderSubType() const;
  QString decoderErrors() const;

private:
  uint8_t cvStore[MAX_CVS + 1];           // Indexed by CV number, and holds its current value
};

#endif // DCCDECODER_H
