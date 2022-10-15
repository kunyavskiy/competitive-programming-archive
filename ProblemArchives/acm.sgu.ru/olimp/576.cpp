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

int64 t[100];

string s;
int L,R;

bool glasn(char c){
	return c=='a' || c=='o' || c=='e' || c=='u' || c=='i';
}

bool check(int l,int r){
	if (r-l<L || r-l>R)
		return false;
	int cnt1,cnt2;
	cnt1=cnt2=0;
	for (int i=l;i<r;i++){
		if (glasn(s[i]))
			cnt1++,cnt2=0;
		else
			cnt2++,cnt1=0;
		if (cnt1 == 3 || cnt2==4)
			return false;
	}
	return true;
}





int main()
{                        
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int n;
	cin>>n>>L>>R>>s;
	t[0]=1;
	for (int i=1;i<=n;i++){
		for (int j=0;j<i;j++)
			t[i]+=check(j,i)*t[j];		
	}
	cout<<t[n]<<endl;
	return 0;
}