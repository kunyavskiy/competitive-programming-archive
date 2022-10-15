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

const int MAXN = 110000;




struct funcs{

	/*vector<int64> a;
	vector<int64> b;	
	bool bad;*/
	
	struct _node;
	typedef _node* node;
	
	vector<node> deleted;
	vector<int> deletedl;
	vector<int> deletedr;
	
	struct _node{
		int64 a,b;
		int xl,xr;
		int y;
		node l,r;
		_node(){
			a=b=xl=xr=0;
			y = rand();
			l=r=0;
		}
		_node(int64 a,int64 b):a(a),b(b){
			xl = xr = 0;
			y = rand()|(rand()<<16);
			l=r=0;
		}
		node right(){
			node tmp = this;
			for (;tmp->r;tmp=tmp->r);
			return tmp;
		}	
		node left(){
			node tmp = this;
			for (;tmp->l;tmp=tmp->l);
			return tmp;
		}	
	};
	
	node root;
	
	node merge(node l,node r){
		if (!l) return r;
		if (!r) return l;
		if (l->y > r->y){
			l->r = merge(l->r,r);
			return l;
		}
		r->l = merge(l,r->l);
		return r;
	}
	
	void splita(node v,int64 a,node& l,node & r){
		if (!v){
			l=r=0;
			return;
		}
		if (v->a >= a){
			l = v;
			splita(v->r,a,v->r,r);
			return;
		}
		r=v;
		splita(v->l,a,l,v->l);
		return;
	}
	
	void splitr(node v,int64 a,int64 b,node& l,node& r){
		if (!v){
			l=r=0;
			deletedr.pb(1<<30);
			return;
		}
		if (v->a*1LL*v->xr + v->b < a*1LL*v->xr + b){
			l = v;
			splitr(v->r,a,b,v->r,r);
			return;
		}
		if (v->a*1LL*v->xl + v->b > a*1LL*v->xl + b){
			r = v;
			splitr(v->l,a,b,l,v->l);
			return;
		}
		assert(b >= v->b);
		assert(a < v->a);
		deletedr.pb(v->xr);
		v->xr = (b - v->b)/(v->a - a);
		r = v->r;
		v->r = 0;
		l = v;
		return;
	}
	
	void splitl(node v,int64 a,int64 b,node& l,node& r){
		if (!v){
			l=r=0;
			deletedl.pb(0);
			return;
		}	
		if (v->a*1LL*v->xr + v->b > a*1LL*v->xr + b){
			l = v;
			splitl(v->r,a,b,v->r,r);
			return;
		}	
		if (v->a*1LL*v->xl + v->b < a*1LL*v->xl + b){
			r = v;
			splitl(v->l,a,b,l,v->l);
			return;
		}
		assert (b <= v->b);
		assert (a > v->a);
		deletedl.pb(v->xl);
		v->xl = (v->b - b)/(a - v->a);
		if (v->xl*(a-v->a) < v->b - b)
			v->xl++;
		r = v->r;
		v->r = 0;
		l = v;
		return;
	}
	
	node findx(int64 x){
		node v = root;
		while (v->xl > x || v->xr < x){
			if (v->xl > x)
				v = v->l;
			else
				v = v->r;
			assert(v);
		}
		return v;
	}
	
	void print(node root){
		if (!root)
			return;
		print(root->l);
		fprintf(stderr,"([%d,%d],a="LLD")",root->xl,root->xr,root->a);
		print(root->r);
	}
	
	
	int64 get(int64 x){
		/*if (bad){
			int64 val=1LL<<60LL;
			for (int i=0;i<(int)a.size();i++)
				val = min(val,a[i]*1LL*x+b[i]);
			return val;
		}
		else{*/
			node v = findx(x);
			return v->a*1LL*x+v->b;
//		}
	}	
	
	void add(int64 a,int64 b){
	/*	this->a.pb(a);
		this->b.pb(b);
		if (!bad){*/
			node l,r,m1,m2,m;
			m = new _node(a,b);
			splita(root,a,l,r);
			splitr(l,a,b,l,m1);
			splitl(r,a,b,m2,r);
			deleted.pb(merge(m1,m2));
			m->xl = (l?l->right()->xr+1:0);
			m->xr = (r?r->left()->xl-1:(1<<30));
			root = merge(merge(l,m),r);
		//}
	}
	
	void erase(int64 a,int64 b){
/*		assert(this->a.back() == a);
		assert(this->b.back() == b);
		this->a.pop_back();
		this->b.pop_back();
		bad = true;*/      		
		node l,r,m,dv;
		m = new _node(a,b);		
		m = deleted.back();
		deleted.pop_back();
		splita(root,a,l,r);
		splita(l,a+1,l,dv);
		if (l) l->right()->xr = deletedr.back();
		if (r) r->left()->xl = deletedl.back();		
		deletedr.pop_back();
		deletedl.pop_back();				
		root = merge(merge(l,m),r);	
		if (root){
			root->left()->xl = 0;
			root->right()->xr = 1<<30;
		}
	}
	
	funcs(){
	//    cerr << sizeof(_node) << endl;
	//	bad = false;
		root = 0;
	}
		
} lst;

vector<int> g[MAXN];
vector<int> l[MAXN];
int p[MAXN];
int h[MAXN];
int64 answer[MAXN];
int v[MAXN];
int s[MAXN];
int n;

vector<int> order;


void dfs1(int v){
	if (!v || g[v].size() >1){
		order.pb(v);
		for (int i=0;i<g[v].size();i++)
			if (g[v][i] != p[v]){
				p[g[v][i]] = v;
				h[g[v][i]] = h[v] + l[v][i];
				dfs1(g[v][i]);	
			}
		order.pb(-v);
	}
}

inline void solve(int v){
	if (!v){
		answer[v] = 0;
		::v[v] = 0;
	}
	else
		answer[v] = s[v]+::v[v]*1LL*h[v] + lst.get(::v[v]);
	lst.add(-h[v],answer[v]);		
}

inline void erase(int v){
	lst.erase(-h[v],answer[v]);
}






int main(){
    freopen("harbingers.in","r",stdin);
    freopen("harbingers.out","w",stdout);
    scanf("%d",&n);
    for (int i=0;i<n-1;i++){
    	int a,b,c;
    	scanf("%d %d %d",&a,&b,&c);
    	--a,--b;
    	g[a].pb(b);
    	g[b].pb(a);
    	l[a].pb(c);
    	l[b].pb(c);
    }
    for (int i=1;i<n;i++){
    	int a,b;
    	scanf("%d %d",&a,&b);
    	s[i] = a;
    	v[i] = b;
    }
    
    	
    dfs1(0);
    for (int i=0;i+1<order.size();i++){
    	if (order[i] >= 0){
    	//	cerr<<"ADD"<<i<<endl;
    		solve(order[i]);    	
    	}
    	else {
    		erase(-order[i]);    	
    	//	cerr<<"ERASE"<<i<<endl;
    	}
    //	lst.print(lst.root);
    //	cerr << endl;
    }
    for (int i=1;i<n;i++)
    	cout << answer[i] <<" \n"[i==n-1];
	return 0;
}