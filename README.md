# Bondi 
A custom Launcher for MacOS/Hackintosh and Linux/Unix.

- **Project Status:** Am working on a guide for running Bondi on the deck :).

![Bondi Screenshot](Photos/Screenshot%20from%202023-10-13%2019-50-41.png)

Bondi is a versatile custom launcher designed to enhance your MacOS, Hackintosh, Linux, or Unix experience, providing powerful features to streamline your workflow and improve your desktop environment.

## Files
- [Installation Commands.md](Installtion-Commands.md): Instructions for installing Bondi.
- [Runners.md](Runners.md): A list of premade buttons for apps/games.
- [Setup Guide.md](Setup-Guide.md): The setup guide.

## Installation

The install page has moved to [here](Installtion-Commands.md):

1) Copy the installation command from the [Installtion-Commands.md](Installtion-Commands.md) file.
2) Paste it into your terminal.
3) Press Enter to execute the command.
4) Bondi will be downloaded and installed on your system.

Certainly! Here's an improved version of your Markdown file:

## Steamdeck Installation

To install Bondi on your Steamdeck, follow these steps in the terminal:

1. **Download JDK 21 from the Java website:**
   ```bash
   wget https://download.oracle.com/java/21/latest/jdk-21_linux-x64_bin.tar.gz
   ```

2. **Extract the JDK file:**
   ```bash
   tar -zxvf jdk-21_linux-x64_bin.tar.gz
   ```

3. **Download Bondi from [here](https://github.com/HttpAnimation/Bondi/releases).**

4. **Extract the Bondi file.**

5. **Ensure your directory structure matches the following (note: "V#" denotes a version number):**
   ```bash
   $:/ls
   -V#
   -jdk-21_linux-x64_bin
   -jdk-21_linux-x64_bin.tar.gz
   -V#.tar.gz
   ```

6. **Remove unnecessary tar.gz files:**
   ```bash
   rm jdk-21_linux-x64_bin.tar.gz V#.tar.gz
   ```

7. **Navigate to the Bondi directory:**
   ```bash
   cd V#
   ```

8. **Compile Bondi:**
   ```bash
   /path/to/jdk-21.0.1/bin/javac Bondi.java
   ```

9. **Run Bondi:**
   ```bash
   /path/to/jdk-21.0.1/bin/java Bondi
   ```

Make sure to replace `/path/to/` with the actual path where you extracted the JDK. Now you're ready to run Bondi on your Steamdeck!
## Documentation and Usage

To set up Bondi, head over to the setup [guide](Setup-Guide.md). For detailed information on using Bondi and its features, please refer to our [official documentation](https://httpanimation.github.io/Bondi/).

## Features

- **Open Source:** Everything can be changed to whatever you want, including the art.
- **Efficiency:** Streamline your workflow and improve productivity with Bondi's efficient launcher capabilities.
- **Cross-Platform:**
  1) Linux **Fully**
  2) MacOS/Hackintosh **Sort of** (read [this](More/MacOS-Hackintosh-More.md))

## Getting Started

Once you've installed Bondi, explore its features and customization options. Our documentation provides step-by-step instructions to help you get the most out of Bondi.

## Adding to steam
This guide will show you how to add Bondi steam
1) Have Bondi downloaded first 
2) Download the Steam art with this script.
  ```
  wget https://raw.githubusercontent.com/HttpAnimation/Bondi/main/Steam%20Art/Download.sh && chmod +x Download.sh && ./Download.sh
  ```
3) Go to Steam and click Add a game then add a non-steam game.
4) Add the **Bondi.java** file into steam.
5) Go to the settings on that Steam game and add **java** to the start.

6) Add the steam art

## Plans
The plans of Bondi can change all the time either because I just am not able to get stuff working or if I want to add something.

~~A better UI (Work in Progress)~~

~~Simple ROM importer (Not until the first is done and everything is working right) [Not now]~~

Controller support.

~~Fullscreen support.~~

Light mode and Dark mode options

Have the UI be held in HTML and then display that page on 

the Bondi window.

Compile into a .deb and [Flatpak](https://flatpak.org/)

~~Updater~~

Auto updater when you click update.

Server host for **Games.ini** and **subsections.ini**.

## Support

If you encounter any issues or have questions, please open an issue on the [GitHub repository](https://github.com/HttpAnimation/Bondi/issues). We appreciate your feedback and will do our best to assist you.

Thank you for choosing Bondi as your custom launcher. We hope it enhances your computing experience!

## Tweaks
Tweaks allow you to modify Bondi or auto-make the **Games.ini** and **subsections.ini** files you can view them by clicking [here](/Tweaks/README.md). 

## IOS & Android

Android has not been tested but a Java simulator can most likely be found on the Playstore. For IOS you can find an IPA either on the app store or sideloaded with [TrollStore](https://github.com/opa334/TrollStore).
