package Lab03;
//2021113772 이수민

//본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.

public class Lab03_03 {

	private enum Status {
		CONTINUE, WON, LOST
	};

	private enum Numbers {
		ZERO, ONE, TWO
	};

	public void play() {
		// systax errors - int형의 변수 intNum1과 intNum2는 enum형의 변수 enmNum1과 enmNum2와 자료형이 다르기 때문에 서로 대입이 불가능하다.
		int intNum1 = Status.CONTINUE;
		int intNum2 = (int) Status.CONTINUE;
		Status enmNum1 = 1;
		Status enmNum2 = (Status) 1;

		// correct statements // switch문 내에서 enum 자료형들끼리 비교하므로 에러가 발생하지 않는다. (같은 자료형)
		Numbers enumNum = Numbers.ZERO;
		switch (enumNum) {
		case ZERO:
			break;
		case ONE:
			break;
		case TWO:
			break;
		}

		// correct statements // switch문 내에서 int 자료형들끼리 비교하므로 에러가 발생하지 않는다. (같은 자료형)
		final int intConsNum = 0; 
		int intNum3 = 0;
		switch (intNum3) {
		case intConsNum:
			break;
		}
		// systax error - intNum4는 자료형이 int인데 ZERO는 자료형이 enum이어서 서로 다른 자료형끼리 비교가 불가능하다.
		int intNum4 = 0;
		switch (intNum4) {
		case ZERO:
			break;
		}

	}

}
