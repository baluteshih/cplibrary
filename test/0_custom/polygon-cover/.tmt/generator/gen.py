import math,random,sys
mode,count,seed=sys.argv[1],int(sys.argv[2]),int(sys.argv[3]);r=random.Random(seed)
def rect(x,y,w,h):return [(x,y),(x+w,y),(x+w,y+h),(x,y+h)]
p=[]
if mode=='empty':pass
elif mode=='maxdepth':p=[[(0,0),(10,0),(0,10)]]*count
elif mode=='shared':p=[rect(0,0,6,4)]*(count//2)+[rect(2,-4,3,4)]*(count-count//2)
elif mode=='fraction':p=[[(0,0),(3,0),(0,3)],[(0,0),(3,0),(3,3)]]
elif mode=='ring':p=[rect(0,0,6,2),rect(0,4,6,2),rect(0,2,2,2),rect(4,2,2,2)]
elif mode=='touch':p=[rect(0,0,4,2),rect(1,2,2,3),rect(4,0,3,2),rect(7,2,2,2)]
elif mode=='duplicates':p=[rect(-7,3,17,11)]*count
elif mode=='nested':p=[rect(-i-1,-i-1,2*i+2,2*i+2) for i in range(count)]
elif mode=='adjacent':p=[rect(3*i,0,3,5) for i in range(count)]
elif mode=='thin':p=[[(0,0),(9999-i,9998-i),(10000-i,9999-i)] for i in range(count)]
elif mode=='concave':
    for i in range(count):
        x=r.randint(-10,10);y=r.randint(-10,10)
        p.append([(x,y),(x+12,y),(x+12,y+3),(x+3,y+3),(x+3,y+12),(x,y+12)])
elif mode=='stress':
    for i in range(count):
        x=r.randint(-200,200);y=r.randint(-200,200);a=r.random()*6.28
        p.append([(x+round((9000 if j%2==0 else 4000)*math.cos(a+j*math.pi/4)),y+round((9000 if j%2==0 else 4000)*math.sin(a+j*math.pi/4))) for j in range(8)])
else:
    for i in range(count):
        x=r.randint(-20,20);y=r.randint(-20,20);w=r.randint(1,30);h=r.randint(1,30)
        p.append(rect(x,y,w,h) if mode=='rect' else [(x,y),(x+w,y),(x,y+h)])
print(len(p))
for shape in p:
    if mode=='rect' and seed==10:
        a,b=shape[0],shape[1]
        if b[0]-a[0]>=2:shape=shape[:1]+[((a[0]+b[0])//2,a[1])]+shape[1:]
    shift=seed%len(shape);shape=shape[shift:]+shape[:shift]
    print(len(shape))
    for a in shape:print(*a)
