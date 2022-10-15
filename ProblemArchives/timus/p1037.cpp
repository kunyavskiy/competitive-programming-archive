#ifndef LOCAL
    #pragma comment(linker, "/STACK:33554432")
#endif

#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <cmath>
#include <cassert>
#include <ctime>
#include <algorithm>
#include <queue>
#include <memory.h>
#include <stack>
#define mp make_pair
#define pb push_back                     
#define setval(a,v) memset(a,v,sizeof(a))



#ifdef LOCAL
    #define LLD "%I64d"
#else
    #define LLD "%lld"
	#define M_PI 3.1415926535897932384626433832795
    #define prev prev_dsfdfgfhgfh
    #define next next_mkdlsmfdgkl
    #define hash hash_mdfdsgdhgfm
    #undef assert
    #define assert(x) if (!(x)) throw 1
    #define sqrt(x) sqrt((double)(x))
#endif

using namespace std;

typedef long long ll;
typedef long double ld;

set<int> f;
set<pair<int,int> > used;

int last[31000];


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    int t;char c;
    int id;

    for (int i = 1; i <= 30000; i++)
        f.insert(i),last[i] = -1;

    
    while (scanf("%d %c",&t,&c) == 2){
        if (c == '.')
            scanf("%d",&id);

        while (used.size() && used.begin()->first <= t - 600){
            f.insert(used.begin()->second);
            last[used.begin()->second] = -1;
            used.erase(used.begin());
        }

        if (c == '.'){
            if (last[id] == -1){
                printf("-\n");
                continue;
            }
            used.erase(mp(last[id],id));
            last[id] = t;
            used.insert(mp(last[id],id));
            printf("+\n");
            continue;
        }

        id = *f.begin();
        last[id] = t;
        used.insert(mp(t,id));
        f.erase(id);
        printf("%d\n",id);           
    }
        


    return 0;
}