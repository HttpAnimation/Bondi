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
    fp = popen("flatpak list --app --columns=Application", "r");
    if (fp == NULL) {
        printf("Failed to run command\n");
        return 1;
    }

    // Read the output line by line
    while (fgets(buffer, MAX_LENGTH, fp) != NULL) {
        // Store the application ID (launch command)
        apps[num_apps] = strdup(buffer);
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

    // Write each application ID to the file
    for (int i = 0; i < num_apps; i++) {
        // Trim newline character from the end of the app ID
        apps[i][strlen(apps[i])-1] = '\0';
        fprintf(fp, "flatpak run %s\n", apps[i]);
        free(apps[i]);
    }

    fclose(fp);
    printf("Data written to Data.conf successfully\n");

    return 0;
}
