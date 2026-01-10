#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

struct Player {
    int rating;
    string name;
    int hp;
    int height;
    int size;
    Player *left, *right;

    Player(int r, string n, int h)
        : rating(r), name(n), hp(h), height(0), size(1), left(nullptr), right(nullptr) {}
};

class ArenaTree {
private:
    Player* root;

    int height(Player* n) {
        return n ? n->height : -1;
    }

    int size(Player* n) {
        return n ? n->size : 0;
    }

    void update(Player* n) {
        if (n) {
            n->height = 1 + max(height(n->left), height(n->right));
            n->size = 1 + size(n->left) + size(n->right);
        }
    }

    int balance(Player* n) {
        return n ? height(n->left) - height(n->right) : 0;
    }

    Player* rotateRight(Player* y) {
        Player* x = y->left;
        Player* t = x->right;
        x->right = y;
        y->left = t;
        update(y);
        update(x);
        return x;
    }

    Player* rotateLeft(Player* x) {
        Player* y = x->right;
        Player* t = y->left;
        y->left = x;
        x->right = t;
        update(x);
        update(y);
        return y;
    }

    Player* rebalance(Player* n) {
        update(n);
        int b = balance(n);

        if (b > 1) {
            if (balance(n->left) < 0)
                n->left = rotateLeft(n->left);
            return rotateRight(n);
        }

        if (b < -1) {
            if (balance(n->right) > 0)
                n->right = rotateRight(n->right);
            return rotateLeft(n);
        }
        return n;
    }

    Player* insertNode(Player* n, int r, string name, int hp, bool &ok) {
        if (!n) {
            ok = true;
            return new Player(r, name, hp);
        }
        if (r < n->rating)
            n->left = insertNode(n->left, r, name, hp, ok);
        else if (r > n->rating)
            n->right = insertNode(n->right, r, name, hp, ok);
        else {
            ok = false;
            return n;
        }
        return rebalance(n);
    }

    Player* deleteNode(Player* n, int r, bool &ok) {
        if (!n) {
            ok = false;
            return nullptr;
        }
        if (r < n->rating)
            n->left = deleteNode(n->left, r, ok);
        else if (r > n->rating)
            n->right = deleteNode(n->right, r, ok);
        else {
            ok = true;
            if (!n->left || !n->right) {
                Player* temp = n->left ? n->left : n->right;
                delete n;
                return temp;
            } else {
                Player* s = n->right;
                while (s->left) s = s->left;
                n->rating = s->rating;
                n->name = s->name;
                n->hp = s->hp;
                n->right = deleteNode(n->right, s->rating, ok);
            }
        }
        return rebalance(n);
    }

    void rangePrint(Player* n, int l, int r, bool &found) {
        if (!n) return;
        if (n->rating > l) rangePrint(n->left, l, r, found);
        if (n->rating >= l && n->rating <= r) {
            cout << n->rating << " " << n->name << " " << n->hp << "\n";
            found = true;
        }
        if (n->rating < r) rangePrint(n->right, l, r, found);
    }

    int leafCount(Player* n) {
        if (!n) return 0;
        if (!n->left && !n->right) return 1;
        return leafCount(n->left) + leafCount(n->right);
    }

    Player* kth(Player* n, int k) {
        int ls = size(n->left);
        if (k == ls + 1) return n;
        if (k <= ls) return kth(n->left, k);
        return kth(n->right, k - ls - 1);
    }

    int depth(Player* n, int r, int d) {
        if (!n) return -1;
        if (n->rating == r) return d;
        if (r < n->rating) return depth(n->left, r, d + 1);
        return depth(n->right, r, d + 1);
    }

    Player* lca(Player* n, int a, int b) {
        if (!n) return nullptr;
        if (a < n->rating && b < n->rating) return lca(n->left, a, b);
        if (a > n->rating && b > n->rating) return lca(n->right, a, b);
        return n;
    }

public:
    ArenaTree() : root(nullptr) {}

    void JOIN(int r, string n, int h) {
        bool ok = false;
        root = insertNode(root, r, n, h, ok);
        cout << (ok ? "JOINED\n" : "DUPLICATE\n");
    }

    void LEAVE(int r) {
        bool ok = false;
        root = deleteNode(root, r, ok);
        cout << (ok ? "LEFT\n" : "NOT FOUND\n");
    }

    void STATUS(int r) {
        Player* c = root;
        while (c) {
            if (c->rating == r) {
                cout << c->rating << " " << c->name << " " << c->hp << "\n";
                return;
            }
            c = (r < c->rating) ? c->left : c->right;
        }
        cout << "NOT FOUND\n";
    }

    void DAMAGE(int r, int a) {
        Player* c = root;
        while (c) {
            if (c->rating == r) {
                c->hp = max(0, c->hp - a);
                cout << "DAMAGED " << c->hp << "\n";
                return;
            }
            c = (r < c->rating) ? c->left : c->right;
        }
        cout << "NOT FOUND\n";
    }

    void HEAL(int r, int a) {
        Player* c = root;
        while (c) {
            if (c->rating == r) {
                c->hp += a;
                cout << "HEALED " << c->hp << "\n";
                return;
            }
            c = (r < c->rating) ? c->left : c->right;
        }
        cout << "NOT FOUND\n";
    }

    Player* neighbor(int x, bool next) {
        Player* res = nullptr;
        Player* c = root;
        while (c) {
            if (next) {
                if (c->rating > x) { res = c; c = c->left; }
                else c = c->right;
            } else {
                if (c->rating < x) { res = c; c = c->right; }
                else c = c->left;
            }
        }
        return res;
    }

    void RANGE(int l, int r) {
        bool found = false;
        rangePrint(root, l, r, found);
        if (!found) cout << "EMPTY\n";
    }

    void RANK(int x) {
        int cnt = 0;
        Player* c = root;
        while (c) {
            if (x > c->rating) {
                cnt += size(c->left) + 1;
                c = c->right;
            } else c = c->left;
        }
        cout << cnt << "\n";
    }

    void KTH(int k) {
        if (k < 1 || k > size(root)) cout << "OUT_OF_RANGE\n";
        else {
            Player* p = kth(root, k);
            cout << p->rating << " " << p->name << " " << p->hp << "\n";
        }
    }

    void DUEL(int a, int b) {
        Player* A = nullptr;
        Player* B = nullptr;
        Player* c = root;

        while (c) {
            if (c->rating == a) { A = c; break; }
            c = (a < c->rating) ? c->left : c->right;
        }
        c = root;
        while (c) {
            if (c->rating == b) { B = c; break; }
            c = (b < c->rating) ? c->left : c->right;
        }

        if (!A || !B) cout << "NOT_FOUND\n";
        else {
            Player* L = lca(root, a, b);
            int d = depth(root, a, 0) + depth(root, b, 0) - 2 * depth(root, L->rating, 0);
            cout << "DIST " << d << "\n";
        }
    }

    void STATS() {
        cout << "PLAYERS " << size(root) << "\n";
        if (!root) {
            cout << "MIN NONE\nMAX NONE\n";
        } else {
            Player* mn = root;
            while (mn->left) mn = mn->left;
            Player* mx = root;
            while (mx->right) mx = mx->right;
            cout << "MIN " << mn->rating << "\n";
            cout << "MAX " << mx->rating << "\n";
        }
        cout << "HEIGHT " << height(root) << "\n";
        cout << "LEAVES " << leafCount(root) << "\n";
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ArenaTree arena;
    int Q;
    cin >> Q;

    while (Q--) {
        string cmd;
        cin >> cmd;

        if (cmd == "JOIN") {
            int r, h; string n;
            cin >> r >> n >> h;
            arena.JOIN(r, n, h);
        } else if (cmd == "LEAVE") {
            int r; cin >> r;
            arena.LEAVE(r);
        } else if (cmd == "STATUS") {
            int r; cin >> r;
            arena.STATUS(r);
        } else if (cmd == "DAMAGE") {
            int r, a; cin >> r >> a;
            arena.DAMAGE(r, a);
        } else if (cmd == "HEAL") {
            int r, a; cin >> r >> a;
            arena.HEAL(r, a);
        } else if (cmd == "NEXT") {
            int x; cin >> x;
            Player* p = arena.neighbor(x, true);
            if (p) cout << p->rating << " " << p->name << " " << p->hp << "\n";
            else cout << "NONE\n";
        } else if (cmd == "PREV") {
            int x; cin >> x;
            Player* p = arena.neighbor(x, false);
            if (p) cout << p->rating << " " << p->name << " " << p->hp << "\n";
            else cout << "NONE\n";
        } else if (cmd == "RANGE") {
            int l, r; cin >> l >> r;
            arena.RANGE(l, r);
        } else if (cmd == "RANK") {
            int x; cin >> x;
            arena.RANK(x);
        } else if (cmd == "KTH") {
            int k; cin >> k;
            arena.KTH(k);
        } else if (cmd == "DUEL") {
            int a, b; cin >> a >> b;
            arena.DUEL(a, b);
        } else if (cmd == "STATS") {
            arena.STATS();
        }
    }
    return 0;
}
