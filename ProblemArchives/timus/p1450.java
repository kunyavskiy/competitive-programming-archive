import java.io.*;
import java.lang.*;
import java.util.*;
import java.math.*;

public class p1450
{
    int[][] g;
    int[] ans;
    int f,s,n;


    int calc(int id){
        if (ans[id] != -1)
            return ans[id];

        ans[id] = -(1<<30);

        for (int i = 0; i < n; i++)
            if (g[id][i] > 0)
                ans[id] = Math.max(ans[id],g[id][i] + calc(i));
        return ans[id];
    }



	void solve() throws IOException{
        n = nextInt();
        g = new int[n][n];
        int m = nextInt();
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                g[i][j] = -(1<<30);

        for (int i = 0; i < m; i++){
            int a,b;
            a = nextInt()-1;b = nextInt()-1;
            g[a][b] = Math.max(g[a][b],nextInt());
        }

        ans = new int[n];

        for (int i = 0; i < n; i++)
            ans[i] = -1;

        s = nextInt()-1;f = nextInt()-1;
        ans[f] = 0;
        if (calc(s) < 0)
            out.println("No solution");
        else
            out.println(calc(s));
	}

	public static void main(String[] args) throws IOException{
		new p1450().run();
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
