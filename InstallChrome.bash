#!/bin/bash

OS=$(uname)
if [[ "$OS" == "Darwin" ]]; then
    echo "This is macOS."
elif [[ "$OS" == "Linux" || "$OS" == "GNU" ]]; then
    echo "Running on unix/Linux."
    echo "Downloading chromedriver for Linux"
    wget https://chromedriver.storage.googleapis.com/114.0.5735.90/chromedriver_linux64.zip
    echo "Unziping chromedriver_linux64.zip"
    unzip chromedriver_linux64.zip
    echp "Done unziping"
    echo "Removing the old zip file"
    rm chromedriver_linux64.zip
    echo "Done removing"
    echo "Done installing chomedriver"
else
    echo "Unknown operating system."
fi
