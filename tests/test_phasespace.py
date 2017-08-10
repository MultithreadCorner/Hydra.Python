import unittest
import HydraPython as hp
import random
import math


def foo(*data):
    p1 = data[0]
    p2 = data[1]
    p3 = data[2]
    p = p1 + p2 + p3
    q = p2 + p3
    pd = p * p2
    pq = p * q
    qd = q * p2
    mp2 = p.mass2()
    mq2 = q.mass2()
    md2 = p2.mass2()
    return (pd * mq2 - pq * qd) / math.sqrt((pq * pq - mq2 * mp2) * (qd * qd - mq2 * md2))


def random_floats(low, high, size):
    return [random.uniform(low, high) for _ in range(size)]


class TestPhaseSpace(unittest.TestCase):
    """
    TestPhaseSpace test class, which tests all the methods available in PhaseSpace class.
    """

    def check_equals(self, event1, tup):
        self.assertEqual(event1.GetNEvents(), len(tup))
        for first, second in zip(event1.Events(), tup):
            self.assertEqual(first, second)

    def test_default_constructor(self):
        vector_mass = 5.140252
        float_list = [1.1, 1.2, 0.242, 0.8385977]
        ps = hp.PhaseSpace4(vector_mass, float_list)
        self.assertIsInstance(ps, hp.PhaseSpace4, 'Failure: Not an instance of PhaseSpace_4')

    def test_N_PhaseSpace(self):
        vector_mass = 9629.140252
        ps1 = hp.PhaseSpace1(vector_mass, random_floats(0.1, 2.2, 1))
        ps2 = hp.PhaseSpace2(vector_mass, random_floats(0.1, 2.2, 2))
        ps3 = hp.PhaseSpace3(vector_mass, random_floats(0.1, 2.2, 3))
        ps4 = hp.PhaseSpace4(vector_mass, random_floats(0.1, 2.2, 4))
        ps5 = hp.PhaseSpace5(vector_mass, random_floats(0.1, 2.2, 5))
        ps6 = hp.PhaseSpace6(vector_mass, random_floats(0.1, 2.2, 6))
        ps7 = hp.PhaseSpace7(vector_mass, random_floats(0.1, 2.2, 7))
        ps8 = hp.PhaseSpace8(vector_mass, random_floats(0.1, 2.2, 8))
        ps9 = hp.PhaseSpace9(vector_mass, random_floats(0.1, 2.2, 9))
        ps10 = hp.PhaseSpace10(vector_mass, random_floats(0.1, 2.2, 10))
        self.assertIsInstance(ps1, hp.PhaseSpace1, 'Failure: Not an instance of PhaseSpace1')
        self.assertIsInstance(ps2, hp.PhaseSpace2, 'Failure: Not an instance of PhaseSpace2')
        self.assertIsInstance(ps3, hp.PhaseSpace3, 'Failure: Not an instance of PhaseSpace3')
        self.assertIsInstance(ps4, hp.PhaseSpace4, 'Failure: Not an instance of PhaseSpace4')
        self.assertIsInstance(ps5, hp.PhaseSpace5, 'Failure: Not an instance of PhaseSpace5')
        self.assertIsInstance(ps6, hp.PhaseSpace6, 'Failure: Not an instance of PhaseSpace6')
        self.assertIsInstance(ps7, hp.PhaseSpace7, 'Failure: Not an instance of PhaseSpace7')
        self.assertIsInstance(ps8, hp.PhaseSpace8, 'Failure: Not an instance of PhaseSpace8')
        self.assertIsInstance(ps9, hp.PhaseSpace9, 'Failure: Not an instance of PhaseSpace9')
        self.assertIsInstance(ps10, hp.PhaseSpace10, 'Failure: Not an instance of PhaseSpace10')

    def test_seed(self):
        vector_mass = 5.140252
        float_list = [1.1, 1.2, 0.242, 0.8385977]
        ps = hp.PhaseSpace4(vector_mass, float_list)
        ps.SetSeed(123)
        self.assertEqual(123, ps.GetSeed())

    def test_generate_body(self):
        vec4 = hp.Vector4R(5.2795, 0.0, 0.0, 0.0)
        ps = hp.PhaseSpace4(vec4.mass(), [3.096916, 0.493677, 0.13957018, 0.0195018])
        e_host = hp.hostEvents4(3)
        ps.Generatehost(vec4, e_host)
        tup = ((0.0005088938029113608,
                (3.3132858802680483, 0.9817474906791471, 0.005536704420369649, -0.6504735373379763),
                (0.5282720749856796, 0.1548944580532786, 0.00630733261693118, -0.10640643448737479),
                (0.20941853033806007, -0.15242520203160884, 0.024947630249289168, 0.02281357565767795),
                (1.2285235144082114, -0.984216746700817, -0.036791667286590016, 0.7340663961676733)),
               (0.05861767078785821, (3.181438349277635, -0.034345750002169745, 0.6924554981496236, 0.2235777532258999),
                (0.5954612442938403, -0.018288616145264284, -0.05383670420157987, -0.3280613493344976),
                (0.9107110775437897, 0.09954561322034503, -0.7592887348141828, -0.4727431857664381),
                (0.5918893288847361, -0.046911247072911, 0.12066994086613904, 0.5772267818750357)),
               (0.037078448741628245, (3.436518049135502, -0.543157507761998, 1.2016283729299582, 0.6927025090971975),
                (1.1090010467339142, 0.23884482485918399, -0.9089525597618451, -0.32081885086181117),
                (0.551878708090105, 0.31080862812530574, -0.3785298310452291, -0.21261099922089335),
                (0.18210219604047817, -0.006495945222491611, 0.08585401787711583, -0.15927265901449317)))
        self.check_equals(e_host, tup)

        e_device = hp.deviceEvents4(3)
        ps.Generatedevice(vec4, e_device)
        self.check_equals(e_device, tup)

    def test_average_on_body(self):
        vec4 = hp.Vector4R(5.2795, 0.0, 0.0, 0.0)
        p = hp.PhaseSpace4(vec4.mass(), [3.096916, 0.493677, 0.13957018, 0.0195018])
        tup1 = p.AverageONhost(vec4, foo, 10)
        tup2 = (-0.9830497866945361, 0.010451881904521492)
        self.assertAlmostEqual(tup1[0], tup2[0])
        self.assertAlmostEqual(tup1[1], tup2[1])
        # Below will segfault due to GIL
        # tup1 = p.AverageONdevice(vec4, foo, 10)
        # tup2 = (-0.9830497866945361, 0.010451881904521492)
        # self.assertAlmostEqual(tup1[0], tup2[0])
        # self.assertAlmostEqual(tup1[1], tup2[1])


    def test_average_on_body2(self):
        pass

    def test_generate_2(self):
        pass

    def test_evaluate(self):
        pass

    def test_evaluate_2(self):
        pass
        


if __name__ == '__main__':
    unittest.main()
