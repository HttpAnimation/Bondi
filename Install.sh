#!/bin/bash

# Check if the system is macOS
if [ "$(uname)" == "Darwin" ]; then
  # Check if Homebrew is installed
  if ! command -v brew &> /dev/null; then
    echo "Homebrew is not installed. Installing Homebrew..."
    /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
  fi
  
  # Install Zenity using Homebrew
  if ! command -v zenity &> /dev/null; then
    echo "Zenity is not installed. Installing Zenity..."
    brew install zenity
  fi
fi

# Clone the Bondi repository
git clone https://github.com/HttpAnimation/Bondi.git
cd Bondi

# Remove README.md (if it exists)
if [ -f README.md ]; then
  rm README.md
fi

# Make Bondi.sh executable
chmod +x Bondi.sh

# Run Bondi.sh
./Bondi.sh
