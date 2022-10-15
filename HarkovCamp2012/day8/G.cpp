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

#define taskname "g"

const int inf = 1000000000;
const ld eps = 1e-9;
const int MAXN = 110000;

struct node{
	node *l,*r;

	int val,cnt;

	node* copy(){
		node* a = new node();
		a->l = l;
		a->r = r;
		a->val = val;
		a->cnt = cnt;
		return a;
	}

	void update(){
		cnt = 1;
		if (l) cnt += l->cnt;
		if (r) cnt += r->cnt;
	}
};


int a[MAXN];

node* build(int l,int r){
	if (l >= r)
		return 0;
	int mid = (l+r)/2;

	node* res = new node();
	res->l = build(l,mid);
	res->r = build(mid+1,r);	
	res->val = a[mid];
	res->update();
	return res;
}
int n;

node* ver[MAXN];


node* change(node* a,int cnt,int val){

	assert(a->cnt > cnt);
	a = a->copy();
	if (a->l){
		if (a->l->cnt > cnt){
			a->l = change(a->l,cnt,val);
			a->update();
			return a;
		}
		cnt -= a->l->cnt;
	}

		
	if (cnt == 0){
		a->val = val;
		return a;
	}
	cnt--;
    a->r = change(a->r,cnt,val);
	a->update();
	return a;
}

int get(node* a,int cnt){
	assert(a->cnt > cnt);
	if (a->l){
		if (a->l->cnt > cnt)
			return get(a->l,cnt);		
		cnt -= a->l->cnt;
	}

	
	if (cnt == 0)
		return a->val;	
	cnt--;      
	return get(a->r,cnt);;	
}

void print(node* v){
	if (!v)
		return;
	print(v->l);
	fprintf(stderr,"%d/%d ",v->val,v->cnt);
	print(v->r);
}

int main(){
  freopen(taskname".in","r",stdin);
  freopen(taskname".out","w",stdout);
  scanf("%d",&n);
  for (int i = 0; i < n; i++)
  	scanf("%d",&a[i]);

  ver[1] = build(0,n);
  int cnt = 1;

  int m;
  scanf("%d",&m);

  for (int i = 0; i < m; i++){
  	int a,b,c;
  	if (scanf(" create %d %d %d",&a,&b,&c) == 3){
  		ver[++cnt] = change(ver[a],b-1,c);
  	}
  	else {
  		scanf(" get %d %d",&a,&b);
  	/*	print(ver[a]);
  		cerr <<"["<<b<<"]"<<endl;
  		cerr<<endl<<endl;*/
  		printf("%d\n",get(ver[a],b-1));
  	}
  }
  return 0;
}

