package Main;

import java.awt.Color;
import java.awt.Image;
import java.awt.image.BufferedImage;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;

import javax.imageio.ImageIO;

public class PressureCell {
	double pressure;
	Color cellColor;
	int imageId;

	public BufferedImage cellImg;
	public Image scaledImg;

	public static BufferedImage initCellImg;
	public static Image initScaledImg;

	public static void Init() {
		try {
			initCellImg = ImageIO.read(ImageIO.createImageInputStream(
					new FileInputStream("C:/Users/Owner/workspace/Migration_v1/Assets/Square.png")));
			;
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
		tint(initCellImg, Color.WHITE);
		initScaledImg = initCellImg.getScaledInstance(16, 32, Image.SCALE_FAST);
	}

	public PressureCell() {
		this.cellImg = initCellImg;
		this.scaledImg = initScaledImg;
		this.pressure = 0;
		this.cellColor = Color.WHITE;
		imageId = 1;
	}

	public static void tint(BufferedImage img, Color tintColor) {
		for (int x = 0; x < img.getWidth(); x++) {
			for (int y = 0; y < img.getHeight(); y++) {
				// Color color = new Color(img.getRGB(x, y));
				img.setRGB(x, y, tintColor.getRGB());
			}
		}
	}

	public void modifyPressureLevel(double pressureValue) {
		if (pressureValue > 1) {
			pressureValue = 1;
		} else if (pressureValue < 0) {
			pressureValue = 0;
		}

		this.pressure = pressureValue;

		if (pressureValue == 0) {
			cellColor = Color.WHITE;
		} else if (pressureValue > 0 && pressureValue <= 0.25) {
			cellColor = Color.BLUE;
		} else if (pressureValue > 0.25 && pressureValue <= 0.5) {
			cellColor = Color.GREEN;
		} else if (pressureValue > 0.50 && pressureValue <= 0.75) {
			cellColor = Color.YELLOW;
		} else if (pressureValue > 0.75 && pressureValue <= 1.00) {
			cellColor = Color.RED;
		}

		tint(cellImg, this.cellColor);
		scaledImg = this.cellImg.getScaledInstance(16, 32, Image.SCALE_FAST);
	}
}
