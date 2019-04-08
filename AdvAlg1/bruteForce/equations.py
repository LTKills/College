

tests = int(input())

for i in range(tests):
    x = y = z = 0
    coefs = [int(a) for a in input().split(' ')]
    ans = [0, 0, 0]

    for x in range(100):
        for y in range(100):
            for z in range(100):
                ans[0] = x + y + z
                ans[1] = x*y*z
                ans[2] = x*x + y*y + z*z
                if (ans == coefs):
                    break
            if (ans == coefs):
                break
        if (ans == coefs):
            break

    if (ans == coefs):
        print (str(x) + ' ' + str(y) + ' ' + str(z))
    else:
        print ('No solution')

