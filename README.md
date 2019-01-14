# dining_philosophers
Simple solution of classic dining philosophers problem.

[Latest version .zip archive](https://github.com/ivzhuravlev/dining_philosophers/blob/master/installer/DiningPhilosophers-1.0.1-win32.zip)

[Latest version Windows Installer](https://github.com/ivzhuravlev/dining_philosophers/blob/master/installer/DiningPhilosophers-1.0.1-win32.exe)

## Problem description
This application is the simulation of [dining philosophers problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem). A solution of this problem (and many other insteresting ones) is described in details in a wonderful free book [The Little Book of Semaphores](http://greenteapress.com/wp/semaphores/). To avoid deadlocks the Footman Semaphore approach was applied. Number of philosophers is not limited.

## Application structure
The program consists of two parts:

*dphCore* is a library that contains dinner simulation logic.

*dphGui* is a driver GUI application that runs the simulation and supports some customizations through the *Settings* dialog. 

## Application screenshots
Main window:

![main window](https://github.com/ivzhuravlev/dining_philosophers/blob/master/screenshots/main_window.png "Main window")

Settings dialog:

![settings dialog](https://github.com/ivzhuravlev/dining_philosophers/blob/master/screenshots/settings.png "Settings dialog")

## Build requirements
- CMake version >= 3.11
- Qt version >= 5.9
