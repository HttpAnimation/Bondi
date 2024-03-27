#import <Cocoa/Cocoa.h>

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

@property (nonatomic, strong) NSWindow *window;
@property (nonatomic, strong) NSButton *buttons[MAX_APPS];

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
        NSButton *button = [[NSButton alloc] initWithFrame:NSMakeRect(20, 20 + 40 * numApps, 200, 30)];
        [button setTitle:[NSString stringWithUTF8String:apps[numApps].name]];
        [button setTarget:self];
        [button setAction:@selector(launchSelectedApp:)];
        [self.window.contentView addSubview:button];
        self.buttons[numApps] = button;
        numApps++;
        if (numApps >= MAX_APPS) {
            fprintf(stderr, "Too many applications in config file\n");
            break;
        }
    }

    fclose(file);
}

- (void)launchApp:(NSInteger)appIndex {
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Child process
        if (execlp("/bin/sh", "sh", "-c", apps[appIndex].command, NULL) == -1) {
            perror("execlp");
            exit(EXIT_FAILURE);
        }
    } else {
        // Parent process
        int status;
        waitpid(pid, &status, 0);
        printf("Application has exited with status: %d\n", status);
    }
}

- (void)launchSelectedApp:(NSButton *)sender {
    NSInteger index = [self indexOfButton:sender];
    [self launchApp:index];
}

- (NSInteger)indexOfButton:(NSButton *)button {
    for (NSInteger i = 0; i < numApps; i++) {
        if (self.buttons[i] == button) {
            return i;
        }
    }
    return -1;
}

@end

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        AppDelegate *delegate = [[AppDelegate alloc] init];
        NSApplication *application = [NSApplication sharedApplication];
        [application setDelegate:delegate];
        
        NSWindow *window = [[NSWindow alloc] initWithContentRect:NSMakeRect(0, 0, 640, 480)
                                                       styleMask:NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskResizable
                                                         backing:NSBackingStoreBuffered
                                                           defer:NO];
        [window setTitle:@"Bondi - Big Picture Mode"];
        [window makeKeyAndOrderFront:nil];
        delegate.window = window;
        
        [application run];
    }
    return 0;
}
