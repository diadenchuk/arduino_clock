#include <Arduino.h>

const int A_PIN = 2;
const int B_PIN = 3;
const int C_PIN = 4;
const int D_PIN = 5;
const int E_PIN = 6;
const int F_PIN = 7;
const int G_PIN = 8;
const int D1_PIN = 9;
const int D2_PIN = 10;
const int D3_PIN = 11;
const int D4_PIN = 12;
const int DP_PIN = 13;

void setup()
{
  pinMode(A3, INPUT); // button
  pinMode(A_PIN, OUTPUT);
  pinMode(B_PIN, OUTPUT);
  pinMode(C_PIN, OUTPUT);
  pinMode(D_PIN, OUTPUT);
  pinMode(E_PIN, OUTPUT);
  pinMode(F_PIN, OUTPUT);
  pinMode(G_PIN, OUTPUT);

  pinMode(D1_PIN, OUTPUT);
  pinMode(D2_PIN, OUTPUT);
  pinMode(D3_PIN, OUTPUT);
  pinMode(D4_PIN, OUTPUT);
  pinMode(DP_PIN, OUTPUT);
  // Serial.begin(9600); // Initialize serial communication
}
int interval = 1;
unsigned long startTime = 0; // Variable to hold the start time
bool increase = true;
int holdButtonSec = 0;
class Clock
{
public:
  int hour;
  int minute;
  int seconds;
  int miliseconds;

  // Constructor
  Clock(int f1, int f2, int f3, int f4) : hour(f1), minute(f2), seconds(f3), miliseconds(f4){};

  bool Second()
  {
    // Calculate the elapsed time
    unsigned long elapsedTime = millis();
    if ((elapsedTime - startTime) >= 998)
    {

      startTime = elapsedTime;
      seconds++;
      // Serial.print("digitalRead(0):");
      // Serial.println();
    }
    if (digitalRead(A3) == 1)
    {
      if (elapsedTime - holdButtonSec >= 1000)
      {
        minute++;
      }
    }
    if (digitalRead(A3) == 1 && increase)
    {
      minute++;
      increase = false;
    }
    if (digitalRead(A3) == 0)
    {
      increase = true;
      holdButtonSec = elapsedTime;
    }
    if (seconds >= 60)
    {
      seconds = 0;
      minute++;
    }

    if (minute >= 60)
    {
      minute = 0;
      hour++;
    }

    if (hour >= 13)
    {
      hour = 1;
    }

    return seconds % 2 != 0;
  }
};

class Segment
{
public:
  int pin;
  int output;

  // Constructor
  Segment(int f1, int f2) : pin(f1), output(f2){};
};

class Digit
{
public:
  int pin;
  int output;

  // Constructor
  Digit(int f1, int f2) : pin(f1), output(f2){};
};
const int SEGMENT_ARRAY_SIZE = 7;
Segment ZERO[SEGMENT_ARRAY_SIZE]{
    {A_PIN, 1},
    {B_PIN, 1},
    {C_PIN, 1},
    {D_PIN, 1},
    {E_PIN, 1},
    {F_PIN, 1},
    {G_PIN, 0}};
const Segment ONE[SEGMENT_ARRAY_SIZE]{
    {A_PIN, 0},
    {B_PIN, 1},
    {C_PIN, 1},
    {D_PIN, 0},
    {E_PIN, 0},
    {F_PIN, 0},
    {G_PIN, 0}};
const Segment TWO[SEGMENT_ARRAY_SIZE]{
    {A_PIN, 1},
    {B_PIN, 1},
    {C_PIN, 0},
    {D_PIN, 1},
    {E_PIN, 1},
    {F_PIN, 0},
    {G_PIN, 1}};
const Segment THREE[SEGMENT_ARRAY_SIZE]{
    {A_PIN, 1},
    {B_PIN, 1},
    {C_PIN, 1},
    {D_PIN, 1},
    {E_PIN, 0},
    {F_PIN, 0},
    {G_PIN, 1}};
const Segment FOUR[SEGMENT_ARRAY_SIZE]{
    {A_PIN, 0},
    {B_PIN, 1},
    {C_PIN, 1},
    {D_PIN, 0},
    {E_PIN, 0},
    {F_PIN, 1},
    {G_PIN, 1}};
const Segment FIVE[SEGMENT_ARRAY_SIZE]{
    {A_PIN, 1},
    {B_PIN, 0},
    {C_PIN, 1},
    {D_PIN, 1},
    {E_PIN, 0},
    {F_PIN, 1},
    {G_PIN, 1}};
const Segment SIX[SEGMENT_ARRAY_SIZE]{
    {A_PIN, 1},
    {B_PIN, 0},
    {C_PIN, 1},
    {D_PIN, 1},
    {E_PIN, 1},
    {F_PIN, 1},
    {G_PIN, 1}};
const Segment SEVEN[SEGMENT_ARRAY_SIZE]{
    {A_PIN, 1},
    {B_PIN, 1},
    {C_PIN, 1},
    {D_PIN, 0},
    {E_PIN, 0},
    {F_PIN, 0},
    {G_PIN, 0}};
const Segment EIGHT[SEGMENT_ARRAY_SIZE]{
    {A_PIN, 1},
    {B_PIN, 1},
    {C_PIN, 1},
    {D_PIN, 1},
    {E_PIN, 1},
    {F_PIN, 1},
    {G_PIN, 1}};
const Segment NINE[SEGMENT_ARRAY_SIZE]{
    {A_PIN, 1},
    {B_PIN, 1},
    {C_PIN, 1},
    {D_PIN, 1},
    {E_PIN, 0},
    {F_PIN, 1},
    {G_PIN, 1}};

const int DIGIT_ARRAY_SIZE = 4;

const Digit FIRST_N[DIGIT_ARRAY_SIZE]{
    {D1_PIN, 0},
    {D2_PIN, 1},
    {D3_PIN, 1},
    {D4_PIN, 1}};

const Digit SECOND_N[DIGIT_ARRAY_SIZE]{
    {D1_PIN, 1},
    {D2_PIN, 0},
    {D3_PIN, 1},
    {D4_PIN, 1}};

const Digit THIRD_N[DIGIT_ARRAY_SIZE]{
    {D1_PIN, 1},
    {D2_PIN, 1},
    {D3_PIN, 0},
    {D4_PIN, 1}};

const Digit FOURTH_N[DIGIT_ARRAY_SIZE] = {
    {D1_PIN, 1},
    {D2_PIN, 1},
    {D3_PIN, 1},
    {D4_PIN, 0}};

void draw(const Digit digitN[], const Segment segmentN[])
{
  for (size_t i = 0; i < DIGIT_ARRAY_SIZE; i++)
  {
    digitalWrite(digitN[i].pin, digitN[i].output);
  }
  for (size_t i = 0; i < SEGMENT_ARRAY_SIZE; i++)
  {
    digitalWrite(segmentN[i].pin, segmentN[i].output);
  }
}

void drawDot(int output)
{
  digitalWrite(DP_PIN, output);
}

const Segment SEGMENTS_ARRAY[][7] = {
    {ZERO[0], ZERO[1], ZERO[2], ZERO[3], ZERO[4], ZERO[5], ZERO[6]},
    {ONE[0], ONE[1], ONE[2], ONE[3], ONE[4], ONE[5], ONE[6]},
    {TWO[0], TWO[1], TWO[2], TWO[3], TWO[4], TWO[5], TWO[6]},
    {THREE[0], THREE[1], THREE[2], THREE[3], THREE[4], THREE[5], THREE[6]},
    {FOUR[0], FOUR[1], FOUR[2], FOUR[3], FOUR[4], FOUR[5], FOUR[6]},
    {FIVE[0], FIVE[1], FIVE[2], FIVE[3], FIVE[4], FIVE[5], FIVE[6]},
    {SIX[0], SIX[1], SIX[2], SIX[3], SIX[4], SIX[5], SIX[6]},
    {SEVEN[0], SEVEN[1], SEVEN[2], SEVEN[3], SEVEN[4], SEVEN[5], SEVEN[6]},
    {EIGHT[0], EIGHT[1], EIGHT[2], EIGHT[3], EIGHT[4], EIGHT[5], EIGHT[6]},
    {NINE[0], NINE[1], NINE[2], NINE[3], NINE[4], NINE[5], NINE[6]},
};
Clock clock = {1, 59, 0, 0};
void loop()
{
  bool toDrawDot = clock.Second();
  int firstH = 0;
  int secondH = clock.hour;
  if (clock.hour > 9)
  {
    firstH = clock.hour / 10;
    secondH = clock.hour % 10;
  }

  int firstM = 0;
  int secondM = clock.minute;

  if (clock.minute > 9)
  {
    firstM = clock.minute / 10;
    secondM = clock.minute % 10;
  }

  draw(FIRST_N, SEGMENTS_ARRAY[firstH]);
  drawDot(0);
  delay(interval);

  draw(SECOND_N, SEGMENTS_ARRAY[secondH]);
  if (toDrawDot)
  {
    drawDot(1);
  }
  else
  {
    drawDot(0);
  }
  delay(interval);
  drawDot(0);
  draw(THIRD_N, SEGMENTS_ARRAY[firstM]);

  delay(interval);
  draw(FOURTH_N, SEGMENTS_ARRAY[secondM]);
  drawDot(0);
  delay(interval);
}
