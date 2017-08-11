.. _basics:

First steps
###########

This sections demonstrates the basic features of HydraPython. Before getting
started, make sure that development environment is set up to compile the
included set of test cases.


Compiling the test cases
========================

Linux/MacOS
-----------

On Linux  you'll need the `Hydra`_, `Pybind11`_ and the **cmake**. Also you will
be requiring the **python-dev** or **python3-dev** package. You can clone
and fetch the latest code for both of the mentioned libraries. Than you could
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

The last line will both compile and create a shared ``.so`` file which can be
imported in the python.

The best way to check if the installation is correct or not is to run the test
cases provided in the Hydra.Python/tests.

Creating simple Vector4R particle and calculate it's mass
=========================================================

Let's start by creating importing the module:

.. code-block:: python

    import HydraPython as hp


The name ``HydraPython`` is quite long so generally we use it's alias as ``hp``.

Now that we have already imported the module let's just simple create a ``Vector4R``
object.

.. code-block:: python

    import HydraPython as hp
    vec4 = hp.Vector4R()
    print(vec4)  # (0, 0, 0, 0)

So this is it. You just created a Vector4R object. The Vector4R object in Hydra
is used as a ``particle``. This understanding is important when
you will use the ``PhaseSpace`` class to generate the Events over N particles.

The next 3 pages explain the Vector classes (``Vector4R`` and ``Vector3R``), ``Events``
classes and the ``PhaseSpace`` class in more detail.
