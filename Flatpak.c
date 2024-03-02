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

void display_usage() {
    printf("Usage: program [-f filename] [-h]\n");
    printf("Options:\n");
    printf("  -f filename  Specify the filename to save the commands (default: Data.conf)\n");
    printf("  -h           Display this help message\n");
}

int main(int argc, char *argv[]) {
    const char *games_ini_path = "Data.conf";

    if (argc > 1) {
        if (strcmp(argv[1], "-h") == 0) {
            display_usage();
            return 0;
        }

        if (strcmp(argv[1], "-f") == 0 && argc > 2) {
            char *filename = argv[2];
            // Check if the filename ends with ".conf", if not, append it
            if (strlen(filename) < 5 || strcmp(filename + strlen(filename) - 5, ".conf") != 0) {
                char new_filename[MAX_LINE_LENGTH];
                snprintf(new_filename, sizeof(new_filename), "%s.conf", filename);
                games_ini_path = new_filename;
            } else {
                games_ini_path = filename;
            }
        }
    }

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

    printf("Commands have been written to %s\n", games_ini_path);
    printf("Make sure to open the file %s to make sure all the data is right\n", games_ini_path);
    return 0; 
}
