/*
*	File:		main.c of TypeServicesForUnicode
* 
*	Contains:	This is a sample program that demonstrates how to use
*					the Apple Text Services For Unicode Imaging (ATSUI) technology
*					in a Carbon Events based HIView architectured application.
*					
*					It contains a ready-to-use HIATSUIView which is a custom HIView
*
*					The HIATSUIView handles:
*						- getting and setting the text content
*						- getting and setting the styles
*						- getting and setting the selection
*						- various features like colors, wrapping, framing, justification, and transparency
*						- copying and dragging
*						- scrolling and auto-scrolling
*						- handling of	double-clicks, triple-clicks, quadruple=clicks,
*											click-and-drag, shift-clicking
*
*					The TypeForServices code handles:
*						- showing how to set the text
*						- showing how to set the text and styles
*						- showing how to rotate
*						- showing how to handle font variants
*						- showing how to handle font selection through the standard Font menu
*						- showing how to handle font selection through the standard Font panel
*						- showing how to instantiate the HIATSUIView from a nib
*						- showing how to read a text file and set the HIATSUIView content
*						- showing how to handle the clipboard
*						- showing how to handle background pictures
*
*  Note:		The project is set up so that the DEBUG macro is set to one when the "Development"
*				build style is chosen and not at all when the "Deployment" build style is chosen.
*				Thus, all the require asserts "fire" only in "Development".
*	
*	Version:	2.0
* 
*	Created:	11/4/04
*
*	Disclaimer:	IMPORTANT:  This Apple software is supplied to you by Apple Computer, Inc.
*				("Apple") in consideration of your agreement to the following terms, and your
*				use, installation, modification or redistribution of this Apple software
*				constitutes acceptance of these terms.  If you do not agree with these terms,
*				please do not use, install, modify or redistribute this Apple software.
*
*				In consideration of your agreement to abide by the following terms, and subject
*				to these terms, Apple grants you a personal, non-exclusive license, under Apple�s
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
*	Copyright:  Copyright � 2005 Apple Computer, Inc, All Rights Reserved
*/
//****************************************************
#pragma mark * compilation directives *

//****************************************************
#pragma mark -
#pragma mark * includes & imports *

#include <Carbon/Carbon.h>
#include "TypeServicesForUnicode.h"

//****************************************************
#pragma mark -
#pragma mark * typedef's, struct's, enums, defines, etc. *

//****************************************************
#pragma mark -
#pragma mark * local (static) function prototypes *

static pascal OSErr Handle_OpenApplication(const AppleEvent *inAppleEvent, AppleEvent *outAppleEvent, long inHandlerRefcon);
static pascal OSErr Handle_ReopenApplication(const AppleEvent *inAppleEvent, AppleEvent *outAppleEvent, long inHandlerRefcon);
static pascal OSErr Handle_OpenDocuments(const AppleEvent *inAppleEvent, AppleEvent *outAppleEvent, long inHandlerRefcon);
static pascal OSErr Handle_PrintDocuments(const AppleEvent *inAppleEvent, AppleEvent *outAppleEvent, long inHandlerRefcon);
static void Install_AppleEventHandlers(void);

static pascal OSStatus Handle_CommandUpdateStatus(EventHandlerCallRef inHandlerCallRef, EventRef inEvent, void *inUserData);
static pascal OSStatus Handle_CommandProcess(EventHandlerCallRef inHandlerCallRef, EventRef inEvent, void *inUserData);

static void Do_Preferences(void);

static OSStatus Do_CleanUp(void);

//****************************************************
#pragma mark -
#pragma mark * exported globals *

//****************************************************
#pragma mark -
#pragma mark * local (static) globals *

static IBNibRef gIBNibRef;

//****************************************************
#pragma mark -
#pragma mark * exported function implementations *

/*****************************************************
*
* main (argc, argv) 
*
* Purpose:  main program entry point
*
* Notes:	   You might want to change this to something more verbose
*
* Inputs:   argc     - the number of elements in the argv array
*				argv     - an array of pointers to the parameters to this application
*
* Returns:  int      - error code (0 == no error) 
*/
int main(int argc, char* argv[])
	{
	OSStatus status;
	
	// Can we run this particular demo application?
	long response;
	status = Gestalt(gestaltSystemVersion, &response);
	Boolean ok = ((noErr == status) && (response >= 0x00001030));
	if (!ok)
		{
		DialogRef theAlert;
		CreateStandardAlert(kAlertStopAlert, CFSTR("Mac OS X 10.3 (minimum) is required for this application"), NULL, NULL, &theAlert);
		RunStandardAlert(theAlert, NULL, NULL);
		ExitToShell();
		}
	
	// Create a Nib reference passing the name of the nib file (without the .nib extension)
	// CreateNibReference only searches into the application bundle.
	status = CreateNibReference(CFSTR("main"), &gIBNibRef);
	require_noerr(status, CantGetNibRef);
	
	// Once the nib reference is created, set the menu bar. "MainMenu" is the name of the menu bar
	// object. This name is set in InterfaceBuilder when the nib is created.
	status = SetMenuBarFromNib(gIBNibRef, CFSTR("MenuBar"));
	require_noerr(status, CantSetMenuBar);
	
	// Adding a Font menu
	MenuRef fontMenu = GetMenuRef(3);
	require(fontMenu != NULL, CantSetMenuBar);
	status = CreateStandardFontMenu(fontMenu, 0, 0, 0, NULL);
	require_noerr(status, CantSetMenuBar);
	
	// Enabling Preferences menu item
	EnableMenuCommand(NULL, kHICommandPreferences);
	
	// Let's react to User's commands.
	Install_AppleEventHandlers();
	
	EventTypeSpec eventTypeCP = {kEventClassCommand, kEventCommandProcess};
	InstallEventHandler(GetApplicationEventTarget(), Handle_CommandProcess, 1, &eventTypeCP, NULL, NULL);
	
	EventTypeSpec eventTypeCUS = {kEventClassCommand, kEventCommandUpdateStatus};
	InstallEventHandler(GetApplicationEventTarget(), Handle_CommandUpdateStatus, 1, &eventTypeCUS, NULL, NULL);
	
	EventTypeSpec eventTypeAA = {kEventClassApplication,  kEventAppActivated};
	InstallEventHandler(GetApplicationEventTarget(), Handle_AppActivated, 1, &eventTypeAA, NULL, NULL);
	
	// Call the event loop
	RunApplicationEventLoop();
	
CantSetMenuBar:
CantGetNibRef:
	return status;
	}   // main

/*****************************************************/
#pragma mark -
#pragma mark * local (static) function implementations *
#pragma mark * AppleEvent Handlers *

/*****************************************************
*
* Handle_OpenApplication(inAppleEvent, reply, inHandlerRefcon) 
*
* Purpose:  AppleEvent handler for the kAEOpenApplication event
*
* Inputs:   inAppleEvent       - the Apple event
*           reply              - our reply to the Apple event
*           inHandlerRefcon    - refcon passed to AEInstallEventHandler when this hander was installed
*
* Returns:  OSErr              - error code (0 == no error) 
*/
static pascal OSErr Handle_OpenApplication(const AppleEvent *inAppleEvent, AppleEvent *outAppleEvent, long inHandlerRefcon)
	{
	return Do_NewSingleLineSingleStyleWindow(); // create an empty window
	}   // Handle_OpenApplication

/*****************************************************
*
* Handle_ReopenApplication(inAppleEvent, reply, inHandlerRefcon) 
*
* Purpose:  AppleEvent handler for the kAEReopenApplication event
*
* Inputs:   inAppleEvent       - the Apple event
*           reply              - our reply to the Apple event
*           inHandlerRefcon    - refcon passed to AEInstallEventHandler when this hander was installed
*
* Returns:  OSErr              - error code (0 == no error) 
*/
static pascal OSErr Handle_ReopenApplication(const AppleEvent *inAppleEvent, AppleEvent *outAppleEvent, long inHandlerRefcon)
	{
	// We were already running but with no windows so we create an empty one.
	WindowRef theWindow = GetFrontWindowOfClass(kDocumentWindowClass, true);
	if (theWindow == NULL)
		return Do_NewSingleLineSingleStyleWindow();
	else
		return noErr;
	}   // Handle_ReopenApplication

/*****************************************************
*
* Handle_OpenDocuments(inAppleEvent, reply, inHandlerRefcon) 
*
* Purpose:  AppleEvent handler for the kAEOpenDocuments event
*
* Inputs:   inAppleEvent       - the Apple event
*           reply              - our reply to the Apple event
*           inHandlerRefcon    - refcon passed to AEInstallEventHandler when this hander was installed
*
* Returns:  OSErr              - error code (0 == no error) 
*/
static pascal OSErr Handle_OpenDocuments(const AppleEvent *inAppleEvent, AppleEvent *outAppleEvent, long inHandlerRefcon)
	{
	return errAEEventNotHandled;
	}   // Handle_OpenDocuments

/*****************************************************
*
* Handle_PrintDocuments(inAppleEvent, reply, inHandlerRefcon) 
*
* Purpose:  AppleEvent handler for the kAEPrintDocuments event
*
* Inputs:   inAppleEvent       - the Apple event
*           reply              - our reply to the Apple event
*           inHandlerRefcon    - refcon passed to AEInstallEventHandler when this hander was installed
*
* Returns:  OSErr              - error code (0 == no error) 
*/
static pascal OSErr Handle_PrintDocuments(const AppleEvent *inAppleEvent, AppleEvent *outAppleEvent, long inHandlerRefcon)
	{
	return errAEEventNotHandled;
	}   // Handle_PrintDocuments

/*****************************************************
*
* Install_AppleEventHandlers(void) 
*
* Purpose:  installs the AppleEvent handlers
*
* Inputs:   none
*
* Returns:  none
*/
static void Install_AppleEventHandlers(void)
	{
	OSErr	status;
	status = AEInstallEventHandler(kCoreEventClass, kAEOpenApplication, Handle_OpenApplication, 0, false);
	require_noerr(status, CantInstallAppleEventHandlerOpenAppl);
	
	status = AEInstallEventHandler(kCoreEventClass, kAEReopenApplication, Handle_ReopenApplication, 0, false);
	require_noerr(status, CantInstallAppleEventHandlerReOpenAppl);
	
	status = AEInstallEventHandler(kCoreEventClass, kAEOpenDocuments, Handle_OpenDocuments, 0, false);
	require_noerr(status, CantInstallAppleEventHandlerOpenDocs);
	
	status = AEInstallEventHandler(kCoreEventClass, kAEPrintDocuments, Handle_PrintDocuments, 0, false);
	require_noerr(status, CantInstallAppleEventHandlerPrintDocs);
	
	// Note: Since RunApplicationEventLoop installs a Quit AE Handler, there is no need to do it here.
	
CantInstallAppleEventHandlerOpenAppl:
CantInstallAppleEventHandlerReOpenAppl:
CantInstallAppleEventHandlerOpenDocs:
CantInstallAppleEventHandlerPrintDocs:
	return;
	}   // Install_AppleEventHandlers

#pragma mark -
#pragma mark * CarbonEvent Handlers *

/*****************************************************
*
* Handle_CommandUpdateStatus(inHandlerCallRef, inEvent, inUserData) 
*
* Purpose:  called to update status of the commands, enabling or disabling the menu items
*
* Inputs:   inHandlerCallRef    - reference to the current handler call chain
*				inEvent             - the event
*           inUserData          - app-specified data you passed in the call to InstallEventHandler
*
* Returns:  OSStatus            - noErr indicates the event was handled
*                                 eventNotHandledErr indicates the event was not handled and the Toolbox should take over
*/
static pascal OSStatus Handle_CommandUpdateStatus(EventHandlerCallRef inHandlerCallRef, EventRef inEvent, void *inUserData)
	{
	OSStatus status = eventNotHandledErr;
	
	HICommand aCommand;
	GetEventParameter(inEvent, kEventParamDirectObject, typeHICommand, NULL, sizeof(HICommand), NULL, &aCommand);
	
	// Do we have a front window containing a HIATSUIView?
	WindowRef frontWindow;
	HIViewRef atsuiView;
	Get_FrontWindowAndATSUIView(&frontWindow, &atsuiView, false);
	
	// Do we have some selected text?
	Boolean textSelected = false;
	if (atsuiView != NULL)
		{
		UniCharArrayOffset start, end;
		HIATSUIViewGetSelection(atsuiView, &start, &end);
		textSelected = (start != end);
		}

	if (frontWindow == NULL)
		{
		// no window, let's disable all relevant menu items
		switch (aCommand.commandID)
			{
			case kHICommandSelectAll:
			case kHICommandCopy:
			case kHICommandClose:
				DisableMenuItem(aCommand.menu.menuRef, aCommand.menu.menuItemIndex);
				break;
			}
		}
	else
		{
		switch (aCommand.commandID)
			{
			// the "Copy" menu item is enabled only is some text is selected
			case kHICommandCopy:
				if (textSelected)
					EnableMenuItem(aCommand.menu.menuRef, aCommand.menu.menuItemIndex);
				else
					DisableMenuItem(aCommand.menu.menuRef, aCommand.menu.menuItemIndex);
				break;
			
			// the "Select All" menu item is enabled only if there is a HIATSUIView in the front window
			case kHICommandSelectAll:
				if (atsuiView != NULL)
					EnableMenuItem(aCommand.menu.menuRef, aCommand.menu.menuItemIndex);
				else
					DisableMenuItem(aCommand.menu.menuRef, aCommand.menu.menuItemIndex);
				break;
			
			// the "Close" menu item is enabled only if there is a window
			case kHICommandClose:
				EnableMenuItem(aCommand.menu.menuRef, aCommand.menu.menuItemIndex);
				break;
			}
		}
	
	// let's adjust the "Show/Hide Fonts" menu item title depending on the visibility of the Standard Font panel
	if (aCommand.commandID == kHICommandShowHideFontPanel)
		{
		CFStringRef menuItemString;
		if (FPIsFontPanelVisible())
			menuItemString = CFCopyLocalizedString( CFSTR("Hide Fonts"), CFSTR("") );
		else
			menuItemString = CFCopyLocalizedString( CFSTR("Show Fonts"), CFSTR("") );
		SetMenuItemTextWithCFString(aCommand.menu.menuRef, aCommand.menu.menuItemIndex, menuItemString);
		CFRelease(menuItemString);
		}

	return status;
	}   // Handle_CommandUpdateStatus

/*****************************************************
*
* Handle_CommandProcess(inHandlerCallRef, inEvent, inUserData) 
*
* Purpose:  called to process commands from Carbon events
*
* Inputs:   inHandlerCallRef    - reference to the current handler call chain
*			   inEvent             - the event
*           inUserData          - app-specified data you passed in the call to InstallEventHandler
*
* Returns:  OSStatus            - noErr indicates the event was handled
*                                 eventNotHandledErr indicates the event was not handled and the Toolbox should take over
*/
static pascal OSStatus Handle_CommandProcess(EventHandlerCallRef inHandlerCallRef, EventRef inEvent, void *inUserData)
	{
	HICommand aCommand;
	OSStatus status = eventNotHandledErr;
	
	GetEventParameter(inEvent, kEventParamDirectObject, typeHICommand, NULL, sizeof(HICommand), NULL, &aCommand);
	
	switch (aCommand.commandID)
		{
		case kHICommandPreferences:
			Do_Preferences();
			break;
		case kHICommandOpen:
			status = Do_OpenATextFile();
			break;
		case kHICommandSelectAll:
			status = Handle_SelectAll();
			break;
		case kHICommandCopy:
			status = Handle_Copy();
			break;
		case 'SLSS':
			status = Do_NewSingleLineSingleStyleWindow();
			break;
		case 'SLMS':
			status = Do_NewSingleLineMultipleStyleWindow();
			break;
		case 'VLMS':
			status = Do_NewSingleVerticalLineMultipleStyleWindow();
			break;
		case 'PRGR':
			status = Do_NewParagraphsWindow();
			break;
		case 'HGHL':
			status = Do_NewHighlightingWindow();
			break;
		case 'HTST':
			status = Do_NewHitTestingWindow();
			break;
		case 'UCLP':
			status = Do_ShowClipboardWindow();
			break;
		case 'TXTB':
			status = Do_NewTextBoxWindow(gIBNibRef);
			break;
		case 'FNTV':
			status = Do_NewUsingFontVariantsWindow();
			break;
		case 'SCRL':
			status = Do_NewScrollingWindow();
			break;
		case 'UAPI':
			status = Do_CreateWithTextWindow();
			break;
		case 'UNIB':
			status = Do_CreateFromNibWindow(gIBNibRef);
			break;
		case kHICommandShowHideFontPanel:
			// nothing to do, we just pass through, returning eventNotHandledErr so that the HIToolbox
			// shows or hides the System Font Panel
			break;
		case kHICommandAbout:
			// nothing to do, we just pass through, returning eventNotHandledErr so that the HIToolbox
			// shows the Standard About Box
			break;
		case kHICommandQuit:
			status = Do_CleanUp();
			break;
		default:
			{
			// we may have a font selection from the Font Menu.
			status = Handle_FontMenuSelection(&aCommand);
			
			// if not, let's print out the unknown command for debugging purposes
			if (status != noErr)
				{
				char buffer[200];
				char smallbuf[4], *p = smallbuf;
				*((UInt32 *)p) = aCommand.commandID;
				sprintf(buffer, "Got unknown command id: %ld, '%c%c%c%c', ", aCommand.commandID, p[0], p[1], p[2], p[3]);
				debug_string(buffer);
				}
			}
			break;
		}
	return status;
	}   // Handle_CommandProcess

#pragma mark -
#pragma mark * Windows *

/*****************************************************
*
* Do_Preferences(void) 
*
* Purpose:  routine to display dialog to set our applications preferences
*
* Inputs:   none
*
* Returns:  none
*/
static void Do_Preferences(void)
	{
	DialogRef theAlert;
	CreateStandardAlert(kAlertStopAlert, CFSTR("No Preferences yet!"), NULL, NULL, &theAlert);
	RunStandardAlert(theAlert, NULL, NULL);
	}   // Do_Preferences

/*****************************************************
*
* Do_CleanUp(void) 
*
* Purpose:  called when we get the quit event, closes all the windows.
*
* Inputs:   none
*
* Returns:  OSStatus   - eventNotHandledErr indicates that the quit process can continue
*/
static OSStatus Do_CleanUp(void)
	{
	WindowRef windowToDispose, aWindowRef = GetFrontWindowOfClass(kDocumentWindowClass, true);

	for ( ; aWindowRef != NULL; )
		{
		windowToDispose = aWindowRef;
		aWindowRef = GetNextWindowOfClass(aWindowRef, kDocumentWindowClass, true);
		DisposeWindow(windowToDispose);
		}
	
	return eventNotHandledErr;
	}   // Do_CleanUp
