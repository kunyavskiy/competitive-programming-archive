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
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

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

const char prog[] = "loop {\n";

int main() {
#ifdef LOCAL
  freopen("f.in", "r", stdin);
  freopen("f.out", "w", stdout);
#endif

  printf("loop {\n"
             "    if head == nil { break } else { }\n"
             "    if ans_head == nil { } else { break }\n"
             "    prev = nil\n"
             "    ptr = head\n"
             "    loop {\n"
             "        first = ptr\n"
             "        if first == nil { break } else { }\n"
             "        loop {\n"
             "            prev_ptr = ptr\n"
             "            ptr = ptr #next\n"
             "            if ptr == nil { break } else { }\n"
             "            if ptr #value < prev_ptr #value { break } else { }\n"
             "        }\n"
             "        prev_ptr #next = nil\n"
             "        second = ptr\n"
             "        if second == nil {\n"
             "            if prev == nil {\n"
             "                ans_head = head\n"
             "                break\n"
             "            } else {\n"
             "                prev #next = first\n"
             "                break\n"
             "            }\n"
             "        } else { }\n"
             "        loop {\n"
             "            prev_ptr = ptr\n"
             "            ptr = ptr #next\n"
             "            if ptr == nil { break } else { }\n"
             "            if ptr #value < prev_ptr #value { break } else { }\n"
             "        }\n"
             "        prev_ptr #next = nil\n"
             "\n"
             "        if second #value < first #value {\n"
             "            new_ptr = second\n"
             "            second = second #next\n"
             "        } else {\n"
             "            new_ptr = first\n"
             "            first = first #next\n"
             "        }\n"
             "\n"
             "        if prev == nil {\n"
             "            head = new_ptr\n"
             "        } else {\n"
             "            prev #next = new_ptr\n"
             "        }\n"
             "\n"
             "        loop {\n"
             "            if first == nil {\n"
             "                if second == nil {\n"
             "                    break\n"
             "                } else {\n"
             "                    new_ptr #next = second\n"
             "                    new_ptr = second\n"
             "                    second = second #next\n"
             "                }\n"
             "            } else {\n"
             "                if second == nil {\n"
             "                    new_ptr #next = first\n"
             "                    new_ptr = first\n"
             "                    first = first #next\n"
             "                } else {\n"
             "                    if second #value < first #value {\n"
             "                        new_ptr #next = second\n"
             "                        new_ptr = second\n"
             "                        second = second #next\n"
             "                    } else {\n"
             "                        new_ptr #next = first\n"
             "                        new_ptr = first\n"
             "                        first = first #next\n"
             "                    }\n"
             "                }\n"
             "            }\n"
             "        }\n"
             "        prev = new_ptr\n"
             "    }\n"
             "}");

  return 0;
}
