#!/bin/bash
random_dir=$(mktemp -d)
cd "$random_dir" || exit
wget https://raw.githubusercontent.com/HttpAnimation/Bondi/stable/BondiWeb.py
wget https://raw.githubusercontent.com/HttpAnimation/Bondi/stable/InstallChrome.bash
