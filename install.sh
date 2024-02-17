echo "Bondi installer"
echo "Lsat updated: Friday/9/Feb/2024"
echo "Fuck anti furs, homophobes and racists"
echo "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-="

echo "Making Bondi folder."
mkdir Bondi
cd Bondi
echo "Done"

echo "Downloading the Json editor."
wget https://raw.githubusercontent.com/HttpAnimation/Bondi/stable/JsonEditorApp.py
echo "Done"
echo "Downloading the main script."
wget https://raw.githubusercontent.com/HttpAnimation/Bondi/stable/BondiWeb.py
wget https://raw.githubusercontent.com/HttpAnimation/Bondi/stable/window.py
echo "Done"

echo "Making dir's"
mkdir templates
mkdir Config
echo "Done"

echo "Downloading webUI"
cd templates
wget https://raw.githubusercontent.com/HttpAnimation/Bondi/stable/templates/index.html
cd ../
echo "Done"
cd Config
wget https://raw.githubusercontent.com/HttpAnimation/Bondi/stable/Config/subsections.json
wget https://raw.githubusercontent.com/HttpAnimation/Bondi/stable/Config/Games.json
echo "Done"

echo "Rename the main script."
cd Bondi
mv BondiWeb.py Bondi.py
cd ../
echo "Done mate have fun with Bondi"
rm Install.sh