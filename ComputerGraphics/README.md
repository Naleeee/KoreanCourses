# Dependencies:
## On Debian based OS

enable 32bits repositories
```Bash
sudo dpkg --add-architecture i386
sudo apt-get update
```
install fltk 32bit lib and glu 32bit lib
```Bash
sudo apt install libfltk:i386
```

## On Arch based OS
enable 32bits repositories
enable multilib: https://wiki.archlinux.org/title/Official_repositories#multilib
install fltk 32bit lib and glu 32bit lib
```Bash
paru -S lib32-fltk lib32-glu
```
