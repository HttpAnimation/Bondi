echo "Bondi installer"
echo "Last updated | Sun\4\Feb"
echo ""
echo ""
echo ""
echo ""

# Git download
echo "Downloading main files"
git clone -b stable https://github.com/HttpAnimation/Bondi.git 
echo "Done downloading main files"

# CD
echo "Entering the dir"
cd Bondi
echo "Done"

# Remove files
echo "Removeing files that don't get used."
echo "Removing README.md"
rm README.md
echo "Done"
echo "Removing Data.md"
rm Data.md
echo "Done"
echo "Removing Config/README.md"
rm Config/README.md
echo "Done"
echo "Removing remove_comments.py"
rm remove_comments.py
echo "Done"

# Pips
echo "Downloading pips"
echo "Downloading tk"
pip install tk
echo "Done"
echo "Downloading pygame"
pip install pygame
echo "Done"

# Done
echo "Run | ./run"
echo "Install script it now done now removing good bye mate."
rm install.sh
