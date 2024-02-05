
* Bondi
    - Config
        * Games.ini
        * subsections.ini
    - Bondi.py

## How a Games.ini file works
1) Catagory

    The Catagory is the 2nd thing then a then | to say that parts over for exp one might be Games

2) Name
    
    The name is the first thing then | to say that parts over exp Minecraft

3) Run command

    The run command is the last thing and thats the command to run when the button is clicked a exp might be
    ```bash
    firefox https://www.minecraft.net/en-us
    ```
4) A full part might be the following
    
    ```bash
    Games | Minecraft | firefox https://www.minecraft.net/en-us
    ```

## How a subsections.ini files works
This file just holds the Catagory's on where the buttons will go a file may look as the following.
    
    ```
    Games
    Websites
    Apps
    ```

## How the Bondi.py script will work
1) have a sidebar and be in darkmode while in full screen have it use **tk** and **pygame** 

2) reads the subsections.ini file for each catagory and put each one on the sidebar

3) When you click a button on the sidebar it will load the games for it from from Games.ini

4) When you a games is active on the main part of window make a button for each thing from Games.ini for that catagory have the buttons that get display the name then when you click it will run that command

5) Have buttons go left to right and if they are about to go off screen it will go to the next line

6) Have all the UI scale to the screen size 