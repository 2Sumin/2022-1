//2021113772 �̼���
//������ �� �ҽ������� �ٸ� ����� �ҽ��� �������� �ʰ� ���� �ۼ��Ͽ����ϴ�.
//unchecked

import java.util.Scanner;

class Unchecked extends RuntimeException {

}

public class Exceptiontest_2_2 {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);

		System.out.print("numerator: ");
		int numerator = sc.nextInt();
		System.out.print("denominator: ");
		int denominator = sc.nextInt();
		divide(numerator, denominator);
	}

	public static void divide(int x, int y) {
		if (y == 0)
			throw new Unchecked();
		System.out.println(x + " / " + y + " = " + x / y);
	}
}