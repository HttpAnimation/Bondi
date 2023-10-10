# Setup-Guide
# [Back to README](README.md)

### This guide is for MacOS and Linux for windows use the text editor.


Games.ini is the file that will locate/make main buttons that will be launching your games/apps
subsections.ini is the file that will locate/make the sidebar buttons that will navigate to the buttons for Games.ini

# subsections.ini
To make a subsections.ini file open the terminal and cd into the same dir were your java file located
```shell
$Terminal://cd /media/code/bondi/V69/
```
Your ls will look like this if you are in the right dir
```shell
$Terminal://ls 
Bondi.java, Games.ini, subsections.ini, Config\ EXPS
```
Note that more files might be in there if Bondi gets a update

In the same terminal type
```shell
nano subsections.ini
```
once you type that a new text editer will open in your terminal this is the file will you make your categories for this lets use flatpak for flatpak apps/games
```shell
Flatpaks
```
now save the file with ctrl+s and exit the editor with ctrl+x

# Games.ini
To make a Games.ini file open the terminal and cd into the same dir were your java file located
```shell
$Terminal://cd /media/code/bondi/V69/
```
Your ls will look like this if you are in the right dir
```shell
$Terminal://ls 
Bondi.java, Games.ini, subsections.ini, Config\ EXPS
```
Note that more files might be in there if Bondi gets a update

In the same terminal type
```shell
nano Games.ini
```
A text editor will open in your terminal lets make a button
```shell
Flatpaks | Minecraft | flatpak run flatpak.minecraft.net
```
The frist thing Flatpaks | is the the category the button will be placed in and the | will end the segment Minecraft | is the game/app name that will show up a text button and | is to end the segment and last thing flatpak run flatpak.minecraft.net is the command that will get ran when the buttoon is clicked.

now save the file with ctrl+s and exit the editor with ctrl+x