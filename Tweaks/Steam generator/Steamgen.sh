#!/bin/bash

script_dir=$(dirname "$(readlink -f "$0")")
source_ini="$script_dir/source.ini"
if [ "$1" == "-KS" ]; then
    echo "Keeping the existing source.ini file."
    echo "Note: This file will not be updated."
else
    curl -sSL https://raw.githubusercontent.com/HttpAnimation/Bondi/main/Tweaks/Steam%20generator/source.ini -o "$source_ini"

    if [ ! -f "$source_ini" ]; then
        echo "source.ini not found in the script directory. Exiting."
        exit 1
    fi
fi
if [ "$1" == "-r" ]; then
    path_file="$script_dir/TestingPath.ini"
    if [ ! -f "$path_file" ]; then
        echo "TestingPath.ini not found in the script directory. Exiting."
        exit 1
    fi
    read -r file_path < "$path_file"
else
    read -p "Enter the folder path of where the SteamLibrary is stored: " file_path
fi
if [ ! -d "$file_path/SteamLibrary/steamapps/common" ]; then
    echo "Invalid path. Exiting."
    exit 1
fi
cd "$file_path/SteamLibrary/steamapps/common" || exit 1
output_file="$script_dir/output/Games.ini"
while IFS= read -r folder; do
    source_line=$(grep -E "^$folder" "$source_ini")
    if [ -n "$source_line" ]; then
        new_name=$(echo "$source_line" | awk -F'|' '{gsub(/^[ \t]+|[ \t]+$/, "", $2); print $2}')
        rungameid=$(echo "$source_line" | awk -F'|' '{gsub(/^[ \t]+|[ \t]+$/, "", $3); print $3}')
        echo "Processing folder: $folder"
        echo "New Name: $new_name"
        echo "RunGameID: $rungameid"

        echo "Steam | $new_name | $rungameid" >> "$output_file"
        echo "----------------------------------------"
    else
        echo "No matching entry found in source.ini for folder: $folder"
        echo "----------------------------------------"
    fi
done < <(ls -1)
if [ "$1" != "-KS" ]; then
    rm "$source_ini"
fi

echo "Games.ini generated at $output_file"
echo "If a game was not found and made in the Games.ini file submit a new one by opening a issue. You could also make a edit to the source.ini file on the Github to donate the games data."