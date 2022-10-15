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

int n,k;

char a[100000];


int main()
{                        
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
	cin>>n>>k;
	ld m=0;
	memset(a,1,sizeof(a));
	for (int i=0;i<k;i++){
		m+=n*1.0/k;
		a[(int(m+0.5))-1]=0;
	}
	for(int i=0;i<n;i++)
		printf("%d",(int)a[i]);
	printf("\n");
    return 0;
}