/**
*    author:  tourist
*    created: 19.09.2021 13:00:34
**/

#include <bits/stdc++.h>

using namespace std;

template <typename A, typename B>
string to_string(pair<A, B> p);

template <typename A, typename B, typename C>
string to_string(tuple<A, B, C> p);

template <typename A, typename B, typename C, typename D>
string to_string(tuple<A, B, C, D> p);

string to_string(const string& s) {
 return '"' + s + '"';
}

string to_string(const char* s) {
 return to_string((string) s);
}

string to_string(bool b) {
 return (b ? "true" : "false");
}

string to_string(vector<bool> v) {
 bool first = true;
 string res = "{";
 for (int i = 0; i < static_cast<int>(v.size()); i++) {
   if (!first) {
     res += ", ";
   }
   first = false;
   res += to_string(v[i]);
 }
 res += "}";
 return res;
}

template <size_t N>
string to_string(bitset<N> v) {
 string res = "";
 for (size_t i = 0; i < N; i++) {
   res += static_cast<char>('0' + v[i]);
 }
 return res;
}

template <typename A>
string to_string(A v) {
 bool first = true;
 string res = "{";
 for (const auto &x : v) {
   if (!first) {
     res += ", ";
   }
   first = false;
   res += to_string(x);
 }
 res += "}";
 return res;
}

template <typename A, typename B>
string to_string(pair<A, B> p) {
 return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
}

template <typename A, typename B, typename C>
string to_string(tuple<A, B, C> p) {
 return "(" + to_string(get<0>(p)) + ", " + to_string(get<1>(p)) + ", " + to_string(get<2>(p)) + ")";
}

template <typename A, typename B, typename C, typename D>
string to_string(tuple<A, B, C, D> p) {
 return "(" + to_string(get<0>(p)) + ", " + to_string(get<1>(p)) + ", " + to_string(get<2>(p)) + ", " + to_string(get<3>(p)) + ")";
}

void debug_out() { cerr << endl; }

template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T) {
 cerr << " " << to_string(H);
 debug_out(T...);
}

#ifdef LOCAL
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#else
#define debug(...) 42
#endif

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
 typename enable_if<is_same<typename Modular<U>::Type, long long>::value, Modular>::type& operator*=(const Modular& rhs) {
   long long q = static_cast<long long>(static_cast<long double>(value) * rhs.value / mod());
   value = normalize(value * rhs.value - q * mod());
   return *this;
 }
 template <typename U = T>
 typename enable_if<!is_integral<typename Modular<U>::Type>::value, Modular>::type& operator*=(const Modular& rhs) {
   value = normalize(value * rhs.value);
   return *this;
 }

 Modular& operator/=(const Modular& other) { return *this *= Modular(inverse(other.value, mod())); }

 friend const Type& abs(const Modular& x) { return x.value; }

 template <typename U>
 friend bool operator==(const Modular<U>& lhs, const Modular<U>& rhs);

 template <typename U>
 friend bool operator<(const Modular<U>& lhs, const Modular<U>& rhs);

 template <typename V, typename U>
 friend V& operator>>(V& stream, Modular<U>& number);

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
bool IsZero(const Modular<T>& number) {
 return number() == 0;
}

template <typename T>
string to_string(const Modular<T>& number) {
 return to_string(number());
}

// U == std::ostream? but done this way because of fastoutput
template <typename U, typename T>
U& operator<<(U& stream, const Modular<T>& number) {
 return stream << number();
}

// U == std::istream? but done this way because of fastinput
template <typename U, typename T>
U& operator>>(U& stream, Modular<T>& number) {
 typename common_type<typename Modular<T>::Type, long long>::type x;
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

constexpr int md = 998244353;
using Mint = Modular<std::integral_constant<decay<decltype(md)>::type, md>>;

/*vector<Mint> fact(1, 1);
vector<Mint> inv_fact(1, 1);

Mint C(int n, int k) {
 if (k < 0 || k > n) {
   return 0;
 }
 while ((int) fact.size() < n + 1) {
   fact.push_back(fact.back() * (int) fact.size());
   inv_fact.push_back(1 / fact.back());
 }
 return fact[n] * inv_fact[k] * inv_fact[n - k];
}*/

const double eps = 1e-9;

bool IsZero(double v) {
 return abs(v) < 1e-9;
}

enum GAUSS_MODE {
 DEGREE, ABS
};

template <typename T>
void GaussianElimination(vector<vector<T>>& a, int limit, GAUSS_MODE mode = DEGREE) {
 if (a.empty() || a[0].empty()) {
   return;
 }
 int h = static_cast<int>(a.size());
 int w = static_cast<int>(a[0].size());
 for (int i = 0; i < h; i++) {
   assert(w == static_cast<int>(a[i].size()));
 }
 assert(limit <= w);
 vector<int> deg(h);
 for (int i = 0; i < h; i++) {
   for (int j = 0; j < w; j++) {
     deg[i] += !IsZero(a[i][j]);
   }
 }
 int r = 0;
 for (int c = 0; c < limit; c++) {
   int id = -1;
   for (int i = r; i < h; i++) {
     if (!IsZero(a[i][c]) && (id == -1 || (mode == DEGREE && deg[i] < deg[id]) || (mode == ABS && abs(a[id][c]) < abs(a[i][c])))) {
       id = i;
     }
   }
   if (id == -1) {
     continue;
   }
   if (id > r) {
     swap(a[r], a[id]);
     swap(deg[r], deg[id]);
     for (int j = c; j < w; j++) {
       a[id][j] = -a[id][j];
     }
   }
   vector<int> nonzero;
   for (int j = c; j < w; j++) {
     if (!IsZero(a[r][j])) {
       nonzero.push_back(j);
     }
   }
   T inv_a = 1 / a[r][c];
   for (int i = r + 1; i < h; i++) {
     if (IsZero(a[i][c])) {
       continue;
     }
     T coeff = -a[i][c] * inv_a;
     for (int j : nonzero) {
       if (!IsZero(a[i][j])) deg[i]--;
       a[i][j] += coeff * a[r][j];
       if (!IsZero(a[i][j])) deg[i]++;
     }
   }
   ++r;
 }
 for (r = h - 1; r >= 0; r--) {
   for (int c = 0; c < limit; c++) {
     if (!IsZero(a[r][c])) {
       T inv_a = 1 / a[r][c];
       for (int i = r - 1; i >= 0; i--) {
         if (IsZero(a[i][c])) {
           continue;
         }
         T coeff = -a[i][c] * inv_a;
         for (int j = c; j < w; j++) {
           a[i][j] += coeff * a[r][j];
         }
       }
       break;
     }
   }
 }
}

template <typename T>
T Determinant(vector<vector<T>>/*&*/ a) {
 if (a.empty()) {
   return T{1};
 }
 assert(a.size() == a[0].size());
 GaussianElimination(a, static_cast<int>(a[0].size()));
 T d{1};
 for (int i = 0; i < a.h; i++) {
   d *= a[i][i];
 }
 return d;
}

template <typename T>
int Rank(vector<vector<T>>/*&*/ a) {
 if (a.empty()) {
   return 0;
 }
 GaussianElimination(a, static_cast<int>(a[0].size()));
 int rank = 0;
 for (int i = 0; i < static_cast<int>(a.size()); i++) {
   for (int j = 0; j < static_cast<int>(a[i].size()); j++) {
     if (!IsZero(a[i][j])) {
       ++rank;
       break;
     }
   }
 }
 return rank;
}

template <typename T>
vector<T> SolveLinearSystem(vector<vector<T>>& a, const vector<T>& b, int w) {
 int h = static_cast<int>(a.size());
 assert(h == static_cast<int>(b.size()));
 if (h > 0) {
   assert(w == static_cast<int>(a[0].size()));
 }
 for (int i = 0; i < h; i++) {
   a[i].push_back(b[i]);
 }
 GaussianElimination(a, w);
 vector<T> x(w, 0);
 for (int i = 0; i < h; i++) {
   for (int j = 0; j < w; j++) {
     if (!IsZero(a[i][j])) {
       x[j] = a[i][w] / a[i][j];
       break;
     }
   }
 }
 return x;
}

template <typename T>
vector<vector<T>> Inverse(vector<vector<T>>/*&*/ a) {
 if (a.empty()) {
   return a;
 }
 int h = static_cast<int>(a.size());
 for (int i = 0; i < h; i++) {
   assert(h == static_cast<int>(a[i].size()));
 }
 for (int i = 0; i < h; i++) {
   a[i].resize(2 * h);
   a[i][i + h] = 1;
 }
 GaussianElimination(a, h);
 for (int i = 0; i < h; i++) {
   if (IsZero(a[i][i])) {
     return {{}};
   }
 }
 vector<vector<T>> b(h);
 for (int i = 0; i < h; i++) {
   b[i] = vector<T>(a[i].begin() + h, a[i].end());
   T coeff = 1 / a[i][i];
   for (int j = 0; j < h; j++) {
     b[i][j] *= coeff;
   }
 }
 return b;
}

int main() {
 ios::sync_with_stdio(false);
 cin.tie(0);
 mt19937 rng(58);
 vector<vector<Mint>> mat;
 vector<Mint> R;
 for (int it = 0; it < 1000; it++) {
   int n = rng() % 10 + 4;
   vector<vector<int>> g(n, vector<int>(n));
   vector<int> deg(n);
   for (int i = 0; i < n; i++) {
     for (int j = i + 1; j < n; j++) {
       g[i][j] = rng() % 2;
       g[j][i] = g[i][j];
       deg[i] += g[i][j];
       deg[j] += g[i][j];
     }
   }
   int expected = 0;
   for (int a = 0; a < n; a++) {
     for (int b = a + 1; b < n; b++) {
       for (int c = b + 1; c < n; c++) {
         for (int d = c + 1; d < n; d++) {
           int k = g[a][b] + g[a][c] + g[b][c] + g[a][d] + g[b][d] + g[c][d];
           if (k == 5 || k == 1) {
             expected -= 1;
           }
           if (k == 3) {
             if (g[a][b] + g[a][c] + g[b][c] == 3) continue;
             if (g[a][d] + g[a][c] + g[d][c] == 3) continue;
             if (g[a][b] + g[a][d] + g[b][d] == 3) continue;
             if (g[d][b] + g[d][c] + g[b][c] == 3) continue;
             expected += 1;
           }
         }
       }
     }
   }
   mat.emplace_back();
   mat.back().push_back(1);
   mat.back().push_back(n);
   mat.back().push_back(n * n);
   mat.back().push_back(n * n * n);
   mat.back().push_back(n * n * n * n);
   for (int pw = 1; pw <= 4; pw++) {
     Mint sum = 0;
     for (int i = 0; i < n; i++) {
       sum += power(Mint(deg[i]), pw);
     }
     mat.back().push_back(sum);
     mat.back().push_back(sum * n);
     mat.back().push_back(sum * n * n);
   }
   for (int pw = 1; pw <= 4; pw++) {
     Mint sum = 0;
     for (int i = 0; i < n; i++) {
       for (int j = i + 1; j < n; j++) {
         sum += power(Mint(deg[i] * deg[j]), pw);
       }
     }
     mat.back().push_back(sum);
     mat.back().push_back(sum * n);
   }
   for (int pw = 1; pw <= 4; pw++) {
     Mint sum = 0;
     for (int i = 0; i < n; i++) {
       for (int j = i + 1; j < n; j++) {
         sum += power(Mint(deg[i] * deg[j] * (deg[i] + deg[j])), pw);
       }
     }
     mat.back().push_back(sum);
     mat.back().push_back(sum * n);
   }
   for (int pw = 1; pw <= 4; pw++) {
     Mint sum = 0;
     for (int i = 0; i < n; i++) {
       for (int j = i + 1; j < n; j++) {
         sum += power(Mint(deg[i] * deg[j] * (deg[i] * deg[i] + deg[j] * deg[j])), pw);
       }
     }
     mat.back().push_back(sum);
     mat.back().push_back(sum * n);
   }
   for (int pw = 1; pw <= 4; pw++) {
     Mint sum = 0;
     for (int i = 0; i < n; i++) {
       for (int j = i + 1; j < n; j++) {
         for (int k = j + 1; k < n; k++) {
           if (g[i][j] + g[i][k] + g[j][k] == 1) sum += 1;
         }
       }
     }
     sum = power(sum, pw);
     mat.back().push_back(sum);
   }
   for (int pw = 1; pw <= 4; pw++) {
     Mint sum = 0;
     for (int i = 0; i < n; i++) {
       for (int j = i + 1; j < n; j++) {
         for (int k = j + 1; k < n; k++) {
           if (g[i][j] + g[i][k] + g[j][k] == 1) sum += deg[i] * deg[j] * deg[k];
         }
       }
     }
     sum = power(sum, pw);
     mat.back().push_back(sum);
   }
   R.push_back(expected);
 }
 auto ret = SolveLinearSystem(mat, R, (int) mat[0].size());
 debug(ret);
 for (auto& row : mat) {
   debug(row);
 }
 //  debug(R);
 return 0;
}
