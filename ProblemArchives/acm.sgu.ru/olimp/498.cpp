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

#include "texts.h"


int a1[26];
int a2[26][26];
int a3[26][26][26];
//int a4[26][26][26][26];
int kol1,kol2,kol3;//,kol4;

int b1[26];
int b2[26][26];
int b3[26][26][26];
//int b4[26][26][26][26];

void use(const string& S,int& kol1,int& kol2,int& kol3){
	int l=S.size();
	string s="";
	for (int i=0;i<l;i++)
		if (S[i]!=' ')
			s+=S[i];
	l=s.size();
		
	for (int i=0;i<l;i++)
		a1[s[i]-'a']++,kol1++;
	
	for (int i=0;i<l-1;i++)
		a2[s[i]-'a'][s[i+1]-'a']++,kol2++;
	
	for (int i=0;i<l-2;i++)
		a3[s[i]-'a'][s[i+1]-'a'][s[i+2]-'a']++,kol3++;
}

ld sqr(ld a){
	return abs(a);
}

ld calc(const string& s){
	memset(b1,0,sizeof(b1));
	memset(b2,0,sizeof(b2));
	memset(b3,0,sizeof(b3));	
	int tkol1,tkol2,tkol3,tkol4;
	tkol1=tkol2=tkol3=tkol4=0;
	
	int l=s.size();
	for (int i=0;i<l;i++)
		b1[s[i]-'a']++,tkol1++;
	
	for (int i=0;i<l-1;i++)
		b2[s[i]-'a'][s[i+1]-'a']++,tkol2++;
	
	for (int i=0;i<l-2;i++)
		b3[s[i]-'a'][s[i+1]-'a'][s[i+2]-'a']++,tkol3++;
	
	ld res=0;
	for (int i=0;i<26;i++)
		res+=sqr(((ld)b1[i])/tkol1-((ld)a1[i])/kol1);
	
	for (int i=0;i<26;i++)
		for (int j=0;j<26;j++)
			res+=sqr(((ld)b2[i][j])/tkol2-((ld)a2[i][j])/kol2)*4;
				
	for (int i=0;i<26;i++)
		for (int j=0;j<26;j++)
			for (int k=0;k<26;k++)
				res+=sqr(((ld)b3[i][j][k])/tkol3-((ld)a3[i][j][k])/kol3)*9;



	return res;			
}

string change(string s,int p,int q){
	for (int i=0;i<s.size();i+=2)
		s[i]=((s[i]-'a'+p)%26+'a');
	for (int i=1;i<s.size();i+=2)
		s[i]=((s[i]-'a'+q)%26+'a');
	return s;
}


int main()
{                        
  freopen("input.txt","r",stdin);
  freopen("output.txt","w",stdout);
	for (int i=0;i<txtkol;i++)
		use(texts[i],kol1,kol2,kol3);
//	for (int i=0;i<26;i++)
//		cerr<<a1[i]<<endl;
	string s;
	while(cin>>s){
	int p=0,q=0;
	ld bst=calc(change(s,p,q));	
	for (int i=0;i<26;i++)
		for (int j=0;j<26;j++)
		{
			ld tmp=calc(change(s,i,j));
	//		cerr<<change(s,i,j)<<" "<<tmp<<endl;
			if (tmp<bst)
			{
				bst=tmp;
				p=i;q=j;
			}
		}	
	cout<<change(s,p,q)<<endl;
	//break;
	}
  return 0;
}