//2021113772 이수민

import java.io.IOException;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Scanner;

public class _2 {

	public static void main(String[] args) {
		int a;
		String str1, str2;

		try (Scanner input = new Scanner(Paths.get("input.txt"))) {
			List<Student> student = new ArrayList<Student>();
			// 1. 입력파일 (input.txt)의 각 행을 읽을 때마다 하나의 Student 객체를 생성해서 ArrayList에 저장
			// 입력 데이터를 화면에 출력
			System.out.println("StudentId First Name Last Name");
			a = input.nextInt();
			str1 = input.next();
			str2 = input.next();
			student.add(new Student(a, str1, str2));
			System.out.printf("%-8d  %-10s %-10s %n", a, str1, str2);

			while (input.hasNext()) {
				a = input.nextInt();
				str1 = input.next();
				str2 = input.next();
				student.add(new Student(a, str1, str2));
				System.out.printf("%-8d  %-10s %-10s %n", a, str1, str2);
			}
			System.out.println();

			// 2. 정렬 전 ArrayList를 출력한다
			System.out.println("Unsorted array elements:");
			System.out.println("[");
			for (int i = 0; i < student.size(); i++) {
				if (i != student.size() - 1) {
					System.out.println(student.get(i) + ",");
				} else if (i == student.size() - 1) {
					System.out.println(student.get(i) + "]");
				}
			}
			System.out.println();

			// 3. Student의 studentId 순으로 객체를 정렬한다
			// 조건_2. Collections의 sort 메소드를 사용해서 정렬해야 함
			Collections.sort(student, new Student());
			// 4. 정렬 후 ArrayList를 출력한다
			System.out.println("Sorted array elements:");
			System.out.println("[");
			for (int i = 0; i < student.size(); i++) {
				if (i != student.size() - 1) {
					System.out.println(student.get(i) + ",");
				} else if (i == student.size() - 1) {
					System.out.println(student.get(i) + "]");
				}
			}
			System.out.println();

		} catch (IOException ioException) {
			ioException.printStackTrace();
		}
	}
}
