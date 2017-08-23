# Licensed under a GNU general public license, see LICENSE.
"""
This example shows how to use the Hydra's phase space Monte Carlo algorithms to
generate a sample of B0 -> J/psi K pi and use the multiple daughters to generate the
grand-daughters.

This example is the python version of Hydra's
https://github.com/AAAlvesJr/Hydra/blob/master/examples/phase_space/phsp_chain.cpp

Author: Deepanshu Thakur
Date  : Aug 21, 2017
"""

import HydraPython as hypy
import sys
import time


def main():

    nentries = 1000000
    B0_mass = 5.27955  # All masses are given in GeV/c^2
    Jpsi_mass = 3.0969
    K_mass = 0.493677
    pi_mass = 0.13957061
    mu_mass = 0.1056583745
    if len(sys.argv) > 1:
        nentries = int(sys.argv[1])

    B0 = hypy.Vector4R(B0_mass, 0.0, 0.0, 0.0)
    masses1 = [Jpsi_mass, K_mass, pi_mass]  # List of daughter particles
    masses2 = [mu_mass, mu_mass]  # List of grand-daughter particles

    phsp1 = hypy.PhaseSpace3(B0_mass, masses1)
    phsp2 = hypy.PhaseSpace2(Jpsi_mass, masses2)

    #     Device    #

    daughters_d = hypy.host_events_3(nentries)
    grand_daughters_d = hypy.host_events_2(nentries)
    start = time.time()

    phsp1.GenerateOnhost(B0, daughters_d)
    phsp2.GenerateOnhost(daughters_d.getDaughters(0), grand_daughters_d)

    end = time.time()

    print('\n' * 2)
    print("------------------ Host -----------------")
    print("| B0 -> J/psi K pi | J/psi -> mu+ mu-")
    print("| Number of events :", nentries)
    print("| Time (ms)        :", end - start)
    print("-----------------------------------------")

    for i in range(10):
        print(daughters_d[i], grand_daughters_d[i])

    #     Host    #

    daughters_h = hypy.host_events_3(nentries)
    grand_daughters_h = hypy.host_events_2(nentries)
    start = time.time()

    phsp1.GenerateOnhost(B0, daughters_h)
    phsp2.GenerateOnhost(daughters_h.getDaughters(0), grand_daughters_h)

    end = time.time()

    print('\n' * 2)
    print("----------------- Device ----------------")
    print("| B0 -> J/psi K pi | J/psi -> mu+ mu-")
    print("| Number of events :", nentries)
    print("| Time (ms)        :", end - start)
    print("-----------------------------------------")

    for i in range(10):
        print(daughters_h[i], grand_daughters_h[i])


if __name__ == '__main__':
    main()
