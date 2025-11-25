// Adapted from Google Gemini. Date: 20/11/25
// google search: arduino uno joystick
const int joyX = A0;
const int joyY = A1;
const int joyButton = 2;
bool sprinting = false;
bool jumping = false;
bool moving = false;

void setup() {
  Serial.begin(9600);
  pinMode(joyButton, INPUT_PULLUP);
}

void loop() {
  int xValue = analogRead(joyX);
  int yValue = analogRead(joyY);
  int buttonState = digitalRead(joyButton);
  char movementOut = '\0';
  char jumpOut = '\0';
  char sprintOut = '\0';
  int deadzone = 50;
  int center = 512;
  // Moving horizontally
  if (xValue > center + deadzone) {
    movementOut = 'd';
    moving = true;
  } else if (xValue < center - deadzone) {
    movementOut = 'a';
    moving = true;
  } else if (moving) {
    movementOut = 'c';
    moving = false;
  }
  // Jumping
  if (!jumping && yValue < 200) {
    jumpOut = 'w';
    jumping = true;
  } else if (jumping && yValue > 300) {
    jumpOut = 'e';
    jumping = false;
  }
  // Sprinting
  if (!sprinting && buttonState == LOW) {
    sprintOut = 'z';
    sprinting = true;
  } else if (sprinting && buttonState == LOW) {
    sprintOut = 'x';
    sprinting = false;
  }
  // Set output
  char output = '\0';
  if (jumpOut != '\0') {
    output = jumpOut;
  } else if (sprintOut != '\0') {
    output = sprintOut;
  } else if (movementOut != '\0') {
    output = movementOut;
  }
  // Move downwards
  if (yValue > center + deadzone) {
    output = 's';
  }
  // Write output
  if (output != '\0') {
    Serial.write(output);
  }
  delay(100);
}
