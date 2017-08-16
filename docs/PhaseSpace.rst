.. PhaseSpace:

PhaseSpace Class
################

Ths class implements the phase-space Monte Carlo simulation where N is the number
of particles in the Final state. Currently PhaseSpace class supports up-to
N=10 number of particles in the Final state. Most of the PhaseSpace class
methods can work on both ``HOST`` and ``DEVICE``. The number of particles is
associated with suffix with the class name.

This class is a wrapper of C++ PhaseSpace class. The PhaseSpace class one constructor
to instantiate the PhaseSpace class:

- Constructor with mother mass and N number of daughter masses.

.. code-block:: python

    import HydraPython as hp

    vec4 = hp.Vector4R(5.2795, 0.0, 0.0, 0.0)
    p = hp.PhaseSpace4(vec4.mass(), [3.096916, 0.493677, 0.13957018, 0.0195018])
    # This will construct the PhaseSpace object with the mass provided by the vector4R
    # class and the exactly 4 daughter masses in the list.


The PhaseSpace classes provides the method to Generate a phase-space given a mother particle and an output range
or a phase-space given a range of mother particles and an output range.

.. code-block:: python

    vec4 = hp.Vector4R(5.2795, 0.0, 0.0, 0.0)
    ps = hp.PhaseSpace4(vec4.mass(), [3.096916, 0.493677, 0.13957018, 0.0195018])
    e_host = hp.hostEvents4(3)
    e_device = hp.deviceEvents4(3)
    ps.Generatehost(vec4, e_host)  # Generate particle on host
    ps.Generatedevice(vec, e_device)  # Generate particle on device

    ####### ADD EXAMPLE OF given a range of mother particles and an output range


The ``AverageOn`` method by PhaseSpace classes calculate the ``mean`` and ``sqrt(variance)``
of a functor over the phase-space with n-samples or of a functor over the phase-space given a
list of mother particles.

.. code-block:: python

    import HydraPython as hp
    import math
    def foo(*data):
        p1, p2, p3 = data[0], data[1], data[2]
        p = p1 + p2 + p3
        q = p2 + p3
        pd = p * p2
        pq = p * q
        qd = q * p2
        mp2 = p.mass2()
        mq2 = q.mass2()
        md2 = p2.mass2()
        return (pd * mq2 - pq * qd) / math.sqrt((pq * pq - mq2 * mp2) * (qd * qd - mq2 * md2))

    vec4 = hp.Vector4R(5.2795, 0.0, 0.0, 0.0)
    p = hp.PhaseSpace4(vec4.mass(), [3.096916, 0.493677, 0.13957018, 0.0195018])
    tup1 = p.AverageONhost(vec4, foo, 10)  # Average of host, currently passing functor to device will fail
    print (tup[0])  # Mean
    print (tup[1])  # sqrt of variance

    ####### ADD EXAMPLE of a functor over the phase-space given a list of mother particles.


#### TODO ####
Add example and documentation of ``Evaluate`` methods.

The complete method list supported by PhaseSpace Events classes can be found
on [#f1]_.

The complete list of the classes in the PhaseSpace can be found on [#f2]_.

.. [#f1] The method list for PhaseSpace classes

  - ``GetSeed``  Get the seed. Syntax:

      - p.GetSeed()

  - ``SetSeed``  Set seed. Syntax:

      - p.SetSeed(seed)

  - ``generate``  Generate the phase-space. Syntax:

      - p.generate(vector4R, event)  # event1's content will be assigned to event2.
      - ### SECOND EXAMPLE

  - ``AverageON`` Get the mean and sqrt of variance. Syntax:

      - p.AverageON(vector4R, functor, entires)
      - ### SECOND EXAMPLE

  - ``Evaluate`` dummy Syntax:

      - dummy


.. [#f2] The list of PhaseSpace classes

  - ``PhaseSpace1``  Generate the phase-space with 1 particles. Syntax:

      - p = hp.PhaseSpace1(mass, [1 daughter mass])

  - ``PhaseSpace2``  Generate the phase-space with 2 particles. Syntax:

      - p = hp.PhaseSpace2(mass, [2 daughter masses])

  - ``PhaseSpace3``  Generate the phase-space with 3 particles. Syntax:

      - p = hp.PhaseSpace3(mass, [3 daughter masses])

  - ``PhaseSpace4``  Generate the phase-space with 4 particles. Syntax:

      - p = hp.PhaseSpace4(mass, [4 daughter masses])

  - ``PhaseSpace5``  Generate the phase-space with 5 particles. Syntax:

      - p = hp.PhaseSpace5(mass, [5 daughter masses])

  - ``PhaseSpace6``  Generate the phase-space with 6 particles. Syntax:

      - p = hp.PhaseSpace6(mass, [6 daughter masses])

  - ``PhaseSpace7``  Generate the phase-space with 7 particles. Syntax:

      - p = hp.PhaseSpace7(mass, [7 daughter masses])

  - ``PhaseSpace8``  Generate the phase-space with 8 particles. Syntax:

      - p = hp.PhaseSpace8(mass, [8 daughter masses])

  - ``PhaseSpace9``  Generate the phase-space with 9 particles. Syntax:

      - p = hp.PhaseSpace9(mass, [9 daughter masses])

  - ``PhaseSpace10``  Generate the phase-space with 10 particles. Syntax:

      - p = hp.PhaseSpace10(mass, [10 daughter masses])
