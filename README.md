# gst-plugin-good-qt-examples
Examples for the gstreamer plugins qmlglsrc, qmlglsink and qmlgloverlay with .pro files to compile with qmake. 

## The examples are from the official gstreamer repo [(gitlab.freedesktop.org)](https://gitlab.freedesktop.org/gstreamer/gstreamer)
- location: gstreamer/subprojects/gst-plugins-good/tests/examples/qt
- .pro file was added when not already available

## How to build
Dependencies:
- gstreamer
- plugins: qmlglsrc, qmlglsink, qmlgloverlay

Exemplary build steps:
```
$ cd qmlsink
$ mkdir build && cd build
$ qmake ../play.pro && make
```
## How to run
In oder to have all dependencies and paths set in the environment I use the gst-env.py script which is located in the root folder of the gstreamer repo.
```
$ cd gstreamer 
$ gst-env.py
```
- Export qt library path and run
```
$ export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/$USER/Qt/5.15.2/gcc_64/lib
$ cd <whereever you cloned the example>/build
$ ./play
```
Maybe also works if you have gstreamer packages installed (qmlgloverlay in not included in the apt package of Ubuntu 20.04 though). 


## How to build gstreamer from source

You can build gstreamer and all plugins easily from source.

- Prerequisites (assuming you already have build-essential and the usual suspects installed)
```
$ sudo apt-get install flex bison
$ sudo apt-get install python3-pip
$ sudo apt-get install ninja-build
$ pip3 install --user meson
$ vi ~/.bashrc
  export PATH=$PATH:/home/chris/.local/bin
```
- Install qt5
  - download installer [(here)](https://login.qt.io/login)  (have to make qt account, even for open-source version)
  - install components (I suggest LTS version 5.15.2)  

- Set qt references (example is for qt 5.15.2)
```
$ export QMAKE=/home/$USER/Qt/5.15.2/gcc_64/bin/qmake
$ export PATH=$PATH:/home/$USER/Qt/5.15.2/gcc_64/bin
```

### Build gstreamer
- Clone repo from [(gitlab.freedesktop.org)](https://gitlab.freedesktop.org/gstreamer/gstreamer)

```
$ cd gstreamer
$ meson build --buildtype=debug -Dgood=enabled -Dgst-plugins-good:qt5=enabled
$ ninja -C build -j8
(to clean use: $ ninja -C build/ -t clean)
```
