#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <memory.h>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>

#define cnt cnt_bjkdsd
#define pb push_back
#define mp make_pair
using namespace std;

typedef long double ld;

namespace flow{

const int MAXN = 10000;

struct node{
    int to;
    double f,c;
    node *next,*back;
};

node* g[MAXN];
node* g2[MAXN];
bool used[MAXN];
int n,m;

int T,S;

void add(int a,int b,double c){
    node *temp = new node, *temp2 = new node;
    temp->to = b, temp2->to = a;
    temp->c = c, temp2->c = 0;
    temp->f = 0, temp2->f = 0;
    temp->next = g[a], temp2->next = g[b];
    temp->back = temp2, temp2->back = temp;
    g[a] = temp, g[b] = temp2;
}

int d[MAXN];

const ld eps = 1e-10;

double dfs(int v,double have){
    if (v == T)
        return have;
    ld pushed = 0;
    for (node * &it = g2[v]; it; it = it->next){
        if (d[it->to] != d[v] + 1)
            continue;
        double res = dfs(it->to,min(have,it->c));
        if (res > eps){
            it->c -= res, it->f += res;
            it->back->c += res, it->back->f -= res;
            if (v)
                have -= res;
            pushed += res;
        }
        if (have < eps)
            return pushed;
    }
    return pushed;
}

ld res;

bool bfs(){
    memset(d,63,sizeof(d));
    d[0] = 0;
    queue<int> q;
    q.push(0);
    for (; !q.empty(); ){
        int v = q.front();
        q.pop();
        for (node* it = g[v]; it; it = it->next){
            if (it->c > eps && d[it->to] > d[v] + 1){
                d[it->to] = d[v] + 1;
                q.push(it->to);
            }
        }
    }

    if (d[T] > n)
        return false;
    memcpy(g2,g,sizeof(g));
    res += dfs(S,2e9);
    return true;
}

double flow(){
    while (bfs());
    return res;
}

}


class EllysDeathStars {

struct point{
	int x,y;
	void read(string s){
		stringstream str(s);
		str >> x >> y;
	}
};

struct ship{
	int x1,y1;
	int x2,y2;
	int sp,r;
	
	int e;
	
	int id;
	
	void read(string s){
		stringstream str(s);
		str >> x1 >> y1 >> x2 >> y1 >> sp >> r >> e;
	}
	
};

int cnt;

void gett(point& a,ship& b,vector<pair<double,int> >& t){
	ld l = 0;
	ld r = dist(b.x1,b.y1,b.x2,b.y2)/b.v;
	
	for (int i = 0; i < 100; i++){
		ld x1 = l + (r-l)/3;
		ld x2 = r - (r-l)/3;
		ld f1 = dist(a.x,a.y,b.x1 + (b.x2-b.x1)/v.v*x1,b.y1 + (b.y2-b.y1)/v.v*x1);
		ld f2 = dist(a.x,a.y,b.x1 + (b.x2-b.x1)/v.v*x2,b.y1 + (b.y2-b.y1)/v.v*x2); 
		
		if (f1 < f2)
			r = x2;
		else
			l = x1; 
	}
	
}

public:
    double getMax(vector <string> stars, vector <string> ships) {
        flow::S = 0;
        flow::T = 1;
        cnt = 2;
        
        int n = stars.size(), m = ships.size();
        vector<point> ds(n);
        vector<ship> ss(m);
        
        for (int i = 0; i < n; i++)
            ds[i].read(stars[i]);
            
        for (int j = 0; j < m; j++){
            ss[j].read(ships[j]);
            ss[j].id = cnt++;
            flow::add(flow::S, ss[j].id,ss[j].e);
        }
        
        for (int i = 0; i < n; i++){
            vector<pair<ld,int> > ts;
            
            ts.pb(mp(0.0,0));
            
            for (int j = 0; j < m; j++)
                gett(ds[i],ss[j],ts);
                
            sort(ts.begin(),ts.end());
            
            flow::add(cnt++,flow::T,1e9);
            
            int mask = 0;
            
            int mid = cnt-1;
            
            for (int i = 1; i < ts.size(); i++){
            	flow::add(cnt++,mid,ts[i].first - ts[i-1].first);
            	for (int j = 0; j < m; j++)
            		if (mask & (1<<j))
            			flow::add(ss[j].id,cnt-1,1e9);
            	if (ts[i].second > 0)
            		mask |= (1<<(ts[i].second - 1));
            	else if (ts[i].second < 0)
            		mask &= ~(1<<(-ts[i].second -1));
            }
        }
                    
        
        return flow::flow();
    }
};
