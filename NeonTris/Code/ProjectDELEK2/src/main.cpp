#include <TFT_eSPI.h> // Hardware-specific library
#include <SPI.h>
#include <SD.h>
#include <array>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>


SPIClass SPIADXL(HSPI);    // Make use of the HSPI spi bus for the ADXL sensor
TFT_eSPI tft = TFT_eSPI();       // Invoke custom library
WiFiServer server(80);

//JOYSTICK
#define VRX_PIN  36 // Arduino pin connected to VRX pin...
#define VRY_PIN  37 // Arduino pin connected to VRY pin

int xValue = 0; // To store value of the X axis
int yValue = 0; // To store value of the Y axis

String getMovementofJoyStick();


//BUTTON AND LEDS
int buttonPin = 22; //GPIO 2 knop
int LedPin1 = 21; //Leds
int LedPin2 = 32;

bool Led1State = true;
bool Led2State = false;
unsigned long prev_switch_time;

void turnDetermination();

//ACCELEROMETER
// setting parameters
#define BW_RATE     0x2C  //Data rate and power mode control

#define POWER_CTL   0x2D  //Power Control Register

#define DATA_FORMAT 0x31  //Data format control

#define DATAX0      0x32  //X-Axis Data 0

//TTGO T-display pins (Display uses SPI3)

#define MISO_ADXL  27  //GPIO27 = SDO

#define MOSI_ADXL  26  //GPIO26 = SDA

#define SCK_ADXL   25  //GIPO25 = SCL

#define CS_ADXL    33  //GPIO33 = CS

char values[10] = {'\0'};

int16_t x;

float xg, prev_xg;

void readRegister(char registerAddress, int16_t numBytes, char * values);
void writeRegister(char registerAddress, char value);
String getMovementofAccelerometer();

//WIFI-CONNECTION
bool WifiConnected = false;
const char *ssid = "NeonTris-Connection";
const char *password = "TimeToPlay";
void startGameConnection();
void drawWifiIntro();

//GRID
const int GRID_SIZE = 3;
const int CELL_SIZE = 100;
int xGrid = 1;
int yGrid = 1;
bool GameFinished = false;

std::array<std::array<String, 3>, 3> GridModel;


void drawGrid();
void drawBackground();
void drawNeonCross(int gridX, int gridY);
void drawNeonCircle(int gridX, int gridY);
void Focus(int gridX, int gridY);
void Unfocus(int gridX, int gridY);
void initGridModel();
bool thereIsAWinner();
bool thereIsADraw();
bool FullGrid();
void resetGame();


void setup() {

  //Set Baud Rate for Serial monitor
  Serial.begin(250000);

  //Display SETUP
  tft.init();
  tft.setRotation(3); // Adjust rotation if needed

  //WIFI
    WiFi.softAP(ssid, password);
    IPAddress myIP = WiFi.softAPIP();
    tft.init();
    drawWifiIntro();
    tft.setTextColor(ILI9341_BLACK);
    tft.setCursor(75, 60, 2);
    tft.println("1. Enter the SSID and password");
    tft.setCursor(75, 80, 2);
    tft.println("written on the back.");
    tft.setCursor(75, 100, 2);
    tft.println("2. Search this IP:");
    tft.setCursor(75, 120, 4);
    tft.println(myIP);
    tft.setCursor(80, 140, 2);
    tft.println("3. Press start to play!");
    server.begin();
    Serial.println("Server started");
  

  while (!WifiConnected){
      startGameConnection();
  }

  //Accelerometer SETUP
  pinMode(CS_ADXL, OUTPUT);
  digitalWrite(CS_ADXL, HIGH);

  SPIADXL.begin(SCK_ADXL, MISO_ADXL, MOSI_ADXL, CS_ADXL);
  SPIADXL.setDataMode(SPI_MODE3);
  SPIADXL.setBitOrder(MSBFIRST);
  SPIADXL.setFrequency(1000000);
  writeRegister(DATA_FORMAT, 0x03);  // ±16g 10bit
  writeRegister(POWER_CTL, 0x08);    
  writeRegister(BW_RATE, 0x0F); 

  //Button SETUP
  pinMode(LedPin1, OUTPUT);
  pinMode(LedPin2, OUTPUT);
  pinMode(buttonPin, INPUT);
  attachInterrupt(buttonPin, turnDetermination, RISING);

  //Grid SETUP;
  initGridModel();
  drawBackground();
  drawGrid();
  Focus(1,1);

}

void initGridModel() {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            GridModel[i][j] = ""; // Assign an empty string to each element
        }
    }
}

void loop() {

//JOYSTICK
  String directionJ = getMovementofJoyStick();
  Serial.print("JOYSTICK: ");
  Serial.println(directionJ);

  if (directionJ == "Moving up" && yGrid > 0) {
    Unfocus(xGrid, yGrid); // Unfocus current cell
    yGrid--; // Move up
    Focus(xGrid, yGrid); // Focus new cell
  } else if (directionJ == "Moving down" && yGrid < GRID_SIZE - 1) {
    Unfocus(xGrid, yGrid); // Unfocus current cell
    yGrid++; // Move down
    Focus(xGrid, yGrid); // Focus new cell
  } else if (directionJ == "Moving left" && xGrid > 0) {
    Unfocus(xGrid, yGrid); // Unfocus current cell
    xGrid--; // Move left
    Focus(xGrid, yGrid); // Focus new cell
  } else if (directionJ == "Moving right" && xGrid < GRID_SIZE - 1) {
    Unfocus(xGrid, yGrid); // Unfocus current cell
    xGrid++; // Move right
    Focus(xGrid, yGrid); // Focus new cell
  }

//BUTTON
  digitalWrite(LedPin1, Led1State);
  digitalWrite(LedPin2, Led2State);

  Serial.println(digitalRead(buttonPin));


//ACCELEROMETER
  String directionA = getMovementofAccelerometer();
  Serial.print("ACCELEROMETER: ");
  Serial.println(directionA);


  if (directionA == "Moving Right" && xGrid < GRID_SIZE - 1) {
      Unfocus(xGrid, yGrid); // Unfocus current cell
      xGrid++; // Move right
      Focus(xGrid, yGrid); // Focus new cell
  }
  
  if (directionA == "Moving Left" && xGrid > 0) {
      Unfocus(xGrid, yGrid); // Unfocus current cell
      xGrid--; // Move left
      Focus(xGrid, yGrid);
  } 

  if (GameFinished == true){
      resetGame();
  }


  delay(100);
}


void startGameConnection(){
  WiFiClient client = server.available();   // listen for incoming clients
  if (client) {                                            // if a client connects
    String currentLine = "";                               // String variable to hold incoming data from the client
    while (client.connected()) {                           // Loop as long the client is connected
      if (client.available()) {                            // If bytes are to be to read from the client, read a byte
        char c = client.read();            
        Serial.write(c);                                   // Print every char to the serial monitor
        if (c == '\n') {                                   // Check if the current line is blank, and the incoming char is blank, than it is end of the HTTP request
          if (currentLine.length() == 0) {
            // Send the HTTP response:
            client.println("HTTP/1.1 200 OK");            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            client.println("Content-type:text/html");     // and a content-type so the client knows what's coming, then a blank line:
            client.println();
            // the content of the HTTP response follows the header:
            client.print("<html><head><title>NeonTris!</title>");
            client.print("<style>body {display: flex; background-color: blue; color: white; }</style>");
            client.print("<style>.container { width: 50%; margin: auto; text-align: center; }</style>");
            client.print("</head><body><div class=\"container\"><h1>NeonTris</h1>");
            // Button style
            client.print("<style>.button { background-color: #800080; /* Purple */ border: none; color: white; padding: 15px 32px; text-align: center; text-decoration: none; display: inline-block; font-size: 20px; margin: 4px 2px; cursor: pointer; }</style>");
            // Start The Game!
            client.print("<button class=\"button\" onclick=\"startGame()\">Start Game!</button><br>");
            // JavaScript function to redirect to the '/START' URL
            client.print("<script>");
            client.print("function startGame() {");
            client.print("  window.location.href = '/START';");
            client.print("}");
            client.print("</script>");
            client.print("</body></html>");
            client.println(); 
            break;
          }
          else { 
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;      
        }
        // If pressed on start, website closes and the game can be played.
        if (currentLine.endsWith("GET /START")) {
          WifiConnected = true;
          client.stop();
        }

      }

    }



  }
}




void writeRegister(char registerAddress, char value) {
  digitalWrite(CS_ADXL, LOW);         //Sensor starts listening when CS is low
  SPIADXL.transfer(registerAddress);  //Transfer desired register
  SPIADXL.transfer(value);            //Transfer desired value
  digitalWrite(CS_ADXL, HIGH);
}


void readRegister(char registerAddress, int16_t numBytes, char * values) {

  //Prepare data before transmission
  char address = 0x80 | registerAddress;    //Set MSB to 1, leave rest intact
  if (numBytes > 1) {

    address = address | 0x40;               //Set x1xx xxxx to announce multiple bytes

  }
  digitalWrite(CS_ADXL, LOW);                //Make sensor active
  SPIADXL.transfer(address);                    //Activate data transfer on the sensor
  for (int16_t i = 0; i < numBytes; i++) {  //Write 0x00 for as many times you want to collect data.

    values[i] = SPIADXL.transfer(0x00);

  }
  digitalWrite(CS_ADXL, HIGH);               //Disable sensor communication
}



void IRAM_ATTR turnDetermination() {
  unsigned long switch_time = millis();
  if (switch_time - prev_switch_time > 200)
  {
    prev_switch_time = switch_time;

    //If cell is not full!
    if (GridModel[xGrid][yGrid] == ""){

      //X's turn?
      if (Led1State){
        drawNeonCross(xGrid, yGrid);
      }
      else{ //O's turn?
        drawNeonCircle(xGrid, yGrid);
      }

      if (thereIsAWinner() || thereIsADraw()){//Is there a winner or the game ends with a draw?, end game
        GameFinished = true;
      } 

      Led1State = !Led1State;
      Led2State = !Led2State;
    }


  }

}


String getMovementofAccelerometer(){

  readRegister(DATAX0, 6, values);
  x = ((int16_t)values[1] << 8) | (int16_t)values[0];
  // 0.03125 = (16*2)/(2^10)
  xg = x * 0.03125;

  if (xg < -0.2){
    return "Moving Right";
  }
  else if (xg > 0.2){
    return "Moving Left";
  }
  else{
    return "not moving";
  }

}

String getMovementofJoyStick(){
  xValue = analogRead(VRX_PIN);
  yValue = analogRead(VRY_PIN);

  Serial.println(xValue);
  Serial.println(yValue);

  if (0 <= xValue && xValue <= 3900 && 0 <= yValue && yValue <= 200){
    return "Moving up";
  }

  else if (0 <= yValue && yValue <= 3900 && 0 <= xValue && xValue <= 200){
    return "Moving left";
  }
  else if (yValue >= 3900){
    return "Moving down";
  }
  else if (0 <= yValue && yValue <= 3900 && xValue >= 3400){
    return "Moving right";
  }
  else{
    return "Not moving";
  }



}

void drawWifiIntro(){
  // Define screen dimensions
  int screenWidth = tft.width();
  int screenHeight = tft.height();

  // Define number of sections for mixed color
  int sections = 10;

  // Loop through sections and draw alternating colors
  for (int i = 0; i < sections; i++) {
    int sectionHeight = screenHeight / sections;
    int sectionY = i * sectionHeight;

    // Determine color for this section (blend of orange and red)
    int orangeComponent = map(i, 0, sections - 1, 255, 255); // Set to 255 for full orange
    int redComponent = map(i, 0, sections - 1, 0, 255);
    int blackComponent = 0; // Set to 0 for black

    // Draw rectangle with mixed color
    tft.fillRect(0, sectionY, screenWidth, sectionHeight, tft.color565(orangeComponent, redComponent, blackComponent));
  }
}



void drawBackground() {
  // Define screen dimensions
  int screenWidth = tft.width();
  int screenHeight = tft.height();

  // Define number of sections for mixed color
  int sections = 10;

  // Loop through sections and draw alternating colors
  for (int i = 0; i < sections; i++) {
    int sectionHeight = screenHeight / sections;
    int sectionY = i * sectionHeight;

    // Determine color for this section (blend of purple and blue)
    int purpleComponent = map(i, 0, sections - 1, 128, 255);
    int blueComponent = map(i, 0, sections - 1, 0, 128);

    // Draw rectangle with mixed color
    tft.fillRect(0, sectionY, screenWidth, sectionHeight, tft.color565(purpleComponent, 0, blueComponent));
  }
}

void drawGrid() {
  // Draw grid rectangles
  int cellWidth = tft.width() / GRID_SIZE;
  int cellHeight = tft.height() / GRID_SIZE;

  for (int row = 0; row < GRID_SIZE; ++row) {
    for (int col = 0; col < GRID_SIZE; ++col) {
      int x = col * cellWidth;
      int y = row * cellHeight;
      tft.drawRect(x, y, cellWidth, cellHeight, ILI9341_WHITE);
      tft.drawRect(x, y, cellWidth - 1, cellHeight - 1, ILI9341_WHITE);
      tft.drawRect(x, y, cellWidth + 1, cellHeight + 1, ILI9341_WHITE);
      tft.drawRect(x + 1, y + 1, cellWidth, cellHeight, ILI9341_WHITE);
      tft.drawRect(x + 2, y + 2, cellWidth, cellHeight, ILI9341_WHITE);
    }
  }
}


void Focus(int gridX, int gridY) {
  int cellX = gridX * (tft.width() / GRID_SIZE);
  int cellY = gridY * (tft.height() / GRID_SIZE);
  int cellWidth = tft.width() / GRID_SIZE;
  int cellHeight = tft.height() / GRID_SIZE;

  // Draw thick green edges around the cell
  int borderSize = 5; // Adjust the thickness of the border as needed

  tft.drawRect(cellX, cellY, cellWidth, cellHeight, TFT_GREEN);
  tft.drawRect(cellX, cellY, cellWidth - 1, cellHeight - 1, TFT_GREEN);
  tft.drawRect(cellX, cellY, cellWidth + 1, cellHeight + 1, TFT_GREEN);
  tft.drawRect(cellX + 1, cellY + 1, cellWidth, cellHeight, TFT_GREEN);
  tft.drawRect(cellX + 2, cellY + 2, cellWidth, cellHeight, TFT_GREEN);

}


void Unfocus(int gridX, int gridY) {
  int cellX = gridX * (tft.width() / GRID_SIZE);
  int cellY = gridY * (tft.height() / GRID_SIZE);
  int cellWidth = tft.width() / GRID_SIZE;
  int cellHeight = tft.height() / GRID_SIZE;


  tft.drawRect(cellX, cellY, cellWidth, cellHeight, ILI9341_WHITE);
  tft.drawRect(cellX, cellY, cellWidth - 1, cellHeight - 1, ILI9341_WHITE);
  tft.drawRect(cellX, cellY, cellWidth + 1, cellHeight + 1, ILI9341_WHITE);
  tft.drawRect(cellX + 1, cellY + 1, cellWidth, cellHeight, ILI9341_WHITE);
  tft.drawRect(cellX + 2, cellY + 2, cellWidth, cellHeight, ILI9341_WHITE);


}






void drawNeonCross(int gridX, int gridY) {
  int cellX = gridX * (tft.width() / GRID_SIZE);
  int cellY = gridY * (tft.height() / GRID_SIZE);
  int cellSize = min(tft.width(), tft.height()) / GRID_SIZE;

  // Calculate the center of the cell
  int centerX = cellX + cellSize / 2 + 10;
  int centerY = cellY + cellSize / 2;

  // Calculate the length of the cross arms
  int armLength = cellSize / 2;

  // Calculate the offset for drawing the cross at 45 degrees
  int offset = armLength / sqrt(2);

  // Draw the first arm of the cross
  tft.drawLine(centerX - offset, centerY - offset, centerX + offset, centerY + offset, TFT_RED);
  tft.drawLine(centerX - offset, centerY - offset + 1, centerX + offset, centerY + offset + 1, TFT_RED);
  tft.drawLine(centerX - offset, centerY - offset - 1, centerX + offset, centerY + offset - 1, TFT_RED);
  tft.drawLine(centerX - offset, centerY - offset + 2, centerX + offset, centerY + offset + 2, TFT_RED);
  tft.drawLine(centerX - offset, centerY - offset - 2, centerX + offset, centerY + offset - 2, TFT_RED);
  tft.drawLine(centerX - offset, centerY - offset + 3, centerX + offset, centerY + offset + 3, TFT_ORANGE);
  tft.drawLine(centerX - offset, centerY - offset - 3, centerX + offset, centerY + offset - 3, TFT_ORANGE);
  tft.drawLine(centerX - offset, centerY - offset + 4, centerX + offset, centerY + offset + 4, TFT_ORANGE);
  tft.drawLine(centerX - offset, centerY - offset - 4, centerX + offset, centerY + offset - 4, TFT_ORANGE);


  // Draw the second arm of the cross
  tft.drawLine(centerX - offset, centerY + offset, centerX + offset, centerY - offset, TFT_RED);
  tft.drawLine(centerX - offset, centerY + offset + 1, centerX + offset, centerY - offset + 1, TFT_RED);
  tft.drawLine(centerX - offset, centerY + offset - 1, centerX + offset, centerY - offset - 1, TFT_RED);
  tft.drawLine(centerX - offset, centerY + offset + 2, centerX + offset, centerY - offset + 2, TFT_RED);
  tft.drawLine(centerX - offset, centerY + offset - 2, centerX + offset, centerY - offset - 2, TFT_RED);
  tft.drawLine(centerX - offset, centerY + offset + 3, centerX + offset, centerY - offset + 3, TFT_ORANGE);
  tft.drawLine(centerX - offset, centerY + offset - 3, centerX + offset, centerY - offset - 3, TFT_ORANGE);
  tft.drawLine(centerX - offset, centerY + offset + 4, centerX + offset, centerY - offset + 4, TFT_ORANGE);
  tft.drawLine(centerX - offset, centerY + offset - 4, centerX + offset, centerY - offset - 4, TFT_ORANGE);

  GridModel[gridX][gridY] = "X";


}


void drawNeonCircle(int gridX, int gridY) {
  int cellX = gridX * (tft.width() / GRID_SIZE);
  int cellY = gridY * (tft.height() / GRID_SIZE);
  int cellSize = min(tft.width(), tft.height()) / GRID_SIZE;
  int radius = cellSize / 3; // Adjust the radius as needed
  int thickness = 6; // Adjust the thickness as needed

  // Calculate center coordinates of the circle, accounting for thickness
  int centerX = cellX + cellSize / 2 + thickness / 2 + 10;
  int centerY = cellY + cellSize / 2;

  // Draw the outermost circle with neon green color
  tft.drawCircle(centerX, centerY, radius + thickness + 1, TFT_CYAN);
  tft.drawCircle(centerX, centerY, radius + thickness + 2, TFT_CYAN);
  tft.drawCircle(centerX, centerY, radius + thickness + 3, TFT_CYAN);
  tft.drawCircle(centerX, centerY, radius, TFT_CYAN);
  tft.drawCircle(centerX, centerY, radius - 1, TFT_CYAN);
  tft.drawCircle(centerX, centerY, radius - 2, TFT_CYAN);
  tft.drawCircle(centerX, centerY, radius - 3, TFT_CYAN);
  // Draw additional concentric circles with increasing radii in GreenYellow
  for (int i = 1; i <= thickness; i++) {
    tft.drawCircle(centerX, centerY, radius + i, TFT_DARKCYAN);
  }

  GridModel[gridX][gridY] = "O";


}

bool thereIsAWinner() {
        for (String player : {"X", "O"}){ // Check rows
          for (std::array<String, 3> row : GridModel) {
              if (row[0] == player && row[1] == player && row[2] == player) {
                  return true;
              }
          }

          // Check columns
          for (int i = 0; i < 3; i++) {
              if (GridModel[0][i] == player &&
                  GridModel[1][i] == player &&
                  GridModel[2][i] == player) {
                  return true;
              }
          }

          // Check diagonals
          if (GridModel[0][0] == player &&
              GridModel[1][1] == player &&
              GridModel[2][2] == player) {
              return true;
          }
          if (GridModel[0][2] == player &&
              GridModel[1][1] == player &&
              GridModel[2][0] == player) {
              return true;
          }
        }

        // No winner found
        return false;
        

}

bool thereIsADraw() {
      if (FullGrid() && !thereIsAWinner()){
            return true;
      }
      else{
        return false;
      }
}

bool FullGrid(){
    for (int index = 0; index < 3; ++index){
        for (int index2 = 0; index2 < 3; ++index2){
            if (GridModel[index][index2] == ""){
                return false;
            }
        }
    }
    return true;
}


void resetGame() {
  // Reset the game state
  xGrid = 1;
  yGrid = 1;
  GameFinished = false;


  initGridModel();
  drawBackground();
  drawGrid();
  Focus(1,1);

}