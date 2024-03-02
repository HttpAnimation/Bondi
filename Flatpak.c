#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 256

int main() {
    FILE *fp_in, *fp_out;
    char buffer[MAX_LENGTH];
    char app_id[MAX_LENGTH];

    // Open a pipe to read the list of installed Flatpak applications
    fp_in = popen("flatpak list --app", "r");
    if (fp_in == NULL) {
        printf("Failed to run command\n");
        return 1;
    }

    // Open Data.conf file for writing
    fp_out = fopen("Data.conf", "w");
    if (fp_out == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    // Read the output line by line and write to Data.conf
    while (fgets(buffer, MAX_LENGTH, fp_in) != NULL) {
        // Skip lines that don't start with the application ID
        if (buffer[0] == ' ') continue;

        // Extract the application ID
        sscanf(buffer, "%s", app_id);

        // Write application name and launch command to Data.conf
        fprintf(fp_out, "%s flatpak run %s\n", app_id, app_id);
    }

    // Close the pipes and files
    pclose(fp_in);
    fclose(fp_out);

    printf("Data written to Data.conf successfully\n");

    return 0;
}
