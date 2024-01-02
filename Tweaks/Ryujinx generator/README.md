# [Ryujinx](https://ryujinx.org/) generator
The **[Ryujinx](https://ryujinx.org/) generator** will grab the list of you're [Nintendo Switch](https://www.nintendo.com/us/switch/) roms then make a Games.ini file for them with use with bondi this is for use with the flatpak version of [Ryujinx](https://ryujinx.org/).

## Emualtor
The emualtor used for this tweak is [Ryujinx](https://ryujinx.org/) witch can be downloaded [here](https://flathub.org/apps/org.ryujinx.Ryujinx) or by running the listed command below.
```
flatpak install flathub org.ryujinx.Ryujinx
```

## Installing
Open a terminal and run the command listed below.


```
mkdir Yuzu\ generator && cd Ryujinx\ generator && wget https://github.com/HttpAnimation/Bondi/raw/main/Tweaks/Ryujinx%20generator/RyujinxGenerator.sh && wget https://github.com/HttpAnimation/Bondi/raw/main/RyujinxGenExtra/subsections.ini && echo "Games.ini will be made once the bash script is ran" && chmod +x RyujinxGenerator.sh
```

## Running
In the same place where this tweak is insatlled run the following command. 
```
./RyujinxGenerator.sh
```