#include <iostream>

using namespace std;



int main(){
	FILE* inp=fopen("tests.txt","r");
	FILE* oup;
	for (int i=0;i<20;i++){
		string s="tests\\test";
		if (i/10)
			s+=(i/10+'0');
		s+=(i%10+'0');
		s+=".in";
		oup=fopen(s.data(),"w");
		int a;
		fscanf(inp,"%d",&a);
		fprintf(oup,"%d ",a);
		fscanf(inp,"%d",&a);
		fprintf(oup,"%d\n",a);
		fclose(oup);
	}
}