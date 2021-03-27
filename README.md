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
