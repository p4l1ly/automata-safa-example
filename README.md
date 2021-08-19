# automata-capnp-example

WARNING: The README is obsolete, see dockerfiles!

This is a simple C++ and Python example of reading automata-safa-capnp's
separated alternating finite automata. All the tools and libraries should be
compatible with Linux, Windows and Mac, however I've tried it only with Linux.

If you want to skip the complex installation process and just use docker,
there's a section in the end of this README.

## Installation

The best installation instructions are maybe in the Dockerfiles. This is just a
more human readable description. But it is tested only by the Dockerfiles, so
if you have some problems, please refer to the Dockerfiles.

## Easy installation (system wide) (Ubuntu)

### Python

You will need the following packages and sudo root privileges:
`unzip`, `python3-dev`, `python3-pip`, `libcapnp-dev`, `wget`

```
cd dependencies/
unzip automata-safa-capnp-master.zip
cd automata-safa-capnp-master
pip install .
cd ../..

cd /usr/include/capnp
sudo wget https://raw.githubusercontent.com/capnproto/capnproto-java/ad460a4723363885461d00d02183270038fb7b38/compiler/src/main/schema/capnp/java.capnp
cd -

sudo pip3 install pycapnp==1.0.0b2
python3 main.py example/5
```

### C++

You will need the following packages and sudo root privileges:
`unzip`, `wget`, `cmake`, `g++`, `pkg-config`, `capnproto`, `libcapnp-dev`

It is maybe better to use fresh version of `capnproto` so instead of installing
`capnproto` and `libcapnp-dev` from your package repository, you might want to
install it from source (in case of some problems):
```
wget https://github.com/capnproto/capnproto/archive/master.zip -O capnproto.zip
unzip capnproto.zip
cd capnproto-master
cmake -S . -B build
cmake --build build
cmake --install build
```

If all the dependencies are installed, just run:

```
cd dependencies/
unzip automata-safa-capnp-master.zip
cd automata-safa-capnp-master
cmake -S . -B build
cmake --build build --target automata-safa-capnp
cmake --install build
cd ../..

cmake -S . -B build
cmake --build build

build/automata-safa-example example/5
```

Note: you must specify `--target automata-safa-capnp` if you didn't
install fresh capnproto from source, otherwise some executables might fail to
build (`dummy-model-checker`).

## Local installation

Local installation is more complex because you need to build everything from
source and keep the build environment pointing to the locally installed paths.

For C++ you need to install `capnproto` and `automata-safa-capnp`. For Python
you need to additionally install `pycapnp`. You also need one schema file from
the `capnproto-java` repository, even though we won't build Java support. The
file is imported in the schema and capnproto would complain about missing
import.

The files `DockerfilePython` and `DockerfileCpp` show installation steps for
Ubuntu. The steps are more verbosely described in the sequel.

### capnproto

First you should install the dependency `capnproto`. You can probably find the
package in your package manager but if not, or if you want to install it
locally, without root privileges, clone
[the capnproto repo](https://github.com/capnproto/capnproto), `cd` to it and run

```
mkdir -p ~/.local
cmake -DBUILD_SHARED_LIBS=ON -DCMAKE_INSTALL_PREFIX=~/.local/ -S . -B build
cmake --build build
cmake --install build
```

Then, if you've installed it locally (e.g. to `~/.local`), make sure to set up
your environment:

1. `$HOME/.local/bin` should be in your `PATH`
2. `$HOME/.local/lib` should be in your `LD_LIBRARY_PATH`
3. `$HOME/.local/lib/pkgconfig` should by in your `PKG_CONFIG_PATH`

I have the following in my `~/.zshrc` (substitute it with e.g. `~/.bashrc` or
`~/.bash_profile`, depending on your platform and shell):

```
export PATH="$HOME/.local/bin:$PATH"
export LD_LIBRARY_PATH="$HOME/.local/lib"
export PKG_CONFIG_PATH="$HOME/.local/lib/pkgconfig"
```


### pycapnp

The following should be enough:
```
python3 -mvenv venv
./venv/bin/activate
pip install pycapnp==1.0.0b2 \
    --install-option "--force-system-libcapnp" \
    --global-option build_ext \
    --global-option "-I/root/.local/include/" \
    --global-option "-L/root/.local/lib/"
```

In my local installation I didn't need the install-options and global-options.
But in the Dockerfile it was for some reason necessary, so I've put it here.


## capnproto-java

We support java but it is out of the scope of this example. You will however
need one file to suppress capnproto import errors.

Just `cd` to `~/.local/include/capnp` or wherever you've installed the capnp
headers (maybe `/usr/include/capnp` or `/usr/local/include/capnp`) and issue:
```
wget https://raw.githubusercontent.com/capnproto/capnproto-java/ad460a4723363885461d00d02183270038fb7b38/compiler/src/main/schema/capnp/java.capnp
```


### automata-safa-capnp

This package defines Cap'n'Proto schema for various symbolic alternating finite
automata formats. Moreover it defines communication protocol for model
checkers, preprocessors, etc, but for now it is out of the scope of this
example.

Using the `capnp` tool, the package generates C++ (and Haskell and Java)
library for working with the binary automata formats.

The package is not public yet but I expect you've obtained the source code if
you're reading this.

To install the C++ libraries locally, run the following in the directory of automata-safa-capnp:

```
cmake -DCMAKE_SYSTEM_PREFIX_PATH="$HOME/.local;/;/usr;/usr/local" -DCMAKE_INSTALL_PREFIX=~/.local/ -S . -B build
cmake --build build
cmake --install build
```

If you've installed the capnproto to a standard path (like `/usr/lib`), you
don't need to specify `CMAKE_SYSTEM_PREFIX_PATH`. If you want to install
`automata-safa-capnp` to a standard path `/usr/lib`, you don't need to specify
`CMAKE_INSTALL_PREFIX` and you need to issue the last command with `sudo`.

To install the Python libraries, run:

```
pip install .
```



### Building/running this package

#### C++

```
cmake -DCMAKE_SYSTEM_PREFIX_PATH="$HOME/.local;/;/usr;/usr/local" -S . -B build
cmake --build build
```

The variable `CMAKE_SYSTEM_PREFIX_PATH` is again needed only if you've
installed dependencies to your `$HOME/.local`.

And you've got the executable `automata-safa-example` inside the `build`
directory. You have to provide the path to the input file and the executable
will print out some basic information (see `main.c++`)

#### Python

Just run:

```
python3 main.py
```


## Using Docker

If you have docker installed, you can build and docker images for C++ and
Python to try this all out without the complex installation process. Any of the
following should work.

```
docker build -f DockerfileCpp -t automata-safa-example-cpp .
docker run automata-safa-example-cpp
```

```
docker build -f DockerfilePython -t automata-safa-example-python .
docker run automata-safa-example-python
```

```
docker build -f DockerfileCppSimple -t automata-safa-example-cpp .
docker run automata-safa-example-cpp
```

```
docker build -f DockerfilePythonSimple -t automata-safa-example-python .
docker run automata-safa-example-python
```
