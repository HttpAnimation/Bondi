#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 256
#define MAX_APPS 10000 // Defined as a very large number

int main() {
    FILE *fp;
    char buffer[MAX_LENGTH];
    char *apps[MAX_APPS];
    char *launch_commands[MAX_APPS];
    int num_apps = 0;

    // Open a pipe to read the list of installed Flatpak applications
    fp = popen("flatpak list --app --columns=application,appcommand", "r");
    if (fp == NULL) {
        printf("Failed to run command\n");
        return 1;
    }

    // Read the output line by line
    while (fgets(buffer, MAX_LENGTH, fp) != NULL) {
        // Split the line into application name and launch command
        char *app = strtok(buffer, " ");
        char *launch_command = strtok(NULL, " ");
        
        // Store the application name and launch command
        apps[num_apps] = strdup(app);
        launch_commands[num_apps] = strdup(launch_command);
        num_apps++;
    }

    // Close the pipe
    pclose(fp);

    // Write the data to Data.conf file
    fp = fopen("Data.conf", "w");
    if (fp == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    // Write each application name and launch command to the file
    for (int i = 0; i < num_apps; i++) {
        fprintf(fp, "%s %s\n", apps[i], launch_commands[i]);
        free(apps[i]);
        free(launch_commands[i]);
    }

    fclose(fp);
    printf("Data written to Data.conf successfully\n");

    return 0;
}
