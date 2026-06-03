A personal library for competitive programming.

If you spot any bugs, please feel free to open an [issue](https://github.com/baluteshih/cplibrary/issues/new). However, since this library is tailored strictly to my personal needs, please refrain from submitting Pull Requests (PRs) to add new code.

This project is licensed under the CC0 1.0 Universal - do whatever you want with it!
- Note: Attribution is not required, but highly appreciated if you find this library helpful!

As a note, the templates in this library follow these design conventions:
* Self-Contained: The code assumes `#include <bits/stdc++.h>` is already present. Beyond that, it aims to be entirely self-contained without relying on any additional boilerplate or default code.
* Namespace: I strive to consistently write without `using namespace std;`. Any accidental omissions will be fixed gradually over time.
* Indexing: Most data structures use $0$-based indexing.
* Operator Overloading: For binary operations between elements, the library generally expects the element types to have overloaded operators (e.g., `operator+`).
