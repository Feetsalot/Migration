package Main;

import java.awt.Color;
import java.awt.image.BufferedImage;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;

import javax.imageio.ImageIO;

public class PressureCell {
	double pressure;
	Color cellColor;
	
	BufferedImage cellImg;
	
	public PressureCell(){
		this.pressure = 0;
		this.cellColor = Color.BLUE;
		
		try {
			this.cellImg = ImageIO.read(ImageIO.createImageInputStream(new FileInputStream("C:/Users/Owner/workspace/Migration_v1/Assets/Square.png")));
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	public void modifyPressureLevel(double pressureValue){
		
		if(pressureValue > 1)
		{
			pressureValue = 1;
		} else if(pressureValue < 0)
		{
			pressureValue = 0;
		}
		
		this.pressure = pressureValue;
		
		if(pressureValue == 0)
		{
			cellColor = Color.BLUE;
		} else if (pressureValue > 0 && pressureValue < 0.5){
			cellColor = Color.GREEN;
		} else if (pressureValue > 0.5 && pressureValue < 1.0){
			cellColor = Color.YELLOW;
		} else if (pressureValue == 1.0){
			cellColor = Color.RED;
		}
	}
}
