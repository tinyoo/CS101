#include<iostream>

using namespace std;

int main(void)
{
    long int N, Memo, c;
    cin >> N;
    long int M[N + 1], C[N + 1], comsumption[N + 1];

    for ( int i = 1; i <= N; ++i )
    {
        cin >> Memo;
        M[i] = Memo;
    }
    for ( int i = 1; i <= N; ++i )
    {
        cin >> c;
        C[i] = c;
    }

    for ( int i = 1; i <= N; ++i )
    {
        comsumption[i] = 0;
    }

    for ( int i = 1; i <= N; ++i )
    {
        for ( int j = 1; j <= i; ++j )
        {
            if ( M[j] - C[i] >= 0 )
            {
                comsumption[i] += C[i];
                M[j] -= C[i];
            }
            else
            {
                comsumption[i] += M[j];
                M[j] = 0;
            }
        }
    }

    for ( int i = 1; i <= N; ++i )
    {
        cout << comsumption[i] << " ";
    }

    return 0;

}