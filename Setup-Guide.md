# Setup Guide
- [Back to Main](README.md)

## Games.ini
The **Games.ini** file contains crucial data for the main buttons that will be interpreted by [Bondi](https://github.com/HttpAnimation/Bondi).

## subsections.ini
The **subsections.ini** file, read by [Bondi](https://github.com/HttpAnimation/Bondi), generates sidebar buttons and holds your primary categories.

## [Nano](https://nano-editor.org/)
[Nano](https://nano-editor.org/) serves as an integrated development environment (IDE) present in most Unix distributions, including [MacOS](https://www.apple.com/macos), [Pop_OS!](https://pop.system76.com/), and [Arch Linux](https://archlinux.org/). If you prefer, you can replace [Nano](https://nano-editor.org/) with other IDEs like [Kate](https://kate-editor.org/) or [Gedit](https://gedit-technology.github.io/apps/gedit/).

### subsections.ini Configuration
To create a **subsections.ini** file, navigate to the terminal and use the following commands, assuming your [Bondi](https://github.com/HttpAnimation/Bondi) Java file is in the V## folder.

```bash
$Terminal://cd /media/code/bondi/V69/
```

Ensure you are in the correct directory by checking the file list:

```bash
$Terminal://ls 
Bondi.java, Games.ini, subsections.ini, Config\ EXPS
```

Next, create and open the **subsections.ini** file in the terminal:

```bash
nano subsections.ini
```

Inside the editor, define your categories. For example, to create a category for Flatpak apps/games, type:

```plaintext
Flatpaks
```

Save the file with **ctrl+s** and exit the editor with **ctrl+x**.

### Games.ini Configuration
To set up the **Games.ini** file, use the following commands in the terminal:

```bash
$Terminal://cd /media/code/bondi/V69/
```

Ensure you are in the correct directory:

```bash
$Terminal://ls 
Bondi.java, Games.ini, subsections.ini, Config\ EXPS
```

Create and open the **Games.ini** file:

```bash
nano Games.ini
```

Inside the editor, create a button, for example:

```plaintext
Flatpak | Minecraft | flatpak run flatpak.minecraft.net
```

Here, "Flatpak" represents the category, "Minecraft" is the game/app name, and the command "flatpak run flatpak.minecraft.net" runs when the button is clicked.

Save the file with **ctrl+s** and exit the editor with **ctrl+x**.