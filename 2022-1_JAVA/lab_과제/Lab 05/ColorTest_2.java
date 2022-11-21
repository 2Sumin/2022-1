//2021113772 �̼���

//������ �� �ҽ������� �ٸ� ����� �ҽ��� �������� �ʰ� ���� �ۼ��Ͽ����ϴ�.

package Lab05;

import java.util.EnumSet;

enum MyColor { // 4���� ���
	WHITE("Nina"), BLACK("Yuna"), YELLOW("Sumi"), RED("Mimi");

	private final String name; // 1���� String field

	private MyColor(String name) { // Constructor
		this.name = name;
	}

	public String getName() { // field�� �����ϴ� get �޼ҵ�� ������
		return name;
	}

}

public class ColorTest_2 {

	public static void main(String[] args) {

		// MyColor�� constant�� �迭�� �޾� ������� ����ϱ�
		// enhanced for�� ����ϱ� - for�� body�� �� �������� ������
		for (MyColor mycolor : MyColor.values()) {
			System.out.println(mycolor + "-" + mycolor.getName());
		}

		System.out.println();

		// MyColor�� constant �� 2~3��°�� �迭�� �޾� ������� ����ϱ�
		// enhanced for�� ����ϱ� - for�� body�� �ϳ��� �������� ������
		for (MyColor mycolor : EnumSet.range(MyColor.BLACK, MyColor.YELLOW)) {
			System.out.println(mycolor + "-" + mycolor.getName());
		}

	}

}
