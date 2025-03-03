#include <bits/stdc++.h>
using namespace std;

struct MANACHER_PALINDROME {
        static const int MAXN = 1e6 + 5;
        string s;

        inline void Initilize( string str ) {
                s = str;
        }
        inline string Convert( string s ) {
                char ret[ 2*MAXN + 5 ];
                int id = 0 , len = s.size();
                ret[ id++ ] = '@';
                for( int i = 0; i < len; i++ ) ret[ id++ ] = '#', ret[ id++ ] = s[i];
                ret[ id++ ] = '#' , ret[ id++ ] = '$' , ret[ id ] = '\0';
                string cur = ret;
                return cur;
        }
        inline vector <int> Manacher( ) {
                string Q = Convert( s );
                vector <int> P( Q.size() );
                int c = 0 , r = 0;
                for( int i = 1; i < Q.size() - 1; i++ ) {
                        int imir = c - ( i - c );
                        if( r > i ) P[i] = min( r - i , P[ imir ] );
                        while( Q[ i + 1 + P[i] ] == Q[ i - 1 - P[i] ] ) P[i]++;
                        if( i + P[i] > r ) c = i , r = i + P[i];
                }
                return P;
        }
} manacher;

int main( int argc , char const *argv[] ) {
        ios_base :: sync_with_stdio(false); cin.tie(NULL);

        int t;
        cin >> t;
        for( int tc = 1; tc <= t; tc++ ) {
                cout << "Case " << tc << ": ";
                string s;
                cin >> s;
                manacher.Initilize( s );
                vector <int> P = manacher.Manacher( );
                int pos = P.size() - 2;
                int mx = 0;
                for( int i = 1; i < P.size() - 1; i++ ) {
                        if( P[i] == 0 ) continue;
                        if( P[i] + i == pos ) mx = max( mx , P[i] );
                }
                cout << s.size() + s.size() - mx << endl;
        }
        return 0;
}
