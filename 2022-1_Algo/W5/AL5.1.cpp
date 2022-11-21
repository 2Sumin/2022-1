#include <iostream>
#include <vector>
using namespace std;

/*
input1
10 6 10000
output
210
input2
15 7 10000
output
6435
input3
15 7 100
output
35
*/

//이항계수 구하기 문제
#define MIN(x, y) ((x) > (y) ? (y) : (x))
int MAX;

/*int bin2(vector<vector<int>> &B, int n, int k)
{
    if (k > n - k)
        k = n - k;

    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= MIN(i, k); j++)
            if (j == 0 || j == i)
                B[i][j] = 1;
            else
                B[i][j] = (B[i - 1][j - 1] + B[i - 1][j]) % MAX;

    return B[n][k];
}*/

int bin1(int n, int k)
{
    // 1차원 배열로 바꾸면 시간복잡도는 그대로지만 공간복잡도가 개선됨
    // 최종적으로 구해야하는 것은 nCk이니까 nC0~nCk-1만 1차원 배열에 담으면 되지
    // 굳이 1C0 부터 시작해서 nCk-1까지 모든 값들을 담을 필요가 없음
    // 재귀 아니고 처음에 B행렬 만들고 시작하는거니까 여기서 선언해도 됨
    vector<int> B(n + 1, 0);
    //처음에 B를 모두 0으로 초기화했으니까
    // B에 값을 집어넣을 때 처음에 B[0]=1, B[1]=0
    // -> i=1일 때 B[1]=B[0]+B[1]=1+0=0로 구할 수 있음

    //대칭이니까
    // nCk = nCn-k
    if (k > n / 2)
        k = n - k;

    B[0] = 1;

    for (int i = 0; i <= n; i++)
    {

        int j = MIN(i, k);
        // 1. i -> C의 특성상 iCi까지만 존재 (10C10) 하니까 i까지만 가능
        // 2. k -> 10C2를 구하는 게 목적이라면 굳이 10C10까지 구할 필요 없음
        // i=5인 배열에서 5C0~5C5까지 모두 구할 필요 없이
        // 5C0~5C2 까지만 구하면 10C2를 구하는 데 문제없음
        // MIN(i,k)를 통해 ~C2까지만 구할 수 있음!

        /*
        i=n 이라면 (nC0~nC2를 구한다면) i=n-1일 때의 값들 (이전 for문을 이용해 구해둔 B배열)을 이용해서 구할 수 있음
        ex. i=3, k=2라면
        현재 B 배열에 저장된 값들은 B[0]=2C0=1, B[1]=2C1=2, B[2]=2C2=1
        -> 이번에 while문을 돌리면서 j=MIN(i,k)=MIN(3,2)=2
        B[2]부터 계산 -> B[2]=(B[2]+B[1])%MAX=3=3C2  (B[2],B[1]은 i=2일 때 구한 값)
        B[1] -> B[1]=B[1]+B[0]=2+1=3 (B[1],B[0]은 i=2일 때 구한 값)
        B[0]은 어차피 1이 되니까 굳이 다시 안 구해도 됨.
        */
        while (j > 0)
        {
            // 뒤에서부터 해서 nCn부터 거꾸로 해서 더해나가기
            B[j] = (B[j] + B[j - 1]) % MAX;
            j--;
        }
        // 이렇게 하면 B[0]~B[MIN(i,k)] 까지 저장됨

        //과정 점검용 각 단계에서 B 배열 출력
        cout << i << ": ";
        for (int a = 0; a <= i; a++)
            printf("%3d ", B[a]);
        cout << endl;
    }
    return B[k];
}

int bin2(int n, int k)
{
    // B를 n*k 2차원 배열로 정의 -> 하지만 2차원 배열을 사용하면 공간복잡도가 높아진다
    vector<vector<int>> B(n + 1, vector<int>(n + 1, 0));

    // 대칭 구조니까 10C8 = 10C2 ->10C0~10C5까지만 구하면 대칭
    // 만약 10C8을 구해야하면 10C2를 구하기
    if (k > n - k)
        k = n - k;

    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= MIN(i, k); j++)
            if (j == 0 || j == i)
                B[i][j] = 1;
            else
                B[i][j] = (B[i - 1][j - 1] + B[i - 1][j]) % MAX;

    return B[n][k];
}

int main(void)
{
    int n, k;

    //입력 - 이항계수의 n과 k, 그리고 MAX 값이 주어진다.
    cin >> n;
    cin >> k;
    cin >> MAX;

    //출력 - 변형 이항계수의 값 B[n][k]를 출력한다.
    cout << bin1(n, k);

    return 0;
}