#include <cstdio>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <list>
#include <queue>
#include <stack>
#include <deque>
#include <iterator>

#define mp make_pair
#define pb push_back
#define sqr(a) ((a) * (a))
#define zero(a) memset (a, 0, sizeof(a))
#define sz(a) (int)(a.size())

#ifdef LOCAL
	#define LLD "%I64d"
#else 
	#define LLD "%lld"
#endif

using namespace std;

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef unsigned int uint;

#define taskname "i"

const int inf = 1000000000;
const ld eps = 1e-9;


const int LST = 1<<20;
const int SZ = 2*LST+100;

int tree[SZ];
int sum[SZ];
int n,lst,m;
int a[SZ];


void update(int v){
	sum[v] = sum[2*v] + sum[2*v+1];
}

void push(int v){
	if (tree[v] == -1111)
		return;
	tree[2*v] = tree[v];
	tree[2*v+1] = tree[v];
	tree[v] = -1111;
	sum[2*v] = sum[v]/2;
	sum[2*v+1] = sum[v]/2;
}

void build(){
	lst = 2;
	while (lst < n)
		lst *= 2;
	for (int i = 1; i <= 2*lst - 1; i++)
		tree[i] = -1111;	
	for (int i = 0;i < n; i++)
		sum[lst+i] = a[i];
	for (int i = lst-1; i > 0; i--)
		update(i);
}

void upd(int v,int l,int r,int L,int R,int c){
	if (R < l || r < L)
		return;
	if (L <= l && r <= R){
		tree[v] = c;
		sum[v] = c*(r-l+1);
		return;
	}
	push(v);
	upd(2*v,l,(l+r)/2,L,R,c);
	upd(2*v+1,(l+r)/2+1,r,L,R,c);
	update(v);
}

int get(int v,int l,int r,int L,int R){
	if (R < l || r < L)
		return 0;
	if (L <= l && r <= R)
		return sum[v];	
	push(v);
	return get(2*v,l,(l+r)/2,L,R)+get(2*v+1,(l+r)/2+1,r,L,R);
}




int main(){
  freopen(taskname".in","r",stdin);
  freopen(taskname".out","w",stdout);
  scanf("%d %d",&n,&m);

  for (lst = 2; lst < n; lst *= 2);

  for (int i = 0; i < n; i++)
  	scanf("%d",&a[i]);

  build();

  for (int i = 0; i < m; i++){
//  	cerr << sum[1] <<"\n"<<sum[2]<<" "<<sum[3] <<"\n"<<sum[4] <<" "<<sum[5] <<" "<<sum[6] <<" "<<sum[7] << endl;
  	 int a,b,c;
  	 if (scanf(" ? %d %d",&a,&b) == 2){
  	 	--a,--b;
  	 	printf("%d\n",get(1,0,lst-1,a,b));
  	 }
  	 else {
  	 	scanf(" = %d %d %d",&a,&b,&c);
  	 	--a,--b;
  	 	upd(1,0,lst-1,a,b,c);
  	 }
  }






  return 0;
}

