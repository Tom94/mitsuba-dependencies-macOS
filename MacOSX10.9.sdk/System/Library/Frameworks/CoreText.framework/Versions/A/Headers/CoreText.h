/*
 *  CoreText.h
 *  CoreText
 *
 *  Copyright (c) 2006-2013 Apple Inc. All rights reserved.
 *
 */

/*!
    @header

    Thread Safety Information

    All functions in this header are thread safe unless otherwise specified.
*/

#ifndef __CORETEXT__
#define __CORETEXT__

#include <CoreText/CTDefines.h>
#include <CoreText/CTFont.h>
#include <CoreText/CTFontCollection.h>
#include <CoreText/CTFontDescriptor.h>
#include <CoreText/CTFontManager.h>
#include <CoreText/CTFontTraits.h>
#include <CoreText/CTFrame.h>
#include <CoreText/CTFramesetter.h>
#include <CoreText/CTGlyphInfo.h>
#include <CoreText/CTLine.h>
#include <CoreText/CTParagraphStyle.h>
#include <CoreText/CTRun.h>
#include <CoreText/CTRunDelegate.h>
#include <CoreText/CTStringAttributes.h>
#include <CoreText/CTTextTab.h>
#include <CoreText/CTTypesetter.h>
#include <CoreText/SFNTLayoutTypes.h>
#include <CoreText/SFNTTypes.h>

#if defined(__cplusplus)
extern "C" {
#endif

/*!
    @function   CTGetCoreTextVersion
    @abstract   Returns the version of the CoreText framework.

    @discussion This function returns a number indicating the version of the
                CoreText framework. Note that framework version is not always
                an accurate indicator of feature availability. The recommended
                way to use this function is first to check that the function
                pointer is non-NULL, followed by calling it and comparing its
                result to a defined constant (or constants). For example, to
                determine whether the CoreText API is available:
                    if (&CTGetCoreTextVersion != NULL && CTGetCoreTextVersion() >= kCTVersionNumber10_5) {
                        // CoreText API is available
                    }

    @result     The version number. This value is for comparison with the
                constants beginning with kCTVersionNumber.
*/

uint32_t CTGetCoreTextVersion( void ) CT_AVAILABLE(10_5, 3_2);

#define kCTVersionNumber10_5 0x00020000
#define kCTVersionNumber10_5_2 0x00020001
#define kCTVersionNumber10_5_3 0x00020002
#define kCTVersionNumber10_5_5 0x00020003
#define kCTVersionNumber10_6 0x00030000
#define kCTVersionNumber10_7 0x00040000
#define kCTVersionNumber10_8 0x00050000
#define kCTVersionNumber10_9 0x00060000

#if defined(__cplusplus)
}
#endif

#endif // __CORETEXT__

