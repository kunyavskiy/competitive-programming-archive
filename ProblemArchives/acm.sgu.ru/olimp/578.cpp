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

const int days[12]={31,28,31,30,31,30,31,31,30,31,30,31};
const string names[12]={"January", "February", "March", "April", "May", "June", "July",
				 "August", "September", "October", "November", "December"};


void next(int& d,int& m){
	d++;
	if (d==days[m]+1)
		m++,d=1;
}

void read(int& d,int& m){
	string s;
	scanf("%d",&d);
	cin>>s;
	for (int i=0;i<12;i++)
		if (names[i]==s)
			m=i;	
}

int main()
{                        
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int d1,m1,d2,m2;
	read(d1,m1);
	read(d2,m2);
	if (m1 > m2 || (m1==m2 && d1 > d2)){
		swap(m1,m2);
		swap(d1,d2);
	}
	int cnt = 0;
	for (;m1!=m2 || d1!=d2;cnt++)
		next(d1,m1);
	cout<<cnt<<endl;
	return 0;
}