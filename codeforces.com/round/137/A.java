import java.io.*;
import java.lang.*;
import java.util.*;

public class Main
{

    void solve() throws IOException{
        int n = nextInt(), k = nextInt();
        int[] a = new int[n];
        int[] cnt = new int[100001];
        int gcnt = 0;
        for (int i = 0; i < n; i++){
            a[i] = nextInt();
            cnt[a[i]]++;
            if (cnt[a[i]] == 1)
                gcnt++;
        }
        --k;

        if (gcnt == 1){
            out.println("0");
            return;
        }
            
                                    
        
        for (int i = 0; i < 10*n; i++){
            cnt[a[(i%n)]]--;
            if (cnt[a[i%n]] == 0)  
                gcnt--;
            a[(i%n)] = a[(i+k)%n];
            cnt[a[(i%n)]]++;
            if (cnt[a[i%n]] == 1)  
                gcnt++;
            if (gcnt == 1){
                out.println(i+1);
                return ;
            }
        }

        out.println("-1");           
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
