# DS-202 specific comments

I've created a fork of divsufsort to verify that it works on large inputs. I've revised the following files in this repository:
* [examples/ds202_sample1.c](examples/ds202_sample1.c) : create and print SA of text "abracadabra"
* [examples/ds202_sample2.c](examples/ds202_sample2.c) : create SA of a randomly generated text of size 150 million characters
* [examples/CMakeLists.txt](examples/CMakeLists.txt) 

Open and check above files. Next, I ran the following commands to compile the code
```
git clone https://github.com/cjain7/libdivsufsort.git
cd libdivsufsort
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE="Release" -DCMAKE_INSTALL_PREFIX=$PWD ..
make
```

You should get `ds202_sample1` and `ds202_sample2` executables in `build/examples` folder.

```
$ pwd
... /libdivsufsort/build
$ ./examples/ds202_sample1
SA[ 0] = 10: a$
SA[ 1] =  7: abra$
SA[ 2] =  0: abracadabra$
SA[ 3] =  3: acadabra$
SA[ 4] =  5: adabra$
SA[ 5] =  8: bra$
SA[ 6] =  1: bracadabra$
SA[ 7] =  4: cadabra$
SA[ 8] =  6: dabra$
SA[ 9] =  9: ra$
SA[10] =  2: racadabra$
```

You can start your homework by [downloading](https://github.com/cjain7/libdivsufsort/archive/refs/heads/master.zip) this repository, and then add your code, i.e., either a C or C++ file in [examples](examples) folder.

### FAQ

- Question: While compiling my code, I get an error saying **undefined reference to divsufsort**
- - The above error occurs when you are not linking divsufsort library during compilation. It is better you compile your code by modifying [examples/CMakeLists.txt](examples/CMakeLists.txt). Afterwards, go to the `build` directory, and run `cmake` and `make` commands as indicated above.
