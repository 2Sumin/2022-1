#include <iostream>
#include <cstring>
#define MAX(a, b) (a > b ? a : b)
using namespace std;
int N;
int triangle[100][100];
int cache[100][100];
int sumCache[100][100]; //(y,x)에서 맨 아래줄까지 내려가는 경로의 최대 합
int path(int y, int x)
{
    if (y == N - 1)
        return triangle[y][x];
    int &ret = cache[y][x];
    if (ret != -1)
        return ret;
    return ret = MAX(path(y + 1, x), path(y + 1, x + 1)) + triangle[y][x];
} //(y,x)에서 맨 아래줄까지 내려가는 최대 경로의 개수 리턴
int count(int y, int x)
{
    if (y == N - 1)
        return 1;
    int &ret = sumCache[y][x];
    if (ret != -1)
        return ret;
    ret = 0;
    if (path(y + 1, x) >= path(y + 1, x + 1))
        ret += count(y + 1, x);
    if (path(y + 1, x) <= path(y + 1, x + 1))
        ret += count(y + 1, x + 1);
    return ret;
}
int main()
{

    memset(cache, -1, sizeof(cache));
    memset(sumCache, -1, sizeof(sumCache));
    memset(triangle, -1, sizeof(triangle));
    cin >> N;
    for (int i = 0; i < N; i++)
        for (int j = 0; j <= i; j++)
            cin >> triangle[i][j];
    cout << count(0, 0) << endl;
}
