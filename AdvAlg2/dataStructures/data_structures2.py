
alphabet = {
	'S' : 'A',
    'P' : 'O',
	'X' : 'Z',
	'C' : 'X',
	'D' : 'S',
	'W' : 'Q',
	'E' : 'W',
	'F' : 'D',
	'V' : 'C',
	'G' : 'F',
	'R' : 'E',
	'T' : 'R',
	'H' : 'G',
	'B' : 'V',
	'N' : 'B',
	'J' : 'H',
	'Y' : 'T',
	'U' : 'Y',
	'K' : 'J',
	'M' : 'N',
	'L' : 'K',
	'I' : 'U',
	'O' : 'I',
	';' : 'L',
	',' : 'M',
	'.' : ',',
	"'" : ';',
	'/' : '.',
	' ' : ' ',
}

ans = []

while True:
	try:
		line = input()
		ans = [alphabet[a] for a in line]
		print(''.join(map(str, ans)))
		
	except EOFError:
		break




