#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 256
#define MAX_APPS 10000 // Defined as a very large number

int main() {
    FILE *fp;
    char buffer[MAX_LENGTH];
    char *apps[MAX_APPS];
    int num_apps = 0;

    // Open a pipe to read the list of installed Flatpak applications
    fp = popen("flatpak list --app", "r");
    if (fp == NULL) {
        printf("Failed to run command\n");
        return 1;
    }

    // Read the output line by line
    while (fgets(buffer, MAX_LENGTH, fp) != NULL) {
        // Skip lines that don't start with the application ID
        if (buffer[0] == ' ') continue;
        
        // Extract the application name
        char *app_name = strtok(buffer, " ");
        
        // Store the application name
        apps[num_apps] = strdup(app_name);
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

    // Write each application name to the file
    for (int i = 0; i < num_apps; i++) {
        fprintf(fp, "%s flatpak run %s\n", apps[i], apps[i]);
        free(apps[i]);
    }

    fclose(fp);
    printf("Data written to Data.conf successfully\n");

    return 0;
}
