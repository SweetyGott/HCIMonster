color c = color(239, 12, 12);
Table table;
float scaleValue = 0;
int[] tableValues;
int i = 0;

void setup() {
  size(500,400);
  noFill();
  table = loadTable("pulseParsed.csv", "header");
  tableValues = new int[table.getRowCount()];
  int index = 0;
  for (TableRow row : table.rows()) {
    tableValues[index] = row.getInt("pulse");
    index++;
  }
  println(table.getRowCount() + " total rows in table"); 
  
}

void draw() { 
  background(255);
  runRow(tableValues[i]);
  if(i < tableValues.length-1){
    i++;
  }
}

void runRow(int value){
    scaleValue = float(value)/342;
    scale(scaleValue);
    display();
}


  
void display(){
  
  fill(c);
  
  //Herz
  beginShape();
  bezier(200, 200,  100, 100, 110, 75, 200, 120);
  bezier(200, 200,  300, 100, 275, 75, 200, 120);
  endShape();
}