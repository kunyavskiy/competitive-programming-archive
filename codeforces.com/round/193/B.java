import java.io.*;
import java.util.StringTokenizer;


/**
 * Created with IntelliJ IDEA.
 * User: Pavel Kunyavskiy
 * Date: 24/07/13
 * Time: 16:19
 */
public class B {
    void solve() throws IOException {
        int n,k;
        n = nextInt();
        k = nextInt();
        int[] a;
        a = new int[n];
        for (int i = 0; i < n; i++)
            a[i] = nextInt();
        long[] sum;
        sum = new long[n-k+1];
        long cur = 0;
        for (int i = 0; ; i++){
            if (i >= k) sum[i-k] = cur;
            if (i == n) break;
            cur += a[i];
            if (i >= k) cur -= a[i-k];
        }
        long[] max;
        int[] maxpos;
        max = new long[n-k+1];
        maxpos = new int[n-k+1];
        max[0] = sum[0];
        maxpos[0] = 0;
        for (int i = 1; i < sum.length; i++){
            max[i] = Math.max(sum[i], max[i-1]);
            if (max[i] == max[i-1]) maxpos[i] = maxpos[i-1];
            else maxpos[i] = i;
        }
        long ans = Long.MIN_VALUE;
        int posa = -1, posb = -1;
        for (int i = k; i <= n-k; i++){
            if (ans < sum[i] + max[i-k]){
                ans = sum[i] + max[i-k];
                posa = maxpos[i-k]+1;
                posb = i+1;
            }
        }
        out.println(posa+" "+posb);
    }

    public static void main(String[] args) throws IOException {
        new B().run();
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
