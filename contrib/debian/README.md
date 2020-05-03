
Debian
====================
This directory contains files used to package pawsd/paws-qt
for Debian-based Linux systems. If you compile pawsd/paws-qt yourself, there are some useful files here.

## paws: URI support ##


paws-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install paws-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your pawsqt binary to `/usr/bin`
and the `../../share/pixmaps/paws128.png` to `/usr/share/pixmaps`

paws-qt.protocol (KDE)

