#!/bin/bash
current_dir=$(pwd)
random_dir=$(mktemp -d "$current_dir/tmp.XXXXXX")
cd "$random_dir" || exit
wget https://raw.githubusercontent.com/HttpAnimation/Bondi/stable/BondiWeb.py
wget https://raw.githubusercontent.com/HttpAnimation/Bondi/stable/InstallChrome.bash
cd "$current_dir" || exit
