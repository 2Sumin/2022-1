//2021113772 �̼���
//������ �� �ҽ������� �ٸ� ����� �ҽ��� �������� �ʰ� ���� �ۼ��Ͽ����ϴ�.
//checked

import java.util.Scanner;

public class Exceptiontest_2_1 {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);

		System.out.print("numerator: ");
		int numerator = sc.nextInt();
		System.out.print("denominator: ");
		int denominator = sc.nextInt();
		// checked exception�̱� ������ try-catch���̳� �Ʒ� �Լ��� throws ������ �־�� �Ѵ�.
		// �� �� ������ ������ ���� �߻�
		try {
			divide(numerator, denominator);
		} catch (Exception exception) {
			System.err.println(exception);
		}

	}

//throws ����
//	public static void divide(int x, int y) throws Exception {
	public static void divide(int x, int y) {
		try {
			if (y == 0)
				throw new Exception();
			System.out.println(x + " / " + y + " = " + x / y);
		} catch (Exception exception) {
			System.err.println(exception);
		}
	}

}
