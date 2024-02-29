#!/bin/bash

# Define the GitHub repository URL
repo_url="https://github.com/HttpAnimation/Bondi/tree/Downloads"

# Get the HTML content of the repository page
html_content=$(curl -s "$repo_url")

# Extract the version numbers from the HTML content
versions=($(echo "$html_content" | grep -oP 'V\d+' | sort -V))

# Get the newest version
newest_version="${versions[-1]}"

# Navigate into the directory of the newest version
newest_version_url="$repo_url/$newest_version"
versions_folder_url="${newest_version_url/V/versions}"
html_content=$(curl -s "$versions_folder_url")

# Extract the filename containing "bondi" in its name
filename=$(echo "$html_content" | grep -oP 'href="\K[^"]+bondi[^"]+')

# Download the file
if [[ -n "$filename" ]]; then
    curl -O "$versions_folder_url/$filename"
    echo "Downloaded $filename"
else
    echo "Error: Unable to find a file containing 'bondi' in its name."
fi
