###############
Project Report:
###############

***************************************************************
Google Summer of Code 2017
***************************************************************

===============================================================
Umbrella Organization: CERN-HSF, CERN’s HEP software foundation
===============================================================

================================================================================================================================
Project: Efficient Python routines for analysis on massively multi-threaded platforms-Python bindings for the Hydra C++ library
================================================================================================================================

Submitted by- Deepanshu Thakur
******************************

I spent my last 3 months working on a `GSoC project`_. My GSoC project was
related with writing the bindings of the Hydra C++ library. Hydra is a header-only
C++ library designed and used to run on Linux platforms. Hydra is a
templated C++11 library designed to perform common High Energy Physics data
analysis on massively parallel platforms. The idea of this GSoC project was to
provide the Python bindings for the Hydra library, so that the Python support
can be added to the overall Hydra project and Python can be used for the prototyping or
development.


.. _GSoC project: https://summerofcode.withgoogle.com/projects/#6669304945704960

My original proposal deliverables and final output ended up looking a little bit
different, and there are some very good reasons for it. The change of
deliverables will become evident in the discussion of the design challenges
and choices later in the report. In the beginning the goal was to write the
bindings for the ``Data Fitting``, ``Random Number Generation``,
``Phase-Space Monte Carlo Simulation``, ``Functor Arithmetic`` and
``Numerical integration``, but we ended up having the bindings for
``Random Number Generation`` and ``Phase-Space Monte Carlo Simulation`` only.
(The remaining classes can be binded with some extra effort but we do
not have time left under the current scope of GSoC, so I have decided to
continue with the project outside the scope of GSoC given my interest in the project.)


Choosing the proper tools
*************************

Let me take you though my three-month journey. First step was to find a tool or
package to write the bindings with. Several options were in principle available to
write the bindings. For example, at the beginning we tried to evaluate the
`SWIG`_ project.
But the problem with SWIG is, it is very complicated to use and second it
does not support the ``variadic templates`` while Hydra underlying
`Thrust library`_ depends heavily on variadic templates. After trying hands
with SWIG and realizing it cannot fulfill our requirements, we turned our
attention to `Boost.Python`_, which looked quite promising. It is a very large
project; but this large and complex suite project has so many tweaks and
hacks so that it can work on almost any compiler. It does add much
complexity and cost. Finally, we turned our attention to the newer `pybind11`_ project.
A quote taken from the pybind11 documentation,

   Boost is an enormously large and complex suite of utility libraries
   that works with almost every C++ compiler in existence. This compatibility
   has its cost: arcane template tricks and workarounds are necessary to
   support the oldest and buggiest of compiler specimens. Now
   that C++11-compatible compilers are widely available, this heavy
   machinery has become an excessively large and unnecessary dependency.

After investigating a lot of things and trying `various programs`_ we decided
to go ahead with pybind11. Next step was to `familiarize myself`_ with pybind11.

.. _SWIG: http://swig.org
.. _Thrust library: https://github.com/andrewcorrigan/thrust-multi-permutation-iterator
.. _Boost.Python: http://www.boost.org/doc/libs/1_65_0/libs/python/doc/html/index.html
.. _pybind11: https://github.com/pybind/pybind11
.. _various programs: https://github.com/Deepanshu2017/boost.python_practise
.. _familiarize myself: https://github.com/Deepanshu2017/pybind11_practise


The Basic design problem
************************

The basic design problem is the `CRTP idiom`_.
The Hydra library relies on the CRTP idiom to avoid runtime overhead. I
investigated a lot about CRTP and it took a little while to finally come up
with a solution that can work with any number of final-state particles (denoted N) often used in Hydra applications.
If you know about CRTP, it is a type of static polymorphism, or compile-time polymorphism. The
idea that I implemented was to take a parameter from Python and, based on that
parameter, I was writing the bindings in a new file, compiling and generating
them on runtime with system calls. Unfortunately, generating bindings at
runtime and compiling them would take a lot of time and so, it is not
feasible for a user to each time wait for a few minutes before actually being
able to use the generated package from Python. We decided to go ahead with a fixed number
of values of N. It means we generate the bindings for a limited number of particles.
Currently the Python bindings for the Hydra classes support up to 10 (N = 10) number of
particles in the final state. Note that we can make that to work with any number we want,
as our binding code is written within a macro, so it is just a matter of
writing additional and trivial-to-add extra calls to make the bindings work for extra values of N.

.. _CRTP idiom: https://en.wikipedia.org/wiki/Curiously_recurring_template_pattern


The Hydra bindings
******************

Now that the approach was decided, we jumped into the bindings of Hydra.
(Finally after so many complications but unfortunately this was not the
end of them.) We decided to bind the most important classes first,
``Random Number Generation`` and ``Phase-Space Monte Carlo Simulation``.
My mentors decided that they will bind the ``Random Number Generation`` while
``Phase-Space Monte Carlo Simulation`` was my responsibility. Rest of the
report will explain more about Phase-Space Monte Carlo Simulation.

“Phase-Space Monte Carlo Simulation” or PhaseSpace C++ Hydra class is useful
to generate the phase space monte carlo simulation.

 The events are generated in the center-of-mass frame, but the decay products
 are finally boosted using the betas of the original particle. The code is
 based on the Raubold and Lynch method as documentd in
 [F. James, Monte Carlo Phase Space, CERN 68-15 (1968)]
 (https://cds.cern/ch/record/275743).

The momentum and energy units are GeV/c and GeV/c^2, respectively. The PhaseSpace Monte
Carlo class depends on the ``Vector3R``,  ``Vector4R`` and ``Events`` classes.
Thus PhaseSpace class cannot be binded before without any of the above classes.

The ``Vector3R`` and ``Vector4R`` classes were binded. There were some problems
like generating ``__eq__`` and ``__nq__`` methods for the Python side but I solved
them by creating ``lambda functions`` and iterating over values and checking
if they satisfy the conditions or not. The ``Vector4R`` or four-vector class
represents a particle. The idea is I first bound the particles class
(the four-vector class) than I had to bind the ``Events`` class that will
hold the Phase Space events generated by the ``PhaseSpace`` class, and then bind the
actual ``PhaseSpace`` class. The ``Events`` class were not so easy to bind
because they were dependent on the ``hydra::multiarray`` and without their
bindings, the ``Events`` class was impossible to bind. Thanks to my mentors
who had already binded these bindings for ``Random`` class with some tweaks on
the pybind11’s bind_container itself. We even faced some design issues of
Events class in Hydra itself. But eventually after solving these problems,
I now had Events class working and I therefore converted the binding code
into a macro, so that we can use Events class with up-to 10 particles.

Now came the actual bindings for the ``PhaseSpace`` class. The ``PhaseSpace``
class have constructors and methods like ``GetSeed``, ``SetSeed``, ``AverageOn``, ``Evaluate`` and ``Generate``.


The ``GetSeed`` and ``SetSeed`` were easy to implement. The remaining 3 methods
have two version, one which accept single mother particle and one which accept
a list of mother particle. I got the success of bindings methods which accept
the single mother particle but was unable to bind the methods that accepts
the list of mother particles. I was trying to pass the list of events object
along with the list of mother particles. I was successfully able to pass the
list of mother particles but wasn’t getting any way to pass the list of Events
without casting each Event object from python object in my bindings code.
(Later I realized that is impossible to do) My mentor wrote the bindings for
methods that accept the list of mother particles. After looking at binding
code I realized. Alas! I was making a very stupid mistake. I had to pass the
``single Events object, not the list of Events object`` which I already did
but never showed to my mentor, thought I’m making a mistake. Well learned a
lesson from this, always show your mentor what you did, even though if you
believe you are wrong. Maybe it could save some of your time. ;)

After completing the PhaseSpace code, I quickly converted the code into macro
for supporting up-to 10 particles.

Now the PhaseSpace class was working perfectly! Next step was to create a
series of test cases, documentation, and of-course the example of
PhaseSpace class in action. The remaining algorithms that I named at the
start of the article are left to implement.


The happy learning
******************

GSoC 2017 was a really very learning experience for me. I learned a lot of
things not only related with programming but related with high energy physics.
I learned about *Monte Carlo Simulations*, and how they can be used to solve
challenging real life problems. I read and studied a research paper
( https://cds.cern.ch/record/275743/files/CERN-68-15.pdf ), learned about
particle decays, learned the insights of C++ variadic templates,
wrote a blog about `CRTP`_, learned how to compile a
Python function and why simple Python functions cannot be used in
multithreaded environments. Most importantly I learned how to structure
a project from scratch, how important documentation and test cases are.


.. _CRTP: https://medium.com/@deepanshu2017/a-curiously-recurring-python-d3a441a58174


Special thanks
**************

Shoutout to my amazing mentors. I would like to thank
Dr. Antonio Augusto Alves Jr. and Dr. Eduardo Rodrigues for being awesome
mentors and for all the time they invested in me during GSoC. I also would
like to thank the CERN-HSF community for their time and helping me whenever I
had a problem. Thank you!
