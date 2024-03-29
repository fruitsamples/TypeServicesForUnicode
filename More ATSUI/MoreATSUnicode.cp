/*
*	File:		MoreATSUnicode.cp of TypeServicesForUnicode
* 
*	Contains:	Convenience setters and getters for ATSUI.
*	
*	Version:	2.0
* 
*  Change History (most recent first):
*           11/16/2004      Modernized for Mac OS X 10.3 and later
*				10/14/1999      Changed accessor names
*                           Added ATSUI 1.2 accessors
*                           Added bulk accessors for QD style bits
*                           Added QD style adjustments
*				7/27/1999       Updated for Metrowerks Codewarror Pro 2.1				
*				7/01/1998       Created
*
*	Disclaimer:	IMPORTANT:  This Apple software is supplied to you by Apple Computer, Inc.
*				("Apple") in consideration of your agreement to the following terms, and your
*				use, installation, modification or redistribution of this Apple software
*				constitutes acceptance of these terms.  If you do not agree with these terms,
*				please do not use, install, modify or redistribute this Apple software.
*
*				In consideration of your agreement to abide by the following terms, and subject
*				to these terms, Apple grants you a personal, non-exclusive license, under AppleÕs
*				copyrights in this original Apple software (the "Apple Software"), to use,
*				reproduce, modify and redistribute the Apple Software, with or without
*				modifications, in source and/or binary forms; provided that if you redistribute
*				the Apple Software in its entirety and without modifications, you must retain
*				this notice and the following text and disclaimers in all such redistributions of
*				the Apple Software.  Neither the name, trademarks, service marks or logos of
*				Apple Computer, Inc. may be used to endorse or promote products derived from the
*				Apple Software without specific prior written permission from Apple.  Except as
*				expressly stated in this notice, no other rights or licenses, express or implied,
*				are granted by Apple herein, including but not limited to any patent rights that
*				may be infringed by your derivative works or by other works in which the Apple
*				Software may be incorporated.
*
*				The Apple Software is provided by Apple on an "AS IS" basis.  APPLE MAKES NO
*				WARRANTIES, EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION THE IMPLIED
*				WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY AND FITNESS FOR A PARTICULAR
*				PURPOSE, REGARDING THE APPLE SOFTWARE OR ITS USE AND OPERATION ALONE OR IN
*				COMBINATION WITH YOUR PRODUCTS.
*
*				IN NO EVENT SHALL APPLE BE LIABLE FOR ANY SPECIAL, INDIRECT, INCIDENTAL OR
*				CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
*				GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
*				ARISING IN ANY WAY OUT OF THE USE, REPRODUCTION, MODIFICATION AND/OR DISTRIBUTION
*				OF THE APPLE SOFTWARE, HOWEVER CAUSED AND WHETHER UNDER THEORY OF CONTRACT, TORT
*				(INCLUDING NEGLIGENCE), STRICT LIABILITY OR OTHERWISE, EVEN IF APPLE HAS BEEN
*				ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*	Copyright:  Copyright © 2005 Apple Computer, Inc, All Rights Reserved
*/

#include "MoreATSUnicode.h"


/* Getters and Setters */

/* There's a pair for every basic data type because I didn't feel like making ugly generic polymorphic accessors. */

OSStatus
atsuSetBooleanAttribute( ATSUStyle iStyle, Boolean iSetting, ATSUAttributeTag iTag )
{
	ByteCount				theSize = sizeof(iSetting);
	ATSUAttributeValuePtr	thePtr = &iSetting;

	return ATSUSetAttributes( iStyle, 1, &iTag, &theSize, &thePtr );
}


OSStatus
atsuSetFixedAttribute( ATSUStyle iStyle, Fixed iValue, ATSUAttributeTag iTag )
{
	ByteCount				theSize = sizeof(iValue);
	ATSUAttributeValuePtr	thePtr = &iValue;

	return ATSUSetAttributes( iStyle, 1, &iTag, &theSize, &thePtr );
}


OSStatus
atsuSetFractAttribute( ATSUStyle iStyle, Fract iValue, ATSUAttributeTag iTag )
{
	ByteCount				theSize = sizeof(iValue);
	ATSUAttributeValuePtr	thePtr = &iValue;

	return ATSUSetAttributes( iStyle, 1, &iTag, &theSize, &thePtr );
}

OSStatus
atsuSetIntAttribute( ATSUStyle iStyle, SInt32 iValue, ATSUAttributeTag iTag )
{
	ByteCount				theSize = sizeof(iValue);
	ATSUAttributeValuePtr	thePtr = &iValue;

	return ATSUSetAttributes( iStyle, 1, &iTag, &theSize, &thePtr );
}

OSStatus
atsuSetShortAttribute( ATSUStyle iStyle, SInt16 iValue, ATSUAttributeTag iTag )
{
	ByteCount				theSize = sizeof(iValue);
	ATSUAttributeValuePtr	thePtr = &iValue;

	return ATSUSetAttributes( iStyle, 1, &iTag, &theSize, &thePtr );
}

OSStatus
atsuSetPtrAttribute( ATSUStyle iStyle, void* iValue, ATSUAttributeTag iTag )
{
	ByteCount				theSize = sizeof(iValue);
	ATSUAttributeValuePtr	thePtr = &iValue;

	return ATSUSetAttributes( iStyle, 1, &iTag, &theSize, &thePtr );
}

OSStatus
atsuSetQDStyleBits( ATSUStyle iStyle, StyleParameter iQDStyleBits )
{
	ATSUAttributeTag		theTags[] = {	kATSUQDBoldfaceTag,
											kATSUQDItalicTag,
											kATSUQDUnderlineTag,
											kATSUQDCondensedTag,
											kATSUQDExtendedTag };
	ByteCount				theSizes[] = {	sizeof(Boolean),
											sizeof(Boolean),
											sizeof(Boolean),
											sizeof(Boolean),
											sizeof(Boolean) };
	ATSUAttributeValuePtr	theValues[ sizeof(theTags) / sizeof(ATSUAttributeTag) ];
	Boolean					isBold, isItalic, isUnderline, isCondensed, isExtended;
	
	isBold = (iQDStyleBits & bold) != 0;
	isItalic = (iQDStyleBits & italic) != 0;
	isUnderline = (iQDStyleBits & underline) != 0;
	isCondensed = (iQDStyleBits & condense) != 0;
	isExtended = (iQDStyleBits & extend) != 0;
	
	// C doesn't allow this to be done in an initializer, so we have to fill in the pointers here.
	theValues[0] = &isBold;
	theValues[1] = &isItalic;
	theValues[2] = &isUnderline;
	theValues[3] = &isCondensed;
	theValues[4] = &isExtended;
	
	return ATSUSetAttributes( iStyle, sizeof(theTags) / sizeof(ATSUAttributeTag), theTags, theSizes, theValues );
}

OSStatus
atsuSetColor( ATSUStyle iStyle, RGBColor color )
{
	ATSUAttributeTag		theTag = kATSUColorTag;
	ByteCount				theSize = sizeof(RGBColor);
	ATSUAttributeValuePtr	thePtr = &color;
	return ATSUSetAttributes( iStyle, 1, &theTag, &theSize, &thePtr );
}


OSStatus
atsuSetBaselineClass( ATSUStyle iStyle, BslnBaselineClass baselineClass )
{
	ATSUAttributeTag		theTag = kATSUBaselineClassTag;
	ByteCount				theSize = sizeof(baselineClass);
	ATSUAttributeValuePtr	thePtr = &baselineClass;
	return ATSUSetAttributes( iStyle, 1, &theTag, &theSize, &thePtr );
}


OSStatus
atsuSetPriorityJustOverride( ATSUStyle iStyle, ATSJustPriorityWidthDeltaOverrides overrides )
{
	ATSUAttributeTag		theTag = kATSUPriorityJustOverrideTag;
	ByteCount				theSize = sizeof(ATSJustPriorityWidthDeltaOverrides);
	ATSUAttributeValuePtr	thePtr = &overrides;
	return ATSUSetAttributes( iStyle, 1, &theTag, &theSize, &thePtr );
}


OSStatus
atsuSetBooleanLayoutControl( ATSUTextLayout iLayout, Boolean iValue, ATSUAttributeTag iTag )
{
	ByteCount				theSize = sizeof(iValue);
	ATSUAttributeValuePtr	thePtr = &iValue;

	return ATSUSetLayoutControls( iLayout, 1, &iTag, &theSize, &thePtr );
}


OSStatus
atsuSetFixedLayoutControl( ATSUTextLayout iLayout, Fixed iValue, ATSUAttributeTag iTag )
{
	ByteCount				theSize = sizeof(iValue);
	ATSUAttributeValuePtr	thePtr = &iValue;

	return ATSUSetLayoutControls( iLayout, 1, &iTag, &theSize, &thePtr );
}


OSStatus
atsuSetFractLayoutControl( ATSUTextLayout iLayout, Fract iValue, ATSUAttributeTag iTag )
{
	ByteCount				theSize = sizeof(iValue);
	ATSUAttributeValuePtr	thePtr = &iValue;

	return ATSUSetLayoutControls( iLayout, 1, &iTag, &theSize, &thePtr );
}


OSStatus
atsuSetShortLayoutControl( ATSUTextLayout iLayout, SInt16 iValue, ATSUAttributeTag iTag )
{
	ByteCount				theSize = sizeof(iValue);
	ATSUAttributeValuePtr	thePtr = &iValue;

	return ATSUSetLayoutControls( iLayout, 1, &iTag, &theSize, &thePtr );
}


OSStatus
atsuSetPtrLayoutControl( ATSUTextLayout iLayout, void* iValue, ATSUAttributeTag iTag )
{
	ByteCount				theSize = sizeof(iValue);
	ATSUAttributeValuePtr	thePtr = &iValue;

	return ATSUSetLayoutControls( iLayout, 1, &iTag, &theSize, &thePtr );
}


OSStatus
atsuSetLayoutBaselineValues( ATSUTextLayout iLayout, BslnBaselineRecord iValues )
{
	ATSUAttributeTag		theTag = kATSULineBaselineValuesTag;
	ByteCount				theSize = sizeof(BslnBaselineRecord);
	ATSUAttributeValuePtr	thePtr = &iValues;

	return ATSUSetLayoutControls( iLayout, 1, &theTag, &theSize, &thePtr );
}


OSStatus
atsuSetLayoutOptions( ATSUTextLayout iLayout, UInt32 iOptions )
{
	ATSUAttributeTag		theTag = kATSULineLayoutOptionsTag;
	ByteCount				theSize = sizeof(iOptions);
	ATSUAttributeValuePtr	thePtr = &iOptions;

	return ATSUSetLayoutControls( iLayout, 1, &theTag, &theSize, &thePtr );
}


OSStatus
atsuSetLayoutLineSpan( ATSUTextLayout iLayout, Fixed iAscent, Fixed iDescent )
{
	ATSUAttributeTag		theTags[2] = { kATSULineAscentTag, kATSULineDescentTag };
	ByteCount				theSizes[2] = { sizeof(Fixed), sizeof(Fixed) };
	ATSUAttributeValuePtr	thePtrs[2];
	
	thePtrs[0] = &iAscent;
	thePtrs[1] = &iDescent;
	
	return ATSUSetLayoutControls( iLayout, 2, theTags, theSizes, thePtrs );
}

	
OSStatus
atsuSetFixedLineControl( ATSUTextLayout iLayout, UniCharArrayOffset iLineStart, Fixed iValue, ATSUAttributeTag iTag )
{
	ByteCount				theSize = sizeof(iValue);
	ATSUAttributeValuePtr	thePtr = &iValue;

	return ATSUSetLineControls( iLayout, iLineStart, 1, &iTag, &theSize, &thePtr );
}


OSStatus
atsuSetFractLineControl( ATSUTextLayout iLayout, UniCharArrayOffset iLineStart, Fract iValue, ATSUAttributeTag iTag )
{
	ByteCount				theSize = sizeof(iValue);
	ATSUAttributeValuePtr	thePtr = &iValue;

	return ATSUSetLineControls( iLayout, iLineStart, 1, &iTag, &theSize, &thePtr );
}


OSStatus
atsuSetLineBaselineValues( ATSUTextLayout iLayout, UniCharArrayOffset iLineStart, BslnBaselineRecord iValues )
{
	ATSUAttributeTag		theTag = kATSULineBaselineValuesTag;
	ByteCount				theSize = sizeof(BslnBaselineRecord);
	ATSUAttributeValuePtr	thePtr = &iValues;

	return ATSUSetLineControls( iLayout, iLineStart, 1, &theTag, &theSize, &thePtr );
}


OSStatus
atsuSetLineOptions( ATSUTextLayout iLayout, UniCharArrayOffset iLineStart, UInt32 iOptions )
{
	ATSUAttributeTag		theTag = kATSULineLayoutOptionsTag;
	ByteCount				theSize = sizeof(iOptions);
	ATSUAttributeValuePtr	thePtr = &iOptions;

	return ATSUSetLineControls( iLayout, iLineStart, 1, &theTag, &theSize, &thePtr );
}

OSStatus
atsuSetLineSpan( ATSUTextLayout iLayout, UniCharArrayOffset iLineStart, Fixed iAscent, Fixed iDescent )
{
	ATSUAttributeTag		theTags[2] = { kATSULineAscentTag, kATSULineDescentTag };
	ByteCount				theSizes[2] = { sizeof(Fixed), sizeof(Fixed) };
	ATSUAttributeValuePtr	thePtrs[2];
	
	thePtrs[0] = &iAscent;
	thePtrs[1] = &iDescent;
	
	return ATSUSetLineControls( iLayout, iLineStart, 2, theTags, theSizes, thePtrs );
}


OSStatus
atsuGetOneAttribute( ATSUStyle 				iStyle,
					 ATSUAttributeTag 		iTag,
					 ByteCount 				iExpectedValueSize,
					 ATSUAttributeValuePtr 	oValue )
{
	// Filters out kATSUNotSetErr
	OSStatus status = ATSUGetAttribute( iStyle, iTag, iExpectedValueSize, oValue, NULL );
	return (status == kATSUNotSetErr) ? noErr : status;
}

OSStatus
atsuGetQDStyleBits( ATSUStyle iStyle, Style *oQDStyleBits )
{
	ATSUAttributeTag		theTags[] = {	kATSUQDBoldfaceTag,
											kATSUQDItalicTag,
											kATSUQDUnderlineTag,
											kATSUQDCondensedTag,
											kATSUQDExtendedTag };
	Style					theBits[] = {	bold, italic, underline, condense, extend };
	
	OSStatus	status;
	int 		i;
	
	*oQDStyleBits = normal;
	
	for ( i = 0; i < sizeof(theTags) / sizeof(ATSUAttributeTag); ++i ) {
		Boolean		thisFlag;
		status = ATSUGetAttribute( iStyle, theTags[i], sizeof(thisFlag), &thisFlag, NULL );
		if ( status == noErr && thisFlag )
			*oQDStyleBits |= theBits[i];
		else if ( status == kATSUNotSetErr )
			status = noErr;
		else
			break;	// give up and return the error code.
	}
	
	return status;
}

OSStatus
atsuGetOneLayoutControl( ATSUTextLayout 		iLayout,
						 ATSUAttributeTag 		iTag,
						 ByteCount 				iExpectedValueSize,
						 ATSUAttributeValuePtr 	oValue )
{
	// Filters out kATSUNotSetErr
	OSStatus status = ATSUGetLayoutControl( iLayout, iTag, iExpectedValueSize, oValue, NULL );
	return (status == kATSUNotSetErr) ? noErr : status;
}


OSStatus
atsuGetOneLineControl( ATSUTextLayout 			iLayout,
					   UniCharArrayOffset		iLineStart,
					   ATSUAttributeTag 		iTag,
					   ByteCount 				iExpectedValueSize,
					   ATSUAttributeValuePtr	oValue )
{
	// Filters out kATSUNotSetErr
	OSStatus status = ATSUGetLineControl( iLayout, iLineStart, iTag, iExpectedValueSize, oValue, NULL );
	if ( status == kATSUNotSetErr )
		// If it wasn't set for the line explicitly, try the layout.
		status = ATSUGetLayoutControl(  iLayout, iTag, iExpectedValueSize, oValue, NULL );
	return (status == kATSUNotSetErr) ? noErr : status;
}


OSStatus
atsuGetLayoutLineSpan( ATSUTextLayout	iLayout,
					   Fixed			*oAscent,
					   Fixed			*oDescent )
{
	OSStatus	status;
	
	// Even with GetAllLayoutControls, we have to make another call to get the values, so
	// we just make two calls to our getter.
	status = atsuGetLayoutAscent( iLayout, oAscent );
	if ( status == noErr ) status = atsuGetLayoutDescent( iLayout, oDescent );
	return status;
}


OSStatus
atsuGetLineSpan( ATSUTextLayout		iLayout,
				 UniCharArrayOffset	iLineStart,
				 Fixed				*oAscent,
				 Fixed				*oDescent )
{
	OSStatus status;
	status = atsuGetLineAscent( iLayout, iLineStart, oAscent );
	if ( status == noErr ) status = atsuGetLineDescent( iLayout, iLineStart, oDescent );
	return status;
}


/* This is setting a buncha things at once, so we don't use the accessors we've defined but go back to basics. */

OSStatus
atsuSetStyleFromGrafPtr( ATSUStyle iStyle, GrafPtr iGrafPtr, Boolean clearExistingAttributes )
{
	OSStatus	status = noErr;
	GrafPtr		savedPort;
	
	ATSUAttributeTag		theTags[] = {	kATSUFontTag,
											kATSUSizeTag,
											kATSUQDBoldfaceTag,
											kATSUQDItalicTag,
											kATSUQDUnderlineTag,
											kATSUQDCondensedTag,
											kATSUQDExtendedTag,
											kATSUColorTag };
	ByteCount				theSizes[] = {	sizeof(ATSUFontID),
											sizeof(Fixed),
											sizeof(Boolean),
											sizeof(Boolean),
											sizeof(Boolean),
											sizeof(Boolean),
											sizeof(Boolean),
											sizeof(RGBColor) };
	ATSUAttributeValuePtr	theValues[ sizeof(theTags) / sizeof(ATSUAttributeTag) ];
	
	ATSUFontID			atsuFont;
	Fixed				atsuSize;
	RGBColor			textColor;
	Boolean				isBold, isItalic, isUnderline, isCondensed, isExtended;
	short				txFont, txSize;
	SInt16				txFace, intrinsicStyle;
	
	
	GetPort( &savedPort );
	
	if ( iGrafPtr == NULL ) 
		iGrafPtr = savedPort;
	else
		SetPort( iGrafPtr );

	txFont = GetPortTextFont(iGrafPtr);
	txSize = GetPortTextSize(iGrafPtr);
	txFace = GetPortTextFace(iGrafPtr);
	
	status = FMGetFontFromFontFamilyInstance( txFont, txFace, &atsuFont, &intrinsicStyle );
	require( status == noErr, EXIT );
	
	// Need to adjust the QD style bits based on the intrinsic style of the font.
	// Otherwise, you can end up doing things like artifically bolding an already-bold font.
	txFace &= ~intrinsicStyle;
	
	isBold = ( txFace & bold ) != 0;
	isItalic = ( txFace & italic ) != 0;
	isUnderline = ( txFace & underline ) != 0;
	isCondensed = ( txFace & condense ) != 0;
	isExtended = ( txFace & extend ) != 0;
	
	if ( txSize == 0 )
		txSize = (short) ( GetScriptVariable( FontToScript( txFont ), smScriptPrefFondSize ) & 0xFFFFU );	// this would already be set correctly in a brand-new style
	atsuSize = Long2Fix( txSize );
	
	GetForeColor( &textColor );
	
	// At this point, the only thing that could fail is the set, so it's OK to clear the old settings.
	if ( clearExistingAttributes ) 
		status = ATSUClearStyle( iStyle );
	require( status == noErr, EXIT );
	
	// C doesn't allow this to be done in an initializer, so we have to fill in the pointers here.
	theValues[0] = &atsuFont;
	theValues[1] = &atsuSize;
	theValues[2] = &isBold;
	theValues[3] = &isItalic;
	theValues[4] = &isUnderline;
	theValues[5] = &isCondensed;
	theValues[6] = &isExtended;
	theValues[7] = &textColor;
	
	status = ATSUSetAttributes( iStyle, sizeof(theTags) / sizeof(ATSUAttributeTag), theTags, theSizes, theValues );
	
EXIT:	
	SetPort( savedPort );

	return status;
}


/*	NB: even though ATSUI's coordinate system is left-handed, positive rotations
	are counterclockwise, so we use the inverse transformation of what you might expect. */

static void RotateAndTranslate( Fixed x, Fixed y, Fixed rotateCos, Fixed rotateSin, Fixed x0, Fixed y0, atsuFixedPt *pt )
{
	pt->x =  FixMul(x, rotateCos) + FixMul(y, rotateSin) + x0;
	pt->y =  FixMul(y, rotateCos) - FixMul(x, rotateSin) + y0;
}



// set this to use the version of atsuMeasureRotatedTextImage() that uses a scratch layout
#define USE_CONSY_ROTATION 0

#if !USE_CONSY_ROTATION

OSStatus
atsuMeasureRotatedTextImage( ATSUTextLayout iTextLayout, 
							UniCharArrayOffset iLineOffset,
							UniCharCount iLineLength,
							ATSUTextMeasurement iLocationX,
							ATSUTextMeasurement iLocationY,
							atsuFixedPt *p1,
							atsuFixedPt *p2,
							atsuFixedPt *p3,
							atsuFixedPt *p4 )
{
/* 
   The simple approach is to simply set the line rotation to zero, get the image bounds
   and set it back again. The drawback to doing this is that it will potentially blow
   away cached layout information for the *entire* layout.
 */
 
	OSStatus 				status = noErr;
	Fixed 					lineRotation = 0;
	Rect imageRect;
	
	// Get the current rotation.
	status = atsuGetLayoutRotation( iTextLayout, &lineRotation );
	require( status == noErr, EXIT );
	
	// If the line rotation is a multiple of 90 degrees, the standard routine gives us the right answer.
	if ( lineRotation == 0 || abs(lineRotation) == Long2Fix(90) || abs(lineRotation) == Long2Fix(180) ) {
		status = ATSUMeasureTextImage( iTextLayout, iLineOffset, iLineLength, iLocationX, iLocationY, &imageRect );
		if ( status == noErr ) {
			p1->x = Long2Fix(imageRect.left);	p1->y = Long2Fix(imageRect.top);
			p2->x = Long2Fix(imageRect.right);	p2->y = Long2Fix(imageRect.top);
			p3->x = Long2Fix(imageRect.right);	p3->y = Long2Fix(imageRect.bottom);
			p4->x = Long2Fix(imageRect.left);	p4->y = Long2Fix(imageRect.bottom);
		}
	} else {
		// Set the rotation to zero temporarily.
		status = atsuSetLayoutRotation( iTextLayout, 0 );
		require( status == noErr, EXIT );
		
		// Get the bounding box.
		status = ATSUMeasureTextImage( iTextLayout, iLineOffset, iLineLength, 0, 0, &imageRect );
		require( status == noErr, EXIT );
		
		if ( status == noErr ) {
			// rotate and translate it.
			Fixed lineAngle = FixMul(lineRotation, kATSRadiansFactor);
			Fixed rotateCos = Frac2Fix(FracCos(lineAngle));
			Fixed rotateSin = Frac2Fix(FracSin(lineAngle));
			
			RotateAndTranslate( Long2Fix(imageRect.left), Long2Fix(imageRect.top), rotateCos, rotateSin, iLocationX, iLocationY, p1 );
			RotateAndTranslate( Long2Fix(imageRect.right), Long2Fix(imageRect.top), rotateCos, rotateSin, iLocationX, iLocationY, p2 );
			RotateAndTranslate( Long2Fix(imageRect.right), Long2Fix(imageRect.bottom), rotateCos, rotateSin, iLocationX, iLocationY, p3 );
			RotateAndTranslate( Long2Fix(imageRect.left), Long2Fix(imageRect.bottom), rotateCos, rotateSin, iLocationX, iLocationY, p4 );
		}
		
		// Put the old rotation back
		if ( lineRotation != 0 ) {
			status = atsuSetLayoutRotation( iTextLayout, lineRotation );
		}
	}
	
EXIT:
	return status;
}

#else

OSStatus
atsuMeasureRotatedTextImage( ATSUTextLayout iTextLayout, 
							UniCharArrayOffset iLineOffset,
							UniCharCount iLineLength,
							ATSUTextMeasurement iLocationX,
							ATSUTextMeasurement iLocationY,
							atsuFixedPt *p1,
							atsuFixedPt *p2,
							atsuFixedPt *p3,
							atsuFixedPt *p4 )
{
/* 
   This version leaves the original layout alone, cloning the line in question into a new temporary layout to
   do the unrotated measurement.
   
   For small layouts, this can be slower than the above version.
 */
 
	OSStatus 		status = noErr;
	Fixed 			lineRotation = 0;	
	Rect 			imageRect;
	ATSUTextLayout	tempLayout = NULL;
		
	// Get the current rotation.
	status = atsuGetLineRotation( iTextLayout, &lineRotation );
	require( status == noErr, EXIT );
	
	// If the line rotation is a multiple of 90 degrees, the standard routine gives us the right answer.
	if ( lineRotation == 0 || abs(lineRotation) == Long2Fix(90) || abs(lineRotation) == Long2Fix(180) ) {
		status = ATSUMeasureTextImage( iTextLayout, iLineOffset, iLineLength, iLocationX, iLocationY, &imageRect );
		if ( status == noErr ) {
			p1->x = Long2Fix(imageRect.left);	p1->y = Long2Fix(imageRect.top);
			p2->x = Long2Fix(imageRect.right);	p2->y = Long2Fix(imageRect.top);
			p3->x = Long2Fix(imageRect.right);	p3->y = Long2Fix(imageRect.bottom);
			p4->x = Long2Fix(imageRect.left);	p4->y = Long2Fix(imageRect.bottom);
		}
	} else {
		// Create a new layout that covers the given lines
		status = atsuCloneTextLayout( iTextLayout, iLineOffset, iLineLength, true, &tempLayout );
		require( status == noErr, EXIT );
		
		// Force rotation to 0.
		status = atsuSetLineRotation( tempLayout, 0 );
		require( status == noErr, EXIT );
		
		// Get the bounding box
		status = ATSUMeasureTextImage( tempLayout, iLineOffset, iLineLength, 0, 0, &imageRect );
		
		if ( status == noErr ) {
			// rotate and translate it.
			Fixed lineAngle = FixMul(lineRotation, kATSRadiansFactor);
			Fixed rotateCos = Frac2Fix(FracCos(lineAngle));
			Fixed rotateSin = Frac2Fix(FracSin(lineAngle));
			
			RotateAndTranslate( Long2Fix(imageRect.left), Long2Fix(imageRect.top), rotateCos, rotateSin, iLocationX, iLocationY, p1 );
			RotateAndTranslate( Long2Fix(imageRect.right), Long2Fix(imageRect.top), rotateCos, rotateSin, iLocationX, iLocationY, p2 );
			RotateAndTranslate( Long2Fix(imageRect.right), Long2Fix(imageRect.bottom), rotateCos, rotateSin, iLocationX, iLocationY, p3 );
			RotateAndTranslate( Long2Fix(imageRect.left), Long2Fix(imageRect.bottom), rotateCos, rotateSin, iLocationX, iLocationY, p4 );
		}
	}
	
EXIT:
	if ( tempLayout ) (void) ATSUDisposeTextLayout( tempLayout );

	return status;
}

#endif



OSStatus atsuCloneTextLayout(
			ATSUTextLayout iTextLayout, UniCharArrayOffset iOffset, UniCharCount iLength, Boolean expandToLineBoundary,
			ATSUTextLayout *oTextLayout )
{
	OSStatus			status = noErr;
	void				*theText;
	Boolean				textIsHandle;
	UniCharArrayOffset	textOffset;
	UniCharCount		textLength;
	UniCharCount		textTotalLength;
	ATSUTextLayout		newLayout = NULL;
	UniCharArrayOffset	currentOffset, endOffset, breakOffset;
	ItemCount			breakCount;

	// First get our hands on the text info.
	status = ATSUGetTextLocation( iTextLayout, &theText, &textIsHandle, &textOffset, &textLength, &textTotalLength );
	require( status == noErr, EXIT );
	
	// Fix up the input range
	if ( iOffset == kATSUFromTextBeginning ) iOffset = textOffset;
	if ( iLength == kATSUToTextEnd ) iLength = textLength;
	
	if ( iOffset < textOffset ) {
		iLength -= (textOffset - iOffset);
		iOffset = textOffset;
	}
	if ( iLength > textLength )
		iLength = textLength;
	
	endOffset = iOffset + iLength;
	
	// Now adjust outwards to a line boundary if necessary.
	if ( expandToLineBoundary ) {
		// The easy one: find the first break after our range.
		status = ATSUGetSoftLineBreaks( iTextLayout, endOffset - 1, kATSUToTextEnd, 1, &breakOffset, &breakCount );
		require( status == noErr, EXIT );
		
		if ( breakCount > 0 )
			endOffset = breakOffset;
		else
			endOffset = textOffset + textLength;
		
		iLength = endOffset - iOffset;
				
		// Search for the first line break before this range.
		// We add one to the length so that a break just before the range gets picked up.
		breakOffset = textOffset;
		do {
			status = ATSUGetSoftLineBreaks( iTextLayout, breakOffset, iOffset - breakOffset + 1, 1, &breakOffset, &breakCount );
			require( status == noErr, EXIT );
		} while ( breakCount > 0 );
		
		iLength += iOffset - breakOffset;
		iOffset = breakOffset;
		
		endOffset = iOffset + iLength;
	}
	
	if ( iOffset == textOffset && iLength == textLength ) {
		// If we've asked for a copy of the whole thing, just call the API.
		status = ATSUCreateAndCopyTextLayout( iTextLayout, &newLayout );
	} else
	{
		// Create the new layout.
#ifdef MAC_OS_X_VERSION_10_4
		UniCharArrayPtr textPtr = (UniCharArrayPtr) ( ( textIsHandle ) ? (*((UniCharArrayHandle)theText)) : theText );
		status = ATSUCreateTextLayoutWithTextPtr(textPtr, iOffset, iLength, textTotalLength, 0, NULL, NULL, &newLayout );
#else
		if ( textIsHandle )
			status = ATSUCreateTextLayoutWithTextHandle(
						(UniCharArrayHandle) theText, iOffset, iLength, textTotalLength, 0, NULL, NULL, &newLayout );
		else
			status = ATSUCreateTextLayoutWithTextPtr(
						(ConstUniCharArrayPtr) theText, iOffset, iLength, textTotalLength, 0, NULL, NULL, &newLayout );
#endif

		// Set the styles
		if ( status == noErr ) {
			currentOffset = iOffset;
			while ( (currentOffset < endOffset) && (status == noErr) ) {
				ATSUStyle			runStyle;
				UniCharArrayOffset	runStart;
				UniCharCount		runLength;
				
				// @@@ Will this work for an incomplete layout?
				status = ATSUGetRunStyle( iTextLayout, currentOffset, &runStyle, &runStart, &runLength );
				if ( status == noErr ) {
					// Adjust run bounds
					if ( runStart + runLength > endOffset ) {
						runLength -= runStart + runLength - endOffset;
					}
					if ( runStart < iOffset ) {
						runLength -= iOffset - runStart;
						runStart = iOffset;
					}
					status = ATSUSetRunStyle( newLayout, runStyle, runStart, runLength );
					currentOffset = runStart + runLength;	// NOT currentOffset + runLength !!!
				}
			}
		}
		
		// Copy the soft breaks and line controls.
		// @@@ Note: You may not want to copy the controls for partial lines.
		if ( status == noErr ) {
			currentOffset = iOffset;
			while ( (currentOffset < endOffset) && (status == noErr) ) {
				
				status = ATSUGetSoftLineBreaks( iTextLayout, currentOffset, endOffset - currentOffset, 1, &breakOffset, &breakCount );
				if ( status == noErr && breakCount > 0 ) {
					status = ATSUSetSoftLineBreak( newLayout, breakOffset );
					
					if (status == noErr)
						status = ATSUCopyLineControls( iTextLayout, currentOffset, newLayout, currentOffset );

					currentOffset = breakOffset + 1;
				} else {
					currentOffset = endOffset;
				}
			}
		}
		
		// Copy layout controls
		if ( status == noErr )
			status = ATSUCopyLayoutControls( iTextLayout, newLayout );
	}
	
EXIT:	
	// Clean up if there was an error.
	if ( status != noErr && newLayout != NULL ) {
		(void) ATSUDisposeTextLayout( newLayout );
		newLayout = NULL;
	}
	
	*oTextLayout = newLayout;
	return status;
}



OSStatus
atsuDrawText( ConstUniCharArrayPtr	iTextBuf,
			  UniCharArrayOffset	iFirstChar,
			  UniCharCount			iCharCount )
{
	ATSUStyle		theStyle = NULL;
	ATSUTextLayout	theLayout = NULL;
	OSStatus		status = noErr;
	
	status = ATSUCreateStyle( &theStyle );
	require( status == noErr, EXIT );
	
	// The layout and draw is going to dominate, so individual setters are just fine here.
	
	status = atsuSetStyleFromGrafPtr( theStyle, NULL, false );
	require( status == noErr, EXIT );
	
	status = atsuSetNoCaretAngle( theStyle, true );	// this is for the pen loc calculation later. it also makes things marginally faster.
	require( status == noErr, EXIT );
	
	status = ATSUCreateTextLayoutWithTextPtr(
					iTextBuf, iFirstChar, iCharCount, iFirstChar + iCharCount,
					1, &iCharCount, &theStyle, &theLayout );
	require( status == noErr, EXIT );
	
	// We like to show all the text if possible.
	status = ATSUSetTransientFontMatching( theLayout, true );
	
	// @@@ Any other layout controls that should be forced?
	// E.g., you may want to turn off hangers, optical alignment, &c.
	
	if ( status == noErr ) {
		// Now for the fun part. We need to figure out where to leave the pen when we're finished.
		// We've suppressed caret angles for two reasons: first, this prevents ATSUI from mucking with the last caret
		// position, and second, it makes the location on the baseline easy to compute.
		Boolean	lineDirection;
		Point	penLoc;
		ATSUCaret	theCaret;
		
		GetPen( &penLoc );
		status = atsuGetLayoutLineDirection( theLayout, &lineDirection );
		require( status == noErr, EXIT );
		
		// We need the rightmost caret position. The typographic measure is in ideal coordinates, which won't do,
		// and the image bounds gives us the last bit position, not where the last advance takes us. We could
		// extract this from the highlight, but that would mean poking around inside a region. The solution is to
		// use the last caret position, which is always guaranteed to be at the end of the line. For a right-to-left
		// line, use the first caret position instead.
		status = ATSUOffsetToPosition( theLayout, lineDirection ? iFirstChar : iFirstChar + iCharCount, false,
										&theCaret, NULL, NULL );
		require( status == noErr, EXIT );
		
		// Finally, we get to draw the text
		status = ATSUDrawText(
					theLayout, kATSUFromTextBeginning, kATSUToTextEnd,
					kATSUUseGrafPortPenLoc, kATSUUseGrafPortPenLoc );
		// Adjust the final pen loc.
		if ( status == noErr ) 
			MoveTo( penLoc.h + Fix2Long( theCaret.fX ), penLoc.v );
	}

EXIT:	
	if ( theLayout ) (void) ATSUDisposeTextLayout( theLayout );
	if ( theStyle ) (void) ATSUDisposeStyle( theStyle );
	
	return status;
}
