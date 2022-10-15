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




class ConvenientBlock {

vector<vector<int>> g;
vector<vector<ll>> c;
vector<int> used;
int usedpt;
int n;

ll dfs(int v, ll cur, ll minv) {
	if (used[v] == usedpt) return 0;
	if (v == n - 1) return cur;
	used[v] = usedpt;
	for (int i = 0; i < n; i++)
		if (c[v][i] >= minv) {
			ll tmp = dfs(i, min(cur, c[v][i]), minv);
			if (tmp) {
				c[v][i] -= tmp;
				c[i][v] += tmp;
				return tmp;
			}
		}
	return 0;
}

public:
    ll minCost(int n, vector <int> from, vector <int> to, vector <int> cost) {
        this->n = n;
        g = vector<vector<int>>(n, vector<int>(n, 0));
        c = vector<vector<ll>>(n, vector<ll>(n, 0));
        for (int i = 0; i < (int)from.size(); i++) {
        	g[from[i]][to[i]] = 1;
        	c[from[i]][to[i]] += cost[i];
        	c[to[i]][from[i]] += (ll)1e18;
        }
        
        for (int i = 0; i < n; i++)
        	g[i][i] = 1;
        	
        for (int k = 0; k < n; k++)
        	for (int i = 0; i < n; i++)
        		for (int j = 0; j < n; j++)
        			g[i][j] |= g[i][k] && g[k][j];
        			
       	for (int i = 0; i < n; i++)
       		if (!g[0][i] || !g[i][n]){
       		    for (int j = 0; j < n; j++)
       		    	c[i][j] = c[j][i] = 0;
       		}
        used = vector<int>(n);
        ll tot = 0;
        usedpt = 0;
        for (ll cost = 1LL<<60; cost; cost >>= 1){
        	ll tmp;
        	usedpt++;
        	while ((tmp = dfs(0, cost, cost))){
        		tot += tmp;
        		usedpt++;
        		if (tot >= 1e15) return -1;
        	}
        } 
        return tot;
    }
};
