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
    
    private static final String SUBSECTIONS_FILE_PATH = "subsections.ini";
    private static final String GAMES_FILE_PATH = "Games.ini";
    private static final String CONFIG_FILE_PATH = "Config/SidebarWidth.ini";

    private List<String> categories = new ArrayList<>();
    private JPanel gameButtonPanel;
    private JPanel subArea;

    private int sidebarWidth = 500; 

    public Bondi() {
        
        loadCategories();

        setTitle("Bondi");
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

        setLocationRelativeTo(null); 

        
        loadSidebarWidth();
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
                if (parts.length == 3 && parts[0].trim().equals(category.trim())) {
                    String gameName = parts[1].trim();
                    JButton gameButton = new JButton(gameName);
                    gameButton.setFont(new Font("Arial", Font.PLAIN, 24)); 
                    String command = parts[2].trim();
                    gameButton.addActionListener(new ActionListener() {
                        @Override
                        public void actionPerformed(ActionEvent e) {
                            try {
                                
                                ProcessBuilder pb = new ProcessBuilder("bash", "-c", command);
                                pb.start();
                            } catch (IOException ex) {
                                logError("Error executing game command: " + command, ex);
                            }
                        }
                    });
                    gameButtonPanel.add(gameButton);
                }
            }
        } catch (IOException e) {
            logError("Error loading games from " + GAMES_FILE_PATH, e);
        }

        gameButtonPanel.revalidate();
        gameButtonPanel.repaint();

        
        subArea.removeAll();

        
        subArea.add(gameButtonPanel, BorderLayout.CENTER);

        
        subArea.revalidate();
        subArea.repaint();
    }

    
    private void saveSidebarWidth(int width) {
        try (FileWriter writer = new FileWriter(CONFIG_FILE_PATH)) {
            writer.write(String.valueOf(width));
        } catch (IOException e) {
            logError("Error saving sidebar width to " + CONFIG_FILE_PATH, e);
        }
    }

    
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

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            Bondi launcher = new Bondi();
            launcher.setVisible(true);
        });
    }

    
    private static final Logger logger = Logger.getLogger(Bondi.class.getName());

    private void logError(String message, Throwable e) {
        logger.log(Level.SEVERE, message, e);
        
        JOptionPane.showMessageDialog(this, "An error occurred: " + e.getMessage(), "Error", JOptionPane.ERROR_MESSAGE);
    }
}
