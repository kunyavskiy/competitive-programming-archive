#include <stdio.h>
#include "snakelib.h"
#include <iostream>
//#include <cmath>


using namespace std;


#ifdef LOCAL
extern FILE* log;
#endif

int K;
char a1, a2;

int main()
{
  K = get_speed();
  
  if (K == 0){
	    int ll = 0;
	  int lr = 12122;
	  int rl = 0;
	  int rr = lr;
	  int rmax = rr;
	  for (;lr-ll > 1 || rr-rl>1;){
		char c1,c2;
		ask_snake(((ll+lr)/2),((rl+rr)/2),&c1,&c2);
		if (c1 == 'b')
			ll = (ll+lr)/2;
		else
			lr = (ll+lr)/2;
			
		if (c2 == 'f')
			rr = (rl+rr)/2;
		else
			rl = (rl+rr)/2;	
		#ifdef LOCAL
			fprintf(log,"ll = %d,lr = %d, rl = %d,rr = %d\n",ll,lr,rl,rr);
		#endif
	  }
	  tell_length(rr-ll-1);
  }
  
  
  K = max(K,1);
  int ll = 0;
  int lr = 12122/K + !!(12122/K)+1;
  int rl = 0;
  int rr = lr;
  int rmax = rr;
  for (;lr-ll > 2 || rr-rl>2;){
	char c1,c2;	
	lr = min(lr+1,rmax);
	rr = min(rr+1,rmax);
	ask_snake(((ll+lr+1)/2)*K,((rl+rr+1)/2)*K+K-1,&c1,&c2);
	if (c1 == 'b')
		ll = (ll+lr+1)/2;
	else
		lr = (ll+lr+1)/2;
		
	if (c2 == 'f')
		rr = (rl+rr+1)/2;
	else
		rl = (rl+rr+1)/2;	
	#ifdef LOCAL
		fprintf(log,"ll = %d,lr = %d, rl = %d,rr = %d\n",ll,lr,rl,rr);
	#endif
  }
  tell_length((rl*K+K-1) - ((ll+1)*K) + 1);
}
