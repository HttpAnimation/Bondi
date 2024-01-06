#!/bin/bash

# Read configuration from Config/Repo.ini
config_file="Config/Repo.ini"
url=$(awk -F '=' '/^Url/ {print $2}' "$config_file")
json=$(curl -s "$url")

# Parse JSON data
version=$(echo "$json" | jq -r '.[0].Version')
sub_folder=$(echo "$json" | jq -r '.[0]."Sub-Folder"')
github_page=$(echo "$json" | jq -r '.[0]."Github-Page"')
install_command=$(echo "$json" | jq -r '.[0]."InstallCommand"')
legacy=$(echo "$json" | jq -r '.[0].Legacy')

# Check if the version is installed
install_dir="Bondi/$sub_folder"
installed=false
if [ -d "$install_dir" ]; then
    installed=true
fi

# Define Zenity options
zenity_options=(
    --title="Bondi Version: $version"
    --text="Bondi Version: $version\nLegacy: $legacy"
)

# Display Zenity dialog with appropriate buttons
if [ "$installed" = true ]; then
    choice=$(zenity "${zenity_options[@]}" --width=300 --height=150 --list --column "" --column "" "Open GitHub Page" "Compile" "Run" "Remove")
else
    choice=$(zenity "${zenity_options[@]}" --width=300 --height=150 --list --column "" --column "" "Install" "Open GitHub Page")
fi

# Perform actions based on user choice
case $choice in
    "Install")
        # Create sub-folder and run InstallCommand
        mkdir -p "$install_dir"
        cd "$install_dir" || exit
        eval "$install_command"
        ;;
    "Remove")
        # Remove installed version
        rm -rf "$install_dir"
        zenity --info --title="Bondi" --text="Version $version has been removed."
        ;;
    "Open GitHub Page")
        # Open GitHub page in default web browser
        xdg-open "$github_page"
        ;;
    "Compile")
        # Compile Bondi.java
        cd "$install_dir" || exit
        javac Bondi.java
        zenity --info --title="Bondi" --text="Bondi.java has been compiled successfully."
        ;;
    "Run")
        # Run Bondi
        cd "$install_dir" || exit
        java Bondi
        ;;
    *)
        # User closed the dialog
        exit 0
        ;;
esac

exit 0
