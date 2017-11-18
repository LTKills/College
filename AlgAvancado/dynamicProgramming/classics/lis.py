import sys
import numpy


def lis(ans, vec, pos):
    hi = 0

    # Last element of vector, nothing after it
    if(pos == len(vec)-1):
        return 1

    if(ans[pos] != 0):
        return ans[pos]

    # Test all combinations
    for j in range(pos+1, len(vec)):
        if vec[pos] <= vec[j]:
            a = lis(ans, vec, j)

            if hi < a:
                hi = a

    ans[pos] = hi+1
    return ans[pos]


def main(argv):
    hi = 1
    vec = [int(a) for a in input().split()]
    ans = numpy.zeros(shape=(len(vec)))

    for i in range(len(vec)):
        a = lis(ans, vec, i)

        if hi < a:
            hi = a

    print(int(hi))


if __name__ == "__main__":
    main(sys.argv)
