
def solve(a, b, c):
	for j in range(100):
		for k in range(100):
			for l in range(100):
				if l + j + k == a and l*j*k == b and l*l + j*j + k*k == c:
					return [l, j, k]

lines = int(input())

for i in range(lines):
	a,b,c = [int(a) for a in input().split()]
	
	ans = solve(a, b, c)
	
	if not ans:
		print('No solution.')
	else:
		ans.sort()
		print(str(ans[0]) + ' ' + str(ans[1]) + ' ' + str(ans[2]))
	
