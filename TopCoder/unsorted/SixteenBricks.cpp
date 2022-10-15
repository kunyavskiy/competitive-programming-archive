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


class SixteenBricks {
	int calcclose(int x, int y, int mask){
		const int dx[4] = {0, 1, 0, -1};
		const int dy[4] = {1, 0, -1, 0};
		int cnt = 4;
		for (int i = 0; i < 4; i++){
			int nx = x + dx[i];
			int ny = y + dy[i];
			if (nx < 0 || ny < 0 || nx >= 4 || ny >= 4) continue;
			int id = (nx * 4 + ny);
			if (!(mask & (1<<id))) cnt-=2;
		}
		return cnt;
	}
public:
    int maximumSurface(vector <int> v) {
        vector<int> dp(1<<16, -(1<<29));
        dp[0] = 0;
        sort(v.begin(), v.end());
       	for (int j = 0; j < (1<<16); j++) {
       		int id = __builtin_popcount(j);
       		for (int k = 0; k < 16; k++)
       			if (!(j & (1<<k))) 
       				dp[j | (1<<k)] = max(dp[j | (1<<k)], dp[j] + v[id] * calcclose(k / 4, k % 4, j) + 1);
       	}
       	eprintf("%d\n", dp[3]);
       	return dp[0xffff];
    }
};

class SixteenBricks2 {
    int get(vector<int> a){
		const int dx[4] = {0, 1, 0, -1};
		const int dy[4] = {1, 0, -1, 0};
		int ret = 0;
		for (int x = 0; x < 4; x++)
		for (int y = 0; y < 4; y++)
		for (int i = 0; i < 4; i++){
			int nx = x + dx[i];
			int ny = y + dy[i];
			if (nx < 0 || ny < 0 || nx >= 4 || ny >= 4) {
				ret += a[4*x+y];
				continue;
			}
			ret += max(0, a[4*x+y] - a[4*nx + ny]);
		}
		return ret + 16;
    }
	
public:
    int maximumSurface(vector <int> v) {
    	sort(v.begin(), v.end());
    	int res = 16;
    	for (int i = 0; i < (int)v.size(); i++) res += 4*v[i];
    	for (int i = 0; i < 2; i++) res -= 2*4*v[i];
    	for (int i = 2; i < 6; i++) res -= 2*3*v[i];
    	for (int i = 6; i < 8; i++) res -= 2*2*v[i];
    	return res;
    }
};


int main(){
	while (true){
		vector<int> a(16);
		for (int i = 0; i < 16; i++)
			a[i] = rand() % 100 + 1;

		int ans1 = SixteenBricks().maximumSurface(a);
		int ans2 = SixteenBricks2().maximumSurface(a);

		if (ans1 != ans2){
			for (int i = 0; i < 16; i++)
				printf("%d ", a[i]);
			break;
		}
		printf("%d == %d\n", ans1, ans2);
	}
}
