.. Vector:

Vector Classes
##############

There are two Vector classes available that are ``Vector4R`` and ``Vector3R``.

Vector4R
========

The Vector4R class is the wrapper of C++ Vector4R class. This class basically
deals with the vector of 4 particles. We have three types of constructors
to instantiate the Vector4R class:

- Default empty constructor
- Copy constructor
- Constructor with 4 real (``float``) numbers

.. code-block:: python

    import HydraPython as hp

    vec1 = hp.Vector4R()  # construction with values 0.0 for all 4 particals
    vec2 = hp.Vector4R(0.8385, 0.1242, 0.9821, 1.2424)
    vec3 = hp.Vector4R(vec2)  # Copy construct the vec3 from vec2

    print (vec1)  # (0, 0, 0, 0)
    print (vec2)  # (0.8385,0.1242,0.9821,1.2424)
    print (vec3)  # (0.8385,0.1242,0.9821,1.2424)

The Vector4R class also provides a pretty convenient method to create an
object from python list.

.. code-block:: python

    list_ = [0.9241, 0.13223, 0.13121, 1.1141]
    vec4 = hp.Vector4R(list_)

This will construct a new Vector4R object with the values passed within
a list. The list should contain exactly 4 elements otherwise a ``TypeError``
will be raised.
The ``set`` methods can be used to set all 4 values or a particular value
in a Vector4R object, while the ``get`` method can be used with Vector4R
to get the value of a particular index. The ``__getitem__`` and
``__setitem`` methods can also be used to get or set the value which comes
very handy and maintain more pythonic way to access and set the values.

.. code-block:: python

    vec5 = hp.Vector4R(0.8385, 0.1242, 0.9821, 1.2424)
    print (vec5)  # (0.8385,0.1242,0.9821,1.2424)

    vec5.set(0, 0.9887)
    print (vec5)  # (0.9887,0.1242,0.9821,1.2424)

    vec5.set(0.1234, 0.5118, 0.9101, 0.1121)
    print (vec5)  # (0.1234,0.5118,0.9101,0.1121)

    print (vec5[1])  # 0.5118
    print (vec5.get(1))  # 0.5118
    vec5[1] = 0.5678
    print (vec5)  # (0.1234,0.5678,0.9101,0.1121)

The Vector4R object can be multiplied or divided by a real value while it
can be added or subtracted with another Vector4R object. One Vector4R
object can be multiplied by another Vector4R object.

.. code-block:: python

    vec6 = hp.Vector4R(0.8215, 0.9241, 0.0105, 1.1994)
    vec6 *= 1.1
    print (vec6)  # (0.90365,1.01651,0.01155,1.31934)
    vec6 /= 0.6
    print (vec6)  # (1.50608,1.69418,0.01925,2.1989)

    vec7 = hp.Vector4R(0.1223, 0.6433, 0.1234, 0.3010)
    vec6 += vec7  # Add vec6 with the values of vec7
    print (vec6)  # (1.62838,2.33748,0.14265,2.4999)

    vec6 -= vec7
    print (vec6)  # (1.50608,1.69418,0.01925,2.1989)

Two Vector4R objects can be easily added, subtracted or multiplied so:

 - ``v = v1 + v2`` # Returns a Vector4R object
 - ``v = v1 - v2`` # Returns a Vector4R object
 - ``v = v1 * v2`` # Returns a real number

All above three are valid for any Vector4R object. There are various
other methods available in Vector4R. The list of Vector4R
methods can be found on [#f1]_.

The Vector4R provides an ``assign`` method to assign or copy the Vector4R
object. This is a very useful method to avoid the nasty bugs for example:

.. code-block:: python

    vec = hp.Vector4R(0.2010, 0.3010, 0.0210, 0.8385)
    vec2 = hp.Vector4R()

    # Do things and later in code ...
    vec2.assign(vec)
    vec == vec2  # True since all values are equal
    vec is vec2  # False

    vec = vec2   # Reference is copied
    vec == vec2  # True
    vec is vec2  # True


Vector3R
========

The Vector3R class is the wrapper of C++ Vector3R class. This class basically
deals with the vector of 3 particles. We have three types of constructors
to instantiate the Vector3R class:

- Default empty constructor
- Copy constructor
- Constructor with 3 real (``float``) numbers

.. code-block:: python

    import HydraPython as hp

    vec1 = hp.Vector3R()  # construction with values 0.0 for all 3 particals
    vec2 = hp.Vector3R(0.8385, 0.1242, 0.9821)
    vec3 = hp.Vector3R(vec2)  # Copy construct the vec3 from vec2

    print (vec1)  # (0,0,0)
    print (vec2)  # (0.8385,0.1242,0.9821)
    print (vec3)  # (0.8385,0.1242,0.9821)

The Vector3R class also provides a pretty convenient method to create an
object from python list.

.. code-block:: python

    list_ = [0.9241, 0.13223, 0.13121]
    vec4 = hp.Vector3R(list_)

This will construct a new Vector3R object with the values passed within
a list. The list should contain exactly 3 elements otherwise a ``TypeError``
will be raised.
The ``set`` methods can be used to set all 3 values or a particular value
in a Vector3R object, while the ``get`` method can be used with Vector3R
to get the value of a particular index. The ``__getitem__`` and
``__setitem`` methods can also be used to get or set the value which comes
very handy and maintain more pythonic way to access and set the values.

.. code-block:: python

    vec5 = hp.Vector3R(0.8385, 0.1242, 0.9821)
    print (vec5)  # (0.8385,0.1242,0.9821)

    vec5.set(0, 0.9887)
    print (vec5)  # (0.9887,0.1242,0.9821)

    vec5.set(0.1234, 0.5118, 0.9101)
    print (vec5)  # (0.1234,0.5118,0.9101)

    print (vec5[1])  # 0.5118
    print (vec5.get(1))  # 0.5118
    vec5[1] = 0.5678
    print (vec5)  # (0.1234,0.5678,0.9101)

The Vector3R object can be multiplied or divided by a real value while it
can be added or subtracted with another Vector3R object. One Vector3R
object can be multiplied by another Vector3R object.

.. code-block:: python

    vec6 = hp.Vector3R(0.8215, 0.9241, 0.0105)
    vec6 *= 1.1
    print (vec6)  # (0.90365,1.01651,0.01155)
    vec6 /= 0.6
    print (vec6)  # (1.50608,1.69418,0.01925)

    vec7 = hp.Vector3R(0.1223, 0.6433, 0.1234)
    vec6 += vec7  # Add vec6 with the values of vec7
    print (vec6)  # (1.62838,2.33748,0.14265)

    vec6 -= vec7
    print (vec6)  # (1.50608,1.69418,0.01925)

Two Vector3R objects can be easily added, subtracted or multiplied so:

 - ``v = v1 + v2`` # Returns a Vector3R object
 - ``v = v1 - v2`` # Returns a Vector3R object
 - ``v = v1 * v2`` # Returns a real number

All above three are valid for any Vector3R object. There are various
other methods available in Vector3R. The list of Vector3R
methods can be found on [#f2]_.

The Vector3R provides an ``assign`` method to assign or copy the Vector3R
object. This is a very useful method to avoid the nasty bugs for example:

.. code-block:: python

    vec = hp.Vector3R(0.2010, 0.3010, 0.0210)
    vec2 = hp.Vector3R()

    # Do things and later in code ...
    vec2.assign(vec)
    vec == vec2  # True since all values are equal
    vec is vec2  # False

    vec = vec2   # Reference is copied
    vec == vec2  # True
    vec is vec2  # True

.. [#f1] The method list for Vector4R

  - ``set`` Set the value at an index or all 4 values of Vector4R. Syntax:

      - vec1.set(idx, float)
      - vec1.set(float, float, float, float)

  - ``get`` Get the value at an index for a Vector4R. Syntax:

      - vec1.get(idx)

  - ``assign``  Assigns one Vector4R content to other Vector4R. Syntax:

      - vec1.assign(vec2)

  - ``cont``  Finds the cont of the Vector4R object. Syntax:

      - result = vec1.cont(vec2)

  - ``mass``  Returns the mass of the Vector4R object. Syntax:

      - result = vec1.mass()

  - ``mass2``  Returns the mass2 of the Vector4R object. Syntax:

      - result = vec1.mass()

  - ``applyRotateEuler``  Apply the rotate Eular on given Vector4R object. Syntax:

      - vec1.applyRotateEuler(float, float, float)

  - ``applyBoostTo``  Apply the boost on the given Vector4R object. Syntax:

      - vec1.applyBoostTo(vec2, bool)
      - vec1.applyBoostTo(Vector3R, bool) # Pay attention to Vector3R object
      - vec1.applyBoostTo(float, float, float, bool)

  - ``cross``  Returns the cross product of two Vector4R. Syntax:

      - result_vector = vec1.cross(vec2)

  - ``dot``  Returns the dot product of two Vector4R. Syntax:

      - result = vec1.dot(vec2)

  - ``d3mag``  Returns the d3mag for two Vector4R. Syntax:

      - result = vec1.d3mag()

  - ``dotr3``  Returns the dot product of three Vector4R. Syntax:

      - result = vec1.dotr3(vec2, vec3)

  - ``mag2r3``  Returns the mag2r3 of two Vector4R. Syntax:

      - result = vec1.mag2r3(vec2)

  - ``magr3``  Returns the magr3 of two Vector4R. Syntax:

      - result_vector = vec1.magr3(vec2)


.. [#f2] The method list for Vector3R

  - ``set`` Set the value at an index or all 3 values of Vector3R. Syntax:

      - vec1.set(idx, float)
      - vec1.set(float, float, float)

  - ``get`` Get the value at an index for a Vector3R. Syntax:

      - vec1.get(idx)

  - ``assign``  Assigns one Vector4R content to other Vector3R. Syntax:

      - vec1.assign(vec2)

  - ``dot``  Returns the dot product of two Vector3R. Syntax:

      - result = vec1.dot(vec2)

  - ``d3mag``  Returns the d3mag for two Vector3R. Syntax:

      - result = vec1.d3mag()
