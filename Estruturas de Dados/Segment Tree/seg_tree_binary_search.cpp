namespace seg {
    const int MAX = 1e5+5;
    int n;
    ll tree[4*MAX];
    ll merge(ll a, ll b) { return max(a, b); }
    int le(int n) { return 2*n+1; }
    int ri(int n) { return 2*n+2; }
    void build(int n, int esq, int dir, const vector<ll> &v) {
        if (esq == dir) tree[n] = v[esq];
        else {
            int mid = (esq + dir) / 2;
            build(le(n), esq, mid, v);
            build(ri(n), mid+1, dir, v);
            tree[n] = merge(tree[le(n)], tree[ri(n)]);
        }
    }
    void build(const vector<ll> &v) { n = v.size(); build(0, 0, n-1, v); }
    // find fist index greater than k in [l, r]
    ll query(int n, int esq, int dir, int l, int r, ll k) {
        if(esq > r || dir < l) return -1;
        if(l <= esq && dir <= r) {
            if (tree[n] < k) return -1;
            while(esq != dir) {
                int mid = (esq + dir) / 2;
                if (tree[le(n)] >= k) n = le(n), dir = mid;
                else n = ri(n), esq = mid+1;
            }
            return esq;
        }
        int mid = (esq + dir) / 2;
        int res = query(le(n), esq, mid, l, r, k);
        if (res != -1) return res;
        return query(ri(n), mid+1, dir, l, r, k);
    }
    ll query(int l, int r, ll k) { return query(0, 0, n-1, l, r, k); }
    void update(int n, int esq, int dir, int x, ll v) {
        if (esq > x || dir < x) return;
        if (esq == dir) tree[n] = v;
        else {
            int mid = (esq + dir) / 2;
            if (x <= mid) update(le(n), esq, mid, x, v);
            else update(ri(n), mid+1, dir, x, v);
            tree[n] = merge(tree[le(n)], tree[ri(n)]);
        }
    }
    void update(int x, ll v) { update(0, 0, n-1, x, v); }
}
