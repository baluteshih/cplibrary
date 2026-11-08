import itertools
import random
import sys

mode, n, seed = sys.argv[1], int(sys.argv[2]), int(sys.argv[3])
r = random.Random(seed)
C = 1000000000
cube = list(itertools.product([-100, 100], repeat=3))
if mode == 'tetra':
    p = [(-C, -C, -C), (C, -C, -C), (-C, C, -C), (-C, -C, C)]
elif mode in ('cube', 'interior'):
    p = cube[:]
    p += [tuple(r.randint(-100, 100) for _ in range(3)) for _ in range(n - len(p))]
elif mode == 'translated':
    p = [tuple(x + 900000000 for x in q) for q in cube]
elif mode == 'duplicates':
    p = [cube[i % 8] for i in range(n)]
elif mode == 'collinear':
    p = [(i, 0, 0) for i in range(n - 3)] + [(0, 10, 0), (0, 0, 10), (1, 1, 1)]
elif mode == 'plane':
    p = [(r.randint(-1000, 1000), r.randint(-1000, 1000), 0) for _ in range(n - 1)] + [(0, 0, 1)]
elif mode == 'thin':
    p = [(0, 0, 0), (C, 1, 0), (C - 1, 1, 0), (C - 2, 1, 1)]
elif mode == 'pyramid':
    p = [(i, i * i, 0) for i in range(-100, 100)] + [(0, 5000, 500)]
elif mode in ('grid', 'noise'):
    noise = random.Random(56312)
    p = []
    for x in range(50):
        for y in range(60):
            z = x * x + y * y
            if mode == 'noise':
                z = 10000 * z + noise.randint(-1000, 1000)
            p.append((x, y, z))
    p = p[:n]
    if mode == 'noise':
        p = [(x + 800000000, y - 800000000, z + 800000000) for x, y, z in p]
        if seed % 2 == 0:
            r.shuffle(p)
else:
    p = [tuple(r.randint(-1000000000, 1000000000) for _ in range(3)) for _ in range(n)]
if mode in ('cube', 'interior', 'duplicates', 'random'):
    r.shuffle(p)
assert len(p) == n
assert all(max(map(abs, q)) <= C for q in p)
print(n)
for q in p:
    print(*q)
