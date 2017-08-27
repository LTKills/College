

def printAns(ans):
    for a in ans:
        print (a + ' ' + ans[a])


def search(dic, value):
    for i in dic:
        if dic[i] == value:
            return i
    return None


def priority(wife, lover, husband, preferences):
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

    males = people[:n]
    freeMen = sorted(males)

    females = people[n:]
    freeWomen = sorted(females)


    for person in people:
        preferences[person] = list(input()[2:])

    # free not empty
    while (freeMen):
        man = freeMen[0]
        husband = search(ans, preferences[man][0])

        if (not husband):
            ans[man] = preferences[man].pop(0)  # by the power to me conceived, I here by declare you
            freeMen.pop(0)                      # husband
            freeWomen.remove(ans[man])          # and wife

        elif (priority(preferences[man][0], man, husband, preferences)):
            ans[man] = preferences[man].pop(0)  # by the power to me conceived, I here by declare you
            freeMen.append(husband)
            freeMen.pop(0)                      # husband and wife
            sorted(freeMen)   # sorry old pal



    printAns(ans)
    print ("")





tests = int(input())

for k in range(tests):
    match()
