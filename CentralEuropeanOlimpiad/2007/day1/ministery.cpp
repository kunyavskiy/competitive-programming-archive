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

const int MAXN = 1000100;

int p[MAXN];
int h[MAXN];
int d[MAXN];
int number[MAXN];
int sons[MAXN][3];
int cnt;
int q[MAXN];

int n;

inline bool cmp(int a,int b){
	if (sons[a][0] != sons[b][0])
		return sons[a][0] < sons[b][0];
	if (sons[a][1] != sons[b][1])
		return sons[a][1] < sons[b][1];
	if (sons[a][2] != sons[b][2])
		return sons[a][2] < sons[b][2];
	return false;
}

inline bool eql(int a,int b){
	return sons[a][0] == sons[b][0] && sons[a][1] == sons[b][1] && sons[a][2] == sons[b][2];
}

int ptrl = 0,ptrr=0;

void iterate(){		
	int ptrr2 = ptrr;
	for (int i=ptrl;i<ptrr;i++)
		sort(sons[q[i]],sons[q[i]]+3);
	int ocnt = cnt;
	sort(q+ptrl,q+ptrr,cmp);
	for (int i=ptrl;i<ptrr;){
		int j = i;
		for (;j<ptrr && eql(q[i],q[j]);j++);
		cnt++;
		for (;i<j;i++)
			number[q[i]] = cnt;
	}
	for (int i=ptrl;i<ptrr2;i++){
		int v= q[i];
		if (p[v] != -1){
			sons[p[v]][--d[p[v]]] = number[v];
			if (d[p[v]] == 0)
				q[ptrr++] = p[v],h[p[v]] = h[v] + 1;		
		}
	}
	ptrl = ptrr2;
	printf("%d\n",cnt-ocnt);
}

char buf[2*MAXN+100];
int st[MAXN],sptr;


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
	gets(buf);
	n = 0;
	st[0] = -1;sptr=1;
	for (int i=0;buf[i];i++){
		if (buf[i] == '('){
			p[n] = st[sptr-1];
			d[st[sptr-1]] ++;
			st[sptr++] = n++;
		}
		else{
			--sptr;
			if (d[st[sptr]] == 0)
				q[ptrr++] = st[sptr];
		}
	}
	for (;ptrl != ptrr;)
		iterate();	
	return 0;
}