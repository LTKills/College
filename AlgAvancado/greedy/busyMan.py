



t = int(input())


for k in range(t):
    now = 0
    ans = 0
    time = []
    n = int(input())

    for i in range(n):
        (start, end) = raw_input().strip().split(' ')
        start = int(start)
        end = int(end)
        time.append((start, end))


    time.sort(key=lambda tup: tup[1])

    for tup in time:
        if (tup[0] >= now):
            ans += 1
            now = tup[1]


    print (ans)
