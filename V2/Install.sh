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

git clone https://github.com/HttpAnimation/Bondi.git
cd Bondi
rm README.md # Removes as it not needed
rm -r V1
rm You = gay?.sh
cd ../
rm Install.sh
echo "For MacOS users install zenity with brew if not already| brew install zenity"
cd Bondi
chmod +x Bondi.sh
./Bondi.sh