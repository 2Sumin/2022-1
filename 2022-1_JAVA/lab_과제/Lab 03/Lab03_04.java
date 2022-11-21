package Lab03;
//2021113772 이수민

//본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.

public class Lab03_04 {

	public static void main(String[] args) {
		int x1 = 1, y1 = 2;
		double x2 = 1.1, y2 = 2.2;

		System.out.println("1 + 2 = " + sum(x1, y1));
		System.out.println("1.1 + 2.2 = " + sum(x2, y2));
	}

	public static int sum(int x, int y) {
		return x + y;

	}

	public static double sum(double x, double y) {
		return x + y;

	}

}
