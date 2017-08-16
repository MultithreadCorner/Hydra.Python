.. Random:

Random Class
############

This class implements functionalities associated with random number generation
and pdf sampling. This class can sample and fill ranges with data corresponding
to ``Gaussian``, ``Exponential``, ``Uniform`` and ``Breit-Wigner`` distributions.

This class is a wrapper of ``hydra C++ Random class``. The Random class have
two constructors to instantiate the Random class:

- Constructor with empty seed. The default seed value is ``7895123``.
- Constructor expecting the seed.

.. code-block:: python

    import HydraPython as hp

    r = hp.Random()          # default seed
    r2 = hp.Random(8385977)  # Seed value
    # This will construct the 2 Random class's object one with default seed and
    # one with the seed value 8385977


Apart from setting the seed value at the time of creation the seed can be
set or get with setter and getter methods named ``SetSeed`` and ``GetSeed``.

.. code-block:: python

    r = hp.Random()
    print (r.GetSeed())         # Give the seed value of object r. 7895123
    r.SetSeed(988763)           # New seed is 988763
    print (r.GetSeed())         # 988763


The Random class provides a method named ``Uniform`` to generate the numbers
between range (min, max) (both min and max exclusive) and
fill them into the container according to the `Continuous Uniform
distribution<https://en.wikipedia.org/wiki/Uniform_distribution_(continuous)>`_.
The container can be any of the ``host_vector_float`` or ``device_vector_float``.
In below examples, I have used device_vector_float extensively but they both
can be used interchangeably in place of each other.

.. code-block:: python

    import HydraPython as hp

    container = hp.device_vector_float(1000000)   # Continer to hold 1000000 objects
    r = hp.Random()                              # Random number generator object
    r.Uniform(1.1, 1.5, container)  # Minimum number 1.1, maximum 1.5 and container
    # Above will generate 1000000 numbers between (1.1, 1.5)

    print (container[:10])


The Gauss random number generation method can also be used with the Random class.
The ``Gauss`` method generate the numbers with the given ``mean`` and ``sigma``
values.

.. code-block:: python

    import HydraPython as hp

    container = hp.device_vector_float(1000000)   # Continer to hold 1000000 objects
    r = hp.Random()                              # Random number generator object
    r.Gauss(-2.0, 1.0, container)
    # Above will generate 1000000 with mean -2.0 and sigma as 1.0


The Exponential random number generation method or ``Exp`` method in Random class
generates the numbers with the given ``tau`` value of the Exponential distribution.

.. code-block:: python

    import HydraPython as hp

    container = hp.host_vector_float(100)   # Continer to hold 100 objects.
    r = hp.Random()                         # Random number generator object
    r.Exp(1.0, container)                   # tau is 1.0
    print (container)


The Random class also provides a ``BreitWigner`` method to generate random number
according to a BreitWigner with ``mean`` and ``width``.

.. code-block:: python

    import HydraPython as hp

    container = hp.device_vector_float(10000)   # Continer to hold 10000 objects.
    r = hp.Random()                             # Random number generator object
    r.BreitWigner(2.0, 0.2, container)          # mean=2.0, width=0.2
    print (container)


Apart from all these distributions, you can also define your own distribution
and pass it as a function to the method. The ``Sample`` method allows you to pass
a function that will be sampled for the given sampling range (lower, upper) and
store the result in the container.

.. code-block:: python

    import HydraPython as hp

    # The functon which will be sampled.
    import math
    def gauss1(*args):
        g = 1.0
        mean = -2.0
        sigma = 1.0
        for i in range(3):
            m2 = (args[i] - mean) * (args[i] - mean)
            s2 = sigma * sigma
            g *= math.e ** ((-m2/(2.0 * s2 ))/( math.sqrt(2.0*s2*math.pi)))
        return g

    container = hp.host_vector_float3(10000)  # Container with 10000 objects each having 3 floats
    r = hp.Random()                           # Random object
    r.Sample(d, [6, 6, 6], [-6, -6, -6], gauss1)
    # d is container, [6, 6, 6] is the start range (1 for each float in container),
    # [-6, -6, -6] is end range, gauss1 is the functor.


In sample method, the start range and end range should have the same number of
arguments as in the container. So for example, if you are using container of
``float7`` than start range and end range each should contain ``7`` elements.


.. warning:: Any of device containers will not work with ``Sample`` method.


The complete method list supported by Random class can be found on [#f1]_.

The container list that can be passed to ``Sample`` method can be found on [#f2]_.

.. [#f1] The method list for Random classes

  - ``GetSeed``  Get the seed. Syntax:

      - seed = r.GetSeed()

  - ``SetSeed``  Set seed. Syntax:

      - r.SetSeed(seed)

  - ``Gauss``  Generate the Gauss distribution. Syntax:

      - r.Gauss(mean, sigma, container)  # container can be [device/host]_vector_float

  - ``Uniform`` Generate the Continuous Uniform distribution. Syntax:

      - r.Uniform(min, max, container)   # container can be [device/host]_vector_float

  - ``Exp`` Generate the Exponential distribution. Syntax:

      - r.Exp(tau, container)   # container can be [device/host]_vector_float

  - ``BreitWigner`` Generate the BreitWigner distribution. Syntax:

      - r.BreitWigner(mean, width, container)  # container can be [device/host]_vector_float

  - ``Sample`` sample the given function. Syntax:

      - iterator_accepted_events = r.Sample(container, [min_values_list], [max_limit_list], function)  # Container could be any of the container listed below


.. [#f2] The list of available containers to use with Random.

  - ``host_vector_float``  host container with 1 float. Syntax:

      - h_container1 = hp.host_vector_float(size)

  - ``host_vector_float2``  host container with 2 float. Syntax:

      - h_container2 = hp.host_vector_float2(size)

  - ``host_vector_float3``  host container with 3 float. Syntax:

      - h_container3 = hp.host_vector_float3(size)

  - ``host_vector_float4``  host container with 4 float. Syntax:

      - h_container4 = hp.host_vector_float4(size)

  - ``host_vector_float5``  host container with 5 float. Syntax:

      - h_container5 = hp.host_vector_float5(size)

  - ``host_vector_float6``  host container with 6 float. Syntax:

      - h_container6 = hp.host_vector_float6(size)

  - ``host_vector_float7``  host container with 7 float. Syntax:

      - h_container7 = hp.host_vector_float7(size)

  - ``host_vector_float8``  host container with 8 float. Syntax:

      - h_container8 = hp.host_vector_float8(size)

  - ``host_vector_float9``  host container with 9 float. Syntax:

      - h_container9 = hp.host_vector_float9(size)

  - ``host_vector_float10``  host container with 10 float. Syntax:

      - h_container10 = hp.host_vector_float10(size)

  - ``device_vector_float``  device container with 1 float. Syntax:

      - d_container1 = hp.device_vector_float(size)

  - ``device_vector_float2``  device container with 2 float. Syntax:

      - d_container2 = hp.device_vector_float2(size)

  - ``device_vector_float3``  device container with 3 float. Syntax:

      - d_container3 = hp.device_vector_float3(size)

  - ``device_vector_float4``  device container with 4 float. Syntax:

      - d_container4 = hp.device_vector_float4(size)

  - ``device_vector_float5``  device container with 5 float. Syntax:

      - d_container5 = hp.device_vector_float5(size)

  - ``device_vector_float6``  device container with 6 float. Syntax:

      - d_container6 = hp.device_vector_float6(size)

  - ``device_vector_float7``  device container with 7 float. Syntax:

      - d_container7 = hp.device_vector_float7(size)

  - ``device_vector_float8``  device container with 8 float. Syntax:

      - d_container8 = hp.device_vector_float8(size)

  - ``device_vector_float9``  device container with 9 float. Syntax:

      - d_container9 = hp.device_vector_float9(size)

  - ``device_vector_float10``  device container with 10 float. Syntax:

      - d_container10 = hp.device_vector_float10(size)
