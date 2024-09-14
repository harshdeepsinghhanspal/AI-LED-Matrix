String dataString = "";
int px_val=4;
int binaryMatrix[px_val][px_val]; // To store the px_val x px_val matrix

//Assume there is 4x4 matrix
//Manually remove/ add the values as required
int led[px_val][px_val] = {
  {0, 4, 8, A1},
  {1, 5, 9, A0},
  {2, 6, 10, 13},
  {3, 7, 11, 12}
}; 

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < px_val; i++) {
        for (int j = 0; j < px_val; j++) {
          pinMode(led[i][j], OUTPUT);
        }
      }
}

void loop() {
  if (Serial.available() > 0) {
    char receivedChar = Serial.read();
    
    if (receivedChar != '\n') {
      dataString += receivedChar;
    } 
    else {
      int index = 0;
      int row = 0, col = 0;
      while ((index = dataString.indexOf(',')) != -1) {
        binaryMatrix[row][col] = dataString.substring(0, index).toInt();
        dataString = dataString.substring(index + 1);
        
        col++;
        if (col == px_val) {
          col = 0;
          row++;
        }
      }

      binaryMatrix[row][col] = dataString.toInt();

      dataString = "";

      for (int i = 0; i < px_val; i++) {
        for (int j = 0; j < px_val; j++) {
          if(binaryMatrix[i][j]=='1'){
            digitalWrite(led[i][j], HIGH);
          }
          else{
            digitalWrite(led[i][j], LOW);  
          }
          Serial.print(binaryMatrix[i][j]);
          Serial.print(" ");
        }
        Serial.println();
      }
    }
  }
}
