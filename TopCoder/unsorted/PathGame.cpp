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


class PathGame {

int dp[1100][4][4];

int calc(int n, int m1, int m2){
	if (dp[n][m1][m2] != -1) return dp[n][m1][m2];
	if (n == 0) return 0;
	vector<int> moves;
	for (int i = 0; i < n; i++) 
		for (int t = 1; t <= 2; t++) {
			if (i == 0 && (t & m1) == 0) continue;
			if (i == n-1 && (t & m2) == 0) continue;
			moves.pb(calc(i, m1, t) ^ calc(n - i - 1, t, m2));
		}
	sort(moves.begin(), moves.end());
	moves.erase(unique(moves.begin(), moves.end()), moves.end());
	moves.pb(-1);
	for (int i = 0; ; i++)
		if (moves[i] != i)
			return dp[n][m1][m2] = i;
}

public:
    string judge(vector <string> s) {
        memset(dp,-1,sizeof(dp));
        int lastm = 3;
        int lastid = -1;
        int n = s[0].size();
        int g = 0;
        for (int i = 0; i < n; i++) {
        	if (s[0][i] == '#') {
        		eprintf("%d %d %d: %d\n", i - lastid - 1, lastm, 2, calc(i - lastid - 1, lastm, 2));
        		g ^= calc(i - lastid - 1, lastm, 2), lastid = i, lastm = 2;
        	} else if (s[1][i] == '#') {
        		eprintf("%d %d %d: %d\n", i - lastid - 1, lastm, 1, calc(i - lastid - 1, lastm, 1));
        		g ^= calc(i - lastid - 1, lastm, 1), lastid = i, lastm = 1;
        	}
        }
        eprintf("%d %d %d: %d\n", n - lastid - 1, lastm, 3, calc(n - lastid - 1, lastm, 3));
        g ^= calc(n - lastid - 1, lastm, 3);
        eprintf("g = %d, lastid = %d\n", g, lastid);
        if (g == 0)
        	return "Sothe";
        return "Snuke";
    }
};


int main() {
	PathGame().judge({"........#..","..#........"});
}