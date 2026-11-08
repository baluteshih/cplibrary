import math
import random
import sys

mode, count, seed = sys.argv[1], int(sys.argv[2]), int(sys.argv[3])
large = mode.startswith('large-')
if large:
    mode = mode[6:]
limit = 1000000000 if large else 1000000
rng = random.Random(seed)
bound = 1000000
extra = []
if mode == 'box':
    bound = 7
elif mode == 'fraction':
    bound = 5
    extra = [(3, 0, 0, 2), (0, 3, -2, 0), (-3, 0, 0, -2), (0, -3, 2, 0)]
elif mode == 'parallel':
    bound = 100
    for i in range(count - 4):
        c = 1 + i % 40
        extra.append((c, -1, c, 1) if i % 2 else (-1, -c, 1, -c))
    if seed % 2:
        extra.reverse()
elif mode == 'duplicates':
    sides = [(-1, -30, 1, -30), (30, -1, 30, 1), (1, 30, -1, 30), (-30, 1, -30, -1)]
    for i in range(count - 4):
        a, b, c, d = sides[i % 4]
        extra.append((a, b, c, d))
        if i % 2:
            extra[-1] = (2 * a - c, 2 * b - d, 2 * c - a, 2 * d - b)
elif mode == 'corner':
    bound = 100
    for i in range(count - 4):
        a, b = 1 + i % 37, 1 + (i // 37) % 41
        extra.append((-bound, -bound, -bound + b, -bound - a))
elif mode == 'thin':
    bound = limit
    sides = [(limit - 1, -limit + 2, -1, 1), (-limit + 1, limit - 2, 1, -1),
             (1, -1, -limit + 2, limit - 1), (-1, 1, limit - 2, -limit + 1)]
    extra = [sides[i % 4] for i in range(count - 4)]
elif mode == 'lattice':
    k = 20 if count < 10000 else 140
    vectors = [(1, 0), (0, 1), (-1, 0), (0, -1)]
    for x in range(1, k + 1):
        for y in range(1, k + 1):
            if math.gcd(x, y) == 1:
                vectors.extend([(x, y), (-y, x), (-x, -y), (y, -x)])
    vectors.sort(key=lambda p: math.atan2(p[1], p[0]))
    vertices = []
    x = y = 0
    for dx, dy in vectors:
        vertices.append((x, y))
        x += dx
        y += dy
    assert x == y == 0
    cx = (min(x for x, y in vertices) + max(x for x, y in vertices)) // 2
    cy = (min(y for x, y in vertices) + max(y for x, y in vertices)) // 2
    vertices = [(x - cx, y - cy) for x, y in vertices]
    extra = [vertices[i] + vertices[(i + 1) % len(vertices)] for i in range(len(vertices))]
    assert len(extra) <= count - 4
    extra += [extra[rng.randrange(len(extra))] for _ in range(count - 4 - len(extra))]
else:
    bound = limit
    radius = limit if large or seed % 2 else 200
    for i in range(count - 4):
        x, y = rng.randint(-radius, radius), rng.randint(-radius, radius)
        if x == y == 0:
            x = 1
        extra.append((x, y, -y, x))
if mode not in ('parallel',):
    rng.shuffle(extra)
if large and mode == 'lattice':
    bound *= 1000
    extra = [tuple(x * 1000 for x in line) for line in extra]
lines = [(-bound, -bound, bound, -bound), (bound, -bound, bound, bound),
         (bound, bound, -bound, bound), (-bound, bound, -bound, -bound)] + extra
assert len(lines) == count
assert all(max(map(abs, p)) <= limit for p in lines)
print(len(lines), bound)
for line in lines:
    print(*line)
