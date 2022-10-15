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

const int MAXN = 3100;

struct edge{
	int to,c;
	edge *next,*back;
};

edge* g[MAXN];
edge* g2[MAXN];


void add(int a,int b,int c){
	edge* ab = new edge;		
	edge* ba = new edge;
	ab->to = b; ba->to = a;
	ab->c = c; ba->c = c;
	ab->next = g[a]; ba->next = g[b];
	g[a] = ab; g[b] = ba;
	ab->back = ba;ba->back = ab;	
}

int used[MAXN],useptr;
int n;
int d[MAXN];


int dfs(int v,int have){
//	cerr << v <<" "<<have << endl;
	if (v == n-1)
		return have;
	if (have == 0)
		return 0;

	int push = 0;

	for (;g2[v]; g2[v]=g2[v]->next){       
		int to = g2[v]->to;
//		cerr << to << endl;
		if (d[to] != d[v]+1)
			continue;
		int can = min(have-push,g2[v]->c);
		int rcan = dfs(to,can);
		g2[v]->c -= rcan;
		g2[v]->back->c += rcan;
		push += rcan;
		if (push == have)
			break;
	}             

	return push;
}


bool bfs(){
	for (int i = 0; i < n; i++)
		d[i] = 1<<30;
	d[0] = 0;
	queue<int> q;
	q.push(0);
	for (;!q.empty();){
		int v = q.front();
		q.pop();
		for (edge* i = g[v]; i; i = i->next)
			if (i->c && d[i->to] > d[v] + 1){
				d[i->to] = d[v]+1;
                q.push(i->to);
			}
	}
	if (d[n-1] == (1<<30))
		return false;

	for (int i = 0; i < n; i++)
		g2[i] = g[i];

//	cerr <<"!!!!!!!"<<endl;

	dfs(0,1<<30);
	return true;
}

char s[MAXN];int slen;
char t[MAXN];int tlen;


void build(){

	for (int i = 0; i < slen + tlen +1 ; i++)
		g[i] = g2[i] = 0;

	for (int i = 0; i < slen; i++)
		for (int j = 0; j < tlen; j++)
			if (s[i] == '?' && t[j] == '?' && i>=j && i - j + tlen <= slen)
				add(i + 1,j + slen + 1,1);

   
    for (int i = 0; i < slen; i++){
		if (s[i] != '?')
			continue;
		int cnt0 = 0,cnt1 = 0;
		for (int j = 0; j < tlen; j++)
			if (s[i] == '?' && i>=j && i - j + tlen <= slen){
				if (t[j] == '0')
					cnt0++;
				else if (t[j] == '1')
					cnt1++;
			}
		cnt0 -= cnt1;
		if (cnt0 > 0)
			add(0,i+1,cnt0);
		else if (cnt0 < 0)
			add(i+1,slen + tlen + 1,-cnt0);				
	}

	for (int j = 0; j < tlen; j++){
		if (t[j] != '?')
			continue;
		int cnt0 = 0,cnt1 = 0;        
		for (int i = 0; i < slen; i++)
			if (i>=j && i - j + tlen <= slen){
				if (s[i] == '0')
					cnt0++;
				else if (s[i] == '1')
					cnt1++;
			}
		cnt0 -= cnt1;
		if (cnt0 > 0)
			add(0,j+slen+1,cnt0);
		else if (cnt0 < 0)
			add(j+slen + 1,slen + tlen + 1,-cnt0);				
	}
	n = slen + tlen + 2;		
}

void color(int v){
	if (used[v] == useptr)
		return ;

	if (v > 0 && v <= slen)
		s[v-1] = '0';
	if (v > slen && v < n-1)
		t[v - slen -1] = '0';	

	used[v] = useptr;

	for (edge* i = g[v]; i; i = i->next){
		if (i->c)
			color(i->to);
	}

	return ;            
}


int calc(){
	int ans = 0;
	for (int i = 0; i + tlen <= slen; i++)
		for (int j = i; j < i+tlen; j++)
			if (t[j-i] != s[j])
				ans++;
	return ans;
}






int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  gets(s);slen = strlen(s);
  gets(t);tlen = strlen(t);
  build();
  for (useptr++;bfs();useptr++);
  ++useptr;
  color(0);
  for (int i = 0; s[i]; i++)
  	if (s[i] == '?')
  		s[i] = '1';
  for (int i = 0; t[i]; i++)
  	if (t[i] == '?')
  		t[i] = '1';

  cout << calc() << endl;
  puts(s);
  puts(t);
  return 0;
}