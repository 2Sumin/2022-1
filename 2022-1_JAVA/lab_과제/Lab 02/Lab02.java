package Lab02;
// 2021113772 �̼���

// ������ �� �ҽ������� �ٸ� ����� �ҽ��� �������� �ʰ� ���� �ۼ��Ͽ����ϴ�.

import java.util.Scanner;

public class Lab02 {
	static Scanner sc = new Scanner(System.in);

	static void q1() {

		System.out.println("���� ���� �� �����Դϴ�. ����, ����, �� �߿��� �Է��ϼ���");

		while (true) {
			int A, B, result;
			System.out.print("���� >> ");
			String AS = sc.next();
			if (AS.equals("exit")) {
				System.out.println("����Ǿ����ϴ�.");
				break;
			} else if (AS.equals("����"))
				A = 0;
			else if (AS.equals("����"))
				A = 1;
			else
				A = 2;
			System.out.print("�ع� >> ");
			String BS = sc.next();
			if (BS.equals("exit")) {
				System.out.println("����Ǿ����ϴ�.");
				break;
			} else if (BS.equals("����"))
				B = 0;
			else if (BS.equals("����"))
				B = 1;
			else
				B = 2;
			result = (A - B + 3) % 3;
			switch (result) {
			case 0:
				System.out.println("���º��Դϴ�.\n");
				break;
			case 1:
				System.out.println("��̰� �̰���ϴ�.\n");
				break;
			case 2:
				System.out.println("�ع��̰� �̰���ϴ�.\n");
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
			System.out.println("�Էµ� �� ���� ����Ǿ����ϴ�.");

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
		System.out.print("�� (x,y) �� �Է��ϼ���: ");
		x = sc.nextInt();
		y = sc.nextInt();
		if (x > 50 && x < 100) {
			if (y > 50 && y < 100) {
				System.out.println("�� (" + x + "," + y + ")�� ���簢�� �ȿ� �ֽ��ϴ�.");
			}
		} else
			System.out.println("�� (" + x + "," + y + ")�� ���簢�� �ȿ� �����ϴ�.");

	}

	static void q4() {
		int x1, x2, y1, y2;
		System.out.print("�� (x1,y1) �� �Է��ϼ���: ");
		x1 = sc.nextInt();
		y1 = sc.nextInt();

		System.out.print("�� (x2,y2) �� �Է��ϼ���: ");
		x2 = sc.nextInt();
		y2 = sc.nextInt();

		// ���μ��� ��ġ�� ���-1) x1 �ȿ�, x2 �ۿ�
		if ((x1 > 50 && x1 < 100) && (x2 < 50 || x2 > 100))
			System.out.println("�� ���� ���簢���� ���� �浹�մϴ�.");
		// ���μ��� ��ġ�� ���-2) x2 �ȿ�, x1 �ۿ�
		else if ((x2 > 50 && x2 < 100) && (x1 < 50 || x1 > 100))
			System.out.println("�� ���� ���簢���� ���� �浹�մϴ�.");

		// ���μ��� ��ġ�� ���-1) y1 �ȿ�, y2 �ۿ�
		else if ((y1 > 50 && y1 < 100) && (y2 < 50 || y2 > 100))
			System.out.println("�� ���� ���簢���� ���� �浹�մϴ�.");

		// ���μ��� ��ġ�� ���-2) y2 �ȿ�, y1 �ۿ�
		else if ((y2 > 50 && y2 < 100) && (y1 < 50 || y1 > 100))
			System.out.println("�� ���� ���簢���� ���� �浹�մϴ�.");
		else
			System.out.println("�� ���� ���簢���� ���� �浹���� �ʽ��ϴ�.");
	}

	public static void main(String[] args) {
		 //q1();
//		  q2();
		 //q3();
		 q4();
	}

}
