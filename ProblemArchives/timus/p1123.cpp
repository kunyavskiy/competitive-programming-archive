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

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
    string s;
    getline(cin,s);

    int n = s.size();

    bool ch = false;

    for (int j = n/2,i = n-j-1; i >= 0; i--,j++){
  //  	cerr << i <<" "<<j<<endl;
    	if (s[i] != s[j]){
    		if (ch)
    			s[j] = s[i];
    		else {
    			if (s[j] < s[i])
    				s[j] = s[i], ch = true;
    			else {
//    				cerr <<"!!!"<<endl;
    				for (int k = j-1;; --k){
    					if (s[k] == '9')
	    					s[k] = '0';
	    				else {
	    					s[k]++;
	    					break;
	    				}
    				}
    				ch = true;
    				j = n/2-1,i = n-n/2-1+1;
    				continue;
    			}
    		}
    	}
    }

    cout << s << endl;
    return 0;
}