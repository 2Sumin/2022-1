package Lab04;


//2021113772 �̼���

//������ �� �ҽ������� �ٸ� ����� �ҽ��� �������� �ʰ� ���� �ۼ��Ͽ����ϴ�.
public class ArrayTest_02 {

	public static void main(String[] args) {
		// (1) 2���� �迭 ����, new ������ ���, 4����

		int[][] arr = new int[3][3];
		arr[0] = new int[2];
		arr[1] = new int[1];
		arr[2] = new int[3];

		// (2) ��� �迭 ���ҿ� 1 �Ҵ�, counter controlled for statement
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

		// (3) �迭 ������ ���� �׸��� ���� ������� ���, enhanced for statement
		for (int[] row : arr) {
			for (int col : row)
				System.out.print(col + " ");
			System.out.println();
		}

	}

}
