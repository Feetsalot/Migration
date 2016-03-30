package Main;

public class PressureGrid {

	public PressureCell[][] cells = new PressureCell[40][15];

	public PressureGrid(){
	PressureCell.Init();
		for (int x=0; x < 40; x++)
		{
			for (int y=0; y<15; y++)
			{
				cells[x][y] = new PressureCell();
				
			}
		}
		System.out.println(cells[0][0]);
	}
	
	public void modifyCell(int cellIndex_x, int cellIndex_y, double pressureValue){
		this.cells[cellIndex_x][cellIndex_y].modifyPressureLevel(pressureValue);
	}
}
