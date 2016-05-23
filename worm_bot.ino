#include <SoftwareSerial.h>
#include <Servo.h>

Servo servo1;
Servo servo2;

// Setup our program variables.
char *tmp;

const int input_size = 10;
char input_byte;
char input_buffer[input_size];
int input_len = 0;
int input_index = 0;

// Get substring of a string using index.
char *substr(char *str, int start_index, int end_index) {
  // Setup variables.
  int len = (end_index - start_index);
  char *sub = (char *)malloc(sizeof(char) * len);

  // Copy over chars to sub char array offset by start_index.
  for(int i = 0; i < len; i += 1) {
    sub[i] = str[start_index + i];
  }

  // Add the null byte to the end of our new char array.
  sub[len] = 0;

  return sub; 
}

// Return the index of a character;
int char_index(char *str, char target) {
  // Setup Variables.
  int i = 0;
  int len = strlen(str);
  int index = -1;

  // Loop through our string until we hit our target char.
  for (i; i < len; i++) {
    if (str[i] == target) {
      index = i;
      break;
    }
  }

  return index;
}

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(57600);
  while (!Serial) { }

  Serial.println("Connected to Serial!");

  servo1.attach(9);
  servo2.attach(8);
}

void loop() {
  if (Serial.available() > 0) {
    int input_byte_len = Serial.available();
    
    Serial.readBytes(&input_byte, input_byte_len);
    input_buffer[input_index] = input_byte;
  
    if (input_byte == '\n') {
      // Set the null byte at the end of the input buffer and get it's length.
      input_buffer[input_index] = 0;
      input_len = strlen(input_buffer);

      // Get delim index and then get each value from the input buffer.
      int delim_index = char_index(input_buffer, ',');
      char *str1 = substr(input_buffer, 0, delim_index);
      char *str2 = substr(input_buffer, delim_index + 1, input_len);

      // Convert these values into an integer.
      int pos1 = (int)strtol(str1, &tmp, 10);
      int pos2 = (int)strtol(str2, &tmp, 10);

      // Print out the locations we are moving the servos to.
      Serial.println("Moving servos: ");
      Serial.print("Servo 1: ");
      Serial.println(pos1);
      Serial.print("Servo 2: ");
      Serial.println(pos2);
      Serial.print("\n");

      // Actually move the servos.
      servo1.write(pos1);
      servo2.write(pos2);

      // Reset the input index.
      input_index = 0;
    } else {
      // Increase the input index to target the next byte in the input buffer.
      input_index = input_index + 1;
      
    }
  }
}

