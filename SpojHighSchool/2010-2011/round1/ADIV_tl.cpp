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

typedef short int sint;

int a[110];

int t[2][1100000];


int main()
{
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
	string s;
	int n;
	cin>>s>>n;
	reverse(s.begin(),s.end());
	int st=1%n;
	assert(s.size()>20 || ((1<<s.size())>n));
	
	int cur=0;
	
	int sz=s.size();
	
	for (int i=0;i<sz;i++){
		if (s[i]=='0')
			a[i]=st;
		else{
			a[i]=n-st;	
			if (a[i]==n) a[i]=0;
			cur+=st;
		}
		if (cur>=n)	cur-=n;
		st=st*2;
		if (st>=n) st-=n;	
	//	cerr<<a[i]<<endl;
	}
	
	for (int i=0;i<n;i++)
		t[1][i]=t[0][i]=200;
	t[0][cur]=0;
	int *t1,*t2;
	t1=t[0];
	t2=t[1];
	for (int i=0;i<sz;++i){
		int tmp=a[i];
		if (tmp==0) continue;
		for (int j=0;j<n;++j){
			if (t2[tmp]>t1[j]+1)
				t2[tmp]=t1[j]+1;
			if (t2[j]>t1[j])
				t2[j]=t1[j];
			t1[j]=200;	
			++tmp;
			if (tmp>=n) tmp-=n;
		}
		swap(t1,t2);
	}
	printf("%d\n",t1[0]);	
	
	return 0;
}