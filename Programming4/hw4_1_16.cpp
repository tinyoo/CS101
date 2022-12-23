#include <iostream>

using namespace std;

#define ElemType long long
#define P 100000

//---------------------------------------------------

typedef struct HashNode {
    ElemType index;
    ElemType data;
    struct HashNode* link;
}HashNode;

typedef HashNode* HashTable[P];

void Initialize(HashTable ht)
{
    for( int i = 0; i < P; ++i )
        ht[i] = NULL;
}

int Hash( ElemType key )
{
    return key % P;
}

void Insert( HashTable ht, ElemType x, ElemType i)
{
    int index = Hash(x);
    HashNode* s = (HashNode*)malloc(sizeof(HashNode));
    if ( s != NULL )
    {
        s -> data = x;
        s -> index = i;
    }

    s -> link = ht[index];
    ht[index] = s;
}

HashNode* Search( HashTable ht, ElemType x )
{
    int index = Hash(x);
    HashNode* p = ht[index];
    while( p != NULL && p -> data != x )
        p = p -> link;
    return p;
}

int gcd( int x, int y )
{
    if ( y == 0 )
        return x;
    else
        return gcd( y, x % y );
}

int main()
{
    long n, s, num_x;
    long long x;

    // Address the sequence
    cin >> n;
    int *Sequence = new int[n];
    for ( int i = 0; i < n; ++i )
    {
        cin >> s;
        Sequence[i] = s;
    }

    HashTable T;
    Initialize(T);

    // Address x
    cin >> num_x;
    for ( int i = 0; i < num_x; ++i )
    {
        cin >> x;
        Insert(T, x, i);
    }

    int *Ans = new int[num_x];
    for ( int i = 0; i < num_x; ++i )
        Ans[i] = 0;

    for ( int i = 0; i < n; ++i )
    {
        for ( int j = i; j < n; ++j )
        {
            if ( Search( T, gcd( Sequence[i], Sequence[j] ) ) != NULL )
            {
                int k = Search( T, gcd( Sequence[i], Sequence[j] ) ) -> index;
                Ans[k] += 1;
            }
            Sequence[i] = gcd( Sequence[i], Sequence[j] );
        }
    }

    for ( int i = 0; i < num_x; ++i )
        cout << Ans[i] << " ";

    return 0;
}