#include <iostream>
#include <vector>
using namespace std;

typedef vector<int> matrix1;
typedef vector<vector<int>> matrix2;

/*
input-1
4 5
1 2
1 3
1 4
2 3
3 4
output-1
3
6

input-2
4 6
1 2
1 3
1 4
2 3
2 4
3 4
output-2
4
24
*/

/*
<m-coloring problem>
 : 무방향 그래프에서 m개의 다른 색으로 어떠한 인접한 정점도 같은 색으로 칠해지지 않는 경우의 수 찾기
*/

int n;          // 그래프 내 정점의 수
matrix2 W;      // 그래프 내 인접한 정점인지 알려주는 배열
matrix1 vcolor; // 각 노드별 색상 저장

bool promising(int i)
{
    //인접한 노드끼리 서로 다른 색을 사용했는가
    int j = 1;
    bool flag = true;
    while (j < i && flag) // flag가 false가 되면 더 이상 볼 필요없이 while문 종료
    {
        // W[i][j]==True (1) : 인접하다
        // vcolor[i] == vcolor[j] : 인접한 노드끼리 같은 색 썼나
        // -> 인접한 노드이고, 같은 색 썼다면 false
        if (W[i][j] && vcolor[i] == vcolor[j])
            flag = false;
        j++;
    }
    return flag;
}

int cnt;
void m_coloring(int i, int m)
{
    int color;
    if (promising(i))
    {
        // 모든 노드를 다 찾았다 (solution)
        if (i == n)
        {
            // cout << vcolor[1] through vcolor[n];

            cnt++;
            // vcolor 배열 출력
            // cout << "cnt: " << cnt << endl;
            // for (int k = 1; k <= n; k++)
            // {
            //     cout << vcolor[k];
            //     if (k != n)
            //         cout << " ";
            // }
            // cout << endl;
        }
        else
        {
            // 다음 정점에 모든 색을 시도해본다
            // 반복할 때마다 모든 컬러를 넣어본다
            // m개의 모든 컬러를 조사해본다.

            // 기존에 색칠한 노드들을 보면서
            for (color = 1; color <= m; color++)
            {
                // i+1번 째 컬러를 선택하고
                vcolor[i + 1] = color;
                // i+1번 째 컬러가 가능한지 검사하러 가본다.
                m_coloring(i + 1, m);
            }
        }
    }
}

int main()
{
    // 입력 1 - 첫 줄에 정점의 수 n과 간선의 수 k가 주어진다.
    int k;
    cin >> n >> k;
    W.resize(n + 1, vector<int>(n + 1, 0));
    vcolor.resize(n + 1);

    // 입력 2 - 둘째 줄부터 k개의 간선이 주어진다. (간선의 집합 입력)
    for (int i = 0; i < k; i++)
    {
        //무방향 그래프
        pair<int, int> edge;
        cin >> edge.first >> edge.second;
        W[edge.first][edge.second] = 1;
        W[edge.second][edge.first] = 1;
    }

    // 출력 1 - 첫째 줄에 색칠 가능한 최소의 m값을 출력한다.
    // 1부터 호출해서 출력되는지 확인하고 2, 3, 4까지 확인해보고 최솟값 찾기
    // 최대값이 4 (그 이상은 안 나옴) - 모든 평면그래프는 최대 4가지 색으로 칠할 수 있다
    int minM;
    for (int m = 1; m <= 4; m++)
    {
        vcolor.clear();
        m_coloring(0, m);
        // m이 현재 주어진 m일 때 가능한 경우의 수가 0이 아니라면 (하나라도 있다면) -> 그 값이 m
        // 가능한 m 중 최솟값이 minM
        if (cnt != 0)
        {
            minM = m;
            break;
        }
    }
    cout << "***output***" << endl;
    cout << "minimum m : " << minM << endl;
    // 출력 2 - 둘째 줄에 해당 m값으로 색칠할 수 있는 경우의 수를 출력한다.
    cout << "number of cases: " << cnt;
}
