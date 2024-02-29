#!/bin/bash

# GitHub repository owner and name
owner="HttpAnimation"
repo="Bondi"

# Retrieve the latest release version using GitHub API
latest_release=$(curl -sL "https://api.github.com/repos/$owner/$repo/releases/latest" | grep -o '"tag_name": "[^"]*' | sed 's/"tag_name": "//')

# Check if the latest_release variable is empty
if [ -z "$latest_release" ]; then
    echo "Failed to retrieve the latest release version."
    exit 1
fi

# Form the download URL for the bondi file
download_url="https://github.com/$owner/$repo/releases/download/$latest_release/bondi"

# Download the bondi file
echo "Downloading bondi file from version $latest_release..."
wget "$download_url" -O bondi

# Check if the download was successful
if [ $? -eq 0 ]; then
    echo "bondi file downloaded successfully."
else
    echo "Failed to download bondi file."
fi
