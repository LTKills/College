import sys


def check_containers(volume):
    """
    This function only checks if a given volume is valid.
    It does not try fill all the containers.
    If the given volume is valid for a subset k < m, it is certanly valid for m
    """
    container_count = 0
    container_sum = 0
    for bottle in range(0, n):
        if container_sum > volume:
                return False

        if container_sum + capacities[bottle] > volume:
                container_sum = 0
                container_count += 1
        if container_count >= m:
                return False
        container_sum += capacities[bottle]
    return True
		

def bisection(low, high):
    " Returns the minimum of the highest volume in all the bottles."""
    while (low != high):
        middle = (low+high) // 2 # "//" is the same as integer division

        print ('mid = ' + str(middle))
        if check_containers(middle):
            high = middle
        else:
            low = middle+1
    return low


while(True):
    line = sys.stdin.readline()
    if not line:
        break

    n, m = map(int, line.split())
    capacities = [int(x) for x in input().split()]
    print(bisection(max(capacities), sum(capacities)))
