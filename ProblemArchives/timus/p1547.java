import java.io.*;
import java.math.BigInteger;
import java.util.StringTokenizer;


/**
 * Created with IntelliJ IDEA.
 * User: Pavel Kunyavskiy
 * Date: 21/08/13
 * Time: 12:07
 */
public class p1547 {
    void solve() throws IOException {
        int n = nextInt();
        BigInteger m = new BigInteger(nextToken());
        BigInteger total = BigInteger.ZERO;
        for (int i = 1; i <= n; i++)
            total = total.add(BigInteger.valueOf(26).pow(i));
        int big = total.mod(m).intValue();
        for (int i = 0; i < m.intValue(); i++){
            BigInteger from = total.divide(m).multiply(BigInteger.valueOf(i)).add(BigInteger.valueOf(Math.min(i,big)));
            BigInteger to = total.divide(m).multiply(BigInteger.valueOf(i + 1)).subtract(BigInteger.ONE).add(BigInteger.valueOf(Math.min(i+1, big)));
            String resF = getString(from);
            String resT = getString(to);
            out.printf("%s-%s\n",resF,resT);
        }
    }

    private String getString(BigInteger val) {
        StringBuilder res = new StringBuilder();
        int len = 1;
        while (BigInteger.valueOf(26).pow(len).compareTo(val) < 0){
            val = val.subtract(BigInteger.valueOf(26).pow(len));
            len++;
        }

        for (int i = 0; i < len; i++){
            res.append((char)(val.mod(BigInteger.valueOf(26)).intValue() + 'a'));
            val = val.divide(BigInteger.valueOf(26));
        }

        return res.reverse().toString();
    }

    public static void main(String[] args) throws IOException {
        new p1547().run();
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
