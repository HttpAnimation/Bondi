import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.GridLayout;
import java.awt.Insets;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.*;
import java.net.URL;
import java.util.*;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JSplitPane;
import javax.swing.SwingUtilities;
import javax.swing.UIManager;


public class Bondi extends JFrame {
    private static final String UPDATE_CHECK_URL = "https://raw.githubusercontent.com/HttpAnimation/Bondi/main/Version.ini";
    private static final String SUBSECTIONS_FILE_PATH = "Config/subsections.ini";
    private static final String GAMES_FILE_PATH = "Config/Games.ini";
    private static final String CONFIG_FILE_PATH = "Config/SidebarWidth.ini";
    private static final String UPDATE_PREFERENCE_FILE_PATH = "Config/Update.ini";

    private List<String> categories = new ArrayList<>();
    private JPanel gameButtonPanel;
    private JPanel subArea;
    private boolean darkMode = true;
    private int sidebarWidth = 230;

    // Needed lists
    private List<Game> games = new ArrayList<>();
    private List<Map<String, List<String>>> repos = new ArrayList<>();

    private static boolean isWindows() {
        return System.getProperty("os.name").toLowerCase().contains("win");
    }

    public Bondi() {
        if (isWindows()) {
            System.out.println("Bondi does not support Windows.");
            System.out.println("Due to Windows being closed-source and no way to run unix commands on it, Bondi is unable to be run on it. You can try the Linux subsystem for Windows, but there may still be issues while running Bondi.");
            System.out.println("Bondi does run natively on Linux and MacOS X. Consider switching to make Bondi fully work.");
            System.exit(1);
        }
        loadCategories();
        System.out.println("Welcome to Bondi");
        System.out.println("Github: ");
        System.out.println("https://github.com/HttpAnimation/Bondi");
        System.out.println("Bondi is made by: HttpAnimations");
        System.out.println("Bondi is now loading");
        System.out.println("This version of Bondi is a dev-branch for testing repos.");

        setTitle("Bondi Repo-Testing");
        setExtendedState(JFrame.MAXIMIZED_BOTH);
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        setSystemLookAndFeel();

        JPanel sidebar = new JPanel(new GridBagLayout());
        GridBagConstraints gbc = new GridBagConstraints();
        gbc.gridx = 0;
        gbc.gridy = 0;
        gbc.fill = GridBagConstraints.HORIZONTAL;
        gbc.weightx = 1.0;
        gbc.insets = new Insets(5, 5, 5, 5);
        Font buttonFont = new Font("Arial", Font.PLAIN, 18);
        for (String category : categories) {
            JButton categoryButton = new JButton(category);
            categoryButton.addActionListener(new CategoryButtonListener(category));
            categoryButton.setFont(buttonFont);
            sidebar.add(categoryButton, gbc);
            gbc.gridy++;
        }

        subArea = new JPanel(new BorderLayout());
        gameButtonPanel = new JPanel(new GridLayout(0, 3, 10, 10));
        JSplitPane splitPane = new JSplitPane(JSplitPane.HORIZONTAL_SPLIT, sidebar, subArea);
        splitPane.setDividerLocation(sidebarWidth);
        splitPane.setResizeWeight(0.0);
        add(splitPane);
        createMenuBar();
        setLocationRelativeTo(null);
        updateColors();
        setMinimumSize(new Dimension(800, 600));
        loadCategories();
        checkForUpdate();
        loadRepos();  // Added to load repos during initialization
    }

    private void checkForUpdate() {
        try {
            URL url = new URL(UPDATE_CHECK_URL);
            try (Scanner scanner = new Scanner(url.openStream())) {
                while (scanner.hasNextLine()) {
                    String line = scanner.nextLine().trim();
                    if (!line.startsWith("#") && line.startsWith("version")) {
                        int remoteVersion = Integer.parseInt(line.split("=")[1].trim());
                        /// Version tag
                        int localVersion = 999;
                        // Below is the testing command if you need to force a lower version.
                        //int localVersion = 2; 
                        System.out.println("Version's loaded");
                        System.out.println("Bondi is now opening.");
                        if (localVersion < remoteVersion) {
                            showUpdatePrompt();
                        }
                        break;
                    }
                }
            }
        } catch (IOException | NumberFormatException e) {
            logError("Error checking for updates", e);
        }
    }

    private void loadCategories() {
        try (BufferedReader reader = new BufferedReader(new FileReader(SUBSECTIONS_FILE_PATH))) {
            String line;
            while ((line = reader.readLine()) != null) {
                categories.add(line.trim());
            }
        } catch (IOException e) {
            logError("Error loading categories from " + SUBSECTIONS_FILE_PATH, e);
        }
    }

    private void setSystemLookAndFeel() {
    try {
        UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
    } catch (Exception e) {
        logError("Error setting system look and feel", e);
    }
}

    private void showUpdatePrompt() {
        try {
            File updatePreferenceFile = new File(UPDATE_PREFERENCE_FILE_PATH);
            boolean showUpdatePrompt = true;

            if (updatePreferenceFile.exists()) {
                try (BufferedReader reader = new BufferedReader(new FileReader(UPDATE_PREFERENCE_FILE_PATH))) {
                    String line = reader.readLine();
                    if (line != null && !line.isEmpty()) {
                        showUpdatePrompt = line.trim().equals("1");
                    }
                }
            }

            if (showUpdatePrompt) {
                int choice = JOptionPane.showOptionDialog(
                        this,
                        "An update is available! Do you want to update?",
                        "Update Available",
                        JOptionPane.YES_NO_OPTION,
                        JOptionPane.INFORMATION_MESSAGE,
                        null,
                        new Object[]{"Update", "Never show again", "Close"},
                        "Update");

                if (choice == 0) {
                    openUpdatePage();
                } else if (choice == 1) {
                    try (FileWriter writer = new FileWriter(UPDATE_PREFERENCE_FILE_PATH)) {
                        writer.write("0");
                    } catch (IOException e) {
                        logError("Error saving update preference to " + UPDATE_PREFERENCE_FILE_PATH, e);
                    }
                }
            }
        } catch (Exception e) {
            logError("Error showing update prompt", e);
        }
    }

    private void openUpdatePage() {
        try {
            String command = "firefox https://github.com/HttpAnimation/Bondi";
            ProcessBuilder processBuilder = new ProcessBuilder("bash", "-c", command);
            processBuilder.start();
            System.exit(1);
        } catch (IOException e) {
            logError("Error opening update page: " + e.getMessage(), e);
        }
    }

    private void loadRepos() {
        try (BufferedReader reader = new BufferedReader(new FileReader("Config/Repos.ini"))) {
            String line;
            StringBuilder jsonContent = new StringBuilder();
            while ((line = reader.readLine()) != null) {
                jsonContent.append(line).append("\n");
            }

            parseRepos(jsonContent.toString());
        } catch (IOException e) {
            logError("Error loading repos from Config/Repos.ini", e);
        }
    }

    private void parseRepos(String jsonContent) {
        try {
            List<Map<String, List<String>>> parsedRepos = new ArrayList<>();

            // Remove square brackets from the JSON content
            String cleanedJson = jsonContent.trim().substring(1, jsonContent.length() - 2);

            // Split the content into each repository
            String[] reposArray = cleanedJson.split("\\},\\s*\\{");

            for (String repo : reposArray) {
                Map<String, List<String>> repoMap = new HashMap<>();

                // Split into subsections and games
                String[] sections = repo.split(",\\s*");

                for (String section : sections) {
                    String[] keyValue = section.split(":\\s*\\[");
                    String key = keyValue[0].trim().replace("\"", "");
                    String[] values = keyValue[1].replace("\"", "").split(",\\s*");

                    List<String> valueList = new ArrayList<>(Arrays.asList(values));
                    repoMap.put(key, valueList);
                }

                parsedRepos.add(repoMap);
            }

            repos.addAll(parsedRepos);

        } catch (Exception e) {
            logError("Error parsing JSON content from Config/Repos.ini", e);
        }
    }

    private void createMenuBar() {
        JMenuBar menuBar = new JMenuBar();
        JMenu optionsMenu = new JMenu("Options");
        JMenuItem changeWidthItem = new JMenuItem("Change Sidebar Width");
        changeWidthItem.addActionListener(e -> {
            String input = JOptionPane.showInputDialog("Enter the new Width:");
            try {
                int newWidth = Integer.parseInt(input);
                updateSidebarWidth(newWidth);
            } catch (NumberFormatException ex) {
                JOptionPane.showMessageDialog(this, "Numbers not found please only use numbers.", "Error", JOptionPane.ERROR_MESSAGE);
            }
        });
        optionsMenu.add(changeWidthItem);

        JMenuItem createGameItem = new JMenuItem("Create New Game");
        createGameItem.addActionListener(e -> createNewGameDialog());
        optionsMenu.add(createGameItem);

        menuBar.add(optionsMenu);
        setJMenuBar(menuBar);
    }

    private void updateSidebarWidth(int newWidth) {
        sidebarWidth = newWidth;
        saveSidebarWidth(newWidth);
        JSplitPane splitPane = (JSplitPane) getContentPane().getComponent(0);
        splitPane.setDividerLocation(newWidth);
    }

    private void addNewGame(String category, String gameName, String command) {
        Game newGame = new Game(category, gameName, command);
        games.add(newGame);
        saveGamesToFile(games, GAMES_FILE_PATH);
        displayGameButtonsForCategory(category);
    }

    private void createNewGameDialog() {
        String category = JOptionPane.showInputDialog("Enter the app/game category:");
        String gameName = JOptionPane.showInputDialog("Enter the app/game name:");
        String command = JOptionPane.showInputDialog("Enter the app/game command:");
        addNewGame(category, gameName, command);
    }

    private class CategoryButtonListener implements ActionListener {
        private String category;

        public CategoryButtonListener(String category) {
            this.category = category;
        }

        @Override
        public void actionPerformed(ActionEvent e) {
            displayGameButtonsForCategory(category);
        }
    }

    private void displayGameButtonsForCategory(String category) {
        gameButtonPanel.removeAll();

        try (BufferedReader reader = new BufferedReader(new FileReader(GAMES_FILE_PATH))) {
            String line;
            while ((line = reader.readLine()) != null) {
                String[] parts = line.split("\\|");
                if (parts.length >= 3) {
                    String categoryPart = parts[0].trim();
                    String gameNamePart = parts[1].trim();
                    String commandPart = parts[2].trim();

                    if (categoryPart.equals(category)) {
                        JButton gameButton = new JButton(gameNamePart);
                        gameButton.setFont(new Font("Arial", Font.PLAIN, 24));
                        gameButton.addActionListener(e -> {
                            try {
                                ProcessBuilder pb = new ProcessBuilder("bash", "-c", commandPart);
                                pb.start();
                            } catch (IOException ex) {
                                logError("Error executing game command sorry mate. : " + commandPart, ex);
                            }
                        });
                        gameButton.setMargin(new Insets(10, 10, 10, 10));
                        
                        gameButtonPanel.add(gameButton);                        
                    }
                }
            }
    } catch (IOException e) {
        logError("Error loading games from " + GAMES_FILE_PATH, e);
    }
}

    private void saveSidebarWidth(int width) {
        try (FileWriter writer = new FileWriter(CONFIG_FILE_PATH)) {
            writer.write(String.valueOf(width));
        } catch (IOException e) {
            logError("Error saving sidebar width to " + CONFIG_FILE_PATH, e);
        }
    }

    private void saveGamesToFile(List<Game> games, String filePath) {
        try (BufferedWriter writer = new BufferedWriter(new FileWriter(filePath, true))) {
            for (Game game : games) {
                writer.write(game.toCustomFormat());
                writer.newLine();
            }
        } catch (IOException e) {
            logError("Error saving app/games to " + filePath, e);
        }
    }

    private List<Game> loadGamesFromFile(String filePath) {
        List<Game> games = new ArrayList<>();
        try (BufferedReader reader = new BufferedReader(new FileReader(filePath))) {
            String line;
            while ((line = reader.readLine()) != null) {
                Game game = Game.fromCustomFormat(line);
                if (game != null) {
                    games.add(game);
                }
            }
        } catch (IOException e) {
            logError("Error loading games from " + filePath + " - make sure that the file is located in the Bondi folder", e);
        }

        return games;
    }

    private static final Logger logger = Logger.getLogger(Bondi.class.getName());

    
    private void logError(String message, Throwable e) {
        if (e != null) {
            logger.log(Level.SEVERE, message, e);
            JOptionPane.showMessageDialog(this, "An error occurred: " + e.getMessage(), "Error", JOptionPane.ERROR_MESSAGE);
        } else {
            logger.log(Level.SEVERE, message);
            JOptionPane.showMessageDialog(this, "An error occurred: " + message, "Error", JOptionPane.ERROR_MESSAGE);
        }
    }

    private void logError(String message) {
        logError(message, null);
    }

    public static class Game {
        private String category;
        private String gameName;
        private String command;

        public Game(String category, String gameName, String command) {
            this.category = category;
            this.gameName = gameName;
            this.command = command;
        }

        public String toCustomFormat() {
            return category + "|" + gameName + "|" + command;
        }

        public static Game fromCustomFormat(String line) {
            String[] parts = line.split("\\|");
            if (parts.length >= 3) {
                return new Game(parts[0], parts[1], parts[2]);
            }
            return null;
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            Bondi launcher = new Bondi();
            launcher.setExtendedState(JFrame.MAXIMIZED_BOTH);
            launcher.setUndecorated(true); // Set to undecorated mode
            launcher.setVisible(true);
        });
    }

    private void toggleDarkMode() {
        darkMode = !darkMode;
        updateColors();
    }

    private void updateColors() {
        if (darkMode) {
            UIManager.put("Panel.background", Color.darkGray);
            UIManager.put("MenuBar.background", Color.darkGray);
            UIManager.put("Menu.background", Color.darkGray);
            UIManager.put("MenuItem.background", Color.darkGray);
            UIManager.put("MenuItem.foreground", Color.white);
            UIManager.put("Button.background", Color.darkGray);
            UIManager.put("Button.foreground", Color.white);
            UIManager.put("SplitPaneDivider.draggingColor", Color.darkGray);
            subArea.setBackground(Color.darkGray);
        } else {
            UIManager.put("Panel.background", UIManager.getDefaults().getColor("Panel.background"));
            UIManager.put("MenuBar.background", UIManager.getDefaults().getColor("MenuBar.background"));
            UIManager.put("Menu.background", UIManager.getDefaults().getColor("Menu.background"));
            UIManager.put("MenuItem.background", UIManager.getDefaults().getColor("MenuItem.background"));
            UIManager.put("MenuItem.foreground", UIManager.getDefaults().getColor("MenuItem.foreground"));
            UIManager.put("Button.background", UIManager.getDefaults().getColor("Button.background"));
            UIManager.put("Button.foreground", UIManager.getDefaults().getColor("Button.foreground"));
            subArea.setBackground(UIManager.getDefaults().getColor("Panel.background"));
            UIManager.put("SplitPaneDivider.draggingColor", UIManager.getDefaults().getColor("SplitPaneDivider.draggingColor"));
        }
        SwingUtilities.updateComponentTreeUI(this);
    }
}