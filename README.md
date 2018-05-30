# seed-qt — Seed for QT Systelab projects

This project is an application skeleton for a typical QT application. You can use it to quickly bootstrap your projects and dev environment.

The seed contains a Patient Management sample application.

The app doesn't do much, just shows how to use different QT patterns and other suggested tools together:

* ...
* ...


## Getting Started

To get you started you can simply clone the `seed-qt` repository.

### Prerequisites

You need [git][git] to clone the seed-qt repository.

Qt is a cross-platform software development tool for embedded and desktop, so you can set your development environment in most of the OS (including Windows, Mac, Linux, etc.). We strongly recommend you using Linux so this is the os we will use through this tutorial.

We will use [QtCreator](https://qt.io) as an IDE and [CMake](https://cmake.org/) to manage the build process.

### Clone `seed-qt`

Clone the `seed-qt` repository using git:

```bash
git clone https://github.com/systelab/seed-qt.git
cd seed-qt
```

If you just want to start a new project without the seed-qt commit history then you can do:

```bash
git clone --depth=1 https://github.com/systelab/seed-qt.git <your-project-name>
```

The depth=1 tells git to only pull down one commit worth of historical data.

## Install Dependencies

In order to install QtCreator follow [instructions](http://doc.qt.io/qt-5/gettingstarted.html). Basically you have to [download](https://www.qt.io/download) and execute the installation package.
You might need to give execution rights to the installer:

1. cd Downloads (or any path where the installer was downloaded).
2. chmod +x qt-unified-linux-x64-3.0.2-online.run
3. ./qt-unified-linux-x64-3.0.2-online.run

To be able to build from the shell:  echo 'export PATH=$HOME/Qt/5.9.4/gcc_64/bin:$PATH' >> ~/.bashrc

Reboot.

Check if you already have a compatible version of CMake (3.9 or above):

1. sudo apt install cmake
2. Reopen terminal and: cmake --version

If you don't have a compatible version then install it:

1. sudo apt install zlib1g-dev
2. sudo apt install libcurl4-openssl-dev
3. wget https://cmake.org/files/v3.10/cmake-3.10.2.tar.gz
4. tar xvf cmake-3*
5. cd cmake-3*
6. ./bootstrap --system-curl && make -j 4
7. sudo make install

## Other dependencies

Check if you have gcc and g++ installed. If not install build-essential package:

sudo apt-get install build-essential

Install also OpenGL libraries:

sudo apt-get install mesa-common-dev 

## Run the application

To run the project, ...

### How it works

...

[git]: https://git-scm.com/
