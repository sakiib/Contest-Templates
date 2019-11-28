#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long uLL;
typedef long long int LL;
typedef pair <int,int> pii;
typedef pair <int,pii> piii;
typedef pair <long long,long long> pll;
typedef pair <long long,pll> plll;
const int N = 1e5 + 5;
const int inf = 1e9;
const long long INF = 1e18;
const double PI = acos(-1.0);
const double EPS = 1e-8;
const int MOD = 1000000007;

struct point {
        LL x, y;
        point () {}
        point( LL x , LL y ) : x(x), y(y) {}
        void operator = ( const point &p ) { x = p.x, y = p.y; }
        bool operator < ( const point &p ) { return x == p.x ? y < p.y : x < p.x; }
        point operator + ( const point &p ) const { point pt( x + p.x, y + p.y ); return pt; }
        point operator - ( const point &p ) const { point pt( x - p.x, y - p.y ); return pt; }
        LL dist( point q ){ return ( ( x-q.x )*(x-q.x) + ( y-q.y )*(y-q.y) ); }
};

bool comp( point &p1, point &p2 ) { return p1.x != p2.x ? p1.x < p2.x : p1.y < p2.y; }

bool cw( point &a, point &b, point &c ) {
        LL area = a.x*( b.y-c.y ) + b.x*( c.y-a.y ) + c.x*( a.y-b.y ); return area < 0;
}
bool ccw( point &a, point &b, point &c ) {
        LL area = a.x*( b.y-c.y ) + b.x*( c.y-a.y ) + c.x*( a.y-b.y ); return area > 0;
}
vector <point> convex_hull( vector<point> &v ) {
        if( v.size() == 1 ) return v;
        sort( v.begin(), v.end() );
        point p1 = v[0], p2 = v.back();
        vector <point> up , down;
        up.push_back( p1 );
        down.push_back( p1 );
        for( int i = 1; i < v.size(); i++ ) {
                if( i == v.size()-1 || cw( p1, v[i], p2 ) ) {
                        while( up.size() >= 2 && !cw( up[up.size()-2], up[up.size()-1], v[i] ) )
                                up.pop_back();
                                up.push_back( v[i] );
                }
                if( i == v.size()-1 || ccw( p1, v[i], p2 ) ) {
                        while( down.size() >= 2 && !ccw( down[down.size()-2], down[down.size()-1], v[i] ) )
                                down.pop_back();
                                down.push_back( v[i] );
                }
        }
        for( int i = down.size()-2; i > 0; i-- ) up.push_back( down[i] );
        return up;
}

int n;
vector <point> V;

/// Diameter using rotating callipers method.

LL area( point a , point b , point c ) {
        return abs( (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x) );
}
LL Diameter( vector <point> h ) {
        int m = h.size();
        if ( m == 1 ) return 0;
        if ( m == 2 ) return h[0].dist(h[1]);
        int k = 1;
        while( area(h[m - 1], h[0], h[(k + 1) % m]) > area(h[m - 1], h[0], h[k]) ) ++k;
        LL res = 0;
        for (int i = 0, j = k; i <= k && j < m; i++) {
                res = max( res, h[i].dist( h[j] ) );
                while (j < m && area(h[i], h[(i + 1) % m], h[(j + 1) % m]) > area(h[i], h[(i + 1) % m], h[j])) {
                        res = max( res, h[i].dist( h[(j + 1) % m] ) );
                        ++j;
                }
        }
        return res;
}
int main( int argc , char const *argv[] ) {
        ios_base::sync_with_stdio( false ); cin.tie( NULL );
        int t;
        cin >> t;
        while( t-- ) {
                cin >> n;
                V.clear();
                for( int i = 1; i <= n; i++ ) {
                        LL x , y , l;
                        cin >> x >> y >> l;
                        V.push_back( point( x , y ) );
                        V.push_back( point( x+l , y ) );
                        V.push_back( point( x , y+l ) );
                        V.push_back( point( x+l , y+l ) );
                }
                vector <point> c = convex_hull( V );
                LL dia = Diameter( c );
                cout << dia << endl;
        }
        return 0;
}










