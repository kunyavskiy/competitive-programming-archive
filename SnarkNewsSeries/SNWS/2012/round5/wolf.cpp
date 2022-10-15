#include <iostream>
#include <sstream>
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

#define mp make_pair
#define pb push_back

#ifdef LOCAL
	#define LLD "%I64d"
#else
	#define LLD "%lld"
#endif

#define taskname "wolf"

using namespace std;

typedef long long ll;
typedef long double ld;


int p[16];

void dfs(int v,int p){
    if ( ::p[v] != -1)
        return;
    if ((v == 6) || (v == (15^6)) || (v == 12) || (v == (15^12)) || (v == 14) || (v == (15^14)))
        return;
    ::p[v] = p;
    dfs(v^1,v);
    if ((v&1) == !!(v&2))
        dfs(v^3,v);
    if ((v&1) == !!(v&4))
        dfs(v^5,v);
    if ((v&1) == !!(v&8))
        dfs(v^9,v);
}

void gen(int v){
    if (p[v] == -2)
        return;
    int x = v ^ p[v];
    gen(p[v]);
    if (x == 1)
        printf("Self\n");
    if (x == 3)
        printf("Wolf\n");
    if (x == 5)
        printf("Goat\n");
    if (x == 9)
        printf("Cabbage\n");
}

int main(){
	#ifndef taskname
		#error taskname is not defined
	#else
		freopen(taskname".in","r",stdin);
		freopen(taskname".out","w",stdout);
	#endif
        memset(p,-1,sizeof(p));

        string s;
        getline(cin,s);
        stringstream str(s);
        string t;
        int cur = 0;
        while (str >> t){
            if (t == "Farmer")
                cur |= 1;
            if (t == "Wolf")
                cur |= 2;
            if (t == "Goat")
                cur |= 4;
            if (t == "Cabbage")
                cur |= 8;
        }


        dfs(cur,-2);


        if (p[0] == -1){
            printf("Impossible\n");
            return 0;
        }

        gen(0);          
        return 0;
} 