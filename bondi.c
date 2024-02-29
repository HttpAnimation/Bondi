#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>

#define INITIAL_CATEGORY_CAPACITY 10
#define INITIAL_APP_CAPACITY 10
#define BUFFER_SIZE 256

// Structure to store app information
typedef struct {
    char name[50];
    char command[100];
} App;

// Structure to store category information
typedef struct {
    char name[50];
    int num_apps;
    int capacity;
    App *apps;
} Category;

Category *categories = NULL;
int num_categories = 0;
int category_capacity = 0;

// Function to initialize categories
void initialize_categories() {
    categories = malloc(INITIAL_CATEGORY_CAPACITY * sizeof(Category));
    if (categories == NULL) {
        perror("Memory allocation failed.");
        exit(EXIT_FAILURE);
    }
    category_capacity = INITIAL_CATEGORY_CAPACITY;
}

// Function to read data from Data.conf
void read_data(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening Data.conf. Make sure the file exists.");
        exit(EXIT_FAILURE);
    }

    char line[BUFFER_SIZE];
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
            if (num_categories == category_capacity) {
                category_capacity *= 2;
                categories = realloc(categories, category_capacity * sizeof(Category));
                if (categories == NULL) {
                    perror("Memory allocation failed.");
                    exit(EXIT_FAILURE);
                }
            }
            strcpy(categories[num_categories].name, category_name);
            categories[num_categories].num_apps = 0;
            categories[num_categories].capacity = INITIAL_APP_CAPACITY;
            categories[num_categories].apps = malloc(INITIAL_APP_CAPACITY * sizeof(App));
            if (categories[num_categories].apps == NULL) {
                perror("Memory allocation failed.");
                exit(EXIT_FAILURE);
            }
            num_categories++;
        }

        // Extract app name and command
        token = strtok(NULL, "|");
        char *app_name = token;

        token = strtok(NULL, "|");
        char *app_command = token;

        // Add app to the category
        if (categories[cat_index].num_apps == categories[cat_index].capacity) {
            categories[cat_index].capacity *= 2;
            categories[cat_index].apps = realloc(categories[cat_index].apps, categories[cat_index].capacity * sizeof(App));
            if (categories[cat_index].apps == NULL) {
                perror("Memory allocation failed.");
                exit(EXIT_FAILURE);
            }
        }
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
    GtkWidget *main_area = GTK_WIDGET(data);
    const char *category_name = gtk_button_get_label(GTK_BUTTON(widget));

    // Clear previous apps
    gtk_container_foreach(GTK_CONTAINER(main_area), (GtkCallback)gtk_widget_destroy, NULL);

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
        gtk_widget_set_size_request(launch_button, 150, 150);
        gtk_button_set_relief(GTK_BUTTON(launch_button), GTK_RELIEF_NONE);
        gtk_widget_set_tooltip_text(launch_button, categories[cat_index].apps[j].command);
        gtk_widget_show(launch_button);
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

    // Initialize categories
    initialize_categories();

    // Read data from Data.conf
    // This is the file the script will read.
    read_data("Data.conf");

    // Create main window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Bondi - V7");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(window, "key-press-event", G_CALLBACK(on_key_press), NULL);

    // Create grid layout for main window
    GtkWidget *grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    // Apply CSS styling to the whole application
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(provider,
                                    ".app-button {"
                                    "   background-color: #4CAF50;"
                                    "   border: none;"
                                    "   color: white;"
                                    "   padding: 10px 20px;"
                                    "   text-align: center;"
                                    "   text-decoration: none;"
                                    "   display: inline-block;"
                                    "   font-size: 16px;"
                                    "   margin: 4px 2px;"
                                    "   cursor: pointer;"
                                    "   border-radius: 12px;"
                                    "}"
                                    ".app-button:hover {"
                                    "   background-color: #45a049;"
                                    "}"
                                    ".category-button {"
                                    "   background-color: #008CBA;"
                                    "   border: none;"
                                    "   color: white;"
                                    "   padding: 10px 20px;"
                                    "   text-align: center;"
                                    "   text-decoration: none;"
                                    "   display: inline-block;"
                                    "   font-size: 16px;"
                                    "   margin: 4px 2px;"
                                    "   cursor: pointer;"
                                    "   border-radius: 12px;"
                                    "}"
                                    ".category-button:hover {"
                                    "   background-color: #006E9D;"
                                    "}",
                                    -1,
                                    NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);

    // Create sidebar
    GtkWidget *sidebar = gtk_list_box_new();
    gtk_grid_attach(GTK_GRID(grid), sidebar, 0, 0, 1, 1);

    // Populate sidebar with category buttons
    for (int i = 0; i < num_categories; i++) {
        GtkWidget *category_button = gtk_button_new_with_label(categories[i].name);
        gtk_style_context_add_class(GTK_STYLE_CONTEXT(category_button), "category-button");
        gtk_container_add(GTK_CONTAINER(sidebar), category_button);

        // Create a grid for each category
        GtkWidget *category_grid = gtk_grid_new();
        gtk_grid_set_row_homogeneous(GTK_GRID(category_grid), TRUE);
        gtk_grid_set_column_homogeneous(GTK_GRID(category_grid), TRUE);
        gtk_grid_attach(GTK_GRID(grid), category_grid, 1, 0, 1, 1);
        
        // Connect the load_apps callback to each category button
        g_signal_connect(category_button, "clicked", G_CALLBACK(load_apps), category_grid);
    }

    // Show all widgets
    gtk_widget_show_all(window);

    // Run the GTK main loop
    gtk_main();

    // Free allocated memory
    for (int i = 0; i < num_categories; i++) {
        free(categories[i].apps);
    }
    free(categories);

    return 0;
}
