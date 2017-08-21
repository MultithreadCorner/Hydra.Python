import HydraPython as hypy
import sys
import time
import math
import constants


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


def main():
    """
    This example shows how to use the Hydra's
    phase space Monte Carlo algorithms to calculate the
    average value and corresponding variance of a functor
    over the phase space of the decay B0 -> J/psi K pi.
    """
    nentries = 1000000
    B0_mass = 5.27955
    Jpsi_mass = 3.0969
    K_mass = 0.493677
    pi_mass = 0.13957061
    if len(sys.argv) > 1:
        nentries = int(sys.argv[1])

    B0 = hypy.Vector4R(B0_mass, 0.0, 0.0, 0.0)
    masses = [Jpsi_mass, K_mass, pi_mass]
    phsp = hypy.PhaseSpace3(B0_mass, masses)

    #     Device    #

    print()
    print(constants.RED, "ERROR: device is not supported with custom functors in current HydraPython version.", sep='')
    print(constants.RESET)

    #     Host    #
    start = time.time()
    pair = phsp.AverageOnhost(B0, functor, nentries)
    end = time.time()

    print('\n' * 2)
    print("----------------- Host ----------------")
    print("|< cos(theta_K) >(B0 -> J/psi K pi): ", pair[0], " +- ", pair[1])
    print("| Number of events :", nentries)
    print("| Time (ms)        :", end - start)
    print("-----------------------------------------")


if __name__ == '__main__':
    main()
