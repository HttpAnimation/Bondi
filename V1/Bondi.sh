#!/bin/bash

# Default Steam path
steam_dir="$HOME/.steam"

# Check if Steam path is configured in Config/Steam-Path.inf
if [ -f "Config/Steam-Path.inf" ]; then
  steam_dir=$(cat "Config/Steam-Path.inf")
fi

# Function to display help and open Help.html
show_steampath() {
  if [ -f "Config/Steam-Path.inf" ]; then
    xdg-open "Config/Steam-Path.inf" || zenity --error --text "Unable to open the inf file. Make sure you have the default application set for .inf files."
  else
    zenity --error --text "Steam-Path.inf not found. Make sure it is in the Config directory."
  fi
}

show_help() {
  if [ -f "Config/Advance/Help.html" ]; then
    xdg-open "Config/Advance/Help.html" || zenity --error --text "Unable to open Help.html. Please check your file and web browser settings. (Default browser only)"
  else
    zenity --error --text "Help.html not found in Config/Advance directory."
  fi
}

# Check for command-line arguments
if [ "$1" == "-h" ]; then
  show_help
  exit 0
fi

if [ "$1" == "-SP" ]; then
  show_steampath
  exit 0
fi

# Get a list of installed games from Steam, excluding the "common" directory
games=$(find "$steam_dir/steamapps/common" -maxdepth 1 -type d -exec basename {} \; | sort)

# Use Zenity to display a list of installed games
selected_game=$(zenity --list \
  --title "Select a Steam game to play" \
  --column "Game" $games \
  --width=1000 --height=500)

# Check if the user selected a game
if [ -n "$selected_game" ]; then
  # Launch the selected game using its executable
  game_executable="$steam_dir/steamapps/common/$selected_game/$selected_game.sh"  # Assuming the game's executable script has the same name as the game folder
  if [ -f "$game_executable" ]; then
    chmod +x "$game_executable"  # Make sure the script is executable
    "$game_executable"
  else
    zenity --error --text "Game executable not found for $selected_game."
  fi
fi