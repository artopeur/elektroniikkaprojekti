#include<stdio.h>
#include<math.h>
#include<arduino.h>
int main() {
    int value = 0;
    int drate = 20;
    int prev = 0;
    int mtime = 200;
    while(true) {    
        prev = value;
        value = read(adc);
        printf("%d", value);
        delay(drate);
        if(value == prev) {
            // all good
            // no changes needed
            delay(10);

        }
        else if(value < prev) {
            // lower drate
            if((prev - 10) >= value) {
                drate = drate-10;

                delay(10);
            }

        }
        else {
            // increase drate
            if((prev +10) <= value) {
                drate = drate + 10;
            }
        }
        set(0x33, 0);        
        delay(drate);
        set(0x33, 1);
        delay(mtime-drate);


    }
    return 0;
}


int read(int addr) {
    // need to randomize between 1 and 40
    int hex = 20;
    return hex;   
}
int set(int addr, short data) {
    // simulate setting the pin
    print("%d is set with %d", &addr, &data);

}