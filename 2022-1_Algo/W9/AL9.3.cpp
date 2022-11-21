#include <iostream>
#include <vector>
#include <queue>
using namespace std;

/*
input-1
3
5 10 20
50 60 140
1
30
output-1
220
5 50
20 140
5 30

input-2
4
2 5 10 5
40 30 50 10
4
8
16
20
25
output-2
75
2 40
5 30
1 5
115
2 40
5 30
9 45
126
2 40
5 30
10 50
3 6
130
2 40
5 30
10 50
5 10
*/

/*
 <분할 가능한 knapsack problem - Greedy>
 -> 배낭에 담을 수 있는 이익이 최대가 되도록 배낭 채우기
 단위무게당 이익이 가장 비싼것부터 정렬(내림차순) 후 배낭 무게를 초과하지 않을때까지 비싼 순으로 채우기
 마지막 아이템은 전부 담지 못한다면 분할해서 담을 수 있음
*/

typedef vector<int> matrix1;
typedef vector<vector<int>> matrix2;

typedef struct item *item_ptr;
typedef struct item
{
    int id;
    int weight;
    int profit;
    int profit_per_unit;
} item_t;

typedef vector<item_t> matrixItem;
matrixItem items;

int T;

struct compare
{
    bool operator()(item_t *i, item_t *j)
    {
        // 단위무게당 이익이 가장 비싼것부터 (내림차순) 정렬
        if (i->profit_per_unit < j->profit_per_unit)
            return true;
        return false;
    }
};

typedef priority_queue<item_ptr, vector<item_ptr>, compare> PriorityQueue;

item_ptr create_node(int i, int w, int p)
{
    item_ptr item = (item_ptr)malloc(sizeof(item_t));
    item->id = i;
    item->weight = w;
    item->profit = p;
    item->profit_per_unit = p / w;
    return item;
}

void sorting(PriorityQueue &PQ, int n, matrix1 &w, matrix1 &p)
{
    for (int i = 1; i <= n; i++)
    {
        item_ptr item = create_node(i, w[i], p[i]);
        PQ.push(item);
    }
}

void knapsack(int n, int W, matrix1 w, matrix1 p, int cnt)
{
    // sorting - PQ에 넣기
    PriorityQueue PQ;
    sorting(PQ, n, w, p);

    matrix2 result(n + 1, matrix1(3, 0)); //결과 저장용
    // position 행의 [0]idx - 무게, [1]idx - 이익 저장
    int total_weight = 0, position = 0;

    while (!PQ.empty())
    {
        item_ptr i = PQ.top();
        PQ.pop();
        total_weight += i->weight;
        // 총 무게가 배낭 최대수용 무게 초과하면
        if (total_weight >= W)
        {
            // i를 담을 수 있는 최대 무게
            int iMaxWeight = i->weight - (total_weight - W); // i의 무게 - 가방 무게보다 초과한 무게
            // i를 iMaxWeight만큼 담았을 떄 얻을 수 있는 이익
            int iMaxprofit = iMaxWeight * i->profit_per_unit; // W의 무게에 딱 맞게 i를 담았을 때 i로 얻을 수 있는 수익
            result[position][0] = iMaxWeight;
            result[position++][1] = iMaxprofit;
            break;
        }
        result[position][0] = i->weight;
        result[position++][1] = i->profit;
    }

    // 출력 1 - 첫 줄에 탐욕법으로 배낭에 담을 수 있는 최대이익을 출력한다.
    int maxProfit = 0; //배낭에 담은 것들의 총 이익
    for (int i = 0; i < position; i++)
        maxProfit += result[i][1];

    cout << "max profit: " << maxProfit << endl;

    // 출력 2 - 둘째 줄부터 배낭에 담은 아이템의 순서대로 무게와 이익의 쌍을 한 줄에 하나씩 출력한다.
    for (int i = 0; i < position; i++)
    {
        // if (cnt == T && i == position - 1)
        //     cout << result[i][0] << " " << result[i][1];
        // else
        cout << i + 1 << "th weight: " << result[i][0] << " profit: " << result[i][1] << endl;
    }
}

int main()
{
    // 입력 1 - 첫째 줄에 아이템의 개수 n이 주어진다.
    int n;
    cin >> n;

    // 입력 2 - 둘째 줄에 n개의 아이템의 무게가 주어진다.
    matrix1 weight_(n + 1, 0);
    for (int i = 1; i <= n; i++)
        cin >> weight_[i];

    // 입력 3 - 셋째 줄에 n개의 아이템별 이익이 주어진다.
    matrix1 profit_(n + 1, 0);
    for (int i = 1; i <= n; i++)
        cin >> profit_[i];

    // 입력 4 - 넷째 줄에 도둑의 배낭 무게 W의 개수 T가 주어진다.
    // int T; // W의 개수
    cin >> T;

    // 입력 5 - 다섯째 줄부터 T개의 배낭 무게 W가 주어진다.
    matrix1 bagWeight(T + 1, 0);
    for (int i = 1; i <= T; i++)
        cin >> bagWeight[i];

    cout << "***output***" << endl;

    // 출력 1 - 첫 줄에 탐욕법으로 배낭에 담을 수 있는 최대이익을 출력한다.
    // 출력 2 - 둘째 줄부터 배낭에 담은 아이템의 순서대로 무게와 이익의 쌍을 한 줄에 하나씩 출력한다.
    // 출력 3 - 다음 줄에는 다음에 주어지는 W에 대해서 위의 출력을 반복한다.
    for (int i = 1; i <= T; i++)
        knapsack(n, bagWeight[i], weight_, profit_, i);
}
