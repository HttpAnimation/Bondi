## This is the install guide for windows
# Back to [README.md](README.md)

### Notes 
1. Java is needed for this guide.
2. Windows powershell is needed for this guide and light wight versions of windows might not work.
3. Windows does not get tested builds so issues might be seen and noticed please report these to get fixed

### Go to the download page witch can be found [here](https://github.com/HttpAnimation/Bondi/releases)
Extract the zip file for the version you are downloading and then open a power shell and cd into the dir that has the Bondi.java file an exp can be found under here
```
cd c:/users/Bondi/desktop/Bondi/V69/
```
then run ls to see the files and make sure the Bondi.java file is placed there
```
c:/users/Bondi/desktop/Bondi/V69/ | ls
```
If it is placed there then make sure java is installed by running
```
java -version
```
If the command is not found head over to [java 17 archive](https://www.oracle.com/java/technologies/javase/jdk17-archive-downloads.html) downloads page and download java but if it downloaded run
```
javac Bondi.java
```
to compile the java app/Bondi now to run the app run
```
java Bondi
```