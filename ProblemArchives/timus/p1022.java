import java.io.*;
import java.lang.*;
import java.util.*;

public class p1022
{

	private class Vertex{
		ArrayList<Vertex> es;
		boolean used;
		int num;
		Vertex(){
		}
	}
	int n;

	Vertex[] g;
	ArrayList<Integer> ans;

	void dfs(Vertex v){
		if (v.used)
			return;
		v.used = true;
		for (Vertex to: v.es)
		 	dfs(to);
		ans.add(v.num);
	}

	void solve() throws IOException{
		n = nextInt();
		g = new Vertex[n];
		for (int i = 0; i < n; i++)
			g[i] = new Vertex();
		for (int i = 0; i < n; i++){				
			g[i].num = i+1;
			g[i].es = new ArrayList<Vertex>();
			int x = nextInt();  
			while (x != 0){     
				g[i].es.add(g[x-1]);
				x = nextInt();
			}
		}

		ans = new ArrayList<Integer>();

		for (int i = 0; i < n; i++)
			if (!g[i].used)
				dfs(g[i]);

		Object[] res = ans.toArray();

		for (int i = n-1; i >= 0; --i)
			out.print(res[i]+" ");
		out.println();		
	}
          

	public static void main(String[] args) throws IOException{
		new p1022().run();
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
