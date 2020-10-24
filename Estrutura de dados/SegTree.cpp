typedef vector <int> vi;

vi tree;

int le(n) {return 2*n;}
int ri(n) {return 2*n+1;}

void build(int n, int esq, int dir, vi &v) {
    if (esq == dir) tree[n] = v[esq];
    else {
        int mid = (esq + dir) / 2;
        build(le(n), esq, mid, v);
        build(ri(n), mid+1, dir, v);
        tree[n] = tree[le(n)] + tree[ri(n)];
    }
}

int sum(int n, int esq, int dir, int l, int r) {
    if (esq > r || dir < l) return 0;
    if (l <= esq && dir <= r) return tree[n];
    int mid = (esq + dir) / 2;
    return sum(le(n), esq, mid, l, r)
           + sum(ri(n), mid+1, dir, l, r);
}

void update(int n, int esq, int dir, int x, int v) {
    if (esq == dir) tree[n] = v;
    else {
        int mid = (esq + dir) / 2;
        if (x <= mid)
            update(le(n), esq, mid, x, v);
        else
            update(ri(n), mid+1, dir, x, v);
        tree[n] = tree[le(n)] + tree[ri(n)];
    }
}

int main() {
    int n;
    cin >> n;
    tree.assign(n, 0);
}