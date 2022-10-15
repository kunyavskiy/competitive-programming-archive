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
	int xl,xr;
	int y;
	node l,r;
	node p;
	int under;
	_node(){
	}
	_node(int xl,int xr):xl(xl),xr(xr){
		l = r = p = 0;
		under = xr-xl+1;
		#if (RAND_MAX > (1<<17))
			y = rand();
		#else
			y = (rand()<<16) | rand();
		#endif
	}	
	void update(){
		under = xr-xl+1;
		if (l) l->p=this,under += l->under;
		if (r) r->p=this,under += r->under;
	}
};

node merge(node l,node r){
	if (!l) return r;
	if (!r) return l;
	l->p = r->p = 0;
	if (l->y > r->y){
		l->r = merge(l->r,r);
		l->update();
		return l;
	}
	r->l = merge(l,r->l);
	r->update();
	return r;
}

map<int,node> back;


void split(node v,int cnt,node &l,node& r){
	if (!v){
		assert(!cnt);
		l = r = 0;
		return;
	}
	if (cnt == 0){
		l = 0;r = v;
		return;
	}
	if (v->l){
		if (v->l->under > cnt){
			r = v;
			split(v->l,cnt,l,v->l);
			r->update();
			return;			
		}
		cnt -= v->l->under;
	}
	if (cnt == 0){
		l = v->l;
		r = v;
		v->l = 0;
		r->update();l->update();
		return;
	}
	cnt -= v->xr - v->xl + 1;
	assert(cnt >= 0);
	l = v;
	split(v->r,cnt,v->r,r);
	l->update();
	return;
}

node root;

int getat(int x){
	node v = root;
	for (;;){
		if (v->l){
			if (v->l->under > x){
				v = v->l;
				continue;
			}
			else
				x -= v->l->under;
		}
		if (v->xr - v->xl >= x)
			return v->xl + x;
		x -= v->xr - v->xl + 1;
		v = v->r;
	}
	assert(false);
}


int getnum(node x){
	int ans = 0;
	if (x->l) ans += x->l->under;
	for (;x->p;x=x->p){
		if (x->p->r == x){
			ans += x->p->xr - x->p->xl + 1;
			if (x->p->l) ans += x->p->l->under;
		}			
	}
	return ans;	
}

int getnum(int id){
	return getnum(back[id]);
}


int swaps[50000][2];
int req[50000][2];
node mem[200000];
int evs[200000];
int n,q;


node build(int l,int r){
	if (l == r)	return 0;
	if (l == r-1) return mem[l];
	return merge(build(l,(l+r)/2),build((l+r)/2,r));
}

void build(){
	int ptr = 0;
	for (int i=0;i<n;i++){
		evs[ptr++] = swaps[i][0];
		evs[ptr++] = swaps[i][1];		
	}
	for (int i=0;i<q;i++)
		if (req[i][0] == 0)
			evs[ptr++] = req[i][1];
	sort(evs,evs+ptr);
	ptr = unique(evs,evs+ptr) - evs;
//	for (int i=0;i<ptr;i++)
//		cerr << evs[i] <<" \n"[i==ptr-1];
	int ptr2 = 0;
	if (evs[0] != 1)
		mem[ptr2++] = new _node(1,evs[0]-1);
	for (int i=0;i<ptr;i++){
		mem[ptr2++] = new _node(evs[i],evs[i]);
		back[evs[i]] = mem[ptr2-1];
		if (i != ptr-1 && evs[i+1] != evs[i]+1)
			mem[ptr2++] = new _node(evs[i]+1,evs[i+1]-1);		
	}
	mem[ptr2++] = new _node(evs[ptr-1]+1,1010*1010*1010);
	root = build(0,ptr2);
}


void print(node v){
	#ifdef LOCAL
		if (!v) return;
		print(v->l);
		fprintf(stderr,"[%d %d]",v->xl,v->xr);
		print(v->r);
	#endif
}


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif	
  	scanf("%d",&n);
  	for (int i=0;i<n;i++)
  		scanf("%d %d",&swaps[i][0],&swaps[i][1]);
  	scanf("%d",&q);
  	for (int i=0;i<q;i++){
  		char c;
  		scanf(" %c %d",&c,&req[i][1]);
  		req[i][0] = c=='L';
  	}
  	build();
  	
  //	print(root);cerr << endl;
  	
  	for (int i=0;i<n;i++){
 		int id1 = getnum(swaps[i][0]);
 		int id2 = getnum(swaps[i][1]);
 	//	cerr << id1 <<" "<<id2 << endl;
 		node l,m1,m2,r;
 		if (id1 < id2){
			split(root,id2,l,r);
			split(l,id1+1,l,m2);
			split(l,id1,l,m1);
 		}
 		else {
			split(root,id1+1,l,r);
			split(l,id1,l,m2);
			split(l,id2,l,m1); 			
 		}
 		swap(m1,m2);
 		root = merge(merge(l,m1),merge(m2,r));
	  //	cerr<<swaps[i][0] <<" "<<swaps[i][1]<<" : ";print(root);cerr << endl;
  	}
  	
  	
  	
  	for (int i = 0;i<q;i++){
  		if (req[i][0] == 0)
  			printf("%d\n",getnum(req[i][1])+1);
  		else
  			printf("%d\n",getat(req[i][1]-1));
  	}
    return 0;
}