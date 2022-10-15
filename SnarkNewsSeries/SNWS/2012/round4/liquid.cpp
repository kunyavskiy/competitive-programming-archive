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

#define taskname "liquid"

using namespace std;

typedef long long int64;
typedef long double ld;

int n;
bool can[110];


int d[110][110];

queue<int> qx,qy;

void update(int a,int b,int c,int d){
    if ( ::d[a][b] > ::d[c][d]+1){
        ::d[a][b] = ::d[c][d]+1;
        qx.push(a);
        qy.push(b);
    }
}

int main(){
	#ifndef taskname
		#error taskname is not defined
	#else
		freopen(taskname".in","r",stdin);
		freopen(taskname".out","w",stdout);
	#endif

        can[0] = true;

        scanf("%d",&n);
        int maxv = 0;
        for (int i = 0; i < n; i++){
            int a;
            scanf("%d",&a);
            can[a] = true;
            maxv = max(maxv,a);
        }

        int need = 0;
        scanf("%d",&need);

        memset(d,63,sizeof(d));

        qx.push(0),qy.push(0);
        d[0][0] = 0;

        for (;!qx.empty();){
            int x = qx.front();qx.pop();
            int y = qy.front();qy.pop();

            if (x == need || y == need){
                printf("%d",d[x][y]);
                return 0;
            }

            for (int i = 0; i <= maxv; i++)
                if (can[i]){
                    update(i,y,x,y);
                    update(x,i,x,y);
                }

            for (int i = 0; i <= maxv; i++)
                if (can[i] && (0 <= x + (y-i) && x + (y-i) <= maxv))
                    update(x+(y-i),i,x,y);

            for (int i = 0; i <= maxv; i++)
                if (can[i] && (0 <= y + (x-i) && y + (x-i) <= maxv))
                    update(i,y+(x-i),x,y);                
        }


        printf("0\n");
    	return 0;
} 