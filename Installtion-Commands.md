# Bondi Installation Guide

## [Back](README.md)

To install Bondi, follow these simple steps:

1. Open your terminal.
2. Copy and paste the command for your selected version:

## Version 7
- This version added the following listed below.
    - Added a new list for games.
    - Added a new menu bar with an "Options" menu containing "Change Sidebar Width" and "Create New Game" options.
    - Added a method to update the sidebar width.
    - Added a method to add a new game.
    - Added a method to create a dialog for adding a new game.
    - Added a method to save games to a file (in append mode).
    - Added a method to load games from a file.
    - Added a Game class to represent game data.
    - Updated the displayGameButtonsForCategory method to use the new Game class and load games from the new list.
    - Updated the createMenuBar method to add a menu item for creating a new game.
    - Updated the CategoryButtonListener inner class to use the new displayGameButtonsForCategory method.
    - Updated the loadSidebarWidth method to use the new CONFIG_FILE_PATH constant.
    - Updated the saveSidebarWidth method to use try-with-resources.
    - Updated the displayGameButtonsForCategory method to remove all previous components in the subArea before adding new game buttons.
    - Updated the sidebarWidth default value to 200.
    ```
    git clone https://github.com/HttpAnimation/Bondi.git && cd Bondi && git sparse-checkout init --cone && git sparse-checkout set V7 && rm README.md && rm Setup-Guide.md && rm Installation-Commands.md && rm Install-Windows-Guide.md
    ```

## Version 6
- This version added the following listed .
    - This version is to old to support the version changelog.
    ```
    git clone https://github.com/HttpAnimation/Bondi.git && cd Bondi && git sparse-checkout init --cone && git sparse-checkout set V6 && rm README.md && rm Setup-Guide.md && rm Installation-Commands.md && rm Install-Windows-Guide.md
    ```

## Version 5
- This version added the following listed .
    - This version is to old to support the version changelog.
    ```
    git clone https://github.com/HttpAnimation/Bondi.git && cd Bondi && git sparse-checkout init --cone && git sparse-checkout set V5 && rm README.md && rm Setup-Guide.md && rm Installation-Commands.md && rm Install-Windows-Guide.md
    ```

## Version 4
- This version added the following listed .
    - This version is to old to support the version changelog.
    ```
    git clone https://github.com/HttpAnimation/Bondi.git && cd Bondi && git sparse-checkout init --cone && git sparse-checkout set V4 && rm README.md && rm Setup-Guide.md && rm Installation-Commands.md && rm Install-Windows-Guide.md
    ```

## Version 3
- This version added the following listed .
    - This version is to old to support the version changelog.
    ```
    git clone https://github.com/HttpAnimation/Bondi.git && cd Bondi && git sparse-checkout init --cone && git sparse-checkout set V3 && rm Runners.md && rm README.md && rm Setup-Guide.md && rm Installation-Commands.md && rm Install-Windows-Guide.md
    ```

## Version 2
- This version added the following listed .
    - This version is to old to support the version changelog.
    ```
    git clone https://github.com/HttpAnimation/Bondi.git && cd Bondi && git sparse-checkout init --cone && git sparse-checkout set V2 && rm README.md && rm Setup-Guide.md && rm Installation-Commands.md && rm Install-Windows-Guide.md
    ```

## Version 1
- This version added the following listed .
    - This version is to old to support the version changelog.
    ```
    git clone https://github.com/HttpAnimation/Bondi.git && cd Bondi && git sparse-checkout init --cone && git sparse-checkout set V1 && rm README.md && rm Setup-Guide.md && rm Installation-Commands.md && rm Install-Windows-Guide.md
    ```
