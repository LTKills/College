from sys import stdin


for line in stdin:
	line = line.split()
	t = int(line.pop(0))
	n = int(line.pop(0))
	numbers = [int(a) for a in line]
	
	if(n == 0) break
	
	print('Sums of ' + str(t) + ':')
	solve(n, t, numbers)
	

	
