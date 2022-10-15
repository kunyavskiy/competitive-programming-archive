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

int q[1100];
map<string,int> number;

int num[1100];
int kol[1100];
int need[1100];
int tovar[1100];

char s[1100];


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
    int m;
    scanf("%d",&m);
    for (int i=0;i<m;i++){        
        scanf("%d of %s ",&kol[i],s);
        string name=s;
        number.insert(mp(s,i));  
    }
    int n;
    scanf("%d",&n);
    for (int i=0;i<n;i++){
        scanf("%d of %s ",&need[i],s);
        string name=s;
        if (number.find(name)!=number.end())
            tovar[i]=number[name];
        else
            tovar[i]=-1;
        q[i]=i;
    }                       
    q[n]=n;
    int ptr=0;
    for (int iter=0;;++iter){
        if (q[ptr]==n){
            cout<<iter<<endl;
            return 0;
        }
        int v=q[ptr];
        if (tovar[v]==-1 || kol[tovar[v]]==0)
            ++ptr;
        else{
            if (kol[tovar[v]]>=need[v]){
                kol[tovar[v]]-=need[v];
                ++ptr;
            }
            else{
                swap(q[ptr],q[ptr+1]);
                need[v]=kol[tovar[v]];
            }
        }
    }
    return 0;
}