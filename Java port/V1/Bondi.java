import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;

public class Bondi extends JFrame {

    private List<String> categories = new ArrayList<>();
    private JTextArea gameListArea;

    public Bondi() {
        // Load categories from subsections.ini
        try {
            categories = Files.readAllLines(Paths.get("subsections.ini"));
        } catch (IOException e) {
            e.printStackTrace();
        }

        setTitle("Game Launcher");
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        setLayout(new BorderLayout());

        // Create a panel for category buttons
        JPanel categoryPanel = new JPanel(new FlowLayout());
        for (String category : categories) {
            JButton categoryButton = new JButton(category);
            categoryButton.addActionListener(new CategoryButtonListener());
            categoryPanel.add(categoryButton);
        }

        // Create a text area for displaying the game list
        gameListArea = new JTextArea(20, 40);
        gameListArea.setEditable(false);

        // Add components to the frame
        add(categoryPanel, BorderLayout.NORTH);
        add(new JScrollPane(gameListArea), BorderLayout.CENTER);

        pack();
        setLocationRelativeTo(null); // Center the window
    }

    private class CategoryButtonListener implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            String selectedCategory = ((JButton) e.getSource()).getText();
            displayGameList(selectedCategory);
        }
    }

    private void displayGameList(String category) {
        gameListArea.setText("");
        try {
            List<String> games = Files.readAllLines(Paths.get("Games.ini"));
            for (String line : games) {
                String[] parts = line.split("\\|");
                if (parts.length == 3 && parts[0].trim().equals(category.trim())) {
                    gameListArea.append(parts[1].trim() + "\n");
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            Bondi launcher = new Bondi();
            launcher.setVisible(true);
        });
    }
}
