#!/bin/bash

OS=$(uname)
if [[ "$OS" == "Darwin" ]]; then
    echo "This is macOS."
elif [[ "$OS" == "Linux" || "$OS" == "GNU" ]]; then
    echo "Running on unix/Linux."
else
    echo "Unknown operating system."
fi
