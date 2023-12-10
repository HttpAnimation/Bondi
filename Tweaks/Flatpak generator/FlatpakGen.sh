#!/bin/bash

games_ini_path="Output/Games.ini"
if [ ! -e "$games_ini_path" ]; then
    echo "# Flatpak" > "$games_ini_path"
fi

cp "subsections.ini" "Output/subsections.ini"

flatpak_list_output=$(flatpak list)

prev_app_name=""
prev_run_command=""

while IFS= read -r line; do
    IFS=$'\t' read -ra columns <<< "$line"

    if [ ${#columns[@]} -ge 4 ] && [ -n "${columns[2]}" ]; then
        app_name="${columns[0]}"
        flatpak_name="${columns[1]}"
        run_command="${columns[2]}"

        IFS='.' read -ra version_parts <<< "$flatpak_name"
        version_number="${version_parts[-1]}"

        command_str="Flatpak | $app_name | flatpak run $flatpak_name | $version_number"

        if [ "$app_name" != "$prev_app_name" ] || [ "$run_command" != "$prev_run_command" ]; then
            echo "" >> "$games_ini_path"
        fi

        echo "$command_str" >> "$games_ini_path"

        prev_app_name="$app_name"
        prev_run_command="$run_command"
    fi
done <<< "$flatpak_list_output"

echo "Commands have been written to Games.ini"
