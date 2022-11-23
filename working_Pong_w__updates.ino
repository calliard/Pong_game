#include <TVout.h>
#include <fontALL.h>


TVout TV;
//#define WHEEL_ONE_PIN 0 //analog
//#define WHEEL_TWO_PIN 1 //analog
//#define BUTTON_ONE_PIN 2 //analog
//#define BUTTON_ONE_PIN 2 //digital to start game
#define BUTTON_TWO_PIN 3 //digital to reset and go back to main menu
//#define UP_PIN 5
//#define DOWN_PIN 6

#define PADDLE_HEIGHT 14
#define PADDLE_WIDTH 1

#define RIGHT_PADDLE_X (TV.hres()-4)
#define LEFT_PADDLE_X 2

#define IN_GAMEA 0 //in game state - draw constants of the game box
#define IN_GAMEB 0 //in game state - draw the dynamic part of the game

#define IN_MENU 1 //in menu state
#define GAME_OVER 2 //game over state
#define START_OVER 3 // start game over


#define LEFT_SCORE_X (TV.hres()/2-15)
#define RIGHT_SCORE_X (TV.hres()/2+10)
#define SCORE_Y 4

#define MAX_Y_VELOCITY 6
#define PLAY_TO 5







#define LEFT 2
#define RIGHT 3

//TVout TV;
unsigned char x, y;

boolean button1Status = false;
boolean button2Status = false; //out

int AIposition = 0;

int wheelTwoPosition = 0;
int rightPaddleY = 0;
int leftPaddleY = 0;
unsigned char ballX = 0;
unsigned char ballY = 0;
char ballVolX = 2;
char ballVolY = 2;

int leftPlayerScore = 0;
int rightPlayerScore = 0;

int frame = 0;
int state = IN_MENU;

int Reset = 12;


const int SW_pin = 10;
const int Y_pin = A1;
void setup() {
pinMode(SW_pin, INPUT);      //setup SW input
digitalWrite(SW_pin, HIGH);
}


void processInputs() {
  wheelTwoPosition = (analogRead(Y_pin));
  delay(50);
  button1Status = (digitalRead(SW_pin));
void int readAxis(int thisAxis){
    int reading = analogRead(thisAxis);
    reading = map(readig, 0, 126,0,range);
    int distance = reading - center;
    if(abs(distace) < threshold){
      distance = 0;
    }
    return distance;
  }
  int yReading = readAxis(A1);



//button2Status = (digitalRead(BUTTON_TWO_PIN) == LOW);  //out
  if ((button1Status == false) && (state == GAME_OVER))

    if ((button1Status == false) && (state == START_OVER))



      delay(50);
  //Serial.println(button1Status);
  //Serial.println(state);
  //Serial.println(button2Status);
  //Serial.println(wheelOnePosition);
  //Serial.println(wheelTwoPosition);



}



void drawGameScreen() {
  //  TV.clear_screen();

  if (ballY > AIposition) {
    AIposition++;
  }
  else if (ballY < AIposition) {
    AIposition--;
  }

  //draw right paddle
  rightPaddleY = ((AIposition * 2) * (TV.vres() - PADDLE_HEIGHT)) / 128;
  x = RIGHT_PADDLE_X;
  for (int i = 0; i < PADDLE_WIDTH; i++) {
    TV.draw_line(x + i, rightPaddleY, x + i, rightPaddleY + PADDLE_HEIGHT, 1);

  }
  leftPaddleY = ((wheelTwoPosition / 8) * (TV.vres() - PADDLE_HEIGHT)) / 128;
  x = LEFT_PADDLE_X;
  for (int i = 0; i < PADDLE_WIDTH; i++) {
    TV.draw_line(x + i, leftPaddleY, x + i, leftPaddleY + PADDLE_HEIGHT, 1);
  }




  //draw score
  TV.print_char(LEFT_SCORE_X, SCORE_Y, '0' + leftPlayerScore);
  TV.print_char(RIGHT_SCORE_X, SCORE_Y, '0' + rightPlayerScore);






  //draw ball
  TV.set_pixel(ballX, ballY, 2);
}



//player == LEFT or RIGHT
void playerScored(byte player) {
  if (player == LEFT) leftPlayerScore++;
  if (player == RIGHT) rightPlayerScore++;

  //check for win
  if (leftPlayerScore == PLAY_TO) {
    state = GAME_OVER;
  }
  //check for lose
  if (rightPlayerScore == PLAY_TO) {
    state = START_OVER;
  }

  ballVolX = -ballVolX;
}



void drawBox() {
  TV.clear_screen();

  //draw net
  for (int i = 1; i < TV.vres() - 4; i += 6) {
    TV.draw_line(TV.hres() / 2, i, TV.hres() / 2, i + 3, 1);
  }
  // had to make box a bit smaller to fit tv
  TV.draw_line(0, 0, 0, 95, 1 ); // left
  TV.draw_line(0, 0, 126, 0, 1 ); // top
  TV.draw_line(126, 0, 126, 95, 1 ); // right
  //TV.draw_line(0, 0, 126, 95, 1 ); // right
  TV.draw_line(0, 95, 126, 95, 1 ); // bottom


  state = IN_GAMEB;
}


void drawMenu() {
  x = 0;
  y = 0;
  char volX = 3;
  char volY = 3;
  TV.clear_screen();
  TV.select_font(font8x8);
  TV.print(10, 5, "Pong");
  TV.select_font(font4x6);
  TV.print(22, 35, "Press Button");
  TV.print(30, 45, "To Start");


  delay(1000);
  while (!button1Status) {

    processInputs();
    TV.delay_frame(3);
    if (x + volX < 1 || x + volX > TV.hres() - 1) volX = -volX;
    if (y + volY < 1 || y + volY > TV.vres() - 1) volY = -volY;
    if (TV.get_pixel(x + volX, y + volY)) {
      TV.set_pixel(x + volX, y + volY, 0);

      if (TV.get_pixel(x + volX, y - volY) == 0) {
        volY = -volY;
      }
      else if (TV.get_pixel(x - volX, y + volY) == 0) {
        volX = -volX;
      }
      else {
        volX = -volX;
        volY = -volY;
      }
    }
    TV.set_pixel(x, y, 0);
    x += volX;
    y += volY;
    TV.set_pixel(x, y, 1);
  }



  TV.select_font(font4x6);
  state = IN_GAMEA;
}




void setup() {

  digitalWrite(Reset, HIGH);
  delay(200);
  pinMode(Reset, OUTPUT);
  Serial.begin(9600);
  delay(200);

  pinMode(SW_pin, INPUT);      //setup SW input
  digitalWrite(SW_pin, HIGH);  //reading button state:1=not pressed,0=pressed
  Serial.begin(9600);          //Seput serical connection for print out to console

  //Serial.begin(9600);
  x = 0;
  y = 0;
  TV.begin(_NTSC);       //for devices with only 1k sram(m168) use TV.begin(_NTSC,128,56)

  ballX = TV.hres() / 2;
  ballY = TV.vres() / 2;

  //  pinMode(BUTTON_ONE_PIN, INPUT);      // sets the digital pin as output
}

void loop() {
  processInputs();




  if (state == IN_MENU) {
    drawMenu();
  }
  if (state == IN_GAMEA) {

    drawBox();
  }

  if (state == IN_GAMEB) {
    if (frame % 3 == 0) { //every third frame
      ballX += ballVolX;
      ballY += ballVolY;


      // change if hit top or bottom
      if (ballY <= 1 || ballY >= TV.vres() - 1)
      { ballVolY = -ballVolY;
        delay(100);
        TV.tone( 2000, 30  );
      }

      // test left side for wall hit
      if (ballVolX < 0 && ballX == LEFT_PADDLE_X + PADDLE_WIDTH - 1 && ballY >= leftPaddleY && ballY <= leftPaddleY + PADDLE_HEIGHT) {
        ballVolX = -ballVolX;
        ballVolY += 2 * ((ballY - leftPaddleY) - (PADDLE_HEIGHT / 2)) / (PADDLE_HEIGHT / 2);


        delay(100);
        TV.tone(2000, 30 );
      }

      // test right side for wall hit
      if (ballVolX > 0 && ballX == RIGHT_PADDLE_X && ballY >= rightPaddleY && ballY <= rightPaddleY + PADDLE_HEIGHT) {
        ballVolX = -ballVolX;
        ballVolY += 2 * ((ballY - rightPaddleY) - (PADDLE_HEIGHT / 2)) / (PADDLE_HEIGHT / 2);
        delay(100);
        TV.tone( 2000, 30  );
      }

      //limit vertical speed
      if (ballVolY > MAX_Y_VELOCITY) ballVolY = MAX_Y_VELOCITY;
      if (ballVolY < -MAX_Y_VELOCITY) ballVolY = -MAX_Y_VELOCITY;




      // Scoring
      if (ballX <= 1) {
        playerScored(RIGHT);
        // sound
        delay(100);
        TV.tone( 500, 300 );
      }
      if (ballX >= TV.hres() - 1) {
        playerScored(LEFT);
        // sound
        delay(100);
        TV.tone(  500, 300 );
      }
    }



    drawGameScreen();
  }

  if (state == GAME_OVER) {
    drawGameScreen();
    TV.select_font(font8x8);
    TV.print(29, 25, "GAME");
    TV.print(68, 25, "OVER");
    TV.print(24, 45, "THE CODE IS");
    TV.print(48, 55, "5263");
    delay(5000);
    digitalWrite(Reset, LOW);

  }
  if (state == START_OVER) {
    drawGameScreen();
    TV.select_font(font8x8);
    TV.print(29, 25, "TRY AGAIN");
    delay(1000);
    digitalWrite(Reset, LOW);

  }


  TV.delay_frame(1);
  if (++frame == 60) frame = 0; //increment and/or reset frame counter
}
