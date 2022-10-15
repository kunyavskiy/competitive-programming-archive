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
#include "libmeandian.h"
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

int n;
int a[110];
pair<int,int> b[110];

map<pair<pair<int,int>,pair<int,int> >,int> results;

int meandian(int a,int b,int c,int d){
	int temp[4];
	temp[0] = a,temp[1]=b,temp[2]=c,temp[3]=d;
	sort(temp,temp+4);
	pair<pair<int,int>,pair<int,int> > req = mp(mp(temp[0],temp[1]),mp(temp[2],temp[3]));
	if (results.find(req) != results.end())
		return results[req];
	//cerr << temp[0] <<" "<<temp[1] <<" "<<temp[2] <<" "<<temp[3] << endl;
	return results[req] = Meandian(temp[0]+1,temp[1]+1,temp[2]+1,temp[3]+1);
}




void srt(int* l,int* r,int a,int b,int c){	
	int n = r-l;
	for (int i=0;i<n;i++){
		int temp = meandian(l[i],a,b,c); 
		::b[i] = mp(temp,l[i]);
	}
	sort(::b,::b+n);
	for (int i=0;i<n;i++)
		l[i] = ::b[i].second;	
}

int res[110];

void get3(int& a,int& b,int& c,int x,int y){
	int AB = meandian(a,b,x,y);
	int BC = meandian(b,c,x,y);
	int AC = meandian(a,c,x,y);
	if (AB == AC)
		swap(a,c);
	else if (AB == BC)
		swap(b,c);
}

pair<int,int> getmin(int* l,int* r,int a,int b){
	int n = r-l;
	int id = l[0],id2 = l[1];
	for (int i=2;i<n;i++){
		int x = l[i];
		get3(id,id2,x,a,b);
	}	
	return mp(id,id2);
}

pair<int,int> getmax(int* l,int* r,int a,int b){
	cerr << l- ::a <<" "<<r- ::a << endl;
	int n = r-l;
	int id = l[0],id2 = l[1];
	for (int i=2;i<n;i++){
		int x = l[i];
		get3(id,id2,x,a,b);
	}	
	return mp(id,id2);
}


void getminmax(){
//	cerr << "try" << " "<<a[0] <<" "<<a[1] <<" "<<a[2]<<endl;
	srt(a+3,a+n,a[0],a[1],a[2]);	
	pair<int,int> minid,maxid;
	if (b[n-4].first == b[0].first || b[1].first != b[0].first /*|| b[n-4].first != b[n-5].first*/){
//		cerr <<"unsucsess"<<endl;
		random_shuffle(a,a+n);
		getminmax();
		return;		
	}
	minid = getmin(a+3,upper_bound(b,b+n-3,mp(b[0].first,1<<30))-b+a+3,a[0],a[1]);
	if (b[n-4].first != b[n-5].first){
		int u=a[0],x=a[1],y=a[2],z=b[n-4].second;
		get3(x,y,u,minid.second,minid.first);
		get3(x,y,z,minid.second,minid.first);
		maxid = mp(x,y);
	}
	else
		maxid = getmax(lower_bound(b,b+n-3,mp(b[n-4].first,-(1<<30)))-b+a+3,a+n,a[0],a[1]);
//	cerr << "minid :"<< minid.first <<" "<<minid.second <<endl;		
//	cerr << "maxid :"<< maxid.first <<" "<<maxid.second <<endl;	

	sort(a,a+n);
	for (int i=0;i<n;i++)
		if (a[i] == minid.first)
			swap(a[i],a[0]);
	for (int i=0;i<n;i++)
		if (a[i] == minid.second)
			swap(a[i],a[1]);
			

	for (int i=0;i<n;i++)
		if (a[i] == maxid.first)
			swap(a[i],a[n-2]);
	for (int i=0;i<n;i++)
		if (a[i] == maxid.second)
			swap(a[i],a[n-1]);			

}

int main(){
	n = Init();
	for (int i=0;i<n;i++)
		a[i] = i;
	getminmax();
	if (n == 4){
		res[0] = res[1] = res[2] = res[3] = -1;
		Solution(res);
		return 0;		
	}
	if (n == 5){
		res[a[0]] = res[a[1]] = res[a[3]] = res[a[4]] = res[a[2]] = -1;
		Solution(res);
		return 0;				
	}
	
	
//	for (int i=0;i<n;i++)
//		cerr << a[i] <<" \n"[i==n-1];
	
	res[a[2]] =  meandian(a[0],a[2],a[3],a[n-1]) + 
	 			 meandian(a[0],a[2],a[4],a[n-1]) -
				 meandian(a[0],a[3],a[4],a[n-1]);				
	for (int i=3;i<n-2;i++)
		res[a[i]] = 2*meandian(a[0],a[2],a[i],a[n-1]) - res[a[2]];
	
	res[a[0]] = res[a[1]] = res[a[n-1]] = res[a[n-2]] = -1;
	Solution(res);		
    return 0;
}