import math

def invertions(vec):
    i = c = 0
    j = int(len(vec)/2)

    if (int(len(vec) == 1)):
#        print ('base case with ' + str(vec))
        return (vec, 0)

    v1 = vec[:int(len(vec)/2)]
    v2 = vec[int(len(vec)/2):]

#    print ('calling for ' + str(v1) + ' and ' + str(v2))

    (v1, a) = invertions(v1)
    (v2, b) = invertions(v2)

    vec = v1 + v2
#    print (vec)

    while(i < int(math.ceil(len(vec)/2)) and j < len(vec)):
        if(vec[i] > vec[j]):
            c += int(len(vec)/2) - i
#            print ('c is: ' + str(c))
            j += 1
        else:
            i += 1

#    print (str(vec) + ': ' + str(c))

    vec.sort()

#    print ('sorted = ' + str(vec))

    return (vec, a + b + c)


tests = int(input())
#blank = input()

for i in range(tests):

    vec = []

    try:
        cur = input()
    except:
        break

    n = int(input())

    for j in range(n):
#    while(cur != blank or cur != None):
        cur = input()
        vec.append(int(cur))

#    vec.pop(0)
#    print (vec)
    print (str(invertions(vec)[1]))

