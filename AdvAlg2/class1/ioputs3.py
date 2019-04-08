

def calc(op, line):
    line = [int(a) for a in line]

    if(op == 'S'): # soma
        return 'T ' + str(sum(line))

    elif(op == 'R'): # resto
        return 'T ' + str(2*line[0] - sum(line))

    else:
        return 'E'



lines = int(input())

for i in range(lines):
    line = input().split()
    print(calc(line[0], line[1:]))

