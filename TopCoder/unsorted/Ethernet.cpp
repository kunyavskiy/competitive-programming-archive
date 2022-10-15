#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <cstdlib>
#include <cstdio>
#include <stack>
#include <algorithm>
#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <iterator>
#include <functional>
#include <bitset>
#include <ctime>
#include <cassert>
#define pb push_back
#define mp make_pair      
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
using namespace std;
 
typedef long long ll;
typedef long double ld;


class Ethernet {

vector<int> g[55], d[55];
vector<vector<int>> dp[550];
int k;

int calc(int v, int son, int maxh){
	if (son == -1) {
		return 0;
	}
	int& res = dp[maxh][v][son];
	if (res != -1) return res;
	
	res = 1<<30;
	int ch = g[v][son];
	int chs = (int)g[ch].size()-1;
	res = calc(ch, chs, k) + calc(v, son-1, maxh) + 1;
	
    for (int i = 0; i + d[v][son] <= maxh; i++) {
    	res = min(res, calc(ch, (int)g[ch].size()-1, maxh - d[v][son]) + calc(v, son - 1, min(maxh, k - (i + d[v][son]))));
    }
    return res;
}

public:
    int connect(vector <int> p, vector <int> dst, int _k) {
    	k = _k;
        int n = p.size()+1;
        for (int i = 0; i < n - 1; i++)
        	g[p[i]].pb(i+1), d[p[i]].pb(dst[i]);
       	for (int j = 0; j <= k; j++) {
       		dp[j].resize(n);
	        for (int i = 0; i < n; i++)
        		dp[j][i].resize(g[i].size(),-1);
        }
        return calc(0, (int)g[0].size() - 1, k) + 1;
    }
};
