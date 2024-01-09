#!/bin/bash

json_url="https://github.com/HttpAnimation/Bondi/raw/main/Bondi-Installer/Repo/Repo.json"
temp_file=$(mktemp)

# Download JSON data
curl -sL "$json_url" > "$temp_file"

# Parse JSON data
versions=($(jq -r '.[].Version' "$temp_file"))
names=($(jq -r '.[].Name' "$temp_file"))
commands=($(jq -r '.[].Install-Command' "$temp_file"))

# Function to check if a version folder exists
version_installed() {
    [ -d "$1" ]
}

# Function to install or uninstall based on the folder existence
install_or_uninstall() {
    if version_installed "$1"; then
        rm -rf "$1"
        zenity --info --text="Uninstalled $1"
    else
        mkdir "$1" && cd "$1" && eval "$2"
        zenity --info --text="Installed $1"
    fi
}

# Function to run java Bondi in the specified folder
run_bondi() {
    if version_installed "$1"; then
        cd "$1" && java Bondi
    else
        zenity --error --text="Version $1 is not installed."
    fi
}

# Function to compile Bondi.java in the specified folder
compile_bondi() {
    if version_installed "$1"; then
        cd "$1" && javac Bondi.java
    else
        zenity --error --text="Version $1 is not installed."
    fi
}

# Create buttons for each version
selection=$(zenity --list --title="Bondi Installer" --text="Select Version" --column="Version" "${names[@]}")

# Find the index of the selected version
selected_index=-1
for i in "${!names[@]}"; do
    if [ "${names[i]}" == "$selection" ]; then
        selected_index=$i
        break
    fi
done

# Display appropriate buttons based on version existence
if [ $selected_index -ne -1 ]; then
    selected_version="${versions[selected_index]}"
    selected_command="${commands[selected_index]}"
    
    if version_installed "$selected_version"; then
        zenity --question --text="Version $selected_version is installed. Do you want to uninstall?"
        if [ $? -eq 0 ]; then
            install_or_uninstall "$selected_version" "$selected_command"
        else
            run_bondi "$selected_version"
            compile_bondi "$selected_version"
        fi
    else
        install_or_uninstall "$selected_version" "$selected_command"
    fi
fi

# Clean up temp file
rm -f "$temp_file"
