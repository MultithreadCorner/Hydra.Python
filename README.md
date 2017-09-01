[![GPL Licence](https://badges.frapsoft.com/os/gpl/gpl.png?v=103)](https://opensource.org/licenses/GPL-3.0/)
[![Documentation Status](https://readthedocs.org/projects/hydrapython-documentation/badge/?version=latest)](http://hydrapython-documentation.readthedocs.io/en/latest/?badge=latest)
[![Gitter](https://img.shields.io/gitter/room/nwjs/nw.js.svg)](https://gitter.im/hydra-hython)

Hydra.Python
============

Python 2.7+ and 3.x bindings for the [Hydra C++ library](https://github.com/MultithreadCorner/Hydra/)
The bindings are produced with [pybind11](http://pybind11.readthedocs.io/). The project makes use of [CMAKE](https://cmake.org/).

You can find the Hydra.Python GSoC2017-release [here](https://github.com/MultithreadCorner/Hydra.Python/tree/GSoC2017-release).

Documentation
-------------

Comprehensive documentation is can be found under the `docs/` folder. The `docs/` folder
also contains the [GSoC 2017 project report](https://github.com/MultithreadCorner/Hydra.Python/blob/master/docs/project_report.rst).

The manual of the project is generated using [Sphinx](http://www.sphinx-doc.org/en/stable/) and is hosted in 
[ReadTheDocs](https://readthedocs.org/).
Find below the links for the different versions available for the manual:

  1. [__latest html__](https://readthedocs.org/projects/hydrapython-documentation/badge/?version=latest)
  2. [__latest pdf__](https://readthedocs.org/projects/hydrapython-documentation/downloads/pdf/latest/)
  3. [__latest epub__](https://readthedocs.org/projects/hydrapython-documentation/downloads/epub/latest/)
 
Other versions, generated from different branches can be found on the [here](https://readthedocs.org/projects/hydrapython-documentation/downloads).

[Doxygen](http://www.doxygen.nl/index.html) reference documentation is underway. 

Getting started
---------------

Work-in-progress instructions:

0. when cmake'ing pybind11, make sure to specify the correct major Python version. For example `cmake -DPYTHON_EXECUTABLE:FILEPATH=/usr/bin/python` to make sure Python 2 is picked up. (Or provide the path to python3)
1. clone the git repository: `git clone https://github.com/AAAlvesJr/Hydra.git`
2. go to the Hydra.Python directory just retrieved: `cd Hydra.Python`
3. create a build directory: `mkdir build`
4. go to build directory: `cd build`
5. `cmake -DHYDRA_INSTALL_PATH=/path2sw/Hydra/ -DTHRUST_INSTALL_PATH=/path2sw/Hydra/ -DPYBIND11_INSTALL_PATH=/path2sw/pybind11/include/ ..`
6. `make`

These instructions create a library .so to be imported from Python.

Authors
=======
[Antonio Augusto Alves Jr](@AAAlvesJr) , [Deepanshu Tharkur](@Deepanshu2017) and [Eduardo Rodrigues](@eduardo-rodrigues)
