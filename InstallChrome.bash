#!/bin/bash

OS=$(uname)
if [[ "$OS" == "Darwin" ]]; then
    echo "This is macOS."
elif [[ "$OS" == "Linux" || "$OS" == "GNU" ]]; then
    echo "Running on unix/Linux."
    echo "Downloading chromedriver for Linux"
    wget https://chromedriver.storage.googleapis.com/114.0.5735.90/chromedriver_linux64.zip
else
    echo "Unknown operating system."
fi
