#!/usr/bin/env python3
"""
Testcase generator for Codeforces Gym 106033E (Dinic Max Flow + Route Decomposition).
Usage: python3 106033E_gen.py <output_directory>
"""

import os
import random
import sys
from pathlib import Path


def generate_cases(output_dir: Path):
    output_dir.mkdir(parents=True, exist_ok=True)
    random.seed(106033)

    cases = []

    # Case 1: Simple handcrafted testcase
    cases.append("""4 4
1 2 5
1 3 3
2 4 4
3 4 4
""")

    # Case 2: Disconnected graph (maxflow = 0)
    cases.append("""5 3
1 2 10
2 3 5
4 5 10
""")

    # Case 3: Line graph
    cases.append("""6 5
1 2 100
2 3 50
3 4 70
4 5 20
5 6 90
""")

    # Case 4: Multiple parallel-like independent paths
    cases.append("""8 9
1 2 10
2 8 10
1 3 20
3 8 15
1 4 30
4 8 25
1 5 5
5 8 5
1 8 50
""")

    # Case 5: Small random DAG
    def random_dag(n, m, max_c):
        edges = []
        possible = [(u, v) for u in range(1, n + 1) for v in range(u + 1, n + 1)]
        random.shuffle(possible)
        m = min(m, len(possible))
        for u, v in possible[:m]:
            c = random.randint(1, max_c)
            edges.append((u, v, c))
        lines = [f"{n} {len(edges)}"]
        for u, v, c in edges:
            lines.append(f"{u} {v} {c}")
        return "\n".join(lines) + "\n"

    cases.append(random_dag(n=6, m=10, max_c=100))
    cases.append(random_dag(n=15, m=30, max_c=1000))
    cases.append(random_dag(n=30, m=80, max_c=10**9))

    # Case 8: Graph with cycles (non-DAG)
    def random_graph_with_cycles(n, m, max_c):
        edges = []
        existing = set()
        while len(edges) < m:
            u = random.randint(1, n)
            v = random.randint(1, n)
            if u != v and (u, v) not in existing:
                existing.add((u, v))
                c = random.randint(1, max_c)
                edges.append((u, v, c))
        lines = [f"{n} {len(edges)}"]
        for u, v, c in edges:
            lines.append(f"{u} {v} {c}")
        return "\n".join(lines) + "\n"

    cases.append(random_graph_with_cycles(n=10, m=25, max_c=500))
    cases.append(random_graph_with_cycles(n=20, m=60, max_c=10**9))

    # Write all cases
    for idx, content in enumerate(cases, start=1):
        filename = output_dir / f"gen_{idx:02d}.in"
        filename.write_text(content)

    print(f"Generated {len(cases)} test cases in {output_dir}")


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python3 106033E_gen.py <output_directory>", file=sys.stderr)
        sys.exit(1)

    generate_cases(Path(sys.argv[1]))
