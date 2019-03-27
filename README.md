## building
```
$ make
$ simh-pdp11 boot.ini
```

the installation process is as follows:

- build the bootloader, kernel, userspace, and tools.
- use `tools/mkfs` to copy the root directory to `boot.img`
- use `tools/mkboot` to install the bootloader to the first sector of `boot.img`

## building pdp11-aout-gcc

### binutils

download the latest version of [binutils](https://ftp.gnu.org/gnu/binutils/)

```bash
tar xvf /path/to/binutils-version-stuff.tar.bz2
cd binutils-version-stuff
mkdir build-pdp11-aout
cd build-pdp11-aout
../configure --target=pdp11-aout --prefix=$PREFIX
make
sudo make install
```

### gcc

download gcc 9 or greater [gcc](https://ftp.gnu.org/gnu/gcc/). if gcc 9 has not
been released yet, get a development snapshot.

```bash
tar xvf /path/to/gcc-version-stuff.tar.bz2
cd gcc-version-stuff
mkdir build-pdp11-aout
cd build-pdp11-aout
../configure --target=pdp11-aout --prefix=$PREFIX --enable-languages=c --disable-libssp
make
sudo make install
```

build references:

- http://docs.cslabs.clarkson.edu/wiki/Developing_for_a_PDP-11
- https://wiki.osdev.org/GCC_Cross-Compiler
