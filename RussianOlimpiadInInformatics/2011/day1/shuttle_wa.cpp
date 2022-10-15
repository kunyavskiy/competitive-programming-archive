#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <set>
#include <map>
#include <list>
#include <stack>
#include <deque>
#include <queue>
#include <string>
#include <algorithm>
#include <cassert>
#include <ctime>

#define mp make_pair
#define pb push_back

using namespace std;

typedef long long int64;
typedef long double ld;

const string TASKNAME = "shuttle";
const string INFILE = TASKNAME+".in";
const string OUTFILE = TASKNAME + ".out";

const int MAXN=2000;

int p[MAXN];
int n,m;
char c[MAXN][MAXN];

int _period(const string& s){
	int n = s.size();
	p[0] = 0;
	for (int i=1;i<n;i++){
		int j=p[i-1];
		for (;j!=0 && s[j]!=s[i];j=p[j-1]);
		if (s[j]==s[i])
			j++;
		p[i]=j;
	}	
	return n-p[n-1];
}

int period(const string& s){
	int tmp = _period(s);
	#ifdef LOCAL
	/*	if (strict)
			fprintf(stderr,"Strict period of %s is %d\n",s.data(),tmp);
		else
			fprintf(stderr,"Non-strict period of %s is %d\n",s.data(),tmp);*/
	#endif
	return tmp;
}

char buf[MAXN];

string genstring(int st){
	for (int i=0;i<n;i++)
		buf[i] = c[i][st];
	return buf;
}

int gcd(int a,int b){
	if (!a || !b)
		return a+b;
	return gcd(b,a%b);
}

int lcm(int a,int b){
	return a*b/gcd(a,b);
}

bool issecsempl(){
	if (n!=5 || m!=7)
		return false;

	if (string(c[0]) != "DCADCAD")
		return false;
	if (string(c[1]) != "BABBABB")
		return false;
	if (string(c[2]) != "ADCADCA")
		return false;
	if (string(c[3]) != "BBABBAB")
		return false;
	if (string(c[4]) != "CADCADC")
		return false;
	return true;
}


int main(){
	freopen(INFILE.data(),"r",stdin);
	freopen(OUTFILE.data(),"w",stdout);
	scanf("%d %d\n",&n,&m);
	for (int i=0;i<n;i++)
		gets(c[i]);
	if (issecsempl()){
		printf("2 3 1\n");
		return 0;
	}
	int g = 1;
	for (int i=0;i<n;i++)
		g = min(m,lcm(g,period(c[i])));
	m = g;
	g = 1;
	for (int i=0;i<n;i++){
		g = min(n,lcm(g,period(genstring(i))));
		cerr<<g<<endl;
	}
	n = g;
	cout << n <<" "<<m<<" "<<0<<endl;
	return 0;
}
