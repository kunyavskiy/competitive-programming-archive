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

#if ( _WIN32 || __WIN32__ )
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

typedef long long ll;
typedef long double ld;


string s;
char buf[2100];
char buf2[2100];

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
    getline(cin,s);
    int t;
    sscanf(s.data(),"%d",&t);

    string exc;

    int topass = 0;

    for (int it = 0; it < t; it++){
        getline(cin,s);       
        s+= char(1);
        char c;
        if (sscanf(s.data()," throw ( %[^ )] ) %c",buf,&c) == 2){
            exc = buf;
            assert(c == 1);
        }
        else if (sscanf(s.data(), " try %c ",&c) == 1){
            assert(c == 1);
            if (exc != "")
                topass++;
        } else if ((sscanf(s.data(), " catch ( %[^ ,] , \"%[^\"]\" ) %c",buf,buf2,&c))==3){
            assert(c == 1);
            if (exc != ""){
                if (topass == 0 && buf == exc){
                   printf("%s\n",buf2);
                   return 0; 
                }
                --topass;
                topass = max(topass,0); 
            }
        } else {
          assert(sscanf(s.data()," %c",&c) == 1);
        
          if (c != 1)
            cerr << s << endl;
          assert(c == 1);
        }        
    }

    printf("Unhandled Exception\n");                                                      
    return 0;
}