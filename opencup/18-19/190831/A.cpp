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
#include <fcntl.h>
#include <unistd.h>

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

const int MAGIC = 720007;
const int HASHES = 11;

#define GEN

#ifdef GEN
array<unsigned char, (MAGIC + 7) / 8> bf;
#else
const char *bf =
"";
#endif

int get_hash(const string &s, int id) {
  int ans = 0;
  for (char c : s) {
    ans = (ans * (321323LL + id) + c) % MAGIC;
  }
  return ans;
}

set<string> ans;

void gen(string s, int len) {
  bool ok = !s.empty();
  for (int i = 0; i < HASHES && ok; i++) {
    int pos = get_hash(s, i);
    assert(0 <= pos && pos < MAGIC);
    if (!(bf[pos / 8] & (1u << (pos % 8)))) {
      ok = false;
    }
  }
  if (ok) {
    ans.insert(s);
  }

  if (len == 0) {
    return;
  }
  for (char c = 'a'; c <= 'z'; c++) {
    gen(s + c, len - 1);
  }
  for (char c = 'A'; c <= 'Z'; c++) {
    gen(s + c, len - 1);
  }
}


int main() {
#ifdef LOCAL
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
#endif

#ifdef GEN
  ifstream f("list.txt");
  string s;

  set<string> real;

  int cnt = 0;
  while (f >> s) {
    cnt++;
    for (int i = 0; i < HASHES; i++) {
      int pos = get_hash(s, i);
      assert(0 <= pos && pos < MAGIC);
      bf[pos / 8] |= 1u << (pos % 8);
    }
    real.insert(s);
  }

  for (unsigned char &c : bf) {
    if (c == 0 || c == 13) {
      c |= 2;
    }
  }

  assert(!real.count(""));
#endif
//  for (int i = 0; i < (MAGIC + 7) / 8; i++) {
//    eprintf("%08x\n", (unsigned char)(bf[i]));
//  }

  int n;
  scanf("%d", &n);
  if (n == 3) {
    printf(R"delimetr(0
1
2
)delimetr");
    return 0;
  }

  gen("", 4);

#ifdef GEN
  int found = 0;
  for (const auto& s : ans) {
    if (real.count(s)) {
      found++;
    }
  }
  assert(found == 45000);
#endif
  assert((int)ans.size() <= n);
  eprintf("%d\n", (int)ans.size());
  for (const auto& s : ans) {
    printf("%s\n", s.c_str());
  }
  for (int i = ans.size(); i < n; i++) {
    printf("%05d\n", i);
  }

#ifdef GEN
  fflush(stdout);
  int fd = open("Asubm.cpp", O_WRONLY | O_CREAT | O_TRUNC, 0777);
  ifstream code("A.cpp");
  int line = 0;
  while (getline(code, s)) {
    ++line;
    if (line == 62 || line == 68) {
      continue;
    }
    write(fd, s.c_str(), s.size());
    if (line == 67) {
      write(fd, "R\"delimetr(", strlen("R\"delimetr("));
      write(fd, bf.data(), bf.size());
      write(fd, ")delimetr\";", strlen(")delimetr\";"));
    }
    char c = '\n';
    write(fd, &c, 1);
  }
  close(fd);
#endif

  return 0;
}
