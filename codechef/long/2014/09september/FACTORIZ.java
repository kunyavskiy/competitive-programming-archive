import java.io.*;
import java.math.BigInteger;
import java.util.ArrayList;
import java.util.Random;
import java.util.StringTokenizer;

public class Main
{

    static final int maxPrime = (int) 1e6;
    Random rnd = new Random(239);
    ArrayList<Integer> primes;
    int[] minPrimeDivisor = new int[maxPrime];

    public Main() {
    }

    int randInt(int l, int r){
        return l + rnd.nextInt(r - l + 1);
    }

    long min(long a, long b){
        if (a < b) return a;
        return b;
    }


    final static int MAXD = 110;

    void pollard(long n) {
        if (n == 1) return;
        if (n < maxPrime){
            divs.add(BigInteger.valueOf(minPrimeDivisor[((int) n)]));
            pollard(n / minPrimeDivisor[((int) n)]);
            return;
        }
        if (BigInteger.valueOf(n).isProbablePrime(1)) {
            divs.add(BigInteger.valueOf(n));
            return;
        }

        int MAXX = (int)(1e9);

        int q = randInt(2, MAXD);
        long x1 = randInt(1, (int)min(MAXX, n - 1));
        long x2 = x1, g = 0;
        int maxJ = 1 << 15;
        for (int j = 1; j < maxJ; j++) {
            x1 = mmul(x1, x1, n);
            if ((x1 += q) >= n) x1 -= n;
            long z = abs(x1 - x2);
            g = gcd(z, n);
            if (g != 1) break;
            if ((j & (j - 1)) == 0)
                x2 = x1;
        }
        if (1 < g && g < n) {
            pollard(g);
            pollard(n / g);
            return;
        }
        divs.add(BigInteger.valueOf(n));
    }

    private long gcd(long a, long b) {
        while (a != 0 && b != 0){
            long t = a % b;
            a = b;
            b = t;
        }
        return a+b;
    }

    private long abs(long l) {
        if (l > 0) return l;
        return -l;
    }

    private long mmul(long x, long y, long n) {
        return BigInteger.valueOf(x).multiply(BigInteger.valueOf(y)).mod(BigInteger.valueOf(n)).longValue();
    }

    ArrayList<BigInteger> divs;

    void solveOne(BigInteger x){
        if (x.bitLength() < 64){
            out.println(1);
            out.println(x);
            return;
        }
        divs = new ArrayList<BigInteger>();
        boolean big = x.bitLength() >= 60;
        if (big) {
            for (int i : primes) {
                while (x.mod(BigInteger.valueOf(i)).equals(BigInteger.ZERO)) {
                    divs.add(BigInteger.valueOf(i));
                    x = x.divide(BigInteger.valueOf(i));
                }
                if (i >= 10000) break;
            }
        } else {
            long xx = x.longValue();
            for (int i : primes) {
                while (xx % i == 0) {
                    divs.add(BigInteger.valueOf(i));
                    xx = xx / i;
                }
            }
            x = BigInteger.valueOf(xx);
        }
        if (!x.equals(BigInteger.ONE)) {
            if (x.compareTo(BigInteger.TEN.pow(18)) > 0) {
                divs.add(x);
            } else {
                pollard(x.longValue());
            }
        }
        out.println(divs.size());
        for (BigInteger b : divs)
            out.println(b);
    }

    void solve() throws IOException{
        genPrimes();
        int t = nextInt();
        for (int i = 0; i < t; i++) {
            solveOne(nextBigint());
        }
    }

    private void genPrimes() {
        primes = new ArrayList<Integer>();
        for (int i = 2; i < maxPrime; i++){
            if (minPrimeDivisor[i] == 0){
                minPrimeDivisor[i] = i;
                primes.add(i);
            }
            for (int x : primes){
                if (x > minPrimeDivisor[i] || x * i >= maxPrime) break;
                minPrimeDivisor[x * i] = x;
            }
        }
    }

    public static void main(String[] args) throws IOException{
        new Main().run();
    }

    BufferedReader in;
    StringTokenizer tokenizer;
    PrintWriter out;

    public void run() throws IOException
    {
        try {
            boolean oj;
            try {
                oj = System.getProperty("LOCAL") == null;
            } catch (Exception unused){
                oj = true;
            }
            long start = System.currentTimeMillis();
            Reader reader = oj ? new InputStreamReader(System.in) : new FileReader("input.txt");
            Writer writer = oj ? new OutputStreamWriter(System.out) : new FileWriter("output.txt");
            in = new BufferedReader(reader);
            tokenizer = null;
            out = new PrintWriter(writer);
            solve();
            System.err.println(System.currentTimeMillis() - start);
            //while (System.currentTimeMillis() - start < 2800);
            //in.close();
            out.close();
        } catch (Exception e) {
            e.printStackTrace();
            System.exit(1);
        }
    }

    BigInteger nextBigint() throws IOException {
        return new BigInteger(nextToken());
    }

    int nextInt() throws IOException {
        return Integer.parseInt(nextToken());
    }

    String nextToken() throws IOException {
        while (tokenizer == null || !tokenizer.hasMoreTokens()) {
            tokenizer = new StringTokenizer(in.readLine());
        }
        return tokenizer.nextToken();
    }

}
