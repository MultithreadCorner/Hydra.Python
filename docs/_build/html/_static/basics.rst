.. _basics:

First steps
###########

This section demonstrates the basic features of HydraPython. Before getting
started, make sure that the development environment is set up to compile the
included set of test cases.


Quick start
===========

On Linux you'll need the `Hydra`_ and `Pybind11`_ projects as well as **cmake** to build. The **python-dev** or **python3-dev** package is required too.
You can clone
and fetch the latest code for both of the mentioned libraries. Then you could
create a directory structure similar to below one.

.. code-block:: bash

    Project root -
      - Hydra.Python            (latest code of Hydra Python)
      - Hydra                   (latest code of Hydra)
      - Pybind11                (latest code of Pybind11)
      - build                   (build directory)

.. _Hydra: https://github.com/MultithreadCorner/Hydra
.. _Pybind11: https://github.com/pybind/pybind11.git

After downloading the prerequisites, run

.. code-block:: bash

   cd build
   cmake -DHYDRA_INSTALL_PATH=../Hydra -DPYBIND11_INSTALL_PATH=../pybind11/include -DTHRUST_INSTALL_PATH=../Hydra ../Hydra.Python
   make all

The last line will both compile and create a shared ``.so`` file which is the library imported in python.

The best way to check if the installation is correct or not is to run the test
cases provided in the ``Hydra.Python/tests/`` directory.

Creating a simple Lorentz vector and calculating the particle's mass
====================================================================

Let's start by importing the module:

.. code-block:: python

    import HydraPython as hp


The name ``HydraPython`` is quite long so generally, we use its alias as ``hp``.

Now that we have already imported the module let's just simply create the particle Lorentz vector, i.e. the ``Vector4R`` instance.

.. code-block:: python

    import HydraPython as hp
    vec4 = hp.Vector4R()
    print(vec4)  # (0, 0, 0, 0)

So this is it. We've just created a ``Vector4R`` object represending the 4-momentum vector of a particle.
This matter is important when the ``PhaseSpace`` class will be used to generate Events with N particles.

The next 3 pages explain the Vector classes (``Vector4R`` and ``Vector3R``), the ``Events``
classes and the ``PhaseSpace`` class in more detail.
