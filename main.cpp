#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 100005;

int head[MAXN];
int to[MAXN * 2];
int nxt[MAXN * 2];
int edge_cnt = 0;

void add_edge(int u, int v) {
    to[++edge_cnt] = v;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
}

int parent_node[MAXN];
int order[MAXN];
int sz[MAXN];
int max_comp[MAXN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    if (!(cin >> n >> k)) return 0;

    for (int i = 1; i <= n; ++i) {
        head[i] = 0;
        parent_node[i] = 0;
    }

    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        add_edge(u, v);
        add_edge(v, u);
    }

    int head_q = 0, tail_q = 0;
    order[tail_q++] = 1;
    parent_node[1] = -1; // Mark as visited

    while (head_q < tail_q) {
        int u = order[head_q++];
        for (int e = head[u]; e; e = nxt[e]) {
            int v = to[e];
            if (parent_node[v] == 0) {
                parent_node[v] = u;
                order[tail_q++] = v;
            }
        }
    }

    parent_node[1] = 0; // Restore parent of root to 0

    for (int i = 1; i <= n; ++i) {
        sz[i] = 1;
        max_comp[i] = 0;
    }

    for (int i = n - 1; i >= 0; --i) {
        int u = order[i];
        int p = parent_node[u];
        if (p != 0) {
            sz[p] += sz[u];
            if (sz[u] > max_comp[p]) {
                max_comp[p] = sz[u];
            }
        }
    }

    bool found = false;
    bool first = true;
    for (int u = n; u >= 1; --u) {
        int comp_parent = n - sz[u];
        int current_max_comp = max_comp[u] > comp_parent ? max_comp[u] : comp_parent;
        if (current_max_comp <= k) {
            if (!first) cout << " ";
            cout << u;
            first = false;
            found = true;
        }
    }

    if (!found) {
        cout << "None\n";
    } else {
        cout << "\n";
    }

    return 0;
}