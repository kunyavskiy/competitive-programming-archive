#include <iostream>
#include <fstream>


using namespace std;

const int MAXN = 410000;
const int MAXLOG = 20;



int up[MAXN][MAXLOG];
int h[MAXN];
int n;
	
int doup(int a,int h){
	for (int i=MAXLOG-1;i>=0;i--)
		if ((1<<i)&h)
			a = up[a][i];
	return a;	
}


int lca(int a,int b){
	if (h[a] < h[b])
		swap(a,b);
	a = doup(a,h[a]-h[b]);
	if (a == b)
		return a;
	for (int i=MAXLOG-1;i>=0;--i){
		if (up[a][i] != up[b][i]){
			a = up[a][i];
			b = up[b][i];
		}			
	}
	return up[a][0];
}

void add(int p){
	//cerr << n <<" as "<<p<<"'s son"<<endl;
	up[n][0] = p;
	for (int i=1;i<MAXLOG;i++)
		up[n][i] = up[up[n][i-1]][i-1];
	h[n] = h[p]+1;
	n++;
}


void init(){
	for (int i=0;i<MAXLOG;i++)
		up[0][i] = 0;
	n = 1;		
}	


void path(int a, int b){
	add(a-1);
	for (int i=1;i<b;i++)
		add(n-1);
}

int dig(int a, int b){
	--a,--b;
	int l = lca(a,b);
	int len = h[a] + h[b] - 2 * h[l];
	int lfa = len/2;
	int lfb = len - lfa;
//	cerr << a << " "<<b<<" "<<l<<" "<<lfa<<endl;
	if (h[a] - h[l] >= lfa)
		return doup(a,lfa)+1;
	return doup(b,lfb)+1;
}
