//
//  DCCDecoder.h
//  CV Editor for Feedback decoder
//
//  Created by Aiko Pras on 26-02-12 / 11-03-2013
//  Copyright (c) 2013 by Aiko Pras. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface DCCDecoderClass: NSObject

// Generic decoder properties
@property (assign) int decoderAddress;     // The address of the decoder we're acting on
@property (assign) int cvNumber;           // Stores the cvNumber entered at the CV Tab
@property (assign) uint8_t cvValue;        // Maintains the associated value (which can be set or get)


// Methods
- (void)initialise;
- (void)setCv:(int)number withValue:(u_int8_t)cvValue;
- (u_int8_t)getCv:(int)number;
- (NSString *)DecoderVendor;
- (NSString *)DecoderVersion;
- (NSString *)DecoderType;
- (NSString *)DecoderSubType;
- (NSString *)DecoderErrors;


@end
