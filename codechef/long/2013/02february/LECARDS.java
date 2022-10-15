import java.io.*;
import java.util.StringTokenizer;


/**
 * Created with IntelliJ IDEA.
 * User: �
 * Date: 05/02/13
 * Time: 19:38
 * To change this template use File | Settings | File Templates.
 */
public class LECARDS {
    int[][] c;
    final int MOD = 1000000007;
    void solve() throws IOException {
        c = new int[1001][1001];
        c[0][0]=1;
        for (int i = 0; i <= 1000; i++)
            for (int j = 0; j <= 1000; j++){
                if (i > 0) c[i][j] = (c[i][j] + c[i-1][j]) % MOD;
                if (i > 0 && j > 0) c[i][j] = (c[i][j] + c[i-1][j-1]) % MOD;
            }

        int t = nextInt();
        for (int it = 0; it < t; it++){
            int ans = 0;
            int n = nextInt();
            for (int i = 0; i < n; i++) nextInt();
            for (int i = n/2+1; i <= n; i++)
                 ans = (ans + c[n][i]) % MOD;
            out.println(ans);
        }
    }

    public static void main(String[] args) throws IOException {
        new WORDPLAY().run();
    }

    BufferedReader in;
    StringTokenizer tokenizer;
    PrintWriter out;

    public void run() throws IOException {
        try {
            boolean oj = System.getProperty("LOCAL") == null;
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