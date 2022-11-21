//2021113772 이수민
//본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.
//checked

import java.util.Scanner;

public class Exceptiontest_2_1 {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);

		System.out.print("numerator: ");
		int numerator = sc.nextInt();
		System.out.print("denominator: ");
		int denominator = sc.nextInt();
		// checked exception이기 때문에 try-catch문이나 아래 함수에 throws 선언이 있어야 한다.
		// 둘 다 없으면 컴파일 에러 발생
		try {
			divide(numerator, denominator);
		} catch (Exception exception) {
			System.err.println(exception);
		}

	}

//throws 선언
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
