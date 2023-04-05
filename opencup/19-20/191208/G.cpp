#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <cstring>
#include <string>
#include <cmath>
#include <cassert>
#include <ctime>
#include <algorithm>
#include <sstream>
#include <list>
#include <queue>
#include <deque>
#include <stack>
#include <cstdlib>
#include <cstdio>
#include <iterator>
#include <functional>
#include <bitset>
#include <random>

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
clock_t __my_start_clock = clock();
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", (clock() - __my_start_clock)*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, (clock() - __my_start_clock)*1.0/CLOCKS_PER_SEC)

#define db(x) cerr << #x << " = " << x << endl
#define db2(x, y) cerr << "(" << #x << ", " << #y << ") = (" << x << ", " << y << ")\n";
#define db3(x, y, z) cerr << "(" << #x << ", " << #y << ", " << #z << ") = (" << x << ", " << y << ", " << z << ")\n"
#define dbv(a) cerr << #a << " = "; for (auto xxxx: a) cerr << xxxx << " "; cerr << endl


using namespace std;

#ifdef LOCAL
static struct __timestamper {
  string what;
  __timestamper(const char* what) : what(what){};
  __timestamper(const string& what) : what(what){};
  ~__timestamper(){
    TIMESTAMPf("%s", what.data());
	}
} __TIMESTAMPER("end");
#else 
struct __timestamper {};
#endif

typedef long long ll;
typedef long double ld;

namespace n_mint {
// Almost everything is copied from https://github.com/the-tourist/algo/blob/master/numeric/mint.cpp

  template<typename T>
  T inverse(T a, T m) {
    T u = 0, v = 1;
    while (a != 0) {
      T t = m / a;
      m -= t * a;
      swap(a, m);
      u -= t * v;
      swap(u, v);
    }
    assert(m == 1);
    return u;
  }

  template<typename T>
  class Mint {
  public:
    using Arg = T;
    using Type = typename decay<decltype(T::value)>::type;

    constexpr Mint() : value() {}

    template<typename U>
    Mint(const U &x) {
      value = normalize(x);
    }

    template<typename U>
    static Type normalize(const U &x) {
      Type v;
      if (-mod() <= x && x < mod()) v = static_cast<Type>(x);
      else v = static_cast<Type>(x % mod());
      if (v < 0) v += mod();
      return v;
    }

    const Type &operator()() const { return value; }

    template<typename U>
    explicit operator U() const { return static_cast<U>(value); }

    constexpr static Type mod() { return T::value; }

    Mint &operator+=(const Mint &other) {
      if ((value += other.value) >= mod()) value -= mod();
      return *this;
    }

    Mint &operator-=(const Mint &other) {
      if ((value -= other.value) < 0) value += mod();
      return *this;
    }

    template<typename U>
    Mint &operator+=(const U &other) { return *this += Mint(other); }

    template<typename U>
    Mint &operator-=(const U &other) { return *this -= Mint(other); }

    Mint &operator++() { return *this += 1; }

    Mint &operator--() { return *this -= 1; }

    const Mint operator++(int) {
      Mint result(*this);
      *this += 1;
      return result;
    }

    const Mint operator--(int) {
      Mint result(*this);
      *this -= 1;
      return result;
    }

    Mint operator-() const { return Mint(-value); }

    template<typename U = T>
    typename enable_if<is_same<typename Mint<U>::Type, int>::value, Mint>::type &operator*=(const Mint &rhs) {
#ifdef _WIN32
      uint64_t x = static_cast<int64_t>(value) * static_cast<int64_t>(rhs.value);
            uint32_t xh = static_cast<uint32_t>(x >> 32), xl = static_cast<uint32_t>(x), d, m;
            asm(
                "divl %4; \n\t"
                : "=a" (d), "=d" (m)
                : "d" (xh), "a" (xl), "r" (mod())
            );
            value = m;
#else
      value = normalize(static_cast<int64_t>(value) * static_cast<int64_t>(rhs.value));
#endif
      return *this;
    }

    template<typename U = T>
    typename enable_if<is_same<typename Mint<U>::Type, int64_t>::value, Mint>::type &operator*=(const Mint &rhs) {
      auto q = static_cast<int64_t>(static_cast<long double>(value) * rhs.value / mod());
      value = normalize(value * rhs.value - q * mod());
      return *this;
    }

    template<typename U = T>
    typename enable_if<!is_integral<typename Mint<U>::Type>::value, Mint>::type &operator*=(const Mint &rhs) {
      value = normalize(value * rhs.value);
      return *this;
    }

    Mint &operator/=(const Mint &other) { return *this *= Mint(inverse(other.value, mod())); }

    Mint inv() const { return Mint(inverse(value, mod())); }

    template<typename U>
    friend bool operator==(const Mint<U> &lhs, const Mint<U> &rhs);

    template<typename U>
    friend bool operator<(const Mint<U> &lhs, const Mint<U> &rhs);

    template<typename U>
    friend bool operator>(const Mint<U> &lhs, const Mint<U> &rhs);

    template<typename U>
    friend std::istream &operator>>(std::istream &stream, Mint<U> &number);

  private:
    Type value;
  };

  template<typename T>
  Mint<T> abs(const Mint<T> &val) { return val; }

  template<typename T>
  bool operator==(const Mint<T> &lhs, const Mint<T> &rhs) { return lhs.value == rhs.value; }

  template<typename T, typename U>
  bool operator==(const Mint<T> &lhs, U rhs) { return lhs == Mint<T>(rhs); }

  template<typename T, typename U>
  bool operator==(U lhs, const Mint<T> &rhs) { return Mint<T>(lhs) == rhs; }

  template<typename T>
  bool operator!=(const Mint<T> &lhs, const Mint<T> &rhs) { return !(lhs == rhs); }

  template<typename T, typename U>
  bool operator!=(const Mint<T> &lhs, U rhs) { return !(lhs == rhs); }

  template<typename T, typename U>
  bool operator!=(U lhs, const Mint<T> &rhs) { return !(lhs == rhs); }

  template<typename T>
  bool operator<(const Mint<T> &lhs, const Mint<T> &rhs) { return lhs.value < rhs.value; }

  template<typename T>
  bool operator>(const Mint<T> &lhs, const Mint<T> &rhs) { return lhs.value > rhs.value; }

  template<typename T>
  Mint<T> operator+(const Mint<T> &lhs, const Mint<T> &rhs) { return Mint<T>(lhs) += rhs; }

  template<typename T, typename U>
  Mint<T> operator+(const Mint<T> &lhs, U rhs) { return Mint<T>(lhs) += rhs; }

  template<typename T, typename U>
  Mint<T> operator+(U lhs, const Mint<T> &rhs) { return Mint<T>(lhs) += rhs; }

  template<typename T>
  Mint<T> operator-(const Mint<T> &lhs, const Mint<T> &rhs) { return Mint<T>(lhs) -= rhs; }

  template<typename T, typename U>
  Mint<T> operator-(const Mint<T> &lhs, U rhs) { return Mint<T>(lhs) -= rhs; }

  template<typename T, typename U>
  Mint<T> operator-(U lhs, const Mint<T> &rhs) { return Mint<T>(lhs) -= rhs; }

  template<typename T>
  Mint<T> operator*(const Mint<T> &lhs, const Mint<T> &rhs) { return Mint<T>(lhs) *= rhs; }

  template<typename T, typename U>
  Mint<T> operator*(const Mint<T> &lhs, U rhs) { return Mint<T>(lhs) *= rhs; }

  template<typename T, typename U>
  Mint<T> operator*(U lhs, const Mint<T> &rhs) { return Mint<T>(lhs) *= rhs; }

  template<typename T>
  Mint<T> operator/(const Mint<T> &lhs, const Mint<T> &rhs) { return Mint<T>(lhs) /= rhs; }

  template<typename T, typename U>
  Mint<T> operator/(const Mint<T> &lhs, U rhs) { return Mint<T>(lhs) /= rhs; }

  template<typename T, typename U>
  Mint<T> operator/(U lhs, const Mint<T> &rhs) { return Mint<T>(lhs) /= rhs; }

  template<typename T, typename U>
  Mint<T> bin(const Mint<T> &a, const U &b) {
    assert(b >= 0);
    Mint<T> x = a, res = 1;
    U p = b;
    while (p > 0) {
      if (p & 1) res *= x;
      x *= x;
      p >>= 1;
    }
    return res;
  }

  template <typename T>
  Mint<T> inv(const Mint<T> &a) {
    return inverse(a(), Mint<T>::mod());
  }

  template<typename T>
  string to_string(const Mint<T> &number) {
    return std::to_string(number());
  }

  template<typename T>
  std::ostream &operator<<(std::ostream &stream, const Mint<T> &number) {
    return stream << number();
  }

  template<typename T>
  std::istream &operator>>(std::istream &stream, Mint<T> &number) {
    typename common_type<typename Mint<T>::Type, int64_t>::type x;
    stream >> x;
    number.value = Mint<T>::normalize(x);
    return stream;
  }

  template<typename T, typename Enabled = void>
  struct is_modular : std::false_type {};

  template<typename T>
  struct is_modular<T, typename enable_if<
    is_same<T, Mint<typename T::Arg>>::value &&
    is_integral<typename T::Type>::value
  >::type> : true_type {};

  struct DynamicMod {
    static int value;
  };

  constexpr int MOD = (int)1e9 + 7;
  using mint = Mint<std::integral_constant<decay<decltype(MOD)>::type, MOD>>;
//using mint = Mint<DynamicMod>;
}
using namespace n_mint;

template<typename T>
struct linear {
  T mul;
  T add;

  T apply(T x) {
    return x * mul + add;
  }

  linear inv() const {
    linear res;
    // mul * (res.mul * x + res.add) + add = 1 * x + 0
    // mul * res.mul * x + mul * res.add + add = 1 * x + 0
    res.mul = 1 / mul;
    res.add = -add / mul;
    return res;
  }

  linear combine(const linear &t) const {
    linear res;
    // x -> t.mul * (mul * x + add) + t.add
    res.mul = t.mul * mul;
    res.add = t.add + t.mul * add;
    return res;
  }
};

template<typename T>
struct my_vector {
  vector<T> a;
  linear<T> lazy{1, 0};

  void push_front(const T &x) {
    a.push_back(lazy.inv().apply(x));
  }

  int size() const {
    return a.size();
  }

  T get(int id) {
    assert(0 <= id && id < size());
    return lazy.apply(a[(int)a.size() - id - 1]);
  }

  void set(int id, T val) {
    assert(0 <= id && id < size());
    a[(int)a.size() - id - 1] = lazy.inv().apply(val);
  }

  T back() {
    return get(size() - 1);
  }

  void apply_linear(linear<T> l, int suf) {
    assert(0 <= suf && suf <= size());
    linear<T> ol = l.inv();
    for (int i = 0; i < suf; i++) {
      set(i, ol.apply(get(i)));
    }
    lazy = lazy.combine(l);
  }

  void feed_vector(my_vector<T> &nw) {
    assert(nw.size() <= size());
    for (int i = 0; i < nw.size(); i++) {
      set(i, get(i) * nw.get(i));
    }
    apply_linear({nw.back(), 0}, nw.size());
  }
};

int solve(vector<vector<int>> e) {
  int n = e.size();
  if (n == 1) return 1;
  vector<my_vector<mint>> vcts(n);
  function<my_vector<mint>*(int, int)> dfs = [&](int v, int pr) {
    my_vector<mint> *cur = &vcts[v];
    cur->push_front(1);

    for (int to : e[v]) {
      if (to == pr) continue;
      auto *nw = dfs(to, v);
      if (nw->size() > cur->size()) swap(nw, cur);
      cur->feed_vector(*nw);
    }
    cur->push_front(0);
    cur->apply_linear({1, 1}, 0);

    return cur;
  };

  vector<my_vector<mint>*> vct;
  for (int to : e[0]) {
    vct.push_back(dfs(to, 0));
  }
  sort(vct.begin(), vct.end(), [&](my_vector<mint> *x, my_vector<mint> *y) {
    return x->size() > y->size();
  });

  my_vector<mint> prod = *vct[0];
  for (int i = 1; i < (int)vct.size(); i++) {
    prod.feed_vector(*vct[i]);
  }


  mint all = 1;
  for (auto v : vct) {
    all *= v->back();
  }
  mint sub = 0;
  for (int i = 0; i < (int)vct.size(); i++) {
    for (int h = 1; h < (int)vct[i]->size(); h++) {
      mint cur_ways = (*vct[i]).get(h) - (*vct[i]).get(h - 1);
      sub += cur_ways * (prod.get(h - 1) / (*vct[i]).get(h - 1));
    }
  }

  mint ans = all - sub;
  return ans();
}

void stress() {
  for (int it = 4;; it++) {
    mt19937 rnd(it);
    db(it);

    int n = rnd() % 10 + 1;
    vector<vector<int>> e(n);
    for (int i = 1; i < n; i++) {
      int pr = rnd() % i;
      e[pr].push_back(i);
      e[i].push_back(pr);
    }
    solve(e);
  }
}

int main() {
#ifdef LOCAL
  freopen("g.in", "r", stdin);
//  freopen("g.out", "w", stdout);
#endif
  stress();

  int T;
  scanf("%d", &T);
  for (int test = 1; test <= T; test++) {
    int n;
    scanf("%d", &n);
    vector<vector<int>> e(n);
    for (int i = 0; i < n - 1; i++) {
      int u, v;
      scanf("%d%d", &u, &v);
      u--; v--;
      e[u].push_back(v);
      e[v].push_back(u);
    }


    int ans = solve(e);
    printf("Case #%d: %d\n", test, ans);
  }

  return 0;
}
