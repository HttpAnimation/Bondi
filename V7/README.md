Change log for Bondi V7:

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