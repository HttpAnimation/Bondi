#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

void append_to_file(const char *filename, const char *text) {
    FILE *file = fopen(filename, "a");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    fprintf(file, "%s", text);
    fclose(file);
}

int main() {
    // Run flatpak update to ensure the list is up-to-date
    system("flatpak update");

    const char *games_ini_path = "Data.conf";
    FILE *games_ini_file = fopen(games_ini_path, "r");
    if (games_ini_file == NULL) {
        games_ini_file = fopen(games_ini_path, "w");
        if (games_ini_file == NULL) {
            perror("Error creating Data.conf");
            exit(EXIT_FAILURE);
        }
        fclose(games_ini_file);
    } else {
        fclose(games_ini_file);
    }

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
                snprintf(command_str, sizeof(command_str), "%s\n", columns[2]);
            } else {
                // Extract app name, flatpak name, and run command
                char *app_name = columns[0];
                char *flatpak_name = columns[1];

                // Extract version number from flatpak name
                char *version_number = strrchr(flatpak_name, '.') + 1;

                // Build the command string
                snprintf(command_str, sizeof(command_str), "Flatpak | %s | %s | %s\n", app_name, columns[2], version_number);
            }

            // Append command to file
            append_to_file(games_ini_path, command_str);
        }
    }
    pclose(pipe);

    printf("Commands have been written to Data.conf\n");

    return 0;
}
