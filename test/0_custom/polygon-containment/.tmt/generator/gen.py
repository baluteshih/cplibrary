import random,sys
n,q,mode,seed=map(int,sys.argv[1:]);r=random.Random(seed)
if n==0:p=[]
elif n==1:p=[(3,-5)]
elif n==2:p=[(-2,-2),(2,2)]
elif mode==1:p=[(0,0),(6,0),(6,2),(2,2),(2,6),(0,6)]
elif mode==2:p=[(-100000000,-100000000),(100000000,-100000000),(100000000,100000000),(-100000000,100000000)]
elif n==3:p=[(0,0),(8,0),(1,7)]
else:p=[(i,r.randint(0,20)) for i in range(n-2)]+[(n-3,100),(0,100)]
if seed%2:p.reverse()
n=len(p);q=min(q,2000000//max(n,1));print(n,q)
for a in p:print(*a)
for i in range(q):
    if p and i%5==0:a=p[(i//5)%n]
    elif len(p)>1 and i%5==1:
        u=p[(i//5)%n];v=p[(i//5+1)%n];a=((u[0]+v[0])//2,(u[1]+v[1])//2)
    elif mode==1:a=r.choice([(1,1),(3,3),(2,3),(7,7),(0,0),(3,2)])
    elif mode==2:a=r.choice([(0,0),(0,100000000),(100000000,0),(-99999999,99999999)])
    else:a=(r.randint(-5,max(n,10)),r.randint(-5,105))
    print(*a)
