import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.*;
import java.util.ArrayList;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;

public class Bondi extends JFrame {
    // Constants for file paths
    private static final String SUBSECTIONS_FILE_PATH = "subsections.ini";
    private static final String GAMES_FILE_PATH = "Games.ini";
    private static final String CONFIG_FILE_PATH = "Config/SidebarWidth.ini";

    private List<String> categories = new ArrayList<>();
    private JPanel gameButtonPanel;
    private JPanel subArea;

    private int sidebarWidth = 200; // Default sidebar width

    private List<Game> games = new ArrayList<>(); // New list for games

    public Bondi() {
        // Load categories from subsections.ini
        loadCategories();

        setTitle("Bondi");
        setExtendedState(JFrame.MAXIMIZED_BOTH);
        setDefaultCloseOperation(EXIT_ON_CLOSE);

        // Set a modern UI look and feel if available
        setSystemLookAndFeel();

        // Create a sidebar for category buttons
        JPanel sidebar = new JPanel(new GridBagLayout());
        GridBagConstraints gbc = new GridBagConstraints();
        gbc.gridx = 0;
        gbc.gridy = 0;
        gbc.fill = GridBagConstraints.HORIZONTAL;
        gbc.weightx = 1.0; // Allow buttons to expand horizontally
        gbc.insets = new Insets(5, 5, 5, 5); // Add padding

        Font buttonFont = new Font("Arial", Font.PLAIN, 18); // Set a larger font
        for (String category : categories) {
            JButton categoryButton = new JButton(category);
            categoryButton.addActionListener(new CategoryButtonListener(category));
            categoryButton.setFont(buttonFont); // Apply the larger font
            sidebar.add(categoryButton, gbc);
            gbc.gridy++; // Move to the next row
        }

        // Create a sub-area with a white background
        subArea = new JPanel(new BorderLayout()); // Use BorderLayout for the subArea

        // Create a panel for game buttons
        gameButtonPanel = new JPanel(new GridLayout(0, 3, 10, 10)); // 3 columns, 10px horizontal and vertical gaps

        // Create a split pane to separate the sidebar and sub-area
        JSplitPane splitPane = new JSplitPane(JSplitPane.HORIZONTAL_SPLIT, sidebar, subArea);
        splitPane.setDividerLocation(sidebarWidth); // Set initial divider location
        splitPane.setResizeWeight(0.0); // Disable resizing of the sidebar

        // Add the split pane to the frame
        add(splitPane);

        createMenuBar(); // New method to add a menu bar

        setLocationRelativeTo(null); // Center the window

        // Load the saved sidebar width from the configuration file
        loadSidebarWidth();
    }

    // Load categories from subsections.ini
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

    // Set system look and feel
    private void setSystemLookAndFeel() {
        try {
            UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
        } catch (Exception e) {
            logError("Error setting system look and feel", e);
        }
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
                        gameButton.setFont(new Font("Arial", Font.PLAIN, 24)); // Larger font for game buttons
                        gameButton.addActionListener(e -> {
                            try {
                                // Execute the command when the game button is clicked
                                ProcessBuilder pb = new ProcessBuilder("bash", "-c", commandPart);
                                pb.start();
                            } catch (IOException ex) {
                                logError("Error executing game command: " + commandPart, ex);
                            }
                        });
                        gameButtonPanel.add(gameButton);
                    }
                }
            }
        } catch (IOException e) {
            logError("Error loading games from " + GAMES_FILE_PATH, e);
        }

        gameButtonPanel.revalidate();
        gameButtonPanel.repaint();

        // Remove any previous components in the subArea
        subArea.removeAll();

        // Add gameButtonPanel to the subArea's center
        subArea.add(gameButtonPanel, BorderLayout.CENTER);

        // Refresh the subArea
        subArea.revalidate();
        subArea.repaint();
    }

    // Save the sidebar width to the configuration file
    private void saveSidebarWidth(int width) {
        try (FileWriter writer = new FileWriter(CONFIG_FILE_PATH)) {
            writer.write(String.valueOf(width));
        } catch (IOException e) {
            logError("Error saving sidebar width to " + CONFIG_FILE_PATH, e);
        }
    }

    // Load the saved sidebar width from the configuration file
    private void loadSidebarWidth() {
        File configFile = new File(CONFIG_FILE_PATH);
        if (configFile.exists()) {
            try (BufferedReader reader = new BufferedReader(new FileReader(CONFIG_FILE_PATH))) {
                String line = reader.readLine();
                if (line != null && !line.isEmpty()) {
                    sidebarWidth = Integer.parseInt(line);
                }
            } catch (IOException e) {
                logError("Error loading sidebar width from " + CONFIG_FILE_PATH, e);
            }
        }
    }

    // New method to create a menu bar
    private void createMenuBar() {
        JMenuBar menuBar = new JMenuBar();
        JMenu optionsMenu = new JMenu("Options");
        JMenuItem changeWidthItem = new JMenuItem("Change Sidebar Width");
        changeWidthItem.addActionListener(e -> {
            String input = JOptionPane.showInputDialog("Enter new sidebar width:");
            try {
                int newWidth = Integer.parseInt(input);
                updateSidebarWidth(newWidth);
            } catch (NumberFormatException ex) {
                JOptionPane.showMessageDialog(this, "Invalid input. Please enter a valid number.", "Error", JOptionPane.ERROR_MESSAGE);
            }
        });
        optionsMenu.add(changeWidthItem);

        // New menu item to create a new game
        JMenuItem createGameItem = new JMenuItem("Create New Game");
        createGameItem.addActionListener(e -> createNewGameDialog());
        optionsMenu.add(createGameItem);

        menuBar.add(optionsMenu);
        setJMenuBar(menuBar);
    }

    // New method to update the sidebar width
    private void updateSidebarWidth(int newWidth) {
        sidebarWidth = newWidth;
        saveSidebarWidth(newWidth);
        // Update the divider location in the split pane
        JSplitPane splitPane = (JSplitPane) getContentPane().getComponent(0);
        splitPane.setDividerLocation(newWidth);
    }

    // New method to add a new game
    private void addNewGame(String category, String gameName, String command) {
        Game newGame = new Game(category, gameName, command);
        games.add(newGame);
        saveGamesToFile(games, GAMES_FILE_PATH);
        displayGameButtonsForCategory(category);
    }

    // New method to create a dialog for adding a new game
    private void createNewGameDialog() {
        String category = JOptionPane.showInputDialog("Enter the game category:");
        String gameName = JOptionPane.showInputDialog("Enter the game name:");
        String command = JOptionPane.showInputDialog("Enter the game command:");
        addNewGame(category, gameName, command);
    }

    // New method to save games to a file (append mode)
    private void saveGamesToFile(List<Game> games, String filePath) {
        try (BufferedWriter writer = new BufferedWriter(new FileWriter(filePath, true))) {
            for (Game game : games) {
                writer.write(game.toCustomFormat());
                writer.newLine();
            }
        } catch (IOException e) {
            logError("Error saving games to " + filePath, e);
        }
    }

    // New method to load games from a file
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
            logError("Error loading games from " + filePath, e);
        }
        return games;
    }

    // Logging utility
    private static final Logger logger = Logger.getLogger(Bondi.class.getName());

    private void logError(String message, Throwable e) {
        logger.log(Level.SEVERE, message, e);
        // Display a user-friendly error message if needed
        JOptionPane.showMessageDialog(this, "An error occurred: " + e.getMessage(), "Error", JOptionPane.ERROR_MESSAGE);
    }

    // Game class to represent game data
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
            launcher.setExtendedState(JFrame.MAXIMIZED_BOTH); // Set to fullscreen mode
            launcher.setVisible(true);
        });
    }
}
