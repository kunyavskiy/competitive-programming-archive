import java.io.*;
import java.util.Arrays;
import java.util.HashSet;
import java.util.StringTokenizer;


/**
 * Created with IntelliJ IDEA.
 * User: �
 * Date: 06/02/13
 * Time: 13:34
 * To change this template use File | Settings | File Templates.
 */
public class WORDPLAY {

    HashSet<String> dictionary;

    void solve() throws IOException {
        dictionary = new HashSet<String>();
        int n = nextInt();
        for (int i = 0; i < n; i++){
            char[] str = nextToken().toCharArray();
            Arrays.sort(str);
            dictionary.add(new String(str));
        }
        int r = nextInt(),c = nextInt();
        int q = nextInt();

        for (int it = 0; it < q; it++){
            String res = "";
            for (int i = 0; i < r; i++)
               res = res.concat(nextToken());
            char[] _res = res.toCharArray();
            Arrays.sort(_res);
            solve(_res);
        }
    }

    private void solve(char[] a) {
        boolean[] can = new boolean[1<<a.length];
        for (int i = 0; i < (1<<a.length); i++){
            StringBuilder str = new StringBuilder();
            for (int j = 0; j < a.length; j++)
                if ((i & (1<<j)) != 0)
                    str.append(a[j]);
            if (dictionary.contains(str.toString()))
                can[i] = true;
        }
        boolean[] dp = new boolean[1<<a.length];

        for (int i = 0; i < (1<<a.length); i++){
            for (int j = i; j != 0 && !dp[i]; j = (j-1)&i)
                if (can[j] && !dp[i^j])
                    dp[i] = true;
        }

        if (dp[(1<<a.length)-1])
            out.println("Alice");
        else
            out.println("Bob");
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