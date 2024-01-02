# [Yuzu](https://yuzu-emu.org/) generator
The **[Yuzu](https://yuzu-emu.org/) generator** will grab the list of you're [Nintendo Switch](https://www.nintendo.com/us/switch/) roms then make a Games.ini file for them with use with bondi this is for use with the flatpak version of [Yuzu](https://yuzu-emu.org/).

## Emualtor
The emualtor used for this tweak is [Yuzu](https://yuzu-emu.org/) witch can be downloaded [here](https://flathub.org/apps/org.yuzu_emu.yuzu) or by running the listed command below.
```
flatpak install flathub org.yuzu_emu.yuzu
```

## Installing
Open a terminal and run the command listed below.

```
mkdir Yuzu\ generator && cd Yuzu\ generator && wget https://github.com/HttpAnimation/Bondi/raw/main/Tweaks/Yuzu%20generator/YuzuGenerator.sh && wget https://github.com/HttpAnimation/Bondi/raw/main/RyujinxGenExtra/subsections.ini && echo "Games.ini will be made once the bash script is ran" && chmod +x YuzuGenerator.sh
```

## Running
In the same place where this tweak is insatlled run the following command. 
```
./YuzuGenerator.sh
```