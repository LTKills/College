
def kmp(aux):
    vec = []
    j = 0
    i = 1
    vec.append(0)

    while(i < len(aux)):

        while (j > 0 and aux[i] != aux[j]):
            j = vec[j-1]

        if (aux[i] == aux[j]):
            vec.append(j+1)
            i += 1
            j += 1
        else:
            vec.append(0)
            i += 1

    return max(vec)


def solve(s, aux):
    hi = kmp(aux)
    return s[:len(s)-hi]


while True:
    try:
        s = input()
    except:
        break

    print (s + solve(s, s[::-1] + '#' + s)[::-1])


