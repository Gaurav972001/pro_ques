#include <bits/stdc++.h>
using namespace std;

class Union
{
private:
    vector<int> par;
    vector<int> rank;

public:
    Union()
    {
        rank = vector<int>(1e5, 1);
        par = vector<int>(1e5, -1);
        for (int i = 0; i < 1e5; i++)
        {
            par[i] = i;
        }
    }
    int findPar(int node)
    {
        if (node == par[node])
            return node;
        return par[node] = findPar(par[node]);
    }
    void makeUnion(int u, int v)
    {
        int v_par = findPar(v);
        par[v_par] = u;
        rank[u] += rank[v_par];
    }

    int getRank(int node)
    {
        return rank[node];
    }
};

class tile
{
public:
    int x1, y1, x2, y2, num;
    tile(int i, int j, int k, int l, int n)
    {
        x1 = i;
        y1 = j;
        x2 = k;
        y2 = l;
        num = n;
    }
};

bool isRectangleOverlap(tile r1, tile r2)
{
    if (r1.x1 >= r2.x2 || r2.x1 >= r1.x2)
        return false;
    if (r1.y1 >= r2.y2 || r2.y1 >= r1.y2)
        return false;
    return true;
}

vector<tile> tiles;
int solve(Union &u, int &num)
{
    cout << "enter i, j, m : ";
    int i, j, player, m;
    cin >> i >> j >> m;

    int x1 = i, y1 = j, x2 = i + m, y2 = j + m;
    tile cur(x1, y1, x2, y2, num);

    tiles.push_back(cur);

    int size = tiles.size();
    // cout << size << endl;
    for (int t = 0; t < size - 1; t++)
    {
        if (isRectangleOverlap(tiles[t], cur))
        {
            if (u.findPar(tiles[t].num) == num)
                continue;
            u.makeUnion(num, tiles[t].num);
        }
    }

    return u.getRank(num++);
}

int main()
{
    cout << "no of tiles : ";
    int n;
    cin >> n;
    Union u;
    int num = 0;
    while (n--)
    {
        cout << solve(u, num) << endl;
    }
}