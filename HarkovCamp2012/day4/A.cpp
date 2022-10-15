#include <cstdio>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <list>
#include <queue>
#include <stack>
#include <deque>
#include <iterator>

#define mp make_pair
#define pb push_back
#define sqr(a) ((a) * (a))
#define zero(a) memset (a, 0, sizeof(a))
#define sz(a) (int)(a.size())

#ifdef LOCAL
	#define LLD "%I64d"
#else 
	#define LLD "%lld"
#endif

using namespace std;

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef unsigned int uint;

#define taskname "a"

const int inf = 1000000000;
const ld eps = 1e-9;

const int MAXN = 2100;

int t[2100];
int l[2100];
int n,K;

ll dp1[2100][2100];
ll dp2[2100][2100];
ll dp3[2100][2100];
ll sum[2100];
ll pos[2100];

void update(int r,int cnt,int prev){
	if (dp1[r][cnt] > dp1[prev][cnt-1] + dp3[prev][r]){
		//cerr <<"!!!"<<r<<" "<<cnt << " "<<prev<<" : "<<dp3[prev][r]<<endl;
		dp1[r][cnt] = dp1[prev][cnt-1] + dp3[prev][r];
		dp2[r][cnt] = prev;
	}
}

ll dist(int l,int r){
	return abs(pos[r] - pos[l]);
}

ll sumcost(int l,int r){
	return sum[r] - (l?sum[l-1]:0);
}

void gen(int n,int k){
	if (k == 0)
		return;
	gen(dp2[n][k],k-1);
	if (n != ::n-1)
		printf("%d ",n+1);	
}

int main(){
  freopen(taskname".in","r",stdin);
  freopen(taskname".out","w",stdout);
  scanf("%d %d",&n,&K);
  scanf("%d",&t[0]);
  sum[0] = t[0];
  for (int i = 1; i < n; i++){
  	scanf("%d %d",&l[i],&t[i]);
  	sum[i] = sum[i-1] + t[i];
  	pos[i] = pos[i-1] + l[i];	
  }
  l[n] = 1000000000;
  t[n] = 1000000000;
  sum[n] = sum[n-1] + l[n-1];
  pos[n] = pos[n-1] + l[n];
  n++,K++;


  for (int i = 0; i < n; i++){
  	 int k = 0;
  	 ll sum = 0;
  	 for (int j = i+1; j < n; j++){
		sum += l[j]*1LL*sumcost(k,j-1);
		while (dist(i,k) < dist(j,k)){
			sum += dist(i,k)*t[k];
			sum -= dist(j,k)*t[k];
			k++;
		}
		dp3[i][j] = sum;
  	 }

  }

  for (int i = 0; i < n; i++)
  	for (int j = 2; j <= n; j++)
  		dp1[i][j] = (1LL<<60);

  memset(dp2,-1,sizeof(dp2));

  for (int i = 0; i < n; i++)  
  	for (int j = 0; j < i; j++){
  		dp1[i][1] += dist(i,j)*t[j];
  		dp2[i][1] = 0;
  	}

  for (int i = 0; i < n; i++)
  	for (int j = i+1; j >= 2; j--){

  		int L = (i?dp2[i-1][j]:0);
  		int R = ((j<=i)?dp2[i][j+1]:(i-1));
  		L = max(L,0);
		//int L = 0;
		//int R = i-1;
  		//cerr << i <<" "<<j<<" "<<L <<" "<<R<<endl;
  		for (int prev = L;prev <= R; prev++)
  			update(i,j,prev);  			
  	}

  cout << dp1[n-1][K] << endl;
  gen(n-1,K);  
  return 0;
}

