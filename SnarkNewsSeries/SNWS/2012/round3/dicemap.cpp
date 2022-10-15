#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <queue>
#include <deque>
#include <stack>
#include <algorithm>
#include <memory.h>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iterator>

#define mp make_pair
#define pb push_back

#ifdef LOCAL
	#define LLD "%I64d"
#else
	#define LLD "%lld"
#endif

#define taskname "dicemap"

using namespace std;

typedef long long int64;
typedef long double ld;

char buf[2100];

const int dx[4] = {1,-1,0,0};
const int dy[4] = {0,0,1,-1};


const int perm[4][6] = {
                        {1,5,2,0,4,3},
                        {3,0,2,5,4,1},
                        {4,1,0,3,5,2},
                        {2,1,5,3,0,4}
                       };

                            

int nap1,nap2;
int cnt;
int curp[6] = {0,4,1,2,3,5};

int main(){
	#ifndef taskname
		#error taskname is not defined
	#else
		freopen(taskname".in","r",stdin);
		freopen(taskname".out","w",stdout);
	#endif
        gets(buf);
        nap1 = 0,nap2 = 2;
        
        int ptr = 0;
        cnt = 1;
        int x,y;
        x = y = 0;

        for (;buf[ptr];){
            //cerr << ptr << buf[ptr] << endl;
            if (buf[ptr] == '.'){
                printf("%d %d %d\n",x,y,curp[0]+1);
                return 0;
            }
            if (buf[ptr] == '-'){
                nap1 = 1;
                nap2 = 3;
                ptr++;
                continue;
            }
            if (buf[ptr] == '+'){
                nap1 = 0;
                nap2 = 2;
                ptr++;
                continue;
            }
            if (buf[ptr] == 'X'){
                x += cnt * dx[nap1];
                cnt %= 4;
                if (dx[nap1] < 0)
                    cnt = 4-cnt;
                for (int i = 0; i < cnt; i++){
                    int temp[6];
                    for (int j = 0; j < 6; j++)
                        temp[perm[0][j]] = curp[j];
                    for (int j = 0; j < 6; j++)
                        curp[j] = temp[j];
                }
                cnt = 1;
                ptr++;
                continue;
            }
            if (buf[ptr] == 'Y'){
                y += cnt * dy[nap2];
                cnt %= 4;
                if (dy[nap2] < 0)
                    cnt = 4-cnt;
                //cerr << nap2 << endl;
                for (int i = 0; i < cnt; i++){
                    int temp[6];
                    for (int j = 0; j < 6; j++)
                        temp[perm[2][j]] = curp[j];
                    for (int j = 0; j < 6; j++)
                        curp[j] = temp[j];
                }
                cnt = 1;
                ptr++;
                continue;
            }

            sscanf(buf+ptr,"%d",&cnt);
            while ('0' <= buf[ptr] && buf[ptr] <= '9')
                ptr++;
        }


    	return 0;
} 