package Lab03;

//2021113772 �̼���

//������ �� �ҽ������� �ٸ� ����� �ҽ��� �������� �ʰ� ���� �ۼ��Ͽ����ϴ�.

public class Lab03_01 {
	private static int num1;
	private int num2;

	public static void show1() { //static �޼ҵ忡���� static �޼ҵ峪 ������ ��� ����
		System.out.println(num1);   //(1) O - num1�� static �����̹Ƿ� static �޼ҵ��� show1 �ȿ��� ��� �����ϴ�
		System.out.println(num2);   //(2) X - num2�� static ������ �ƴϹǷ� static �޼ҵ��� show1 �ȿ��� ��� �Ұ����ϴ�
		show4(); 					//(3) O - show4�� static �޼ҵ��̹Ƿ� static �޼ҵ��� show1 �ȿ��� ��� �����ϴ�
		show5(); 					//(4) X - show5�� static �޼ҵ尡 �ƴϹǷ� static �޼ҵ��� show1 �ȿ��� ��� �Ұ����ϴ�
	}

	public void show2() { //non-static �޼ҵ忡���� ���� Ŭ���� ���� �ƹ� �޼ҵ峪 ���� ��� ����
		System.out.println(num1);   //(5) O - show2�� static �޼ҵ尡 �ƴϹǷ� static ������ num1�� ��� �����ϴ�.
		System.out.println(num2);   //(6) O - show2�� static �޼ҵ尡 �ƴϹǷ� static ������ �ƴ� num2�� ��� �����ϴ�.
		show4(); 					//(7) O - show2�� static �޼ҵ尡 �ƴϹǷ� static �޼ҵ��� show4�� ��� �����ϴ�.
		show5(); 					//(8) O - show2�� static �޼ҵ尡 �ƴϹǷ� static �޼ҵ尡 �ƴ� show5�� ��� �����ϴ�.
	}

	public static void show4() {
	}

	public void show5() {
	}
	
}
