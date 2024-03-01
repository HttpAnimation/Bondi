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
        
        // Bring back Bondi window to focus
        gtk_window_present(parentWindow);
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
    GtkWidget *box;
    GtkWidget *label;
    GtkCssProvider *provider;
    GdkDisplay *display;
    GdkScreen *screen;

    readConfigFile();

    // Create a new window
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Bondi - Big Picture Mode");
    gtk_window_set_default_size(GTK_WINDOW(window), 1280, 720); // Set window size to match Big Picture Mode
    gtk_window_fullscreen(GTK_WINDOW(window)); // Set the window to full-screen mode

    // Load CSS provider for styling
    provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(provider,
                                    "button {\n"
                                    "    background-color: #2C313A;\n"
                                    "    color: #FFFFFF;\n"
                                    "    border: none;\n"
                                    "    border-radius: 5px;\n"
                                    "    padding: 20px;\n"
                                    "    margin: 10px;\n"
                                    "}\n"
                                    "button:hover {\n"
                                    "    background-color: #3F4854;\n"
                                    "}\n"
                                    "label {\n"
                                    "    font-size: 24px;\n"
                                    "    color: #FFFFFF;\n"
                                    "}\n",
                                    -1,
                                    NULL);

    // Apply CSS provider to the window
    display = gdk_display_get_default();
    screen = gdk_display_get_default_screen(display);
    gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    // Create a vertical box layout
    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(window), box);

    // Create a label for the title
    label = gtk_label_new("Bondi - Big Picture Mode");
    gtk_widget_set_name(label, "title");
    gtk_box_pack_start(GTK_BOX(box), label, FALSE, FALSE, 20);

    // Create a grid layout
    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(box), grid);

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
