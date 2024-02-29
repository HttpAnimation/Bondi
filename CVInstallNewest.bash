#!/bin/bash

# GitHub repository URL
repo_url="https://github.com/HttpAnimation/Bondi"

# Retrieve the latest release version
latest_release=$(curl -sL "$repo_url/releases/latest" | grep -o 'tag/[v.0-9]*"' | sed 's/tag\///' | sed 's/"//')

# Check if the latest_release variable is empty
if [ -z "$latest_release" ]; then
    echo "Failed to retrieve the latest release version."
    exit 1
fi

# Form the download URL for the bondi file
download_url="$repo_url/releases/download/$latest_release/bondi"

# Download the bondi file
echo "Downloading bondi file from version $latest_release..."
wget "$download_url" -O bondi

# Check if the download was successful
if [ $? -eq 0 ]; then
    echo "bondi file downloaded successfully."
else
    echo "Failed to download bondi file."
fi
