import java.io.*;
import java.util.StringTokenizer;

/**
 * Created with IntelliJ IDEA.
 * User: �
 * Date: 05/02/13
 * Time: 18:43
 * To change this template use File | Settings | File Templates.
 */
public class CLMBSTRS
{
    int[] f;

    int calc(int n){
        int a = f[n];
        int cnt = 0;
        while (a > 0){
            cnt += a%2;
            a /= 2;
        }
        return cnt;
    }

    void solve() throws IOException {
        int t = nextInt();
        f = new int[1000001];
        f[0] = 1;
        f[1] = 1;
        for (int i = 2; i <= 1000000; i++)
            f[i] = (f[i-1] + f[i-2]) % 1000000007;
        for (int it = 0; it < t; it++){
            int n = nextInt();
            if (calc(n) == nextInt())
                out.println("CORRECT");
            else
                out.println("INCORRECT");
        }
    }

    public static void main(String[] args) throws IOException{
        new WORDPLAY().run();
    }

    BufferedReader in;
    StringTokenizer tokenizer;
    PrintWriter out;

    public void run() throws IOException
    {
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