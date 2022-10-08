#include <algorithm>
#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <assert.h>

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x, ...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

using namespace std;

typedef long long ll;
typedef long double ld;

void PreCalc() {
}

const string NO = "IMPOSSIBLE";

const char* names = "!RYOBVG!";

string extend(string cur, char c, char nc) {
  if (cur == NO) {
    return NO;
  }
  if (cur == "") {
    return (string("") + c) + nc;
  }
  for (int i = 0; i < (int)cur.size(); i++) {
    if (cur[i] == c) {
      string res = ((cur.substr(0, i + 1) + nc) + c) + cur.substr(i + 1);
      assert(res.size() == cur.size() + 2);
      if (res[0] == res.back()) {
        return NO;
      }
      return res;
    }
  }
  return NO;
}

string solve(vector<int> colors) {
  int mid = -1, smid = -1;
  for (int i = 1; i < 8; i *= 2) {
    if (colors[7 ^ i] > 0) {
      if (colors[i] == 0) {
        return NO;
      }
      colors[i]--;
      colors[i ^ 7]--;
      string res = solve(colors);
      res = extend(res, names[i], names[i ^ 7]);
      return res;
    }
    int t = i;
    if (mid == -1 || colors[mid] < colors[t]) {
      int tt = t;
      t = mid;
      mid = tt;
    }
    if (t != -1 && (smid == -1 || colors[smid] < colors[t])) {
      int tt = t;
      t = smid;
      smid = tt;
    }
  }
  if (colors[mid] == 0) {
    return "";
  }
  if (colors[mid] == 1) {
    string res = "";
    for (int i = 1; i < 8; i *= 2) {
      if (colors[i]) {
        res += names[i];
      }
    }
    return res;
  }
  if (colors[smid] <= 0) {
    return NO;
  }
  colors[mid]--;
  colors[smid]--;
  string res = solve(colors);
  string ores = res;
  res = extend(res, names[mid], names[smid]);
  assert(res == NO || ores == NO || res.size() == ores.size() + 2);
  return res;
}

void solve() {
  int N, R, O, Y, G, B, V;
  scanf("%d%d%d%d%d%d%d", &N, &R, &O, &Y, &G, &B, &V);

  vector<int> colors = vector<int>(8);
  colors[1] = R;
  colors[2] = Y;
  colors[3] = O;
  colors[4] = B;
  colors[5] = V;
  colors[6] = G;

  string s = solve(colors);
  if (s != NO) {
    if ((int) s.size() != N) {
      s = NO;
      assert(0);
    } else {
      for (int i = 0; i < (int) s.size(); i++) {
        char c = s[i];
        char c1 = s[(i + 1) % s.size()];
        assert(strchr(names, c) != NULL);
        assert(strchr(names, c1) != NULL);
        int cc = strchr(names, c) - names;
        int cc1 = strchr(names, c1) - names;
        assert(1 <= cc && cc <= 6);
        assert(1 <= cc1 && cc1 <= 6);
        assert(!(cc & cc1));
      }
    }
  }
  printf("%s\n", s.c_str());
}


int main() {
//  freopen("b.in", "r", stdin);
//  freopen("B-large.in", "r", stdin);
//  freopen("B-small-attempt0.in", "r", stdin);
//  freopen("b.out", "w", stdout);


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