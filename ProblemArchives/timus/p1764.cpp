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

const ld eps = 1e-9;

ld a[10][4];
ld b[10];
ld x[4];
ld bx[4];

bool check(){	
	for (int i=0;i<10;i++)
		if (a[i][0]*x[0] + a[i][1]*x[1] + a[i][2]*x[2] + a[i][3]*x[3] > b[i] + eps)
			return false;
	return true;		
}

ld calc(ld* x){
	return x[0] + x[1] + x[2] + x[3];
}

void gauss(ld** a,ld* b,ld* x){
	for (int i=0;i<4;i++){
		if (abs(a[i][i]) < eps){
			for (int j=i;j<4;j++)
				if (abs(a[j][i]) > eps){
					swap(a[i],a[j]);
					swap(b[i],b[j]);
				}
		}
		if (abs(a[i][i]) < eps)
			return;
		for (int j=i+1;j<4;j++)
			a[i][j] /= a[i][i];
		b[i] /= a[i][i];
		a[i][i] = 1;
		for (int j=0;j<4;j++)
			if (j != i){
				ld coef = a[j][i];
				for (int k=i;k<4;k++)
					a[j][k] -= coef*a[i][k];
				b[j] -= coef*b[i];
			}		
	}
	for (int i=0;i<4;i++)
		x[i] = b[i];
}

void solve(int mask){
	ld** A = new ld*[4];
	ld* B = new ld[4];
	int cnt = 0;
	for (int i=0;i<10;i++)
		if (mask & (1<<i)){
			if (cnt == 4)
				return;			
			A[cnt] = new ld[4];
			memcpy(A[cnt],a[i],sizeof(ld)*4);
			B[cnt] = b[i];
			cnt++;
		}
	if (cnt != 4)
		return;		
	gauss(A,B,x);
	if (check() && calc(x) > calc(bx)){
		bx[0] = x[0];
		bx[1] = x[1];
		bx[2] = x[2];
		bx[3] = x[3];
	}
}


int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
	for (int i=0;i<6;i++)
		cin>>b[i];
	a[0][0] = a[1][0] = a[5][0] = 1;
	a[3][1] = a[4][1] = a[5][1] = 1;
	a[3][2] = a[1][2] = a[2][2] = 1;
	a[0][3] = a[4][3] = a[2][3] = 1;
	a[6][0] = a[7][1] = a[8][2] = a[9][3] = -1;
	b[6] = b[7] = b[8] = b[9] = 0;
	
	for (int i=0;i<(1<<10);i++)
		solve(i);
	cout.precision(15);
	cout << fixed << bx[0]<<" "<<bx[1]<<" "<<bx[2]<<" "<<bx[3]<<endl;
	return 0;
}