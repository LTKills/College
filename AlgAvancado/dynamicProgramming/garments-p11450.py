import sys
import numpy


def solve(M, call, value, end, garments, mat):
    aux = []

    M -= value

    if M < 0:
        return sys.maxsize

    if call == end:
        return M

    if(mat[M][call] != -1):
        return mat[M][call]

    aux = [int(solve(M, call+1, a, end, garments, mat)) for a in garments[call]]
    mat[M][call] = min(aux)

    return mat[M][call]


def main(argv):
    n = int(input())

    for _ in range(n):
        garments = []
        (M, ngarments) = [int(a) for a in input().split(' ')]
        mat = numpy.zeros(shape=(201, 21))
        numpy.place(mat, mat == 0, -1)

        for i in range(ngarments):
            garments.append([int(a) for a in input().split(' ')][1:])

        ans = solve(int(M), 0, 0, ngarments, garments, mat)

        if(M - ans < 0):
            print('no solution')
        else:
            print(int(M - ans))


if __name__ == "__main__":
    main(sys.argv)
