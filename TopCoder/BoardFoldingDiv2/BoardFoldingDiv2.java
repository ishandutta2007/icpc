import java.io.*;
import java.util.*;

public class BoardFoldingDiv2 {
	public int howMany(String[] paper) {
		n = paper.length;
		m = paper[0].length();
		mat = new boolean[n][m];
		for (int i = 0; i < n; ++ i)
			for (int j = 0; j < m; ++ j)
				if (paper[i].charAt(j) == '1')
					mat[i][j] = true;
		int t = Math.max(n,m);
		left = new long[t][t][t];
		right = new long[t][t][t];
		up = new long[t][t][t];
		down = new long[t][t][t];
		make(0,0,n-1,m-1);
		row = new long[n][m];
		cor = new long[n][m];
		for (int i = 0; i < n; ++ i) {
			for (int j = 0; j < m; ++ j) {
				if (j != 0) {
					row[i][j] = row[i][j-1];
				}
				if (i != 0) {
					cor[i][j] = cor[i-1][j];
				}
				if (mat[i][j] == true) {
					row[i][j] |= 1l<<j;
					cor[i][j] |= 1l<<i;
				}
			}
		}
		u_d = new int[t][t][t];
		l_r = new int[t][t][t];
		for (int i = 0; i < n; ++ i) {
			for (int j = i; j < n; ++ j) {
				for (int k = 0; k < m; ++ k) {
					int p = 0,tp = 1;
					while (k-tp>=0 && k-1+tp<m) {
						if (get_cor(k-tp,i,j) != get_cor(k-1+tp,i,j)) break;
						p = tp ++;
					}
					l_r[k][i][j] = p;
				}
			}
		}
		for (int i = 0; i < m; ++ i) {
			for (int j = i; j < m; ++ j) {
				for (int k = 0; k < n; ++ k) {
					int p = 0,tp = 1;
					while (k-tp>=0 && k-1+tp<n) {
						if (get_row(k-tp,i,j) != get_row(k-1+tp,i,j)) break;
						p = tp ++;
					}
					u_d[k][i][j] = p;
				}
			}
		}
		int ret = 1;
		for (int i = n; i >= 1; -- i) {
			for (int j = m; j >= 1; -- j) {
				for (int ox = 0; ox+i-1 < n; ++ ox) {
					for (int oy = 0; oy+j-1 < m; ++ oy) {
						if (query_left(ox,oy,ox+i-1,oy+j-1)
								|| query_right(ox,oy,ox+i-1,oy+j-1)
								|| query_up(ox,oy,ox+i-1,oy+j-1)
								|| query_down(ox,oy,ox+i-1,oy+j-1)
						   ) {
							ret ++;
							make(ox,oy,ox+i-1,oy+j-1);
						}

					}
				}
			}
		}
		return ret;
	}

	boolean query_left(int x0,int y0,int x1,int y1) {
		if (y0 == 0) return false;
		int t = l_r[y0][x0][x1];
		int p = Math.max(y0-t,0);
		return ((left[x0][x1][y1]>>p)&(1l<<t)-1) != 0;
	}
	boolean query_right(int x0,int y0,int x1,int y1) {
		if (y1 == m-1) return false;
		int t = l_r[y1+1][x0][x1];
		int p = Math.min(m-1,y1+t);
		return ((right[x0][x1][y0]>>y1+1)&(1l<<t)-1) != 0;
	}
	boolean query_up(int x0,int y0,int x1,int y1) {
		if (x0 == 0) return false;
		int t = u_d[x0][y0][y1];
		int p = Math.max(x0-t,0);
		return ((up[y0][y1][x1]>>p)&(1l<<t)-1) != 0;
	}
	boolean query_down(int x0,int y0,int x1,int y1) {
		if (x1 == n-1) return false;
		int t = u_d[x1+1][y0][y1];
		int p = Math.min(n-1,x1+t);
		return ((down[y0][y1][x0]>>x1+1)&(1l<<t)-1) != 0;
	}
	long get_row(int x,int y0,int y1) {
		return row[x][y1]>>y0;
	}

	long get_cor(int y,int x0,int x1) {
		return cor[x1][y]>>x0;
	}

	void make(int x0,int y0,int x1,int y1) {
		left[x0][x1][y1] |= 1l<<y0;
		right[x0][x1][y0] |= 1l<<y1;
		up[y0][y1][x1] |= 1l<<x0;
		down[y0][y1][x0] |= 1l<<x1;
	}

	int[][][] u_d,l_r;
	long[][] row,cor;
	long[][][] left,right,up,down;
	boolean[][] mat;
	int n,m;

	// CUT begin
	public static void main(String[] args){
		System.err.println("BoardFoldingDiv2 (1000 Points)");
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

			String[] paper = new String[Integer.parseInt(Reader.nextLine())];
			for (int i = 0; i < paper.length; ++i)
				paper[i] = Reader.nextLine();
			Reader.nextLine();
			int __answer = Integer.parseInt(Reader.nextLine());

			cases++;
			if (caseSet.size() > 0 && !caseSet.contains(cases - 1))
				continue;
			System.err.print(String.format("  Testcase #%d ... ", cases - 1));

			if (doTest(paper, __answer))
				passed++;
		}
		if (caseSet.size() > 0) cases = caseSet.size();
		System.err.println(String.format("%nPassed : %d/%d cases", passed, cases));

		int T = (int)(System.currentTimeMillis() / 1000) - 1417176976;
		double PT = T / 60.0, TT = 75.0;
		System.err.println(String.format("Time   : %d minutes %d secs%nScore  : %.2f points", T / 60, T % 60, 1000 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT))));
	}

	static boolean doTest(String[] paper, int __expected) {
		for (int i = 0; i < paper.length; i++) {
			paper[i] = new String(paper[i]);
		}
		long startTime = System.currentTimeMillis();
		Throwable exception = null;
		BoardFoldingDiv2 instance = new BoardFoldingDiv2();
		int __result = 0;
		try {
			__result = instance.howMany(paper);
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
			System.err.println("           Received: " + __result);
			return false;
		}
	}

	static class Reader {
		private static final String dataFileName = "BoardFoldingDiv2.sample";
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
