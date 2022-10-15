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
    #undef assert
    #define assert(x) if (!(x)) throw 1
#endif

using namespace std;

typedef long long ll;
typedef long double ld;

bool used[1100][1100];

char ans[2100];

char a[2100];
char b[2100];
int n;

void solve(int pos1,int pos2,int cnt1,int cnt2){
    if (pos1 == n+1 || pos2 == n+1)
        return;
    if (used[pos1][pos2])
        return;
    if (abs(cnt1 - cnt2) > 1)
        return;
    if (pos1 == n && pos2 == n){
        puts(ans);
        exit(0);
    }
    used[pos1][pos2] = true;
    ans[pos1+pos2] = '1';
    solve(pos1+1,pos2,cnt1 + (a[pos1] == '0'), cnt2 + (a[pos1] == '1'));
    ans[pos1+pos2] = '2';
    solve(pos1,pos2+1,cnt1 + (b[pos2] == '0'), cnt2 + (b[pos2] == '1'));
}


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
    gets(a);
    sscanf(a,"%d",&n);
    gets(a);
    gets(b);

    solve(0,0,0,0);

    cout << "Impossible\n";

    return 0;
}