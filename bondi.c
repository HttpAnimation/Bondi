#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_GAMES 100
#define MAX_NAME_LENGTH 50
#define CONFIG_FILE "Data.conf"

typedef struct {
    char name[MAX_NAME_LENGTH];
    char executable[MAX_NAME_LENGTH];
} Game;

Game games[MAX_GAMES];
int numGames = 0;

void readConfigFile() {
    FILE *file = fopen(CONFIG_FILE, "r");
    if (file == NULL) {
        perror("Error opening config file");
        exit(EXIT_FAILURE);
    }

    while (fscanf(file, "%s %s", games[numGames].name, games[numGames].executable) == 2) {
        numGames++;
        if (numGames >= MAX_GAMES) {
            fprintf(stderr, "Too many games in config file\n");
            break;
        }
    }

    fclose(file);
}

void launchGame(int gameIndex) {
    // Code to launch the game executable
    printf("Launching game: %s\n", games[gameIndex].executable);
}

int main() {
    readConfigFile();

    // Example: Launch the first game in the list
    if (numGames > 0) {
        launchGame(0);
    } else {
        printf("No games found in config file\n");
    }

    return 0;
}
