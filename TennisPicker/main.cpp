#include "mbed-os/mbed.h"
#include "parallax/parallax.h"
#include "uLCD_4DGL/uLCD_4DGL.h"

uLCD_4DGL uLCD(D12, D11, D2);

double SERVO_CONTROL_DELAY = 0.1f;
Serial pc(USBTX, USBRX);
Serial rpi(D1, D0);
PwmOut left_servo_pin(D11), right_servo_pin(D12);
//    PwmOut left_shoulder_pin(D5), right_shoulder_pin(D6);
//    PwmOut left_wrist_pin(D9), right_wrist_pin(D10);

parallax_servo *left_servo;
parallax_servo *right_servo;
// parallax_stdservo *left_shoulder, *right_shoulder, *left_wrist, *right_wrist;
void car_set_speed(int, int);
//void arm_set_init();

void init(){
    left_servo = new parallax_servo(left_servo_pin);
    right_servo = new parallax_servo(right_servo_pin);
    servo_ticker.attach(&servo_control, .5);

    uLCD.background_color(0xFF0000);
    uLCD.color(0xFAFBFC);
    uLCD.locate(1,2);
    uLCD.printf("INIT");
    wait(5);
    //uLCD.cls();
    // uLCD.text_width(3);
    // uLCD.text_height(4);
    
    
    // left_shoulder = new parallax_stdservo(left_shoulder_pin);
    // right_shoulder = new parallax_stdservo(right_shoulder_pin);
    // left_wrist = new parallax_stdservo(left_wrist_pin);
    // right_wrist = new parallax_stdservo(right_wrist_pin);

    car_set_speed(0, 0);
    // arm_set_init();

    pc.baud(115200);
    rpi.baud(38400);
}


void catch_the_ball();

void flushSerialBuffer(void) { 
    char char1 = 0; 
    while (pc.readable()){ 
        char1 = pc.getc(); 
    } 
    return; 
}

int main(void){
    init();

    // uLCD.cls();
    uLCD.text_width(1);
    uLCD.text_height(2);
    uLCD.color(0xFAFBFC);
    uLCD.printf("FINDING");

    while(1){
        // pc.printf("hi");
        while(rpi.readable()){
            char c = rpi.getc();
            flushSerialBuffer();
            pc.printf("%d\n\r", c);
            if (c == 'w'){
                car_set_speed(50, 50);
            }
            else if (c == 'b'){
                car_set_speed(-20, -20);
            }
            else if (c == 'l'){
                car_set_speed(-20, 20);
            }
            else if (c == 'r'){
                car_set_speed(20, -20);
            }
            else if (c == 'c'){
                car_set_speed(0, 0);
                catch_the_ball();
            }
            else {
                car_set_speed(0, 0);
            }
        }
    }
}

void catch_the_ball(){
    int i;

    // uLCD.cls();
    uLCD.text_width(3);
    uLCD.text_height(4);
    uLCD.color(0xFAFBFC);
    uLCD.printf("CATCH");
    // for (i = (-90); i <= 20; i+=5){
    //     *left_shoulder = i;
    //     wait(0.05f);
    //     *right_shoulder = 0 - i;
    //     wait(0.05f);
    //     // printf("%d\n\r", i);
    // }
    // wait(1);

    // *left_wrist = 20;
    // printf("LeftWrist\r\n");
    // wait(0.5);
    // *right_wrist = -20;
    // printf("RightWrist\r\n");
    // wait(0.5);
    // wait(1);
    // for (i = (-90); i <= 20; i+=){
    //     *left_wrist = i;
    //     *right_wrist = 0 - i;
    //     wait(0.02f);
    // }

    // *left_shoulder = -90;
    // *right_shoulder = 90;
    // wait(1);
    // // for (i = 90; i--; i > -90){
    // //     *left_wrist = i;
    // //     *right_wrist = 0 - i;
    // //     wait(0.01f);
    // // }
    // *left_wrist = 90;
    // *right_wrist = -90;
    wait(5);
    // uLCD.cls();
    uLCD.text_width(1);
    uLCD.text_height(2);
    uLCD.color(0xFAFBFC);
    uLCD.printf("FINDING");
}

void arm_set_init(){
    // *left_shoulder = (-90);
    // *right_shoulder = (90);

    // *left_wrist = 90;
    // *right_wrist = -90;
}

void car_set_speed(int left, int right){
    *left_servo = left;
    *right_servo = 0 - right;
    wait(SERVO_CONTROL_DELAY);
}
