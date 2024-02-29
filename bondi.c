#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QListWidget>
#include <QGridLayout>
#include <QFile>
#include <QMessageBox>

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
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(nullptr, "Error", "Failed to open Data.conf. Make sure the file exists.");
        exit(EXIT_FAILURE);
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split("|");

        // Extract category name
        QString category_name = parts[0];

        // Check if the category already exists
        int cat_index;
        for (cat_index = 0; cat_index < num_categories; cat_index++) {
            if (strcmp(categories[cat_index].name, category_name.toUtf8().constData()) == 0)
                break;
        }

        // If the category doesn't exist, add it
        if (cat_index == num_categories) {
            strcpy(categories[num_categories].name, category_name.toUtf8().constData());
            categories[num_categories].num_apps = 0;
            num_categories++;
        }

        // Extract app name and command
        QString app_name = parts[1];
        QString app_command = parts[2];

        // Add app to the category
        strcpy(categories[cat_index].apps[categories[cat_index].num_apps].name, app_name.toUtf8().constData());
        strcpy(categories[cat_index].apps[categories[cat_index].num_apps].command, app_command.toUtf8().constData());
        categories[cat_index].num_apps++;
    }

    file.close();
}

// Slot function for launching an app
void launch_app(const QString &command) {
    system(command.toUtf8().constData());
}

// Slot function for loading apps of a category
void load_apps(const QString &category_name, QGridLayout *mainLayout) {
    // Clear previous apps
    QLayoutItem *child;
    while ((child = mainLayout->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }

    // Find category index
    int cat_index;
    for (cat_index = 0; cat_index < num_categories; cat_index++) {
        if (strcmp(categories[cat_index].name, category_name.toUtf8().constData()) == 0)
            break;
    }

    // Add apps buttons to the main area
    for (int j = 0; j < categories[cat_index].num_apps; j++) {
        QPushButton *launch_button = new QPushButton(categories[cat_index].apps[j].name);
        mainLayout->addWidget(launch_button, j / 3, j % 3, 1, 1);
        QObject::connect(launch_button, &QPushButton::clicked, [=]() {
            launch_app(categories[cat_index].apps[j].command);
        });
    }
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Read data from Data.conf
    // This is the file the script will read.
    read_data("Data.conf");

    // Create main window
    QWidget window;
    window.setWindowTitle("Bondi - V4");
    window.resize(600, 400);

    // Create main layout
    QVBoxLayout *mainLayout = new QVBoxLayout(&window);

    // Create sidebar
    QListWidget *sidebar = new QListWidget(&window);
    mainLayout->addWidget(sidebar);

    // Populate sidebar with category buttons
    for (int i = 0; i < num_categories; i++) {
        sidebar->addItem(categories[i].name);
        QObject::connect(sidebar, &QListWidget::itemClicked, [=](QListWidgetItem *item) {
            load_apps(item->text(), mainLayout);
        });
    }

    // Create main area
    QGridLayout *mainArea = new QGridLayout();
    mainLayout->addLayout(mainArea);

    window.show();

    return app.exec();
}
