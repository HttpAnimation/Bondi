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

# Split the output into lines and process each line to generate the commands
commands = []
for line in flatpak_list_output.splitlines():
    # Split the line into columns
    columns = line.split("\t")

    # Ensure there are at least 4 columns and that the run command is not empty
    if len(columns) >= 4 and columns[2]:
        app_name = columns[0]
        flatpak_name = columns[1]
        run_command = columns[2]

        # Generate the command string
        command_str = f"Flatpak | {app_name} | flatpak run {flatpak_name} | {run_command}"

        # Append the command to the list
        commands.append(command_str)

# Append the commands to the Games.ini file
with open(games_ini_path, "a") as games_ini_file:
    for command in commands:
        games_ini_file.write(command + "\n")

print("Commands have been written to Games.ini")
