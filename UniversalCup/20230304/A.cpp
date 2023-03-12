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

int main() {
#ifdef LOCAL
    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);
#endif

    map<string, string> code;
    code["F"] = "UUU UUC";
    code["L"] = "UUA UUG CUU CUC CUA CUG";
    code["I"] = "AUU AUC AUA";
    code["M"] = "AUG";
    code["V"] = "GUU GUC GUA GUG";
    code["S"] = "UCU UCC UCA UCG AGU AGC";
    code["P"] = "CCU CCC CCA CCG";
    code["T"] = "ACU ACC ACA ACG";
    code["A"] = "GCU GCC GCA GCG";
    code["Y"] = "UAU UAC";
    code["H"] = "CAU CAC";
    code["Q"] = "CAA CAG";
    code["N"] = "AAU AAC";
    code["K"] = "AAA AAG";
    code["D"] = "GAU GAC";
    code["E"] = "GAA GAG";
    code["C"] = "UGU UGC";
    code["W"] = "UGG";
    code["R"] = "CGU CGC CGA CGG AGA AGG";
    code["G"] = "GGU GGC GGA GGG";
    code["STOP"] = "UAA UAG UGA";

    int t;
    scanf("%d", &t);
    for (int i = 0; i < t; i++) {
        string s;
        cin >> s;
        string ans = "";
        for (int j = 0; j < (int)s.size(); j += 3) {
            string sub = s.substr(j, 3);
            eprintf("sub = %s\n", sub.c_str());
            string match;
            for (auto [key, val] : code) {
                if (val.find(sub) != string::npos) {
                    match = key;
                    break;
                }
            }
            if (match == "STOP") break;
            ans += match;
        }
        printf("%s\n", ans.c_str());
    }

    return 0;
}
