#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 256
#define MAX_APPS 10000 // Defined as a very large number

int main() {
    FILE *fp;
    char buffer[MAX_LENGTH];
    char *app_name;
    int num_apps = 0;

    // Open a pipe to read the list of installed Flatpak applications
    fp = popen("flatpak list --app", "r");
    if (fp == NULL) {
        printf("Failed to run command\n");
        return 1;
    }

    // Write the data to Data.conf file
    fp = fopen("Data.conf", "w");
    if (fp == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    // Read the output line by line
    while (fgets(buffer, MAX_LENGTH, fp) != NULL) {
        // Skip lines that don't start with the application ID
        if (buffer[0] == ' ') continue;
        
        // Extract the application name
        app_name = strtok(buffer, " ");
        
        // Write the application name and its launch command to Data.conf
        fprintf(fp, "%s flatpak run %s", app_name, app_name);
        num_apps++;
    }

    // Close the pipe and file
    pclose(fp);
    fclose(fp);

    printf("Data written to Data.conf successfully\n");

    return 0;
}
