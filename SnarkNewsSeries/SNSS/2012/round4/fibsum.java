import java.io.*;
import java.lang.*;
import java.util.*;
import java.math.*;

public class Main
{

    void solve() throws IOException{
        String s = nextToken(), t = nextToken();

        BigInteger fib[] = new BigInteger[10010];
        fib[0] = BigInteger.ONE;
        fib[1] = BigInteger.valueOf(2);
        for (int i = 2; i < 10010; i++)
            fib[i] = fib[i-1].add(fib[i-2]);



        BigInteger res = BigInteger.ZERO;

        for (int i = 0; i < s.length(); i++)
            if (s.charAt(i) == '1')
                res = res.add(fib[s.length()-i-1]);
            
        for (int i = 0; i < t.length(); i++)
            if (t.charAt(i) == '1')
                res = res.add(fib[t.length()-i-1]);

        StringBuilder sb = new StringBuilder();


        boolean any = false;

        for (int i = 10009; i >= 0; i--){
            if (fib[i].compareTo(res) > 0){
                if (any)
                    sb.append('0');
            }
            else {
                res = res.subtract(fib[i]);
                sb.append('1');
                any = true;
            }                              
        }

        out.println(sb.toString());
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
            boolean oj = System.getProperty("LOCAL") == null;
            Reader reader = oj ? new InputStreamReader(System.in) : new FileReader("input.txt");
            Writer writer = oj ? new OutputStreamWriter(System.out) : new FileWriter("output.txt");
            in = new BufferedReader(reader);
            tokenizer = null;
            out = new PrintWriter(writer);
            solve();
            in.close();
            out.close();
        } catch (IOException e){
            e.printStackTrace();
            System.exit(1);
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
