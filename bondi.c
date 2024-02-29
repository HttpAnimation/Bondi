#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>

#define MAX_CATEGORIES 10
#define MAX_APPS_PER_CATEGORY 10

// Structure to store app information
typedef struct {
    char name[50];
    char command[100];
} App;

// Structure to store category information
typedef struct {
    char name[50];
    int num_apps;
    App apps[MAX_APPS_PER_CATEGORY];
} Category;

Category categories[MAX_CATEGORIES];
int num_categories = 0;

// Function to read data from Data.conf
void read_data(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening Data.conf make sure the file exists :3.");
        exit(EXIT_FAILURE);
    }

    char line[100];
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0; // Remove trailing newline character

        // Tokenize the line
        char *token = strtok(line, "|");

        // Extract category name
        char *category_name = token;

        // Check if the category already exists
        int cat_index;
        for (cat_index = 0; cat_index < num_categories; cat_index++) {
            if (strcmp(categories[cat_index].name, category_name) == 0)
                break;
        }

        // If the category doesn't exist, add it
        if (cat_index == num_categories) {
            strcpy(categories[num_categories].name, category_name);
            categories[num_categories].num_apps = 0;
            num_categories++;
        }

        // Extract app name and command
        token = strtok(NULL, "|");
        char *app_name = token;

        token = strtok(NULL, "|");
        char *app_command = token;

        // Add app to the category
        strcpy(categories[cat_index].apps[categories[cat_index].num_apps].name, app_name);
        strcpy(categories[cat_index].apps[categories[cat_index].num_apps].command, app_command);
        categories[cat_index].num_apps++;
    }

    fclose(file);
}

// Callback function for launching an app
void launch_app(GtkWidget *widget, gpointer data) {
    char *command = (char *)data;
    system(command);
}

// Callback function for loading apps of a category
void load_apps(GtkWidget *widget, gpointer data) {
    GtkWidget *main_area = (GtkWidget *)data;
    char *category_name = (char *)gtk_button_get_label(GTK_BUTTON(widget));

    // Clear previous apps
    GList *children = gtk_container_get_children(GTK_CONTAINER(main_area));
    for (GList *iter = children; iter != NULL; iter = g_list_next(iter)) {
        gtk_widget_destroy(GTK_WIDGET(iter->data));
    }
    g_list_free(children);

    // Find category index
    int cat_index;
    for (cat_index = 0; cat_index < num_categories; cat_index++) {
        if (strcmp(categories[cat_index].name, category_name) == 0)
            break;
    }

    // Add apps buttons to the main area
    for (int j = 0; j < categories[cat_index].num_apps; j++) {
        GtkWidget *launch_button = gtk_button_new_with_label(categories[cat_index].apps[j].name);
        g_signal_connect(launch_button, "clicked", G_CALLBACK(launch_app), categories[cat_index].apps[j].command);
        gtk_grid_attach(GTK_GRID(main_area), launch_button, j % 3, j / 3, 1, 1);
    }

    // Show all widgets
    gtk_widget_show_all(main_area);
}

// Callback function to toggle fullscreen on F11 key press
gboolean on_key_press(GtkWidget *window, GdkEventKey *event, gpointer user_data) {
    if (event->keyval == GDK_KEY_F11) {
        gtk_window_fullscreen(GTK_WINDOW(window));
        return TRUE;
    }
    return FALSE;
}

int main(int argc, char *argv[]) {
    // Start GTK
    gtk_init(&argc, &argv);

    // Read data from Data.conf
    // This is the file the script will read.
    read_data("Data.conf");

    // Create main window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Bondi - V3");
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 400);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(window, "key-press-event", G_CALLBACK(on_key_press), NULL);

    // Create grid layout for main window
    GtkWidget *grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    // Create sidebar
    GtkWidget *sidebar = gtk_list_box_new();
    gtk_grid_attach(GTK_GRID(grid), sidebar, 0, 0, 1, 1);

    // Populate sidebar with category buttons
    for (int i = 0; i < num_categories; i++) {
        GtkWidget *button = gtk_button_new_with_label(categories[i].name);
        gtk_container_add(GTK_CONTAINER(sidebar), button);
        g_signal_connect(button, "clicked", G_CALLBACK(load_apps), grid);
    }

    // Create main area
    GtkWidget *main_area = gtk_grid_new();
    gtk_grid_attach(GTK_GRID(grid), main_area, 1, 0, 1, 1);

    // Show all widgets
    gtk_widget_show_all(window);

    // Run the GTK main loop
    gtk_main();

    return 0;
}
