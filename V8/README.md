# Version 8 Change Log

## General Changes

1. **Version Number and Title:**
   - The application version has been updated to **V8**.
   - The title of the application now reflects the new version: **"Bondi V8"**.

2. **Operating System Check:**
   - Bondi now checks whether it is running on a Windows system.
   - If run on Windows, a message is displayed, stating that Bondi does not support Windows and provides information about potential issues.

3. **Update Checking:**
   - Bondi now includes functionality to check for updates by fetching version information from a specified URL.
   - If an update is available, users are prompted with an option to update or skip the update.

4. **Dark Mode:**
   - Dark mode has been introduced, allowing users to toggle between light and dark themes.
   - The UI colors are dynamically adjusted based on the selected mode.

5. **Minimum Window Size:**
   - The minimum size of the Bondi window has been set to ensure a responsive and usable interface.

6. **Undecorated Mode:**
   - The main frame is set to undecorated mode, removing the window decorations such as title bar and borders.

7. **GitHub Information:**
   - Information about Bondi's GitHub repository, the developer (HttpAnimations), and a welcome message are displayed in the console during application startup.

8. **System Look and Feel:**
   - The application utilizes the system look and feel for a native appearance.

## User Interface Changes

1. **Sidebar Width:**
   - The default width of the sidebar has been increased to **230 pixels**.

2. **Font and Margin Adjustment:**
   - Font size and margin settings for category buttons and game buttons have been adjusted for better readability and appearance.

3. **Update Prompt:**
   - Users are now prompted with an update message if a new version is available.
   - The prompt provides options to update, never show the update prompt again, or close the prompt.

4. **Menu Bar Items:**
   - The menu bar now includes a "Change Sidebar Width" option, allowing users to modify the sidebar width dynamically.
   - A "Create New Game" option has been added to the menu bar, providing a way to add new games to the configuration.

5. **Update Page Link:**
   - A link to the GitHub page for updates is provided in the update prompt, opening in the default web browser.

## Code Structure and Maintenance

1. **Code Reorganization:**
   - Code has been restructured for better organization and readability.
   - New methods have been introduced for specific functionalities, improving code modularity.

2. **Exception Handling:**
   - Improved exception handling and logging, providing more detailed information in case of errors.
   - The logging now includes stack traces for debugging purposes.

3. **Code Comments:**
   - Comments have been added or updated throughout the code for better understanding.

4. **Update Preference File:**
   - An update preference file is introduced to store user preferences regarding update prompts.

5. **Input Validation:**
   - Additional input validation is implemented, ensuring that user inputs are within acceptable ranges or formats.

6. **Toggle Dark Mode:**
   - A method to toggle dark mode is introduced, providing a visual switch between light and dark themes.

7. **Color Updates:**
   - The application dynamically updates UI colors based on the selected mode (light or dark).

8. **GitHub Information:**
   - GitHub information is displayed during the application startup for user awareness.

## Bug Fixes and Error Handling

1. **Error Messages:**
   - Improved error messages provide more context and information to users when an error occurs.

2. **Windows Compatibility:**
   - Bondi now explicitly mentions that it does not support Windows due to limitations in running Unix commands.

3. **File Path Corrections:**
   - File paths have been updated and corrected for consistency.

4. **UI Update Method:**
   - The method for updating UI colors has been refined for better performance and consistency.

5. **Update Check Exception Handling:**
   - Enhanced exception handling during the update check process to ensure smoother execution.

6. **Category Loading Error:**
   - Improved error handling when loading categories from the subsections file.

7. **Game Execution Error Message:**
   - If an error occurs during game execution, a more user-friendly error message is displayed.

8. **Undecorated Mode:**
   - The undecorated mode is set explicitly to enhance the application's appearance.

## Additional Notes

- **Testing Command:**
  - A testing command to force a lower version is included in the update check section for development and testing purposes.

- **GitHub Repository:**
  - The GitHub repository link is displayed in the console for user reference.

- **Console Messages:**
  - Various informational messages are added to the console during startup for user awareness.