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

pair<int,pair<int,int> > v[50];


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
    int n;
    scanf("%d",&n);
    for (int i = 0; i < n; i++)
        scanf("%d %d %d",&v[i].first,&v[i].second.first,&v[i].second.second);
    sort(v,v+n);

    int ans = 0;

    for (int i = 0; i < n; i++){
        v[i].second.first += max(v[i].first,(i?v[i-1].second.first:0));
        ans = max(ans,v[i].second.first - v[i].second.second);
    }

    cout << ans << endl;       

    return 0;
}