package Lab03;
//2021113772 �̼���

//������ �� �ҽ������� �ٸ� ����� �ҽ��� �������� �ʰ� ���� �ۼ��Ͽ����ϴ�.

import java.security.SecureRandom;
import java.util.Scanner;

public class Lab03_05 {

	public static void main(String[] args) {
		SecureRandom randomNumbers = new SecureRandom();
		Scanner sc = new Scanner(System.in);

		String right[] = { "Very good!", "Excellent!", "Nice work!", "Keep up the good work!" };
		String wrong[] = { "No. Please try again.", "Wrong. Try once more.", "Don't give up!", "No. Keep trying" };

		while (true) {

			int x = 1 + randomNumbers.nextInt(10);
			int y = 1 + randomNumbers.nextInt(10);
			System.out.println("How much is " + x + " times " + y + "?");
			System.out.print("Enter your answer (-1 to exit): ");
			int ans = sc.nextInt();
			int cal_ans = x * y;
			if (ans == -1)
				break;
			int idx = randomNumbers.nextInt(4);
			if (ans == cal_ans)
				System.out.println(right[idx]);

			else
				System.out.println(wrong[idx]);
			System.out.println();

		}
	}

}
