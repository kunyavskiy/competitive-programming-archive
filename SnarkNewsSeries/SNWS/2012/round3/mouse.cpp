#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <queue>
#include <deque>
#include <stack>
#include <algorithm>
#include <memory.h>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iterator>

#define mp make_pair
#define pb push_back

#ifdef LOCAL
	#define LLD "%I64d"
#else
	#define LLD "%lld"
#endif

#define taskname "mouse"

using namespace std;

typedef long long int64;
typedef long double ld;

struct rect{
    short int xl,xr,yl,yr;
};

rect a[51000];
int next[51000];
int r,c;
int n,m;

int main(){
	#ifndef taskname
		#error taskname is not defined
	#else
		freopen(taskname".in","r",stdin);
		freopen(taskname".out","w",stdout);
	#endif
       
    scanf("%d %d %d",&r,&c,&n);
    for (int i = 0; i < n; i++){
        int A,B,C,D;
        scanf("%d %d %d %d",&A,&B,&C,&D);
        a[i].xl=A;
        a[i].yr=B;
        a[i].xr=C;
        a[i].yl=D;
        next[i] = i-1;
    }
    next[0] = n;

    int head = n-1;

    scanf("%d",&m);
    short int x,y;
    int _x,_y;

    for (int i = 0; i < m; i++){
        int ptr = head;
        int p1 = -1;
        scanf("%d %d",&_x,&_y);
        x = _x;
        y = _y;
        for (;ptr != n;){
            rect& a = ::a[ptr];
            if (a.xl <= x && x <= a.xr && a.yl <= y && y <= a.yr){
                printf("%d\n",ptr+1);
                break;
            }
            p1 = ptr;
            ptr = next[ptr];
        }
        if (ptr == n){
            printf("0\n");
            continue;
        }
        if (p1 != -1){
            next[p1] = next[ptr];
            next[ptr] = head;
            head = ptr;
        }
    }

	return 0;
} 