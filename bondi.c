#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // For the exec family of functions
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_APPS 100
#define MAX_NAME_LENGTH 50
#define MAX_COMMAND_LENGTH 100
#define CONFIG_FILE "Data.conf"

typedef struct {
    char name[MAX_NAME_LENGTH];
    char command[MAX_COMMAND_LENGTH];
} App;

App apps[MAX_APPS];
int numApps = 0;

void readConfigFile() {
    FILE *file = fopen(CONFIG_FILE, "r");
    if (file == NULL) {
        perror("Error opening config file");
        exit(EXIT_FAILURE);
    }

    while (fscanf(file, "%s %[^\n]", apps[numApps].name, apps[numApps].command) == 2) {
        numApps++;
        if (numApps >= MAX_APPS) {
            fprintf(stderr, "Too many applications in config file\n");
            break;
        }
    }

    fclose(file);
}

void launchApp(int appIndex) {
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

int main() {
    readConfigFile();

    // Example: Launch the first application in the list
    if (numApps > 0) {
        launchApp(0);
    } else {
        printf("No applications found in config file\n");
    }

    return 0;
}
