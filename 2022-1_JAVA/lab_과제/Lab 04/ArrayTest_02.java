package Lab04;


//2021113772 이수민

//본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.
public class ArrayTest_02 {

	public static void main(String[] args) {
		// (1) 2차원 배열 선언, new 연산자 사용, 4문장

		int[][] arr = new int[3][3];
		arr[0] = new int[2];
		arr[1] = new int[1];
		arr[2] = new int[3];

		// (2) 모든 배열 원소에 1 할당, counter controlled for statement
		for (int i = 0; i < arr.length; i++) {
			if (i == 0)
				for (int j = 0; j < arr[i].length; j++)
					arr[i][j] = 1;
			else if (i == 1)
				for (int j = 0; j < arr[i].length; j++)
					arr[i][j] = 1;
			else if (i == 2)
				for (int j = 0; j < arr[i].length; j++)
					arr[i][j] = 1;
		}

		// (3) 배열 원소의 값을 그림과 같은 모양으로 출력, enhanced for statement
		for (int[] row : arr) {
			for (int col : row)
				System.out.print(col + " ");
			System.out.println();
		}

	}

}
