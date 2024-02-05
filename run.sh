#!/bin/bash

choice=$(zenity --list --title="Choose Script" --column="Script" "Run Bondi" "Run Json editor" --width=300 --height=400)

if [ -n "$choice" ]; then
    case "$choice" in
        "Run Bondi")
            python3 Bondi.py
            ;;
        "Run Json editor")
            python3 JsonEditorApp.py
            ;;
        *)
            zenity --error --text="Invalid selection: $choice"
            ;;
    esac
else
    zenity --info --text="Script execution canceled."
fi
