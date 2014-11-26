import java.io.*;
import java.util.*;

public class ConnectingGame {
	public String isValid(String[] board) {
		int n = board.length;
		int m = board[0].length();
		char[][] str = new char[n][m];
		for (int i = 0; i < n; ++ i)
			str[i] = board[i].toCharArray();

		int[] dx = {1,-1,0,0,1,-1,1,-1};
		int[] dy = {0,0,1,-1,1,1,-1,-1};

		int[][] block = new int[n][m];

		int tot = n*m*2+6;
		int source = tot-2;
		int target = tot-1;
		for (int i = 0; i < n; ++ i) {
			for (int j = 0; j < m; ++ j) {
				if (block[i][j] != 0) continue;
				Queue<Integer> que = new LinkedList<Integer>();
				que.offer(i);
				que.offer(j);
				block[i][j] = tot ++;
				tot ++;
				while (que.peek() != null) {
					int x = que.poll();
					int y = que.poll();
					for (int k = 0; k < 4; ++ k) {
						int ex = x+dx[k];
						int ey = y+dy[k];
						if (ex<0 || ex>=n || ey<0 || ey>=m) continue;
						if (str[ex][ey] != str[x][y]) continue;
						if (block[ex][ey] != 0) continue;
						block[ex][ey] = block[i][j];
						que.offer(ex);
						que.offer(ey);
					}
				}
			}
		}

		for (int x = 0; x < n-1; ++ x) {
			for (int y = 0; y < m-1; ++ y) {
				if (str[x][y]==str[x][y+1]
						|| str[x][y+1]==str[x+1][y+1]
						|| str[x+1][y+1]==str[x+1][y]
						|| str[x+1][y]==str[x][y])
					continue;

				Dinic F = new Dinic(tot);
				for (int i = target+1; i < tot; i += 2) {
					F.addEdge(i,i+1,1);
				}
				for (int i = 0; i < 4; ++ i) {
					F.addEdge(n*m*2+i,target,1);
				}
				F.addEdge(source,block[x][y],1);
				F.addEdge(source,block[x][y+1],1);
				F.addEdge(source,block[x+1][y+1],1);
				F.addEdge(source,block[x+1][y],1);

				for (int i = 0; i < n; ++ i) {
					for (int j = 0; j < m; ++ j) {
						F.addEdge(i*m+j,block[i][j],1);
						F.addEdge(block[i][j]+1,i*m+j+n*m,1);
						for (int k = 0; k < 4; ++ k) {
							int ei = i+dx[k];
							int ej = j+dy[k];
							if (ei == -1) {
								F.addEdge(i*m+j+n*m,n*m*2,1);
							} else if (ei == n) {
								F.addEdge(i*m+j+n*m,n*m*2+1,1);
							} else if (ej == -1) {
								F.addEdge(i*m+j+n*m,n*m*2+2,1);
							} else if (ej == m) {
								F.addEdge(i*m+j+n*m,n*m*2+3,1);
							} else if (block[i][j] != block[ei][ej]) {
								F.addEdge(i*m+j+n*m,ei*m+ej,1);
							}
						}
						for (int k = 4; k < 8; ++ k) {
							int ei = i+dx[k];
							int ej = j+dy[k];
							if (ei<0 || ei>=n || ej<0 || ej>=m) continue;
							if (block[i][j] != block[ei][ej])
								F.addEdge(i*m+j+n*m,ei*m+ej,1);
						}
					}
				}

				if (F.run(source,target) == 4) {
					return "invalid";
				}
			}
		}
		return "valid";
	}

	class Dinic {
		class Edge {
			int to,cap;
			Edge rev;
			Edge(int to,int cap) {
				this.to = to;
				this.cap = cap;
			}
		}

		Dinic(int n) {
			dis = new int[n];
			edges = new ArrayList[n];
			for (int i = 0; i < n; ++ i)
				edges[i] = new ArrayList<Edge>();
		}

		void addEdge(int from,int to,int cap) {
			Edge e = new Edge(to,cap);
			Edge ee = new Edge(from,0);
			e.rev = ee;
			ee.rev = e;
			edges[from].add(e);
			edges[to].add(ee);
		}

		boolean bfs() {
			Queue<Integer> que = new LinkedList<Integer>();
			que.offer(target);
			Arrays.fill(dis,-1);
			dis[target] = dis.length;
			while (que.peek() != null) {
				int u = que.poll();
				for (Edge e : edges[u]) {
					if (e.rev.cap>0 && dis[e.to]==-1) {
						dis[e.to] = dis[u]-1;
						que.offer(e.to);
					}
				}
			}
			return dis[source]!=-1;
		}

		int dfs(int u,int a) {
			if (u == target) return a;
			int flow = 0,f;
			for (Edge e : edges[u]) {
				if (e.cap>0 && dis[e.to]>dis[u]) {
					f = dfs(e.to,Math.min(e.cap,a));
					flow += f;
					e.cap -= f;
					e.rev.cap += f;
					a -= f;
					if (a == 0) break;
				}
			}
			if (flow == 0) dis[u] = -1;
			return flow;
		}

		int run(int source,int target) {
			this.source = source;
			this.target = target;
			int flow = 0;
			while (bfs()) flow += dfs(source,Integer.MAX_VALUE);
			return flow;
		}

		ArrayList<Edge>[] edges;
		int source;
		int target;
		int[] dis;
	}

// CUT begin
	public static void main(String[] args){
		System.err.println("ConnectingGame (1000 Points)");
		System.err.println();
		HashSet<Integer> cases = new HashSet<Integer>();
        for (int i = 0; i < args.length; ++i) cases.add(Integer.parseInt(args[i]));
        runTest(cases);
	}

	static void runTest(HashSet<Integer> caseSet) {
	    int cases = 0, passed = 0;
	    while (true) {
	    	String label = Reader.nextLine();
	    	if (label == null || !label.startsWith("--"))
	    		break;

            String[] board = new String[Integer.parseInt(Reader.nextLine())];
            for (int i = 0; i < board.length; ++i)
                board[i] = Reader.nextLine();
            Reader.nextLine();
            String __answer = Reader.nextLine();

            cases++;
            if (caseSet.size() > 0 && !caseSet.contains(cases - 1))
                continue;
    		System.err.print(String.format("  Testcase #%d ... ", cases - 1));

            if (doTest(board, __answer))
                passed++;
	    }
	    if (caseSet.size() > 0) cases = caseSet.size();
        System.err.println(String.format("%nPassed : %d/%d cases", passed, cases));

        int T = (int)(System.currentTimeMillis() / 1000) - 1416827793;
        double PT = T / 60.0, TT = 75.0;
        System.err.println(String.format("Time   : %d minutes %d secs%nScore  : %.2f points", T / 60, T % 60, 1000 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT))));
	}

	static boolean doTest(String[] board, String __expected) {
		for (int i = 0; i < board.length; i++) {
			board[i] = new String(board[i]);
		}
		long startTime = System.currentTimeMillis();
		Throwable exception = null;
		ConnectingGame instance = new ConnectingGame();
		String __result = "";
		try {
			__result = instance.isValid(board);
		}
		catch (Throwable e) { exception = e; }
		double elapsed = (System.currentTimeMillis() - startTime) / 1000.0;

		if (exception != null) {
			System.err.println("RUNTIME ERROR!");
			exception.printStackTrace();
			return false;
		}
		else if (__expected.equals(__result)) {
			System.err.println("PASSED! " + String.format("(%.2f seconds)", elapsed));
			return true;
		}
		else {
			System.err.println("FAILED! " + String.format("(%.2f seconds)", elapsed));
			System.err.println("           Expected: " + "\"" + __expected + "\"");
			System.err.println("           Received: " + "\"" + __result + "\"");
			return false;
		}
	}

	static class Reader {
        private static final String dataFileName = "ConnectingGame.sample";
	    private static BufferedReader reader;

	    public static String nextLine() {
	        try {
                if (reader == null) {
                    reader = new BufferedReader(new InputStreamReader(new FileInputStream(dataFileName)));
                }
                return reader.readLine();
	        }
	        catch (IOException e) {
	            System.err.println("FATAL!! IOException");
	            e.printStackTrace();
	            System.exit(1);
	        }
	        return "";
	    }
	}
// CUT end
}
