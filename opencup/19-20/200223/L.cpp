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
#include <numeric>

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
      value = normalize(static_cast<int64_t>(value) * static_cast<int64_t>(rhs.value));
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
  constexpr int MOD = 1000'000'007;
  using mint = Mint<std::integral_constant<decay<decltype(MOD)>::type, MOD>>;
}
using namespace n_mint;

template<typename T>
vector<T> gauss(vector<vector<T>> a) {
  constexpr typename conditional<is_floating_point<T>::value, double, int>::type _EPS = is_floating_point<T>::value ? 1e-9 : 0;
  const T EPS = _EPS;
  int n = a.size();
  int m = a[0].size() - 1;
  vector<int> wh(m, -1);
  for (int col = 0, row = 0; col < m && row < n; col++) {
    int id = row;
    for (int i = row + 1; i < n; i++) {
      if (abs(a[i][col]) > abs(a[id][col])) {
        id = i;
      }
    }
    if (!(abs(a[id][col]) > EPS)) {
      continue;
    }
    swap(a[row], a[id]);
    wh[col] = row;
    T x = T(1) / a[row][col];
    for (int j = 0; j <= m; j++) {
      a[row][j] *= x;
    }
    for (int i = 0; i < n; i++) {
      if (i == row) continue;
      T coef = a[i][col];
      for (int j = 0; j <= m; j++) {
        a[i][j] -= coef * a[row][j];
      }
    }
    row++;
  }
  for (int i = 0; i < n; i++) {
    bool fail = 1;
    for (int j = 0; j < m; j++) fail &= !(abs(a[i][j]) > EPS);
    fail &= abs(a[i][m]) > EPS;
    if (fail) return vector<T>();
  }
  vector<T> ans(m);
  for (int i = 0; i < m; i++) {
    if (wh[i] != -1) {
      ans[i] = a[wh[i]][m];
    }
  }
  return ans;
}
namespace linear_rec_coef {
  vector<mint> find_gauss(vector<mint> s) {
    int m = s.size() / 2;
    int n = s.size() - m;
    vector<vector<mint>> a(n, vector<mint>(m + 1));
    for (int i = 0; i < n; i++) {
      a[i][m] = s[m + i];
      for (int j = 0; j < m; j++) {
        a[i][j] = s[m + i - 1 - j];
      }
    }
    auto res = gauss(a);
    assert(res.size() > 0);
    return res;
  }
  vector<mint> find_berlekamp(vector<mint> a) {
    vector<mint> p({1}), r({1});
    mint dif = 1;
    for (int i = 0; i < (int)a.size(); i++) {
      mint u = 0;
      for (int j = 0; j < (int)p.size(); j++) {
        u += p[j] * a[i - j];
      }
      if (u == 0) {
        r.insert(r.begin(), 0);
      } else {
        auto op = p;
        p.resize(max(p.size(), r.size() + 1));
        mint idif = 1 / dif;
        for (int j = 0; j < (int)r.size(); j++) {
          p[j + 1] -= r[j] * idif * u;
        }
        dif = u;
        r = op;
      }
    }
    assert(p[0] == 1);
    p.erase(p.begin());
    for (mint &x : p) x *= -1;
    return p;
  }
}


namespace n_matrix {
  template<typename T>
  struct matrix {
    vector<vector<T>> a;
    matrix() {}
    matrix(int n, int m) : a(n, vector<T>(m, T(0))) {}
    matrix(vector<vector<T>> _a) : a(_a) {}
    matrix(const matrix &_a) : a(_a.a) {}
    vector<T> &operator[](int i) {
      assert(0 <= i && i < (int) a.size());
      return a[i];
    }
    const vector<T> &operator[](int i) const {
      assert(0 <= i && i < (int) a.size());
      return a[i];
    }
    matrix operator+(const matrix &b) const {
      assert(a.size() == b.a.size() && a[0].size() == b.a[0].size());
      matrix c = *this;
      for (int i = 0; i < (int) a.size(); i++) {
        for (int j = 0; j < (int) a[0].size(); j++) {
          c[i][j] += b[i][j];
        }
      }
      return c;
    }
    matrix operator-(const matrix &b) const {
      assert(a.size() == b.a.size() && a[0].size() == b.a[0].size());
      matrix c = *this;
      for (int i = 0; i < (int) a.size(); i++) {
        for (int j = 0; j < (int) a[0].size(); j++) {
          c[i][j] -= b[i][j];
        }
      }
      return c;
    }
    matrix operator*(const matrix &b) const {
      assert(a[0].size() == b.a.size());
      matrix c(a.size(), b.a[0].size());
      for (int i = 0; i < (int) a.size(); i++) {
        for (int j = 0; j < (int) b.a[0].size(); j++) {
          T x = 0;
          for (int k = 0; k < (int) a[0].size(); k++) {
            x += a[i][k] * b[k][j];
          }
          c[i][j] = x;
        }
      }
      return c;
    }
    matrix operator*(T d) const {
      auto b = *this;
      for (auto &v : b.a) {
        for (auto &x : v) {
          x *= d;
        }
      }
      return b;
    }
    bool operator==(const matrix &b) const {
      return a == b.a;
    }
    void print() {
      for (auto v : a) {
        for (auto x : v) cout << x << " ";
        cout << endl;
      }
    }
  };
  template<>
  matrix<mint> matrix<mint>::operator*(const matrix<mint> &b) const {
    assert(a[0].size() == b.a.size());
    matrix c(a.size(), b.a[0].size());
    const long long MODMOD = 1LL * MOD * MOD;
    for (int i = 0; i < (int) a.size(); i++) {
      for (int j = 0; j < (int) b.a[0].size(); j++) {
        long long x = 0;
        for (int k = 0; k < (int) a[0].size(); k++) {
          x += (long long) a[i][k]() * b[k][j]();
          if (x >= MODMOD) x -= MODMOD;
        }
        c[i][j] = x % MOD;
      }
    }
    return c;
  }
  template<typename T>
  matrix<T> id_matrix(int n) {
    matrix<T> res(n, n);
    for (int i = 0; i < n; i++) {
      res[i][i] = 1;
    }
    return res;
  }
  template<typename T>
  matrix<T> bin(matrix<T> a, long long n) {
    assert(n >= 0);
    matrix<T> res = id_matrix<T>(a.a.size());
    while (n) {
      if (n & 1) res = res * a;
      a = a * a;
      n >>= 1;
    }
    return res;
  }
}
using namespace n_matrix;



namespace n_ffti {
  struct ffti {
    static std::vector<mint> root;
    static std::vector<int> rev;
    static int N;
    static void prepRoots() {
      static int lastMod = 0;
      if (mint::mod() == lastMod && (int) root.size() >= N) return;
      lastMod = mint::mod();
      int cN = max(N, 1 << 17);
      rev.resize(cN);
      root.resize(cN);
      for (int i = 1; i < cN; i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) * (cN / 2));
      mint croot = 2;
      while (!(bin(croot, cN) == mint(1) && bin(croot, cN / 2) != mint(1))) croot++;
      mint cur = 1;
      for (int i = cN >> 1; i < cN; i++) {
        root[i] = cur;
        cur *= croot;
      }
      for (int i = (cN >> 1) - 1; i >= 1; i--) {
        root[i] = root[i * 2];
      }
    }
    static void prepAB(std::vector<mint> &A, std::vector<mint> &B) {
      N = 1;
      while (N < (int) (A.size() + B.size())) N <<= 1;
      while ((int) A.size() < N) A.push_back(0);
      while ((int) B.size() < N) B.push_back(0);
      prepRoots();
    }
    static void fft(std::vector<mint> &f) {
      for (int i = 0; i < N; i++) {
        int j = rev[i] >> __builtin_ctz(root.size() / N);
        if (i < j) std::swap(f[i], f[j]);
      }
      for (int k = 1; k < N; k <<= 1) {
        for (int i = 0; i < N; i += 2 * k) {
          for (int j = 0; j < k; j++) {
            mint z = f[i + k + j] * root[k + j];
            f[i + j + k] = f[i + j] - z;
            f[i + j] = f[i + j] + z;
          }
        }
      }
    }
    static std::vector<mint> mul(std::vector<mint> a, std::vector<mint> b) {
      int rsz = a.size() + b.size() - 1;
      bool eq = a == b;
      prepAB(a, b);
      fft(a);
      if (eq) {
        b = a;
      } else {
        fft(b);
      }
      mint oN = mint(N).inv();
      for (int i = 0; i < N; i++) {
        a[i] = a[i] * b[i] * oN;
      }
      reverse(a.begin() + 1, a.begin() + N);
      fft(a);
      a.resize(rsz);
      return a;
    }
  };
  std::vector<mint> ffti::root;
  std::vector<int> ffti::rev;
  int ffti::N;
}
using namespace n_ffti;

namespace n_fftd {
  struct num {
    double x, y;
    num() {}
    num(double xx, double yy) : x(xx), y(yy) {}
    num(double alp) : x(cos(alp)), y(sin(alp)) {}
  };
  inline num operator+(const num &a, const num &b) { return num(a.x + b.x, a.y + b.y); }
  inline num operator-(const num &a, const num &b) { return num(a.x - b.x, a.y - b.y); }
  inline num operator*(const num &a, const num &b) { return num(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x); }
  inline num conj(num a) { return num(a.x, -a.y); }
  struct fftd {
  private:
    static constexpr double PI = M_PI;
    static std::vector<num> root;
    static std::vector<int> rev;
    static std::vector<num> a, b;
    static int N;
    static void prepRoots() {
      if ((int) root.size() >= N) return;
      int old = root.size();
      root.resize(N);
      if (old == 0) {
        if (root.size() < 2) root.resize(2);
        root[1] = num(1, 0);
      }
      for (int k = 1; (1 << k) < N; k++) {
        if ((1 << k) < old) continue;
        num x(2 * PI / (1LL << (k + 1)));
        for (int i = (1LL << (k - 1)); i < (1LL << (k)); i++) {
          root[2 * i] = root[i];
          root[2 * i + 1] = root[i] * x;
        }
      }
      rev.resize(N);
      for (int i = 1; i < N; i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) * (N / 2));
    }
    template<typename T>
    static void prepAB(std::vector<T> &A, std::vector<T> &B) {
      N = 1;
      while (N < (int) (A.size() + B.size())) N <<= 1;
      while ((int) A.size() < N) A.push_back(0);
      while ((int) B.size() < N) B.push_back(0);
      prepRoots();
    }
    static void fft(std::vector<num> &f) {
      for (int i = 0; i < N; i++) {
        int j = rev[i] >> __builtin_ctz(root.size() / N);
        if (i < j) std::swap(f[i], f[j]);
      }
      for (int k = 1; k < N; k <<= 1) {
        for (int i = 0; i < N; i += 2 * k) {
          for (int j = 0; j < k; j++) {
            num z = f[i + j + k] * root[j + k];
            f[i + j + k] = f[i + j] - z;
            f[i + j] = f[i + j] + z;
          }
        }
      }
    }
    template<typename T>
    static std::vector<T> mulSingle(std::vector<T> A, std::vector<T> B) {
      int rsz = A.size() + B.size() - 1;
      prepAB(A, B);
      if ((int) a.size() < N) a.resize(N);
      for (int i = 0; i < N; i++) a[i] = num((double) A[i], (double) B[i]);
      fft(a);
      for (int i = 0; i <= N / 2; i++) {
        int j = (N - i) & (N - 1);
        num x = (a[j] * a[j] - conj(a[i] * a[i])) * num(0, -0.25 / N);
        num y = (a[i] * a[i] - conj(a[j] * a[j])) * num(0, -0.25 / N);
        a[i] = x;
        if (j != i) a[j] = y;
      }
      fft(a);
      std::vector<T> C(N);
      for (int i = 0; i < N; i++) {
        if (is_floating_point<T>::value) {
          C[i] = a[i].x;
        } else {
          C[i] = (T)(long long)round(a[i].x);
        }
      }
      C.resize(rsz);
      return C;
    }
    struct PossibleTypes {
      struct Modular {};
      struct NonModular {};
    };
    template<typename T, typename Enabled = void>
    struct GetType {
      using Type = PossibleTypes::NonModular;
    };
    template<typename T>
    struct GetType<T, typename enable_if<is_modular<T>::value>::type> {
      using Type = PossibleTypes::Modular;
    };
    template<typename T>
    static std::vector<T> mul(const std::vector<T> &A, const std::vector<T> &B, PossibleTypes::Modular) {
      return mulMod(A, B, T::mod());
    }
    template<typename T>
    static std::vector<T> mul(const std::vector<T> &A, const std::vector<T> &B, PossibleTypes::NonModular) {
      return mulSingle(A, B);
    }
  public:
    template<typename T>
    static std::vector<T> mulMod(std::vector<T> A, std::vector<T> B, int CUR_MOD) {
      int rsz = A.size() + B.size() - 1;
      prepAB(A, B);
      if ((int) a.size() < N) a.resize(N);
      for (int i = 0; i < N; i++) {
        int x = A[i];
        a[i] = num(x & ((1 << 15) - 1), x >> 15);
      }
      fft(a);
      if (A == B) {
        b = a;
      } else {
        if ((int) b.size() < N) b.resize(N);
        for (int i = 0; i < N; i++) {
          int x = B[i];
          b[i] = num(x & ((1 << 15) - 1), x >> 15);
        }
        fft(b);
      }
      for (int i = 0; i <= N / 2; i++) {
        int j = (N - i) & (N - 1);
        num a1 = (a[i] + conj(a[j])) * num(0.5, 0);
        num a2 = (a[i] - conj(a[j])) * num(0, -0.5);
        num b1 = (b[i] + conj(b[j])) * num(0.5 / N, 0);
        num b2 = (b[i] - conj(b[j])) * num(0, -0.5 / N);
        if (i != j) {
          num aa1 = (a[j] + conj(a[i])) * num(0.5, 0);
          num aa2 = (a[j] - conj(a[i])) * num(0, -0.5);
          num bb1 = (b[j] + conj(b[i])) * num(0.5 / N, 0);
          num bb2 = (b[j] - conj(b[i])) * num(0, -0.5 / N);
          a[i] = aa1 * bb1 + aa2 * bb2 * num(0, 1);
          b[i] = aa1 * bb2 + aa2 * bb1;
        }
        a[j] = a1 * b1 + a2 * b2 * num(0, 1);
        b[j] = a1 * b2 + a2 * b1;
      }
      fft(a);
      fft(b);
      std::vector<T> C(N);
      for (int i = 0; i < N; i++) {
        long long aa = a[i].x + 0.5;
        long long bb = b[i].x + 0.5;
        long long cc = a[i].y + 0.5;
        C[i] = (aa + bb % CUR_MOD * (1LL << 15) + cc % CUR_MOD * (1LL << 30)) % CUR_MOD;
      }
      C.resize(rsz);
      return C;
    }
    template<typename T>
    static std::vector<T> mul(const std::vector<T> &A, const std::vector<T> &B) {
      using CurType = typename GetType<T>::Type;
      return mul(A, B, CurType());
    }
  };
  std::vector<num> fftd::root;
  std::vector<int> fftd::rev;
  std::vector<num> fftd::a, fftd::b;
  int fftd::N;
}
using namespace n_fftd;
template <typename T, typename FFT = fftd>
struct fft_online {
  vector<T> a, b, c;
  fft_online(vector<T> _a) : a(_a) {}
  T add(int k, T x) {
    if ((int)c.size() < 3 * (k + 1)) {
      a.resize(max((int)a.size(), 4 * (k + 1)));
      b.resize(max((int)b.size(), 4 * (k + 1)));
      c.resize(max((int)c.size(), 4 * (k + 1)));
    }
    b[k] = x;
    c[k] += a[0] * b[k];
    int z = 1;
    while ((k & (z - 1)) == (z - 1)) {
      vector<T> ca(z), cb(z);
      for (int i = 0; i < z; i++) ca[i] = a[z + i];
      for (int i = 0; i < z; i++) cb[i] = b[k - z + 1 + i];
      auto cc = FFT::mul(ca, cb);
      for (int i = 0; i < 2 * z - 1; i++) c[k + 1 + i] += cc[i];
      z <<= 1;
    }
    return c[k];
  }
};
template <typename T, typename FFT = fftd>
struct poly : vector<T> {
  using vector<T>::vector;
  poly(const vector<T> &a) : vector<T>(a) {}
  explicit poly(int x) : vector<T>(x) {}
  friend ostream& operator<< (ostream& out, const poly& p) {
    out << p.to_string();
    return out;
  }
  poly& operator+= (const poly &p) {
    this->resize(max(this->size(), p.size()));
    for (int i = 0; i < (int)p.size(); i++) {
      (*this)[i] += p[i];
    }
    return *this;
  }
  friend poly operator+ (poly a, const poly &b) {
    return a += b;
  }
  poly& operator-= (const poly &p) {
    this->resize(max(this->size(), p.size()));
    for (int i = 0; i < (int)p.size(); i++) {
      (*this)[i] -= p[i];
    }
    return *this;
  }
  friend poly operator- (poly a, const poly &b) {
    return a -= b;
  }
  poly& operator*= (T d) {
    for (int i = 0; i < (int)this->size(); i++) {
      (*this)[i] *= d;
    }
    return *this;
  }
  friend poly operator* (poly a, T d) {
    return a *= d;
  }
  poly& operator/= (T d) {
    auto od = T(1) / d;
    for (int i = 0; i < (int)this->size(); i++) {
      (*this)[i] *= od;
    }
    return *this;
  }
  friend poly operator/ (poly a, T d) {
    return a /= d;
  }
  static poly slow_mul(const poly &a, const poly &b) {
    poly res(a.size() + b.size() - 1);
    for (int i = 0; i < (int)a.size(); i++) {
      for (int j = 0; j < (int)b.size(); j++) {
        res[i + j] += a[i] * b[j];
      }
    }
    return res;
  }
  poly& operator*= (const poly &p) {
    if (min(this->size(), p.size()) <= 100) {
      *this = slow_mul(*this, p);
    } else {
      *this = poly(FFT::mul(*this, p));
    }
    return *this;
  }
  friend poly operator* (poly a, const poly &b) {
    return a *= b;
  }
  poly inv() const {
    assert((*this)[0] != 0);
    poly r({T(1) / (*this)[0]});
    for (int n = 1; n < (int)this->size(); n <<= 1) {
      poly ca = cut(2 * n);
      r = (r * 2 - r * r * ca).cut(2 * n);
    }
    r.resize(this->size());
    return r;
  }
  poly sqrt() const {
    assert((*this)[0] == 1);
    poly r(1, 1);
    for (int n = 1; n < (int)this->size(); n <<= 1) {
      poly ca = cut(2 * n);
      r = ((r + ca * r.cut(2 * n).inv()) / 2).cut(2 * n);
    }
    r.resize(this->size());
    return r;
  }
  void norm() {
    while (this->size() > 1 && this->back() == 0) {
      this->pop_back();
    }
  }
  poly rev() const {
    return poly(this->rbegin(), this->rend());
  }
  poly cut(int n) const {
    poly res = *this;
    res.resize(n);
    return res;
  }
  pair<poly, poly> div(poly b) const {
    auto a = *this;
    a.norm(); b.norm();
    if (a.size() < b.size()) return make_pair(poly({0}), a);
    T x = b.back();
    assert(x != 0);
    b /= x;
    auto rb = b.rev().cut(a.size() - b.size() + 1);
    auto q = (rb.inv() * a.rev()).cut(a.size() - b.size() + 1).rev();
    poly r = a - b * q;
    q /= x;
    r.norm();
    return {q, r};
  }
  friend poly operator/ (poly a, const poly &b) {
    return a /= b;
  }
  poly& operator/= (const poly &p) {
    return *this = div(p).first;
  }
  friend poly operator% (poly a, const poly &b) {
    return a %= b;
  }
  poly& operator%= (const poly &p) {
    return *this = div(p).second;
  }
  poly derivative() const {
    poly res(max(1, (int)this->size() - 1), 0);
    for (int i = 1; i < (int)this->size(); i++) res[i - 1] = (*this)[i] * i;
    return res;
  }
  poly integrate() const {
    poly res(this->size() + 1);
    for (int i = 1; i < (int)res->size(); i++) {
      res[i] = (*this)[i - 1] / i;
    }
    return res;
  }
  poly exp() const {
    assert((*this)[0] == 0);
    fft_online<T, FFT> t(derivative());
    vector<T> g(this->size());
    g[0] = T(1);
    for (int i = 1; i < (int)g.size(); i++) {
      int x = t.add(i - 1, g[i - 1]);
      g[i] = x / T(i);
    }
    return g;
  }
  T eval(T x) const {
    T res = 0;
    for (int i = (int)this->size() - 1; i >= 0; i--) {
      res = res * x + (*this)[i];
    }
    return res;
  }
  vector<T> eval(const vector<T> &x) {
    int m = x.size();
    vector<poly> t(4 * m);
    function<poly(int, int, int)> prod = [&](int v, int l, int r) {
      poly res;
      if (l == r) {
        res = poly({-x[l], 1});
      } else {
        int m = (l + r) >> 1;
        res = prod(v * 2, l, m) * prod(v * 2 + 1, m + 1, r);
      }
      return t[v] = res;
    };
    prod(1, 0, m - 1);
    vector<T> ans(m);
    function<void(poly, int, int, int)> eval = [&](poly cur, int v, int l, int r) {
      cur %= t[v];
      if (r - l <= 500) {
        for (int i = l; i <= r; i++) {
          ans[i] = cur.eval(x[i]);
        }
      } else {
        int m = (l + r) >> 1;
        eval(cur, v * 2, l, m);
        eval(cur, v * 2 + 1, m + 1, r);
      }
    };
    eval(*this, 1, 0, m - 1);
    return ans;
  }
  string to_string() const {
    string res;
    for (int i = 0; i < (int)this->size(); i++) {
      res += ::to_string((*this)[i]);
      if (i + 1 < (int)this->size()) res += " ";
    }
    return res;
  }
};
namespace linear_rec_elem {
  typedef long long ll;
  mint find_linear(ll n, vector<mint> s, const vector<mint> &x) {
    int k = x.size();
    if (n < (int)s.size()) return s[n];
    for (ll i = (int)s.size(); i <= n; i++) {
      mint cur = 0;
      for (int j = 0; j < k; j++) {
        cur += x[j] * s[(int)s.size() - 1 - j];
      }
      s.push_back(cur);
      s.erase(s.begin());
    }
    return s.back();
  }
  mint find_matrix(ll n, const vector<mint> &s, const vector<mint> &x) {
    assert(n >= 0);
    int k = x.size();
    if (n < k) return s[n];
    matrix<mint> a(k, k);
    for (int i = 0; i < k - 1; i++) {
      a[i + 1][i] = 1;
    }
    for (int i = 0; i < k; i++) {
      a[i][k - 1] = x[k - 1 - i];
    }
    a = bin(a, n);
    mint res = 0;
    for (int i = 0; i < k; i++) res += s[i] * a[i][0];
    return res;
  }
  poly<mint> bin(poly<mint> a, ll n, const vector<mint> &MOD) {
    assert(n > 0);
    poly<mint> res = a;
    n--;
    while (n) {
      if (n & 1) res = res * a % MOD;
      a = a * a % MOD;
      n >>= 1;
    }
    return res;
  }
  mint find_poly(ll n, vector<mint> s, const vector<mint> &x) {
    assert(n >= 0);
    int k = x.size();
    if (n < k) return s[n];
    poly<mint> p = poly<mint>(x).rev() * (mint)(MOD - 1);
    p.push_back(1);
    auto t = bin(poly<mint>({0, 1}) % p, n, p).cut(k);
    mint res = 0;
    for (int i = 0; i < k; i++) {
      res += t[i] * s[i];
    }
    return res;
  }
  mint find(ll n, const vector<mint> &s, const vector<mint> &x) {
    ll k = s.size();
    assert(n >= 0 && k > 0);
    assert((int)s.size() >= k);
    if (n <= k * k) {
      return find_linear(n, s, x);
//    } else if (k <= 16) {
//      return find_matrix(n, s, x);
    } else {
      return find_poly(n, s, x);
    }
  }
}
namespace linear_rec {
  mint find(const vector<mint> &a, long long n) {
    vector<mint> coefs = linear_rec_coef::find_berlekamp(a);
    mint res = linear_rec_elem::find(n, a, coefs);
    return res;
  }
}

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

typedef vector<ll> vll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<bool> vb;
typedef vector<vb> vvb;
typedef pair<int, int> pii;
typedef pair<ll,ll> pll;

//const int inf = 1e9;
const double eps = 1e-9;
//const double INF = inf;
const double EPS = eps;

const long long checkItCnt = 2000000;
const long long maxMod = (ll)2e9;
const long long maxT = 1000;

void gcdex(ll a,ll b,ll &x,ll &y) {
  if (!a){
    x = 0, y = 1;
    return;
  }
  ll x1, y1;
  gcdex(b % a, a, x1, y1);
  x = y1 - (b / a) * x1;
  y = x1;
}

// BEGIN ALGO
//return pair(nmod,nr)
//nr%mod1=r1, nr%mod2=r2
//nmod=mod1*mod2/gcd(mod1,mod2)
//if input incosistent return mp(-1,-1)

pair<ll, ll> kto (ll mod1, ll r1, ll mod2, ll r2) {
  ll d = __gcd(mod1, mod2);
  if (r1 % d != r2 % d)
    return {-1, -1};
  ll rd = r1 % d;
  mod1 /= d, mod2 /= d, r1 /= d, r2 /= d;

  if (mod1 < mod2)
    swap(mod1, mod2), swap(r1, r2);

  ll k = (r2 - r1) % mod2;
  if (k < 0)
    k += mod2;

  ll x, y;
  gcdex(mod1, mod2, x, y);
  x %= mod2;
  if (x < 0)
    x += mod2;
  k *= x, k %= mod2;
  return {mod1 * mod2 * d, (k * mod1 + r1) * d + rd};
}
// END ALGO

int calc_sum(ll rem, ll mod, ll n, int k) {
  if (n < rem) return 0;
//  eprintf("%lld %lld %lld %d\n", rem, mod, n, k);
  vector<mint> prefix;
  int cur = 0;
  for (int i = 0; i < 3 * k; i++) {
    int pos = (rem + mod * i) % MOD;
    int val = 1;
    for (int j = 0; j < k; j++) {
      val = mul(val, pos + j);
    }
    add(cur, val);
    prefix.push_back(cur);
  }
  int res = linear_rec::find(prefix, (n - rem) / mod)();

#ifdef LOCAL
  if (0) {
    int res2 = 0;

    for (ll pos = rem; pos <= n; pos += mod) {
      int val = 1;
      for (int j = 0; j < k; j++) {
        val = mul(val, pos + j);
      }
      add(res2, val);
    }
    assert(res2 == res);
  }
#endif
  return res;
}

int main() {
#ifdef LOCAL
  freopen("l.in", "r", stdin);
  freopen("l.out", "w", stdout);
#endif

  const int divsp[] = {16, 27, 25, 7, 11, 13, 17, 19, 23, 29};
  const int divs[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
  const int divd[] = {4, 3, 2, 1, 1, 1, 1, 1, 1, 1};

  ll n;
  int k;
  while (scanf("%lld%d", &n, &k) == 2) {
    k++;
    int D = sizeof(divs) / sizeof(int);
    vector<vector<pair<int, int>>> d(D);
    for (int i = 0; i < D; i++) {
      for (int j = 0; j < divsp[i]; j++) {
        vector<int> cnts;
        for (int t = 0; t < k; t++) {
          int x = (j + t) % divsp[i];
          if (x == 0) {
            cnts.push_back(divd[i]);
          } else {
            cnts.push_back(0);
            while (x % divs[i] == 0) {
              cnts.back()++;
              x /= divs[i];
            }
          }
        }
        sort(cnts.begin(), cnts.end());
        cnts.pop_back();
        d[i].emplace_back( accumulate(cnts.begin(), cnts.end(), 0), j);
      }
    }

    int coef = 1;
    ll prod = 1;
    vector<int> bestp(D);

    for (int div_id = 0; div_id < D; div_id++) {
      prod *= divsp[div_id];
      auto &v = d[div_id];
      sort(v.begin(), v.end());
      int best = 0;
      int best_val = 0;
      for (int i = 0; i < (int)v.size(); ) {
        int j = i;
        while (j < (int)v.size() && v[j].first == v[i].first) j++;
        if (j - i > best_val) {
          best = v[i].first;
          best_val = j - i;
        }
        i = j;
      }
      for (int i = 0; i < best; i++) {
        coef = mul(coef, minv(divs[div_id]));
      }
      bestp[div_id] = best;
      v.erase(remove_if(v.begin(), v.end(), [&](auto x) { return x.first == best; }), v.end());
    }

    unsigned long long ops = 1;
    for (auto x : d) {
      ops *= x.size() + 1;
    }
    eprintf("will call %llu calc_sum\n", ops);

    int ans = 0;

    std::function<void(int, ll, ll, int)> calc = [&](int did, ll cur_rem, ll cur_mod, int cur_coef) {
      if (did == D) {
        add(ans, mul(cur_coef, calc_sum(cur_rem, cur_mod, n, k)));
        return;
      }
      int best_p = mpow(minv(divs[did]), bestp[did]);
      calc(did + 1, cur_rem, cur_mod, mul(cur_coef, best_p));
      for (auto x : d[did]) {
        auto nxt = kto(cur_mod, cur_rem, divsp[did], x.second);
        assert(nxt.first != -1);
        int coef = mpow(minv(divs[did]), x.first);
        sub(coef, best_p);
        calc(did + 1, nxt.second, nxt.first, mul(cur_coef, coef));
      }
    };
    calc(0, 0, 1, 1);

    printf("%d\n", ans);
  }


  return 0;
}
