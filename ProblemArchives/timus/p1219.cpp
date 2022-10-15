#ifndef LOCAL
    #pragma comment(linker, "/STACK:33554432")
#endif

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

#ifdef LOCAL
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

typedef long long ll;
typedef long double ld;


const int LEN = 1000*1000;
const int LIM1 = 40000;
const int LIM2 = 2000;
const int LIM3 = 100;


char s[LEN+10];

void randstr(){
	for (int i = 0; i < LEN; i++)
		s[i] = rand()%26+'a';	
}

int cnt[26];
int cnt2[26][26];
int cnt3[26][26][26];

bool check(){
	memset(cnt,0,sizeof(cnt));
	for (int i = 0; i < LEN; i++){
		cnt[s[i]-'a']++;
		if (cnt[s[i]-'a'] > LIM1)
			return false;
	}        
	memset(cnt2,0,sizeof(cnt2));
	for (int i = 0; i < LEN-1; i++){
		cnt2[s[i]-'a'][s[i+1]-'a']++;
		if (cnt2[s[i]-'a'][s[i+1]-'a'] > LIM2)
			return false;
	}        
	memset(cnt3,0,sizeof(cnt3));
	for (int i = 0; i < LEN-2; i++){
		cnt3[s[i]-'a'][s[i+1]-'a'][s[i+2]-'a']++;
		if (cnt3[s[i]-'a'][s[i+1]-'a'][s[i+2]-'a'] > LIM3)
			return false;
	}        
	return true;
}                             

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
	do {
		randstr();
	} while (!check());
	puts(s);
  return 0;
}