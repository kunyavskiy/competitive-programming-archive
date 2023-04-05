
import java.io.*;
import java.math.BigInteger;
import java.util.Random;
import java.util.StringTokenizer;

public class D {

    private void solve() throws IOException {
        int n = 50;
        System.out.println(n);
        Random random = new Random();
        for (int i = 0; i < n; i++) {
            BigInteger p = BigInteger.probablePrime(8, random);
            BigInteger q = null;
            while (q == null || !q.isProbablePrime(100)) {
                q = p.multiply(p).multiply(p).multiply(BigInteger.valueOf(random.nextInt(1000000000))).add(BigInteger.ONE);
            }
            System.out.println(p + " " + BigInteger.valueOf(random.nextLong()).modPow(p, q) + " " +  q);
        }
    }

    // --------------------------------------

    BufferedReader br;
    StringTokenizer st;
    PrintWriter out;

    String next() throws IOException {
        try {
            while (st == null || !st.hasMoreTokens()) {
                st = new StringTokenizer(br.readLine());
            }
            return st.nextToken();
        } catch (Exception e) {
            throw new IOException();
        }
    }

    int nextInt() throws IOException {
        try {
            return Integer.parseInt(next());
        } catch (Exception e) {
            throw new IOException();
        }
    }

    public static void main(String[] args) throws FileNotFoundException {
        new D().run();
    }

    private void run() throws FileNotFoundException {
        br = new BufferedReader(new InputStreamReader(System.in));
        out = new PrintWriter(System.out);
        try {
            solve();
        } catch (IOException e) {
            e.printStackTrace();
        }
        out.close();
    }

}