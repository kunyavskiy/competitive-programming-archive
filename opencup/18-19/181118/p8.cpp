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

struct Figure {
  int id;
  string type;
  int coord[3][2];
  bool included[3];

  Figure() {
    id = 0;
    type = "";
    memset(coord, 0, sizeof(coord));
    memset(included, 0, sizeof(included));
  }

  Figure intersectWith(Figure f) {
    Figure res;
    for (int i = 0; i < 3; i++) {
      res.coord[i][0] = max(coord[i][0], f.coord[i][0]);
      res.coord[i][1] = min(coord[i][1], f.coord[i][1]);
      res.included[i] = true;
      if (coord[i][0] == res.coord[i][0] && !included[i])
        res.included[i] = false;
      if (f.coord[i][0] == res.coord[i][0] && !f.included[i])
        res.included[i] = false;
      if (coord[i][1] == res.coord[i][1] && !included[i])
        res.included[i] = false;
      if (f.coord[i][1] == res.coord[i][1] && !f.included[i])
        res.included[i] = false;
      if (res.coord[i][1] < res.coord[i][0] || (res.coord[i][1] == res.coord[i][0] && !res.included[i])) {
        res.id = -1;
      }
    }
    return res;
  }

  int dim() const {
    int s = 0;
    for (int i = 0; i < 3; i++) if (coord[i][1] > coord[i][0]) s++;
    return s;
  }

  void print() {
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 2; j++) {
        printf("%d ", coord[i][j]);
      }
    }
    printf(" ");
    for (int i = 0; i < 3; i++) {
      printf("%d", included[i] ? 1 : 0);
    }
  }
};

vector<Figure> readParallelogram();

void solveTest() {
  vector<Figure> a = readParallelogram();
  vector<Figure> b = readParallelogram();
  vector<Figure> res;
  for (int i = 0; i < (int) a.size(); i++) {
    Figure fa = a[i];
    for (int i1 = 0; i1 < (int) b.size(); i1++) {
      Figure fb = b[i1];
      Figure c = fa.intersectWith(fb);
      if (c.id != -1) {
        c.id = res.size() + 1;
        stringstream str;
        str << "pcs"[c.dim()] << "VEF"[fa.dim()] << "VEF"[fb.dim()] << " " << (i + 1) << " " << (i1 + 1);
        c.type = str.str();
        res.push_back(c);
      }
    }
  }
//        System.err.println(res.size());
  sort(res.begin(), res.end(), [](const Figure &a, const Figure &b) {
    return a.dim() < b.dim();
  });
  for (int i = 0; i < (int) res.size(); i++) {
    res[i].id = i + 1;
  }

  vector<int> d(3);
  for (const Figure &f : res) {
    d[f.dim()]++;
  }
  for (int i = 0; i < 3; i++) {
    printf("%d ", d[i]);
  }
  printf("\n");

  vector<vector<Figure>> byType(3);
  for (const Figure &f : res) {
    byType[f.dim()].push_back(f);
  }

  for (const Figure &f : res) {
    printf("%d %s ", f.id, f.type.c_str());
    if (f.dim() == 0) {
      printf("%d %d %d", f.coord[0][0], f.coord[1][0], f.coord[2][0]);
      vector<int> q;
      for (const Figure &f2 : byType[1]) {
        Figure ff = f2;
        ff.included[0] = ff.included[1] = ff.included[2] = true;
        if (ff.intersectWith(f).id != -1) {
          q.push_back(f2.id);
        }
      }
      printf("  %d  ", (int) q.size());
      for (int figure : q) {
        printf("%d ", figure);
      }
    } else if (f.dim() == 1) {
      vector<int> q;
      for (const Figure &f2 : byType[0]) {
        Figure ff = f;
        ff.included[0] = ff.included[1] = ff.included[2] = true;
        if (ff.intersectWith(f2).id != -1) {
          q.push_back(f2.id);
        }
      }
      for (int figure : q) {
        printf("%d ", figure);
      }
    } else {
      vector<int> q;
      for (const Figure &f2 : byType[1]) {
        Figure ff = f;
        ff.included[0] = ff.included[1] = ff.included[2] = true;
        if (ff.intersectWith(f2).id != -1) {
          q.push_back(f2.id);
        }
      }
      printf("  %d  ", (int) q.size());
      for (int figure : q) {
        printf("%d ", figure);
      }
    }
    printf("\n");
  }
  printf("===\n");
}

vector<Figure> readParallelogram() {
  vector<Figure> res(26);
  int coord[3][2];
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 3; j++) {
      scanf("%d", &coord[j][i]);
    }
  }
  int k = 0;
  for (int l1 = 0; l1 < 2; l1++) {
    for (int r1 = l1; r1 < 2; r1++) {
      for (int l2 = 0; l2 < 2; l2++) {
        for (int r2 = l2; r2 < 2; r2++) {
          for (int l3 = 0; l3 < 2; l3++) {
            for (int r3 = l3; r3 < 2; r3++) {
              if (r1 - l1 + r2 - l2 + r3 - l3 < 3) {
                Figure f;
                f.coord[0][0] = coord[0][l1];
                f.coord[0][1] = coord[0][r1];
                f.coord[1][0] = coord[1][l2];
                f.coord[1][1] = coord[1][r2];
                f.coord[2][0] = coord[2][l3];
                f.coord[2][1] = coord[2][r3];
                for (int i = 0; i < 3; i++) {
                  f.included[i] = f.coord[i][0] == f.coord[i][1];
                }
                res[k++] = f;
              }
            }
          }
        }
      }
    }
  }
  return res;
}

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    solveTest();
  }
}
