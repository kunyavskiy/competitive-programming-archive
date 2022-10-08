import java.io.*;
import java.lang.*;
import java.util.*;

public class Main
{
    static final int MOD = 1000000007;
    int[] p;
    int[] l;

    int root(int v){
        if (p[v] == v)
            return v;
        int temp = p[v];
        p[v] = root(p[v]);
        l[v] = (l[v] + l[temp])%MOD; 
        return p[v];
    }

    void solve() throws IOException{
        int n = nextInt();
        p = new int[n];
        l = new int[n];
        for (int i = 0; i < n; i++){
            p[i] = i;
            l[i] = 0;
        }

        int ans = 0;

        for (int i = 0; i < n; i++){
            int k = nextInt();
            for (int j = 0; j < k; j++){
                int a = nextInt() - 1, b = (nextInt()+MOD)%MOD;
                int r = root(a);
                p[r] = i;
                l[r] = (l[a] + b)%MOD;
                ans = (ans + l[r])%MOD;
            }
        }

        out.println(ans);      
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
