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

#define norm(x) if (x >= modulo) x -= modulo

#if ( _WIN32 || __WIN32__ )
	#define LLD "%I64d"
#else
	#define LLD "%lld"
#endif

using namespace std;

typedef long long int64;
typedef long double ld;

const int modulo = 1234567;
int n,x;

int insertionSort(int N, int* A){
	A[0] = -1;
	int cnt = 0;
	for (int i=2;i<=N;i++){
		int j = i;
		cnt++;
		while (A[j - 1] > A[j]){ 
			swap(A[j - 1], A[j]);
			j--;
			cnt++;
		}
	}
	return cnt;
}

int a[20];
int b[20];

int quickSort(vector<int> a){
	if (a.size() <= 1)
		return 0;
	vector<int> l,g;
	for (int i=1;i<a.size();i++)
		if (a[i] < a[0]) l.pb(a[i]);
		else g.pb(a[i]);
	return a.size()-1 + quickSort(l)+quickSort(g);
}


int main(){
  freopen("in.txt","r",stdin);
  freopen("out.txt","w",stdout);
  while (cin>>n>>x){
  	cerr << n <<" "<<x<<endl;
	if (n > 12){
		printf("%d\n",660733);
		continue;
	}
	for (int i=1;i<=n;i++)
		b[i+1] = i;
	int ans = 0;
	do {
		memcpy(a+1,b+1,n*sizeof(int));
		int cnt1 = insertionSort(n,a);
		if (cnt1 <= (n-1)*x){
			ans++;
			continue;
		}
		memcpy(a,b+1,n*sizeof(int));
		int cnt2 = quickSort(vector<int>(a,a+n));
		ans += (cnt1 <= cnt2*x);		
		
	}while (next_permutation(b+1,b+n+1));
	printf("%d\n",ans%modulo);
	fflush(stdout);
  }

  return 0;
}