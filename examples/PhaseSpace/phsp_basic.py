# Licensed under a GNU general public license, see LICENSE.
"""
This example shows how to use the Hydra's phase space Monte Carlo algorithms
to generate a sample of B0 -> J/psi K pi decays.

Author: Deepanshu Thakur
Date  : Aug 21, 2017
"""

import sys
import time

import HydraPython as hypy


def main():
    nentries = 1000000
    B0_mass = 5.27955    # All masses are given in GeV/c^2
    Jpsi_mass = 3.0969
    K_mass = 0.493677
    pi_mass = 0.13957061
    if len(sys.argv) > 1:
        nentries = int(sys.argv[1])

    B0 = hypy.Vector4R(B0_mass, 0.0, 0.0, 0.0)
    masses = [Jpsi_mass, K_mass, pi_mass]  # List of final-state particles
    phsp = hypy.PhaseSpace3(B0_mass, masses)

    #     Device    #
    events_d = hypy.device_events_3(nentries)
    start = time.time()
    phsp.GenerateOndevice(B0, events_d)
    end = time.time()

    print('\n' * 2)
    print("----------------- Device ----------------")
    print("| B0 -> J/psi K pi")
    print("| Number of events :", nentries)
    print("| Time (ms)        :", end - start)
    print("-----------------------------------------")

    for i in range(10):
        print(events_d[i])

    #     Host    #
    events_h = hypy.host_events_3(nentries)
    start = time.time()
    phsp.GenerateOnhost(B0, events_h)
    end = time.time()

    print('\n' * 2)
    print("------------------ Host -----------------")
    print("| B0 -> J/psi K pi")
    print("| Number of events :", nentries)
    print("| Time (ms)        :", end - start)
    print("-----------------------------------------")

    for i in range(10):
        print(events_h[i])


if __name__ == '__main__':
    main()
