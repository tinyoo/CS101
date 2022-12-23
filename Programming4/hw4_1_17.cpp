#include <iostream>

using namespace std;

struct Hash {
    size_t operator()(const int &key)
    {
         return key % 3; 
    }
};

struct Compare {
    bool operator() (const int &a, const int &b) const 
    {
        return a == b;
    }
};

template<class Key,class Value>
class Hash_Node {
    public:
        int key;
        int value;
        struct Hash_Node *next;
        Hash_Node(Key key1,Value value1):key(key1),value(value1),next(NULL){}
};

template<class Key, class Value, class Hash, class Compare>
class Hash_Map{
    public:
        Hash_Map(int len = 10000):size(len) {
            cur = 0;
            bucket = size/2;
            hash_map = new Hash_Node<Key,Value> *[size];
            for(int i = 0;i < bucket;i++)
                hash_map[i] = NULL;
        }
        
        Hash_Node<Key,Value>* find(Key key) {
           int hash_code = hash(key);
           Hash_Node<Key,Value> *pNode = hash_map[hash_code];
           while(pNode) {
                if(compare(pNode->key,key)) 
                    return pNode; 
                else 
                    pNode = pNode->next;
           }
           return NULL;
        }
         
        bool set(Key key,Value value) {
           if(cur > size)
                return false;
            Hash_Node<Key,Value> *pNode = find(key);
            if(pNode == NULL) {
                int hash_code = hash(key);
                Hash_Node<Key,Value> *pData = new Hash_Node<Key,Value>(key,value);
                Hash_Node<Key,Value> *pnode = hash_map[hash_code];
                if(pnode == NULL) {
                    hash_map[hash_code] = pData;
                } else {
                    while(pnode->next!=NULL) {
                        pnode = pnode->next;
                    }
                    pnode->next = pData;
                }
            } else {
                pNode->value = value;
            }
            ++cur;
            return true;
        }

        Value &get(Key key) {
            Hash_Node<Key,Value> *pnode = find(key);
            if(pnode)
                return pnode->value;
            set(key,0);
            return find(key)->value;
        }

        ~Hash_Map() {
            for(int i=0; i<bucket; i++) {
                while(true) {
                    Hash_Node<Key, Value> *pnode = hash_map[i];
                    if(pnode) {
                       hash_map[i] = pnode->next;
                       delete pnode;
                    } else {
                        break;
                    }    
                }
            }
            delete []hash_map;
        }
    private:
        Hash_Node<Key, Value> **hash_map;
        Hash hash;
        Compare compare;
        int bucket;
        int size;
        int cur;
};

int gcd( int x, int y );

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

    Hash_Map<int, int, Hash, Compare> map;

    // Address x
    cin >> num_x;
    for ( int i = 0; i < num_x; ++i )
    {
        cin >> x;
        map.set(x,i);
    }

    int *Ans = new int[num_x];
    for ( int i = 0; i < num_x; ++i )
        Ans[i] = 0;

    for ( int i = 0; i < n; ++i )
    {
        for ( int j = i; j < n; ++j )
        {
            //cout << k << endl;
            if ( map.get( gcd( Sequence[i], Sequence[j] ) ) != 0 )
            {
                int k = map.get( gcd( Sequence[i], Sequence[j] ) );
                Ans[k] += 1;
            }
            Sequence[i] = gcd( Sequence[i], Sequence[j] );
            //cout << Sequence[i] << " ";
        }
    }
    //cout << "Hello!" << endl;

    for ( int i = 0; i < num_x; ++i )
        cout << Ans[i] << " ";

    return 0;
}

int gcd( int x, int y )
{
    if ( y == 0 )
        return x;
    else
        return gcd( y, x % y );
}