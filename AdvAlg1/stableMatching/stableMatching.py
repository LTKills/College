

def printAns(ans):
    for a in range(len(ans)):
        letter = chr(a + 97)
        print (letter + ' ' + ans[letter])


def search(dic, value):
    for i in dic:
        if dic[i] == value:
            return i
    return None


def priority(wife, lover, husband, preferences):
    if (husband == None):
        return True

    for pretendent in preferences[wife]:
        if (pretendent == lover):
            return True
        elif (pretendent == husband):
            return False



def match():
    preferences = {}
    ans = {}

    n = int(input())
    people = input().split(' ')

    freeMen = people[:n]

    for person in people:
        preferences[person] = list(input()[2:])

    # there are uncoupled men
    while (freeMen):

        # choose man
        man = freeMen[0]
        husband = search(ans, preferences[man][0])

        # woman is free
        if (husband == None):
            ans[man] = preferences[man][0]
            freeMen.pop(0)

        # woman prefers man to her husband
        elif (priority(preferences[man][0], man, husband, preferences)):
            ans[man] = preferences[man][0]
            ans[husband] = -1
            freeMen.pop(0)
            freeMen.append(husband)

        preferences[man].pop(0)

    printAns(ans)





tests = int(input())

for k in range(tests):
    match()
    if (k != tests-1):
        print ()

