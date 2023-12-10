#!/bin/bash

# Get the directory of the script
script_dir=$(dirname "$(readlink -f "$0")")

# Path to the source.ini file
source_ini="$script_dir/source.ini"

# Check if source.ini exists
if [ ! -f "$source_ini" ]; then
    echo "source.ini not found in the script directory. Exiting."
    exit 1
fi

# Prompt the user for the file path or read from a file
if [ "$1" == "-r" ]; then
    path_file="$script_dir/TestingPath.ini"
    if [ ! -f "$path_file" ]; then
        echo "TestingPath.ini not found in the script directory. Exiting."
        exit 1
    fi
    read -r file_path < "$path_file"
else
    read -p "Enter the file path: " file_path
fi

# Check if the path is valid
if [ ! -d "$file_path/SteamLibrary/steamapps/common" ]; then
    echo "Invalid path. Exiting."
    exit 1
fi

# Go to the common folder
cd "$file_path/SteamLibrary/steamapps/common" || exit 1

# Initialize the output file
output_file="$script_dir/output/Games.ini"

# Process the folders
for folder in *; do
    if [ -d "$folder" ]; then
        # Extract data from source.ini for the matching line
        source_line=$(grep -E "^$folder" "$source_ini")
        if [ -n "$source_line" ]; then
            new_name=$(echo "$source_line" | cut -d '|' -f 2 | tr -d '[:space:]')
            rungameid=$(echo "$source_line" | cut -d '|' -f 3 | tr -d '[:space:]')

            # Print debugging information
            echo "Processing folder: $folder"
            echo "New Name: $new_name"
            echo "RunGameID: $rungameid"

            # Append to Games.ini
            echo "Steam | $new_name | $rungameid" >> "$output_file"
            echo "----------------------------------------"
        else
            echo "No matching entry found in source.ini for folder: $folder"
            echo "----------------------------------------"
        fi
    fi
done

echo "Games.ini generated at $output_file"
