# Licensed under a GNU general public license, see LICENSE.

# -----------------------------------------------------------------------------
# Import statements
# -----------------------------------------------------------------------------
import unittest

from HydraPython import (hostEvents1,
                         hostEvents2,
                         hostEvents3,
                         hostEvents4,
                         hostEvents5,
                         hostEvents6,
                         hostEvents7,
                         hostEvents8,
                         hostEvents9,
                         hostEvents10)
from HydraPython import (deviceEvents1,
                         deviceEvents2,
                         deviceEvents3,
                         deviceEvents4,
                         deviceEvents5,
                         deviceEvents6,
                         deviceEvents7,
                         deviceEvents8,
                         deviceEvents9,
                         deviceEvents10)


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
        h_event = hostEvents10()
        self.assertIsInstance(h_event, hostEvents10, 'Failure: Not an instance of hostEvents10')

    def test_argument_constructor(self):
        h_event = hostEvents10(100)
        self.assertIsInstance(h_event, hostEvents10, 'Failure: Not an instance of hostEvents10')
        self.assertEqual(h_event.GetNEvents(), 100)

    def test_N_host(self):
        h_event1 = hostEvents1(10)
        h_event2 = hostEvents2(10)
        h_event3 = hostEvents3(10)
        h_event4 = hostEvents4(10)
        h_event5 = hostEvents5(10)
        h_event6 = hostEvents6(10)
        h_event7 = hostEvents7(10)
        h_event8 = hostEvents8(10)
        h_event9 = hostEvents9(10)
        h_event10 = hostEvents10(10)
        self.assertIsInstance(h_event1, hostEvents1, 'Failure: Not an instance of hostEvents1')
        self.assertIsInstance(h_event2, hostEvents2, 'Failure: Not an instance of hostEvents2')
        self.assertIsInstance(h_event3, hostEvents3, 'Failure: Not an instance of hostEvents3')
        self.assertIsInstance(h_event4, hostEvents4, 'Failure: Not an instance of hostEvents4')
        self.assertIsInstance(h_event5, hostEvents5, 'Failure: Not an instance of hostEvents5')
        self.assertIsInstance(h_event6, hostEvents6, 'Failure: Not an instance of hostEvents6')
        self.assertIsInstance(h_event7, hostEvents7, 'Failure: Not an instance of hostEvents7')
        self.assertIsInstance(h_event8, hostEvents8, 'Failure: Not an instance of hostEvents8')
        self.assertIsInstance(h_event9, hostEvents9, 'Failure: Not an instance of hostEvents9')
        self.assertIsInstance(h_event10, hostEvents10, 'Failure: Not an instance of hostEvents10')


    def test_copy_constructor_from_host(self):
        h_event = hostEvents10(100)
        h_event_2 = hostEvents10(h_event)
        self.assertIsInstance(h_event_2, hostEvents10, 'Failure: Not an instance of hostEvents10')
        self.check_equals(h_event, h_event_2)

    def test_copy_constructor_from_device(self):
        d_event = deviceEvents10(100)
        h_event = hostEvents10(d_event)
        self.assertIsInstance(h_event, hostEvents10, 'Failure: Not an instance of hostEvents10')
        self.check_equals(d_event, h_event)

    def test_setWeight(self):
        h_event = hostEvents10(100)
        h_event.setWeight(10, 10.838597782598)
        self.assertAlmostEqual(h_event.getWeight(10), 10.838597782598)

    def test_assign_host(self):
        h_event = hostEvents10(100)
        h_event.setWeight(10, 10.838597782598)
        h_event_2 = hostEvents10()
        h_event_2.assign(h_event)
        self.check_equals(h_event, h_event_2)

    def test_assign_device(self):
        h_event = deviceEvents10(100)
        h_event.setWeight(10, 10.838597782598)
        h_event_2 = hostEvents10()
        h_event_2.assign(h_event)
        self.check_equals(h_event, h_event_2)

    def test_get_max_weight(self):
        h_event = hostEvents10(100)
        h_event.SetMaxWeight(10.838597782598)
        self.assertAlmostEqual(h_event.GetMaxWeight(), 10.838597782598)

    def test_flags(self):
        h_event = hostEvents10(100)
        for flag in h_event.Flags():
            self.assertEqual(flag, False)

    def test_weights(self):
        h_event = hostEvents10(100)
        for i in range(100):
            h_event.setWeight(i, 9.876123456745)
        for weight in h_event.Weights():
            self.assertAlmostEqual(weight, 9.876123456745)

    def test_Daughters(self):
        h_event = hostEvents10(100)
        for d in h_event.Daughters(3):
            self.assertAlmostEqual(d, (0.0, 0.0, 0.0, 0.0))

    def test_getitem(self):
        h_event = hostEvents2(10)
        item = h_event[3]
        test = (0.0, (0.0, 0.0, 0.0, 0.0), (0.0, 0.0, 0.0, 0.0))
        self.assertAlmostEqual(item, test)

    def test_unweight(self):
        h_event = hostEvents2(10)
        h_event.setFlag(1, True)
        self.assertEqual(h_event.unweight(123), 10)

    def test_setFlag(self):
        h_event = hostEvents10(100)
        h_event.setFlag(1, True)
        self.assertAlmostEqual(h_event.getFlag(1), True)

    def test_size(self):
        h_event = hostEvents10(100)
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
        d_event = deviceEvents10()
        self.assertIsInstance(d_event, deviceEvents10, 'Failure: Not an instance of deviceEvents10')

    def test_argument_constructor(self):
        d_event = deviceEvents10(100)
        self.assertIsInstance(d_event, deviceEvents10, 'Failure: Not an instance of deviceEvents10')
        self.assertEqual(d_event.GetNEvents(), 100)

    def test_N_host(self):
        d_event1 = deviceEvents1(10)
        d_event2 = deviceEvents2(10)
        d_event3 = deviceEvents3(10)
        d_event4 = deviceEvents4(10)
        d_event5 = deviceEvents5(10)
        d_event6 = deviceEvents6(10)
        d_event7 = deviceEvents7(10)
        d_event8 = deviceEvents8(10)
        d_event9 = deviceEvents9(10)
        d_event10 = deviceEvents10(10)
        self.assertIsInstance(d_event1, deviceEvents1, 'Failure: Not an instance of deviceEvents1')
        self.assertIsInstance(d_event2, deviceEvents2, 'Failure: Not an instance of deviceEvents2')
        self.assertIsInstance(d_event3, deviceEvents3, 'Failure: Not an instance of deviceEvents3')
        self.assertIsInstance(d_event4, deviceEvents4, 'Failure: Not an instance of deviceEvents4')
        self.assertIsInstance(d_event5, deviceEvents5, 'Failure: Not an instance of deviceEvents5')
        self.assertIsInstance(d_event6, deviceEvents6, 'Failure: Not an instance of deviceEvents6')
        self.assertIsInstance(d_event7, deviceEvents7, 'Failure: Not an instance of deviceEvents7')
        self.assertIsInstance(d_event8, deviceEvents8, 'Failure: Not an instance of deviceEvents8')
        self.assertIsInstance(d_event9, deviceEvents9, 'Failure: Not an instance of deviceEvents9')
        self.assertIsInstance(d_event10, deviceEvents10, 'Failure: Not an instance of deviceEvents10')

    def test_copy_constructor_from_device(self):
        d_event = deviceEvents10(100)
        d_event_2 = deviceEvents10(d_event)
        self.assertIsInstance(d_event_2, deviceEvents10, 'Failure: Not an instance of deviceEvents10')
        self.check_equals(d_event, d_event_2)

    def test_copy_constructor_from_host(self):
        h_event = hostEvents10(100)
        d_event = deviceEvents10(h_event)
        self.assertIsInstance(h_event, hostEvents10, 'Failure: Not an instance of deviceEvents10')
        self.check_equals(d_event, h_event)

    def test_setWeight(self):
        d_event = deviceEvents10(100)
        d_event.setWeight(10, 10.838597782598)
        self.assertAlmostEqual(d_event.getWeight(10), 10.838597782598)

    def test_assign_device(self):
        d_event = deviceEvents10(100)
        d_event.setWeight(10, 10.838597782598)
        d_event_2 = deviceEvents10()
        d_event_2.assign(d_event)
        self.check_equals(d_event, d_event_2)

    def test_assign_host(self):
        d_event = deviceEvents10(100)
        d_event.setWeight(10, 10.838597782598)
        h_event = hostEvents10()
        d_event.assign(h_event)
        self.check_equals(d_event, h_event)

    def test_get_max_weight(self):
        d_event = deviceEvents10(100)
        d_event.SetMaxWeight(10.838597782598)
        self.assertAlmostEqual(d_event.GetMaxWeight(), 10.838597782598)

    def test_flags(self):
        d_event = deviceEvents10(100)
        for flag in d_event.Flags():
            self.assertEqual(flag, False)

    def test_weights(self):
        d_event = deviceEvents10(100)
        for i in range(100):
            d_event.setWeight(i, 9.876123456745)
        for weight in d_event.Weights():
            self.assertAlmostEqual(weight, 9.876123456745)

    def test_Daughters(self):
        d_event = deviceEvents10(100)
        for d in d_event.Daughters(3):
            self.assertAlmostEqual(d, (0.0, 0.0, 0.0, 0.0))

    def test_getitem(self):
        d_event = deviceEvents2(10)
        item = d_event[3]
        test = (0.0, (0.0, 0.0, 0.0, 0.0), (0.0, 0.0, 0.0, 0.0))
        self.assertAlmostEqual(item, test)

    def test_unweight(self):
        d_event = deviceEvents2(10)
        d_event.setFlag(1, True)
        self.assertEqual(d_event.unweight(123), 10)

    def test_setFlag(self):
        d_event = deviceEvents10(100)
        d_event.setFlag(1, True)
        self.assertAlmostEqual(d_event.getFlag(1), True)

    def test_size(self):
        d_event = deviceEvents10(100)
        d_event.resize(1000)
        self.assertEqual(d_event.GetNEvents(), 1000)


if __name__ == '__main__':
    unittest.main()
