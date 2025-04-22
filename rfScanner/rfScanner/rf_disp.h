/* rf_disp.h

*/
#ifndef RF_DISP_H
#define RF_DISP_H

// comment out if not running on arduino
 //#define ARDUINO

#ifndef ARDUINO
  #include <avr/io.h>
  #include <xc.h>
#endif
#include "rf_I2C.h"

#define SLAVE_ADDR 0x78

typedef struct {
    unsigned char part1[20];
    unsigned char part2[20];
} SplitResult;

typedef struct {
	unsigned char row1[20];
	unsigned char row2[20];
	unsigned char buffer[6];
	unsigned char part1[10];
	unsigned char part2[10];
    void (*set)(uint8_t row, unsigned char* text);
    void (*init)(void);
    void (*intToChar)(int num, unsigned char* buffer, int buffer_size);
    void (*floatToChar)(float num, unsigned char* buffer, int buffer_size, int precision);
    unsigned char* (*combine) (unsigned char* x, unsigned char* y, unsigned char* combined);
    SplitResult (*split) (unsigned char* s, int number);
    void (*setRowPlace) (uint8_t row, uint8_t step);
    void (*clearBuffer)(uint8_t size, unsigned char* buffer);
    void (*clear)(void);
 } scr;
 



void initDisp();
void setText(uint8_t row, unsigned char*);
void setbacklight(volatile uint8_t backlight);
void floatToChar(float num, unsigned char* buffer, int buffer_size, int precision);
void intToChar(int num, unsigned char* buffer, int buffer_size);
void setRowStep(uint8_t row, uint8_t step);
void clearBuffer(uint8_t size, unsigned char*);
unsigned char* combine(unsigned char*, unsigned char*, unsigned char*);
int strlenCustom(unsigned char*);
SplitResult split(unsigned char* s, int number);


scr screen = {
    "",
    "",
    "",
    "",
    "",
    setText,
    initDisp,
    intToChar,
    floatToChar,
    combine,
    split,
    setRowPlace,
    clearBuffer,
    clearScreen
};

void initDisp() {
  uint16_t response;
	initI2C();
  start_transmission();
  response = write_command(SLAVE_ADDR);
  if(response == 0x28);
  response = write_command(0x38);
  #ifndef ARDUINO
    delay_ms(10);
  #endif
  #ifdef ARDUINO
    delay(10);
  #endif
  response=write_command(0x39);
  #ifndef ARDUINO
    delay_ms(10);
  #endif
  #ifdef ARDUINO
    delay(10);
  #endif
  char data[7] = {0x14,0x78,0x5E, 0x6D, 0x0C, 0x01, 0x06};
  for(uint8_t n = 0; n<7;n++) {
    response = write_command(data[n]);
  }
  #ifndef ARDUINO
    delay_ms(10);
  #endif
  #ifdef ARDUINO
    delay(10);
  #endif
	stop_transmission();
}

void setText(uint8_t row, unsigned char *chars) {
  //uint16_t response;
  //response = write_command(0);
  //setRow(row);
  for(int i = 0; i< 19; i++) {
    screen.row1[i] = (chars[i] != '\0') ? chars[i]:' ';
  }
  screen.row1[19] = '\0';
  write_data(chars, 19, row);
	
}

void setbacklight(volatile uint8_t backlight) {
	
}

void intToChar(int num, unsigned char* buffer, int buffer_size) {
  // Handle negative numbers
  int is_negative = 0;
  if (num < 0) {
      is_negative = 1;
      num = -num;
  }
  
  // Find the end position for the string
  int i = 0;
  int temp = num;
  
  // Count digits
  do {
      i++;
      temp /= 10;
  } while (temp > 0);
  
  // Check if we need space for negative sign
  if (is_negative) {
      i++;
  }
  
  // Make sure the buffer is large enough
  if (i >= buffer_size) {
      // Not enough space, fill with error indicator
      for (int j = 0; j < buffer_size - 1; j++) {
          buffer[j] = 'E';
      }
      buffer[buffer_size - 1] = '\0';
      return;
  }
  
  // Null-terminate the buffer
  buffer[i] = '\0';
  
  // Fill the buffer from right to left
  int idx = i - 1;
  
  // Handle the case when num is 0
  if (num == 0) {
      buffer[0] = '0';
      buffer[1] = '\0';
      return;
  }
  
  // Convert each digit
  while (num > 0) {
      buffer[idx] = '0' + (num % 10);
      num /= 10;
      idx--;
  }
  
  // Add negative sign if needed
  if (is_negative) {
      buffer[0] = '-';
  }
}
void floatToChar(float num, unsigned char* buffer, int buffer_size, int precision) {
  // Handle negative numbers
  int is_negative = 0;
  if (num < 0) {
      is_negative = 1;
      num = -num;
  }
  
  // Extract integer part
  int int_part = (int)num;
  
  // Extract decimal part and convert to integer
  float decimal_part = num - int_part;
  int decimal_int = 0;
  int multiplier = 1;
  
  // Calculate multiplier based on precision
  for (int i = 0; i < precision; i++) {
      multiplier *= 10;
  }
  
  decimal_int = (int)(decimal_part * multiplier + 0.5); // Add 0.5 for rounding
  
  // Handle cases where rounding makes decimal part roll over
  if (decimal_int >= multiplier) {
      int_part += 1;
      decimal_int = 0;
  }
  
  // Calculate required space
  int int_digits = 0;
  int temp = int_part;
  
  // Count integer digits
  do {
      int_digits++;
      temp /= 10;
  } while (temp > 0);
  
  // Calculate total space needed
  int total_size = int_digits + (precision > 0 ? precision + 1 : 0) + (is_negative ? 1 : 0) + 1; // +1 for decimal point, +1 for null terminator
  
  // Check if buffer is large enough
  if (total_size > buffer_size) {
      // Not enough space, fill with error indicator
      for (int j = 0; j < buffer_size - 1; j++) {
          buffer[j] = 'E';
      }
      buffer[buffer_size - 1] = '\0';
      return;
  }
  
  // Start filling the buffer from the end
  int idx = total_size - 1;
  buffer[idx--] = '\0';
  
  // Handle the case when both integer and decimal parts are 0
  if (int_part == 0 && decimal_int == 0) {
      if (precision > 0) {
          // Fill decimal places with zeros
          for (int i = 0; i < precision; i++) {
              buffer[idx--] = '0';
          }
          buffer[idx--] = '.';
      }
      buffer[idx] = '0';
      
      // Add negative sign if needed
      if (is_negative) {
          for (int i = idx; i >= 1; i--) {
              buffer[i] = buffer[i-1];
          }
          buffer[0] = '-';
      }
      return;
  }
  
  // Fill decimal part
  if (precision > 0) {
      for (int i = 0; i < precision; i++) {
          buffer[idx--] = '0' + (decimal_int % 10);
          decimal_int /= 10;
      }
      buffer[idx--] = '.';
  }
  
  // Fill integer part (at least one digit, even if int_part is 0)
  if (int_part == 0) {
      buffer[idx--] = '0';
  } else {
      while (int_part > 0) {
          buffer[idx--] = '0' + (int_part % 10);
          int_part /= 10;
      }
  }
  
  // Add negative sign if needed
  if (is_negative) {
      buffer[idx] = '-';
  }
  
  // Move everything to the beginning of the buffer if necessary
  if (idx > 0) {
      for (int i = 0; i <= total_size - idx - 2; i++) {
          buffer[i] = buffer[idx + i];
      }
  }
}
void clearBuffer(uint8_t size, unsigned char* buffer) {
    for (uint8_t i=0;i<size;i++)  {   // clearing buffer. Might need to move to rf_disp.h to make a function for this.
    buffer[i] = ' ';
  }
}


unsigned char* combine(unsigned char* x, unsigned char* y, unsigned char* combined)
{
    int length_x = strlenCustom(x);
    int length_y = strlenCustom(y);

    int total = length_x+length_y ;

    if (total >= 20) {
        total=20;
    }

    int i = 0 ;


    while (i < length_x&&i<total) {
        combined[i] = x[i];
        i++;
    }
    int j = 0;

    while (j < length_y&&i<total) {
        combined[i] = y[j];
        i++;
        j++;
    }

    combined[i] = '\0';

    return combined;
}

int strlenCustom(unsigned char* z) {
    int length = 0;
    while (z[length] != '\0') {
        length++;
    }
    return length;
}

SplitResult split(unsigned char* s, int number) {
    SplitResult result;


    int i = 0;
    int length = 0;


    while (s[length] != '\0') {
        length++;
    }

    if (number > length) {
        number = length;
    }


    while (i < number) {
        result.part1[i] = s[i];
        i++;
    }
    result.part1[i] = '\0';


    int j = 0;
    while (i < length) {
        result.part2[j] = s[i];
        i++;
        j++;
    }
    result.part2[j] = '\0';

    return result;
}




#endif