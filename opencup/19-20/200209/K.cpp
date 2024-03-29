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

  constexpr int MOD = 998244353;
  using mint = Mint<std::integral_constant<decay<decltype(MOD)>::type, MOD>>;
//using mint = Mint<DynamicMod>;
}
using namespace n_mint;

int main() {
#ifdef LOCAL
  freopen("k.in", "r", stdin);
//  freopen("k.out", "w", stdout);
#endif

  const int N = 2020;
//  const int N = 410;
  vector<vector<vector<mint>>> dp(N / 2);
  for (int ans = 1; ans < (int)dp.size(); ans++) {
    int max_n = 1;
//    while ((max_n + 1) * ans <= N) max_n++;
    if (ans == 1) max_n = N;
    else {
      while ((N + max_n) / (max_n + 1) >= ans) max_n++;
    }
//    db2(ans, max_n);


    int n = max_n + 1;
    int m = N;

    dp[ans].assign(n, vector<mint>(m));


    vector<vector<vector<mint>>> sum(2, vector<vector<mint>>(n, vector<mint>(m)));
    sum[0][0][0] = sum[1][0][0] = 1;

    auto get_sum = [&](int f, int lx, int ly, int rx, int ry) {
      if (rx < 0 || ry < 0) return mint(0);
      mint res = 0;
      res += sum[f][rx][ry];
      if (lx > 0) res -= sum[f][lx - 1][ry];
      if (ly > 0) res -= sum[f][rx][ly - 1];
      if (lx > 0 && ly > 0) res += sum[f][lx - 1][ly - 1];
      return res;
    };

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        if (i + j == 0) continue;

        for (int f = 0; f < 2; f++) {
          mint val = 0;
          if (f == 0) val += get_sum(f ^ 1, i - ans, j, i - 1, j);
          else val += get_sum(f ^ 1, i, j - ans, i, j - 1);
          if (i > 0) val += sum[f][i - 1][j];
          if (j > 0) val += sum[f][i][j - 1];
          if (i > 0 && j > 0) val -= sum[f][i - 1][j - 1];
          sum[f][i][j] = val;
        }
        dp[ans][i][j] = get_sum(0, i, j, i, j) + get_sum(1, i, j, i, j);
      }
    }
  }

  for (int xx = 1; xx <= 2000; xx++) {
    for (int yy = 1; yy <= 2000; yy++) {
      int x = xx;
      int y = yy;

      if (x > y) swap(x, y);
      int ans = (y + x) / (x + 1);

//      db3(x, y, ans);
      assert(ans < (int)dp.size());
      assert(x < (int)dp[ans].size());
      assert(y < (int)dp[ans][x].size());
    }
  }

  int T;
  scanf("%d", &T);
  while (T--) {
    int x, y;
    scanf("%d%d", &x, &y);
    if (x > y) swap(x, y);
    int ans = (y + x) / (x + 1);

    assert(ans < (int)dp.size());
    assert(x < (int)dp[ans].size());
    assert(y < (int)dp[ans][x].size());

    cout << dp[ans][x][y] << endl;
  }

  return 0;
}
