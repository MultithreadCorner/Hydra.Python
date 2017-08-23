# Licensed under a GNU general public license, see LICENSE.
"""
Author: Deepanshu Thakur
Date  : Aug 21, 2017
"""

# -----------------------------------------------------------------------------
# Import statements
# -----------------------------------------------------------------------------
import unittest

from HydraPython import (host_events_1,
                         host_events_2,
                         host_events_3,
                         host_events_4,
                         host_events_5,
                         host_events_6,
                         host_events_7,
                         host_events_8,
                         host_events_9,
                         host_events_10)
from HydraPython import (device_events_1,
                         device_events_2,
                         device_events_3,
                         device_events_4,
                         device_events_5,
                         device_events_6,
                         device_events_7,
                         device_events_8,
                         device_events_9,
                         device_events_10)


# -----------------------------------------------------------------------------
# Actual tests
# -----------------------------------------------------------------------------
class TestEventsHost(unittest.TestCase):
    """
    TestEventsHost test class, which tests all the methods available in Host Events class.
    """
    def check_equals(self, event1, event2):
        self.assertEqual(event1.GetNEvents(), event2.GetNEvents())
        for first, second in zip(event1.Events(), event2.Events()):
            self.assertEqual(first, second)

    def test_default_constructor(self):
        h_event = host_events_10()
        self.assertIsInstance(h_event, host_events_10, 'Failure: Not an instance of host_events_10')

    def test_argument_constructor(self):
        h_event = host_events_10(100)
        self.assertIsInstance(h_event, host_events_10, 'Failure: Not an instance of host_events_10')
        self.assertEqual(h_event.GetNEvents(), 100)

    def test_N_host(self):
        h_event1 = host_events_1(10)
        h_event2 = host_events_2(10)
        h_event3 = host_events_3(10)
        h_event4 = host_events_4(10)
        h_event5 = host_events_5(10)
        h_event6 = host_events_6(10)
        h_event7 = host_events_7(10)
        h_event8 = host_events_8(10)
        h_event9 = host_events_9(10)
        h_event10 = host_events_10(10)
        self.assertIsInstance(h_event1, host_events_1, 'Failure: Not an instance of host_events_1')
        self.assertIsInstance(h_event2, host_events_2, 'Failure: Not an instance of host_events_2')
        self.assertIsInstance(h_event3, host_events_3, 'Failure: Not an instance of host_events_3')
        self.assertIsInstance(h_event4, host_events_4, 'Failure: Not an instance of host_events_4')
        self.assertIsInstance(h_event5, host_events_5, 'Failure: Not an instance of host_events_5')
        self.assertIsInstance(h_event6, host_events_6, 'Failure: Not an instance of host_events_6')
        self.assertIsInstance(h_event7, host_events_7, 'Failure: Not an instance of host_events_7')
        self.assertIsInstance(h_event8, host_events_8, 'Failure: Not an instance of host_events_8')
        self.assertIsInstance(h_event9, host_events_9, 'Failure: Not an instance of host_events_9')
        self.assertIsInstance(h_event10, host_events_10, 'Failure: Not an instance of host_events_10')


    def test_copy_constructor_from_host(self):
        h_event = host_events_10(100)
        h_event_2 = host_events_10(h_event)
        self.assertIsInstance(h_event_2, host_events_10, 'Failure: Not an instance of host_events_10')
        self.check_equals(h_event, h_event_2)

    def test_copy_constructor_from_device(self):
        d_event = device_events_10(100)
        h_event = host_events_10(d_event)
        self.assertIsInstance(h_event, host_events_10, 'Failure: Not an instance of host_events_10')
        self.check_equals(d_event, h_event)

    def test_setWeight(self):
        h_event = host_events_10(100)
        h_event.setWeight(10, 10.838597782598)
        self.assertAlmostEqual(h_event.getWeight(10), 10.838597782598)

    def test_assign_host(self):
        h_event = host_events_10(100)
        h_event.setWeight(10, 10.838597782598)
        h_event_2 = host_events_10()
        h_event_2.assign(h_event)
        self.check_equals(h_event, h_event_2)

    def test_assign_device(self):
        h_event = device_events_10(100)
        h_event.setWeight(10, 10.838597782598)
        h_event_2 = host_events_10()
        h_event_2.assign(h_event)
        self.check_equals(h_event, h_event_2)

    def test_get_max_weight(self):
        h_event = host_events_10(100)
        h_event.SetMaxWeight(10.838597782598)
        self.assertAlmostEqual(h_event.GetMaxWeight(), 10.838597782598)

    def test_flags(self):
        h_event = host_events_10(100)
        for flag in h_event.Flags():
            self.assertEqual(flag, False)

    def test_weights(self):
        h_event = host_events_10(100)
        for i in range(100):
            h_event.setWeight(i, 9.876123456745)
        for weight in h_event.Weights():
            self.assertAlmostEqual(weight, 9.876123456745)

    def test_Daughters(self):
        h_event = host_events_10(100)
        for d in h_event.Daughters(3):
            self.assertAlmostEqual(d, (0.0, 0.0, 0.0, 0.0))

    def test_getitem(self):
        h_event = host_events_2(10)
        item = h_event[3]
        test = (0.0, (0.0, 0.0, 0.0, 0.0), (0.0, 0.0, 0.0, 0.0))
        self.assertAlmostEqual(item, test)

    def test_Unweight(self):
        h_event = host_events_2(10)
        h_event.setFlag(1, True)
        self.assertEqual(h_event.Unweight(123), 10)

    def test_setFlag(self):
        h_event = host_events_10(100)
        h_event.setFlag(1, True)
        self.assertAlmostEqual(h_event.getFlag(1), True)

    def test_size(self):
        h_event = host_events_10(100)
        h_event.resize(1000)
        self.assertEqual(h_event.GetNEvents(), 1000)


class TestEventsDevice(unittest.TestCase):
    """
    TestEventsDevice test class, which tests all the methods available in Host Events class.
    """
    def check_equals(self, event1, event2):
        self.assertEqual(event1.GetNEvents(), event2.GetNEvents())
        for first, second in zip(event1.Events(), event2.Events()):
            self.assertEqual(first, second)

    def test_default_constructor(self):
        d_event = device_events_10()
        self.assertIsInstance(d_event, device_events_10, 'Failure: Not an instance of device_events_10')

    def test_argument_constructor(self):
        d_event = device_events_10(100)
        self.assertIsInstance(d_event, device_events_10, 'Failure: Not an instance of device_events_10')
        self.assertEqual(d_event.GetNEvents(), 100)

    def test_N_host(self):
        d_event1 = device_events_1(10)
        d_event2 = device_events_2(10)
        d_event3 = device_events_3(10)
        d_event4 = device_events_4(10)
        d_event5 = device_events_5(10)
        d_event6 = device_events_6(10)
        d_event7 = device_events_7(10)
        d_event8 = device_events_8(10)
        d_event9 = device_events_9(10)
        d_event10 = device_events_10(10)
        self.assertIsInstance(d_event1, device_events_1, 'Failure: Not an instance of device_events_1')
        self.assertIsInstance(d_event2, device_events_2, 'Failure: Not an instance of device_events_2')
        self.assertIsInstance(d_event3, device_events_3, 'Failure: Not an instance of device_events_3')
        self.assertIsInstance(d_event4, device_events_4, 'Failure: Not an instance of device_events_4')
        self.assertIsInstance(d_event5, device_events_5, 'Failure: Not an instance of device_events_5')
        self.assertIsInstance(d_event6, device_events_6, 'Failure: Not an instance of device_events_6')
        self.assertIsInstance(d_event7, device_events_7, 'Failure: Not an instance of device_events_7')
        self.assertIsInstance(d_event8, device_events_8, 'Failure: Not an instance of device_events_8')
        self.assertIsInstance(d_event9, device_events_9, 'Failure: Not an instance of device_events_9')
        self.assertIsInstance(d_event10, device_events_10, 'Failure: Not an instance of device_events_10')

    def test_copy_constructor_from_device(self):
        d_event = device_events_10(100)
        d_event_2 = device_events_10(d_event)
        self.assertIsInstance(d_event_2, device_events_10, 'Failure: Not an instance of device_events_10')
        self.check_equals(d_event, d_event_2)

    def test_copy_constructor_from_host(self):
        h_event = host_events_10(100)
        d_event = device_events_10(h_event)
        self.assertIsInstance(h_event, host_events_10, 'Failure: Not an instance of device_events_10')
        self.check_equals(d_event, h_event)

    def test_setWeight(self):
        d_event = device_events_10(100)
        d_event.setWeight(10, 10.838597782598)
        self.assertAlmostEqual(d_event.getWeight(10), 10.838597782598)

    def test_assign_device(self):
        d_event = device_events_10(100)
        d_event.setWeight(10, 10.838597782598)
        d_event_2 = device_events_10()
        d_event_2.assign(d_event)
        self.check_equals(d_event, d_event_2)

    def test_assign_host(self):
        d_event = device_events_10(100)
        d_event.setWeight(10, 10.838597782598)
        h_event = host_events_10()
        d_event.assign(h_event)
        self.check_equals(d_event, h_event)

    def test_get_max_weight(self):
        d_event = device_events_10(100)
        d_event.SetMaxWeight(10.838597782598)
        self.assertAlmostEqual(d_event.GetMaxWeight(), 10.838597782598)

    def test_flags(self):
        d_event = device_events_10(100)
        for flag in d_event.Flags():
            self.assertEqual(flag, False)

    def test_weights(self):
        d_event = device_events_10(100)
        for i in range(100):
            d_event.setWeight(i, 9.876123456745)
        for weight in d_event.Weights():
            self.assertAlmostEqual(weight, 9.876123456745)

    def test_Daughters(self):
        d_event = device_events_10(100)
        for d in d_event.Daughters(3):
            self.assertAlmostEqual(d, (0.0, 0.0, 0.0, 0.0))

    def test_getitem(self):
        d_event = device_events_2(10)
        item = d_event[3]
        test = (0.0, (0.0, 0.0, 0.0, 0.0), (0.0, 0.0, 0.0, 0.0))
        self.assertAlmostEqual(item, test)

    def test_Unweight(self):
        d_event = device_events_2(10)
        d_event.setFlag(1, True)
        self.assertEqual(d_event.Unweight(123), 10)

    def test_setFlag(self):
        d_event = device_events_10(100)
        d_event.setFlag(1, True)
        self.assertAlmostEqual(d_event.getFlag(1), True)

    def test_size(self):
        d_event = device_events_10(100)
        d_event.resize(1000)
        self.assertEqual(d_event.GetNEvents(), 1000)


if __name__ == '__main__':
    unittest.main()
