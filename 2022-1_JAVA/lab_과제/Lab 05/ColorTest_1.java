//2021113772 �̼���

//������ �� �ҽ������� �ٸ� ����� �ҽ��� �������� �ʰ� ���� �ۼ��Ͽ����ϴ�.

package Lab05;

enum Color { //4���� ���
	WHITE,BLACK,YELLOW,RED;
}

public class ColorTest_1 {
	
	public static void main(String[] args) {
		// Color�� constant�� �迭�� �޾� ������� ����ϱ�
		//enhanced for�� ����ϱ� - for�� body�� �� �������� ������
		for (Color color : Color.values()) {
			System.out.println(color+" ");
		}
		
		
	}

}
