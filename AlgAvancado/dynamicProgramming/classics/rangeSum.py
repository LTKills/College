import sys


def main(argv):
    partialSum = ans = 0
    vec = [int(a) for a in input().split()]

    for i in range(len(vec)):
        if partialSum + vec[i] >= 0:
            partialSum += vec[i]
            ans = max(ans, partialSum)

        else:
            partialSum = 0

    print(int(ans))

if __name__ == "__main__":
    main(sys.argv)
