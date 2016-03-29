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
	  

     
	public void paint(Graphics g)
	{	
		Graphics2D g2d = (Graphics2D)g;
                // 0, 640
                BufferedImage image;
                Image image1 = pg.cells[(32/32)][(32/32)].scaledImg; // calling this every loop slows down the grid a ton
                image = pg.cells[1][1].cellImg;
     

             
		for(int x=0; x<640; x+=32)
		   {
			   for(int y=0; y<480; y+=32)
			   {
                               if(pg.cells[(x/32)][(y/32)].imageId == 1 ){
                                   
                                   g2d.drawImage(image1,x,y,null);
                               }
                         
				   //tint(pg.cells[(x/32)][(y/32)].cellImg, pg.cells[(x/32)][(y/32)].cellColor);
				   //g2d.drawImage(pg.cells[(x/32)][(y/32)].cellImg.getScaledInstance(32, 32, Image.SCALE_DEFAULT), x, y, null);
     
				
			   }
			   
		   }
                for(int x=0; x<640; x+=32)
		   {
			   for(int y=0; y<480; y+=32)
			   {
                            
                            g2d.drawLine(0, y, 640, y);
                           }
                           g2d.drawLine(x, 0, x, 480);
                   }

	}
}



