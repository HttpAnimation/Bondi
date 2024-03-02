#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 256
#define MAX_APPS 10000 // Defined as a very large number

int main() {
    FILE *fp;
    char buffer[MAX_LENGTH];
    char *apps[MAX_APPS];
    char *app_ids[MAX_APPS];
    int num_apps = 0;

    // Open a pipe to read the list of installed Flatpak applications
    fp = popen("flatpak list --app --columns=Name,Application", "r");
    if (fp == NULL) {
        printf("Failed to run command\n");
        return 1;
    }

    // Read the output line by line
    while (fgets(buffer, MAX_LENGTH, fp) != NULL) {
        // Split the line into application name and application ID
        char *app_name = strtok(buffer, " ");
        char *app_id = strtok(NULL, " ");
        
        // Store the application name and application ID
        apps[num_apps] = strdup(app_name);
        app_ids[num_apps] = strdup(app_id);
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

    // Write each application name and application ID to the file
    for (int i = 0; i < num_apps; i++) {
        fprintf(fp, "%s flatpak run %s\n", apps[i], app_ids[i]);
        free(apps[i]);
        free(app_ids[i]);
    }

    fclose(fp);
    printf("Data written to Data.conf successfully\n");

    return 0;
}
