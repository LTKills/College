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


def lds(ans, vec, pos):
    hi = 0

    # Last element of vector, nothing after it
    if(pos == len(vec)-1):
        return 1

    if(ans[pos] != 0):
        return ans[pos]

    # Test all combinations
    for j in range(pos+1, len(vec)):
        if vec[pos] >= vec[j]:
            a = lds(ans, vec, j)

            if hi < a:
                hi = a

    ans[pos] = hi+1
    return ans[pos]


def main(argv):
    tests = int(input())

    for _ in range(tests):
        vec = []
        hi = 0
        n = int(input())

        # Vector
        for i in range(n):
            vec.append(int(input()))
        ans1 = numpy.zeros(shape=(len(vec)))
        ans2 = numpy.zeros(shape=(len(vec)))

        for i in range(len(vec)):
            a = lis(ans1, vec, i)
            b = lds(ans2, vec, i)

            if hi < (a+b-1):
                hi = (a+b-1)

        print(int(hi))


if __name__ == "__main__":
    main(sys.argv)
