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

vector<pair<int,int> > v;

bool cmp(const pair<int,int>& a,const pair<int,int>& b){
    return a.second < b.second;
}


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
    int n;
    scanf("%d",&n);
    for (int i = 0; i < n; i++){
        int a,b;
        scanf("%d %d",&a,&b);
        if (a > b)
            swap(a,b);
        v.pb(mp(a,b));
    }    

    sort(v.begin(),v.end(),cmp);

    vector<pair<int,int> > ans;

    for (int i = 0; i < v.size(); i++){
        if (!ans.size() || ans.back().second <= v[i].first)
            ans.pb(v[i]);
    }

    cout << ans.size() << endl;
    for (int i = 0; i < ans.size(); i++)
        cout << ans[i].first <<" "<<ans[i].second << endl;


    return 0;
}                  