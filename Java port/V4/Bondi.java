import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.*;
import java.util.ArrayList;
import java.util.List;

public class Bondi extends JFrame {

    private List<String> categories = new ArrayList<>();
    private JPanel gameButtonPanel;
    private JPanel subArea;

    private final String configFilePath = "Config/SidebarWidth.ini"; // Configuration file path
    private int sidebarWidth = 250; // Default sidebar width

    public Bondi() {
        // Load categories from subsections.ini
        try (BufferedReader reader = new BufferedReader(new FileReader("subsections.ini"))) {
            String line;
            while ((line = reader.readLine()) != null) {
                categories.add(line.trim());
            }
        } catch (IOException e) {
            e.printStackTrace();
        }

        setTitle("Bondi");
        setExtendedState(JFrame.MAXIMIZED_BOTH);
        setDefaultCloseOperation(EXIT_ON_CLOSE);

        // Set a modern UI look and feel if available
        try {
            UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
        } catch (Exception e) {
            e.printStackTrace();
        }

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
        subArea = new JPanel(new GridLayout(0, 3, 10, 10)); // 3 columns, 10px horizontal and vertical gaps

        // Create a panel for game buttons
        gameButtonPanel = new JPanel(new FlowLayout());

        // Create a split pane to separate the sidebar and sub-area
        JSplitPane splitPane = new JSplitPane(JSplitPane.HORIZONTAL_SPLIT, sidebar, subArea);
        splitPane.setDividerLocation(sidebarWidth); // Set initial divider location
        splitPane.setResizeWeight(0.0); // Disable resizing of the sidebar

        // Add the split pane to the frame
        add(splitPane);

        setLocationRelativeTo(null); // Center the window

        // Load the saved sidebar width from the configuration file
        loadSidebarWidth();
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

        try (BufferedReader reader = new BufferedReader(new FileReader("Games.ini"))) {
            String line;
            while ((line = reader.readLine()) != null) {
                String[] parts = line.split("\\|");
                if (parts.length == 3 && parts[0].trim().equals(category.trim())) {
                    String gameName = parts[1].trim();
                    JButton gameButton = new JButton(gameName);
                    gameButton.setFont(new Font("Arial", Font.PLAIN, 24)); // Larger font for game buttons
                    String command = parts[2].trim();
                    gameButton.addActionListener(new ActionListener() {
                        @Override
                        public void actionPerformed(ActionEvent e) {
                            try {
                                // Execute the command when the game button is clicked
                                ProcessBuilder pb = new ProcessBuilder("bash", "-c", command);
                                pb.start();
                            } catch (IOException ex) {
                                ex.printStackTrace();
                            }
                        }
                    });
                    gameButtonPanel.add(gameButton);
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }

        gameButtonPanel.revalidate();
        gameButtonPanel.repaint();

        // Remove any previous components in the subArea
        subArea.removeAll();

        // Add gameButtonPanel to the subArea's center
        subArea.add(gameButtonPanel);

        // Refresh the subArea
        subArea.revalidate();
        subArea.repaint();
    }

    // Save the sidebar width to the configuration file
   // Not used
    private void saveSidebarWidth(int width) {
        try (FileWriter writer = new FileWriter(configFilePath)) {
            writer.write(String.valueOf(width));
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    // Load the saved sidebar width from the configuration file
    private void loadSidebarWidth() {
        File configFile = new File(configFilePath);
        if (configFile.exists()) {
            try (BufferedReader reader = new BufferedReader(new FileReader(configFilePath))) {
                String line = reader.readLine();
                if (line != null && !line.isEmpty()) {
                    sidebarWidth = Integer.parseInt(line);
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            Bondi launcher = new Bondi();
            launcher.setVisible(true);
        });
    }
}
