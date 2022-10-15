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
typedef double ld;

ld dp[105][105][10];
ld dp2[105][105][10];
int va,vb,sa,sb,m;


ld calc2(int,int,int);

ld calc(int a,int b,int c){
    if (dp[a][b][c] > -0.5)
        return dp[a][b][c];
    if (a == 0)
        return 0;
    if (b == 0)
        return 1;
        
    dp[a][b][c] = 0;
    ld temp = calc2(a-1,b,c);
    temp += calc2(a,b-1,c);
    temp -= calc2(a-1,b-1,c);
    temp -= calc2(a-sa-1,b,c);
    temp -= calc2(a,b-sb-1,c);
    temp += calc2(a-sa-1,b-sb-1,c);
    if (b <= sb)
        temp += (sa+1)*(sb-b+1);
    if (a <= sa && b <= sb){
        temp -= (sa-a+1)*(sb-b+1);
        temp += (sa-a+1)*(sb-b+1)*calc(0,0,0);
    }

    temp /= (sa+1)*(sb+1)-1;
    if (c > 0)
        dp[a][b][c] = max(calc(a/2+a%2,b/2+b%2,c-1),temp);    
    else
        dp[a][b][c] = temp;
//    cerr << a <<" "<<b<<" "<<c<<" "<<dp[a][b][c] << endl;
    return dp[a][b][c];
}

ld calc2(int a,int b,int c){
    if (a <= 0 || b <= 0)
        return 0;
    if (dp2[a][b][c] > -0.5)
        return dp2[a][b][c];
    return dp2[a][b][c] = calc2(a-1,b,c) + calc2(a,b-1,c) - calc2(a-1,b-1,c) + calc(a,b,c);
}


int main()
{
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    cin >>va >> vb >> sb >> sa >> m;

    for (int i = 0; i <= va; i++)
        for (int j = 0; j <= vb; j++)
            for (int k = 0; k <= m; k++)
                dp[i][j][k] = dp2[i][j][k] = -1+(i+j==0);


   ld temp = calc(va,vb,m);


    for (int i = 0; i <= va; i++)
        for (int j = 0; j <= vb; j++)
            for (int k = 0; k <= m; k++)
                dp[i][j][k] = dp2[i][j][k] = -1+2*(i+j==0);

   ld temp2 = calc(va,vb,m);

   temp2 -= temp;

   temp /= (1-temp2);

   cerr << temp << " "<<temp2 << endl;

   printf("%.18lf",(double)temp);


  return 0;
}