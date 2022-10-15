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


int dp[110][110];
char s[110];


int calc(int l,int r){
    if (l >= r)
        return 0;
    int& ans = dp[l][r];
    if (ans != -1)
        return ans;
    ans = 1<< 29;
    for (int i = l+1; i < r; i++)
        ans = min(ans,calc(l,i)+calc(i,r));
    ans = min(ans,calc(l+1,r)+2);
    ans = min(ans,calc(l,r-1)+2);
    if (s[l] == '(' && s[r-1] == ')')
        ans = min(ans,calc(l+1,r-1)+2);
    if (s[l] == '[' && s[r-1] == ']')
        ans = min(ans,calc(l+1,r-1)+2);
    return ans;
}


void gen(int l,int r){
    if (l >= r)
        return;
    int ans = calc(l,r);
    for (int i = l+1; i < r; i++)
        if (ans == calc(l,i) + calc(i,r)){
            gen(l,i);
            gen(i,r);
            return;
        }
    if (ans == calc(l+1,r) + 2){
        if (s[l] == '[' || s[l] == ']')
            printf("[]");        
        else
            printf("()");
        gen(l+1,r);
        return;
    }
    if (ans == calc(l,r-1) + 2){
        gen(l,r-1);
        if (s[r-1] == '[' || s[r-1] == ']')
            printf("[]");
        else
            printf("()");
        return;
    }
    printf("%c",s[l]);
    gen(l+1,r-1);
    printf("%c",s[r-1]);

}


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    gets(s);
    memset(dp,-1,sizeof(dp));
    gen(0,strlen(s));

    return 0;
}