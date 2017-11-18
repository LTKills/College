import sys
import numpy


def lis(vec, n):
    print('foo')


def main(argv):
    tests = int(input())

    for _ in range(tests):
        n = int(input())
        vec = []

        for i in range(n):
            vec.append(int(input()))

        print(lis(vec))


if __name__ == "__main__":
    main(sys.argv)
