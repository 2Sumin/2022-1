//2021113772 �̼���
//������ �� �ҽ������� �ٸ� ����� �ҽ��� �������� �ʰ� ���� �ۼ��Ͽ����ϴ�.

import java.util.Scanner;

class ExceptionA extends Exception {

}

class ExceptionB extends ExceptionA {

}

class ExceptionC extends ExceptionB {

}

public class Exceptiontest_1_2 {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);

		System.out.print("numerator: ");
		int numerator = sc.nextInt();
		System.out.print("denominator: ");
		int denominator = sc.nextInt();
		divide(numerator, denominator);
	}

	public static void divide(int x, int y) {
		try {
			if (y == 0) 
//				throw new Exception(");
//				 throw new ExceptionA();
				 throw new ExceptionB();
//				throw new ExceptionC();
			
			System.out.println(x + " / " + y + " = " + x / y);
		} catch (ExceptionC exception) {
			exception.printStackTrace();
		} catch (ExceptionB exception) {
			exception.printStackTrace();
		} catch (ExceptionA exception) {
			exception.printStackTrace();
		} catch (Exception exception) {
			exception.printStackTrace();
		}
	}

}
