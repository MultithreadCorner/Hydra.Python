import unittest
import HydraPython as hp


class TestEventsHost(unittest.TestCase):
    """
    TestEventsHost test class, which tests all the methods available in Host Events class.
    """
    def check_equals(self, event1, event2):
        self.assertEqual(event1.GetNEvents(), event2.GetNEvents())
        for first, second in zip(event1.Events(), event2.Events()):
            self.assertEqual(first, second)

    def test_default_constructor(self):
        h_event = hp.hostEvents10()
        self.assertIsInstance(h_event, hp.hostEvents10, 'Failure: Not an instance of hostEvents10')

    def test_argument_constructor(self):
        h_event = hp.hostEvents10(100)
        self.assertIsInstance(h_event, hp.hostEvents10, 'Failure: Not an instance of hostEvents10')
        self.assertEqual(h_event.GetNEvents(), 100)

    def test_N_host(self):
        h_event1 = hp.hostEvents1(10)
        h_event2 = hp.hostEvents2(10)
        h_event3 = hp.hostEvents3(10)
        h_event4 = hp.hostEvents4(10)
        h_event5 = hp.hostEvents5(10)
        h_event6 = hp.hostEvents6(10)
        h_event7 = hp.hostEvents7(10)
        h_event8 = hp.hostEvents8(10)
        h_event9 = hp.hostEvents9(10)
        h_event10 = hp.hostEvents10(10)
        self.assertIsInstance(h_event1, hp.hostEvents1, 'Failure: Not an instance of hostEvents1')
        self.assertIsInstance(h_event2, hp.hostEvents2, 'Failure: Not an instance of hostEvents2')
        self.assertIsInstance(h_event3, hp.hostEvents3, 'Failure: Not an instance of hostEvents3')
        self.assertIsInstance(h_event4, hp.hostEvents4, 'Failure: Not an instance of hostEvents4')
        self.assertIsInstance(h_event5, hp.hostEvents5, 'Failure: Not an instance of hostEvents5')
        self.assertIsInstance(h_event6, hp.hostEvents6, 'Failure: Not an instance of hostEvents6')
        self.assertIsInstance(h_event7, hp.hostEvents7, 'Failure: Not an instance of hostEvents7')
        self.assertIsInstance(h_event8, hp.hostEvents8, 'Failure: Not an instance of hostEvents8')
        self.assertIsInstance(h_event9, hp.hostEvents9, 'Failure: Not an instance of hostEvents9')
        self.assertIsInstance(h_event10, hp.hostEvents10, 'Failure: Not an instance of hostEvents10')


    def test_copy_constructor_from_host(self):
        h_event = hp.hostEvents10(100)
        h_event_2 = hp.hostEvents10(h_event)
        self.assertIsInstance(h_event_2, hp.hostEvents10, 'Failure: Not an instance of hostEvents10')
        self.check_equals(h_event, h_event_2)

    def test_copy_constructor_from_device(self):
        d_event = hp.deviceEvents10(100)
        h_event = hp.hostEvents10(d_event)
        self.assertIsInstance(h_event, hp.hostEvents10, 'Failure: Not an instance of hostEvents10')
        self.check_equals(d_event, h_event)

    def test_setWeight(self):
        h_event = hp.hostEvents10(100)
        h_event.setWeight(10, 10.838597782598)
        self.assertAlmostEqual(h_event.getWeight(10), 10.838597782598)

    def test_assign_host(self):
        h_event = hp.hostEvents10(100)
        h_event.setWeight(10, 10.838597782598)
        h_event_2 = hp.hostEvents10()
        h_event_2.assign(h_event)
        self.check_equals(h_event, h_event_2)

    def test_assign_device(self):
        h_event = hp.deviceEvents10(100)
        h_event.setWeight(10, 10.838597782598)
        h_event_2 = hp.hostEvents10()
        h_event_2.assign(h_event)
        self.check_equals(h_event, h_event_2)

    def test_get_max_weight(self):
        h_event = hp.hostEvents10(100)
        h_event.SetMaxWeight(10.838597782598)
        self.assertAlmostEqual(h_event.GetMaxWeight(), 10.838597782598)

    def test_flags(self):
        h_event = hp.hostEvents10(100)
        for flag in h_event.Flags():
            self.assertEqual(flag, False)

    def test_weights(self):
        h_event = hp.hostEvents10(100)
        for i in range(100):
            h_event.setWeight(i, 9.876123456745)
        for weight in h_event.Weights():
            self.assertAlmostEqual(weight, 9.876123456745)

    def test_Daughters(self):
        h_event = hp.hostEvents10(100)
        for d in h_event.Daughters(3):
            self.assertAlmostEqual(d, (0.0, 0.0, 0.0, 0.0))

    def test_getitem(self):
        h_event = hp.hostEvents2(10)
        item = h_event[3]
        test = (0.0, (0.0, 0.0, 0.0, 0.0), (0.0, 0.0, 0.0, 0.0))
        self.assertAlmostEqual(item, test)

    def test_unweight(self):
        h_event = hp.hostEvents2(10)
        h_event.setFlag(1, True)
        self.assertEqual(h_event.unweight(123), 10)

    def test_setFlag(self):
        h_event = hp.hostEvents10(100)
        h_event.setFlag(1, True)
        self.assertAlmostEqual(h_event.getFlag(1), True)

    def test_size(self):
        h_event = hp.hostEvents10(100)
        h_event.resize(1000)
        self.assertEqual(h_event.GetNEvents(), 1000)


class TestEventsDevice(unittest.TestCase):
    """
    TestEventsHost test class, which tests all the methods available in Host Events class.
    """
    def check_equals(self, event1, event2):
        self.assertEqual(event1.GetNEvents(), event2.GetNEvents())
        for first, second in zip(event1.Events(), event2.Events()):
            self.assertEqual(first, second)

    def test_default_constructor(self):
        d_event = hp.deviceEvents10()
        self.assertIsInstance(d_event, hp.deviceEvents10, 'Failure: Not an instance of deviceEvents10')

    def test_argument_constructor(self):
        d_event = hp.deviceEvents10(100)
        self.assertIsInstance(d_event, hp.deviceEvents10, 'Failure: Not an instance of deviceEvents10')
        self.assertEqual(d_event.GetNEvents(), 100)

    def test_N_host(self):
        d_event1 = hp.deviceEvents1(10)
        d_event2 = hp.deviceEvents2(10)
        d_event3 = hp.deviceEvents3(10)
        d_event4 = hp.deviceEvents4(10)
        d_event5 = hp.deviceEvents5(10)
        d_event6 = hp.deviceEvents6(10)
        d_event7 = hp.deviceEvents7(10)
        d_event8 = hp.deviceEvents8(10)
        d_event9 = hp.deviceEvents9(10)
        d_event10 = hp.deviceEvents10(10)
        self.assertIsInstance(d_event1, hp.deviceEvents1, 'Failure: Not an instance of deviceEvents1')
        self.assertIsInstance(d_event2, hp.deviceEvents2, 'Failure: Not an instance of deviceEvents2')
        self.assertIsInstance(d_event3, hp.deviceEvents3, 'Failure: Not an instance of deviceEvents3')
        self.assertIsInstance(d_event4, hp.deviceEvents4, 'Failure: Not an instance of deviceEvents4')
        self.assertIsInstance(d_event5, hp.deviceEvents5, 'Failure: Not an instance of deviceEvents5')
        self.assertIsInstance(d_event6, hp.deviceEvents6, 'Failure: Not an instance of deviceEvents6')
        self.assertIsInstance(d_event7, hp.deviceEvents7, 'Failure: Not an instance of deviceEvents7')
        self.assertIsInstance(d_event8, hp.deviceEvents8, 'Failure: Not an instance of deviceEvents8')
        self.assertIsInstance(d_event9, hp.deviceEvents9, 'Failure: Not an instance of deviceEvents9')
        self.assertIsInstance(d_event10, hp.deviceEvents10, 'Failure: Not an instance of deviceEvents10')

    def test_copy_constructor_from_device(self):
        d_event = hp.deviceEvents10(100)
        d_event_2 = hp.deviceEvents10(d_event)
        self.assertIsInstance(d_event_2, hp.deviceEvents10, 'Failure: Not an instance of deviceEvents10')
        self.check_equals(d_event, d_event_2)

    def test_copy_constructor_from_host(self):
        h_event = hp.hostEvents10(100)
        d_event = hp.deviceEvents10(h_event)
        self.assertIsInstance(h_event, hp.hostEvents10, 'Failure: Not an instance of deviceEvents10')
        self.check_equals(d_event, h_event)

    def test_setWeight(self):
        d_event = hp.deviceEvents10(100)
        d_event.setWeight(10, 10.838597782598)
        self.assertAlmostEqual(d_event.getWeight(10), 10.838597782598)

    def test_assign_device(self):
        d_event = hp.deviceEvents10(100)
        d_event.setWeight(10, 10.838597782598)
        d_event_2 = hp.deviceEvents10()
        d_event_2.assign(d_event)
        self.check_equals(d_event, d_event_2)

    def test_assign_host(self):
        d_event = hp.deviceEvents10(100)
        d_event.setWeight(10, 10.838597782598)
        h_event = hp.hostEvents10()
        d_event.assign(h_event)
        self.check_equals(d_event, h_event)

    def test_get_max_weight(self):
        d_event = hp.deviceEvents10(100)
        d_event.SetMaxWeight(10.838597782598)
        self.assertAlmostEqual(d_event.GetMaxWeight(), 10.838597782598)

    def test_flags(self):
        d_event = hp.deviceEvents10(100)
        for flag in d_event.Flags():
            self.assertEqual(flag, False)

    def test_weights(self):
        d_event = hp.deviceEvents10(100)
        for i in range(100):
            d_event.setWeight(i, 9.876123456745)
        for weight in d_event.Weights():
            self.assertAlmostEqual(weight, 9.876123456745)

    def test_Daughters(self):
        d_event = hp.deviceEvents10(100)
        for d in d_event.Daughters(3):
            self.assertAlmostEqual(d, (0.0, 0.0, 0.0, 0.0))

    def test_getitem(self):
        d_event = hp.deviceEvents2(10)
        item = d_event[3]
        test = (0.0, (0.0, 0.0, 0.0, 0.0), (0.0, 0.0, 0.0, 0.0))
        self.assertAlmostEqual(item, test)

    def test_unweight(self):
        d_event = hp.deviceEvents2(10)
        d_event.setFlag(1, True)
        self.assertEqual(d_event.unweight(123), 10)

    def test_setFlag(self):
        d_event = hp.deviceEvents10(100)
        d_event.setFlag(1, True)
        self.assertAlmostEqual(d_event.getFlag(1), True)

    def test_size(self):
        d_event = hp.deviceEvents10(100)
        d_event.resize(1000)
        self.assertEqual(d_event.GetNEvents(), 1000)


if __name__ == '__main__':
    unittest.main()
