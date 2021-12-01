// https://en.wikipedia.org/wiki/Dancing_Links
// Given a 0/1 matrix, select a group of rows so that every column is exactly covered for once.
struct DancingLinks {
 public:
  explicit DancingLinks(int num_columns) : num_columns(num_columns), num_selected_nodes_in_column(num_columns + 1, 0) {
    for (int i = 0; i <= num_columns; ++i) {
      int u = allocate_node();
      --L[u];
      ++R[u];
    }
    L[0] = num_columns;
    R[num_columns] = 0;
  }

  // Note: The column 0 is preserved, do not use it in building contraints.
  // Which means contraints are labeled as 1, 2, .., num_columns.
  // But for row_label, it can be anything you like.
  void add_row(int r, const std::vector<int>& line) {
    int first = num_nodes;
    for (int c : line) {
      int u = allocate_node();
      --L[u];
      ++R[u];
      U[u] = U[c];
      D[u] = c;
      D[U[c]] = u;
      U[c] = u;
      row_label[u] = r;
      col_label[u] = c;
      ++num_selected_nodes_in_column[c];
    }
    R[num_nodes - 1] = first;
    L[first] = num_nodes - 1;
  }

  bool solve(std::vector<int>& result) {
    result.clear();
    if (!dfs(0, result)) return false;
    return true;
  }

private:
  int allocate_node() {
    int u = num_nodes++;
    L.emplace_back(u);
    R.emplace_back(u);
    U.emplace_back(u);
    D.emplace_back(u);
    row_label.emplace_back();
    col_label.emplace_back();
    return u;
  }

#define FOR_CHAIN(i, A, s) for (int i = A[s]; i != s; i = A[i])
  void remove(int c) {
    L[R[c]] = L[c];
    R[L[c]] = R[c];
    FOR_CHAIN(i, D, c) FOR_CHAIN(j, R, i) U[D[j]] = U[j], D[U[j]] = D[j], --num_selected_nodes_in_column[col_label[j]];
  }
  void restore(int c) {
    FOR_CHAIN(i, U, c) FOR_CHAIN(j,L,i) U[D[j]] = j, D[U[j]] = j, ++num_selected_nodes_in_column[col_label[j]];
    R[L[c]] = c;
    L[R[c]] = c;
  }
  bool dfs(int dep, std::vector<int>& selected_row_labels) {
    if (R[0] == 0) return true;

    int c = R[0];
    FOR_CHAIN(i, R, 0) if (num_selected_nodes_in_column[i] < num_selected_nodes_in_column[c]) c = i;

    remove(c);
    FOR_CHAIN(i, D, c) {
      selected_row_labels.emplace_back(row_label[i]);
      FOR_CHAIN(j, R, i) remove(col_label[j]);
      if (dfs(dep + 1, selected_row_labels)) return true;
      FOR_CHAIN(j, L, i) restore(col_label[j]);
      selected_row_labels.pop_back();
    }
    restore(c);

    return false;
  }
#undef FOR_CHAIN

  int num_columns = 0;
  std::vector<int> num_selected_nodes_in_column;

  int num_nodes = 0;
  std::vector<int> L, R, U, D;  // Orthogonal linked list.
  std::vector<int> row_label, col_label;  // row/column label of each node.
};

