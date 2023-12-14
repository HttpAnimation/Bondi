import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class Bondi extends JFrame {

    private List<String> categories = new ArrayList<>();
    private JPanel gameButtonPanel;
    private JPanel subArea;

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
        setUndecorated(true); 
        setExtendedState(JFrame.MAXIMIZED_BOTH); 
        setDefaultCloseOperation(EXIT_ON_CLOSE);

        
        getContentPane().setBackground(new Color(245, 154, 175)); 

        setLayout(new BorderLayout());

        
        JPanel categoryPanel = new JPanel(new FlowLayout());
        categoryPanel.setOpaque(false); 
        for (String category : categories) {
            JButton categoryButton = new JButton(category);
            categoryButton.addActionListener(new CategoryButtonListener(category));
            categoryPanel.add(categoryButton);
        }

        
        subArea = new JPanel(new BorderLayout());
        subArea.setBackground(new Color(207, 140, 156)); 

        
        gameButtonPanel = new JPanel(new FlowLayout());
        gameButtonPanel.setOpaque(false); 

        
        add(categoryPanel, BorderLayout.NORTH);
        add(subArea, BorderLayout.CENTER); 

        pack();
        setLocationRelativeTo(null); 
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

        
        subArea.add(gameButtonPanel, BorderLayout.CENTER);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            Bondi launcher = new Bondi();
            launcher.setVisible(true);
        });
    }
}
