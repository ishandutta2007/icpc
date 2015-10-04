import java.io.*;
import java.math.BigInteger;
import java.util.*;

public class F {

	FastScanner in;
	PrintWriter out;

	int n;

	BigInteger[][] ans = new BigInteger[14][301];

	class Partition {
		ArrayList<Integer> a;

		public Partition(ArrayList<Integer> a) {
			super();
			this.a = a;
		}

		@Override
		public String toString() {
			return "Partition [a=" + a + "]";
		}

	}

	ArrayList<Partition> allPartition;
	ArrayList<Integer> curPart = new ArrayList<>();

	void go(int need, int max) {
		if (need == 0) {
			allPartition.add(new Partition(new ArrayList<Integer>(curPart)));
		} else {
			for (int next = Math.min(need, max); next >= 1; next--) {
				curPart.add(next);
				go(need - next, next);
				curPart.remove(curPart.size() - 1);
			}
		}
	}

	void sol(int t) {
		allPartition = new ArrayList<>();
		go(n, n);
		int m = allPartition.size();
		// for (Partition p : allPartition)
		// System.err.println(p);
		ArrayList<Road>[] g = generateGraph();
		BigInteger[][] prob = new BigInteger[t + 1][m];

		for (int i = 0; i <= t; i++)
			for (int j = 0; j < m; j++)
				prob[i][j] = BigInteger.ZERO;
		prob[0][m - 1] = BigInteger.ONE;

		ans[n - 1][0] = BigInteger.ONE;
		for (int i = 0; i < t; i++) {
			for (int now = 0; now < m; now++) {
				for (Road r : g[now]) {
					BigInteger addPr = r.prob.multiply(prob[i][now]);
					prob[i + 1][r.to] = prob[i + 1][r.to].add(addPr);
				}
			}
			ans[n - 1][i + 1] = prob[i + 1][m - 1];
		}

//		BigInteger denom = BigInteger.valueOf(n).pow(2 * t);
//		BigInteger num = prob[t][m - 1];
//		BigInteger gcd = denom.gcd(num);
//		num = num.divide(gcd);
//		denom = denom.divide(gcd);
//		out.println(num + "/" + denom);
	}

	class Road {
		int to;
		BigInteger prob;

		public Road(int to, BigInteger prob) {
			super();
			this.to = to;
			this.prob = prob;
		}
	}

	ArrayList<Road>[] generateGraph() {
		int m = allPartition.size();
		ArrayList<Road>[] res = new ArrayList[m];
		for (int i = 0; i < m; i++) {
			BigInteger[] nextPr = new BigInteger[m];
			for (int j = 0; j < m; j++)
				nextPr[j] = BigInteger.ZERO;
			int[] curPart = generatePartition(allPartition.get(i).a);
			for (int ch1 = 0; ch1 < n; ch1++)
				for (int ch2 = 0; ch2 < n; ch2++) {
					int tmp = curPart[ch1];
					curPart[ch1] = curPart[ch2];
					curPart[ch2] = tmp;

					// ttt++;

					int partId = findPartition(curPart);
					nextPr[partId] = nextPr[partId].add(BigInteger.ONE);

					tmp = curPart[ch1];
					curPart[ch1] = curPart[ch2];
					curPart[ch2] = tmp;
				}
			ArrayList<Road> roads = new ArrayList<>();
			for (int j = 0; j < m; j++)
				if (!nextPr[j].equals(BigInteger.ZERO))
					roads.add(new Road(j, nextPr[j]));
			res[i] = roads;
		}
		return res;
	}

	int[] generatePartition(ArrayList<Integer> x) {
		int[] res = new int[n];
		int now = 0;
		for (int cur : x) {
			for (int i = 0; i < cur; i++) {
				res[i + now] = i + now + 1;
			}
			res[cur + now - 1] = now;
			now += cur;
		}
		return res;
	}

	int findPartition(int[] next) {
		boolean[] was = new boolean[n];
		ArrayList<Integer> currentPart = new ArrayList<>();
		for (int i = 0; i < n; i++) {
			if (!was[i]) {
				int curSum = 0;
				int cur = i;
				while (!was[next[cur]]) {
					curSum++;
					cur = next[cur];
					was[cur] = true;
				}
				currentPart.add(curSum);
			}
		}
		Collections.sort(currentPart);
		Collections.reverse(currentPart);
		for (int i = 0; i < allPartition.size(); i++)
			if (sameArrayLists(allPartition.get(i).a, currentPart))
				return i;
		return -1;
	}

	boolean sameArrayLists(ArrayList<Integer> one, ArrayList<Integer> two) {
		if (one.size() != two.size())
			return false;
		for (int i = 0; i < one.size(); i++)
			if (one.get(i) != two.get(i))
				return false;
		return true;
	}

	void init() {
		for (int i = 1; i <= 14; i++) {
			this.n = i;
			sol(300);
		}
	}
	
	void print(int n, int t) {
		BigInteger denom = BigInteger.valueOf(n).pow(2 * t);
		BigInteger num = ans[n - 1][t];
		BigInteger gcd = denom.gcd(num);
		num = num.divide(gcd);
		denom = denom.divide(gcd);
		for (int i = 1; i <= n; i++)
			out.print(i + " ");
		out.println();
		out.println(num + "/" + denom);
	}

	void solve() throws Exception {
		init();
		while (true) {
			n = in.nextInt();
			int t = in.nextInt();
			if (n == 0)
				return;
			print(n, t);
		}
	}

	void run() {
		try {
			in = new FastScanner("frequent.in");
			out = new PrintWriter("frequent.out");
			solve();
			out.close();
		} catch (Exception e) {
			e.printStackTrace();
			System.exit(1);
		}
	}

	class FastScanner {
		BufferedReader br;
		StringTokenizer st;

		public FastScanner(String s) {
			try {
				br = new BufferedReader(new FileReader(s));
			} catch (FileNotFoundException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}

		public FastScanner() {
			br = new BufferedReader(new InputStreamReader(System.in));
		}

		String nextToken() {
			while (st == null || !st.hasMoreElements()) {
				try {
					st = new StringTokenizer(br.readLine());
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
			return st.nextToken();
		}

		int nextInt() {
			return Integer.parseInt(nextToken());
		}

		long nextLong() {
			return Long.parseLong(nextToken());
		}

		double nextDouble() {
			return Double.parseDouble(nextToken());
		}
	}

	public static void main(String[] args) {
		new F().run();
	}
}
