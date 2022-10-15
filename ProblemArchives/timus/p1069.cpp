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
#endif

using namespace std;

typedef long long ll;
typedef long double ld;

vector<int> g[11000];

multiset<int> s;
multiset<int> s2;

int a[11000];


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    int n = 1;
    for (;;){
        if (scanf("%d",&a[n-1]) == 1)
            n++;
        else
            break;
        s.insert(--a[n-2]);
    }

    for (int i = 0; i < n; i++)
        if (s.find(i) == s.end())
           s2.insert(i); 

    for (int i = 0; i < n-1; i++){                
        assert(s2.size());
        int temp = *s2.begin();       
        g[temp].pb(a[i]);
        g[a[i]].pb(temp);
        s.erase(s.find(a[i]));
        s2.erase(s2.begin());
        if (s.find(a[i]) == s.end())
            s2.insert(a[i]);
    }

    for (int i = 0; i < n; i++){
        printf("%d:",i+1);
        sort(g[i].begin(),g[i].end());
        for (int j = 0; j < g[i].size(); j++)
            printf(" %d",g[i][j]+1);
        printf("\n");
    }
    
    return 0;
}