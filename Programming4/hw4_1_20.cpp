#include <iostream>

using namespace std;

#define ElemType long long
#define P 30000

//---------------------------------------------------

typedef struct HashNode {
    ElemType data;
    ElemType number;
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

void Insert( HashTable ht, ElemType x, ElemType n)
{
    int index = Hash(x);
    HashNode* s = (HashNode*)malloc(sizeof(HashNode));
    if ( s != NULL )
    {
        s -> data = x;
        s -> number = n;
    }

    s -> link = ht[index];
    ht[index] = s;
}

HashNode* Search( HashTable ht, ElemType x )
{
    int index = Hash(x);
    HashNode* p = ht[index];
    while( ( p != NULL ) && ( p -> data != x ) )
        p = p -> link;
    return p;
}

int gcd( long x, long y )
{
    if ( y == 0 )
        return x;
    else
        return gcd( y, x % y );
}

int main(void)
{
    long n, s, num_x;
    long long x;

    // Address the sequence
    cin >> n;
    long *Sequence = new long[n];
    for ( long i = 0; i < n; ++i )
    {
        cin >> s;
        Sequence[i] = s;
    }

    HashTable T;
    Initialize(T);

    // Address x
    cin >> num_x;
    long *Xs = new long[num_x];
    for ( long i = 0; i < num_x; ++i )
    {
        cin >> x;
        Xs[i] = x;
    }

    for ( long i = 0; i < n; ++i )
    {
        long x = Sequence[i];
        if ( Search(T, x) == NULL )
            Insert(T, x, 1);
        else
            Search(T, x) -> number += 1;
        for ( long j = i; j < n - 1; ++j )
        {
            x = gcd(x, Sequence[j + 1]);
            if ( Search(T, x) == NULL )
                Insert(T, x, 1);
            else
                Search(T, x) -> number += 1;
            if ( x == 1 )
            {
                if ( Search(T, x) == NULL )
                    Insert(T, 1, n - j - 2);
                else
                    Search(T, x) -> number += ( n - j - 2 );
                break;
            } 
        }
    }

    long *Ans = new long[num_x];
    for ( int i = 0; i < num_x; ++i )
        Ans[i] = 0;

    for ( long i = 0; i < num_x; ++i )
    {
        if ( Search(T, Xs[i]) != NULL )
        {
            Ans[i] += Search(T, Xs[i]) -> number;
        }
    }

    for ( long i = 0; i < num_x; ++i )
        cout << Ans[i] << " ";

    return 0;
}