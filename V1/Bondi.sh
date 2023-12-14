#!/bin/bash
steam_dir="$HOME/.steam"
if [ -f "Config/Steam-Path.inf" ]; then
  steam_dir=$(cat "Config/Steam-Path.inf")
fi
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
if [ "$1" == "-h" ]; then
  show_help
  exit 0
fi

if [ "$1" == "-SP" ]; then
  show_steampath
  exit 0
fi
games=$(find "$steam_dir/steamapps/common" -maxdepth 1 -type d -exec basename {} \; | sort)
selected_game=$(zenity --list \
  --title "Select a Steam game to play" \
  --column "Game" $games \
  --width=1000 --height=500)
if [ -n "$selected_game" ]; then
  game_executable="$steam_dir/steamapps/common/$selected_game/$selected_game.sh"
  if [ -f "$game_executable" ]; then
    chmod +x "$game_executable" 
    "$game_executable"
  else
    zenity --error --text "Game executable not found for $selected_game."
  fi
fi
