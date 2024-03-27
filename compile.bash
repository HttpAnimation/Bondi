gcc -o bondi bondi.c `pkg-config --cflags --libs gtk+-3.0`

#!/bin/bash
clear

# Get current date and time
current_datetime=$(date +'%Y-%m-%d_%H-%M-%S')

# Create a folder with the current date and time
build_folder="$current_datetime"
mkdir -p "$build_folder"

# Compile c scripts into the build folder
# gcc -o "$build_folder/openGLTest" openGLTest.c -lglfw -lGL -I/usr/include
gcc -o "$build_folder/sdl_example" sdl_example.c -lSDL2 -I/usr/x86_64-w64-mingw32/sys-root/mingw/include/SDL2
gcc CView.c -o "$build_folder/CView" -I/usr/include/SDL2 -L/usr/lib64 -lSDL2 -lSDL2_image -lSDL2_ttf

# Copy files into the build folder
cp openGLTest.c "$build_folder"

# Create a Version.ini file with the current date and time
echo "$current_datetime" > "$build_folder/Version.ini"

# Create README file
readme_file="$build_folder/README.txt"
echo "Build created at: $current_datetime" > "$readme_file"
echo "This folder contains builds for the server and client programs." >> "$readme_file"
echo "This is an auto-generated message and might work or might not." >> "$readme_file"

# Print the path to the build folder
echo "Builds created at: $build_folder"
echo "You can also run it by typing this in:"
echo "./$build_folder/bondi"