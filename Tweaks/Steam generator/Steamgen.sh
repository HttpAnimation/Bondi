#!/bin/bash

# Prompt the user for the file path
read -p "Enter the file path: " file_path

# Check if the path is valid
if [ ! -d "$file_path/SteamLibrary/steamapps/common" ]; then
    echo "Invalid path. Exiting."
    exit 1
fi

# Go to the common folder
cd "$file_path/SteamLibrary/steamapps/common" || exit 1

# Initialize the output file
output_file="output/Games.ini"
echo "" > "$output_file"

# Loop through each folder in the common directory
for folder in */; do
    # Check if source.ini exists in the folder
    source_file="${folder}source.ini"
    if [ -f "$source_file" ]; then
        # Extract data from source.ini
        name=$(awk -F "|" '/Name/ {print $2}' "$source_file" | tr -d '[:space:]')
        new_name=$(awk -F "|" '/new name/ {print $2}' "$source_file" | tr -d '[:space:]')
        rungameid=$(awk -F "|" '/steam:\/\/rungameid/ {print $2}' "$source_file" | tr -d '[:space:]')

        # Print debugging information
        echo "Processing folder: $folder"
        echo "Name: $name"
        echo "New Name: $new_name"
        echo "RunGameID: $rungameid"

        # Append to Games.ini
        echo "Steam | $new_name | $rungameid" >> "$output_file"
        echo "----------------------------------------"
    else
        echo "source.ini not found in $folder"
        echo "----------------------------------------"
    fi
done

echo "Games.ini generated at $output_file"
