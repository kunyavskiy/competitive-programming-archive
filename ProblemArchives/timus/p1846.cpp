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
#endif

using namespace std;

typedef long long ll;
typedef long double ld;

const int MAXN = 110000;
const int MAXLST = 1<<17;
const int MAXSZ = MAXLST*2 + 100;

int tree[MAXSZ];
int lst;

int gcd(int a,int b){
	if (!a || !b)
		return a+b;
	return gcd(b,a%b);
}

void init(int n){
	lst = 2;
	while (lst < n)
		lst *= 2;
	
	for (int i = 1; i <= 2*lst-1; i++)
		tree[i] = 0;
}

void update(int v,int val){
	v += lst - 1;
	tree[v] = val;
	for (v /= 2;v;v /= 2)
		tree[v] = gcd(tree[2*v],tree[2*v+1]);
}



int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  	int n;
	scanf("%d",&n);
	init(n);
	set<pair<int,int> > s;
	for (int i = 0; i < n; i++){
		char c;int v;
		scanf(" %c %d",&c,&v);
		if (c == '+'){
			s.insert(mp(v,i));
			update(i,v);
		}
		else {
			int pos = s.lower_bound(mp(v,-1))->second;
			s.erase(mp(v,pos));
			update(pos,0);
		}

		printf("%d\n",tree[1] + !tree[1]);    			
	}
  return 0;
}