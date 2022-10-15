#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <queue>
#include <deque>
#include <stack>
#include <algorithm>
#include <memory.h>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iterator>
#include <cassert>

#define mp make_pair
#define pb push_back

#ifdef LOCAL
	#define LLD "%I64d"
#else
	#define LLD "%lld"
#endif

#define taskname "opsos"

using namespace std;

typedef long long int64;
typedef long double ld;

int ans[(1<<10)+10][(1<<10)+10][2];

int mask[10];
int n;

int dfs(int mask1,int mask2,int h){
    if (ans[mask1][mask2][h] != -1)
        return ans[mask1][mask2][h];
    if (h == 0){
        for (int i = 0; i < n; i++){
            if (mask[i] & mask1)
                continue;
            if (mask1 & (1<<i))
                continue;
            if (mask2 & (1<<i))
                continue;
            if (dfs(mask1|(1<<i),mask2,1-h) == 0 || dfs(mask1|(1<<i),mask2,h))
                return ans[mask1][mask2][h] = 1;
        }
        return ans[mask1][mask2][h] = 0;
    }
    else {
        for (int i = 0; i < n; i++){
            if (mask[i] & mask2)
                continue;
            if (mask1 & (1<<i))
                continue;
            if (mask2 & (1<<i))
                continue;
            if (dfs(mask1,mask2|(1<<i),1-h) == 0 || dfs(mask1,mask2|(1<<i),h))
                return ans[mask1][mask2][h] = 1;
        }
        return ans[mask1][mask2][h] = 0;
    }
}

int main(){
	#ifndef taskname
		#error taskname is not defined
	#else
		freopen(taskname".in","r",stdin);
		freopen(taskname".out","w",stdout);
	#endif

    memset(ans,-1,sizeof(ans));

    string s;
    getline(cin,s);
    n = s.size();

    int m1,m2;
    m1 = m2 = 0;
    for (int i = 0; i < n; i++)
        if (s[i] == 'G')
            m1 |= (1<<i);
        else if (s[i] == 'B')
            m2 |= (1<<i);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++){
            char c;
            scanf(" %c ",&c);
            if (c == '+'){
                mask[i] |= (1<<j);
                assert(i != j);
            }
        }

    int temp = dfs(m1,m2,0);
    if (temp == 0)
         puts("G");
    else
         puts("B");
	return 0;
} 