
lines = int(input())

s = 0

for n in range(lines):
    numbers = [int(a) for a in input().split()]
    s += sum(numbers)

print(s)
