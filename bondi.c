#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // For the exec family of functions
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_APPS 100
#define MAX_NAME_LENGTH 50
#define MAX_COMMAND_LENGTH 100
#define CONFIG_FILE "Data.conf"

typedef struct {
    char name[MAX_NAME_LENGTH];
    char command[MAX_COMMAND_LENGTH];
} App;

App apps[MAX_APPS];
int numApps = 0;

void readConfigFile() {
    FILE *file = fopen(CONFIG_FILE, "r");
    if (file == NULL) {
        perror("Error opening config file");
        exit(EXIT_FAILURE);
    }

    while (fscanf(file, "%s %[^\n]", apps[numApps].name, apps[numApps].command) == 2) {
        numApps++;
        if (numApps >= MAX_APPS) {
            fprintf(stderr, "Too many applications in config file\n");
            break;
        }
    }

    fclose(file);
}

void launchApp(int appIndex, GtkWindow *parentWindow) {
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Child process
        if (execlp("/bin/sh", "sh", "-c", apps[appIndex].command, NULL) == -1) {
            perror("execlp");
            exit(EXIT_FAILURE);
        }
    } else {
        // Parent process
        int status;
        waitpid(pid, &status, 0);
        printf("Application has exited with status: %d\n", status);
    }
}

static void launch_selected_app(GtkWidget *widget, gpointer data) {
    int appIndex = GPOINTER_TO_INT(data);
    GtkWindow *parentWindow = GTK_WINDOW(gtk_widget_get_toplevel(widget));
    
    // Minimize the parent window (Bondi window)
    gtk_window_iconify(parentWindow);
    
    // Launch the selected application
    launchApp(appIndex, parentWindow);
}

static void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *button;

    readConfigFile();

    // Create a new window
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Bondi - Big Picture Mode");
    gtk_window_set_default_size(GTK_WINDOW(window), 200, 100);
    gtk_window_fullscreen(GTK_WINDOW(window)); // Set the window to full-screen mode

    // Create a grid layout
    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    // Create buttons for each application
    for (int i = 0; i < numApps; i++) {
        button = gtk_button_new_with_label(apps[i].name);
        g_signal_connect(button, "clicked", G_CALLBACK(launch_selected_app), GINT_TO_POINTER(i));
        gtk_grid_attach(GTK_GRID(grid), button, 0, i, 1, 1);
    }

    gtk_widget_show_all(window);
}

int main(int argc, char **argv) {
    GtkApplication *app;
    int status;

    app = gtk_application_new("org.example.bondi", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}
