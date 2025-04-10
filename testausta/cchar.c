/**
 * Test program for int and float to char conversion functions
 * This demonstrates how the functions work with various input values
 */

#include <stdio.h>  // Only included for test output visualization

// Function to convert integer to string
void int_to_char(int num, unsigned char* buffer, int buffer_size) {
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

// Function to convert float to string with specified precision
void float_to_char(float num, unsigned char* buffer, int buffer_size, int precision) {
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

// Function to simulate sending a string to the LCD
void send_to_lcd(const char* str) {
    printf("LCD Display: [%s]\n", str);
}

int main() {
    unsigned char buffer[20]; // Buffer for converted strings
    
    // Test integer conversion with various values
    printf("\n--- Integer Conversion Tests ---\n");
    
    int test_integers[] = {0, 123, -456, 9999, -10000, 2147483647, -2147483648};
    int num_int_tests = sizeof(test_integers) / sizeof(test_integers[0]);
    
    for (int i = 0; i < num_int_tests; i++) {
        int_to_char(test_integers[i], buffer, sizeof(buffer));
        printf("Int %d -> ", test_integers[i]);
        send_to_lcd((char*)buffer);
    }
    
    // Test integer buffer overflow
    printf("\n--- Integer Buffer Overflow Test ---\n");
    int_to_char(123456, buffer, 5); // Buffer too small
    printf("Int 123456 with small buffer -> ");
    send_to_lcd((char*)buffer);
    
    // Test float conversion with various values and precisions
    printf("\n--- Float Conversion Tests ---\n");
    
    float test_floats[] = {0.0, 123.456, -78.9, 0.001, -0.001, 99.999, -99.999};
    int num_float_tests = sizeof(test_floats) / sizeof(test_floats[0]);
    
    for (int i = 0; i < num_float_tests; i++) {
        // Test with different precisions
        for (int precision = 0; precision <= 3; precision++) {
            float_to_char(test_floats[i], buffer, sizeof(buffer), precision);
            printf("Float %.3f with precision %d -> ", test_floats[i], precision);
            send_to_lcd((char*)buffer);
        }
        printf("\n");
    }
    
    // Test rounding behavior
    printf("\n--- Rounding Tests ---\n");
    float rounding_tests[] = {9.999, 0.995, 1.999, 99.990005};
    for (int i = 0; i < 4; i++) {
        float_to_char(rounding_tests[i], buffer, sizeof(buffer), 8);
        printf("Float %.3f rounded to 2 decimals -> ", rounding_tests[i]);
        send_to_lcd((char*)buffer);
    }
    
    // Test float buffer overflow
    printf("\n--- Float Buffer Overflow Test ---\n");
    float_to_char(1234.5678, buffer,sizeof(buffer), 8); // Buffer too small
    printf("Float 1234.5678 with small buffer -> ");
    send_to_lcd((char*)buffer);
    
    // Edge cases
    printf("\n--- Edge Cases ---\n");
    
    // Zero cases
    int_to_char(0, buffer, sizeof(buffer));
    printf("Int 0 -> ");
    send_to_lcd((char*)buffer);
    
    float_to_char(0.000001, buffer, sizeof(buffer), 10);
    printf("Float 0.0 -> ");
    send_to_lcd((char*)buffer);
    
    float_to_char(-0.0, buffer, sizeof(buffer), 2);
    printf("Float -0.0 -> ");
    send_to_lcd((char*)buffer);
    
    // Decimal-only cases
    float_to_char(0.123, buffer, sizeof(buffer), 3);
    printf("Float 0.123 -> ");
    send_to_lcd((char*)buffer);
    
    float_to_char(-0.123, buffer, sizeof(buffer), 3);
    printf("Float -0.123 -> ");
    send_to_lcd((char*)buffer);
    
    return 0;
}
