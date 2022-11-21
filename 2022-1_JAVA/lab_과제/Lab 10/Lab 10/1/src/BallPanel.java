//2021113772 이수민
//본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.

// JPanel that creates a ball when the mouse is pressed.  Ball bounces
// around the JPanel.
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.util.ArrayList;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

import javax.swing.JFrame;
import javax.swing.JPanel;

public class BallPanel extends JPanel {
	private ArrayList<Ball> ballArray = new ArrayList<Ball>();
	private ExecutorService threadExecutor; // for running Ball runnable
	private JFrame parentWindow; // parent window of JPanel
	private final int MAX_X = 200; // horizontal edge of JPanel
	private final int MAX_Y = 200; // vertical edge of JPanel

	public BallPanel(JFrame window) {
		parentWindow = window; // set parent window of JPanel

		// create ExecutorService for running ball runnable
		threadExecutor = Executors.newCachedThreadPool();

		// anonymous inner class handles mouse events
		this.addMouseListener(new MouseAdapter() {
			public void mousePressed(MouseEvent event) {
				createBall(event); // delegate call to ball starter
				RepaintTimer timer = new RepaintTimer(parentWindow);
				threadExecutor.execute(timer);
			} // end method mousePressed
		} // end anonymous inner class
		); // end call to addMouseListener
	} // end BallPanel constructor

	// create a ball if no ball exists and set it in motion
	private void createBall(MouseEvent event) {
		int x = event.getX(); // get x position of mouse press
		int y = event.getY(); // get y position of mouse press
		Ball newBall = new Ball(x, y); // create new ball
		ballArray.add(newBall);
		threadExecutor.execute(newBall); // set ball in motion
	} // end method createBall

	// return minimum size of animation
	public Dimension getMinimumSize() {
		return getPreferredSize();
	} // end method getMinimumSize

	// return preferred size of animation
	public Dimension getPreferredSize() {
		return new Dimension(MAX_X, MAX_Y);
	} // end method getPreferredSize

	// draw ball at current position
	public void paintComponent(Graphics g) {
		super.paintComponent(g);

		for (Ball tmp : ballArray) {
			g.setColor(tmp.getColor()); // random color
			g.fillOval(tmp.getX(), tmp.getY(), 10, 10); // draws
		} 
	} // end method paintComponent
}
// end class BallPanel