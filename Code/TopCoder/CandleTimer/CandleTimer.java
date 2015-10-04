import java.io.*;
import java.util.*;

public class CandleTimer {
	public int differentTime(int[] A, int[] B, int[] len) {
		int n = A.length+1;
		int[] degree = new int[n];
		int[][] G = new int[n][n];
		ArrayList<Edge>[] edges = new ArrayList[n];
		for (int i = 0; i < n; ++ i) {
			edges[i] = new ArrayList<Edge>();
		}
		for (int i = 0; i < n; ++ i) {
			for (int j = 0; j < n; ++ j) {
				G[i][j] = (i==j) ? 0 : INF;
			}
		}
		for (int i = 0; i < n-1; ++ i) {
			int a = A[i];
			int b = B[i];
			int c = len[i]<<1;
			degree[a] ++;
			degree[b] ++;
			G[a][b] = G[b][a] = c;
			edges[a].add(new Edge(b,c));
			edges[b].add(new Edge(a,c));
		}

		// floyd
		for (int k = 0; k < n; ++ k) {
			for (int i = 0; i < n; ++ i) {
				for (int j = 0; j < n; ++ j) {
					G[i][j] = Math.min(G[i][j],G[i][k]+G[k][j]);
				}
			}
		}

		Set<Integer> set = new TreeSet<Integer>();
		int[] dis = new int[n];

		for (int i = 0; i < n; ++ i) {
			if (degree[i] != 1) continue;
			for (int j = 0; j < n; ++ j) {
				if (degree[j]!=1 || i==j) continue;
				Arrays.fill(dis,-1);
				for (int k = 0; k < n; ++ k) {
					if (degree[k] != 1) continue;
					if (G[k][j] >= G[i][j])
						dis[k] = G[i][j];
				}
				if (spfa(dis,edges)) {
					set.add(G[i][j]);
				}
			}

			for (int j = 0; j < n; ++ j) {
				if (degree[j]!=1 || i==j) continue;
				Arrays.fill(dis,-1);
				int p = -1,mp = -1,q = -1,mq = -1;
				for (int k = 0; k < n; ++ k) {
					if (G[i][k]+G[k][j] != G[i][j]) continue;
					if (G[i][k]<= G[k][j] && mp < G[i][k]) {
						p = k;
						mp = G[i][k];
					}
					if (G[k][j] <= G[i][k] && mq < G[k][j]) {
						q = k;
						mq = G[k][j];
					}
				}
				for (int k = 0; k < n; ++ k) {
					if (degree[k] != 1) continue;
					if (G[i][k] <= G[k][j]) {
						if (G[k][p] >= G[i][p])
							dis[k] = G[i][j]>>1;
					} else {
						if (G[k][q] >= G[j][q])
							dis[k] = G[i][j]>>1;
					}
				}
				if (spfa(dis,edges)) {
					set.add(G[i][j]>>1);
				}
			}
		}

		return set.size();

	}

	boolean spfa(int[] dis,ArrayList<Edge>[] edges) {
		Queue<Integer> que = new LinkedList<Integer>();
		boolean[] inq = new boolean[dis.length];
		for (int i = 0; i < dis.length; ++ i) {
			if (dis[i] > 0) {
				que.offer(i);
				inq[i] = true;
			}
		}
		while (que.peek() != null) {
			int u = que.poll();
			inq[u] = false;
			for (Edge e : edges[u]) {
				if (dis[u]-e.cost > dis[e.to]) {
					dis[e.to] = dis[u]-e.cost;
					if (!inq[e.to]) {
						que.offer(e.to);
						inq[e.to] = true;
					}
				}
			}
		}
		for (int x : dis) {
			if (x < 0) return false;
		}
		for (int u = 0; u < dis.length; ++ u) {
			for (Edge e : edges[u]) {
				if (dis[u]+dis[e.to] < e.cost)
					return false;
			}
		}
		return true;
	}

	final int INF = 0x3f3f3f3f;

	class Edge {
		int to,cost;
		Edge(int to,int cost) {
			this.to = to;
			this.cost = cost;
		}
	}

	// CUT begin
	public static void main(String[] args){
		System.err.println("CandleTimer (800 Points)");
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

			int[] A = new int[Integer.parseInt(Reader.nextLine())];
			for (int i = 0; i < A.length; ++i)
				A[i] = Integer.parseInt(Reader.nextLine());
			int[] B = new int[Integer.parseInt(Reader.nextLine())];
			for (int i = 0; i < B.length; ++i)
				B[i] = Integer.parseInt(Reader.nextLine());
			int[] len = new int[Integer.parseInt(Reader.nextLine())];
			for (int i = 0; i < len.length; ++i)
				len[i] = Integer.parseInt(Reader.nextLine());
			Reader.nextLine();
			int __answer = Integer.parseInt(Reader.nextLine());

			cases++;
			if (caseSet.size() > 0 && !caseSet.contains(cases - 1))
				continue;
			System.err.print(String.format("  Testcase #%d ... ", cases - 1));

			if (doTest(A, B, len, __answer))
				passed++;
		}
		if (caseSet.size() > 0) cases = caseSet.size();
		System.err.println(String.format("%nPassed : %d/%d cases", passed, cases));

		int T = (int)(System.currentTimeMillis() / 1000) - 1415893120;
		double PT = T / 60.0, TT = 75.0;
		System.err.println(String.format("Time   : %d minutes %d secs%nScore  : %.2f points", T / 60, T % 60, 800 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT))));
	}

	static boolean doTest(int[] A, int[] B, int[] len, int __expected) {
		long startTime = System.currentTimeMillis();
		Throwable exception = null;
		CandleTimer instance = new CandleTimer();
		int __result = 0;
		try {
			__result = instance.differentTime(A, B, len);
		}
		catch (Throwable e) { exception = e; }
		double elapsed = (System.currentTimeMillis() - startTime) / 1000.0;

		if (exception != null) {
			System.err.println("RUNTIME ERROR!");
			exception.printStackTrace();
			return false;
		}
		else if (__result == __expected) {
			System.err.println("PASSED! " + String.format("(%.2f seconds)", elapsed));
			return true;
		}
		else {
			System.err.println("FAILED! " + String.format("(%.2f seconds)", elapsed));
			System.err.println("           Expected: " + __expected);
			System.err.println("           Rece.toed: " + __result);
			return false;
		}
	}

	static class Reader {
		private static final String dataFileName = "CandleTimer.sample";
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
