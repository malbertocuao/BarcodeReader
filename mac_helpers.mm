// mac_helpers.mm
#import <Cocoa/Cocoa.h>

extern "C" void bringMacWindowToFront(void *winId) {
    NSWindow *nsWindow = (__bridge NSWindow *)winId;
    [nsWindow makeKeyAndOrderFront:nil];
    [[NSApplication sharedApplication] activateIgnoringOtherApps:YES];
}
