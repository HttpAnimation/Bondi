#include <QApplication>
#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QFile>
#include <QTextStream>
#include <QProcess>
#include <QDebug>

#define MAX_APPS 100
#define MAX_NAME_LENGTH 50
#define MAX_COMMAND_LENGTH 100
#define VERSION 8
#define CONFIG_FILE "config.conf"

struct App {
    QString name;
    QString command;
};

App apps[MAX_APPS];
int numApps = 0;

void readConfigFile() {
    QFile file(CONFIG_FILE);
    if (!file.open(QIODevice::ReadOnly)) {
        qCritical() << "Error opening config file";
        exit(EXIT_FAILURE);
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(':');
        if (parts.size() == 2) {
            apps[numApps].name = parts[0].trimmed();
            apps[numApps].command = parts[1].trimmed();
            numApps++;
            if (numApps >= MAX_APPS) {
                qCritical() << "Too many applications in config file";
                break;
            }
        }
    }

    file.close();
}

void launchApp(int appIndex) {
    QProcess process;
    process.startDetached("/bin/sh", QStringList() << "-c" << apps[appIndex].command);
    process.waitForFinished(-1);
    qDebug() << "Application has exited with status:" << process.exitCode();
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Read configuration file
    readConfigFile();

    // Create a main window
    QWidget window;
    window.setWindowTitle("Bondi - Big Picture Mode");
    window.resize(1280, 720);

    // Create a layout
    QVBoxLayout *layout = new QVBoxLayout(&window);

    // Add title label
    QLabel *titleLabel = new QLabel(QString("Bondi CV%1").arg(VERSION));
    titleLabel->setStyleSheet("font-size: 24px; color: #FFFFFF;");
    layout->addWidget(titleLabel);

    // Add buttons
    QGridLayout *gridLayout = new QGridLayout();
    for (int i = 0; i < numApps; ++i) {
        QPushButton *button = new QPushButton(apps[i].name);
        connect(button, &QPushButton::clicked, [i]() { launchApp(i); });
        gridLayout->addWidget(button, i, 0);
    }
    layout->addLayout(gridLayout);

    window.show();

    return app.exec();
}
