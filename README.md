# Bondi
Bondi is a app/game launcher made in [C](https://en.wikipedia.org/wiki/C_(programming_language)).

## Installing
To install Bondi open a terminal and run the following command. You can also find the program [here](https://github.com/HttpAnimation/Bondi/releases).
```bash
echo "Installing" && wget https://raw.githubusercontent.com/HttpAnimation/Bondi/main/CVInstallNewest.bash && chmod +x CVInstallNewest.bash
```

## Compiling
If you would like to compile from source follow these instructions.

### [Fedora](https://fedoraproject.org/) ([dnf](https://docs.fedoraproject.org/en-US/quick-docs/dnf/))

#### Perrepisites 
To install the needed packages open a terminal and run the following commands.

1) Update
```bash
sudo dnf update
```
2) Install [gcc](https://gcc.gnu.org/)
```bash
sudo dnf install gcc
```
3) Intall [gtk3-devel](https://packages.fedoraproject.org/pkgs/gtk3/gtk3-devel/)
```bash
sudo dnf install gtk3-devel
```
4) Clone the repo with stable data.
```bash
git clone -b stable https://github.com/HttpAnimation/Bondi.git 
```
5) Enter the repo
```bash
cd Bondi
```
6) Allow the script to run.
```bash
chmod +x Compile.sh
```
7) Compile
```bash
../Compile.bash
```
### Debian/Ubuntu based
Right now none