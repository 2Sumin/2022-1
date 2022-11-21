//2021113772 이수민

import java.awt.Color;
import java.awt.Container;
import java.awt.FlowLayout;
import java.awt.Font;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JTextField;
import javax.swing.SwingConstants;

class GUI extends JFrame {
	private JTextField count;
	private final JLabel myName;
	private String[] moneyUnit = { "오만원", "만원", "천원", "500원", "100원", "50원", "10원", "1원" };
	private JTextField result[] = new JTextField[8];
	private JCheckBox[] checkbox = new JCheckBox[moneyUnit.length - 1];

	public GUI() {
		super("Money Changer");
		setLayout(new FlowLayout());
		setLayout(null);

		Container container = getContentPane();
		container.setBackground(Color.PINK);

		JLabel price = new JLabel("금액");
		price.setHorizontalAlignment(SwingConstants.CENTER);
		price.setSize(50, 20);
		price.setLocation(20, 20);
		add(price);

		count = new JTextField(30);
		count.setSize(100, 20);
		count.setLocation(100, 20);
		count.setHorizontalAlignment(SwingConstants.LEFT);
		count.addActionListener(new MyActionListener());

		JButton button = new JButton("계산");
		button.addActionListener(new MyActionListener());
		button.setSize(70, 20);
		button.setLocation(210, 20);

		container.add(price);
		container.add(count);
		container.add(button);

		for (int i = 0; i < moneyUnit.length; i++) {
			int loc = 50 + i * 20;
			price = new JLabel(moneyUnit[i]);
			price.setSize(60, 20);
			price.setLocation(50, loc);
			add(price);

			result[i] = new JTextField(35);
			result[i].setHorizontalAlignment(SwingConstants.CENTER);
			result[i].setSize(80, 20);
			result[i].setLocation(100, loc);
			add(result[i]);
		}

		// 체크박스
		for (int i = 0; i < checkbox.length; i++) {
			checkbox[i] = new JCheckBox();
			checkbox[i].setSize(40, 20);
			checkbox[i].setBackground(Color.PINK);
			checkbox[i].setLocation(220, 50 + i * 20);
			add(checkbox[i]);
		}

		// 하단에 학번 이름
		myName = new JLabel();
		myName.setText("2021113772 이수민");
		myName.setHorizontalTextPosition(SwingConstants.CENTER);
		myName.setVerticalTextPosition(SwingConstants.BOTTOM);
		myName.setSize(150, 20);
		myName.setLocation(70, 230);
		add(myName);
	}

	private class MyActionListener implements ActionListener {
		public void actionPerformed(ActionEvent event) {
			int[] money = { 50000, 10000, 1000, 500, 100, 50, 10, 1 };
			int[] res = new int[money.length];

			int total = Integer.valueOf(count.getText());

			for (int i = 0; i < money.length; i++) {
				// #1원짜리 동전은 체크박스가 주어지지 않으며 항상 참여시킨다
				// 화폐 단위가 1원이면 체크박스 상관없이 무조건 표현
				if (i == money.length - 1) {
					res[i] = total / money[i];
					result[i].setText(String.valueOf(res[i]));
				}
				// 나머지 화폐단위에 대해서는 체크되어있으면 화폐 계산
				// 체크 안돼있으면 0원 표시
				if (!checkbox[i].isSelected()) {
					result[i].setText("0");
					continue;
				}
				// 체크되어있으면 화폐 변환
				res[i] = total / money[i];
				result[i].setText(String.valueOf(res[i]));
				total %= money[i];
			}
		}
	}

}

public class _1 {
	public static void main(String[] args) {
		GUI gui = new GUI();
		gui.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		gui.setSize(300, 350);
		gui.setVisible(true);
	}
}