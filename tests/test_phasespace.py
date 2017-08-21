# Licensed under a GNU general public license, see LICENSE.

# -----------------------------------------------------------------------------
# Import statements
# -----------------------------------------------------------------------------
import unittest
import random
import math

import HydraPython as hypy


def functor(*four_vector):
    p1 = four_vector[0]
    p2 = four_vector[1]
    p3 = four_vector[2]

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


# -----------------------------------------------------------------------------
# Actual tests
# -----------------------------------------------------------------------------
class TestPhaseSpace(unittest.TestCase):
    """
    TestPhaseSpace test class, which tests all the methods available in PhaseSpace class.
    """

    def check_tuple(self, a, b):
        for i, j in zip(a, b):
            if isinstance(i, (list, tuple)):
                self.check_tuple(i, j)
            else:
                self.assertAlmostEqual(i, j)

    def check_equals(self, event1, tup):
        self.assertEqual(event1.GetNEvents(), len(tup))
        for first, second in zip(event1.Events(), tup):
            self.check_tuple(first, second)

    def test_default_constructor(self):
        vector_mass = 5.140252
        float_list = [1.1, 1.2, 0.242, 0.8385977]
        ps = hypy.PhaseSpace4(vector_mass, float_list)
        self.assertIsInstance(ps, hypy.PhaseSpace4, 'Failure: Not an instance of PhaseSpace_4')

    def test_N_PhaseSpace(self):
        vector_mass = 9629.140252
        # ps1 = hypy.PhaseSpace1(vector_mass, random_floats(0.1, 2.2, 1))
        ps2 = hypy.PhaseSpace2(vector_mass, random_floats(0.1, 2.2, 2))
        ps3 = hypy.PhaseSpace3(vector_mass, random_floats(0.1, 2.2, 3))
        ps4 = hypy.PhaseSpace4(vector_mass, random_floats(0.1, 2.2, 4))
        ps5 = hypy.PhaseSpace5(vector_mass, random_floats(0.1, 2.2, 5))
        ps6 = hypy.PhaseSpace6(vector_mass, random_floats(0.1, 2.2, 6))
        ps7 = hypy.PhaseSpace7(vector_mass, random_floats(0.1, 2.2, 7))
        ps8 = hypy.PhaseSpace8(vector_mass, random_floats(0.1, 2.2, 8))
        ps9 = hypy.PhaseSpace9(vector_mass, random_floats(0.1, 2.2, 9))
        ps10 = hypy.PhaseSpace10(vector_mass, random_floats(0.1, 2.2, 10))
        # self.assertIsInstance(ps1, hypy.PhaseSpace1, 'Failure: Not an instance of PhaseSpace1')
        self.assertIsInstance(ps2, hypy.PhaseSpace2, 'Failure: Not an instance of PhaseSpace2')
        self.assertIsInstance(ps3, hypy.PhaseSpace3, 'Failure: Not an instance of PhaseSpace3')
        self.assertIsInstance(ps4, hypy.PhaseSpace4, 'Failure: Not an instance of PhaseSpace4')
        self.assertIsInstance(ps5, hypy.PhaseSpace5, 'Failure: Not an instance of PhaseSpace5')
        self.assertIsInstance(ps6, hypy.PhaseSpace6, 'Failure: Not an instance of PhaseSpace6')
        self.assertIsInstance(ps7, hypy.PhaseSpace7, 'Failure: Not an instance of PhaseSpace7')
        self.assertIsInstance(ps8, hypy.PhaseSpace8, 'Failure: Not an instance of PhaseSpace8')
        self.assertIsInstance(ps9, hypy.PhaseSpace9, 'Failure: Not an instance of PhaseSpace9')
        self.assertIsInstance(ps10, hypy.PhaseSpace10, 'Failure: Not an instance of PhaseSpace10')

    def test_seed(self):
        vector_mass = 5.140252
        float_list = [1.1, 1.2, 0.242, 0.8385977]
        ps = hypy.PhaseSpace4(vector_mass, float_list)
        ps.SetSeed(123)
        self.assertEqual(123, ps.GetSeed())

    def test_generator_1(self):
        vec4 = hypy.Vector4R(5.2795, 0.0, 0.0, 0.0)
        phsp = hypy.PhaseSpace4(vec4.mass(), [3.096916, 0.493677, 0.13957018, 0.0195018])
        e_host = hypy.host_events_4(3)
        phsp.GenerateOnhost(vec4, e_host)
        tup = ((0.00050889380,
                (3.313285880268, 0.981747490679, 0.005536704420, -0.650473537337),
                (0.528272074985, 0.154894458053, 0.006307332616, -0.106406434487),
                (0.209418530338, -0.152425202031, 0.024947630249, 0.022813575657),
                (1.228523514408, -0.984216746700, -0.036791667286, 0.734066396167)),
               (0.058617670787, (3.181438349277, -0.034345750002, 0.692455498149, 0.223577753225),
                (0.595461244293, -0.018288616145, -0.053836704201, -0.328061349334),
                (0.910711077543, 0.099545613220, -0.759288734814, -0.472743185766),
                (0.591889328884, -0.046911247072, 0.120669940866, 0.577226781875)),
               (0.037078448741, (3.436518049135, -0.543157507761, 1.201628372929, 0.692702509097),
                (1.109001046733, 0.238844824859, -0.908952559761, -0.320818850861),
                (0.551878708090, 0.310808628125, -0.378529831045, -0.212610999220),
                (0.182102196040, -0.006495945222, 0.085854017877, -0.159272659014)))
        self.check_equals(e_host, tup)

        e_device = hypy.device_events_4(3)
        phsp.GenerateOndevice(vec4, e_device)
        self.check_equals(e_device, tup)

    def test_average_on(self):
        vec4 = hypy.Vector4R(5.2795, 0.0, 0.0, 0.0)
        p = hypy.PhaseSpace4(vec4.mass(), [3.096916, 0.493677, 0.13957018, 0.0195018])
        tup1 = p.AverageOnhost(vec4, functor, 10)
        tup2 = (-0.983049786694, 0.010451881904)
        self.assertAlmostEqual(tup1[0], tup2[0])
        self.assertAlmostEqual(tup1[1], tup2[1])
        # Below will segfault due to GIL
        # tup1 = p.AverageOndevice(vec4, foo, 10)
        # tup2 = (-0.983049786694, 0.010451881904)
        # self.assertAlmostEqual(tup1[0], tup2[0])
        # self.assertAlmostEqual(tup1[1], tup2[1])

    def test_evaluate(self):
        b0_mass = 5.27955
        jpsi_mass = 3.0969
        k_mass = 0.493677
        pi_mass = 0.13957061

        b0 = hypy.Vector4R(b0_mass, 0.0, 0.0, 0.0)
        masses = [jpsi_mass, k_mass, pi_mass]
        phsp = hypy.PhaseSpace3(b0_mass, masses)

        result = hypy.host_vector_float2(5)
        phsp.EvaluateOnhost(b0, result, functor)
        tup = ((0.004857093031, -0.999950534243),
               (0.006868934284, -0.999842558622),
               (0.011390565091, -0.999882127917),
               (0.016108047503, -0.999560206432),
               (0.020888558031, -0.999196543388))

        for i in range(5):
            self.assertAlmostEqual(tup[i][0], result[i][0])
            self.assertAlmostEqual(tup[i][1], result[i][1])


if __name__ == '__main__':
    unittest.main()
