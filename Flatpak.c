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
    const char *games_ini_path = "Data.conf";
    FILE *games_ini_file = fopen(games_ini_path, "r");
    if (games_ini_file == NULL) {
        games_ini_file = fopen(games_ini_path, "w");
        if (games_ini_file == NULL) {
            perror("Error creating Games.ini");
            exit(EXIT_FAILURE);
        }
        fprintf(games_ini_file, "# Flatpak\n");
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

    // Declarations for prev_app_name and prev_run_command
    char prev_app_name[MAX_LINE_LENGTH] = "";
    char prev_run_command[MAX_LINE_LENGTH] = "";

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

        // Ensure we have at least three columns and the third column is not empty
        if (col >= 3 && columns[2] != NULL) {
            // Check if the third column is a valid command
            if (strncmp(columns[2], "flatpak run ", 12) == 0) {
                char app_name[MAX_LINE_LENGTH];
                char flatpak_name[MAX_LINE_LENGTH];
                char run_command[MAX_LINE_LENGTH];

                // Extract app name, flatpak name, and run command
                strcpy(app_name, columns[0]);
                strcpy(flatpak_name, columns[1]);
                strcpy(run_command, columns[2]);

                // Extract version number from flatpak name
                char *version_number = strrchr(flatpak_name, '.') + 1;

                // Build the command string
                char command_str[MAX_LINE_LENGTH];
                snprintf(command_str, sizeof(command_str), "Flatpak | %s | %s | %s\n", app_name, run_command, version_number);

                // Write to file if app name or run command changes
                if (strcmp(app_name, prev_app_name) != 0 || strcmp(run_command, prev_run_command) != 0) {
                    append_to_file(games_ini_path, "\n");
                }

                append_to_file(games_ini_path, command_str);

                // Update prev_app_name and prev_run_command
                strcpy(prev_app_name, app_name);
                strcpy(prev_run_command, run_command);
            }
        }
    }
    pclose(pipe);

    printf("Commands have been written to Games.ini\n");

    return 0;
}
