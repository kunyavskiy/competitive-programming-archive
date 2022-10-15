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

#define taskname "revision"

using namespace std;

typedef long long ll;
typedef long double ld;

int n, q, a, b;

int SHORT_RAND(int &x){
    return ((x = x * 214013LL + 2531011L) >> 16) & 0x7fff;
}
int RAND(int &x)
{
    return (SHORT_RAND(x) << 16) + SHORT_RAND(x);
}

void add(int,int);
void find(int,int);

void GEN()
{
    int t, t1, t2;
    for (int i = 0; i < q; i++)
    {
        t = RAND(a);
        if (t & 0x1ff)
        {
            t1 = RAND(b) % n;
            t2 = SHORT_RAND(b) % 100;
            add(t1, t2);
        }
        else
        {
            t1 = RAND(b) % n;
            t2 = t1 + RAND(b) % (n - t1);
            find(t1, t2);
        }
    }
}

const int MAXSQ = 400; 
const int MAXN = 110000;

ll sum[MAXN];
ll sumb[MAXN/MAXSQ];

void add(int a,int b){
//    cerr <<"!!!"<<a <<" "<<b<<endl;
    sum[a]+=b;
    sumb[a/MAXSQ]+=b;
}

void find(int a,int b){
    ll ans = 0;

    for (;a % MAXSQ && a <= b; a++)
        ans += sum[a];
    for (;(b % MAXSQ) != MAXSQ-1 && a <= b; b--)
        ans += sum[b];
    for (; a <= b; a+= MAXSQ)
        ans += sumb[a/MAXSQ];
    printf("%lld\n",ans);
}

int main(){
	#ifndef taskname
		#error taskname is not defined
	#else
		freopen(taskname".in","r",stdin);
		freopen(taskname".out","w",stdout);
	#endif    
    scanf("%d %d %d %d", &n, &q, &a, &b);
    GEN();
    return 0;
}
 