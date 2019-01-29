// be naame khodaa
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> PT;
typedef pair<PT, PT> LS;
#define X first
#define Y second
#define pb push_back

struct Poly
{
    PT* p;
    int sz;
    Poly(int n)
    {
        p = new PT[n];
        sz = 0;
    }
    void pop_back()
    {
        sz--;
    }
    void push_back(PT pt)
    {
        p[sz++] = pt;
    }
    int size()
    {
        return sz;
    }
    PT& operator[](int x)
    {
        return p[x];
    }
};

inline int in()
{
    int x, y;
    y = scanf("%d", &x);
    return x;
}

const int N = -1;

const int LEFT = 0, RIGHT = 1;

bool cmpXY(PT a, PT b)
{
    if (a.X == b.X)
        return a.Y < b.Y;
    return a.X < b.X;
}

ll cross(PT a, PT b)
{
    return a.X * b.Y - a.Y * b.X;
}

PT operator-(PT a, PT b)
{
    return PT(a.X - b.X, a.Y - b.Y);
}

int side(PT a, PT b, PT c)
{
    b = b - a, c = c - a;
    ll cr = cross(b, c);
    return cr > 0 ? 1 : (cr < 0) ? -1 : 0;
}

Poly getHull(Poly& po, bool lower)
{
    sort(po.p, po.p + po.sz, cmpXY);
    Poly res(po.size());
    int n = res.size();
    for (int i = 0; i < po.size(); i++)
    {
        PT p = po.p[i];
        while (n >= 2 && side(res[n - 2],
                                res[n - 1], p) == (lower ? RIGHT : LEFT))
            res.pop_back(), n--;
        res.pb(p), n++;
    }
    return res;
}

Poly convexHull(Poly& po)
{
    int n = po.size();
    Poly lower = getHull(po, true), upper = getHull(po, false);
    Poly res(lower.size() + upper.size());
    for (int i = 0; i < lower.size(); i++)
        res.pb(lower[i]);
    for (int i = (int)upper.size() - 2; i; i--)
        res.pb(upper[i]);
    return res;
}

int main()
{
    clock_t start = clock();
    int n = in();
    Poly poly(n);
    for (int i = n; i; i--)
    {
        PT p;
        cin >> p.X >> p.Y;
        poly.pb(p);
    }
    Poly CH = convexHull(poly);
    int st = 0;
    for (int i = 0; i < CH.size(); i++)
        if (CH[i].Y < CH[st].Y || (CH[i].Y == CH[st].Y && CH[i].X < CH[st].X))
            st = i;
    int cur = st;
    cout << setprecision(0) << fixed;
    cout << CH.size() << endl;
    do
    {
        cout << CH[cur].X << ' ' << CH[cur].Y << '\n';
        cur = (cur + 1) % (CH.size());
    } while (cur != st);
    cerr << "OverallTime: " << (clock() - start) / (ld)CLOCKS_PER_SEC << endl;
    return 0;
}
