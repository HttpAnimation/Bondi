# Bondi Repo-Testing
### DO NOT USE THIS AS A MAIN BONDI INSTALL

This version of Bondi is made for one thing and one thing only testing out repos. 

## How it works
The java file reads the file **Config/Repos.ini** for a url with a json file and takes that data and makes the buttons form file a EXP can be found below
   ```json
   [
      {
         "subsections.ini": [
               "Apps",
               "Other Apps"
         ],

         "Games.ini": [
               "Apps | Firefox | firefox",
               "Apps | Discord | discord",
               "Other Apps | yuzu | org.yuzu_emu.yuzu",
               "Other Apps | Ryujinx | org.ryujinx.Ryujinx"
         ]
      }
   ]
   ```

## Planned date?
There is no real plan of date that this will come out but it should come out of beta and into in version nine.

## Installing
To install the beta open a terminal and run the following command
   ```
   mkdir Bondi && cd Bondi && mkdir Repo-Testing && cd Repo-Testing && mkdir Config && wget https://github.com/HttpAnimation/Bondi/raw/Repo-Testing/V8/Bondi.java && cd Config && wget https://github.com/HttpAnimation/Bondi/raw/Repo-Testing/V8/Config/Games.ini && wget https://github.com/HttpAnimation/Bondi/raw/Repo-Testing/V8/Config/Lightmode.ini && wget https://github.com/HttpAnimation/Bondi/raw/Repo-Testing/V8/Config/Repos.ini && wget https://github.com/HttpAnimation/Bondi/raw/Repo-Testing/V8/Config/SidebarWidth.ini && wget https://github.com/HttpAnimation/Bondi/raw/Repo-Testing/V8/Config/Update.ini && wget https://github.com/HttpAnimation/Bondi/raw/Repo-Testing/V8/Config/subsections.ini && cd ../ && javac Bondi.java
   ```
