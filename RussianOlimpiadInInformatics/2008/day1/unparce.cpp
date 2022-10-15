#include <iostream>
#include <fstream>
#define int64 long long
using namespace std;



int main(){
	ofstream oup("answer.txt");
	for (int i=0;i<20;i++){
		string s="answers\\ans";
		if (i/10)
			s+=(i/10+'0');
		s+=(i%10+'0');
		s+=".out";
		ifstream inp(s.data());
		string a;
		inp>>a;
		cerr<<s<<" "<<a<<endl;
		oup<<a<<endl;
		inp.close();
	}
}