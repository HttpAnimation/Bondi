# Bondi 
An custom Launcher for MacOS/Hackintosh and Linux/Unix.

- **Project Status:** This project is no longer on hold as I was able to get my hands on a [Steam Deck](https://store.steampowered.com/steamdeck). **V8** will be released once it arrive's in Ireland and I get my hands on it, and I complete testing and work on the update. Feel free to message me on [Discord](https://discord.com/app) **httpanimations** to get a pre-release build.

![Bondi Screenshot](Photos/Screenshot%20from%202023-10-13%2019-50-41.png)

Bondi is a versatile custom launcher designed to enhance your MacOS, Hackintosh, Linux, or Unix experience, providing powerful features to streamline your workflow and improve your desktop environment.

## Files
- [Installation Commands.md](Installtion-Commands.md): Instructions for installing Bondi.
- [Runners.md](Runners.md): A list of premade buttons for apps/games.
- [Setup Guide.md](Setup-Guide.md): The setup guide.

## Installation

The install page has moved to [here](Installation-Commands.md):

1. Copy the installation command from the [Installtion-Commands.md](Installation-Commands.md) file.
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
This will guide will show you how to add Bondi steam
1) Have Bondi downloaded first 
2) Download the steam art with this script.
  ```
  wget https://github.com/HttpAnimation/Bondi/edit/main/Steam%20Art/Download.sh && chmod +x Download.sh && ./Download.sh
  ```
3) Go to steam and click Add a game then add a non-steam game.
![Add a Game](Photos/Screenshot_20231208_121822.png)
4) Add the **Bondi.java** file into steam.
![Adding the file](Photos/Screenshot_20231208_122025.png)
![The file in Steam](Photos/Screenshot_20231208_122110.png)
5) Go to the settings on that steam game and add **java** to the start.
![The game in settings](Photos/Screenshot_20231208_122425.png)

6) Add the steam art
## Plans

1. ~~A better UI (Work in Progress) - [Done]~~
2. ~~Simple ROM importer (Not until the first is done and everything is working right) [Not now]~~
3. Controller support.
4. ~~Fullscreen support.~~
5. Light mode and Dark mode options
6. Have the UI be held in html and then display that page on the Bondi window.
7. Compile into a .deb and [Flatpak](https://flatpak.org/)
8. ~~Updater~~
9. Auto updater when you click update.
10. Server host for **Games.ini** and **subsections.ini**.
## Support

If you encounter any issues or have questions, please open an issue on the [GitHub repository](https://github.com/HttpAnimation/Bondi/issues). We appreciate your feedback and will do our best to assist you.

Thank you for choosing Bondi as your custom launcher. We hope it enhances your computing experience!

## IOS & Android

Andriod has not been tested but a java simualtor can most likly be found and for IOS you can find a IPA either on the app store or sideloaded with [TrollStore](https://github.com/opa334/TrollStore).