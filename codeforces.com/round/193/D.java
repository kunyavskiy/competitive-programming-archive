import java.io.*;
import java.math.BigInteger;
import java.util.StringTokenizer;



/**
 * Created with IntelliJ IDEA.
 * User: Pavel Kunyavskiy
 * Date: 24/07/13
 * Time: 17:43
 */
public class D {

    class Rational{
        BigInteger num, den;

        Rational(long num, long den){
            this.num = BigInteger.valueOf(num);
            this.den = BigInteger.valueOf(den);
        }

        Rational(Rational r){
            num = r.num;
            den = r.den;
        }

        void add(Rational r){
            num = num.multiply(r.den).add(r.num.multiply(den));
            den = den.multiply(r.den);
            norm();
        }

        void norm(){
            BigInteger g = num.gcd(den);
            num = num.divide(g);
            den = den.divide(g);
        }

        BigInteger value(){
            return num.divide(den);
        }
    }

    void solve() throws IOException {
        int n,k;
        n = nextInt();
        k = nextInt();
        int[][] a = new int[n][n];

        for (int i = 0; i < n; i++){
            a[i][i] = -1;
            for (int j = i + 1; j < n; j++)
                a[i][j] = a[j][i] = nextInt();
        }

        Rational ans = new Rational(0,1);

        Rational[] cxk = new Rational[n];

        for (int i = 0; i < k; i++)
            cxk[i] = new Rational(0,1);

        cxk[k-1] = new Rational(1,1);
        for (int i = 1; i <= n; i++)
            cxk[k-1].den = cxk[k-1].den.multiply(BigInteger.valueOf(i));
        for (int i = 1; i <= n-k; i++)
            cxk[k-1].num = cxk[k-1].num.multiply(BigInteger.valueOf(i));
        for (int i = 1; i <= k; i++)
            cxk[k-1].num = cxk[k-1].num.multiply(BigInteger.valueOf(i));
        cxk[k-1].norm();

        for (int i = k; i < n; i++){
            cxk[i] = new Rational(1,1);
            cxk[i].num = cxk[i-1].num.multiply(BigInteger.valueOf(i));
            cxk[i].den = cxk[i-1].den.multiply(BigInteger.valueOf(i-k+1));
            cxk[i].norm();
        }



        for (int i = 0; i < n; i++){
            int cnt = 0;
            long sum = 0;
            for (int j = 0; j < n; j++){
                if (a[i][j] != -1){
                    cnt++;
                    sum += a[i][j];
                }
            }
            if (cnt != 0) {
                Rational cur = new Rational(cxk[cnt-1]);
                cur.num = cur.num.multiply(BigInteger.valueOf(sum));
                //System.err.println(cnt + " " + sum + " -> " + cur.num+"/"+cur.den);
                ans.add(cur);
            }
        }

        out.println(ans.value());
    }

    public static void main(String[] args) throws IOException {
        new D().run();
    }

    BufferedReader in;
    StringTokenizer tokenizer;
    PrintWriter out;

    public void run() throws IOException {
        try {
            boolean oj = System.getProperty("ONLINE_JUDGE") != null;
            Reader reader = oj ? new InputStreamReader(System.in) : new FileReader("input.txt");
            Writer writer = oj ? new OutputStreamWriter(System.out) : new FileWriter("output.txt");
            in = new BufferedReader(reader);
            tokenizer = null;
            out = new PrintWriter(writer);
            solve();
            out.close();
        } catch (Exception e) {
            e.printStackTrace();
            System.exit(1);
        }
    }

    int nextInt() throws IOException {
        return Integer.parseInt(nextToken());
    }

    long nextLong() throws IOException {
        return Long.parseLong(nextToken());
    }

    double nextDouble() throws IOException {
        return Double.parseDouble(nextToken());
    }

    String nextToken() throws IOException {
        while (tokenizer == null || !tokenizer.hasMoreTokens()) {
            tokenizer = new StringTokenizer(in.readLine());
        }
        return tokenizer.nextToken();
    }
}
