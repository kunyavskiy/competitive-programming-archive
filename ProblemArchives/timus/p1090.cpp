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


int fen[11000];
int n;
int a[11000];

int get(int r){
	int ans = 0;
	for (; r != -1; r = (r & (r+1))-1)
		ans += fen[r];
	return ans;
}

void upd(int r){
	for (;r < n; r = r | (r+1))
		fen[r]++;
}

int calc(){
	int ans = 0;
	for (int i = 0; i < n; i++)
		ans += get(a[i]-1),upd(a[i]);
	return ans;
}

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

  int best = -1;
  int id = 0;

  int k;
  scanf("%d %d",&n,&k);

  for (int i = 0; i < k; i++){
  	for (int j = 0; j < n; j++)
  		scanf("%d",&a[j]),a[j] = n-a[j];
  	memset(fen,0,sizeof(fen));
  	int temp = calc();
  	if (temp > best){
  		best = temp;
  		id = i+1;
  	}
  }

  cout << id << endl;
  return 0;
}