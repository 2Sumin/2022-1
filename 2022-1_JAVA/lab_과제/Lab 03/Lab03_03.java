package Lab03;
//2021113772 �̼���

//������ �� �ҽ������� �ٸ� ����� �ҽ��� �������� �ʰ� ���� �ۼ��Ͽ����ϴ�.

public class Lab03_03 {

	private enum Status {
		CONTINUE, WON, LOST
	};

	private enum Numbers {
		ZERO, ONE, TWO
	};

	public void play() {
		// systax errors - int���� ���� intNum1�� intNum2�� enum���� ���� enmNum1�� enmNum2�� �ڷ����� �ٸ��� ������ ���� ������ �Ұ����ϴ�.
		int intNum1 = Status.CONTINUE;
		int intNum2 = (int) Status.CONTINUE;
		Status enmNum1 = 1;
		Status enmNum2 = (Status) 1;

		// correct statements // switch�� ������ enum �ڷ����鳢�� ���ϹǷ� ������ �߻����� �ʴ´�. (���� �ڷ���)
		Numbers enumNum = Numbers.ZERO;
		switch (enumNum) {
		case ZERO:
			break;
		case ONE:
			break;
		case TWO:
			break;
		}

		// correct statements // switch�� ������ int �ڷ����鳢�� ���ϹǷ� ������ �߻����� �ʴ´�. (���� �ڷ���)
		final int intConsNum = 0; 
		int intNum3 = 0;
		switch (intNum3) {
		case intConsNum:
			break;
		}
		// systax error - intNum4�� �ڷ����� int�ε� ZERO�� �ڷ����� enum�̾ ���� �ٸ� �ڷ������� �񱳰� �Ұ����ϴ�.
		int intNum4 = 0;
		switch (intNum4) {
		case ZERO:
			break;
		}

	}

}
