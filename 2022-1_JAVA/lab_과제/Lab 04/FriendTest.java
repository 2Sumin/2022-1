package Lab04;

//2021113772 �̼���

//������ �� �ҽ������� �ٸ� ����� �ҽ��� �������� �ʰ� ���� �ۼ��Ͽ����ϴ�.

class Friend {
	String name;
	int age;

	public Friend(String name, int age) {
		super();
		this.name = name;
		this.age = age;
	}

	@Override
	public String toString() {
		return name + age;
	}
}

public class FriendTest {

	public static void main(String[] args) {
		// �Ʒ� �����͸� �̿��ؾ� ��
		String[] names = { "������", "��ȣ��", "�賲��" };
		int[] ages = { 1997, 1994, 1994 };

		// ��ü�迭 ����, for�� �̿�
		Friend[] friends = new Friend[3];
		for (int i = 0; i < friends.length; i++) {
			friends[i] = new Friend(names[i], ages[i]);
		}

		// counter controlled for���� ����� ��ü ���� ���,
		// System.out.printf�޼ҵ� ���, Friend�� toString�� �Ϲ������� ȣ���
		for (int i = 0; i < 3; i++) {
			System.out.printf("%s\n", friends[i]);
		}

		// enhanced for���� ����� ��ü ���� ���,
		// System.out.printf�޼ҵ� ���, Friend�� toString�� �Ϲ������� ȣ���
		for (Friend element : friends)
			System.out.printf("%s\n", element);

	}

}
