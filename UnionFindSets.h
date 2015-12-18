//
// Created by 陈超 on 15/12/15.
//

#ifndef DBC_V4_UNIONFINDSETS_H
#define DBC_V4_UNIONFINDSETS_H
const int MAX_N = 1<<16;
int par[MAX_N];
int height[MAX_N];
int num[MAX_N];

void init(int n) {
    for(int i=0; i<n; i++) {
        par[i] = i;
        height[i] = 0;
        num[i] = 1;
    }
}

int find(int x) {
    if(par[x] == x) return x;
    return par[x] = find(par[x]);
}

void unite(int x, int y)
{
    assert(x == find(x));

    x = find(x);
    y = find(y);

    assert(x != y);

    par[x] = y;
    num[y] += num[x];
}

bool same(int x, int y)
{
    return find(x) == find(y);
}

int getNum(int x)
{
    return(num[find(x)]);
}

#endif //DBC_V4_UNIONFINDSETS_H
