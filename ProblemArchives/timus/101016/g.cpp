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

pair<int,int> q1[110000],q2[110000];
int ptr1,ptr2,timer;
          

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
    int n;
    scanf("%d",&n);
    for (int i=0;i<n;i++){
        scanf("%d %d",&q1[i].first,&q1[i].second);
        q1[i].second+=q1[i].first-1;
    }
    for (int i=n-2;i>=0;i--)
        q1[i].second=min(q1[i].second,q1[i+1].second-1);
    int m;
    scanf("%d",&m);
    for (int i=0;i<m;i++){
        scanf("%d %d",&q2[i].first,&q2[i].second);
        q2[i].second+=q2[i].first-1;
    }
    for (int i=m-2;i>=0;i--)
        q2[i].second=min(q2[i].second,q2[i+1].second-1);
    //cerr<<q2[0].second<<endl;
    for (;;){
//        cerr<<ptr1<<" "<<ptr2<<" "<<timer<<endl;
        if (ptr1==n && ptr2==m)
            break;
        if (ptr1==n){
            timer=max(timer,q2[ptr2].first);
  //          cerr<<"!!!!!"<<endl;
            if (q2[ptr2].second < timer){
                printf("NO\n");
                return 0;
            }
            timer++;
            ptr2++;
            continue;
        }
        if (ptr2==m){
            timer=max(timer,q1[ptr1].first);
            if (q1[ptr1].second < timer){
                printf("NO\n");
                return 0;
            }
            timer++;
            ptr1++;
            continue;
        }

//        cerr<<"!!!!!"<<endl;

        if (q1[ptr1].first<=timer && q2[ptr2].first<=timer){
  //          cerr<<"!!!"<<endl;
            if (timer>=q2[ptr2].second){
    //            cerr<<"!!!!!!!!!!!!!"<<endl;
                if (q2[ptr2].second < timer){
                    printf("NO\n");
                    return 0;
                }
                timer++;
                ptr2++;
                continue;
            }
                               

            if (q1[ptr1].second < timer){
                printf("NO\n");
                return 0;
            }                
            timer++;
            ptr1++;
            continue;                  
        }

        if (q1[ptr1].first<=timer){  
            if (q1[ptr1].second < timer){
                printf("NO\n");
                return 0;
            }
            timer++;
            ptr1++;
            continue;
        }

        if (q2[ptr2].first<=timer){  
            if (q2[ptr2].second < timer){
                printf("NO\n");
                return 0;
            }
            timer++;
            ptr2++;
            continue;
        }

        
        timer=max(timer,min(q1[ptr1].first,q2[ptr2].first));
    }
    printf("YES\n");
    return 0;
}