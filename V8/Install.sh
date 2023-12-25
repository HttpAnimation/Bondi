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