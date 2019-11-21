# My GameEngine

A fun project for my freetime

##### Why?
- Fun
- Why not
- Learning opportunity

## Libraries used
| Use Case | Name | Link |
| ------ | ------ | ------ |
| Graphics API | GLEW | https://github.com/nigels-com/glew |
| Audio Engine | FMOD | https://www.fmod.com |
| Window & Input API | SDL2 | https://www.libsdl.org/index.php |
| Physics Engine | Bullet3 | https://github.com/bulletphysics/bullet3 |
| Virtual Reality API | OpenVR | https://github.com/ValveSoftware/openvr |
| Serialization Library | FlatBuffers | https://github.com/google/flatbuffers |

## Installation

#### apt packages
```sh
$ sudo apt-get update
$ sudo apt-get upgrade -y
$ sudo apt-get install git build-essential g++ make cmake libx11-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev libxrandr-dev libxext-dev libxcursor-dev libxinerama-dev libxi-dev libxmu-dev libgl-dev mercurial -y
```
#### SDL
```sh
$ hg clone https://hg.libsdl.org/SDL SDL
$ mkdir SDL/build && cd SDL/build
$ ../configure
$ make
$ sudo make install
$ cd ../..
$ rm -rf SDL
```

#### GLEW
```sh
$ git clone https://github.com/nigels-com/glew.git glew
$ cd glew/auto
$ make
$ cd ..
$ make
$ sudo make install
$ make clean
$ sudo ln -s /usr/lib64/libGLEW.so.2.2 /usr/lib/libGLEW.so.2.2
$ cd ..
$ rm -rf glew
```
#### GameEngine
```sh
$ git clone https://github.com/OptoCloud/GameEngine engine
$ mkdir engine/build && cd engine/build
$ cmake ..
$ make
```

