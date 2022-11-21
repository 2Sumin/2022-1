//과제 5.3번 삼각형 최대경로 문제 경로 개수 출력 -> 첫번째 경우 1, 두번째 경우 2

#include <iostream>
#include <algorithm>

#define lld long long int
#define max_int 101
using namespace std;

//시간 복잡도: O(cn^2)
//공간 복잡도: O(n^2)
//사용한 알고리즘: 동적 계획법 ( Bottom-Up )
//사용한 자료구조: 2차원 배열

int t, n, result;
// a[i][j] = 삼각형에서 행 i, 열 j인 숫자
int a[max_int][max_int];
// d[i][j] = i, j에서 얻을 수 있는 가장 큰 숫자의 합
lld d[max_int][max_int];
// i, j에서 최대값을 얻을 수 있는 경로의 개수
int p[max_int][max_int];
lld max_val;

// 변수 및 배열을 초기화 하는 함수
void init()
{
    max_val = 0;
    result = 0;
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            d[i][j] = 0;
            p[i][j] = 0;
        }
    }
}

int main()
{
    scanf("%d", &n);

    // 1. 변수 및 배열 초기화
    init();

    // 2. 숫자 삼각형의 정보를 받습니다.
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= i; j++)
        {
            scanf("%d", &a[i][j]);
        }
    }

    // 3. 초기값 설정
    d[1][1] = a[1][1];
    p[1][1] = 1;
    for (int i = 2; i <= n; i++)
    {
        for (int j = 1; j <= i; j++)
        {

            // j == 1이면 i-1, j의 정보를 그대로 받습니다.
            if (j == 1)
            {
                d[i][j] = d[i - 1][j] + a[i][j];
                p[i][j] = 1;
            }
            // j == i이면 i-1, j-1의 정보를 그대로 받습니다.
            else if (j == i)
            {
                d[i][j] = d[i - 1][j - 1] + a[i][j];
                p[i][j] = 1;
            }
            // 1 < j < i 일때
            else
            {
                // 상단 오른쪽 숫자의 합이 더 크면 i-1, j-1의 정보를 받습니다.
                if (d[i - 1][j - 1] > d[i - 1][j])
                {
                    d[i][j] = d[i - 1][j - 1] + a[i][j];
                    p[i][j] = p[i - 1][j - 1];
                    // 상단 바로 위쪽 숫자의 합이 더 크면 i-1, j의 정보를 받습니다.
                }
                else if (d[i - 1][j - 1] < d[i - 1][j])
                {
                    d[i][j] = d[i - 1][j] + a[i][j];
                    p[i][j] = p[i - 1][j];
                }
                // 상단 오른쪽, 상단 바로 위쪽 숫자의 합이 같다면
                // 합은 둘 중 어느것을 받아도 상관없습니다.
                // 경로의 경우의 수는 두 개를 모두 받아줍니다.
                else
                {
                    d[i][j] = d[i - 1][j] + a[i][j];
                    p[i][j] = p[i - 1][j - 1] + p[i - 1][j];
                }
            }
            // 매 행마다, 최대 값을 갱신해줍니다.
            max_val = max(max_val, d[i][j]);
        }
    }

    // 만약, d[n][j]의 정보가 최대 값이면
    // 경로의 수를 결과에 더해줍니다.
    for (int j = 1; j <= n; j++)
    {
        if (max_val == d[n][j])
        {
            result += p[n][j];
        }
    }
    printf("%d\n", result);
}