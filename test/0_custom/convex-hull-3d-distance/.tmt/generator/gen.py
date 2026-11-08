import itertools
import math
import random
import sys

mode, n, q, seed = sys.argv[1], int(sys.argv[2]), int(sys.argv[3]), int(sys.argv[4])
r = random.Random(seed)
C = 1000000

def sub(a, b):
    return tuple(x - y for x, y in zip(a, b))
def cross(a, b):
    return (a[1] * b[2] - a[2] * b[1], a[2] * b[0] - a[0] * b[2], a[0] * b[1] - a[1] * b[0])
def dot(a, b):
    return sum(x * y for x, y in zip(a, b))
def normal(a, b, c):
    v = cross(sub(b, a), sub(c, a))
    g = math.gcd(math.gcd(abs(v[0]), abs(v[1])), abs(v[2]))
    return tuple(x // g for x in v) if g else None

def facet_normals(points):
    result = set()
    for a, b, c in itertools.combinations(points, 3):
        v = normal(a, b, c)
        if v is None:
            continue
        d = dot(v, a)
        values = [dot(v, x) - d for x in points]
        if min(values) < 0 < max(values):
            continue
        if min(values) == max(values) == 0:
            continue
        if max(values) > 0:
            v = tuple(-x for x in v)
        result.add(v)
    return sorted(result)

if mode == 'grid':
    xy = [(x, y) for x in range(25) for y in range(20)][:n]
    present = set(xy)
    p = [(x, y, x * x + y * y) for x, y in xy]
    normals = [(2 * x + 1, 2 * y + 1, -1) for x, y in xy if {(x + 1, y), (x, y + 1), (x + 1, y + 1)} <= present]
    if seed % 2:
        p = [tuple(x + 500000 for x in a) for a in p]
elif mode == 'pyramid':
    t = list(range(-(n - 1) // 2, -(n - 1) // 2 + n - 1))
    base = [(x, x * x, 0) for x in t]
    apex = (0, 1000, 500)
    p = base + [apex]
    normals = [(0, 0, -1)]
    for i, a in enumerate(base):
        v = normal(a, base[(i + 1) % len(base)], apex)
        if max(dot(v, x) - dot(v, a) for x in p) > 0:
            v = tuple(-x for x in v)
        normals.append(v)
else:
    if mode in ('box', 'translated', 'duplicates'):
        base = list(itertools.product([-100, 100], repeat=3))
        p = base[:]
        if mode == 'duplicates':
            p = [base[i % 8] for i in range(n)]
        else:
            p += [tuple(r.randint(-99, 99) for _ in range(3)) for _ in range(n - 8)]
        if mode == 'translated':
            p = [tuple(x + 500000 for x in a) for a in p]
            base = [tuple(x + 500000 for x in a) for a in base]
    elif mode == 'prefix':
        p = [(i, 0, 0) for i in range(n - 3)] + [(0, 100, 0), (0, 0, 100), (1, 1, 1)]
        base = [(0, 0, 0), (n - 4, 0, 0), (0, 100, 0), (0, 0, 100)]
    elif mode == 'huge':
        m = C - 1
        p = [(-m, -m, m), (-m, m, -m + 1), (m - 1, -m, -m), (m, m, m)]
        base = p[:]
    elif mode == 'thin':
        p = [(0, 0, 0), (C, 1, 0), (C - 1, 1, 0), (C - 2, 1, 1)]
        base = p[:]
    elif mode == 'tetra':
        p = [(0, 0, 0), (2, 0, 0), (0, 2, 0), (0, 0, 2)]
        base = p[:]
    else:
        p = [tuple(r.randint(-C, C) for _ in range(3)) for _ in range(n)]
        base = p[:]
    normals = facet_normals(base)
assert len(p) == n and normals
assert all(max(map(abs, a)) <= C for a in p)
assert all(max(map(abs, v)) <= 8000000000000 for v in normals)
support = {}
for v in normals:
    d = max(dot(v, x) for x in p)
    support[v] = next(x for x in p if dot(v, x) == d)
print(n, q)
for a in p:
    print(*a)
for j in range(q):
    v = normals[j % len(normals)]
    kind = j % 8
    if kind == 0:
        a = support[v]
    elif kind == 1:
        a = p[r.randrange(len(p))]
    elif kind == 2:
        a = (C, C, C)
    elif kind == 3:
        a = (-C, -C, -C)
    elif kind == 5:
        a = (0, 0, 0)
    elif kind == 6:
        a = (C, -C, C)
    else:
        a = tuple(r.randint(-C, C) for _ in range(3))
    if mode == 'huge' and j == 0:
        a = p[3]
        v = max(normals, key=lambda v: abs(dot(v, a) - max(dot(v, x) for x in p)))
        assert abs(dot(v, a) - max(dot(v, x) for x in p)) > 2**63
    print(*v, *a)
