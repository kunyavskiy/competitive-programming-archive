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

const int iters = 50;

int a[110][110];
ld x[110];
int n;

int main(){
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
	cin>>n;
	for (int i=0;i<n;i++)
		for (int j=0;j<n;j++)
			cin>>a[i][j];
			
	for (int i=0;i<n;i++)
		x[i] = 1.0;

	for (int I=0;I<iters;I++){
		for (int i=0;i<n;i++){
			x[i] = 1;
			for (int j=0;j<n;j++)
				if (i!=j)
					x[i] -= a[i][j]*x[j];
			x[i]/=1000;
		}
	}	
	ld sum = 0;
	for (int i=0;i<n;i++)
		sum += x[i];
	for (int i=0;i<n;i++)
		x[i] /= sum;
		
		
	cout.precision(15);
	for (int i=0;i<n;i++)
		cout << fixed << x[i] << endl;
	return 0;
}