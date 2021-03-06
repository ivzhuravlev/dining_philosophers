# dining_philosophers

[![Build status](https://ci.appveyor.com/api/projects/status/vqxf2tauhe7717rp?svg=true)](https://ci.appveyor.com/project/ivzhuravlev/dining-philosophers)
[![Build Status](https://travis-ci.com/ivzhuravlev/dining_philosophers.svg?branch=master)](https://travis-ci.com/ivzhuravlev/dining_philosophers)

Simple solution of classic dining philosophers problem.

## Downloads

[Latest 32bit version .zip archive](https://github.com/ivzhuravlev/dining_philosophers/releases/download/v1.1.0/DiningPhilosophers-1.1.0-win32.zip)

[Latest 64bit version .zip archive](https://github.com/ivzhuravlev/dining_philosophers/releases/download/v1.1.0/DiningPhilosophers-1.1.0-win64.zip)

[Latest 32bit version Windows Installer](https://github.com/ivzhuravlev/dining_philosophers/releases/download/v1.1.0/DiningPhilosophers-1.1.0-win32.exe)

[Latest 64bit version Windows Installer](https://github.com/ivzhuravlev/dining_philosophers/releases/download/v1.1.0/DiningPhilosophers-1.1.0-win64.exe)

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
- Qt IFW version >= 3.0 (optional)
