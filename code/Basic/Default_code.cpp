#ifndef __BALU_DEFAULT_CODE__
#define __BALU_DEFAULT_CODE__
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
#define X first
#define Y second
#define SZ(a) ((int)a.size())
#define ALL(v) v.begin(), v.end()
template<class A, class B>
ostream& operator<<(ostream& os, const pair<A, B> &a) {
    os << "(" << a.first << ", " << a.second << ")";
    return os;
}
template<class T>
ostream& operator<<(ostream& os, const vector<T> &a) {
    os << "[ ";
    for (int i = 0; i < int(a.size()); ++i) {
        os << a[i];
        if (i + 1 < int(a.size()))
            os << ", ";
    }
    os << " ]";
    return os;
}
#ifdef bbq
#include <experimental/iterator>
#define safe cerr<<__PRETTY_FUNCTION__<<" line "<<__LINE__<<" safe\n"
#define debug(a...) debug_(#a, a)
#define orange(a...) orange_(#a, a)
void debug_(auto s, auto ...a) {
  cerr << "\e[1;32m(" << s << ") = (";
  int f = 0;
  (..., (cerr << (f++ ? ", " : "") << a));
  cerr << ")\e[0m\n";
}
void orange_(auto s, auto L, auto R) {
  cerr << "\e[1;33m[ " << s << " ] = [ ";
  using namespace experimental;
  copy(L, R, make_ostream_joiner(cerr, ", "));
  cerr << " ]\e[0m\n";
}
#else
#define safe ((void)0)
#define debug(...) safe
#define orange(...) safe
#endif

void chmax(auto &x, auto val) {
    x = max(x, val);
}

void chmin(auto &x, auto val) {
    x = min(x, val);
}
#endif // __BALU_DEFAULT_CODE__
