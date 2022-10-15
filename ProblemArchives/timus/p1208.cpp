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
    #undef assert
    #define assert(x) if (!(x)) throw 1
#endif

using namespace std;

typedef long long ll;
typedef long double ld;


string a[18][3];
int id[18][3];

map<string,int> ids;

bool check(int mask){
    set<int> s;

    for (int i = 0; i < 18; i++)
        if (mask & (1<<i))
            for (int j = 0; j < 3; j++)
                if (!s.insert(id[i][j]).second)
                    return false;
    return true;
}

int bcnt(int a){
    int ans = 0;
    for (int i = 1; i <= a; i<<=1)
        ans += !!(i&a);
    return ans;
}

int get(string s){
    if (ids.find(s) != ids.end())
        return ids[s];
    int temp = ids.size();
    return ids[s] = temp;
}

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
    int n;
    scanf("%d",&n);
    for (int i = 0; i < n; i++){
        cin >> a[i][0] >> a[i][1] >> a[i][2];
        id[i][0] = get(a[i][0]);
        id[i][1] = get(a[i][1]);
        id[i][2] = get(a[i][2]);
    }

    int ans = 0;

    for (int mask = (1<<n)-1; mask >= 0; mask--)
        if (bcnt(mask) > ans && check(mask))
            ans = max(ans,bcnt(mask));
    cout << ans << endl;
    return 0;
}