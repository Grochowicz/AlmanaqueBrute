#include <bits/stdc++.h>
using namespace std;

typedef vector <int> vi;

vi tin, tout;
vector <vi> adj, st;

int n, me, timer;

void et_dfs(int u, int p) {
    tin[u] = ++timer;

    st[u][0] = p;
    for (int i = 1; i <= me; i++)
        st[u][i] = st[st[u][i-1]][i-1];

    for (int v : adj[u]) 
        if (v != p)
            et_dfs(v, u);

    tout[u] = ++timer;
}

void build(int root=0) {
    tin.assign(n, 0);
    tout.assign(n, 0);
    timer = 0;
    me = floor(log2(n));
    st.assign(n, vi(me+1, 0));
    et_dfs(root, root);
}

bool is_ancestor(int u, int v) {
    return tin[u] <= tin[v] && tout[u] >= tout[v];
}

int lca(int u, int v) {
    if (is_ancestor(u, v)) return u;
    if (is_ancestor(v, u)) return v;
    for (int i = me; i >= 0; i--)
        if (!is_ancestor(st[u][i], v))
            u = st[u][i];
    return st[u][0];
}

// k-th ancestor of u 
int ancestor(int u, int k) {
    for (int i = me; i >= 0; i--)
        if ((1 << i) & k)
            u = st[u][i];
    return u;
}

int main() {
    cin >> n;

    adj.assign(n, vi(0));

    for (int i = 0; i < n-1; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    build();
}