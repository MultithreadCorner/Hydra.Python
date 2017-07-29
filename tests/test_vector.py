import unittest
from HydraPython import Vector4R, Vector3R


def raise_error_4R(*args, **kwargs):
    Vector4R(*args)


def raise_error_3R(*args, **kwargs):
    Vector4R(*args)


class TestVector4R(unittest.TestCase):
    """
    Vector4R test class, which tests all the methods available in Vector4R class.
    TODO: Bind and test `scalartripler3` after the actual implementation in Hydra.
    """
    def _check_approximate_each_value(self, vector, *values, **kwargs):
        places = 12
        if 'places' in kwargs:
            places = kwargs['places']
        for idx, value in enumerate(values):
            self.assertAlmostEqual(vector[idx], value, places=places)

    def test_default_constructor(self):
        vec = Vector4R()
        self.assertIsInstance(vec, Vector4R, 'Failure: Not an instance of Vector4R')

    def test_argument_constructor(self):
        vec = Vector4R(0.3241234856402, 0.712532522433, 0.2428385977825, 1.0389887631011)
        self.assertIsInstance(vec, Vector4R, 'Failure: Not an instance of Vector4R')
        self._check_approximate_each_value(vec, 0.3241234856402, 0.712532522433, 0.2428385977825, 1.0389887631011)

    def test_copy_constructor(self):
        vec1 = Vector4R(0.3241234856402, 0.712532522433, 0.2428385977825, 1.0389887631011)
        vec2 = Vector4R(vec1)
        self.assertIsInstance(vec2, Vector4R, 'Failure: Not an instance of Vector4R')
        self._check_approximate_each_value(vec2, vec1[0], vec1[1], vec1[2], vec1[3])

    def test_raise_error(self):
        self.assertRaises(TypeError, raise_error_4R, 1.1)
        self.assertRaises(TypeError, raise_error_4R, 1.1, 2.2)
        self.assertRaises(TypeError, raise_error_4R, 1.1, 2.2, 3.3)

    def test_get(self):
        vec = Vector4R(0.3241234856402, 0.712532522433, 0.2428385977825, 1.0389887631011)
        self._check_approximate_each_value(vec, vec.get(0), vec.get(1), vec.get(2), vec.get(3))

    def test_set_two_arguments(self):
        vec = Vector4R()
        vec.set(1, 0.32447236432573858356)
        self.assertEqual(vec[1], 0.32447236432573858356)

    def test_set_vector(self):
        vec = Vector4R()
        vec.set(0.3241234856402, 0.712532522433, 0.2428385977825, 1.0389887631011)
        self._check_approximate_each_value(vec, 0.3241234856402, 0.712532522433, 0.2428385977825, 1.0389887631011)

    # Need a comment on that about number of places
    def test_inplace_multiply(self):
        vec = Vector4R(0.3241234856402, 0.712532522433, 0.2428385977825, 1.0389887631011)
        vec *= 5.5
        self._check_approximate_each_value(vec, 0.3241234856402 * 5.5, 0.712532522433 * 5.5, 0.2428385977825 * 5.5, 1.0389887631011 * 5.5)

    def test_inplace_division(self):
        vec = Vector4R(0.3241234856402, 0.712532522433, 0.2428385977825, 1.0389887631011)
        vec /= 5.5
        self._check_approximate_each_value(vec, 0.3241234856402 / 5.5, 0.712532522433 / 5.5, 0.2428385977825 / 5.5, 1.0389887631011 / 5.5)

    def test_assign(self):
        vec1 = Vector4R(0.3241234856402, 0.712532522433, 0.2428385977825, 1.0389887631011)
        vec2 = Vector4R()
        vec2.assign(vec1)
        self._check_approximate_each_value(vec2, vec1[0], vec1[1], vec1[2], vec1[3])

    def test_inplace_add(self):
        vec1 = Vector4R(0.3241234856402, 0.712532522433, 0.2428385977825, 1.0389887631011)
        vec2 = Vector4R(0.1529024479612, 0.983987651234, 0.1339887631011, 0.9123838597782)
        vec1 += vec2
        self._check_approximate_each_value(vec1, 0.3241234856402 + vec2[0], 0.712532522433 + vec2[1], 0.2428385977825 + vec2[2],
                                           1.0389887631011 + vec2[3])

    def test_inplace_sub(self):
        vec1 = Vector4R(0.3241234856402, 0.712532522433, 0.2428385977825, 1.0389887631011)
        vec2 = Vector4R(0.1529024479612, 0.983987651234, 0.1339887631011, 0.9123838597782)
        vec1 -= vec2
        self._check_approximate_each_value(vec1, 0.3241234856402 - vec2[0], 0.712532522433 - vec2[1], 0.2428385977825 - vec2[2],
                                           1.0389887631011 - vec2[3])

    def test_cont(self):
        vec1 = Vector4R(0.3241234856402, 0.712532522433, 0.2428385977825, 1.0389887631011)
        vec2 = Vector4R(0.1529024479612, 0.983987651234, 0.1339887631011, 0.9123838597782)
        self.assertAlmostEqual(vec1.cont(vec2), -1.632058150075024)

    def test_mass(self):
        vec = Vector4R(2.3241234856402, 0.712532522433, 0.2428385977825, 1.0389887631011)
        self.assertAlmostEqual(vec.mass(), 1.9378800650598311, places=12)

    def test_mass2(self):
        vec = Vector4R(2.3241234856402, 0.712532522433, 0.2428385977825, 1.0389887631011)
        self.assertAlmostEqual(vec.mass2(), 3.7553791465562956, places=12)

    def test_apply_rotate_eular(self):
        vec = Vector4R(2.3241234856402, 0.712532522433, 0.2428385977825, 1.0389887631011)
        vec.applyRotateEuler(0.6070696824721713, 1.860040373113793,  0.6360120983116064)
        self._check_approximate_each_value(vec, 2.3241234856402, 0.3645198690237261, 1.0063521991364466, -0.7074965344990902)

    def test_apply_boost_to_vector4R(self):
        vec1 = Vector4R(2.3241234856402, 0.712532522433, 0.2428385977825, 1.0389887631011)
        vec2 = Vector4R(2.1529024479612, 0.983987651234, 0.1339887631011, 0.9123838597782)
        vec1.applyBoostTo(vec2)
        self._check_approximate_each_value(vec1, 3.9835674939442995, 2.332611295964608, 0.4634433489901204, 2.541176034136262)

    def test_apply_boost_to_vector4R_inverse(self):
        vec1 = Vector4R(2.3241234856402, 0.712532522433, 0.2428385977825, 1.0389887631011)
        vec2 = Vector4R(2.1529024479612, 0.983987651234, 0.1339887631011, 0.9123838597782)
        vec1.applyBoostTo(vec2, True)
        self._check_approximate_each_value(vec1, 1.9794964459108633, -0.3928170140328311, 0.09232408980092516, 0.014074400385272287)

    def test_apply_boost_to_vector3R(self):
        vec1 = Vector4R(0.3241234856402, 0.712532522433, 0.2428385977825, 1.0389887631011)
        vec2 = Vector3R(0.1529024479612, 0.683987651234, 0.1339887631011)
        vec1.applyBoostTo(vec2)
        self._check_approximate_each_value(vec1, 1.0539417783464062, 0.8364361913339782, 0.7971042789464847, 1.1475658301206095)

    def test_apply_boost_to_vector3R_inverse(self):
        vec1 = Vector4R(0.3241234856402, 0.712532522433, 0.2428385977825, 1.0389887631011)
        vec2 = Vector3R(0.1529024479612, 0.683987651234, 0.1339887631011)
        vec1.applyBoostTo(vec2, True)
        self._check_approximate_each_value(vec1, -0.12865682140904047, 0.6949578563565814, 0.16422079452874308, 1.0235880432245175)

    def test_apply_boost(self):
        vec = Vector4R(0.3241234856402, 0.712532522433, 0.2428385977825, 1.0389887631011)
        vec.applyBoostTo(0.1529024479612, 0.683987651234, 0.1339887631011)
        self._check_approximate_each_value(vec, 1.0539417783464062, 0.8364361913339782, 0.7971042789464847, 1.1475658301206095)

    def test_apply_boost_inverse(self):
        vec = Vector4R(0.3241234856402, 0.712532522433, 0.2428385977825, 1.0389887631011)
        vec.applyBoostTo(0.1529024479612, 0.683987651234, 0.1339887631011, True)
        self._check_approximate_each_value(vec, -0.12865682140904047, 0.6949578563565814, 0.16422079452874308, 1.0235880432245175)

    def test_cross(self):
        vec1 = Vector4R(2.3241234856402, 0.712532522433, 0.2428385977825, 1.0389887631011)
        vec2 = Vector4R(2.1529024479612, 0.983987651234, 0.1339887631011, 0.9123838597782)
        vec = vec1.cross(vec2)
        self._check_approximate_each_value(vec, 0.0, 0.082349197904065, 0.37224893962745276, -0.14347883011085577)

    def test_dot(self):
        vec1 = Vector4R(0.3241234856402, 0.712532522433, 0.2428385977825, 1.0389887631011)
        vec2 = Vector4R(0.1529024479612, 0.983987651234, 0.1339887631011, 0.9123838597782)
        self.assertAlmostEqual(vec1.dot(vec2), 1.6816174244711273)

    def test_d3mag(self):
        vec = Vector4R(0.3241234856402, 0.712532522433, 0.2428385977825, 1.0389887631011)
        self.assertAlmostEqual(vec.d3mag(), 1.2830318896847648)

    def test_scalartripler3(self):
        pass

    def test_dotr3(self):
        vec1 = Vector4R(2.3241234856402, 0.712532522433, 0.2428385977825, 1.0389887631011)
        vec2 = Vector4R(2.1529024479612, 0.983987651234, 0.1339887631011, 0.9123838597782)
        vec3 = Vector4R(0.9857328372384, 0.923759237593, 0.8473584725274, 0.1489738526833)
        self.assertAlmostEqual(vec1.dotr3(vec2, vec3), 0.16162455324979352)

    def test_mag2r3(self):
        vec1 = Vector4R(2.3241234856402, 0.712532522433, 0.2428385977825, 1.0389887631011)
        vec2 = Vector4R(2.1529024479612, 0.983987651234, 0.1339887631011, 0.9123838597782)
        self.assertAlmostEqual(vec1.mag2r3(vec2), 0.12226270347816381)

    def test_magr3(self):
        vec1 = Vector4R(2.3241234856402, 0.712532522433, 0.2428385977825, 1.0389887631011)
        vec2 = Vector4R(2.1529024479612, 0.983987651234, 0.1339887631011, 0.9123838597782)
        self.assertAlmostEqual(vec1.magr3(vec2), 0.349660840641562)

    def test_multiply(self):
        vec1 = Vector4R(0.3241234856402, 0.712532522433, 0.2428385977825, 1.0389887631011)
        vec2 = Vector4R(0.1529024479612, 0.983987651234, 0.1339887631011, 0.9123838597782)
        self.assertAlmostEqual(vec1 * vec2, -1.632058150075024)
        self.assertAlmostEqual(vec2 * vec1, -1.632058150075024)

    def test_multiply_number(self):
        vec = Vector4R(0.3241234856402, 0.712532522433, 0.2428385977825, 1.0389887631011)
        self._check_approximate_each_value(vec * 5.5, 1.7826791710210999, 3.9189288733815, 1.33561228780375, 5.714438197056051)

    def test_multiply_number_v2(self):
        vec = Vector4R(0.3241234856402, 0.712532522433, 0.2428385977825, 1.0389887631011)
        self._check_approximate_each_value(5.5 * vec, 1.7826791710210999, 3.9189288733815, 1.33561228780375, 5.714438197056051)

    def test_divide(self):
        vec = Vector4R(0.3241234856402, 0.712532522433, 0.2428385977825, 1.0389887631011)
        self._check_approximate_each_value(vec / 5.5, 0.058931542843672725, 0.1295513677150909, 0.04415247232409091, 0.18890704783656367)

    def test_add(self):
        vec1 = Vector4R(0.3241234856402, 0.712532522433, 0.2428385977825, 1.0389887631011)
        vec2 = Vector4R(0.1529024479612, 0.983987651234, 0.1339887631011, 0.9123838597782)
        self._check_approximate_each_value(vec1 + vec2, 0.4770259336014, 1.696520173667, 0.3768273608836, 1.9513726228793002)

    def test_sub(self):
        vec1 = Vector4R(0.3241234856402, 0.712532522433, 0.2428385977825, 1.0389887631011)
        vec2 = Vector4R(0.1529024479612, 0.983987651234, 0.1339887631011, 0.9123838597782)
        self._check_approximate_each_value(vec1 - vec2, 0.171221037679, -0.271455128801, 0.1088498346814, 0.1266049033229001)

    def check_equality(self):
        vec1 = Vector4R(0.3241234856402, 0.712532522433, 0.2428385977825, 1.0389887631011)
        vec2 = Vector4R(0.1529024479612, 0.983987651234, 0.1339887631011, 0.9123838597782)
        self.assertEqual(vec1 == vec1, True)
        self.assertEqual(vec1 != vec1, False)
        self.assertEqual(vec1 == vec2, False)
        self.assertEqual(vec1 != vec2, True)


class TestVector3R(unittest.TestCase):
    """
    Vector3R test class, which tests all the methods available in Vector4R class.
    TODO: Add the test for `assign` after the actual implementation in Hydra.
    """
    def _check_approximate_each_value(self, vector, *values, **kwargs):
        places = 12
        if 'places' in kwargs:
            places = kwargs['places']
        for idx, value in enumerate(values):
            self.assertAlmostEqual(vector[idx], value, places=places)

    def test_default_constructor(self):
        vec = Vector3R()
        self.assertIsInstance(vec, Vector3R, 'Failure: Not an instance of Vector3R')

    def test_argument_constructor(self):
        vec = Vector3R(0.3241234856402, 0.712532522433, 0.2428385977825)
        self.assertIsInstance(vec, Vector3R, 'Failure: Not an instance of Vector3R')
        self._check_approximate_each_value(vec, 0.3241234856402, 0.712532522433, 0.2428385977825)

    def test_copy_constructor(self):
        vec1 = Vector3R(0.3241234856402, 0.712532522433, 0.2428385977825)
        vec2 = Vector3R(vec1)
        self.assertIsInstance(vec2, Vector3R, 'Failure: Not an instance of Vector4R')
        self._check_approximate_each_value(vec2, vec1[0], vec1[1], vec1[2])

    def test_raise_error(self):
        self.assertRaises(TypeError, raise_error_3R, 1.1)
        self.assertRaises(TypeError, raise_error_3R, 1.1, 2.2)

    def test_get(self):
        vec = Vector3R(0.3241234856402, 0.712532522433, 0.2428385977825)
        self._check_approximate_each_value(vec, vec.get(0), vec.get(1), vec.get(2))

    def test_set_two_arguments(self):
        vec = Vector3R()
        vec.set(1, 0.32447236432573858356)
        self.assertEqual(vec[1], 0.32447236432573858356)

    def test_set_vector(self):
        vec = Vector3R()
        vec.set(0.3241234856402, 0.712532522433, 0.2428385977825)
        self._check_approximate_each_value(vec, 0.3241234856402, 0.712532522433, 0.2428385977825)

    # Need a comment on that about number of places
    def test_inplace_multiply(self):
        vec = Vector3R(0.3241234856402, 0.712532522433, 0.2428385977825)
        vec *= 5.5
        self._check_approximate_each_value(vec, 0.3241234856402 * 5.5, 0.712532522433 * 5.5, 0.2428385977825 * 5.5)

    def test_inplace_division(self):
        vec = Vector3R(0.3241234856402, 0.712532522433, 0.2428385977825)
        vec /= 5.5
        self._check_approximate_each_value(vec, 0.3241234856402 / 5.5, 0.712532522433 / 5.5, 0.2428385977825 / 5.5)

    # def test_assign(self):
    #     vec1 = Vector3R(0.3241234856402, 0.712532522433, 0.2428385977825)
    #     vec2 = Vector3R()
    #     vec2.assign(vec1)
    #     self._check_approximate_each_value(vec2, vec1[0], vec1[1], vec1[2])

    def test_inplace_add(self):
        vec1 = Vector3R(0.3241234856402, 0.712532522433, 0.2428385977825)
        vec2 = Vector3R(0.1529024479612, 0.983987651234, 0.1339887631011)
        vec1 += vec2
        self._check_approximate_each_value(vec1, 0.3241234856402 + vec2[0], 0.712532522433 + vec2[1], 0.2428385977825 + vec2[2])

    def test_inplace_sub(self):
        vec1 = Vector3R(0.3241234856402, 0.712532522433, 0.2428385977825)
        vec2 = Vector3R(0.1529024479612, 0.983987651234, 0.1339887631011)
        vec1 -= vec2
        self._check_approximate_each_value(vec1, 0.3241234856402 - vec2[0], 0.712532522433 - vec2[1], 0.2428385977825 - vec2[2])

    def test_apply_rotate_eular(self):
        vec = Vector3R(2.3241234856402, 0.712532522433, 0.2428385977825)
        vec.applyRotateEuler(0.6070696824721713, 1.860040373113793,  0.6360120983116064)
        self._check_approximate_each_value(vec, -1.262214606971851, 1.5020586145520496, -1.4556295411260831)

    def test_dot(self):
        vec1 = Vector3R(0.3241234856402, 0.712532522433, 0.2428385977825)
        vec2 = Vector3R(0.1529024479612, 0.983987651234, 0.1339887631011)
        self.assertAlmostEqual(vec1.dot(vec2), 0.1486778231883103)

    def test_d3mag(self):
        vec = Vector3R(0.3241234856402, 0.712532522433, 0.2428385977825)
        self.assertAlmostEqual(vec.d3mag(), 0.81959088211208)

    def test_multiply(self):
        vec1 = Vector3R(0.3241234856402, 0.712532522433, 0.2428385977825)
        vec2 = Vector3R(0.1529024479612, 0.983987651234, 0.1339887631011)
        self.assertAlmostEqual(vec1 * vec2, 0.7832201209228712)
        self.assertAlmostEqual(vec2 * vec1, 0.7832201209228712)

    def test_multiply_number(self):
        vec = Vector3R(0.3241234856402, 0.712532522433, 0.2428385977825)
        self._check_approximate_each_value(vec * 5.5, 1.7826791710210999, 3.9189288733815, 1.33561228780375)

    def test_multiply_number_v2(self):
        vec = Vector3R(0.3241234856402, 0.712532522433, 0.2428385977825)
        self._check_approximate_each_value(5.5 * vec, 1.7826791710210999, 3.9189288733815, 1.33561228780375)

    def test_divide(self):
        vec = Vector3R(0.3241234856402, 0.712532522433, 0.2428385977825)
        self._check_approximate_each_value(vec / 5.5, 0.058931542843672725, 0.1295513677150909, 0.04415247232409091)

    def test_add(self):
        vec1 = Vector3R(0.3241234856402, 0.712532522433, 0.2428385977825)
        vec2 = Vector3R(0.1529024479612, 0.983987651234, 0.1339887631011)
        self._check_approximate_each_value(vec1 + vec2, 0.4770259336014, 1.696520173667, 0.3768273608836)

    def test_sub(self):
        vec1 = Vector3R(0.3241234856402, 0.712532522433, 0.2428385977825)
        vec2 = Vector3R(0.1529024479612, 0.983987651234, 0.1339887631011)
        self._check_approximate_each_value(vec1 - vec2, 0.171221037679, -0.271455128801, 0.1088498346814)

    def check_equality(self):
        vec1 = Vector3R(0.3241234856402, 0.712532522433, 0.2428385977825)
        vec2 = Vector3R(0.1529024479612, 0.983987651234, 0.1339887631011)
        self.assertEqual(vec1 == vec1, True)
        self.assertEqual(vec1 != vec1, False)
        self.assertEqual(vec1 == vec2, False)
        self.assertEqual(vec1 != vec2, True)


if __name__ == '__main__':
    unittest.main()
