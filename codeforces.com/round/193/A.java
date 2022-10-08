import java.io.*;
import java.util.StringTokenizer;


/**
 * Created with IntelliJ IDEA.
 * User: Pavel Kunyavskiy
 * Date: 24/07/13
 * Time: 16:05
 */
public class A {
    void solve() throws IOException {
        int n = nextInt();
        String s = nextToken();
        int ans = 0;
        for (int i = 0; i < s.length(); i++)
            if (i % n == 0 && i >= 4 && s.charAt(i-1) == s.charAt(i-2) && s.charAt(i-1) == s.charAt(i-3))
                ans++;
        out.println(ans);
    }

    public static void main(String[] args) throws IOException {
        new A().run();
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
