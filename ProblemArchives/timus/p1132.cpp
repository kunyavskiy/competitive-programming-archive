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
    #undef assert
    #define assert(x) if (!(x)) throw 1
    #define LLD "%lld"
	#define M_PI 3.1415926535897932384626433832795
    #define prev prev_dsfdfgfhgfh
#endif

using namespace std;

typedef long long ll;
typedef long double ld;

const int MAXN = 110000;

pair<pair<int,int>,int> req[MAXN];
int ans[MAXN];
int n;

bool cmpsec(const pair<pair<int,int>,int>& a,const pair<pair<int,int>,int>& b){
    return a.second < b.second;
}

int s[MAXN];


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
    int t;
    scanf("%d",&t);
    for (int i = 0; i < t; i++){
        scanf("%d %d",&req[i].first.second,&req[i].first.first);
        req[i].first.second %= req[i].first.first;
        req[i].second = i;
    }

    sort(req,req+t);

    for (int i = 0; i < t;){
        int j = i;
        for (;j < t && req[j].first.first == req[i].first.first; j++);

        int n = req[i].first.first;
        int val = 0;
        memset(s,-1,sizeof(int)*n);
        {
            for (int j = 0; 2*j <= n; j++){
                s[val] = j;
                val += (2*j+1);
                while (val >= n)
                    val -= n;
            }
        }

        for (;i < j; i++)
            ans[req[i].second] = s[req[i].first.second];

    }

    sort(req,req+t,cmpsec);

    for (int i = 0; i < t; i++){

        if (ans[i] == -1)
            printf("No root\n");
        else if (ans[i] == 0 || req[i].first.first - ans[i] == ans[i])
            printf("%d\n",ans[i]);
        else {
            assert(ans[i] < req[i].first.first - ans[i]);
            printf("%d %d\n",ans[i],req[i].first.first - ans[i]);
        }
    }



    return 0;
}