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
#define TIMESTAMPf(x, ...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, (clock() - __my_start_clock)*1.0/CLOCKS_PER_SEC)

#define db(x) cerr << #x << " = " << x << endl
#define db2(x, y) cerr << "(" << #x << ", " << #y << ") = (" << x << ", " << y << ")\n";
#define db3(x, y, z) cerr << "(" << #x << ", " << #y << ", " << #z << ") = (" << x << ", " << y << ", " << z << ")\n"
#define dbv(a) cerr << #a << " = "; for (auto xxxx: a) cerr << xxxx << " "; cerr << endl


using namespace std;

#ifdef LOCAL

static struct __timestamper {
  string what;

  __timestamper(const char *what) : what(what) {};

  __timestamper(const string &what) : what(what) {};

  ~__timestamper() {
    TIMESTAMPf("%s", what.data());
  }
} __TIMESTAMPER("end");

#else
struct __timestamper {};
#endif

typedef long long ll;
typedef long double ld;


constexpr int mul_table[][16] =
  {
    {0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
    {0, 1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15},
    {0, 2,  3,  1,  8,  10, 11, 9,  12, 14, 15, 13, 4,  6,  7,  5},
    {0, 3,  1,  2,  12, 15, 13, 14, 4,  7,  5,  6,  8,  11, 9,  10},
    {0, 4,  8,  12, 6,  2,  14, 10, 11, 15, 3,  7,  13, 9,  5,  1},
    {0, 5,  10, 15, 2,  7,  8,  13, 3,  6,  9,  12, 1,  4,  11, 14},
    {0, 6,  11, 13, 14, 8,  5,  3,  7,  1,  12, 10, 9,  15, 2,  4},
    {0, 7,  9,  14, 10, 13, 3,  4,  15, 8,  6,  1,  5,  2,  12, 11},
    {0, 8,  12, 4,  11, 3,  7,  15, 13, 5,  1,  9,  6,  14, 10, 2},
    {0, 9,  14, 7,  15, 6,  1,  8,  5,  12, 11, 2,  10, 3,  4,  13},
    {0, 10, 15, 5,  3,  9,  12, 6,  1,  11, 14, 4,  2,  8,  13, 7},
    {0, 11, 13, 6,  7,  12, 10, 1,  9,  2,  4,  15, 14, 5,  3,  8},
    {0, 12, 4,  8,  13, 1,  9,  5,  6,  10, 2,  14, 11, 7,  15, 3},
    {0, 13, 6,  11, 9,  4,  15, 2,  14, 3,  8,  5,  7,  10, 1,  12},
    {0, 14, 7,  9,  5,  11, 2,  12, 10, 4,  13, 3,  15, 1,  8,  6},
    {0, 15, 5,  10, 1,  14, 4,  11, 2,  13, 7,  8,  3,  12, 6,  9},
  };

constexpr unsigned long long inverse_table[] = {1, 3, 2, 15, 12, 9, 11, 10, 6, 8, 7, 5, 14, 13, 4,
                                                170, 160, 109, 107, 131, 139, 116, 115, 228, 234, 92, 89, 73, 77,
                                                220, 209, 85, 214, 80, 219, 199, 179, 203, 184, 66, 226, 70, 236,
                                                156, 247, 149, 248, 255, 182, 189, 240, 120, 164, 174, 127, 142, 100,
                                                98, 134, 193, 152, 145, 205, 119, 207, 40, 227, 112, 195, 42, 237,
                                                76, 28, 186, 97, 72, 29, 177, 103, 34, 218, 104, 253, 215, 32, 242,
                                                110, 93, 27, 151, 123, 26, 88, 124, 158, 187, 75, 58, 135, 57, 143,
                                                176, 79, 82, 252, 108, 19, 106, 18, 87, 243, 68, 194, 117, 23, 22,
                                                114, 206, 64, 52, 165, 150, 91, 94, 159, 175, 55, 238, 146, 138, 20,
                                                196, 222, 59, 99, 224, 155, 130, 21, 200, 211, 56, 101, 204, 62, 129,
                                                239, 249, 46, 122, 90, 61, 192, 225, 137, 44, 246, 95, 125, 17, 171,
                                                181, 212, 53, 121, 244, 232, 190, 217, 16, 161, 251, 230, 54, 126,
                                                102, 78, 198, 37, 213, 162, 49, 254, 39, 202, 74, 96, 241, 50, 168,
                                                216, 153, 60, 113, 69, 132, 223, 178, 36, 140, 210, 185, 38, 144, 63,
                                                118, 65, 221, 31, 201, 141, 163, 180, 33, 84, 191, 169, 81, 35, 30,
                                                208, 133, 197, 136, 154, 41, 67, 24, 235, 173, 250, 167, 245, 25,
                                                229, 43, 71, 128, 147, 51, 188, 86, 111, 166, 233, 157, 45, 47, 148,
                                                231, 172, 105, 83, 183, 48};

pair<unsigned long long, unsigned long long> fermat_power(int n) {
  unsigned long long n2 = 1ull << n;
  return {n2, 1ull << n2};
}

struct nimber {
  unsigned long long value;

  nimber(unsigned long long x = 0) : value(x) {}

  explicit operator bool() const { return value; }

  bool operator==(const nimber &other) const { return value == other.value; }

  int prec() const {
    if (value == 0 || value == 1) {
      return 0;
    }
    unsigned long long f = 2;
    int p = 0;
    while (true) {
      f = f * f;
      if (f > value || f == 0) {
        return p;
      } else {
        p = p + 1;
      }
    }
  }

  pair<nimber, nimber> split(int p) {
    auto[p2, f] = fermat_power(p);
    unsigned long long l = value >> p2;
    unsigned long long r = value & (f - 1);
    return {l, r};
  }

};

nimber operator+(const nimber &l, const nimber &r) {
  return l.value ^ r.value;
}

nimber mulp(nimber x, nimber y, int p);

pair<nimber, nimber> mulpp(nimber lx, nimber rx, nimber ly, nimber ry, unsigned long long f, unsigned long long p) {
  auto rr = mulp(rx, ry, p - 1);
  auto ll = mulp(lx, ly, p - 1);
  auto lz = mulp(lx + rx, ly + ry, p - 1) + rr;
  auto rz = rr + mulp(f >> 1, ll, p - 1);
  return {lz, rz};
}


nimber mulp(nimber x, nimber y, int p) {
  if (p < 2) {
    return mul_table[x.value][y.value];
  }
  if (x == 0 || y == 0) {
    return 0;
  }
  if (x == 1) {
    return y;
  }
  if (y == 1) {
    return x;
  }
  auto[p2, f] = fermat_power(p);
  auto[lx, rx] = x.split(p);
  auto[ly, ry] = y.split(p);
  auto[lz, rz] = mulpp(lx, rx, ly, ry, f, p);
  return (lz.value << p2) + rz.value;
}


nimber operator*(const nimber &x, const nimber &y) {
  if (!x || !y) {
    return 0;
  }
  if (x == 1) {
    return y;
  }
  if (y == 1) {
    return x;
  }
  int p = max(x.prec(), y.prec());
  return mulp(x, y, p);
}

nimber divp(nimber x, nimber y, int p);

nimber normpp(nimber lx, nimber rx, unsigned long long f, unsigned long long p) {
  auto ll = mulp(lx, lx, p - 1);
  auto lr = mulp(lx, rx, p - 1);
  auto rr = mulp(rx, rx, p - 1);
  return mulp(f >> 1, ll, p - 1) + lr + rr;
}


pair<nimber, nimber> divpp(nimber lx, nimber rx, nimber ly, nimber ry, unsigned long long f, unsigned long long p) {
  auto n = normpp(ly, ry, f, p);
  auto[lz, rz] = mulpp(lx, rx, ly, ly + ry, f, p);
  auto lw = divp(lz, n, p - 1);
  auto rw = divp(rz, n, p - 1);
  return {lw, rw};
}

nimber divp(nimber x, nimber y, int p) {
  if (p < 3) {
    return mulp(x, inverse_table[y.value - 1], p);
  }
  if (y == 1) {
    return x;
  }
  if (x == 0) {
    return 0;
  }
  auto[lx, rx] = x.split(p);
  auto[ly, ry] = y.split(p);
  auto[p2, f] = fermat_power(p);
  auto[lw, rw] = divpp(lx, rx, ly, ry, f, p);
  return (lw.value << p2) + rw.value;
}


nimber operator/(const nimber &x, const nimber &y) {
  assert(!(y == 0));
  if (y == 1) {
    return x;
  }
  if (x == 0) {
    return 0;
  }
  int p = max(x.prec(), y.prec());
  return divp(x, y, p);
}


int main() {
#ifdef LOCAL
  freopen("l.in", "r", stdin);
  freopen("l.out", "w", stdout);
#endif

//  for (int i = 0; i < 32; i++) {
//    for (int j = 0; j < 32; j++) {
//      printf("%llu ", (nimber(i) * nimber(j)).value);
//    };
//    printf("\n");
//  }

//  for (int i = 0; i < 32; i++) {
//    for (int j = 1; j < 32; j++) {
//      auto x = nimber(i) / nimber(j);
//      assert(nimber(i) == x * j);
//    }
//  }

  int n;
  scanf("%d", &n);
  vector<vector<nimber>> v(n, vector<nimber>(n));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      scanf("%llu", &v[i][j].value);
    }
  }

  nimber res{1};

  for (int i = 0; i < n; i++) {
    for (int j = i; j < n; j++) {
      if (v[j][i]) {
        v[i].swap(v[j]);
        break;
      }
    }
    if (!v[i][i]) {
      res = 0;
      break;
    }
    res = res * v[i][i];
    for (int j = i + 1; j < n; j++) {
      nimber coef = v[j][i] / v[i][i];
      for (int k = i; k < n; k++) {
        v[j][k] = v[j][k] + coef * v[i][k];
      }
    }
  }

  if (res) {
    printf("First\n");
  } else {
    printf("Second\n");
  }


  return 0;
}
