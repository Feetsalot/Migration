package Main;

import java.awt.Color;
import java.awt.image.BufferedImage;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;

import java.awt.*;

import javax.imageio.ImageIO;

public class PressureCell {
	double pressure;
	Color cellColor;
	
	BufferedImage cellImg;
        Image scaledImg;
        
        int imageId;
	
	public PressureCell(){
		this.pressure = 0;
		this.cellColor = Color.BLUE;
                imageId = 1;
                
		
		try {
			this.cellImg = ImageIO.read(ImageIO.createImageInputStream(new FileInputStream("C:\\Users\\ethan\\OneDrive\\Documents\\Github\\Migration_v1\\Assets\\Square.png")));
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
              tint(this.cellImg,this.cellColor);
              scaledImg=  this.cellImg.getScaledInstance(32, 32, this.cellImg.SCALE_FAST);
              
	}
        
        public static void tint(BufferedImage img, Color tintColor) {
            for (int x = 0; x < img.getWidth(); x++) {
                    for (int y = 0; y < img.getHeight(); y++) {
                            //Color color = new Color(img.getRGB(x, y));
                            img.setRGB(x, y, tintColor.getRGB());
                    }
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
