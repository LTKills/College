import sys

stack = []

def recursion(stack, last):
    if stack:
        now = stack.pop()
    else:
        return -1
    s = 0

    while now != -last:
        foo = recursion(stack, now)
        if foo == -1:
            return -1
        s += foo
        if stack:
            now = stack.pop()
        else:
            break

    if now != -last or s >= last:
        return -1
    return last


for line in sys.stdin:
    stack = [int(a) for a in line.split()]

    top = stack.pop()
    ans = recursion(stack, top)

    if ans == -1:
        print(':-( Try again.')
    else:
        print(':-) Matrioshka!')

