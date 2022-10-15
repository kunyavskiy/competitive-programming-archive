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

#ifndef M_PI
	#define M_PI 3.1415926535897932384626433832795
#endif


#ifdef LOCAL
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

typedef long long ll;
typedef long double ld;

char buf[20000];

bool get(string& s){
	buf[0] = 0;
	scanf(" ");
	gets(buf);
	s="";

	for (int i = 0; buf[i]; i++)
		if (buf[i] != ' ')
			s+= buf[i];
	return s.size();
}

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  	int n;
  	scanf(" ");
  	gets(buf);
  	sscanf(buf,"%d",&n);
	string s;
	while (get(s)){

		#ifdef LOCAL
			fprintf(stdout,"%s -> ",s.data());
		#endif

		if (s.size() == n){
			int sum = 0;
			for (int i = 0; i < n; i++)
				if (s[i] == '1'){
					sum += i+1;
					sum %= n+1;
				}
			if (sum == 0)
				fprintf(stdout,"%s\n",s.data());
			else {
				assert(s[sum-1] == '1');
				s[sum - 1] = '0';
				fprintf(stdout,"%s\n",s.data());					
			}
			continue;
		}
		if (s.size() == n+1){
			int cnt = 0;
			int sum = 0;
			for (int i = 0; i < n+1; i++)
				if (s[i] == '1'){
					sum += i+1;
					sum %= n+1;
				}

			for (int j = n; j >= 0; --j){
				if (s[j] == '1'){
					if (((sum - cnt - (j+1) + 2*(n+1))% (n+1)) == 0){
						s = string(s.begin(),s.begin()+j)+string(s.begin()+j+1,s.end());
						break;
					}
					cnt++;
					continue;
				}
				if (((sum - cnt + 2*(n+1))% (n+1)) == 0){
					s = string(s.begin(),s.begin()+j)+string(s.begin()+j+1,s.end());
					break;
				}
			}

			fprintf(stdout,"%s\n",s.data());
			continue;
		}

		int cnt = 0;
		int sum = 0;
		for (int i = 0; i < n-1; i++)
			if (s[i] == '1'){
				sum += i+1;
				sum %= n+1;
			}
        
        for (int j = n-2; j >= -1; --j){
    		if (((sum + cnt + (j+2) )% (n+1)) == 0){
				s = string(s.begin(),s.begin()+j+1)+'1'+string(s.begin()+j+1,s.end());
				break;
			}

			if (((sum + cnt )% (n+1)) == 0){
				s = string(s.begin(),s.begin()+j+1)+'0'+string(s.begin()+j+1,s.end());
				break;
			}

			if (j!=-1 && s[j] == '1')
				cnt++;			
		}
        fprintf(stdout,"%s\n",s.data());
   }

   fflush(stdout);
	
	


  return 0;
}