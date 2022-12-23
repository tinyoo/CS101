#include <iostream>///fall

using namespace std;

void fun(int *array, int size);

int main(void)
{
    int size;
    cin >> size;
    int *array = new int[size];
    for ( int i = 0; i < size; ++i )
        array[i] = 0;
    fun(array, size);
    for ( int i = 0; i < size; ++i )
        cout << array[i] << " ";
    return 0;
}

void fun(int *array, int size)
{
    for ( int i = 0; i < size; ++i )
        array[i] += i;
}

