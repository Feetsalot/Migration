package Main;

import java.awt.*;
import java.awt.event.*;
import java.awt.geom.AffineTransform;
import java.awt.geom.GeneralPath;
import java.awt.image.BufferedImage;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;

import javax.imageio.ImageIO;
import javax.swing.*;
	
public class Mainframe extends Frame {
	PressureGrid pg = new PressureGrid();
	int counter = 0;
	public static void main(String args[])
	{
		Mainframe mf = new Mainframe();
	}
	public Mainframe(){
		super ("Mainframe");
		
		setSize(640,480);
		setVisible(true);
		
		addWindowListener(new WindowAdapter()
		{ public void windowClosing (WindowEvent e)
			{ dispose(); System.exit(0);}
		}
		);
	}
	  
	public static void tint(BufferedImage img, Color tintColor) {
		for (int x = 0; x < img.getWidth(); x++) {
			for (int y = 0; y < img.getHeight(); y++) {
				//Color color = new Color(img.getRGB(x, y));
				img.setRGB(x, y, tintColor.getRGB());
			}
		}
	}
	
	public void paint(Graphics g)
	{	
		Graphics2D g2d = (Graphics2D)g;

		for(int x=0; x<640; x+=32)
		   {
			   for(int y=0; y<480; y+=32)
			   {
				   tint(pg.cells[(x/32)][(y/32)].cellImg, pg.cells[(x/32)][(y/32)].cellColor);
				   g2d.drawImage(pg.cells[(x/32)][(y/32)].cellImg.getScaledInstance(32, 32, Image.SCALE_DEFAULT), x, y, null);
				   g2d.drawLine(0, y, 640, y);
			   }
			   g2d.drawLine(x, 0, x, 480);
		   }
	}
}



