.. Events:

Events Class
##############

There are two types of Events one that run on ``host`` and ``device``. Events
container currently supports up to (N=10) particles in any number of Events.
Both Host and Device Event classes adds number (1 to 10) as their
suffix to create Event for that number of particles and the type
(host or device) is added as their prefix.

HOST
====

The host is generally defined as the CPU. This class is a wrapper of C++
Events class that will work on CPU. This class is a container to hold
the position of particles. We have 4 types of constructors
to instantiate the Events class:

- Default empty constructor
- Constructor with number of events
- Copy constructor (from host to host)
- Copy constructor (from device to host)

.. code-block:: python

    import HydraPython as hp

    h_events_5 = hp.hostEvents5()  # construc host Event with 5 particles and 0 Events
    print (h_events_5.size())  # 0

    h_events_7_100 = hp.hostEvents7(100)
    print (h_events_7_100.size())  # 100


The ``hostEventsN`` object can be copy constructed with the ``hostEventsN``
or ``deviceEventsN`` object.

.. code-block:: python

    import HydraPython as hp
    h_events_3 = hp.hostEvents3(4)
    print (list(h_events_3.Flags()))  # [False, False, False, False]

    h_events_3.setFlag(1, True)
    h_events_3_copy = hp.hostEvents3(h_events_3)
    print(list(h_events_3_copy.Flags()))  # [False, True, False, False]

The ``setFlags`` method as demonstrated above can be used to set the
particular Flag value and the getFlag method can be used the get the
particular flag value with the index.

.. code-block:: python

    h_event = hp.hostEvents5(8)
    h_event.setFlag(1, True)
    print (h_event.getFlag(1))  # True

The host Events class provides a ``assign`` method to assign or copy the Events
object. This is very useful method to avoid the nasty bugs for example:

.. code-block:: python

    h_event = hp.hostEvents5(10)
    h_event2 = hp.hostEvents5()

    # Do things and later in code ...
    h_event2.assign(h_event)
    # This will create the exact same copy of the h_event in h_event2

The host Events class also provides a method to set the Maximum weight of the
Events. The method is useful to set the maximum weight. The complete method
list provided by the Event classes can be found on [#f1]_.

The Events classes also provide a pythonic way to access the events with the
``[]`` operator. For example an event value can be access like this.

.. code-block:: python

    event = hp.hostEvents5(5)
    print(event[1])  # (0.0, (0.0, 0.0, 0.0, 0.0), (0.0, 0.0, 0.0, 0.0), (0.0, 0.0, 0.0, 0.0), (0.0, 0.0, 0.0, 0.0), (0.0, 0.0, 0.0, 0.0))


DEVICE
======

The device is defined as the GPU and any other multicore CPU. The device Event
class is exactly similar to the Host Events class but the only major difference
is HOST Events class work on the single CPU while the DEVICE Events class work
on the multiple CPU's or the GPU devices.

In HydraPython the device Events classes supports all the method defined by
the host Event classes. The device Event class have ``device`` as their prefix
and the number of particle N (up to 10) as their suffix.

It is only the fact that all the methods that can be used with the host can
also be used with the device classes, even the name of the methods are same,
just the declaration of the objects is different. So if you want to create a
device object of particle 7 you will do something like this,

.. code-block:: python

    import HydraPython
    device_event_with_7_particle = HydraPython.deviceEvents7()

    # This will create a device Events with 0 states and 7 particles.


The complete list of the classes in the Events container can be found on [#f2]_.

.. [#f1] The method list for Events classes

  - ``assign``  Assigns one Events content to other Events. Syntax:

      - event2.assign(event1)  # event1's content will be assigned to event2.
      - event2_device.assign(event1_host)  # event1_host's (which is a host event) content will be assigned to event2_device (which is a device event)
      - event2_host.assign(event1_device)  # event1_device's (which is a device event) content will be assigned to event2_host (which is a host event)
      - event2_device.assign(event1_device)  # event1_device's (which is a device event) content will be assigned to event2_device (which is also a device event)
      - event2_host.assign(event1_host)  # event1_host's (which is a host event) content will be assigned to event2_host (which is also a host event)

  - ``GetMaxWeight`` Gets the maximum weight of the Event's container. Syntax:

      - event.GetMaxWeight()
      - event_host.GetMaxWeight()  # Get's the maximum weight of the host Event's container.
      - event_device.GetMaxWeight()  # Get's the maximum weight of the device Event's container.

  - ``GetNEvents`` Gets the number of events. Syntax:

      - event.GetNEvents()
      - event_host.GetNEvents()  # Get's the number of events in host Event's container.
      - event_device.GetNEvents()  # Get's the number of events in device Event's container.

  - ``Flags``  This method returns the iterator of flags. Syntax:

      - iterator = event.Flags()  # event can be of host or device type and than can be used to iterator over the values.
        For example ``for flag in iterator: print(flag)``

  - ``Weights``  This method returns the iterator of weights. Syntax:

      - iterator = event.Weights()  # event can be of host or device type and than can be used to iterator over the values.
        For example ``for weight in iterator: print(weight)``

  - ``Daughters``  This method returns the iterator of daughter at given index (index <= number of particle). Syntax:

      - iterator = event.Daughters(i)  # event can be of host or device type and than can be used to iterator over the values.
        For example ``for daughter in iterator: print(daughter)`` Will print out the ith particle state in all the events.

  - ``Events``  This method returns the iterator of events. Syntax:

      - iterator = event.Events()  # event can be of host or device type and than can be used to iterator over the values.
        For example ``for e in iterator: print(e)`` Will print out all the events where each event will have the N daughters and the weight of the event.

  - ``SetMaxWeight``  Sets the maximum weight of the events. Syntax:

      - event.SetMaxWeight(float)  # Sets the maximum weight of the events.

  - ``resize``  resize the number of events. Syntax:

      - event.resize(knumber)  # Sets the events container to hold ``knumber`` of events.

  - ``size``  Gets the size or the number of events in the container. Syntax:

      - event.size()  # Return the total number of events.

  - ``unweight``  Unweight the events with the given seed. Syntax:

      - events.unweight(seed)

  - ``setFlag``  Set the particular flag with given value. Syntax:

      - event.setFlag(idx, bool)

  - ``getFlag``  Gets the particular flag value. Syntax:

      - events.getFlag(idx)

  - ``setWeight``  Set the particular event's weight given value. Syntax:

      - event.setWeight(idx, float)

  - ``getWeight``  Gets the particular event's weight. Syntax:

      - event.getWeight(idx)



.. [#f2] The list of Events classes

  - ``hostEvents1``  Generate 1 particle Event. Syntax:

      - h_event = hp.hostEvents1(entries)

  - ``hostEvents2``  Generate 2 particle Event. Syntax:

      - h_event = hp.hostEvents2(entries)

  - ``hostEvents3``  Generate 3 particle Event. Syntax:

      - h_event = hp.hostEvents3(entries)

  - ``hostEvents4``  Generate 4 particle Event. Syntax:

      - h_event = hp.hostEvents4(entries)

  - ``hostEvents5``  Generate 5 particle Event. Syntax:

      - h_event = hp.hostEvents5(entries)

  - ``hostEvents6``  Generate 6 particle Event. Syntax:

      - h_event = hp.hostEvents6(entries)

  - ``hostEvents7``  Generate 7 particle Event. Syntax:

      - h_event = hp.hostEvents7(entries)

  - ``hostEvents8``  Generate 8 particle Event. Syntax:

      - h_event = hp.hostEvents8(entries)

  - ``hostEvents9``  Generate 9 particle Event. Syntax:

      - h_event = hp.hostEvents9(entries)

  - ``hostEvents10``  Generate 10 particle Event. Syntax:

      - h_event = hp.hostEvents10(entries)

  - ``deviceEvents1``  Generate 1 particle Event. Syntax:

      - d_event = hp.hostEvents1(entries)

  - ``deviceEvents2``  Generate 2 particle Event. Syntax:

      - d_event = hp.hostEvents2(entries)

  - ``deviceEvents3``  Generate 3 particle Event. Syntax:

      - d_event = hp.hostEvents3(entries)

  - ``deviceEvents4``  Generate 4 particle Event. Syntax:

      - d_event = hp.hostEvents4(entries)

  - ``deviceEvents5``  Generate 5 particle Event. Syntax:

      - d_event = hp.hostEvents5(entries)

  - ``deviceEvents6``  Generate 6 particle Event. Syntax:

      - d_event = hp.hostEvents6(entries)

  - ``deviceEvents7``  Generate 7 particle Event. Syntax:

      - d_event = hp.hostEvents7(entries)

  - ``deviceEvents8``  Generate 8 particle Event. Syntax:

      - d_event = hp.hostEvents8(entries)

  - ``deviceEvents9``  Generate 9 particle Event. Syntax:

      - d_event = hp.hostEvents9(entries)

  - ``devicevents10``  Generate 10 particle Event. Syntax:

      - d_event = hp.hostEvents10(entries)
