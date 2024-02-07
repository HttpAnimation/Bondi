#!/bin/bash

# Check the output of `uname` command
OS=$(uname)

# Check if the OS is macOS
if [[ "$OS" == "Darwin" ]]; then
    echo "This is macOS."
# Check if the OS is Unix/Linux
elif [[ "$OS" == "Linux" || "$OS" == "GNU" ]]; then
    echo "This is Unix/Linux."
else
    echo "Unknown operating system."
fi
