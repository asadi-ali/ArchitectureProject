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

inline int in()
{
    int x, y;
    y = scanf("%d", &x);
    return x;
}

const int N = -1;

PT operator-(PT a, PT b)
{
    return PT(a.X - b.X, a.Y - b.Y);
}

PT operator*(ll c, PT p)
{
    return PT(c * p.X, c * p.Y);
}

ll cross(PT a, PT b)
{
    return a.X * b.Y - a.Y * b.X;
}

int side(PT a, PT b, PT c)
{
    b = b - a, c = c - a;
    ll cr = cross(b, c);
    return cr > 0 ? 1 : (cr < 0 ? -1 : 0);
}

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
            if (c.X >= mx && c.X <= Mx && c.Y >= my && c.Y <= My)
                return true;
    }
    return false;
}

pair<ld, ld> intersection(PT a, PT b, PT c, PT d)
{
    ll c1 = cross(b - a, c - a), c2 = cross(b - a, d - a);
    PT v = c1 * d - c2 * c;
    ld co = 1. / (c1 - c2);
    return { co * v.X, co * v.Y };
}

int main()
{
    cout << setprecision(10) << fixed;
    for (int i = in(); i; i--)
    {
        PT a, b, c, d;
        cin >> a.X >> a.Y >> b.X >> b.Y >> c.X >> c.Y >> d.X >> d.Y;
        pair<ld, ld> p = intersection(a, b, c, d);
        cout << p.X << ' ' << p.Y << endl;
    }
    return 0;
}
