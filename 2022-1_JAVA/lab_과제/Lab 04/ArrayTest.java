package Lab04;

//2021113772 �̼���

//������ �� �ҽ������� �ٸ� ����� �ҽ��� �������� �ʰ� ���� �ۼ��Ͽ����ϴ�.

public class ArrayTest {

	public static void main(String[] args) {
		int[] array = { 10, 20, 30, 40 };

		System.out.printf("sumArray1D1 : %d, sumArray1D2 : %d\n", sumArray1D1(array), sumArray1D2(array));

	}

	// (1) counter controlled for statement
	public static int sumArray1D1(int[] arr) {
		int sum = 0;
		for (int i = 0; i < arr.length; i++)
			sum += arr[i];
		return sum;

	}

	// (2) enhanced for statement
	public static int sumArray1D2(int[] arr) {
		int sum = 0;
		for (int element : arr)
			sum += element;
		return sum;

	}

}
