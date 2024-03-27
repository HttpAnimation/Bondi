#import <Cocoa/Cocoa.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // For the exec family of functions
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_APPS 100
#define MAX_NAME_LENGTH 50
#define MAX_COMMAND_LENGTH 100
#define VERSION 8
#define CONFIG_FILE "Data.conf"

typedef struct {
    char name[MAX_NAME_LENGTH];
    char command[MAX_COMMAND_LENGTH];
} App;

App apps[MAX_APPS];
int numApps = 0;

@interface AppDelegate : NSObject <NSApplicationDelegate>

@property (assign) IBOutlet NSWindow *window;
@property (assign) IBOutlet NSButton *launchButton;
@property (assign) IBOutlet NSTextField *titleLabel;
@property (assign) IBOutlet NSView *buttonContainer;

- (IBAction)launchApp:(id)sender;

@end

@implementation AppDelegate

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    [self readConfigFile];
}

- (void)readConfigFile {
    FILE *file = fopen(CONFIG_FILE, "r");
    if (file == NULL) {
        perror("Error opening config file");
        exit(EXIT_FAILURE);
    }

    while (fscanf(file, "%49[^:]:%99s", apps[numApps].name, apps[numApps].command) == 2) {
        NSButton *button = [[NSButton alloc] initWithFrame:NSMakeRect(0, numApps * 40, 200, 30)];
        [button setTitle:[NSString stringWithUTF8String:apps[numApps].name]];
        [button setTarget:self];
        [button setAction:@selector(launchApp:)];
        [[self.buttonContainer subviews] addObject:button];

        numApps++;
        if (numApps >= MAX_APPS) {
            fprintf(stderr, "Too many applications in config file\n");
            break;
        }
    }

    fclose(file);
}

- (IBAction)launchApp:(id)sender {
    NSButton *button = (NSButton *)sender;
    NSInteger appIndex = [[self.buttonContainer subviews] indexOfObject:button];
    
    NSString *command = [NSString stringWithUTF8String:apps[appIndex].command];
    if (!command) {
        NSLog(@"Failed to get command for app at index %ld", (long)appIndex);
        return;
    }
    
    NSTask *task = [[NSTask alloc] init];
    [task setLaunchPath:@"/bin/sh"];
    [task setArguments:@[@"-c", command]];
    [task launch];
}

@end

int main(int argc, const char * argv[]) {
    NSApplication *application = [NSApplication sharedApplication];
    AppDelegate *delegate = [[AppDelegate alloc] init];
    [application setDelegate:delegate];
    [application run];
    return 0;
}
