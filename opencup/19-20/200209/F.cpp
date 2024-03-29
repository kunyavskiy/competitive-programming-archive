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

vector<mint> fact = {1};
vector<mint> ifact = {1};

mint get_c(int n, int k) {
  if (k < 0 || k > n) return 0;
  while (n >= (int)fact.size()) {
    mint q = (int)fact.size();
    fact.push_back(fact.back() * q);
    ifact.push_back(fact.back().inv());
  }
  return fact[n] * ifact[k] * ifact[n - k];
}



int main() {
#ifdef LOCAL
  freopen("f.in", "r", stdin);
  freopen("f.out", "w", stdout);
#endif

  int n, m;
  scanf("%d%d", &n, &m);

  vector<mint> x(2 * n + 1);
  x[0] = 1;
  for (int i = 1; i < (int)x.size(); i++) {
    x[i] = 2 * x[i - 1] - get_c(i - 1, n - 1);
  }

  vector<mint> pinv2(2 * n + 1);
  pinv2[0] = 1;
  for (int i = 1; i < (int)pinv2.size(); i++) {
    pinv2[i] = pinv2[i - 1] / 2;
  }

  for (int i = 0; i < (int)x.size(); i++) {
    x[i] *= pinv2[i];
  }


  for (int test = 0; test < m; test++) {
    int k;
    scanf("%d", &k);
    vector<int> a(k);
    for (int i = 0; i < k; i++) {
      scanf("%d", &a[i]);
      --a[i];
    }

    mint ans = 0;
    for (int i = 0; i < k; i++) {
      ans += pinv2[i] * (1 - x[a[i] - i]);
    }

    //ans += pinv2[1] * (1 - x[a[0]]);

    int N = a[k - 1] - (k - 1);
    int max_v = n - k + 1;

    mint prob = x[N];
    for (int i = n - 1; i >= max_v; i--) {
      prob -= get_c(N, i) * pinv2[N];
    }

    ans += prob * pinv2[k - 1];

    printf("%d\n", ans());
  }

  return 0;
}
