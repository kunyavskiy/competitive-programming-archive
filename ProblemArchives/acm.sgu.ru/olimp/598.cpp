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

int main()
{                        
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
	int n,sum;
	sum=0;
	cin>>n;
	for (int i=0;i<n;i++){
		int a;
		cin>>a;
		sum+=a;
	}
	int best=1,bestf=1<<30;
	for (int i=1;i<n;i++){
		int curf=abs(sum-(i*5+(n-i)*10));
		if (curf < bestf){
			best=i;
			bestf=curf;
		}
	}
	for (int i=0;i<best;i++)
		cout<<5<<" ";
	for (int i=best;i<n;i++)
		cout<<10<<" \n"[i==n-1];
    return 0;
}