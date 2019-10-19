#ifndef TRIMATRIX_H_INCLUDED
#define TRIMATRIX_H_INCLUDED
#include"printable.h"
#include<vector>
#include<unordered_map>
using namespace std;
typedef pair<int, int> pos;

struct pair_hash
{
    template <class T1, class T2>
    std::size_t operator () (const std::pair<T1, T2> &p) const
    {
        auto h1 = std::hash<T1> {}(p.first);
        auto h2 = std::hash<T2> {}(p.second);
        return h1 ^ h2;
    }
};

template<class T>
struct Tri
{
    Tri() {}
    Tri(int i, int j, T e)
    {
        p.first = i;
        p.second = j;
        this->e = e;
    }
    pos p;
    T e;
};

template<class T>
class TriMatrix : public Printable<T>
{
private:
    typedef Tri<T> N;
public:
    TriMatrix(int m, int n)
    {
        this->m = m;
        this->n = n;
    }
    TriMatrix(const vector<vector<T>> v) {
        this->m = v.size();
        if(!m)return;
        this->n = v[0].size();
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                Tri<T> t(i, j, v[i][j]);
                Insert(t);
            }
        }
    }

    static TriMatrix<T> add(const TriMatrix<T>& a,const  TriMatrix<T>& b)
    {
        int M = a.m, N = a.n;
        if(!(a.m == b.m && a.n == b.n))
        {
            throw "NotSame";
        }
        unordered_map<pos, T, pair_hash> un_map;
        int len = a.data.size();
        for(int i = 0; i < len; i++)
        {
            un_map[a.data[i].p] += a.data[i].e;
        }
        len = b.data.size();
        for(int i = 0; i < len; i++)
        {
            un_map[b.data[i].p] += b.data[i].e;
        }
        TriMatrix<T> c(M, N);
        for(auto i = un_map.begin(); i != un_map.end(); i++)
        {
            Tri<T> temp(i->first.first, i->first.second, i->second);
            c.Insert(temp);
        }
        return c;
    }

    void Reverse()
    {
        for(N& item : data)
        {
            int temp = item.p.first;
            item.p.first = item.p.second;
            item.p.second = temp;
        }
    }

    void printAll()
    {
        unordered_map<pos, T, pair_hash> un_map;
        for(N& item: data)
        {
            un_map[item.p] += item.e;
        }
        for(int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                pos p(i, j);
                cout << un_map[p] << " ";
            }
            cout << endl;
        }
    }

    void Insert(N e)
    {
        data.push_back(e);
    }

public:
    vector<N> data;
    int m, n;
};

#endif // TRIMATRIX_H_INCLUDED
