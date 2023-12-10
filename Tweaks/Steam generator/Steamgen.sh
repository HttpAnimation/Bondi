#!/bin/bash

script_dir=$(dirname "$(readlink -f "$0")")
source_ini="$script_dir/source.ini"

curl -sSL https://raw.githubusercontent.com/HttpAnimation/Bondi/main/Tweaks/Steam%20generator/source.ini -o "$source_ini"

if [ ! -f "$source_ini" ]; then
    echo "source.ini not found in the script directory. Exiting."
    exit 1
fi

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

if [ ! -d "$file_path/SteamLibrary/steamapps/common" ]; then
    echo "Invalid path. Exiting."
    exit 1
fi

cd "$file_path/SteamLibrary/steamapps/common" || exit 1

output_file="$script_dir/output/Games.ini"

for folder in *; do
    if [ -d "$folder" ]; then
        source_line=$(grep -E "^$folder" "$source_ini")
        if [ -n "$source_line" ]; then
            new_name=$(echo "$source_line" | cut -d '|' -f 2 | tr -d '[:space:]')
            rungameid=$(echo "$source_line" | cut -d '|' -f 3 | tr -d '[:space:]')

            echo "Processing folder: $folder"
            echo "New Name: $new_name"
            echo "RunGameID: $rungameid"

            echo "Steam | $new_name | $rungameid" >> "$output_file"
            echo "----------------------------------------"
        else
            echo "No matching entry found in source.ini for folder: $folder"
            echo "----------------------------------------"
        fi
    fi
done

rm "$source_ini"

echo "Games.ini generated at $output_file"
