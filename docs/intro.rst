About this project
==================
The **Hydra.Python** package provides the Python bindings for the header-only C++ `Hydra`_ library.
This library is an abstraction over the C++ library, so that daily work can be coded and run with the Python language,
concentrating on the logic and leaving all the complex memory management and optimisations to the C++ library.

The bindings are produced with `pybind11`_. The project makes use of `CMAKE`_ for what concerns the building of the Hydra.Python library.

The  library is written with ``Linux`` systems in mind, but compatibility with other platforms may be achieved with "hacks".
Python versions 2.7, and 3.x are supported.


.. _Hydra: https://github.com/MultithreadCorner/Hydra
.. _pybind11: http://pybind11.readthedocs.io/
.. _CMAKE: https://cmake.org/


Core features
*************
The core functionality of Hydra has been exposed to Python.
The following core C++ features of Hydra can be mapped to Python:

- The continuous expansion of the original Hydra library.
- Support for particles with ``Vector4R`` class.
- Support for containers like ``Events`` or ``Decay``.


Supported compilers
*******************

1. Clang/LLVM (any non-ancient version with C++11 support).
2. GCC 4.8 or newer.


History
*******
The development of **Hydra.Python** started as a
2017 Google Summer of Code project (`GSoC`_) with student `Deepanshu Thakur`.

.. _GSoC: https://summerofcode.withgoogle.com/projects/#6669304945704960
.. _Deepanshu Thakur: https://github.com/Deepanshu2017
