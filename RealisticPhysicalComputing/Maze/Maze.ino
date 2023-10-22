#include <LedControl.h>

LedControl lc = LedControl(5, 7, 6 ,0);

int roomA[8][8] = {
  {1, 1, 1, 1, 1, 1, 1, 1},
  {1, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 1},
  {6, 0, 0, 0, 0, 0, 0, 1},
  {6, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 1},
  {1, 1, 1, 3, 3, 1, 1, 1},
};

int roomB[8][8] = {
  {1, 1, 1, 2, 2, 1, 1, 1},
  {1, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 1},
  {7, 0, 0, 0, 0, 0, 0, 1},
  {7, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 1},
  {1, 1, 1, 1, 1, 4, 4, 1},
};

int roomC[8][8] = {
  {1, 1, 1, 1, 1, 3, 3, 1},
  {1, 0, 0, 0, 1, 0, 0, 1},
  {1, 0, 0, 0, 1, 0, 0, 1},
  {8, 0, 0, 0, 1, 0, 0, 1},
  {8, 0, 0, 0, 1, 0, 0, 1},
  {1, 0, 0, 0, 1, 0, 0, 1},
  {1, 0, 0, 0, 1, 0, 0, 1},
  {1, 5, 5, 1, 1, 5, 5, 1},
};

int roomD[8][8] = {
  {1, 1, 4, 4, 1, 4, 4, 1},
  {9, 0, 0, 0, 1, 0, 0, 1},
  {9, 0, 0, 0, 1, 0, 0, 1},
  {1, 1, 1, 1, 1, 0, 0, 1},
  {9, 0, 0, 0, 0, 0, 0, 1},
  {9, 0, 0, 0, 0, 0, 0, 1},
  {9, 0, 0, 0, 0, 0, 0, 1},
  {1, 1, 1, 1, 1, 1, 1, 1},
};

int roomE[8][8] = {
  {1, 1, 1, 1, 1, 1, 1, 1},
  {1, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 1},
  {10, 0, 0, 0, 0, 0, 0, 2},
  {10, 0, 0, 0, 0, 0, 0, 2},
  {1, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 1},
  {1, 1, 1, 1, 1, 7, 7, 1},
};

int roomF[8][8] = {
  {1, 1, 1, 1, 1, 6, 6, 1},
  {1, 0, 0, 1, 0, 0, 0, 1},
  {1, 0, 0, 1, 0, 0, 0, 1},
  {11, 0, 0, 1, 0, 0, 0, 3},
  {11, 0, 0, 1, 0, 0, 0, 3},
  {1, 0, 0, 1, 0, 0, 0, 1},
  {1, 0, 0, 1, 0, 0, 0, 1},
  {1, 8, 8, 1, 1, 1, 1, 1},
};

int roomG[8][8] = {
  {1, 7, 7, 1, 1, 1, 1, 1},
  {1, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 4},
  {1, 0, 0, 0, 0, 0, 0, 4},
  {1, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 1},
  {1, 1, 1, 9, 9, 1, 1, 1},
};

int roomH[8][8] = {
  {1, 1, 1, 8, 8, 1, 1, 1},
  {13, 0, 0, 0, 0, 0, 0, 5},
  {13, 0, 0, 0, 0, 0, 0, 5},
  {1, 1, 1, 1, 1, 1, 1, 1},
  {13, 0, 0, 0, 0, 0, 0, 5},
  {13, 0, 0, 0, 0, 0, 0, 5},
  {13, 0, 0, 0, 0, 0, 0, 5},
  {1, 1, 1, 1, 1, 1, 1, 1},
};

int roomI[8][8] = {
  {1, 1, 1, 1, 1, 1, 1, 1},
  {1, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 6},
  {1, 0, 0, 0, 0, 0, 0, 6},
  {1, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 1},
  {1, 11, 11, 1, 1, 1, 1, 1},
};

int roomJ[8][8] = {
  {1, 10, 10, 1, 1, 1, 1, 1},
  {1, 0, 0, 0, 1, 0, 0, 1},
  {1, 0, 0, 0, 1, 0, 0, 1},
  {1, 0, 0, 0, 1, 0, 0, 7},
  {1, 1, 1, 1, 1, 0, 0, 7},
  {1, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 1},
  {1, 1, 1, 12, 12, 1, 1, 1},
};

// int roomK[8][8] = {
//   {1, 1, 1, 11, 11, 1, 1, 1},
//   {1, 0, 0, 0, 0, 0, 0, 1},
//   {1, 0, 0, 0, 0, 0, 0, 1},
//   {1, 0, 0, 14, 14, 0, 0, 1},
//   {1, 0, 0, 14, 14, 0, 0, 1},
//   {1, 0, 0, 0, 0, 0, 0, 1},
//   {1, 0, 0, 0, 0, 0, 0, 1},
//   {1, 1, 1, 1, 1, 1, 1, 1},
// };

int roomK[8][8] = {
  {0, 0, 1, 1, 1, 1, 0, 0},
  {0, 1, 0, 0, 0, 0, 1, 0},
  {1, 0, 0, 1, 0, 1, 0, 1},
  {1, 0, 1, 0, 0, 0, 0, 1},
  {1, 0, 1, 0, 0, 0, 0, 1},
  {1, 0, 0, 1, 0, 1, 0, 1},
  {0, 1, 0, 0, 0, 0, 1, 0},
  {0, 0, 1, 1, 1, 1, 0, 0},
};

int roomL[8][8] = {
  {1, 1, 1, 1, 1, 1, 1, 1},
  {1, 0, 0, 0, 0, 0, 0, 9},
  {1, 0, 0, 0, 0, 0, 0, 9},
  {1, 1, 0, 0, 1, 1, 1, 1},
  {1, 0, 0, 0, 0, 0, 0, 9},
  {1, 0, 0, 0, 0, 0, 0, 9},
  {1, 0, 0, 0, 0, 0, 0, 9},
  {1, 1, 1, 1, 1, 1, 1, 1},
};

int currentRoom[8][8];

int currentColumn = 3;
int currentLine = 3;

#define pinX A2
#define pinY A4
int X = 0;
int Y = 0;

bool win = false;

void setup() {
  Serial.begin(9600);

  pinMode(pinX, INPUT);
  pinMode(pinY, INPUT);

  lc.shutdown(0,false);
  lc.setIntensity(0,15);
  lc.clearDisplay(0);

  setCurrentRoom(roomA);
}

void setCurrentRoom(int room[8][8]) {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      currentRoom[i][j] = room[i][j];
    }
  }
}

void loop() {
  X = analogRead(pinX);
  Y = analogRead(pinY);

  X = map(X, 0, 1023, 0, 360);
  Y = map(Y, 0, 1023, 0, 360);

  if (!win) {
    movePlayer();
  }

  printByte();
  delay(100);
}

void movePlayer() {
  // Serial.print(currentColumn);
  // Serial.print(" / ");
  // Serial.println(currentLine);

  currentRoom[currentColumn][currentLine] = 0;

  if (X < 160 && checkWall(-1, 0)) {
    if (checkTp(-1, 0)) {
      currentColumn = 6;
    } else {
      currentColumn--;
    }
  } else if (X > 200 && checkWall(1, 0)) {
    if (checkTp(1, 0)) {
      currentColumn = 1;
    } else {
      currentColumn++;
    }
  } else if (Y < 160 && checkWall(0, -1)) {
    if (checkTp(0, -1)) {
      currentLine = 6;
    } else {
      currentLine--;
    }
  } else if (Y > 200 && checkWall(0, 1)) {
    if (checkTp(0, 1)) {
      currentLine = 1;
    } else {
      currentLine++;
    }
  }
  if (!win) {
    currentRoom[currentColumn][currentLine] = 1;
  }
}

bool checkWall(int XMove, int YMove) {
  // Serial.print("Checking pos in ");
  // Serial.print(XMove);
  // Serial.print(" / ");
  // Serial.print(YMove);
  // Serial.print(" -> ");
  // Serial.println(currentRoom[currentColumn + XMove][currentLine + YMove]);
  if (currentRoom[currentColumn + XMove][currentLine + YMove] != 1) {
    return true;
  }
  return false;
}

bool checkTp(int XMove, int YMove) {
  // Serial.print("Checking char in ");
  // Serial.print(XMove);
  // Serial.print(" / ");
  // Serial.print(YMove);
  // Serial.print(" -> ");
  // Serial.println(currentRoom[currentColumn + XMove][currentLine + YMove]);
  switch (currentRoom[currentColumn + XMove][currentLine + YMove]) {
    case 2:
      setCurrentRoom(roomA);
      return true;
      break;
    case 3:
      setCurrentRoom(roomB);
      return true;
      break;
    case 4:
      setCurrentRoom(roomC);
      return true;
      break;
    case 5:
      setCurrentRoom(roomD);
      return true;
      break;
    case 6:
      setCurrentRoom(roomE);
      return true;
      break;
    case 7:
      setCurrentRoom(roomF);
      return true;
      break;
    case 8:
      setCurrentRoom(roomG);
      return true;
      break;
    case 9:
      setCurrentRoom(roomH);
      return true;
      break;
    case 10:
      setCurrentRoom(roomI);
      return true;
      break;
    case 11:
      setCurrentRoom(roomJ);
      return true;
      break;
    case 12:
      setCurrentRoom(roomK);
      win = true;
      return true;
      break;
    case 13:
      setCurrentRoom(roomL);
      return true;
      break;
    default:
      return false;
  }
}

void printByte() {
  for(int i = 0; i < 8; i++) {
    for(int j = 0; j < 8; j++) {
      if (currentRoom[i][j] < 2) {
        lc.setLed(0, i, j, currentRoom[i][j]);
      } else if (currentRoom[i][j] == 14) {
        lc.setLed(0, i, j, 0);

      } else {
        lc.setLed(0, i, j, 0);
      }
    }
  }
}