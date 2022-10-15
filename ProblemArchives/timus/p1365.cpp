//#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <cstring>
#include <string>
#include <cmath>
#include <cassert>
#include <ctime>
#include <algorithm>
#include <sstream>
#include <list>
#include <queue>
#include <deque>
#include <stack>
#include <cstdlib>
#include <cstdio>
#include <iterator>
#include <functional>
#include <bitset>
#define mp make_pair
#define pb push_back

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

#if ( ( _WIN32 || __WIN32__ ) && __cplusplus < 201103L)
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

#define TASKNAME "1365"

#ifdef LOCAL
static struct __timestamper {
    string what;
    __timestamper(const char* what) : what(what){};
    __timestamper(const string& what) : what(what){};
	~__timestamper(){
        TIMESTAMPf("%s", what.data());
	}
} __TIMESTAMPER("end");
#else 
struct __timestamper {};
#endif

typedef long long ll;
typedef long double ld;

enum LexTy {
   _OPEN, _CLOSE, _DIV, _MUL, _ADD, _SEP, _END, _NUM
};

string fix(string s){
	if (s[0] == ';')
		s = '1' + s;
	for (int i = 0; i < (int)s.size(); i++){
		if ((s[i] == '(' || s[i] == ';') && (s[i+1] == ')' || s[i+1] == ';')){
			s = string(s.begin(), s.begin() + i + 1) +'1' + string(s.begin() + i + 1, s.end());
		}
	}
	if (s[(int)s.size()-1] == ';')
		s+= "1";
	return s;
}

struct Tokenizer {
	string str;
	int ptr;

	pair<LexTy, int> res;

	pair<LexTy, int> _next(){
		if (ptr == (int)str.size()) return mp(_END, -1);
		char cur = str[ptr]; ptr++;
		if (cur == '(') return mp(_OPEN, -1);
		if (cur == ')') return mp(_CLOSE, -1);
		if (cur == '/') return mp(_DIV, -1);
		if (cur == '*') return mp(_MUL, -1);
		if (cur == '+') return mp(_ADD, -1);
		if (cur == ';') return mp(_SEP, -1);
		assert(isdigit(cur));
		int res = cur - '0';
		while (ptr < (int)str.size() && isdigit(str[ptr]))
			res = 10*res + str[ptr++]-'0';
		return mp(_NUM, res);
	}

	Tokenizer& next(){
		res = _next();
		return *this;
	}

	const pair<LexTy, int>& cur(){
		return res;
	}
	Tokenizer(string _str):str(_str),ptr(0){
	    str = fix(str);
//	    eprintf("After fix : %s\n", str.data());
		next();
	}
	void eprint(){
		eprintf("%s cur = (%d, %d)\n", str.data() + ptr, res.first, res.second);
	}
};

int concat(int a, int b){
	stringstream s;
	s << a << b;
	int res;
	s >> res;
	return res;
}

int concat(Tokenizer& t, bool);

int expr(Tokenizer& t){
//    eprintf("EXPR : "); t.eprint();

	LexTy firstop = t.cur().first;
	while (firstop == _SEP) {
		firstop = t.next().cur().first;
	}
	if (firstop == _OPEN){
		int res = concat(t.next(), true);
		assert(t.cur().first == _CLOSE);
		t.next();
		return res;
	}
	if (firstop == _NUM) {
		int res = t.cur().second;
		t.next();
		return res;
	}
	assert(firstop == _ADD || firstop == _DIV || firstop == _MUL);
	int res = concat(t.next(), false);
	while (t.cur().first == _SEP) {
		int rres = concat(t.next(), false);
		if (firstop == _ADD)
			res = res + rres;
		else if (firstop == _MUL)
			res = res * rres;
		else if (firstop == _DIV) {
			if (rres == 0) res = 0;
			else res = res / rres;
		}
	}
	return res;
}

int concat(Tokenizer& t, bool skipsep){
//	eprintf("CONCAT : "); t.eprint();
	stringstream str;
	while (t.cur().first != _END && t.cur().first != _CLOSE && (skipsep || t.cur().first != _SEP)) 
		str << expr(t);
	int res;
	if (!(str >> res))
		res = 1;
	return res;
}

int main(){
  #ifdef LOCAL
    assert(freopen(TASKNAME".in","r",stdin));
    assert(freopen(TASKNAME".out","w",stdout));
  #endif

    char buf[100];
    int tst = 0;
    while (gets(buf)){
    	Tokenizer t(buf);
    	int res = concat(t, true);
    	printf("Expression %d evaluates to: %d\n", ++tst, res);
    }
      
  return 0;
}