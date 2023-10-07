import subprocess
import os
import shutil

# Check if Games.ini exists, and create it if it doesn't
games_ini_path = "Output/Games.ini"
if not os.path.exists(games_ini_path):
    with open(games_ini_path, "w") as games_ini_file:
        games_ini_file.write("# Flatpak\n")

# Copy subsections.ini to the Output directory
shutil.copy("subsections.ini", "Output/subsections.ini")

# Run the 'flatpak list' command and capture its output
try:
    flatpak_list_output = subprocess.check_output(["flatpak", "list"], universal_newlines=True)
except subprocess.CalledProcessError as e:
    print(f"Error running 'flatpak list': {e}")
    exit(1)

# Initialize variables to store the previous app name and run command
prev_app_name = None
prev_run_command = None

# Append the commands to the Games.ini file
with open(games_ini_path, "a") as games_ini_file:
    for line in flatpak_list_output.splitlines():
        # Split the line into columns
        columns = line.split("\t")

        # Ensure there are at least 4 columns and that the run command is not empty
        if len(columns) >= 4 and columns[2]:
            app_name = columns[0]
            flatpak_name = columns[1]
            run_command = columns[2]

            # Extract the version number from flatpak_name
            version_parts = flatpak_name.split(".")
            version_number = version_parts[-1]

            # Generate the command string with version number at the end
            command_str = f"Flatpak | {app_name} | flatpak run {flatpak_name} | {version_number}"

            # If the app name or run command has changed, add a newline
            if app_name != prev_app_name or run_command != prev_run_command:
                games_ini_file.write("\n")

            # Append the command to the list, excluding the " | " after the last "|"
            games_ini_file.write(command_str + "\n")

            # Update the previous app name and run command
            prev_app_name = app_name
            prev_run_command = run_command

print("Commands have been written to Games.ini")
