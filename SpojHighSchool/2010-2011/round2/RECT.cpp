#include <iostream> 
#include <algorithm> 
#define n(a,b) if (a>b) std::swap(a,b) 
#define p printf( 
          

int main()
{
 	int X,A,C,E,Y,B,D,F;
	for (std::cin>>X;std::cin>>X>>Y>>A>>B>>C>>D>>E>>F;){			
		n(X,A);
		n(Y,B);
		n(C,E);
		n(D,F);
		n(X,C);
		n(Y,D);
		n(A,E);
		n(B,F);
		if (C > A | D > B)
			p"nothing");
		else if (C == A & D == B)
			p"point");
		else if (C < A & D < B)
			p"rectangle");
		else 
			p"line");
		p"\n");	
	}
}
