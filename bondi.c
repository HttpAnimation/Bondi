#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // For the exec family of functions
#include <sys/types.h>
#include <sys/wait.h>

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
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Child process
        if (execlp(games[gameIndex].executable, games[gameIndex].executable, NULL) == -1) {
            perror("execlp");
            exit(EXIT_FAILURE);
        }
    } else {
        // Parent process
        int status;
        waitpid(pid, &status, 0);
        printf("Game has exited with status: %d\n", status);
    }
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
