# Flatpak generator

This tool allows you to effortlessly create a `Games.ini` file for launching any of your installed applications or games from Flatpak on Linux. It simplifies the process of generating this configuration file by utilizing the `flatpak list` command.

## Install
To install this tweak open a terminal and run this command to install
```bash
mkdir Flatpak\ generator && cd Flatpak\ generator && wget https://raw.githubusercontent.com/HttpAnimation/Bondi/main/Tweaks/Flatpak%20generator/Games.ini && wget https://raw.githubusercontent.com/HttpAnimation/Bondi/main/Tweaks/Flatpak%20generator/subsections.ini && wget https://raw.githubusercontent.com/HttpAnimation/Bondi/main/Tweaks/Flatpak%20generator/FlatpakGen.sh && mkdir Output
```

## Working
This script is made for versions of Bondi using the **.java** language of the old **.sh** versions are not gonna work.

## Usage

To generate your `Games.ini` file, follow these simple steps:

1. Ensure you have Flatpak installed on your system.
2. Run the following command:

```bash
bash FlatpakGen.sh
```

3. Sit back and watch as the tool scans your Flatpak-installed applications and games.

4. Voilà! Your `Games.ini` file is now ready to use.

## Note

Please note that this tool is exclusively designed for Linux systems and requires the presence of Flatpak on your machine. It does not include any additional features beyond creating the `Games.ini` file also the `Games.ini` file is not made to be stand-alone and should be added to a `Games.ini`.

Feel free to use and share this tool with fellow Linux gamers!
