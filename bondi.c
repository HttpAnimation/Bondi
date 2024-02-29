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

// Function to read categories from Catagorys.conf
void read_categories(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening Catagorys.conf");
        exit(EXIT_FAILURE);
    }

    char line[100];
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0; // Remove trailing newline character
        strcpy(categories[num_categories].name, line);
        categories[num_categories].num_apps = 0;
        num_categories++;
    }

    fclose(file);
}

// Function to read app data from Data.conf
void read_apps(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening Data.conf");
        exit(EXIT_FAILURE);
    }

    char line[100];
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0; // Remove trailing newline character

        char *token = strtok(line, "|");
        char *category_name = token;

        int cat_index;
        for (cat_index = 0; cat_index < num_categories; cat_index++) {
            if (strcmp(categories[cat_index].name, category_name) == 0)
                break;
        }

        if (cat_index == num_categories) {
            fprintf(stderr, "Category %s not found.\n", category_name);
            continue;
        }

        token = strtok(NULL, "|");
        strcpy(categories[cat_index].apps[categories[cat_index].num_apps].name, token);

        token = strtok(NULL, "|");
        strcpy(categories[cat_index].apps[categories[cat_index].num_apps].command, token);

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
    GtkWidget *window = (GtkWidget *)data;
    char *category_name = (char *)gtk_button_get_label(GTK_BUTTON(widget));

    // Clear previous apps
    GList *children = gtk_container_get_children(GTK_CONTAINER(window));
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

    // Add apps buttons
    for (int j = 0; j < categories[cat_index].num_apps; j++) {
        GtkWidget *launch_button = gtk_button_new_with_label(categories[cat_index].apps[j].name);
        g_signal_connect(launch_button, "clicked", G_CALLBACK(launch_app), categories[cat_index].apps[j].command);
        gtk_container_add(GTK_CONTAINER(window), launch_button);
    }

    // Show all widgets
    gtk_widget_show_all(window);
}

int main(int argc, char *argv[]) {
    // Initialize GTK
    gtk_init(&argc, &argv);

    // Read categories and apps
    read_categories("Catagorys.conf");
    read_apps("Data.conf");

    // Create main window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Bondi - Game/App Launcher");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Create sidebar
    GtkWidget *sidebar = gtk_list_box_new();
    gtk_container_add(GTK_CONTAINER(window), sidebar);

    // Populate sidebar with category buttons
    for (int i = 0; i < num_categories; i++) {
        GtkWidget *button = gtk_button_new_with_label(categories[i].name);
        gtk_list_box_insert(GTK_LIST_BOX(sidebar), button, -1);
        g_signal_connect(button, "clicked", G_CALLBACK(load_apps), window);
    }

    // Show all widgets
    gtk_widget_show_all(window);

    // Run the GTK main loop
    gtk_main();

    return 0;
}
