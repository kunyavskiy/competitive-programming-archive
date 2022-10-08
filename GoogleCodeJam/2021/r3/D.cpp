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


#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
clock_t __my_start_clock = clock();
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", (clock() - __my_start_clock)*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, (clock() - __my_start_clock)*1.0/CLOCKS_PER_SEC)

using namespace std;

typedef long long ll;
typedef long double ld;

namespace interpolate {

  template <typename T>
  T inverse(T a, T m) {
    T u = 0, v = 1;
    while (a != 0) {
      T t = m / a;
      m -= t * a; swap(a, m);
      u -= t * v; swap(u, v);
    }
    assert(m == 1);
    return u;
  }
  template <typename T>
  class Modular {
  public:
    using Type = typename decay<decltype(T::value)>::type;
    constexpr Modular() : value() {}
    template <typename U>
    Modular(const U& x) {
      value = normalize(x);
    }
    template <typename U>
    static Type normalize(const U& x) {
      Type v;
      if (-mod() <= x && x < mod()) v = static_cast<Type>(x);
      else v = static_cast<Type>(x % mod());
      if (v < 0) v += mod();
      return v;
    }
    const Type& operator()() const { return value; }
    template <typename U>
    explicit operator U() const { return static_cast<U>(value); }
    constexpr static Type mod() { return T::value; }
    Modular& operator+=(const Modular& other) { if ((value += other.value) >= mod()) value -= mod(); return *this; }
    Modular& operator-=(const Modular& other) { if ((value -= other.value) < 0) value += mod(); return *this; }
    template <typename U> Modular& operator+=(const U& other) { return *this += Modular(other); }
    template <typename U> Modular& operator-=(const U& other) { return *this -= Modular(other); }
    Modular& operator++() { return *this += 1; }
    Modular& operator--() { return *this -= 1; }
    Modular operator++(int) { Modular result(*this); *this += 1; return result; }
    Modular operator--(int) { Modular result(*this); *this -= 1; return result; }
    Modular operator-() const { return Modular(-value); }
    template <typename U = T>
    typename enable_if<is_same<typename Modular<U>::Type, int>::value, Modular>::type& operator*=(const Modular& rhs) {
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
    template <typename U = T>
    typename enable_if<is_same<typename Modular<U>::Type, int64_t>::value, Modular>::type& operator*=(const Modular& rhs) {
      int64_t q = static_cast<int64_t>(static_cast<long double>(value) * rhs.value / mod());
      value = normalize(value * rhs.value - q * mod());
      return *this;
    }
    template <typename U = T>
    typename enable_if<!is_integral<typename Modular<U>::Type>::value, Modular>::type& operator*=(const Modular& rhs) {
      value = normalize(value * rhs.value);
      return *this;
    }
    Modular& operator/=(const Modular& other) { return *this *= Modular(inverse(other.value, mod())); }
    template <typename U>
    friend bool operator==(const Modular<U>& lhs, const Modular<U>& rhs);
    template <typename U>
    friend bool operator<(const Modular<U>& lhs, const Modular<U>& rhs);
    template <typename U>
    friend std::istream& operator>>(std::istream& stream, Modular<U>& number);
  private:
    Type value;
  };
  template <typename T> bool operator==(const Modular<T>& lhs, const Modular<T>& rhs) { return lhs.value == rhs.value; }
  template <typename T, typename U> bool operator==(const Modular<T>& lhs, U rhs) { return lhs == Modular<T>(rhs); }
  template <typename T, typename U> bool operator==(U lhs, const Modular<T>& rhs) { return Modular<T>(lhs) == rhs; }
  template <typename T> bool operator!=(const Modular<T>& lhs, const Modular<T>& rhs) { return !(lhs == rhs); }
  template <typename T, typename U> bool operator!=(const Modular<T>& lhs, U rhs) { return !(lhs == rhs); }
  template <typename T, typename U> bool operator!=(U lhs, const Modular<T>& rhs) { return !(lhs == rhs); }
  template <typename T> bool operator<(const Modular<T>& lhs, const Modular<T>& rhs) { return lhs.value < rhs.value; }
  template <typename T> Modular<T> operator+(const Modular<T>& lhs, const Modular<T>& rhs) { return Modular<T>(lhs) += rhs; }
  template <typename T, typename U> Modular<T> operator+(const Modular<T>& lhs, U rhs) { return Modular<T>(lhs) += rhs; }
  template <typename T, typename U> Modular<T> operator+(U lhs, const Modular<T>& rhs) { return Modular<T>(lhs) += rhs; }
  template <typename T> Modular<T> operator-(const Modular<T>& lhs, const Modular<T>& rhs) { return Modular<T>(lhs) -= rhs; }
  template <typename T, typename U> Modular<T> operator-(const Modular<T>& lhs, U rhs) { return Modular<T>(lhs) -= rhs; }
  template <typename T, typename U> Modular<T> operator-(U lhs, const Modular<T>& rhs) { return Modular<T>(lhs) -= rhs; }
  template <typename T> Modular<T> operator*(const Modular<T>& lhs, const Modular<T>& rhs) { return Modular<T>(lhs) *= rhs; }
  template <typename T, typename U> Modular<T> operator*(const Modular<T>& lhs, U rhs) { return Modular<T>(lhs) *= rhs; }
  template <typename T, typename U> Modular<T> operator*(U lhs, const Modular<T>& rhs) { return Modular<T>(lhs) *= rhs; }
  template <typename T> Modular<T> operator/(const Modular<T>& lhs, const Modular<T>& rhs) { return Modular<T>(lhs) /= rhs; }
  template <typename T, typename U> Modular<T> operator/(const Modular<T>& lhs, U rhs) { return Modular<T>(lhs) /= rhs; }
  template <typename T, typename U> Modular<T> operator/(U lhs, const Modular<T>& rhs) { return Modular<T>(lhs) /= rhs; }
  template<typename T, typename U>
  Modular<T> power(const Modular<T>& a, const U& b) {
    assert(b >= 0);
    Modular<T> x = a, res = 1;
    U p = b;
    while (p > 0) {
      if (p & 1) res *= x;
      x *= x;
      p >>= 1;
    }
    return res;
  }
  template <typename T>
  string to_string(const Modular<T>& number) {
    return to_string(number());
  }
  template <typename T>
  std::ostream& operator<<(std::ostream& stream, const Modular<T>& number) {
    return stream << number();
  }
  template <typename T>
  std::istream& operator>>(std::istream& stream, Modular<T>& number) {
    typename common_type<typename Modular<T>::Type, int64_t>::type x;
    stream >> x;
    number.value = Modular<T>::normalize(x);
    return stream;
  }
/*
using ModType = int;
struct VarMod { static ModType value; };
ModType VarMod::value;
ModType& md = VarMod::value;
using Mint = Modular<VarMod>;
*/
  constexpr int md = 1000000007;
  using Mint = Modular<std::integral_constant<decay<decltype(md)>::type, md>>;
  template <typename T>
  vector<T>& operator+=(vector<T>& a, const vector<T>& b) {
    if (a.size() < b.size()) {
      a.resize(b.size());
    }
    for (int i = 0; i < (int) b.size(); i++) {
      a[i] += b[i];
    }
    return a;
  }
  template <typename T>
  vector<T> operator+(const vector<T>& a, const vector<T>& b) {
    vector<T> c = a;
    return c += b;
  }
  template <typename T>
  vector<T>& operator-=(vector<T>& a, const vector<T>& b) {
    if (a.size() < b.size()) {
      a.resize(b.size());
    }
    for (int i = 0; i < (int) b.size(); i++) {
      a[i] -= b[i];
    }
    return a;
  }
  template <typename T>
  vector<T> operator-(const vector<T>& a, const vector<T>& b) {
    vector<T> c = a;
    return c -= b;
  }
  template <typename T>
  vector<T> operator-(const vector<T>& a) {
    vector<T> c = a;
    for (int i = 0; i < (int) c.size(); i++) {
      c[i] = -c[i];
    }
    return c;
  }
  template <typename T>
  vector<T> operator*(const vector<T>& a, const vector<T>& b) {
    if (a.empty() || b.empty()) {
      return {};
    }
    vector<T> c(a.size() + b.size() - 1, 0);
    for (int i = 0; i < (int) a.size(); i++) {
      for (int j = 0; j < (int) b.size(); j++) {
        c[i + j] += a[i] * b[j];
      }
    }
    return c;
  }
  template <typename T>
  vector<T>& operator*=(vector<T>& a, const vector<T>& b) {
    return a = a * b;
  }
  template <typename T>
  vector<T> inverse(const vector<T>& a) {
    assert(!a.empty());
    int n = (int) a.size();
    vector<T> b = {1 / a[0]};
    while ((int) b.size() < n) {
      vector<T> a_cut(a.begin(), a.begin() + min(a.size(), b.size() << 1));
      vector<T> x = b * b * a_cut;
      b.resize(b.size() << 1);
      for (int i = (int) b.size() >> 1; i < (int) min(x.size(), b.size()); i++) {
        b[i] = -x[i];
      }
    }
    b.resize(n);
    return b;
  }
  template <typename T>
  vector<T>& operator/=(vector<T>& a, const vector<T>& b) {
    int n = (int) a.size();
    int m = (int) b.size();
    if (n < m) {
      a.clear();
    } else {
      vector<T> d = b;
      reverse(a.begin(), a.end());
      reverse(d.begin(), d.end());
      d.resize(n - m + 1);
      a *= inverse(d);
      a.erase(a.begin() + n - m + 1, a.end());
      reverse(a.begin(), a.end());
    }
    return a;
  }
  template <typename T>
  vector<T> operator/(const vector<T>& a, const vector<T>& b) {
    vector<T> c = a;
    return c /= b;
  }
  template <typename T>
  vector<T>& operator%=(vector<T>& a, const vector<T>& b) {
    int n = (int) a.size();
    int m = (int) b.size();
    if (n >= m) {
      vector<T> c = (a / b) * b;
      a.resize(m - 1);
      for (int i = 0; i < m - 1; i++) {
        a[i] -= c[i];
      }
    }
    return a;
  }
  template <typename T>
  vector<T> operator%(const vector<T>& a, const vector<T>& b) {
    vector<T> c = a;
    return c %= b;
  }
  template <typename T, typename U>
  vector<T> power(const vector<T>& a, const U& b, const vector<T>& c) {
    assert(b >= 0);
    vector<U> binary;
    U bb = b;
    while (bb > 0) {
      binary.push_back(bb & 1);
      bb >>= 1;
    }
    vector<T> res = vector<T>{1} % c;
    for (int j = (int) binary.size() - 1; j >= 0; j--) {
      res = res * res % c;
      if (binary[j] == 1) {
        res = res * a % c;
      }
    }
    return res;
  }
  template <typename T>
  vector<T> derivative(const vector<T>& a) {
    vector<T> c = a;
    for (int i = 0; i < (int) c.size(); i++) {
      c[i] *= i;
    }
    if (!c.empty()) {
      c.erase(c.begin());
    }
    return c;
  }

  template <typename T>
  vector<T> primitive(const vector<T>& a) {
    vector<T> c = a;
    c.insert(c.begin(), 0);
    for (int i = 1; i < (int) c.size(); i++) {
      c[i] /= i;
    }
    return c;
  }
  template <typename T>
  vector<T> logarithm(const vector<T>& a) {
    assert(!a.empty() && a[0] == 1);
    vector<T> u = primitive(derivative(a) * inverse(a));
    u.resize(a.size());
    return u;
  }

  template <typename T>
  vector<T> exponent(const vector<T>& a) {
    assert(!a.empty() && a[0] == 0);
    int n = (int) a.size();
    vector<T> b = {1};
    while ((int) b.size() < n) {
      vector<T> x(a.begin(), a.begin() + min(a.size(), b.size() << 1));
      x[0] += 1;
      vector<T> old_b = b;
      b.resize(b.size() << 1);
      x -= logarithm(b);
      x *= old_b;
      for (int i = (int) b.size() >> 1; i < (int) min(x.size(), b.size()); i++) {
        b[i] = x[i];
      }
    }
    b.resize(n);
    return b;
  }
  template <typename T>
  vector<T> sqrt(const vector<T>& a) {
    assert(!a.empty() && a[0] == 1);
    int n = (int) a.size();
    vector<T> b = {1};
    while ((int) b.size() < n) {
      vector<T> x(a.begin(), a.begin() + min(a.size(), b.size() << 1));
      b.resize(b.size() << 1);
      x *= inverse(b);
      T inv2 = 1 / static_cast<T>(2);
      for (int i = (int) b.size() >> 1; i < (int) min(x.size(), b.size()); i++) {
        b[i] = x[i] * inv2;
      }
    }
    b.resize(n);
    return b;
  }
  template <typename T>
  vector<T> multiply(const vector<vector<T>>& a) {
    if (a.empty()) {
      return {0};
    }
    function<vector<T>(int, int)> mult = [&](int l, int r) {
      if (l == r) {
        return a[l];
      }
      int y = (l + r) >> 1;
      return mult(l, y) * mult(y + 1, r);
    };
    return mult(0, (int) a.size() - 1);
  }
  template <typename T>
  T evaluate(const vector<T>& a, const T& x) {
    T res = 0;
    for (int i = (int) a.size() - 1; i >= 0; i--) {
      res = res * x + a[i];
    }
    return res;
  }
  template <typename T>
  vector<T> evaluate(const vector<T>& a, const vector<T>& x) {
    if (x.empty()) {
      return {};
    }
    if (a.empty()) {
      return vector<T>(x.size(), 0);
    }
    int n = (int) x.size();
    vector<vector<T>> st((n << 1) - 1);
    function<void(int, int, int)> build = [&](int v, int l, int r) {
      if (l == r) {
        st[v] = vector<T>{-x[l], 1};
      } else {
        int y = (l + r) >> 1;
        int z = v + ((y - l + 1) << 1);
        build(v + 1, l, y);
        build(z, y + 1, r);
        st[v] = st[v + 1] * st[z];
      }
    };
    build(0, 0, n - 1);
    vector<T> res(n);
    function<void(int, int, int, vector<T>)> eval = [&](int v, int l, int r, vector<T> f) {
      f %= st[v];
      if ((int) f.size() < 150) {
        for (int i = l; i <= r; i++) {
          res[i] = evaluate(f, x[i]);
        }
        return;
      }
      if (l == r) {
        res[l] = f[0];
      } else {
        int y = (l + r) >> 1;
        int z = v + ((y - l + 1) << 1);
        eval(v + 1, l, y, f);
        eval(z, y + 1, r, f);
      }
    };
    eval(0, 0, n - 1, a);
    return res;
  }
  template <typename T>
  vector<T> interpolate(const vector<T>& x, const vector<T>& y) {
    if (x.empty()) {
      return {};
    }
    assert(x.size() == y.size());
    int n = (int) x.size();
    vector<vector<T>> st((n << 1) - 1);
    function<void(int, int, int)> build = [&](int v, int l, int r) {
      if (l == r) {
        st[v] = vector<T>{-x[l], 1};
      } else {
        int w = (l + r) >> 1;
        int z = v + ((w - l + 1) << 1);
        build(v + 1, l, w);
        build(z, w + 1, r);
        st[v] = st[v + 1] * st[z];
      }
    };
    build(0, 0, n - 1);
    vector<T> m = st[0];
    vector<T> dm = derivative(m);
    vector<T> val(n);
    function<void(int, int, int, vector<T>)> eval = [&](int v, int l, int r, vector<T> f) {
      f %= st[v];
      if ((int) f.size() < 150) {
        for (int i = l; i <= r; i++) {
          val[i] = evaluate(f, x[i]);
        }
        return;
      }
      if (l == r) {
        val[l] = f[0];
      } else {
        int w = (l + r) >> 1;
        int z = v + ((w - l + 1) << 1);
        eval(v + 1, l, w, f);
        eval(z, w + 1, r, f);
      }
    };
    eval(0, 0, n - 1, dm);
    for (int i = 0; i < n; i++) {
      val[i] = y[i] / val[i];
    }
    function<vector<T>(int, int, int)> calc = [&](int v, int l, int r) {
      if (l == r) {
        return vector<T>{val[l]};
      }
      int w = (l + r) >> 1;
      int z = v + ((w - l + 1) << 1);
      return calc(v + 1, l, w) * st[z] + calc(z, w + 1, r) * st[v + 1];
    };
    return calc(0, 0, n - 1);
  }
}

const int MOD = 1000000007;

void add(int &a, int b) {
  if ((a += b) >= MOD) a -= MOD;
}

void sub(int &a, int b) {
  if ((a -= b) < 0) a += MOD;
}

int mul(int a, int b) {
  return (int) ((a * 1LL * b) % MOD);
}

int mpow(int a, int b) {
  int res = 1;
  while (b) {
    if (b & 1) res = mul(res, a);
    a = mul(a, a);
    b >>= 1;
  }
  return res;
}

int minv(int x) {
  return mpow(x, MOD - 2);
}

void PreCalc() {
}

void merge(vector<int>& a, const vector<int>& b, int shift) {
  while (a.size() < b.size() + shift) a.push_back(0);
  for (int i = 0; i < (int)b.size(); i++) {
    add(a[i+shift], b[i]);
  }
}

void merge_mul(vector<int>& a, const vector<int>& b, const vector<int> &c) {
  while (a.size() + 1 < b.size() + c.size()) a.push_back(0);
  for (int i = 0; i < (int) b.size(); i++) {
    for (int j = 0; j < (int) c.size(); j++) {
      add(a[i + j], mul(b[i], c[j]));
    }
  }
}


void solve() {
  int n, m, l;
  scanf("%d%d%d", &n, &m, &l);
  int levels = l;
  l = 1 << l;
  vector<int> a(l);
  vector<int> cnt(n);
  for (int i = 0; i < l; i++) {
    scanf("%d", &a[i]);
    --a[i];
    cnt[a[i]]++;
  }

  vector<int> twice;
  vector<int> twice_id(n, -1);
  for (int i = 0; i < n; i++){
    if (cnt[i] >= 2) {
      twice_id[i] = twice.size();
      twice.push_back(i);
    }
  }

  vector<int> ans;

  for (int i = 0; i < (1 << twice.size()); i++) {
    vector<vector<int>> dp0(l), dp1(l);
    for (int j = 0; j < l; j++) {
      if (twice_id[a[j]] != -1) {
        if ((i >> twice_id[a[j]]) & 1) {
          dp0[j] = {};
          dp1[j] = {1};
        } else {
          dp0[j] = {1};
          dp1[j] = {};
        }
      } else {
        dp0[j] = {1};
        dp1[j] = {0, 1};
      }
    }
    for (int lvl = levels - 1; lvl >= 0; lvl--) {
      vector<vector<int>> ndp0(dp0.size() / 2), ndp1(dp0.size() / 2);
      auto &diff = (lvl % 2 == 0) ? ndp1 : ndp0;
      for (int id = 0; id < (int) ndp0.size(); id++) {
        merge_mul(ndp0[id], dp0[2 * id], dp0[2 * id + 1]);
        merge_mul(ndp1[id], dp1[2 * id], dp1[2 * id + 1]);
        merge_mul(diff[id], dp1[2 * id], dp0[2 * id + 1]);
        merge_mul(diff[id], dp0[2 * id], dp1[2 * id + 1]);
      }
      dp0 = std::move(ndp0);
      dp1 = std::move(ndp1);
    }
    assert(dp1.size() == 1);
    merge(ans, dp1[0], __builtin_popcount(i));
  }

  int not_found = count(cnt.begin(), cnt.end(), 0);

  auto eval = [&](int m) {
    int res = mpow(m, n - not_found);
    for (int j = 0; j < (int) ans.size(); j++) {
      int cur = 0;
      for (int i = 1; i < m; i++) {
        add(cur, mul(mpow(i, n - j - not_found), mpow(m - i, j)));
      }
      add(res, mul(ans[j], cur));
    }

    return mul(res, mpow(m, not_found));
  };

  vector<interpolate::Mint> values(2 * n + 5);
  vector<interpolate::Mint> positions(2 * n + 5);
  for (int i = 0; i < (int)values.size(); i++) {
    positions[i] = i + 2;
    values[i] = eval(i + 2);
  }

  auto poly = interpolate::interpolate(positions, values);

  auto res = interpolate::evaluate(poly, interpolate::Mint{m});
  printf("%d\n", res());
}


int main() {
#ifdef LOCAL
  freopen("d.in", "r", stdin);
  freopen("d.out", "w", stdout);
#endif

  PreCalc();
  TIMESTAMP(PreCalc);

  char buf[1000];
  int testNum;
  fgets(buf, sizeof buf, stdin);
  sscanf(buf, "%d", &testNum);

  for (int testId = 1; testId <= testNum; testId++) {
    if (testId <= 20 || testId >= testNum - 20 || testId % 10 == 0)
      TIMESTAMPf("Test %d", testId);
    printf("Case #%d: ", testId);
    solve();
  }

  TIMESTAMP(end);
  return 0;
}
