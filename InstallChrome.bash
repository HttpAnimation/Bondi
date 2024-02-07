#!/bin/bash

OS=$(uname)
if [[ "$OS" == "Darwin" ]]; then
    echo "This is macOS."
elif [[ "$OS" == "Linux" || "$OS" == "GNU" ]]; then
    echo "This is Unix/Linux."
else
    echo "Unknown operating system."
fi
