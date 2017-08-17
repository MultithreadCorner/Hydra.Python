Hydra.Python
============

Python 2.7+ and 3.x bindings for the [Hydra C++ library](https://github.com/MultithreadCorner/Hydra/).

The bindings are produced with [pybind11](http://pybind11.readthedocs.io/). The project makes use of [CMAKE](https://cmake.org/).


Getting started
---------------

Work-in-progress instructions:

0. when cmake'ing pybind11, make sure to specify the correct major Python version. For example `cmake -DPYTHON_EXECUTABLE:FILEPATH=/usr/bin/python` to make sure Python 2 is picked up.
1. clone the git repository: `git clone https://gitlab.com/aalvesjr/Hydra.Python.git`
2. go to the Hydra.Python directory just retrieved: `cd Hydra.Python`
3. create a build directory: `mkdir build`
4. go to build directory: `cd build`
5. `cmake -DHYDRA_INSTALL_PATH=/path2sw/Hydra/ -DTHRUST_INSTALL_PATH=/path2sw/Hydra/ -DPYBIND11_INSTALL_PATH=/path2sw/pybind11/include/ ..`
6. `make`
