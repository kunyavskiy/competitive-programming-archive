import java.io.*;
import java.util.StringTokenizer;

/**
 * Created with IntelliJ IDEA.
 * User: �
 * Date: 05/02/13
 * Time: 18:43
 * To change this template use File | Settings | File Templates.
 */

public class BUY1GET1
{

    void solve() throws IOException {
        int t = nextInt();
        for (int it = 0; it < t; it++){
            String str = nextToken();
            int[] cnt = new int[52];

            for (char i : str.toCharArray()){
                if ('a' <= i && i <= 'z')
                    cnt[i-'a']++;
                else
                    cnt[i-'A'+26]++;
            }
            int ans = 0;
            for (int i : cnt) {
                ans += (i + 1) / 2;
            }
            out.println(ans);
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