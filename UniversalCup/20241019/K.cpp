#include <bits/stdc++.h>

using std::cin;
using std::cout;
using std::cerr;

using std::vector;
using std::map;
using std::array;
using std::set;
using std::string;

using std::pair;
using std::make_pair;

using std::tuple;
using std::make_tuple;
using std::get;

using std::min;
using std::abs;
using std::max;
using std::swap;

using std::unique;
using std::sort;
using std::generate;
using std::reverse;
using std::min_element;
using std::max_element;

using std::optional;

#ifdef LOCAL
#define LASSERT(X) assert(X)
#else
#define LASSERT(X) {}
#endif

template <typename T>
T input() {
  T res;
  cin >> res;
  LASSERT(cin);
  return res;
}

template <typename IT>
void input_seq(IT b, IT e) {
  std::generate(b, e, input<typename std::remove_reference<decltype(*b)>::type>);
}

#define SZ(vec)         int((vec).size())
#define ALL(data)       data.begin(),data.end()
#define RALL(data)      data.rbegin(),data.rend()
#define TYPEMAX(type)   std::numeric_limits<type>::max()
#define TYPEMIN(type)   std::numeric_limits<type>::min()

const int mod = 998244353;

template <uint32_t mod>
struct LazyMontgomeryModInt {
  using mint = LazyMontgomeryModInt;
  using i32 = int32_t;
  using u32 = uint32_t;
  using u64 = uint64_t;

  static constexpr u32 get_r() {
    u32 ret = mod;
    for (i32 i = 0; i < 4; ++i) ret *= 2 - mod * ret;
    return ret;
  }

  static constexpr u32 r = get_r();
  static constexpr u32 n2 = -u64(mod) % mod;
  static_assert(mod < (1 << 30), "invalid, mod >= 2 ^ 30");
  static_assert((mod & 1) == 1, "invalid, mod % 2 == 0");
  static_assert(r * mod == 1, "this code has bugs.");

  u32 a;

  constexpr LazyMontgomeryModInt() : a(0) {}
  constexpr LazyMontgomeryModInt(const int64_t &b)
      : a(reduce(u64(b % mod + mod) * n2)){};

  static constexpr u32 reduce(const u64 &b) {
    return (b + u64(u32(b) * u32(-r)) * mod) >> 32;
  }

  constexpr mint &operator+=(const mint &b) {
    if (i32(a += b.a - 2 * mod) < 0) a += 2 * mod;
    return *this;
  }

  constexpr mint &operator-=(const mint &b) {
    if (i32(a -= b.a) < 0) a += 2 * mod;
    return *this;
  }

  constexpr mint &operator*=(const mint &b) {
    a = reduce(u64(a) * b.a);
    return *this;
  }

  constexpr mint &operator/=(const mint &b) {
    *this *= b.inverse();
    return *this;
  }

  constexpr mint operator+(const mint &b) const { return mint(*this) += b; }
  constexpr mint operator-(const mint &b) const { return mint(*this) -= b; }
  constexpr mint operator*(const mint &b) const { return mint(*this) *= b; }
  constexpr mint operator/(const mint &b) const { return mint(*this) /= b; }
  constexpr bool operator==(const mint &b) const {
    return (a >= mod ? a - mod : a) == (b.a >= mod ? b.a - mod : b.a);
  }
  constexpr bool operator!=(const mint &b) const {
    return (a >= mod ? a - mod : a) != (b.a >= mod ? b.a - mod : b.a);
  }
  constexpr mint operator-() const { return mint() - mint(*this); }
  constexpr mint operator+() const { return mint(*this); }

  constexpr mint pow(u64 n) const {
    mint ret(1), mul(*this);
    while (n > 0) {
      if (n & 1) ret *= mul;
      mul *= mul;
      n >>= 1;
    }
    return ret;
  }

  constexpr mint inverse() const {
    int x = get(), y = mod, u = 1, v = 0, t = 0, tmp = 0;
    while (y > 0) {
      t = x / y;
      x -= t * y, u -= t * v;
      tmp = x, x = y, y = tmp;
      tmp = u, u = v, v = tmp;
    }
    return mint{u};
  }

  friend std::ostream &operator<<(std::ostream &os, const mint &b) {
    return os << b.get();
  }

  friend std::istream &operator>>(std::istream &is, mint &b) {
    int64_t t;
    is >> t;
    b = LazyMontgomeryModInt<mod>(t);
    return (is);
  }

  constexpr u32 get() const {
    u32 ret = reduce(a);
    return ret >= mod ? ret - mod : ret;
  }

  static constexpr u32 get_mod() { return mod; }
};

using mint = LazyMontgomeryModInt<mod>;

const int max_n = 8003;
mint m_n[max_n][max_n];
mint binom[max_n][max_n];

void precalc() {
  for (int m = 0; m < max_n; ++m) {
    m_n[0][m] = 1;
  }

  for (int n = 1; n < max_n; ++n) {
    for (int m = 0; m < max_n; ++m) {
      m_n[n][m] = m_n[n - 1][m] * m;
    }
  }

  for (int n = 0; n < max_n; ++n) {
    binom[n][0] = binom[n][n] = 1;

    for (int t = 1; t < n; ++t) {
      binom[n][t] = binom[n - 1][t] + binom[n - 1][t - 1];
    }
  }

  for (int i = 0; i < max_n; i++) {
    for (int j = 0; j < max_n; j += 2) {
      binom[i][j] = mint{0} - binom[i][j];
    }
  }
}

#ifdef LOCAL
#define TEST
#endif

void solve() {
  int n, m;
#ifdef TEST
  n = m = 8000;
#else
  cin >> n >> m;
#endif

  mint ans = 0;
  for (int forb = 0; forb <= m; ++forb) {
    ans += m_n[n][m - forb] * binom[m + 1][forb + 1];
  }

  ans = ans / m_n[n][m];
  ans = ans - mint{1};
  cout << ans << "\n";
}

int main() {
#ifdef LOCAL
  freopen("k.in", "r", stdin);
#endif
  precalc();
#ifdef TEST
  int T = 300000;
#else
  int T = input<int>();
#endif
  for (int t = T; t; --t) {
    solve();
  }
  return 0;
}