echo "Downloading java files"
wget https://raw.githubusercontent.com/HttpAnimation/Bondi/main/V8/Bondi.java
mkdir Configs
cd Configs
wget https://github.com/HttpAnimation/Bondi/raw/main/V8/Config/subsections.ini
wget https://github.com/HttpAnimation/Bondi/raw/main/V8/Config/Update.ini
wget https://github.com/HttpAnimation/Bondi/raw/main/V8/Config/SidebarWidth.ini
wget https://github.com/HttpAnimation/Bondi/raw/main/V8/Config/Lightmode.ini
wget https://github.com/HttpAnimation/Bondi/raw/main/V8/Config/Games.ini
cd ../
mkdir "Config EXP'S"
cd "Config EXP'S"
wget "https://github.com/HttpAnimation/Bondi/raw/main/V8/Config%20EXP'S/subsections.ini"
wget "https://github.com/HttpAnimation/Bondi/raw/main/V8/Config%20EXP'S/Games.ini"
cd ../
echo "Downloading Build.sh"
wget https://raw.githubusercontent.com/HttpAnimation/Bondi/main/More/Build.sh
echo "Down downloading Build.sh" 
echo "Downloading run.sh"
wget https://raw.githubusercontent.com/HttpAnimation/Bondi/main/More/Run.sh
echo "Down downloading run.sh"
echo "Allowng Build.sh to run"
chmod +x Build.sh
echo "Allowing Run.sh to run"
chmod +x Run.sh
./Build.sh
echo "Done Installing"
rm Install.sh
