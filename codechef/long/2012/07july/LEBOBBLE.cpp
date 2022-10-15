// WHAT'S WRONG WITH YOU GUYS??? WTF IS PENTIUM 3??? PLEASE UPGRADE SERVERS! IT'S RIDICULOUS TO TEST SOLUTIONS ON 9-YEAR OLD SYSTEM!"
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

#if ( _WIN32 || __WIN32__ )
    #define LLD "%I64d"
    #define LLDP "%0*I64d"
#else
    #define LLD "%lld"
    #define LLDP "%0*lld"
#endif

using namespace std;

typedef long long ll;
typedef long double ld;

const int MAXN = 110000;

pair<int,int> a[MAXN];
int n,d;
long long ans;


void solve(int l,int r){
    if (l >= r-1)
       return;                           
    int mid = (l+r)/2;
    solve(l,mid);
    solve(mid,r);

    int ptr1 = l;
    int ptr2 = mid;
    int ptr3 = mid;
    int ptr4 = mid;
    int sum2 = 0;
    int sum1 = 0; 

    for (;ptr1 < mid;ptr1++){
        for (;ptr3 < r && a[ptr3].first < a[ptr1].first + d; ptr3++)
            sum1 += 100 - a[ptr3].second;

        for (;ptr4 < r && a[ptr4].first < a[ptr1].first; ptr4++){
            sum1 -= 100 - a[ptr4].second;
            sum2 += a[ptr4].second;
        }

        for (;ptr2 < r && a[ptr2].first < a[ptr1].first - d; ptr2++){
            sum2 -= a[ptr2].second;
        }
        //cerr << ptr1 <<" "<<ptr2 <<" "<<ptr3 <<" "<<ptr4 << " "<<sum1 <<" "<<sum2 << endl;
        ans += sum1*a[ptr1].second + (ptr4-mid)*10000 - sum2 * (100 - a[ptr1].second);           
    }
    inplace_merge(a+l,a+mid,a+r);
}

void solve(){
    scanf("%d %d",&n,&d);
    for (int i = 0; i < n; i++)
        scanf("%d",&a[i].first);
    for (int i = 0; i < n; i++)
        scanf("%d",&a[i].second);
    ans = 0;
    solve(0,n);
    printf(LLD"."LLDP"\n",ans/10000,4,ans%10000);
}

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    int t;
    scanf("%d",&t);
    while (t-->0)
        solve();


  return 0;
}