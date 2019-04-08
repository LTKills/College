import math

counter = 0
while(True):
    try:
        (c, s) = [int(a) for a in input().split(' ')]
        masses = [int(a) for a in input().split(' ')]
    except:
        break


    # complete with zeroes
    for i in range(2*c - s):
        masses.append(0)


    # sort
    masses.sort()


    # answer
    im = 0
    average = sum(masses)/(c)

    for i in range(c):
        im += abs((masses[i]+masses[c*2-i-1]) - average)

    print ("IMBALANCE = %.5f" % im)


