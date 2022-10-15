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

#if ( _WIN32 || __WIN32__ )
	#define LLD "%I64d"
#else
	#define LLD "%lld"
#endif

using namespace std;

typedef long long int64;
typedef long double ld;


struct _node;
typedef _node* node;

struct _node{
	int c,to;
	node back;
	node next;
};

node g[2500];

node _add(int a,int b,int c){
	node temp = new _node;
	temp->to = b;
	temp->next = g[a];
	g[a] = temp;
	temp->c = c;
	return temp;		
}

void add(int a,int b,int c){
	node to,back;
	to = _add(a,b,c);
	back = _add(b,a,0);
	((to->back)=back)->back = to;
}

int n;
int used[2500],usit;
int dst[2500];

int flow(int v,int maxv,int minv){
	if (v == n-1)
		return maxv;
	if (used[v] == usit)
		return false;
	used[v] = usit;
	for (node it = g[v];it;it=it->next){
		if (it->c >= minv){
			int tmp = flow(it->to,min(maxv,it->c),minv);
			if (tmp != 0){
				it->c -= tmp;
				it->back->c += tmp;
				return tmp;
			}
		}
	}
	return 0;
}





int main(){
  #ifdef LOCAL
    freopen("order.in","r",stdin);
    freopen("order.out","w",stdout);
  #endif
	int n,m;
	scanf("%d %d",&n,&m);
	::n = n+m+2;
	int ans = 0;
	for (int i=0;i<n;i++){
		int c,b,cnt;
		scanf("%d",&c);
		add(0,i+1,c);
		ans -= c;
		scanf("%d",&cnt);
		for (int j=0;j<cnt;j++){
			scanf("%d %d",&b,&c);
			add(i+1,n+b,c);			
		}
	}
	for (int i=0;i<m;i++){
		int c;
		scanf("%d",&c);
		add(i+n+1,n+m+1,c);
	}
	

	
	for (int i = (1<<15);i>0;i>>=1){
		int tmp = 0;
		while (true){
			usit++;
			tmp = flow(0,1<<30,i);
			//cerr << tmp << endl;
			if (tmp != 0)
				ans += tmp;
			else
				break;
		}
	}
	
	cout << -ans << endl;
		
    return 0;
}