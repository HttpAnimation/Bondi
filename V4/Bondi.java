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

    private final String configFilePath = "Config/SidebarWidth.ini"; 
    private int sidebarWidth = 250; 

    public Bondi() {
        
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

        
        try {
            UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
        } catch (Exception e) {
            e.printStackTrace();
        }

        
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

        
        subArea = new JPanel(new GridLayout(0, 3, 10, 10)); 

        
        gameButtonPanel = new JPanel(new FlowLayout());

        
        JSplitPane splitPane = new JSplitPane(JSplitPane.HORIZONTAL_SPLIT, sidebar, subArea);
        splitPane.setDividerLocation(sidebarWidth); 
        splitPane.setResizeWeight(0.0); 

        
        add(splitPane);

        setLocationRelativeTo(null); 

        
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
                    gameButton.setFont(new Font("Arial", Font.PLAIN, 24)); 
                    String command = parts[2].trim();
                    gameButton.addActionListener(new ActionListener() {
                        @Override
                        public void actionPerformed(ActionEvent e) {
                            try {
                                
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

        
        subArea.removeAll();

        
        subArea.add(gameButtonPanel);

        
        subArea.revalidate();
        subArea.repaint();
    }

    
   
    private void saveSidebarWidth(int width) {
        try (FileWriter writer = new FileWriter(configFilePath)) {
            writer.write(String.valueOf(width));
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    
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
