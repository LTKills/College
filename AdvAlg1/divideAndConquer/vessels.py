import math


def test(vec, bound, n):
    cur = divisions = 0

    for i in vec:
        # create new subset (except when its the last set)
        if (cur > bound):
            return False

        if (cur + i > bound):
            cur = 0
            divisions += 1

        if (divisions >= n):
            return False

        cur += i

    return True



def binSearch(vec, n):
    lo = max(vec)
    hi = sum(vec)

    while(lo != hi):
        mid = int(((lo+hi)/2))

        if(test(vec, mid, n)):
            hi = mid
        else:
            lo = mid+1

    return lo



while(True):

    try:
        (vessels, containers) = [int(a) for a in input().split()]
    except:
        break

    capacities = [int(a) for a in input().split()]

    print (binSearch(capacities, containers))

