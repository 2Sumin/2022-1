#include <iostream>
#include <vector>
using namespace std;

/*
input-1
7
3 1 1 3 1 3 2
40 35 30 25 20 15 10
output-1
100
35 40 25

input-2
5
2 1 2 1 3
97 27 25 19 13
output-2
137
27 97 13
*/

/*
<마감시간 있는 스케줄 짜기>
-마감시간과 함께 여러개의 작업이 주어지고, 각 작업을 마감시간 전에 마치면 받을 수 있는 보상이 정해져있음
-주어진 마감시간 내에 얻을 수 있는 보상을 최대화하는 스케줄 작성

 1. 작업을 보상이 큰 것부터 차례로 정렬한다
 2. 각 작업을 정렬된 순서대로 하나씩 가능한 스케줄(S)에 포함시킨다
 3. 더 이상 남은 작업이 없으면 종료

 feasibility의 정의
 -순서 내의 모든 작업이 데드라인 이전에 시작될 때 'feasible sequence'라고 함
 feasible set
 -그 집합의 원소들로 하나 이상의 적절한 순서를 만들 수 있을 때 적절한 집합이라 한다
 -집합의 원소를 어떻게 조합해도 적절한 순서를 못 만든다면 부적절한 집합
 -S가 feasible < - > S에 속한 작업을 "마감시간이 빠른 것부터 나열"(deadline에 대해 오름차순으로 정렬)해서 얻은 순서가 적절하다

job         - 1  2  3  4  5  6  7
deadline    - 3  1  1  3  1  3  2
profit      - 40 35 30 25 20 15 10

 [[순서도]]
 1. profit에 따라 큰 것부터 정렬 (제일 위에 정렬된 것부터 job의 이름이 1,2,3...으로 정해져있다고 가정)
 2. 1차원 배열 J에 1을 추가
    -> J = [1]
 3. job 2 를 K에 deadline의 오름차순으로 추가했을 때 K=[2,1]이 feasible -> J에 2 추가
    -> J = [2,1]
 4. job 3 을 K에 deadline의 오름차순으로 추가했을 때 K=[2,3,1]이 not feasible -> J에 3은 추가하면 안 됨
    -> J = [2,1]
 5. job 4 를 K에 deadline의 오름차순으로 추가했을 때 K=[2,1,4]이 feasible -> J에 4 추가
    -> J = [2,1,4]
 6. job 5 을 K에 deadline의 오름차순으로 추가했을 때 K=[2,5,1,4]이 not feasible -> J에 5는 추가하면 안 됨
    -> J = [2,1,4]
 7. job 6 을 K에 deadline의 오름차순으로 추가했을 때 K=[2,1,4,6]이 not feasible -> J에 6은 추가하면 안 됨
    -> J = [2,1,4]
 8. job 7 을 K에 deadline의 오름차순으로 추가했을 때 K=[2,7,1,4]이 not feasible -> J에 7은 추가하면 안 됨
    -> J = [2,1,4]
 9. 최종적으로 feasible sequence J = [2,1,4]
    total profit = 35 + 40 + 25 = 100

*/

typedef vector<int> sequence_of_integer;

bool is_feasible(sequence_of_integer &K, sequence_of_integer &deadline)
{
    /*
    현재 시각을 index로 생각하고 보기.
    job을 K에 인덱스가 1일 때부터 순서대로 추가해뒀을 때,
    K의 인덱스보다 deadline이 작으면 not feasible
    (ex. index=4, deadline=3이라면 index가 deadline을 넘었으므로 불가능 )
    */
    for (int i = 1; i < K.size(); i++)
        // K[i] 원소의 deadline이 i(index)보다 작다면 불가능
        if (i > deadline[K[i]])
            return false;
    // for문을 다 지나왔는데 false가 리턴되지 않았다면 true
    return true;
}

void schedule(int n, sequence_of_integer &deadline, sequence_of_integer &J)
{
    sequence_of_integer K; // J에 실제로 job 추가하기 전 가능한지 테스트해보는 배열
    J.clear();
    J.push_back(0); // J의 인덱스가 1부터 시작하게 하기 위해 앞에 0추가
    J.push_back(1);
    for (int i = 2; i <= n; i++)
    {
        // J(현재까지 가능한 job을 저장해둔 배열)를 K에 copy
        K.resize(J.size());
        copy(J.begin(), J.end(), K.begin());
        // deadline의 오름차순으로 i번째 job을 insert하기 위한 인덱스(j) 찾기
        int j = 1;
        // 아직 끝까지 안 갔고 (K.size()>j) 한 칸씩 옆으로 가면서 K[j]의 deadline이 i번째 job의 deadline보다 작다면 계속 인덱스(j) 1씩 키우기
        while (j < K.size() && deadline[K[j]] <= deadline[i])
            j++;
        // K의 j 인덱스에 i번째 job 추가
        K.insert(K.begin() + j, i);

        if (is_feasible(K, deadline))
        {
            // K가 feasible하다면 J에 K를 복사해넣기
            J.resize(K.size());
            copy(K.begin(), K.end(), J.begin());
        }
    }
}

int main()
{
    // 입력 1 - 첫째 줄에 job의 개수 n이 주어진다.
    int n;
    cin >> n;

    // 입력 2 - 둘째 줄에 n개의 deadline이 주어진다.
    sequence_of_integer deadline(n + 1, 0);
    sequence_of_integer scheduled(n + 1, 0); // schedule 함수에서 정렬 후 배열
    for (int i = 1; i <= n; i++)
        cin >> deadline[i];

    // 입력 3 - 셋째 줄에 n개의 profit이 주어진다.
    sequence_of_integer profit(n + 1, 0);
    for (int i = 1; i <= n; i++)
        cin >> profit[i];

    cout << "***output***" << endl;

    schedule(n, deadline, scheduled);
    // 출력 1 - 첫 줄에 최대 이익의 값을 출력한다.
    int maxProfit = 0;
    for (int i = 1; i <= n; i++)
        maxProfit += profit[scheduled[i]];
    cout << "max profit : " << maxProfit << endl;

    // 출력 2 - 둘째 줄에 Algorithm 4.4가 발견한 job sequence의 순서대로 각 job의 profit을 출력한다.
    for (int i = 1; scheduled[i]; i++)
    {
        cout << i << "th job's profit: " << profit[scheduled[i]] << endl;
        // if (i != n)
        //     cout << " ";
    }
}