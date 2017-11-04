
# Longest Common Substring


def lcs(s, pat):
    cp = s + '$'

    print (cp)
    trie = []

    n = len(cp)
    for i in range(n):
        trie.append((i, cp))
        cp = cp[1:]

    print (trie)

    return 'finished'


while (True):
    try:
        s = input()
        pat = input()
        blank = input()
    except:
        break

    print (lcs(s, pat))
