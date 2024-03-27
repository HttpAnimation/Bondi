#!/bin/bash
clear

# Detect the operating system
if [[ "$(uname)" == "Darwin" ]]; then
    OS="macOS"
elif [[ "$(uname)" == "Linux" ]]; then
    OS="Linux"
else
    echo "Unsupported operating system."
    exit 1
fi

# Get current date and time
current_datetime=$(date +'%Y-%m-%d_%H-%M-%S')

# Create a folder with the current date and time
build_folder="$current_datetime"
mkdir -p "$build_folder"

# Compile c scripts into the build folder
if [[ "$OS" == "macOS" ]]; then
    clang -o "$build_folder/BondiMac" -framework Cocoa -framework Foundation BondiMac.c
elif [[ "$OS" == "Linux" ]]; then
    gcc -o "$build_folder/bondiLinux" bondiLinux.c `pkg-config --cflags --libs gtk+-3.0`
fi

# Copy files into the build folder
cp bondi*.c "$build_folder" # Assuming your source files start with bondi

# Create a Version.ini file with the current date and time
echo "$current_datetime" > "$build_folder/Version.ini"

# Create README file
readme_file="$build_folder/README.txt"
echo "Build created at: $current_datetime" > "$readme_file"
echo "This folder contains builds for the server and client programs." >> "$readme_file"
echo "This is an auto-generated message and might work or might not." >> "$readme_file"

# Print the path to the build folder
echo "Builds created at: $build_folder"
echo "You can also run it by typing this in:"
if [[ "$OS" == "macOS" ]]; then
    echo "./$build_folder/bondiMac"
elif [[ "$OS" == "Linux" ]]; then
    echo "./$build_folder/bondiLinux"
fi
