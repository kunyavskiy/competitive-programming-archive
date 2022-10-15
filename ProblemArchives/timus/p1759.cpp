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

const int days[12] = {31,28,31,30,31,30,31,31,30,31,30,31};

bool visok(int y){
    return (y % 4 == 0 && (y % 100 != 0 || y % 400 == 0));
}

int getdate(){
    int d,m,y;
    scanf("%d.%d.%d",&d,&m,&y);
    --m;
    int res = d;
    for (int i = 0; i < m; i++)
        res += days[i] + (i == 1 && visok(y));
    for (int j = 1750; j < y; j++)
        res += 365 + visok(j);
    return res;
}

pair<pair<int,int>,int> getperson(int id){
    int d1 = getdate();
    int d2 = getdate();
    d2 = getdate();

    return mp(mp(d1-d2,d2),id);
}


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    int n;
    scanf("%d",&n);

    vector<pair<pair<int,int>,int> >  v;

    for (int i = 0; i < n; i++) 
        v.pb(getperson(i+1));

    printf("%d\n",min_element(v.begin(),v.end())->second);

    return 0;
}