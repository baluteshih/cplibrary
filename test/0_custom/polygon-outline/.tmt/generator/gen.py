import random, sys
n, q, mode, seed = map(int, sys.argv[1:])
r = random.Random(seed)
square = [(100000000,100000000),(-100000000,100000000),(-100000000,-100000000),(100000000,-100000000)]
points = [square[i%4] if mode in (1,2) else (r.randint(-1000,1000),r.randint(-1000,1000)) for i in range(n)]
if mode == 2: points.reverse()
if mode == 3: points = [(7,-9)]*n
print(n,q)
for x,y in points: print(x,y)
print('A')
left = 2000000//n-1
special = [-1000000000,1000000000,-n-1,-n,-1,0,n-1,n,n+1]
for j in range(q-1):
    op = r.choice('VVEEESAA')
    if op == 'A' and left:
        print('A');left-=1;continue
    if op == 'A': op = 'V'
    i = special[j%len(special)] if j%2==0 else r.randint(-1000000000,1000000000)
    if op == 'S': print(op,i,r.randint(-100000000,100000000),r.randint(-100000000,100000000))
    else: print(op,i)
