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
const ld EPS = 1e-12;

const int LEFT = 0, RIGHT = 1, BACK = 2, FRONT = 3, ON = 4, IN = 5, OUT = 6;

ll dot(PT a, PT b)
{
    return a.X * b.X + a.Y * b.Y;
}

ll cross(PT a, PT b)
{
    return a.X * b.Y - a.Y * b.X;
}

PT operator-(PT a, PT b)
{
    return PT(a.X - b.X, a.Y - b.Y);
}

int relpos(PT a, PT b, PT c)
{
    b = b - a, c = c - a;
    ll Imag = cross(b, c);
    if (Imag > 0)
        return LEFT;
    if (Imag < 0)
        return RIGHT;
    ll bc = dot(b, c), bb = dot(b, b);
    if (bc < 0 && bb > 0 || bc > 0 && bb < 0)
        return BACK;
    if (bc > bb)
        return FRONT;
    return ON;
}

int side(PT a, PT b, PT c)
{
    b = b - a, c = c - a;
    ll cr = cross(b, c);
    return cr > 0 ? 1 : (cr < 0 ? -1 : 0);
}

// If LineSegments Intersect
bool intersect(PT a, PT b, PT c, PT d)
{
    int as = side(c, d, a), bs = side(c, d, b),
        cs = side(a, b, c), ds = side(a, b, d);
    if (as && as == bs || cs && cs == ds)
        return false;
    else if (as || bs || cs || ds)
        return true;
    for (int j = 0; j < 2; j++, swap(a, c), swap(b, d))
    {
        ll mx = min(a.X, b.X), Mx = max(a.X, b.X),
           my = min(a.Y, b.Y), My = max(a.Y, b.Y);
        for (int k = 0; k < 2; k++, swap(c, d))
            if ((c.X >= mx) && (c.X <= Mx) && (c.Y >= my) && (c.Y <= My))
                return true;
    }
    return false;
}

int crossingN(Poly& po, PT a)
{
    int cn = 0;
    ll mx = 1e9;
    PT b(mx, a.Y);
    int n = po.size();
    for (int i = 0; i < n; i++)
    {
        PT p = po[i], q = po[(i + 1) % n];
        if (intersect(a, b, p, q) && (side(a, b, p) == 1 ||
                                side(a, b, q) == 1))
            cn++;
    }
    return cn;
}

int pointInPoly(Poly& po, PT a)
{
    int n = po.size();
    for (int i = 0; i < n; i++)
        if (relpos(po[i], po[(i + 1) % n], a) == ON)
            return ON;
    return (crossingN(po, a) % 2 ? IN : OUT);
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
    for (int i = in(); i; i--)
    {
        PT p;
        cin >> p.X >> p.Y;
        int s = pointInPoly(poly, p);
        cout << (s == IN ? 2 : (s == ON ? 1 : 0)) << endl;
    }
    clock_t allClock = clock() - start;
    cerr << "OverallTime: " << allClock / (ld)CLOCKS_PER_SEC << endl;
    return 0;
}
