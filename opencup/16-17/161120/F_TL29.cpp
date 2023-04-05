#include <bits/stdc++.h>

using namespace std; 

/** Begin fast allocation */
const int MAX_MEM = 5e8;
int mpos = 0;
char mem[MAX_MEM];
inline void * operator new ( size_t n ) {
	assert((mpos += n) <= MAX_MEM);
	return (void *)(mem + mpos - n);
}
inline void operator delete ( void * ) noexcept { } // must have!
/** End fast allocation */

inline int readChar();
template <class T = int> inline T readInt(); 
template <class T> inline void writeInt( T x, char end = 0 );
inline void writeChar( int x ); 
inline void writeWord( const char *s );

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

typedef long long ll;

const int N = 1 << 20;
const int K = 2 * N;

char str[N];
int n, k0, k1, l[K], r[K], covered[K], value[K];
int p[N], x[N + 1], sum[N + 1];
vector<int> ind[2 * N];
int len[2 * N], used[2 * N];

struct Event { int i, type; };
//queue<Event> q;

int get( int i ) {
	// assert(i <= n);
	int res = i;
	while (res < n && x[res] != -1) res = p[res];
	while (i != res) {
		int tmp = p[i];
		p[i] = res;
		i = tmp;
	}
	return res;
}

int zeroes[2 * N];
void inc( int i ) {
	for (i += N; i > 0; i /= 2)
		zeroes[i]++;
}
int get_sum( int l, int r ) {
	int res = 0;
	for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
		if (l & 1) res += zeroes[l++];
		if (r & 1) res += zeroes[--r];
	}
	return res;
}

void go( Event e );

void make( int i, int V ) {
	x[i] = V;
	if (!x[i]) inc(i);
	for (i += N; i > 0; i /= 2) {
		used[i]++;
		if (used[i] + 1 == len[i]) go(Event {i, 0});
		if (used[i] + 0 == len[i]) go(Event {i, 1});
	}
}

void timeS( const char *s ) {
	static double start = 0;
	fprintf(stderr, "%.2f : %s\n", 1. * (clock() - start) / CLOCKS_PER_SEC, s);
	start = clock();

}

void process( int i ) {
	covered[i] = INT_MIN;
	int pos = get(l[i]);
	if (pos < r[i]) {
		int V = value[i];
		//if (x[l[i]] != V && x[r[i] - 1] != V) {
			int zeroes = get_sum(l[i], r[i]);
			if ((V == 0 && zeroes == 0) || (V == 1 && r[i] - l[i] - 1 - zeroes == 0))
				make(pos, V);
		// }
	}
}

void go( Event e ) {
	int dt = e.type ? 1 : (len[e.i] - 1);
	for (int i : ind[e.i]) 
		if ((covered[i] += dt) == r[i] - l[i] - 1) 
			process(i);

}

int main() {
	n = readInt();
	k0 = readInt();
	k1 = readInt();
	forn(i, k0 + k1) {
		l[i] = readInt() - 1;
		r[i] = readInt();
		value[i] = (i >= k0);

		for (int L = l[i] + N, R = r[i] + N; L < R; L >>= 1, R >>= 1) {
			if (L & 1) ind[L++].push_back(i);
			if (R & 1) ind[--R].push_back(i);
		}
	}
	timeS("build");

	for (int len = N, k = 1; len > 0; len >>= 1, k <<= 1)
		forn(i, len)
			::len[len + i] = k;

	forn(i, n + 1) x[i] = -1, p[i] = i + 1;
	//forn(i, N) q.push(Event {N + i, 0});
	timeS("build");
	forn(i, k0 + k1) if (r[i] - l[i] == 1) 
		process(i);

	// while (q.size()) {
	// 	Event e = q.front(); q.pop();
	// 	int dt = e.type ? 1 : (len[e.i] - 1);
	// 	for (int i : ind[e.i]) 
	// 		if ((covered[i] += dt) == r[i] - l[i] - 1) 
	// 			process(i);
	// }
	timeS("miu");

	int cc = 0;
	forn(i, n) {
		if (x[i] == -1)
			x[i] = cc, cc ^= 1;
		sum[i + 1] = sum[i] + x[i];
	}
	forn(i, k0 + k1) {
		int len = r[i] - l[i], ones = sum[r[i]] - sum[l[i]];
		if ((value[i] && ones == 0) || (!value[i] && len - ones == 0)) {
			puts("No");
			return 0;
		}
	}
	puts("Yes");
	forn(i, n) str[i] = '0' + x[i];
	str[n] = 0;
	writeWord(str);
}

/** Read */

static const int buf_size = 4096;

inline int getChar() {
	static char buf[buf_size];
	static int len = 0, pos = 0;
	if (pos == len)
		pos = 0, len = fread(buf, 1, buf_size, stdin);
	if (pos == len)
		return -1;
	return buf[pos++];
}

inline int readChar() {
	int c = getChar();
	while (c <= 32)
		c = getChar();
	return c;
}

template <class T>
inline T readInt() {
	int s = 1, c = readChar();
	T x = 0;
	if (c == '-')
		s = -1, c = getChar();
	while ('0' <= c && c <= '9')
		x = x * 10 + c - '0', c = getChar();
	return s == 1 ? x : -x;
}

/** Write */

static int write_pos = 0;
static char write_buf[buf_size];

inline void writeChar( int x ) {
	if (write_pos == buf_size)
		fwrite(write_buf, 1, buf_size, stdout), write_pos = 0;
	write_buf[write_pos++] = x;
}

template <class T> 
inline void writeInt( T x, char end ) {
	if (x < 0)
		writeChar('-'), x = -x;

	char s[24];
	int n = 0;
	while (x || !n)
		s[n++] = '0' + x % 10, x /= 10;
	while (n--)
		writeChar(s[n]);
	if (end)
		writeChar(end);
}

inline void writeWord( const char *s ) {
	while (*s)
		writeChar(*s++);
}

struct Flusher {
	~Flusher() {
		if (write_pos)
			fwrite(write_buf, 1, write_pos, stdout), write_pos = 0;
	}
} flusher;