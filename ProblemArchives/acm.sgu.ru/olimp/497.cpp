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
#define int64 long long
#define ld long double  
#define setval(a,v) memset(a,v,sizeof(a))
using namespace std;

int b[200000];
int a[200000];

int main()
{                        
  freopen("input.txt","r",stdin);
  freopen("output.txt","w",stdout);
	int n;
	scanf("%d",&n);
	for (int i=0;i<n;i++)
		scanf("%d",&b[i]);
	if (n%3!=0){
		a[0]=0;
		int ptr=0;
		for (int i=0;i<n;i++){
			a[(ptr+3)%n]=a[ptr]-b[(ptr+1)%n]+b[(ptr+2)%n];
			ptr+=3;
			ptr%=n;
		}
//		cerr<<a[0]<<" "<<a[1]<<" "<<a[2]<<" "<<a[3]<<endl;
		int tmp=b[1]-a[0]-a[1]-a[2];
		assert(tmp%3==0);
		tmp/=3;
		for (int i=0;i<n;i++)
			a[i]+=tmp;	
	}
	else {
		a[0]=0;
		int tmp=1;
		for (int i=0;i<n-3;i+=3){
			a[i+3]=a[i]-b[(i+1)%n]+b[(i+2)%n];
			tmp=max(tmp,-a[i+3]+1);
		}
		for (int i=0;i<n;i+=3)
			a[i]+=tmp;
			
	//	cerr<<a[0]<<" "<<a[3]<<" "<<a[6]<<endl;
			

		a[1]=0;
		tmp=1;
		for (int i=1;i<n-3;i+=3){
			a[i+3]=a[i]-b[i+1]+b[i+2];
			tmp=max(tmp,-a[i+3]+1);
		}
		for (int i=1;i<n;i+=3)
			a[i]+=tmp;
			
//		cerr<<a[1]<<" "<<a[4]<<" "<<a[7]<<endl;

		a[2]=0;
		for (int i=2;i<n;i+=3)
			a[i+3]=a[i]-b[(i+1)%n]+b[(i+2)%n];
		tmp=b[1]-a[0]-a[1]-a[2];
				
		for (int i=2;i<n;i+=3)
			a[i]+=tmp;			
	}
	for (int i=0;i<n;i++)
		printf("%d\n",a[i]);
  return 0;
}