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

struct command {
  string from;
  string to;
  bool ret;
  string toString() {
    if (ret) { return from + "=(return)" + to; }
    return from + "=" + to;
  }
};

string str(char c1) { return string() + c1; }
string str(char c1, char c2) { return string() + c1 + c2; }
string str(char c1, char c2, char c3) { return string() + c1 + c2 + c3; }

int main() {
#ifdef LOCAL
  freopen("m.in", "r", stdin);
  freopen("m.out", "w", stdout);
#endif

  vector<command> cmds;

  for (int a = 0; a <= 1; a++) {
    for (int b = 0; b <= 1; b++) {
      for (int c = 0; c < 3; c++) {
        cmds.push_back({str(a ? 'Y' : 'N', 'a' + c, b ? 'Y' : 'N'), str((a && b) ? 'Y' : 'N', 'a' + c), false});
      }
    }
  }

  for (int a = 0; a < 3; a++) {
    cmds.push_back({str('a' + a, 'N'), str('N', 'a' + a), false});
  }
  cmds.push_back({"SN", "NS", false});
  cmds.push_back({"PN", "", false});

  for (int a = 0; a < 3; a++) {
    for (int b = 0; b < 3; b++) {
      cmds.push_back({str('A' + a, 'a' + b), str('a' + b, 'A' + a), false});
    }
    cmds.push_back({str('A' + a, 'S'), str('S', 'A' + a), false});
  }
  for (int a = 0; a < 3; a++) {
    for (int b = 0; b < 3; b++) {
      cmds.push_back({str('a' + a, 'A' + b), str((a == b ? 'Y' : 'N'), 'a' + a), false});
    }
  }
  for (int a = 0; a < 3; a++) {
    cmds.push_back({str('a' + a, 'P'), str('P', 'a' + a, 'A' + a), false});
  }
  for (int a = 0; a < 3; a++) {
    cmds.push_back({str('a' + a, 'Q'), str('P', 'A' + a), false});
  }
  for (int a = 0; a < 3; a++) {
    cmds.push_back({str('S', 'A' + a), "S", false});
  }
  cmds.push_back({"SY", "1", true});
  cmds.push_back({"Q", "0", true});
  cmds.push_back({"Y", "0", true});
  cmds.push_back({"N", "0", true});
  cmds.push_back({"S", "QS", false});

#ifdef LOCAL1
  for (int i = 0; i < 1000; i++) {
    string s;
    {
      int ls = rand() % 1000 + 1;
      for (int j = 0; j < ls; j++) {
        s += 'a' + rand() % 3;
      }
    }
    string t;
    if (rand() % 2 == 0) {
      int lt = rand() % 100 + 1;
      for (int j = 0; j < lt; j++) {
        t += 'a' + rand() % 3;
      }
    } else {
      int l, r;
      do {
        l = rand() % s.size();
        r = rand() % s.size() + 1;
      } while (l >= r);
      t = s.substr(l, r - l);
    }
    int nnn = 125;
    s = string((2 * nnn) / 3 , 'a');
    t = 'b' + string(nnn / 3, 'a');
    //s = "ccaaccc";
    //t = "caacc";
    string input = s + 'S' + t;
    //eprintf("input = %s\n", input.c_str());
    bool finish = false;
    int ops = 0;
    int ops_limit = max<int>(2 * input.size() * input.size(), 50);
    while (!finish) {
      ops++;
      bool done = false;
      //printf("%s\n", input.c_str());
      for (auto &cmd: cmds) {
        auto pos = input.find(cmd.from);
        if (pos == string::npos) continue;
        if (cmd.ret) {
          input = cmd.to;
          printf("%s\n", input.c_str());
          break;
        }
        done = true;
        input = input.replace(pos, cmd.from.size(), cmd.to);
        break;
      }
      if (!done) {
        finish = true;
      }
    }
    fflush(stdout);
    eprintf("%sS%s -> %s in %d of %d\n", s.c_str(), t.c_str(), input.c_str(), ops, ops_limit);
    assert(ops <= ops_limit);
    if (s.find(t) != string::npos) {
      assert(input == "1");
    } else {
      assert(input == "0");
    }
  }
  printf("===============\n");
#endif
  for (auto cmd: cmds) {
    printf("%s\n", cmd.toString().c_str());
  }


  return 0;
}
