#!/bin/bash

# Ask for the directory of the ROMs
read -p "Enter the directory of the ROMs: " rom_directory

# Check if the directory exists
if [ ! -d "$rom_directory" ]; then
  echo "Error: The specified directory does not exist."
  exit 1
fi

# Create Games.ini file
echo "# Switch" > Games.ini

# Iterate through each ROM in the directory
for rom_file in "$rom_directory"/*.nsp "$rom_directory"/*.xci; do
  # Check if the file is a regular file (not a directory)
  if [ -f "$rom_file" ]; then
    # Get the filename without the directory path and extension
    filename=$(basename -- "$rom_file")
    filename_no_ext="${filename%.*}"

    # Add entry to Games.ini
    echo "Switch | $filename_no_ext | flatpak run org.ryujinx.Ryujinx \"$rom_file\"" >> Games.ini
  fi
done

echo "The files subsections.ini and Games.ini have been created and downloaded successfully."
