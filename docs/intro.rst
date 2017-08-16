.. image:: hydra_logo.png

About this project
==================
**HydraPython** is a wrapper around the header-only C++ `Hydra`_ library that provides
the abstraction over the C++ method. This library is an abstraction over the
C++ library, so that you can work with much simpler Python language, concentrate
more on the logic and leave all the memory management stuff up to the library. This
library is written keeping ``Linux`` systems in mind, but you might apply some
hacks to make compatible with other platforms.

.. _Hydra: https://github.com/MultithreadCorner/Hydra


Core features
*************
The following core C++ features can be mapped to Python

- Python 2.7, and 3.x are supported.
- The continuous expansion of the original Hydra library.
- Support for ``particles`` with ``Vector4R`` class.
- Support for containers like ``Events`` or ``Decay``.


Supported compilers
*******************

1. Clang/LLVM (any non-ancient version with C++11 support)
2. GCC 4.8 or newer
