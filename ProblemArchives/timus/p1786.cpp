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

#define forn(i,n) for(int i=0;i<(n);i++)
#define ford(i,n) for(int i=(n)-1;i>=0;i--)

#ifdef LOCAL
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

typedef long long int64;
typedef long long ll;
typedef long double ld;
                            
string s;
const string sandro="Sandro\n";
int n;

int cost(char c1,char c2){
    bool q1='A'<=c1 && c1<='Z';
    bool q2='A'<=c2 && c2<='Z';
    int ans=0;
    if (q1 ^ q2){
        ans++;
        if (q1) c1=c1-'A'+'a';
        else c2=c2-'A'+'a';
    }
    if (c1!=c2)
        ans++;
    return ans;
}

int cost(int i){
    if (i+6>n)
        return 1<<30;
    int ans=0;
    for (int j=0;j<6;j++)
        ans+=cost(s[i+j],sandro[j]);
    return ans;    
}

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif                                                                                                          
    getline(cin,s);
    n=s.size();
    int ans=1<<30;
    for (int i=0;i<n;i++)
        ans=min(ans,cost(i));
    cout<<ans*5<<endl;
    return 0;
}