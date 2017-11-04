import sys
from math import sqrt


def dist(a, b):
    return sqrt((a[1]-b[1])*(a[1]-b[1]) + (a[0]-b[0])*(a[0]-b[0]))



n = int(input())

points = []

for i in range(n):
    (a, b) = [int(a) for a in input().split()]
    points.append((a, b))

copy = sorted(points, key=lambda tup: tup[0])

#print (points)
#print (copy)

min = sys.maxsize
ans = -1

for i in range(len(copy)-1):
    if (dist(copy[i], copy[i+1]) < min):
        min = dist(copy[i], copy[i+1])
        ans = i

print (str(points.index(copy[ans])) + ' ' + str(points.index(copy[ans+1])), end='')

print (' %.6f' % min)




