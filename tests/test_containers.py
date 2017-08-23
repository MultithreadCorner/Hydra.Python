# Licensed under a GNU general public license, see LICENSE.
"""
Author: Eduardo Rodrigues
Date  : Aug 2, 2017
"""

# -----------------------------------------------------------------------------
# Import statements
# -----------------------------------------------------------------------------
import unittest

from HydraPython import ( host_vector_float,
                          host_vector_float2,
                          host_vector_float3,
                          host_vector_float4,
                          host_vector_float5,
                          host_vector_float6,
                          host_vector_float7,
                          host_vector_float8,
                          host_vector_float9,
                          host_vector_float10
                          )
from HydraPython import ( device_vector_float,
                          device_vector_float2,
                          device_vector_float3,
                          device_vector_float4,
                          device_vector_float5,
                          device_vector_float6,
                          device_vector_float7,
                          device_vector_float8,
                          device_vector_float9,
                          device_vector_float10
                          )


# -----------------------------------------------------------------------------
# Actual tests
# -----------------------------------------------------------------------------
class Test(unittest.TestCase):
    def runTest(self):
        # required for Python 2.6 only
        self.test_host_vector_float()
        self.test_host_vector_float2()
        self.test_device_vector_float()
        self.test_device_vector_float2()

    def test_host_vector_float(self):
        v1 = host_vector_float()
        self.assertEqual(len(v1), 0)
        v1 = host_vector_float([i for i in range(100)])
        self.assertEqual(len(v1), 100)
        self.assertEqual(sum(v1), 4950.)

    def test_host_vector_float2(self):
        v2 = host_vector_float2()
        self.assertEqual(len(v2), 0)
        v2 = host_vector_float2([(i,i) for i in range(100)])
        self.assertEqual(len(v2), 100)
        self.assertEqual(v2.count((1,1)),1)
        
    def test_device_vector_float(self):
        v1 = device_vector_float([i for i in range(10)])
        self.assertEqual(len(v1), 10)
        self.assertEqual(sum(v1), 45.)
        self.assertEqual(9 in v1,True)

    def test_device_vector_float2(self):
        v2 = device_vector_float2([(i,i**2) for i in range(10)])
        self.assertEqual(len(v2), 10)
        self.assertEqual(v2.count((1,1)),1)
        self.assertEqual(v2.count((2,2)),0)
        self.assertEqual((3,9) in v2,True)
        v2bis = device_vector_float2(v2)
        self.assertEqual(v2bis, v2)
        
if __name__ == '__main__' :
    unittest.main()
