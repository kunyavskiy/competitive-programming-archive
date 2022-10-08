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



vector<int> intersec(const vector<int>& a,const vector<int>& b){
	int sz1=a.size(),sz2=b.size(),ptr1,ptr2;
	ptr1=ptr2=0;
	vector<int> res;
	for (;;){
		if (ptr1 == sz1 || ptr2==sz2)
			return res;
		if (a[ptr1] == b[ptr2]){
			res.pb(a[ptr1]);
			++ptr1;++ptr2;
		}
		else if (a[ptr1]<b[ptr2])
			++ptr1;
		else
			++ptr2;
	}	
}

vector<int> del(const vector<int>& a,const vector<int>& b){
	vector<int> res;
	for (int i=0;i<a.size();i++)
		if (!binary_search(b.begin(),b.end(),a[i]))
			res.pb(a[i]);
	return res;
}

vector<int> a[300*300];

void print(const vector<int>& a){
	printf("%d",(int)a.size());
	for (int i=0;i<a.size();i++)
		printf(" %d",a[i]);
	printf("\n");
}



int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  	int n;
	cin>>n;
	int m = n*(n-1)/2;
	for (int i=0;i<m;i++){
		int k;
		scanf("%d",&k);
		a[i].resize(k);
		for (int j=0;j<k;j++)
			scanf("%d",&a[i][j]);
		sort(a[i].begin(),a[i].end());
	}
	vector<int> f;
	for (int i=1;i<m;i++){
		f = intersec(a[0],a[i]);
		if (f.size() != 0)
			break;
	}
	print(f);
	for (int i=0;i<m;i++){
		vector<int> tmp = del(a[i],f);
		if (tmp != a[i])
			print(tmp);
	}
	return 0;
}