import time
import random

def gen(i):
    a = 'fodase'
    for l in a:
        yield '{}{}'.format(l, i)

custom_gen = gen(10)

for i in custom_gen:
    print(i)

