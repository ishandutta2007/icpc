import java.io.*;
import java.util.*;

public class TaroCutting {
	public int getNumber(int[] height, int[] add, int[] device, int time) {
		int n = height.length;
		int m = device.length;
		int source = n+time+m;
		int target = source+1;
		CostFlow F = new CostFlow(n+time+m+2);
		for (int i = 0; i < n; ++ i) {
			F.addEdge(source,i,1,0);
			F.addEdge(i,target,1,height[i]+add[i]*time);
		}
		for (int k = 0; k < time; ++ k) {
			for (int i = 0; i < n; ++ i) {
				F.addEdge(i,n+k,1,(time-k-1)*add[i]);
			}
			for (int i = 0; i < m; ++ i) {
				F.addEdge(n+k,n+time+i,1,0);
			}
		}
		for (int i = 0; i < m; ++ i) {
			F.addEdge(n+time+i,target,time,device[i]);
		}
		F.run(source,target);
		return F.cost;
	}

	class CostFlow {
		class Edge {
			int to,cost,cap;
			Edge rev;
			Edge() {
			}
			Edge(int to,int cost,int cap) {
				this.to = to;
				this.cost = cost;
				this.cap = cap;
			}
		}
		void addEdge(int from,int to,int cap,int cost) {
			Edge e = new Edge(to,cost,cap);
			Edge ee = new Edge(from,-cost,0);
			e.rev = ee;
			ee.rev = e;
			edges[from].add(e);
			edges[to].add(ee);
		}
		CostFlow(int n) {
			edges = new ArrayList[n];
			for (int i = 0; i < n; ++ i) {
				edges[i] = new ArrayList<Edge>();
			}
			dis = new int[n];
			prevv = new int[n];
			preve = new Edge[n];
			inq = new boolean[n];
		}
		void run(int source,int target) {
			flow = cost = 0;
			while (true) {
				Arrays.fill(dis,INF);
				dis[source] = 0;
				Queue<Integer> que = new LinkedList<Integer>();
				que.offer(source);
				while (que.peek() != null) {
					int u = que.poll();
					inq[u] = false;
					for (Edge e : edges[u]) {
						if (e.cap>0 && dis[e.to]>dis[u]+e.cost) {
							dis[e.to] = dis[u]+e.cost;
							prevv[e.to] = u;
							preve[e.to] = e;
							if (!inq[e.to]) {
								que.offer(e.to);
								inq[e.to] = true;
							}
						}
					}
				}
				if (dis[target] == INF) break;
				int f = INF;
				for (int u = target; u != source; u = prevv[u]) {
					f = Math.min(f,preve[u].cap);
				}
				for (int u = target; u != source; u = prevv[u]) {
					preve[u].cap -= f;
					preve[u].rev.cap += f;
				}
				flow += f;
				cost += f * dis[target];
			}
		}

		ArrayList<Edge>[] edges;
		int[] dis;
		int[] prevv;
		Edge[] preve;
		int flow,cost;
		boolean[] inq;
	}

	final int INF = Integer.MAX_VALUE;

// CUT begin
	public static void main(String[] args){
		System.err.println("TaroCutting (500 Points)");
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

            int[] height = new int[Integer.parseInt(Reader.nextLine())];
            for (int i = 0; i < height.length; ++i)
                height[i] = Integer.parseInt(Reader.nextLine());
            int[] add = new int[Integer.parseInt(Reader.nextLine())];
            for (int i = 0; i < add.length; ++i)
                add[i] = Integer.parseInt(Reader.nextLine());
            int[] device = new int[Integer.parseInt(Reader.nextLine())];
            for (int i = 0; i < device.length; ++i)
                device[i] = Integer.parseInt(Reader.nextLine());
            int time = Integer.parseInt(Reader.nextLine());
            Reader.nextLine();
            int __answer = Integer.parseInt(Reader.nextLine());

            cases++;
            if (caseSet.size() > 0 && !caseSet.contains(cases - 1))
                continue;
    		System.err.print(String.format("  Testcase #%d ... ", cases - 1));

            if (doTest(height, add, device, time, __answer))
                passed++;
	    }
	    if (caseSet.size() > 0) cases = caseSet.size();
        System.err.println(String.format("%nPassed : %d/%d cases", passed, cases));

        int T = (int)(System.currentTimeMillis() / 1000) - 1418782313;
        double PT = T / 60.0, TT = 75.0;
        System.err.println(String.format("Time   : %d minutes %d secs%nScore  : %.2f points", T / 60, T % 60, 500 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT))));
	}

	static boolean doTest(int[] height, int[] add, int[] device, int time, int __expected) {
		long startTime = System.currentTimeMillis();
		Throwable exception = null;
		TaroCutting instance = new TaroCutting();
		int __result = 0;
		try {
			__result = instance.getNumber(height, add, device, time);
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
        private static final String dataFileName = "TaroCutting.sample";
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
