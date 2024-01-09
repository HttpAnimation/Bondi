#!/bin/bash

# Download Repo.json
wget https://github.com/HttpAnimation/Bondi/raw/main/Bondi-Installer/Repo/Repo.json

# Parse JSON data and extract required fields
versions=$(jq -r '.[].Name' Repo.json)
commands=$(jq -r '.[].Install-Command' Repo.json)

# Function to check if a folder exists
folder_exists() {
  if [ -d "$1" ]; then
    return 0
  else
    return 1
  fi
}

# Function to install a version
install_version() {
  version_folder="$1"
  install_command="$2"
  
  # Check if version folder already exists
  if folder_exists "$version_folder"; then
    zenity --error --text="Version $version_folder is already installed."
  else
    # Execute install command
    bash -c "$install_command"
    zenity --info --text="Version $version_folder installed successfully."
  fi
}

# Function to uninstall a version
uninstall_version() {
  version_folder="$1"
  
  # Check if version folder exists
  if folder_exists "$version_folder"; then
    rm -rf "$version_folder" # Remove the version folder
    zenity --info --text="Version $version_folder uninstalled successfully."
  else
    zenity --error --text="Version $version_folder is not installed."
  fi
}

# Function to run Bondi
run_bondi() {
  version_folder="$1"
  
  # Check if version folder exists
  if folder_exists "$version_folder"; then
    cd "$version_folder"
    java Bondi
  else
    zenity --error --text="Version $version_folder is not installed."
  fi
}

# Function to compile Bondi.java
compile_bondi() {
  version_folder="$1"
  
  # Check if version folder exists
  if folder_exists "$version_folder"; then
    cd "$version_folder"
    javac Bondi.java
    zenity --info --text="Bondi.java compiled successfully."
  else
    zenity --error --text="Version $version_folder is not installed."
  fi
}

# Display Zenity UI
selected_version=$(zenity --list --title="Bondi Installer" --text="Select a version:" --column="Version" "${versions[@]}")

case $selected_version in
  "") # No version selected
    zenity --error --text="No version selected."
    ;;
  *)
    selected_command=$(jq -r --arg version "$selected_version" '.[] | select(.Name==$version) | .["Install-Command"]' Repo.json)
    
    # Check if version is already installed
    if folder_exists "$selected_version"; then
      action=$(zenity --list --title="Bondi Installer" --text="Version $selected_version is installed." \
                  --column="Action" "Uninstall" "Run" "Compile")
      case $action in
        "Uninstall")
          uninstall_version "$selected_version"
          ;;
        "Run")
          run_bondi "$selected_version"
          ;;
        "Compile")
          compile_bondi "$selected_version"
          ;;
      esac
    else
      install_version "$selected_version" "$selected_command"
    fi
esac