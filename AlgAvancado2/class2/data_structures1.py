

def printVec(vec):
	[print(a) for a in vec]

vec = []

while True:
	try:
		vec.append(int(input()))
	except EOFError:
		break
		
vec.sort()

printVec(vec)
print()
printVec(reversed(vec))
		
