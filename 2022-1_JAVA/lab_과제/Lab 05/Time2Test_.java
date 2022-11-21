//2021113772 이수민

//본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.

package Lab05;

class Time2 {

	// Constructor : 모두 second 기준으로 변경
	// Setter : Constructor처럼 모두 second 기준으로 변경
	// -> 총 몇 초인지 second = second + minute*60 + hour*60*60
	// Getter : 모두 원래 단위대로 변경 (출력은 그대로 나와야하니까)
	// hour = second/3600, minute=(second-(getHour()*60*60))/60,
	// second=second-(getHour()*60*60)-(getMinute()*60)

	/*
	 * if 1h10m5s -> 초로 변환 1*60*60+10*60+5=3600+600+5=4205
	 * 
	 * 다시 시간으로 변환 hour = second/3600 =1 minute = (second-(getHour()*60*60))/60=10
	 * second = second-getHour()*60*60-getMinute()*60=5
	 */

	// 1개 필드로 변경
	private int second; // 0 - 59

	// 생성자에서 입력받을 때 모두 초 단위로 hour*60*60, minute*60 으로 바꿔주고
	// 출력할 때

	// <<생성자>>
	// Time2 no-argument constructor:
	// initializes each instance variable to zero
	public Time2() {
		this(0, 0, 0); // invoke constructor with three arguments (네번째 생성자)
	}

	// Time2 constructor: hour supplied, minute and second defaulted to 0
	public Time2(int hour) {
		this(hour, 0, 0); // invoke constructor with three arguments
	}

	// Time2 constructor: hour and minute supplied, second defaulted to 0
	public Time2(int hour, int minute) {
		this(hour, minute, 0); // invoke constructor with three arguments
	}

	// Time2 constructor: hour, minute and second supplied
	public Time2(int hour, int minute, int second) {
		if (hour < 0 || hour >= 24) {
//			throw new IllegalArgumentException("hour must be 0-23");
		}

		if (minute < 0 || minute >= 60) {
//			throw new IllegalArgumentException("minute must be 0-59");
		}

		if (second < 0 || second >= 60) {
//			throw new IllegalArgumentException("second must be 0-59");
		}

		this.second = second + minute * 60 + hour * 60 * 60;

	}

	// Time2 constructor: another Time2 object supplied
	public Time2(Time2 time) {
		// invoke constructor with three arguments

		this(time.getHour(), time.getMinute(), time.getSecond());
	}

	// Set Methods
	// set a new time value using universal time;
	// validate the data
	public void setTime(int hour, int minute, int second) {
		// 예외 생기면 throw 후 생성자 리턴
		if (hour < 0 || hour >= 24) { // 시 분 초 다 잘못돼도 여기서 걸리면 이거만 출력하고 생성자 리턴
			// 그 뒤에있는 내용은 실행하지 않고 넘어감
			throw new IllegalArgumentException("hour must be 0-23");
		}

		if (minute < 0 || minute >= 60) {
			throw new IllegalArgumentException("minute must be 0-59");
		}

		if (second < 0 || second >= 60) {
			throw new IllegalArgumentException("second must be 0-59");
		}

		this.second = second + minute * 60 + hour * 60 * 60;

	}

	// validate and set hour
	public void setHour(int hour) {
		if (hour < 0 || hour >= 24) {
			throw new IllegalArgumentException("hour must be 0-23");
		}

		this.second = hour * 60 * 60;
	}

	// validate and set minute
	public void setMinute(int minute) {
		if (minute < 0 || minute >= 60) {
			throw new IllegalArgumentException("minute must be 0-59");
		}

		this.second = minute * 60;
	}

	// validate and set second
	public void setSecond(int second) {
		if (second < 0 || second >= 60) {
			throw new IllegalArgumentException("second must be 0-59");
		}

		this.second = second;
	}

	// hour = second/3600, minute=(second-(getHour()*60*60))/60,
	// second=second-(getHour()*60*60)-(getMinute()*60)

	// Get Methods
	// get hour value
	public int getHour() {
		return second / 3600;
	}

	// get minute value
	public int getMinute() {
		return (second - (getHour() * 60 * 60)) / 60;
	}

	// get second value
	public int getSecond() {
		return second - (getHour() * 60 * 60) - (getMinute() * 60);
	}

	// convert to String in universal-time format (HH:MM:SS)
	public String toUniversalString() {
		return String.format("%02d:%02d:%02d", getHour(), getMinute(), getSecond());
	}

	// convert to String in standard-time format (H:MM:SS AM or PM)
	public String toString() {
		return String.format("%d:%02d:%02d %s", ((getHour() == 0 || getHour() == 12) ? 12 : getHour() % 12),
				getMinute(), getSecond(), (getHour() < 12 ? "AM" : "PM"));
	}
}

public class Time2Test_ {
	public static void main(String[] args) {
		Time2 t1 = new Time2(); // 00:00:00
		Time2 t2 = new Time2(2); // 02:00:00
		Time2 t3 = new Time2(21, 34); // 21:34:00
		Time2 t4 = new Time2(12, 25, 42); // 12:25:42
		Time2 t5 = new Time2(t4); // 12:25:42

		System.out.println("Constructed with:");
		displayTime("t1: all default arguments", t1);
		displayTime("t2: hour specified; default minute and second", t2);
		displayTime("t3: hour and minute specified; default second", t3);
		displayTime("t4: hour, minute and second specified", t4);
		displayTime("t5: Time2 object t4 specified", t5);

		// attempt to initialize t6 with invalid values
		try { // 6번째 객체 생성
			Time2 t6 = new Time2(27, 74, 99); // invalid values
		} catch (IllegalArgumentException e) { // 예외 객체 받아서 예외 메시지 출력하고 끝
			System.out.printf("%nException while initializing t6: %s%n", e.getMessage());
		}
	}

	// displays a Time2 object in 24-hour and 12-hour formats
	private static void displayTime(String header, Time2 t) {
		System.out.printf("%s%n   %s%n   %s%n", header, t.toUniversalString(), t.toString());
	}
}
