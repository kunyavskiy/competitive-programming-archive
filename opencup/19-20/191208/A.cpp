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

string month[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sept",
"Oct", "Nov", "Dec"};

int main() {
#ifdef LOCAL
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
#endif

  int t;
  scanf("%d", &t);
  auto get_date = []() {
    char buf[100];
    string full = "";
    scanf("%s", buf);
    full += buf;
    int id = find(begin(month), end(month), buf) - month;
    assert(id < end(month) - begin(month));
    scanf("%s", buf);
    int day;
    full += ' ';
    full += buf;
    sscanf(buf, "%d", &day);
    return make_tuple(id, day, full);
  };
  for (int i = 1; i <= t; i++) {
    printf("Case #%d: ", i);;
    int n;
    scanf("%d", &n);
    vector<tuple<int, int, string>> v(n);
    for (auto& x : v) {
      x = get_date();
    }
    sort(v.begin(), v.end());
    auto need = get_date();
    auto it = upper_bound(v.begin(), v.end(), need);
    if (it == v.end()) {
      printf("See you next year\n");
    } else {
      printf("%s\n", get<2>(*it).c_str());
    }
  }

  return 0;
}
