import java.util.*;
import java.io.*;

public class Main {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        PrintWriter out = new PrintWriter(System.out);
        int n = in.nextInt();
        long matrix[][] = new long[n][n];
        long sum = 0;
        long slop = 0;
        for (int i = 0; i < n; ++ i) {
            long tmp = 0;
            for (int j = 0; j < n; ++ j) {
                matrix[i][j] = in.nextLong();
                tmp += matrix[i][j];
            }
            if (i == 0) {
                sum = tmp;
            } else {
                matrix[i][i] = sum - tmp;
                slop += sum - tmp;
            }
        }
        if (n == 1) {
            // 
        } else {
            long x = (sum - slop) / (n - 1);
            for (int i = 0; i < n; ++ i)
                matrix[i][i] += x;
        }
        for (int i = 0; i < n; ++ i) {
            for (int j = 0; j < n; ++ j) {
                if (j > 0) out.print(' ');
                out.print(matrix[i][j]);
            }
            out.println();
        }
        in.close();
        out.close();
    }
}
