#!/bin/bash

# Function to display the game list for a category
show_game_list() {
  category=$1
  games=$(grep "^$category" Games.ini | awk -F '|' '{print $2}' | tr '\n' '\0')

  selected_game=$(zenity --list --title="Game Launcher - $category" --column="Games" $games --height=400 --width=300)

  if [ -n "$selected_game" ]; then
    command=$(grep "^$category | $selected_game" Games.ini | awk -F '|' '{print $3}')
    eval "$command"
  fi
}

# Read subsections from subsections.ini
categories=$(cat subsections.ini)

# Create an array of buttons
buttons=()
for category in $categories; do
  buttons+=(--button="$category" --default-button="$category")
done

# Show the category selection dialog with the default theme
choice=$(zenity --title="Game Launcher" --text="Select a category:" "${buttons[@]}" --modal --no-defaults)
happends
if [ $? -eq 0 ]; then
  selected_category=$(echo $categories | tr ' ' '\n' | sed -n "$choice"p)
  show_game_list "$selected_category"
fi
