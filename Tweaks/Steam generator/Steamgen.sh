#!/bin/bash

# Prompt the user for the file path
read -p "Enter the file path: " folder_path

# Check if the folder exists
if [ ! -d "$folder_path/SteamLibrary/steamapps/common" ]; then
  echo "Error: Folder does not exist."
  exit 1
fi

# Function to fetch source.ini from the provided URL
fetch_source_ini() {
  local url="https://raw.githubusercontent.com/HttpAnimation/Bondi/main/Tweaks/Steam%20generator/source.ini"
  curl -s "$url" || { echo "Error fetching $url"; exit 1; }
}

# Initialize the output file
output_file="output/Games.ini"
echo -e "Steam | new name | steam://rungameid/\n" > "$output_file"

# Iterate through each folder
for folder in */; do
  folder_name="${folder%/}"

  # Print the current folder being processed
  echo "Processing $folder_name..."

  # Fetch source.ini from the URL
  source_ini=$(fetch_source_ini)

  # Check if source.ini file exists
  if [ -n "$source_ini" ]; then
    # Read values from source.ini
    name=$(awk -F'|' '$1=="Name"{print $2}' <<< "$source_ini" | tr -d '[:space:]')
    new_name=$(awk -F'|' '$1=="new name"{print $2}' <<< "$source_ini" | tr -d '[:space:]')
    game_id=$(awk -F'|' '$1=="steam://rungameid/"{print $2}' <<< "$source_ini" | tr -d '[:space:]')

    # Print debugging information
    echo "Name: $name"
    echo "New Name: $new_name"
    echo "Game ID: $game_id"

    # Append to the output file
    echo -e "$name | $new_name | $game_id" >> "$output_file"
  else
    echo "Error: Unable to fetch source.ini from the URL."
    exit 1
  fi

  echo "-------------------------------------"
done

echo "Processing completed. Check $output_file for the result."