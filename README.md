# Bondi 
A custom Launcher for MacOS/Hackintosh and Linux/Unix.

- **Project Status:** V8 is coming out very soon I got my hands on the [Steam Deck](https://store.steampowered.com/steamdeck) and have been working on a ton of bugs that keep making Bondi not working now I will need a little bit more time before this update it rolled out to the masses in the meantime while am working you are free to message me [Discord](discord.com/) my username is httpanimations to receive a beta build.
![Bondi Screenshot](Photos/Screenshot%20from%202023-10-13%2019-50-41.png)

Bondi is a versatile custom launcher designed to enhance your MacOS, Hackintosh, Linux, or Unix experience, providing powerful features to streamline your workflow and improve your desktop environment.

## Files
- [Installation Commands.md](Installtion-Commands.md): Instructions for installing Bondi.
- [Runners.md](Runners.md): A list of premade buttons for apps/games.
- [Setup Guide.md](Setup-Guide.md): The setup guide.

## Installation

The install page has moved to [here](Installtion-Commands.md):

1. Copy the installation command from the [Installtion-Commands.md](Installtion-Commands.md) file.
2. Paste it into your terminal.
3. Press Enter to execute the command.
4. Bondi will be downloaded and installed on your system.

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
