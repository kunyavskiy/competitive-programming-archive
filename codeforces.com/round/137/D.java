import java.io.*;
import java.lang.*;
import java.util.*;
import java.security.*;

public class Main
{

    void solve() throws IOException{
         int n = nextInt();
         int x = nextInt();
         int[] a = new int[n];
         int[] b = new int[n];

         int hash = 0;

         for (int i = 0; i < n; i++){
            a[i] = nextInt();
            hash = hash * 239017 + a[i];
         }
         for (int i = 0; i < n; i++){
            b[i] = nextInt();
            hash = hash * 239017 + b[i];
         }

         Random rnd = new Random(hash);

         for (int i = 0; i < n; i++){
            int id = rnd.nextInt(i+1);
            int t = a[i];
            a[i] = a[id];
            a[id] = t;
         }

         for (int i = 0; i < n; i++){
            int id = rnd.nextInt(i+1);
            int t = b[i];
            b[i] = b[id];
            b[id] = t;
         }

         Arrays.sort(a);
         Arrays.sort(b);

         int cnt = 0;
         int ptr = 0;

         for (int i = n-1; i >= 0; i--){
            while (ptr < n && a[i] + b[ptr] < x)
                ptr++;
            ptr++;
            if (ptr <= n) cnt++;
         }

         out.println(1+" "+cnt);
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
        
            boolean oj = System.getProperty("ONLINE_JUDGE") != null;
            Reader reader = oj ? new InputStreamReader(System.in) : new FileReader("input.txt");
            Writer writer = oj ? new OutputStreamWriter(System.out) : new FileWriter("output.txt");
            in = new BufferedReader(reader);
            tokenizer = null;
            out = new PrintWriter(writer);                   
            solve();
            in.close();
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
