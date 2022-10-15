#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <cstdlib>
#include <cstdio>
#include <stack>
#include <algorithm>
#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <iterator>
#include <functional>
#include <bitset>
#include <ctime>
#include <cassert>
#define pb push_back
#define mp make_pair      
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
using namespace std;
 
typedef long long ll;
typedef long double ld;


const int MAXN = 110000;

struct _node;
typedef _node* node;

struct _node{
    static node null;
    node l,r,p;
    int size;
	ll coef, addcoef;
    ll val, sumvals;
    ll sum;
    bool rev;
    node pp;
    _node(){
        l = r = p = pp = _node::null;
        size = 1;
        rev = 0;
        val = sumvals = 0;
        coef = val = addcoef = sum = 0;
    }
    _node(void*){
        l = r = p = pp = this;
        size = rev = 0;
        val = sumvals = 0;
    }
    void add(ll toadd) {
    	if (this == null) return;
    	addcoef += toadd;
    	coef += toadd;
    	sum += sumvals * toadd;
    }
    void push(){
        if (rev){
            l->rev ^= 1;
            r->rev ^= 1;
            rev = 0;
            swap(l,r);
        }
        l->add(addcoef);
        r->add(addcoef);
        addcoef = 0;
    }
    void update(){
        size = (this != null) + l->size + r->size;
        l->p = r->p = this;
        push();
        sumvals = val + l->sumvals + r->sumvals;
        sum = val * coef + l->sum + r->sum;
    }
};
                                    
node _node::null = new _node(NULL);
node v2n[MAXN];

void rotate(node v){
    node u = v->p;    
    if (v == u->l){
       u->l = v->r;
       v->r = u; 
    }
    else {
       u->r = v->l;
       v->l = u; 
    }          
    swap(u->p,v->p);
    swap(v->pp,u->pp);
    if (v->p != _node::null){
        if (v->p->r == u)
            v->p->r = v;
        else
            v->p->l = v;
    }                   
    u->update();
    v->update();
}

void bigRotate(node v){
    v->p->p->push();
    v->p->push();
    v->push();
    if (v->p->p == _node::null)
        rotate(v);
    else if ((v->p->l == v) ^ (v->p->p->r == v->p))
        rotate(v->p), rotate(v);
    else
        rotate(v), rotate(v);
}

inline void Splay(node v){
     while (v->p != _node::null)
        bigRotate(v);
}

inline void splitAfter(node v){
    v->push();
    Splay(v);
    v->r->p = _node::null;
    v->r->pp = v;
    v->r = _node::null;
    v->update();
}

void expose(int x){
   node v = v2n[x];
   splitAfter(v);
   while (v->pp != _node::null){
       splitAfter(v->pp);
       v->pp->r = v;
       v->pp->update();
       v = v->pp;
       v->r->pp = _node::null;        
   }
   Splay(v2n[x]);
}

inline void makeRoot(int x){
    expose(x);
    v2n[x]->rev ^= 1;
}

inline void link(int x,int y){
    makeRoot(x);
    makeRoot(y);
    v2n[x]->pp = v2n[y];
}


class TreeColoring {

int curValue;

int genNextRandom() {
    curValue = (curValue * 1999 + 17) % 1000003;
    return curValue;
}

vector<int> distance;
vector<int> parent;
vector<int> queryType;
vector<int> queryNode;


public:
    ll color(int N, int Q, int startSeed, int threshold, int maxDist) {
    	distance = vector<int>(N-1);
    	parent = vector<int>(N-1);
    	queryType = vector<int>(Q);
    	queryNode = vector<int>(Q);
    	curValue = startSeed;
        for (int i = 0; i < N-1; i++) {
            distance[i] = genNextRandom() % maxDist;
        	parent[i] = genNextRandom();
            if (parent[i] < threshold) {
                parent[i] = i;
            } else {
                parent[i] = parent[i] % (i + 1);
            }
        }

        for (int i = 0; i < Q; i++) {
            queryType[i] = genNextRandom() % 2 + 1;
            queryNode[i] = genNextRandom() % N;
//            eprintf("%d %d\n", queryType[i], queryNode[i]);
        }

        for (int i = 0; i < N; i++) {
        	v2n[i] = new _node();
        	v2n[i]->val = i ? distance[i-1] : 0;
        }

        for (int i = 0; i < N-1; i++) {
        	link(i+1, parent[i]);
//        	eprintf("!%d %d\n", parent[i], distance[i]);
        }
        makeRoot(0);

        ll totBlueH = 0;
        ll bluecnt = 0;
		vector<bool> blue(N);

		ll res = 0;

        for (int i = 0; i < Q; i++){
        	int v = queryNode[i];
        	if (queryType[i] == 1) {
        		if (blue[v]) continue;
        		expose(v);
        		v2n[v]->add(1);
        		totBlueH += v2n[v]->sumvals;
//        		eprintf("height[%d] = %I64d\n", v, v2n[v]->sumvals);
        		bluecnt++;
        		blue[v] = true;
        	} else {
        		expose(v);
        		ll ans = totBlueH + bluecnt * v2n[v]->sumvals;
//        		eprintf("%I64d %I64d %I64d\n", totBlueH, bluecnt, v2n[v]->sumvals);
        		ans -= 2*v2n[v]->sum;
//        		eprintf("Common = %I64d\n", v2n[v]->sum);
//        		eprintf("ans = %I64d\n", ans);
        		res ^= ans;
        	}
        }

        return res;
        
    }
};
