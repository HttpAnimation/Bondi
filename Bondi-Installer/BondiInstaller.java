import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class BondiInstaller extends Application {
    private static final String INI_FILE_URL = "https://github.com/HttpAnimation/Bondi/raw/main/Bondi-Installer/Repo/Repo.ini";

    public static void main(String[] args) {
        launch(args);
    }

    @Override
    public void start(Stage primaryStage) {
        // Read INI file and extract version information
        VersionInfo versionInfo = readIniFile(INI_FILE_URL);

        // Create UI elements
        VBox root = new VBox(10);
        Scene scene = new Scene(root, 300, 150);
        primaryStage.setTitle("Bondi Installer");
        primaryStage.setScene(scene);

        // Display version name
        System.out.println("Version Name: " + versionInfo.getName());

        // Check if the folder for the version exists
        Path versionFolder = Paths.get(versionInfo.getName());
        boolean isInstalled = Files.exists(versionFolder);

        // Create buttons based on installation status
        Button installButton = new Button("Install");
        Button uninstallButton = new Button("Uninstall");
        Button runButton = new Button("Run");
        Button compileButton = new Button("Compile");

        if (isInstalled) {
            root.getChildren().addAll(uninstallButton, runButton, compileButton);
            installButton.setDisable(true);
        } else {
            root.getChildren().add(installButton);
            uninstallButton.setDisable(true);
            runButton.setDisable(true);
            compileButton.setDisable(true);
        }

        // Install button action
        installButton.setOnAction(e -> {
            // Perform installation steps, e.g., create the folder
            System.out.println("Installing...");
            // You can add your installation logic here
            installButton.setDisable(true);
            uninstallButton.setDisable(false);
            runButton.setDisable(false);
            compileButton.setDisable(false);
        });

        // Uninstall button action
        uninstallButton.setOnAction(e -> {
            // Perform uninstallation steps, e.g., remove the folder
            System.out.println("Uninstalling...");
            // You can add your uninstallation logic here
            installButton.setDisable(false);
            uninstallButton.setDisable(true);
            runButton.setDisable(true);
            compileButton.setDisable(true);
        });

        // Run button action
        runButton.setOnAction(e -> {
            // Perform run steps, e.g., change directory and run command
            System.out.println("Running...");
            // You can add your run logic here
        });

        // Compile button action
        compileButton.setOnAction(e -> {
            // Perform compile steps, e.g., change directory and run javac command
            System.out.println("Compiling...");
            // You can add your compile logic here
        });

        primaryStage.show();
    }

    private VersionInfo readIniFile(String url) {
        // Implement logic to read and parse the INI file
        // For simplicity, a dummy VersionInfo is returned
        return new VersionInfo("Version-8");
    }
}

class VersionInfo {
    private String name;

    public VersionInfo(String name) {
        this.name = name;
    }

    public String getName() {
        return name;
    }
}
