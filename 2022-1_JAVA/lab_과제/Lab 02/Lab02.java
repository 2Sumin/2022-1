package Lab02;
// 2021113772 이수민

// 본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.

import java.util.Scanner;

public class Lab02 {
	static Scanner sc = new Scanner(System.in);

	static void q1() {

		System.out.println("가위 바위 보 게임입니다. 가위, 바위, 보 중에서 입력하세요");

		while (true) {
			int A, B, result;
			System.out.print("혜미 >> ");
			String AS = sc.next();
			if (AS.equals("exit")) {
				System.out.println("종료되었습니다.");
				break;
			} else if (AS.equals("가위"))
				A = 0;
			else if (AS.equals("바위"))
				A = 1;
			else
				A = 2;
			System.out.print("준범 >> ");
			String BS = sc.next();
			if (BS.equals("exit")) {
				System.out.println("종료되었습니다.");
				break;
			} else if (BS.equals("가위"))
				B = 0;
			else if (BS.equals("바위"))
				B = 1;
			else
				B = 2;
			result = (A - B + 3) % 3;
			switch (result) {
			case 0:
				System.out.println("무승부입니다.\n");
				break;
			case 1:
				System.out.println("헤미가 이겼습니다.\n");
				break;
			case 2:
				System.out.println("준범이가 이겼습니다.\n");
				break;
			}
		}
	}

	static void q2() {
		// sentinel : -1
		int n, max, min;

		System.out.print("Enter integer : ");
		n = sc.nextInt();
		if (n < 0)
			System.out.println("입력된 값 없이 종료되었습니다.");

		max = min = n;

		while (n >= 0) {
			if (n > max)
				max = n;
			if (n < min)
				min = n;
			System.out.print("Enter integer : ");
			n = sc.nextInt();
		}

		if (max >= 0 && min >= 0) {
			System.out.println("Smallest Integer is : " + min);
			System.out.println("Largest Integer is : " + max);
		}
	}

	static void q3() {
		int x, y;
		System.out.print("점 (x,y) 을 입력하세요: ");
		x = sc.nextInt();
		y = sc.nextInt();
		if (x > 50 && x < 100) {
			if (y > 50 && y < 100) {
				System.out.println("점 (" + x + "," + y + ")는 직사각형 안에 있습니다.");
			}
		} else
			System.out.println("점 (" + x + "," + y + ")는 직사각형 안에 없습니다.");

	}

	static void q4() {
		int x1, x2, y1, y2;
		System.out.print("점 (x1,y1) 을 입력하세요: ");
		x1 = sc.nextInt();
		y1 = sc.nextInt();

		System.out.print("점 (x2,y2) 을 입력하세요: ");
		x2 = sc.nextInt();
		y2 = sc.nextInt();

		// 가로선이 겹치는 경우-1) x1 안에, x2 밖에
		if ((x1 > 50 && x1 < 100) && (x2 < 50 || x2 > 100))
			System.out.println("두 개의 직사각형은 서로 충돌합니다.");
		// 가로선이 겹치는 경우-2) x2 안에, x1 밖에
		else if ((x2 > 50 && x2 < 100) && (x1 < 50 || x1 > 100))
			System.out.println("두 개의 직사각형은 서로 충돌합니다.");

		// 세로선이 겹치는 경우-1) y1 안에, y2 밖에
		else if ((y1 > 50 && y1 < 100) && (y2 < 50 || y2 > 100))
			System.out.println("두 개의 직사각형은 서로 충돌합니다.");

		// 세로선이 겹치는 경우-2) y2 안에, y1 밖에
		else if ((y2 > 50 && y2 < 100) && (y1 < 50 || y1 > 100))
			System.out.println("두 개의 직사각형은 서로 충돌합니다.");
		else
			System.out.println("두 개의 직사각형은 서로 충돌하지 않습니다.");
	}

	public static void main(String[] args) {
		 //q1();
//		  q2();
		 //q3();
		 q4();
	}

}
