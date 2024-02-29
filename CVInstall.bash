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
html_content=$(curl -s "$newest_version_url")

# Extract the filename
filename=$(echo "$html_content" | grep -oP 'href="\K[^"]+bondi[^"]+')

# Download the file
curl -O "$newest_version_url/$filename"

echo "Downloaded $filename"
