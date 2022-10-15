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
#include <bitset>
#include <ctime>
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

int n,m;
int l1,l2,r1,r2;

void iterate(){
    if (l1+2>=r1){
        l1=n+(n%2);
        r1=-2;
    }
    if (l2+2>=r2){
        l2=n+!(n%2);
        r2=-1;
    }
    int L1,L2,R1,R2;

    if (r1!=-2){
        L2=l1-1;          
        R2=r1+1;
    }
    else{
        L2=n+!(n%2);
        R2=-1;
    }
    if (r2!=-1){
        L1=l2-1;
        R1=r2+1;
    }
    else{
        L1=n+(n%2);
        R1=-2;
    }
    L2=max(L2,-1);
    L1=max(L1,-2);
    R2=min(R2,n+!(n%2));
    R1=min(R1,n+(n%2));

    l1=L1;
    l2=L2;
    r1=R1;
    r2=R2;        
}
                

int main(){
  #ifdef LOCAL
    ld start=clock();
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif      
    scanf("%d %d",&n,&m);
    l1=-2;
    l2=-1;
    r1=n+(n%2);
    r2=n+!(n%2);

    for (int i=0;i<m;i++){
        int a;
        scanf("%d",&a);
        --a;    
        if (l1+2==a)
            l1+=2;
        if (l2+2==a)
            l2+=2;
        if (r1-2==a)
            r1-=2;                    
        if (r2-2==a)
            r2-=2;    
        iterate();    
    }   
    if (r1!=-2 || r2!=-1)
        printf("NO\n");
    else
        printf("YES\n");
     
  #ifdef LOCAL
    cerr<<(clock()-start)/CLOCKS_PER_SEC<<endl;
  #endif
    return 0;
}