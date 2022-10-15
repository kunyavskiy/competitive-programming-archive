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

#define prev fddsgfdhgfgmk_prev

#ifndef M_PI
	#define M_PI 3.1415926535897932384626433832795
#endif


#ifdef LOCAL
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

typedef long long ll;
typedef long double ld;

int a[510][510];
ll  d[510][510];
int p[510][510];

int prev[510][510];
bool used[510];


void print(int a,int b){
	if (a == 0){
		printf("%d ",b+1);
		return;
	}
	if (prev[a][b] == b)
		print(a-1,b);
	else
		print(a,prev[a][b]);
	printf("%d ",b+1);
}

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

  int n,m;
  scanf("%d %d",&n,&m);

  for (int i = 0; i < n; i++)
  	 for (int j = 0; j < m; j++)
  	 	scanf("%d",&a[i][j]);

  for (int i = 0; i < m; i++)
  	d[0][i] = a[0][i];

  for (int i = 1; i < n; i++){
  	for (int j = 0; j < m; j++)
  		d[i][j] = d[i-1][j] + a[i][j], prev[i][j] = j, used[j] = 0;

  	bool upd = true;
  	while (upd){
  		upd = false;
  		for (int j = 0; j < m-1; j++){
  			if (d[i][j] + a[i][j+1] < d[i][j+1]){
  				d[i][j+1] = d[i][j] + a[i][j+1];
  				upd = true;
  				prev[i][j+1] = j;
  			}
  		}
  		for (int j = m-1; j > 0; j--){
  			if (d[i][j] + a[i][j-1] < d[i][j-1]){
  				d[i][j-1] = d[i][j] + a[i][j-1];
  				upd = true;
  				prev[i][j-1] = j;
  			}
  		}
  	}
  }

  print(n-1,min_element(d[n-1],d[n-1]+m) - d[n-1]);
  printf("\n");
  return 0;
}