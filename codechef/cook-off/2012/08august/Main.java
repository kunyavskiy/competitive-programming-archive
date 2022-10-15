import java.io.*;
import java.lang.*;
import java.util.*;
import java.math.*;

public class Main
{
    
    TreeSet<BigInteger> good;

    void PreCalc(){
        good = new TreeSet();
        BigInteger limit = BigInteger.TEN.pow(1010);

        BigInteger a = BigInteger.valueOf(2);

        good.add(a);

        for (int i = 2; a.compareTo(limit) == -1; i++){
            if (i % 2 == 0)
                a = a.multiply(BigInteger.valueOf(i)).divide(BigInteger.valueOf((i+1)/2));
            else
                a = a.multiply(BigInteger.valueOf(i)).divide(BigInteger.valueOf(i - i/2));
            good.add(a);
        }            
    }



    void solve() throws IOException{
        PreCalc();
        int t = nextInt();
        for (;t > 0; t--){
            BigInteger x = new BigInteger(nextToken());
            if (good.contains(x))
                out.println("YES");
            else
                out.println("NO");
        }
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
            boolean oj = true;//System.getProperty("ONLINE_JUDGE") != null;
            Reader reader = oj ? new InputStreamReader(System.in) : new FileReader("input.txt");
            Writer writer = oj ? new OutputStreamWriter(System.out) : new FileWriter("output2.txt");
            in = new BufferedReader(reader);
            tokenizer = null;
            out = new PrintWriter(writer);
            solve();
            //in.close();
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
