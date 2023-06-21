//62050220
//62050243

import java.awt.*;
import java.awt.image.BufferedImage;
import javax.swing.*;
import java.util.*;


class Assignment1_62050243 extends JPanel 
{
	public static void main(String[] args) 
	{
		Assignment1_62050243 n = new Assignment1_62050243();
		JFrame f = new JFrame();
		f.add(n);
        f.setTitle("Assignment1");
        f.setSize(600, 600);
        f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		f.setVisible(true);		
	}

//================= Draw ==================================

	public void paintComponent(Graphics g)
	{
		BufferedImage buffer = new BufferedImage(601,601,BufferedImage.TYPE_INT_ARGB);
		Graphics2D g2 = buffer.createGraphics();
		
		g2.setColor(new Color(187, 245, 255));
		g2.fillRect(0, 0, 600, 600);

	//--------------------- Back ground -----------------------

		// grass
		g2.setColor(new Color(172, 209, 62));
		int [] gx1 = {0,600,0};
		int [] gy1 = {300,300,430};
		g2.fillPolygon(gx1, gy1, 3);
		g2.setColor(new Color(225, 209, 62));
		int [] gx2 = {600,600,0};
		int [] gy2 = {300,430,430};
		g2.fillPolygon(gx2, gy2, 3);
		
		// road
		g2.setColor(new Color(221, 202, 172 ));
		int [] rx1 = {0,600,0};
		int [] ry1 = {450,450,600};
		g2.fillPolygon(rx1, ry1, 3);
		g2.setColor(new Color(243, 202, 172 ));
		int [] rx2 = {600,600,0};
		int [] ry2 = {450,600,600};
		g2.fillPolygon(rx2, ry2, 3);

		// foot path
		g2.setColor(new Color(163, 142, 109 ));
		int [] fx1 = {0,600,0};
		int [] fy1 = {430,430,450};
		g2.fillPolygon(fx1, fy1, 3);
		g2.setColor(new Color(189, 142, 109 ));
		int [] fx2 = {600,600,0};
		int [] fy2 = {430,450,450};
		g2.fillPolygon(fx2, fy2, 3);

	//------------------------------cloud------------------------------

		cloud(g2, buffer, 13, -250, new Color(255,255,255));
		cloud(g2, buffer, 150, -210, new Color(255,255,255));

	//------------------------------sun-----------------------------------

		GradientPaint whiteToBlue = new GradientPaint(400, 0, new Color(230,251,255),280, 100, new Color(187, 245, 255));
		g2.setPaint(whiteToBlue);
		g2.fillArc(300, -250, 500, 500, 180, 200);
		g2.setColor(new Color(255, 208, 65));
		g2.fillArc(400, -150, 300, 300, 180, 200);

	//---------------------------- Building ------------------------------

		// building 1
		g2.setColor(new Color(0, 231, 243 ));
		int [] b1x1 = {30, 30, 70, 100, 100};
		int [] b1y1 = {300, 135, 100, 100, 300};
		g2.fillPolygon(b1x1, b1y1, 5);		
		g2.setColor(new Color(80, 246, 255));
		int [] shadowX1 = {70,100,100};
		int [] shadowY1 = {100,100,200};
		g2.fillPolygon(shadowX1,shadowY1,3);
		g2.setColor(new Color(23, 241, 252));
		int [] shadowX2 = {30,70,100};
		int [] shadowY2 = {135,100,200};
		g2.fillPolygon(shadowX2,shadowY2,3);

		// // building 2
		g2.setColor(new Color(0, 231, 243 ));
		int [] b2x2 = {125, 125, 150, 150, 180, 180};
		int [] b2y2 = {300, 120, 120, 140, 140, 300};
		g2.fillPolygon(b2x2, b2y2, 6);
		g2.setColor(new Color(80, 246, 255));
		int [] shadowX3 = {125,150,150};
		int [] shadowY3 = {120,120,140};
		g2.fillPolygon(shadowX3,shadowY3,3);
		g2.setColor(new Color(80, 246, 255));
		int [] shadowX4 = {150,180,180};
		int [] shadowY4 = {140,140,160};
		g2.fillPolygon(shadowX4,shadowY4,3);
		g2.setColor(new Color(23, 241, 252));
		int [] shadowX5 = {125,180,180};
		int [] shadowY5 = {300,160,300};
		g2.fillPolygon(shadowX5,shadowY5,3);

		// building 3
		g2.setColor(new Color(0, 231, 243 ));
		int [] b3x1 = {200,200,280,280};
		int [] b3y1 = {300,170,170,300};
		g2.fillPolygon(b3x1, b3y1, 4);
		g2.setColor(new Color(80, 246, 255));
		int [] shadowX6 = {200,280,280};
		int [] shadowY6 = {170,170,300};
		g2.fillPolygon(shadowX6,shadowY6,3);

		// building 4
		g2.setColor(new Color(0, 231, 243 ));
		int [] b4x1 = {290, 360, 290};
		int [] b4y1 = {100, 100, 300};
		g2.fillPolygon(b4x1, b4y1, 3);
		int [] b4x2 = {360, 360, 290};
		int [] b4y2 = {100, 300, 300};
		g2.fillPolygon(b4x2, b4y2, 3);
		g2.setColor(new Color(80, 246, 255));
		int [] shadowX7 = {290, 360,360};
		int [] shadowY7 = {100, 100,300};
		g2.fillPolygon(shadowX7,shadowY7,3);

		// building 5
		g2.setColor(new Color(0, 231, 243 ));
		int [] b5x = {370, 400, 425 };
		int [] b5y = {300, 125, 300 };
		g2.fillPolygon(b5x, b5y, 3);

		//building 6
		g2.setColor(new Color(0, 231, 243 ));
		int [] b6x11 = {450, 480, 480};
		int [] b6y11 = {100, 100, 300};
		g2.fillPolygon(b6x11, b6y11, 3);
		int [] b6x12 = {450, 480, 450};
		int [] b6y12 = {100, 300, 300};
		g2.fillPolygon(b6x12, b6y12, 3);
		int [] b6x21 = {500, 530, 530};
		int [] b6y21 = {100, 100, 300};
		g2.fillPolygon(b6x21, b6y21, 3);
		int [] b6x22 = {500, 530, 500};
		int [] b6y22 = {100, 300, 300};
		g2.fillPolygon(b6x22, b6y22, 3);
		int [] b6x31 = {480, 510, 480};
		int [] b6y31 = {165, 167, 175};
		g2.fillPolygon(b6x31, b6y31, 3);
		int [] b6x32 = {510 ,510 ,480};
		int [] b6y32 = {165 ,175 ,175};
		g2.fillPolygon(b6x32, b6y32, 3);
		g2.fillArc(450, 50, 30, 100, 0, 180);
		g2.fillArc(500, 50, 30, 100, 0, 180);

	//------------------- Bush ---------------------------------
	

		// Bush 1
		buffer = bush(g2, buffer, -20, 0, new Color(78, 130, 4));

		// Bush 2
		buffer = bush(g2, buffer, 45, 0, new Color(136, 173, 31));

		// Bush 3
		buffer = bush(g2, buffer, 110, 0, new Color(78, 130, 4));

		// Bush 4
		buffer = bush(g2, buffer, 175, 0, new Color(136, 173, 31));

		// Bush 5
		buffer = bush(g2, buffer, 240, 0, new Color(78, 130, 4));

		// Bush 6
		buffer = bush(g2, buffer, 305, 0, new Color(136, 173, 31));

		// Bush 7
		buffer = bush(g2, buffer, 370, 0, new Color(78, 130, 4));

		// Bush 8
		buffer = bush(g2, buffer, 435, 0, new Color(136, 173, 31));

		// Bush 9
		buffer = bush(g2, buffer, 500, 0, new Color(78, 130, 4));
		
	//-----------------------Tree-----------------------------

		// Tree Left
		tree(g2, buffer, -30, -50);

		// Tree Right
		tree(g2, buffer, -420, -50);

	//-----------------------People Sleep----------------------

		//people
		g2.setColor(new Color(255,219,131));
		g2.setStroke(new BasicStroke(3));
		g2.fillArc(350, 390, 80, 80, 0, 180);
		g2.setColor(new Color(235,235,235));
		g2.setStroke(new BasicStroke(3));
		g2.fillArc(170, 390, 200, 80, 0, 180);
		g2.setColor(new Color(0,0,0));
		g2.setStroke(new BasicStroke(4));
		g2.drawLine(405, 400, 410, 410);
		g2.setColor(new Color(255,125,125));
		g2.setStroke(new BasicStroke(1));
		g2.fillArc(370, 390, 30, 30, 90, 40);

		//bed
		g2.setColor(new Color(255,164,116));
		int [] bedx = {165,430,430,165};
		int [] bedy = {430,430,450,450};
		g2.fillPolygon(bedx,bedy,4);
		g2.setColor(new Color(70,70,70));
		g2.setStroke(new BasicStroke(7));
		g2.drawPolygon(bedx,bedy,4);
		g2.setStroke(new BasicStroke(7));
		g2.drawLine(165, 430, 430, 450);
		g2.setStroke(new BasicStroke(13));
		g2.drawLine(170, 460, 170, 490);
		g2.drawLine(425, 460, 425, 490);

		//zzz1
		g2.setColor(new Color(0,0,0));
		g2.setStroke(new BasicStroke(3));
		zzz(g2,0,0);

		//zzz2
		zzz(g2,15,-15);

		//zzz3
		zzz(g2,30,-30);

		g.drawImage(buffer, 0, 0, null);
	}

//=====================ZZZZ=====================

	public void zzz(Graphics g2,int x,int y)
	{
		g2.drawLine(375+x, 370+y, 385+x, 370+y);
		g2.drawLine(385+x, 370+y, 375+x, 380+y);
		g2.drawLine(375+x, 380+y, 385+x, 380+y);

	}

//=====================Bush=====================

	public BufferedImage bush(Graphics g2, BufferedImage buffer, int x, int y, Color replacementColor)
	{
		g2.setColor(replacementColor);
		g2.drawArc(15+x, 272+y, 50, 30, 120, 120);
		g2.drawArc(25+x, 262+y, 40, 40, 50, 115);
		g2.drawArc(50+x, 262+y, 40, 40, 20, 115);
		g2.drawArc(50+x, 272+y, 50, 30, 300, 120);
		g2.drawLine(28+x, 300+y, 89+x, 300+y);
		return floodFillFix(buffer, 50+x, 280+y, replacementColor, replacementColor);
	}

//=====================Tree=====================

	public BufferedImage tree(Graphics g2, BufferedImage buffer, int x, int y)
	{
		
		g2.setColor(new Color(145, 179, 43 ));
		bezier(g2,520+x, 415+y, 340+x, 440+y, 680+x, 440+y, 520+x, 415+y,1);
		buffer = floodFillFix(buffer, 521+x, 416+y, new Color(145, 179, 43 ), new Color(145, 179, 43 ));
		g2.setColor(new Color(115, 69, 29 ));
		bezier(g2,494+x, 426+y, 538+x, 339+y, 496+x, 337+y, 475+x, 305+y,1);
		g2.drawLine(475+x,305+y,480+x,302+y);
		g2.drawLine(480+x,302+y,512+x,342+y);
		g2.drawLine(512+x,342+y,506+x,273+y);
		g2.drawLine(506+x,273+y,510+x,274+y);
		g2.drawLine(510+x,274+y,527+x,344+y);
		g2.drawLine(527+x,344+y,573+x,311+y);
		g2.drawLine(573+x,311+y,574+x,314+y);
		bezier(g2,574+x, 314+y, 520+x, 345+y, 520+x, 382+y, 531+x, 427+y,1);
		g2.drawLine(494+x,426+y,531+x,427+y);
		buffer = floodFillFix(buffer, 513+x, 351+y, new Color(115, 69, 29 ), new Color(115, 69, 29 ));
		buffer = cloud(g2, buffer, 415+x, 15+y, new Color(153, 218, 73));
		buffer = cloud(g2, buffer, 415+x, 27+y, new Color(47, 99, 0));
		buffer = cloud(g2, buffer, 418+x, 20+y, new Color(78, 130, 3));
		buffer = cloud(g2, buffer, 415+40+x, 15-30+y, new Color(153, 218, 73));
		buffer = cloud(g2, buffer, 415+40+x, 27-30+y, new Color(47, 99, 0));
		buffer = cloud(g2, buffer, 418+40+x, 20-30+y, new Color(78, 130, 3));
		buffer = cloud(g2, buffer, 415+80+x, 15+y, new Color(153, 218, 73));
		buffer = cloud(g2, buffer, 415+80+x, 27+y, new Color(47, 99, 0));
		buffer = cloud(g2, buffer, 418+80+x, 20+y, new Color(78, 130, 3));

		return buffer;
	}

//===================cloud=======================

	public BufferedImage cloud(Graphics g2, BufferedImage buffer, int x, int y, Color replacementColor)
	{
		g2.setColor(replacementColor);
		g2.drawArc(15+x, 272+y, 50, 30, 120, 120);
		g2.drawArc(25+x, 262+y, 40, 40, 50, 115);
		g2.drawArc(50+x, 262+y, 40, 40, 20, 115);
		g2.drawArc(50+x, 272+y, 50, 30, 300, 120);
		g2.drawArc(25+x, 272+y, 40, 40, 200, 140);
		g2.drawArc(50+x, 272+y, 40, 40, 228, 140);

		return floodFillFix(buffer, 50+x, 280+y, replacementColor, replacementColor);
	}
	
//================= Curve =================================

	public void bezier (Graphics g, int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, int size)
	{
		for (int i = 0; i <= 1000; i++)
		{
			double t = i / 1000.0;
			int x = (int)(Math.pow((1 - t), 3)*x1 + 3*t*Math.pow((1-t), 2)*x2 + 3*t*t*(1-t)*x3 + t*t*t*x4);
			int y = (int)(Math.pow((1 - t), 3)*y1 + 3*t*Math.pow((1-t), 2)*y2 + 3*t*t*(1-t)*y3 + t*t*t*y4);
 
			plot (g,x,y,size);
		}
	}

//=============== Fill Color ===============================

	public BufferedImage floodFill(BufferedImage m, int x, int y, Color targetColor, Color replacementColor) 
    { 
        Queue<Point> q = new LinkedList<Point>();
        Graphics2D g2 = m.createGraphics();

        if (new Color(m.getRGB(x,y)).equals(targetColor));
        {
            g2.setColor(replacementColor);
            plot(g2,x,y,1);
            q.add(new Point(x,y));
        }

        while (!q.isEmpty()) 
        {
            Point p = q.poll();
            
            //south
            if (p.y < 600 && new Color(m.getRGB(p.x, p.y + 1)).equals(targetColor)) 
            {
                g2.setColor(replacementColor);
                plot(g2, p.x, p.y + 1, 1);
                q.add(new Point(p.x, p.y + 1));
            }
            
            //north
            if (p.y > 0 && new Color(m.getRGB(p.x, p.y - 1)).equals(targetColor)) 
            {
                g2.setColor(replacementColor);
                plot(g2, p.x, p.y - 1, 1);
                q.add(new Point(p.x, p.y - 1));
            }    
            
            //east
            if (p.y < 600 && new Color(m.getRGB(p.x + 1, p.y)).equals(targetColor)) 
            {
                g2.setColor(replacementColor);
                plot(g2, p.x + 1, p.y, 1);
                q.add(new Point(p.x + 1, p.y));
            }    
            
            //west
            if (p.y < 600 && new Color(m.getRGB(p.x - 1, p.y)).equals(targetColor)) 
            {
                g2.setColor(replacementColor);
                plot(g2, p.x - 1, p.y, 1);
                q.add(new Point(p.x - 1, p.y));
            }    
        }
        return m;
    }

//================= Plot ==================================

	private void plot(Graphics g, int x, int y, int size)
	{
		g.fillRect(x,y,size,size);
	}

//=================floodFillFix=====================

	/*NOTE This method check the lines instead of the background.*/

	public BufferedImage floodFillFix (BufferedImage m, int x, int y, Color borderColour, Color replacementColour)
	{
		Queue<Point> q = new LinkedList<Point>();
		Graphics2D g2 = m.createGraphics();
		if (!new Color(m.getRGB(x, y)).equals(borderColour) && !new Color(m.getRGB(x, y)).equals(replacementColour))
		{
			g2.setColor(replacementColour);
			plot(g2, x, y, 1);
			q.add(new Point(x, y));
		}

		while (!q.isEmpty ())
		{
			Point p = q.poll();
			//south
			if (p.y < 600 && !new Color(m.getRGB(p.x, p.y + 1)).equals(borderColour) && !new Color(m.getRGB(p.x, p.y + 1)).equals(replacementColour))
			{
				g2.setColor(replacementColour);
				plot(g2, p.x, p.y + 1, 1);
				q.add(new Point(p.x, p.y + 1));
			}
			//north
			if (p.y > 0 && !new Color(m.getRGB(p.x, p.y - 1)).equals(borderColour) && !new Color(m.getRGB(p.x, p.y - 1)).equals(replacementColour))
			{
				g2.setColor(replacementColour);
				plot(g2, p.x, p.y - 1, 1);
				q.add(new Point(p.x, p.y - 1));
			}
			//east
			if (p.x < 600 && !new Color(m.getRGB(p.x + 1, p.y)).equals(borderColour) && !new Color(m.getRGB(p.x + 1, p.y)).equals(replacementColour))
			{
				g2.setColor(replacementColour);
				plot(g2, p.x + 1, p.y, 1);
				q.add(new Point(p.x + 1, p.y));
			}

			//west
			if (p.x > 0 && !new Color(m.getRGB(p.x - 1, p.y)).equals(borderColour) && !new Color(m.getRGB(p.x - 1, p.y)).equals(replacementColour))
			{
				g2.setColor(replacementColour);
				plot(g2, p.x - 1, p.y, 1);
				q.add(new Point(p.x - 1, p.y));
			}
		}
		return m;
	}
}
