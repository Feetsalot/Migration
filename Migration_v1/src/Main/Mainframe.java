package Main;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Image;
import java.awt.Toolkit;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.image.BufferedImage;
import java.net.URL;
import java.util.logging.Level;
import java.util.logging.Logger;

import javax.swing.JFrame;
import javax.swing.JPanel;

public class Mainframe extends JFrame {
	private static final long serialVersionUID = 1L;

	public static void main(String args[]) {
		new Mainframe();
	}

	public Mainframe() {
		MainPanel mp = new MainPanel();
		setSize(645, 505);
		setTitle("Main Frame");
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setVisible(true);
		setResizable(false);
		add(mp);

	}

	public class MainPanel extends JPanel implements Runnable {
		private static final long serialVersionUID = 1L;
		Image dbImage;
		int PWIDTH = 640;
		int PHEIGHT = 480;
		Graphics dbg;
		Thread program;
		boolean running = false;
		long period = 6 * 1000000; // Milliseconds -> Nanoseconds
		static final int DELAYS_BEFORE_YEILD = 10;

		int counter = 0;

		PressureGrid pg = new PressureGrid();

		BufferedImage squareBuffer;
		URL url = null;

		public MainPanel() {
			setFocusable(true);
			requestFocusInWindow();
			addKeyListener(new KeyAdapter() {

				@Override
				public void keyPressed(KeyEvent e) {
					System.out.println("Key Pressed: " + e);
				}
			});
			addMouseListener(new MouseAdapter() {
				@Override
				public void mousePressed(MouseEvent e) {
					int mx = e.getX();
					int my = e.getY();
					System.out.println(pg.cells[(int) Math.floor(mx / 16)][(int) Math.floor(my / 32)].pressure);
					pg.cells[(int) Math.floor(mx / 16)][(int) Math.floor(my / 32)].modifyPressureLevel(
							pg.cells[(int) Math.floor(mx / 16)][(int) Math.floor(my / 32)].pressure + 0.25);
					System.out.println(pg.cells[(int) Math.floor(mx / 16)][(int) Math.floor(my / 32)].pressure);
				}
			});
		}

		@Override
		public void run() {
			long beforeTime, afterTime, diff, sleepTime, overSleepTime = 0;
			int delays = 0;

			while (running) {
				beforeTime = System.nanoTime();

				render();
				paintScreen();

				afterTime = System.nanoTime();
				diff = afterTime - beforeTime;
				sleepTime = (period - diff) - overSleepTime;
				// If the sleep time is between 0 and the period sleep
				if (sleepTime < period && sleepTime > 0) {
					try {
						Thread.sleep(sleepTime / 100000L);
						overSleepTime = 0;
					} catch (InterruptedException e) {
						Logger.getLogger(MainPanel.class.getName()).log(Level.SEVERE, null, false);
					}
				}
				// The difference was greater than the period
				else if (diff > period) {
					overSleepTime = diff - period;
				}
				// Accumulate the amount of delays and eventually yield the
				// thread
				else if (++delays >= DELAYS_BEFORE_YEILD) {
					Thread.yield();
					delays = 0;
					overSleepTime = 0;
				}

			}
		}

		private void render() {
			if (dbImage == null) { // Create the buffer
				dbImage = createImage(PWIDTH, PHEIGHT);
				if (dbImage == null) {
					System.err.println("dbImage is still null!");
					return;
				} else {
					dbg = dbImage.getGraphics();
				}
			}
			// Clear the screen
			dbg.setColor(Color.WHITE);
			dbg.fillRect(0, 0, PWIDTH, PHEIGHT);

			draw(dbg);
		}

		public void drawPressureGrid(Graphics g) {
			Graphics2D g2d = (Graphics2D) g;

			// Draw the cells for the grid
			for (int x = 0; x < 640; x += 16) {
				for (int y = 0; y < 480; y += 32) {
					if (pg.cells[(x / 16)][(y / 32)].imageId == 1) {
						g2d.drawImage(pg.cells[x / 16][y / 32].scaledImg, x, y, null);
					}
				}
			}
			// Draw the dividing lines for the Grid
			g2d.setColor(Color.BLACK);

			for (int x = 0; x < 640; x += 16) {
				for (int y = 0; y < 480; y += 32) {
					g2d.drawLine(0, y, 640, y);
				}
				g2d.drawLine(x, 0, x, 480);
			}
		}

		public void draw(Graphics g) {
			drawPressureGrid(g);
		}

		private void paintScreen() {
			Graphics g;
			try {
				g = this.getGraphics();
				if (dbImage != null && g != null) {
					g.drawImage(dbImage, 0, 0, null);
				}
				Toolkit.getDefaultToolkit().sync(); // For some operating
													// systems
				g.dispose();
			} catch (Exception e) {
				System.err.println(e);
				System.exit(1);
			}
		}

		@Override
		public void addNotify() {
			super.addNotify();
			startProgram();
		}

		private void startProgram() {
			if (program == null || !running) {
				program = new Thread(this);
				program.start();
				running = true;
			}
		}

	}
}
