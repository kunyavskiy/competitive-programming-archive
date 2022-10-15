#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <cstring>
#include <string>
#include <cmath>
#include <cassert>
#include <ctime>
#include <algorithm>
#include <list>
#include <queue>
#include <deque>
#include <stack>
#include <cstdlib>
#include <cstdio>
#include <iterator>
#include <functional>
#include <bitset>
#define mp make_pair
#define pb push_back

#if ( _WIN32 || __WIN32__ )
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

#define TASKNAME "MINWDSUM"

typedef long long ll;
typedef long double ld;

const int MAXN = 4100000;

namespace heap {
	int arr[MAXN];
	int pos[MAXN];
	int who[MAXN];

	int n;
	int t;
                        
	inline void swap(int i,int j){
		std::swap(arr[i],arr[j]);            
		std::swap(who[i],who[j]);
		pos[who[i]] = i;
		pos[who[j]] = j;
	}

	inline void siftup(int id){
		while (id > 1 && arr[id] < arr[id/2])
			swap(id,id/2), id/=2;
	}

	inline void siftdown(int id){
		int l,r;
		while (true){
			l = id<<1;
			r = (id<<1)|1;
			if (r <= n && arr[l] > arr[r])
				std::swap(l,r);
			if (l > n || arr[id] < arr[l])
				break;
			swap(id,l);
			id = l;
		}
	}             

	void reset(int n){
		heap::n = n;
		for (int i = 1; i <= n; i++)
			pos[i-1] = i, who[i] = i-1, arr[i] = 1<<30;//mp(1<<30,1<<30);
		arr[1] = 0;//mp(0,0);            
	}

	inline void set(int id,const int& val){
		arr[pos[id]] = val;
		siftup(pos[id]);  
	}

	inline int top(){
		return who[1];
	}

	inline void pop(){
		if (n != 1)
		swap(1,n);
		n--;
		if (n != 0)
		siftdown(1);
	}

	inline bool empty(){
		return n == 0;
	}
}
                         

pair<int,int> d[MAXN];
unsigned int ans[MAXN];
bool used[MAXN];
int p[MAXN];
int W[MAXN];
int m;

void bfs(){
	queue<int> q;
	q.push(0);     
	used[0] = true;
	ans[0] = 0;
	while (!q.empty()){
		int v = q.front();
		q.pop();              
		for (int i = 0; i < 10; i++) {
			int to = (v*10+i) % m;
			if (!used[to] && mp(d[v].first + W[i],d[v].second + 1) == d[to]){
				used[to] = true;
				ans[to] = ans[v] * 3141u + (unsigned int)i;
				q.push(to);
			}
		}
	}		
}

void solve(){


	scanf("%d",&m);

	heap::reset(m);      


	for (int i = 0; i < m; i++) {
		d[i] = mp(1<<30,1<<30);
	}
	for (int i = 0; i < 10; i++)
		scanf("%d",&W[i]);

	d[0] = mp(0,0);
	ans[0] = 0;



	while (!heap::empty()){
		int v = heap::top();
		heap::pop();

		//cerr << v <<" "<<d[v].first <<" "<<d[v].second << endl;


		for (int i = 0; i < 10; i++){
			int to = (v*10+i) % m;
			if (mp(d[v].first + W[i], d[v].second + 1) < d[to]){
				d[to] = mp(d[v].first + W[i], d[v].second + 1);
				heap::set(to,d[to].first*4000+d[to].second);
			}
		}

	}

	//cerr << clock() << endl;


	for (int i = 0; i < m; i++)
		used[i] = false;
	bfs();
                        

	ll ans = 0;

	for (int i = 0; i < m; i++)
		ans += ::ans[i];

	printf(LLD"\n",ans);		
}


int main(){
  #ifdef LOCAL
    freopen(TASKNAME".in","r",stdin);
    freopen(TASKNAME".out","w",stdout);
  #endif


  int t;
  scanf("%d",&t);

  for (int i = 0; i < t; i++){
  	  solve();
  }

  cerr << clock() << endl;

      
  return 0;
}