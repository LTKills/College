import queue



## PROBLEMS RETURNING MULTIPLE VARIABLES


stack = []
queue = []
priority = []

def put(elem):
    stack.append(elem)
    queue.append(elem)
    priority.append(elem)


def rem(ans, isstack, isqueue, ispriority):
    priority.sort()

    if stack and ans != stack.pop():
        isstack = False

    if queue and ans != queue.pop(0):
        isqueue = False

    if priority and ans != priority.pop():
        ispriority = False

    return (isstack, isqueue, ispriority)


while True:

    try:
        isqueue = True
        isstack = True
        ispriority = True
        lines = int(input())

        for i in range(lines):
            (op, elem) = [int(a) for a in input().split()]
            if op == 1:
                put(elem)
            else:
                (isstack, isqueue, ispriority) = rem(elem, isstack, isqueue, ispriority)

        if (not isqueue and not isstack and not ispriority):
            print('impossible')
        elif (not isqueue and not isstack and ispriority):
            print('priority queue')
        elif (not isqueue and isstack and not ispriority):
            print('stack')
        elif (isqueue and not isstack and not ispriority):
            print('queue')
        else:
            print('not sure')

    except EOFError:
        break



