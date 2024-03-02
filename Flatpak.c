#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

void clear_file(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error clearing file");
        exit(EXIT_FAILURE);
    }
    fclose(file);
}

void append_to_file(const char *filename, const char *text) {
    FILE *file = fopen(filename, "a");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    fprintf(file, "%s\n", text);
    fclose(file);
}

int main() {
    const char *games_ini_path = "Data.conf";
    
    // Clear the file
    clear_file(games_ini_path);

    // Run flatpak update to ensure the list is up-to-date
    system("flatpak update");

    // Open the file in append mode to ensure it exists
    FILE *games_ini_file = fopen(games_ini_path, "a");
    if (games_ini_file == NULL) {
        perror("Error opening Data.conf");
        exit(EXIT_FAILURE);
    }
    fclose(games_ini_file);

    char flatpak_list_output[MAX_LINE_LENGTH];
    FILE *pipe = popen("flatpak list", "r");
    if (pipe == NULL) {
        perror("Error executing flatpak list");
        exit(EXIT_FAILURE);
    }

    while (fgets(flatpak_list_output, sizeof(flatpak_list_output), pipe) != NULL) {
        // Tokenize the line by tabs
        char *token;
        char *columns[4];
        int col = 0;
        token = strtok(flatpak_list_output, "\t");
        while (token != NULL && col < 4) {
            columns[col++] = token;
            token = strtok(NULL, "\t");
        }

        // Ensure we have at least three columns
        if (col >= 3) {
            char command_str[MAX_LINE_LENGTH];

            // If the third column starts with "flatpak run", use it directly
            if (strncmp(columns[2], "flatpak run", 11) == 0) {
                snprintf(command_str, sizeof(command_str), "%s : %s\n", columns[0], columns[2]);
            } else {
                // Extract app name, flatpak name, and run command
                char *app_name = columns[0];
                char *flatpak_name = columns[1];

                // Extract version number from flatpak name
                char *version_number = strrchr(flatpak_name, '.') + 1;

                // Build the command string
                snprintf(command_str, sizeof(command_str), "%s : flatpak run %s\n", app_name, flatpak_name);
            }

            // Append command to file
            append_to_file(games_ini_path, command_str);
        }
    }
    pclose(pipe);

    printf("Commands have been written to Data.conf\n");

    return 0;
}
