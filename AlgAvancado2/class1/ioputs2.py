
s = 0

while True:
    try:
        numbers = [int(a) for a in input().split()]
        s += sum(numbers)
    except EOFError:
        break

print(s)
