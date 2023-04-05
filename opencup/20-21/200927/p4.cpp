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

#define BIN_INPUT

struct Input {
  static constexpr int AHEAD = 4096;
  static constexpr int SIZE = 4 * 4096;
  unsigned char buffer[SIZE];
  int offset;
  int size;
  bool eof;

  static int read(unsigned char *to, int bytes) {
#ifdef BIN_INPUT
    return fread(to, 1, bytes, stdin);
#else
    auto conv = [](char c) -> unsigned char {
      if ('0' <= c && c <= '9') {
        return c - '0';
      } else {
        return c - 'A' + 10;
      }
    };
    for (int i = 0; i < bytes; i++) {
      char c1, c2;
      if (scanf(" %c%c", &c1, &c2) == 2) {
        to[i] = conv(c1) * 16 + conv(c2);
      } else {
        return i;
      }
    }
    return bytes;
#endif
  }

  Input() {
    offset = 0;
    size = read(buffer, SIZE);
    eof = size != SIZE;
  }

  unsigned char operator[](int pos) {
    assert(pos >= offset);
    if (!eof && pos >= size - AHEAD) {
      memmove(buffer, buffer + AHEAD, SIZE - AHEAD);
      offset += AHEAD;
      int count = read(buffer + SIZE - AHEAD, AHEAD);
      eprintf("read %d bytes\n", count);
      size += count;
      if (count != AHEAD) {
        eof = true;
      }
    }
    assert(pos <= size);
    return buffer[pos - offset];
  }
};

struct Output {
  vector<pair<int, unsigned char>> data;
  void fix(int pos, unsigned char value) {
    data.emplace_back(pos, value);
  }

  void print() {
    vector<unsigned int> packed(data.size());
    for (int i = 0; i < (int)packed.size(); i++) {
      packed[i] = ((unsigned int)data[i].first) | (((unsigned int)data[i].second) << 24u);
    }
#ifdef BIN_INPUT
    fwrite(packed.data(), sizeof(packed[0]), packed.size(), stdout);
#else
    unsigned char *packed_chars = reinterpret_cast<unsigned char*>(packed.data());
    for (int i = 0; i < (int)(packed.size() * sizeof(int)); i++) {
      printf("%02x ", (unsigned int)packed_chars[i]);
    }
    printf("\n");
    for (auto x : data) {
      printf("%d %d\n", x.first, (int)x.second);
    }
#endif
  }
};


int main() {
#ifdef LOCAL
  freopen("p4.in", "r", stdin);
  freopen("p4.out", "w", stdout);
#endif

  Input reader;
  for (int i = 0; i < reader.size; i++) {
    printf("%d ", reader[i]);
  }

  Output writer;
  writer.fix(3, 2);
  writer.fix(5, 0);
  writer.print();

  return 0;
}
