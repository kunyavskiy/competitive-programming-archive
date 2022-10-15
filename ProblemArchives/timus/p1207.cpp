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

struct point{
    int x,y;
    int num;
};

bool cmpxy(const point& a,const point& b){
    if (a.y != b.y)
        return a.y < b.y;
    return a.x < b.x;
}

bool cmp(const point& a,const point& b){
    return a.x*1LL*b.y - a.y*1LL*b.x > 0;
}              

point p[11000];


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
    int n;
    scanf("%d ",&n);
    for (int i = 0; i < n; i++)
        scanf("%d %d",&p[i].x,&p[i].y),p[i].num = i+1;

    int id = min_element(p,p+n,cmpxy) - p;
    swap(p[id],p[0]);
    for (int i = n-1; i >= 0; --i)
        p[i].x -= p[0].x,p[i].y -= p[0].y;

    sort(p+1,p+n,cmp);
    cout << p[0].num <<" "<<p[n/2].num << endl;
    return 0;
}