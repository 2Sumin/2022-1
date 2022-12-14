//2021113772 이수민

import java.util.Comparator;

public class Student implements Comparator<Student> {
	private int StudentId;
	private String FirstName, LastName;

	public Student() {
		this(0, "", "");
	}

	public Student(int StudentId, String FirstName, String LastName) {
		this.StudentId = StudentId;
		this.FirstName = FirstName;
		this.LastName = LastName;
	}

	public int getStudentId() {
		return StudentId;
	}

	public void setStudentId(int StudentId) {
		this.StudentId = StudentId;
	}

	public String getFirstName() {
		return FirstName;
	}

	public void setFirstName(String FirstName) {
		this.FirstName = FirstName;
	}

	public String getLastName() {
		return LastName;
	}

	public void setLastName(String LastName) {
		this.LastName = LastName;
	}

	@Override
	public int compare(Student o1, Student o2) {
		return o1.getStudentId() - o2.getStudentId();
	}

	//조건_1. Student의 toString을 반드시 사용해서 출력해야 함
	@Override
	public String toString() {
		return "Student[" + StudentId + ", " + FirstName + ", " + LastName + "]";
	}

}