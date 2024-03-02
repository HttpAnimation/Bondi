#include <stdio.h>
#include <stdlib.h>

#define MAX_LENGTH 256

int main() {
    FILE *fp_in, *fp_out;
    char buffer[MAX_LENGTH];

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
        fprintf(fp_out, "%s", buffer);
    }

    // Close the pipes and files
    pclose(fp_in);
    fclose(fp_out);

    printf("Data written to Data.conf successfully\n");

    return 0;
}
