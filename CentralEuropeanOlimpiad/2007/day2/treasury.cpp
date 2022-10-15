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



struct tlong{
	static const int base;
	static const int baselen;
	vector<int> c;
	
	tlong(){
		c.resize(1);
		c[0] = 0;
	}
	tlong(int a){
		c.clear();
		for (;a;){
			c.pb(a%base);
			a/=base;
		}
		if (!c.size())
			c.pb(0);
	}
	
	int& back(){
		return c.back();
	}
	int back() const{
		return c.back();
	}
	int size() const{
		return c.size();
	}
	int& operator[](int a){
		return c[a];
	}
	int operator[](int a) const{
		return c[a];
	}
	void push_back(int x){
		c.pb(x);
	}
	void pop_back(){	
		c.pop_back();
	}
	void print(FILE* f){
		fprintf(f,"%d",c.back());
		for (int i=(int)c.size()-2;i>=0;--i)
			fprintf(f,"%0*d",baselen,c[i]);
		fprintf(f,"\n");				
	}
	tlong& operator+=(const tlong& r){	
		int add = 0;
		for (int i=0;i<r.size() || add;i++){
			if (i == c.size())
				c.pb(0);
			if (i < r.size())
				add += r[i];
			add += c[i];
			c[i] = add%base;
			add /= base;
		}
		return *this;
	}
	tlong& operator*=(const tlong& r);
};

const int tlong::base = 10000;
const int tlong::baselen = 4;


tlong operator+(const tlong& a,const tlong& b){
	tlong res = a;
	res += b;
	return res;
}

tlong operator*(const tlong& a,const tlong& b){
	tlong res;
	res.c.resize(a.size()+b.size()+10);
	for (int i=0;i<a.size();i++)
		for (int j=0;j<b.size();j++){
			res[i+j] += a[i]*b[j];
			for (int k=0;res[i+j+k] >= tlong::base;k++){
				res[i+j+k+1] += res[i+j+k]/tlong::base;
				res[i+j+k] %= tlong::base;
			}
		}
	for (;res.size()>1 && res.back() == 0;)
		res.pop_back();
	return res;	
}

tlong& tlong::operator*=(const tlong& b){
	*this = *this*b;
	return *this;
}



int number[1100];
int id[1100];
int ans[1100][2];
tlong cnt[1100][2];
vector<int> g[1100];
int n;
tlong suf[1100];

void solve(int v){
	
	if (g[v].size() == 0){
		ans[v][0] = ans[v][1] = 0;
		cnt[v][0] = 1;
		cnt[v][1] = 1;
		return;
	}	
		
	ans[v][0] = 0;
	for (int i=0;i<g[v].size();i++)
		ans[v][0] += ans[g[v][i]][1];
	cnt[v][0] = 1;
	for (int i=0;i<g[v].size();i++)
		cnt[v][0] *= cnt[g[v][i]][1];
	ans[v][1] = ans[v][0];
	for (int i=0;i<g[v].size();i++)
		ans[v][1] = max(ans[v][1],ans[v][0] - ans[g[v][i]][1] + ans[g[v][i]][0] + 1);
	
	suf[g[v].size()] = 1;
	for (int i = int(g[v].size())-1;i>=0;--i){
		suf[i] = suf[i+1];
		suf[i] *= cnt[g[v][i]][1];
	}		
	cnt[v][1] = 0;
	if (ans[v][1] == ans[v][0])
		cnt[v][1] = cnt[v][0];
	tlong cur = 1;
	for (int i=0;i<g[v].size();i++){
		if (ans[v][1] == ans[v][0] - ans[g[v][i]][1] + ans[g[v][i]][0] + 1)
			cnt[v][1] += cur * cnt[g[v][i]][0] * suf[i+1];
		cur *= cnt[g[v][i]][1];
	}
}

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  
  
	scanf("%d",&n);
	for (int i=0;i<n;i++){
		scanf("%d",&id[i]);
		--id[i];
		number[id[i]] = i;
		int cnt;
		scanf("%d",&cnt);
		g[i].resize(cnt);
		for (int j=0;j<cnt;j++){
			scanf("%d",&g[i][j]);
			--g[i][j];
		}
	}
	for (int i=0;i<n;i++)
		for (int j=0;j<g[i].size();j++)
			g[i][j] = number[g[i][j]];
	for (int i=n-1;i>=0;--i){
		solve(number[id[i]]);
//		cerr << ans[number[id[i]]][0] <<" "<<cnt[number[id[i]]][0] << endl;
//		cerr << ans[number[id[i]]][1] <<" "<<cnt[number[id[i]]][1] << endl;
//		cerr << endl << endl;
	}
	cout << ans[0][1] <<endl;
	cnt[0][1].print(stdout);
	return 0;
}