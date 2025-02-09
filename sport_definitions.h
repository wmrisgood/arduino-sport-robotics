#include <LiquidCrystal.h>
#include <EEPROM.h>
#include <Wire.h>

#define battery_adc analogRead(A7)

#define start_pin 6 // remote
#define pingPin 25
#define echoPin  16
#define start digitalRead(6)
#define next_page_pin 8
#define next_page digitalRead(8)
#define previuse_page_pin 9
#define previuse_page digitalRead(9)
#define increase_pin 10
#define increase digitalRead(10)
#define decrease_pin 11
#define decrease digitalRead(11)

#define MUX_A 44
#define MUX_B 43
#define MUX_C 42

#define deg     cmps(1)
#define pitch   cmps(2)
#define role    cmps(3)

LiquidCrystal lcd(28, 30, 31, 32, 33, 34); // lcd(rs, en, d4, d5, d6, d7);

// eeprom
int range_value=0,spd = 0, T90 = 0, m1 = 0, m2 = 0, m3 = 0, m4 = 0;
int basket_up=0,basket_normal=0,arm_normal=0,arm_down=0,arm_dropping=0,gripper_close=0,gripper_open=0,check_while_finished,first_touched,correct,side_check,ev_b_ball,turnedtodeg,x_ball=5;
int DN=0,DE=0,DS=0,DW=0;
unsigned int redroom_time;
int silver_voltage_R=03,silver_voltage_L=03;
#define RED 0 // be khatereh tabeye calibrate, tartib rangha mohemeh
#define GREEN 1
#define BLUE 2
#define AMB 3
#define YELLOW 4
#define SILVER 5
#define BLACK 6
#define WHITE 7

#define forward 10
#define Left 11
#define Right 12
#define Back 13
#define sides 3


#define conductive 1
#define inconductive 0

#define xl_error 70


#define SM read_sensor(0, 0, 0)
#define SL1 read_sensor(1, 0, 0)
#define SL2 read_sensor(2, 0, 0)
#define SL3 read_sensor(3, 0, 0)
#define SL4 read_sensor(4, 0, 0)
#define SL5 read_sensor(5, 0, 0)
#define SL6 read_sensor(6, 0, 0)
#define SL7 read_sensor(7, 0, 0)
#define SL8 read_sensor(0, 2, 0)
#define SL9 read_sensor(1, 2, 0)
#define SL10 read_sensor(2, 2, 0)
#define SL11 read_sensor(2, 2, 0)
#define SFL read_sensor(4, 2, 0)
#define ball read_sensor(5, 2, 0)
#define obs read_sensor(6, 2, 0)
#define vic read_sensor(5, 3, 0)
#define free2 read_sensor(7, 2, 0)

#define SMB read_sensor(0, 1, 0)
#define SR1 read_sensor(1, 1, 0)
#define SR2 read_sensor(2, 1, 0)
#define SR3 read_sensor(3, 1, 0)
#define SR4 read_sensor(4, 1, 0)
#define SR5 read_sensor(5, 1, 0)
#define SR6 read_sensor(6, 1, 0)
#define SR7 read_sensor(7, 1, 0)
#define SR8 read_sensor(0, 3, 0)
#define SR9 read_sensor(1, 3, 0)
#define SR10 read_sensor(2, 3, 0)
#define con read_sensor(3, 3, 0)
#define SFR read_sensor(4, 3, 0)
#define free1 read_sensor(5, 3, 0)

#define VSM read_sensor(0, 0, 1)
#define VSL1 read_sensor(1, 0, 1)
#define VSL2 read_sensor(2, 0, 1)
#define VSL3 read_sensor(3, 0, 1)
#define VSL4 read_sensor(4, 0, 1)
#define VSL5 read_sensor(5, 0, 1)
#define VSL6 read_sensor(6, 0, 1)
#define VSL7 read_sensor(7, 0, 1)
#define VSL8 read_sensor(0, 2, 1)
#define VSL9 read_sensor(1, 2, 1)
#define VSL10 read_sensor(2, 2, 1)
#define VSL11 read_sensor(2, 2, 1)
#define VSFL read_sensor(4, 2, 1)
#define Vball read_sensor(5, 2, 1)
#define Vobs read_sensor(6, 2, 1)
#define Vvic read_sensor(5, 3, 1)
#define Vfree2 read_sensor(7, 2, 1)

#define VSMB read_sensor(0, 1, 1)
#define VSR1 read_sensor(1, 1, 1)
#define VSR2 read_sensor(2, 1, 1)
#define VSR3 read_sensor(3, 1, 1)
#define VSR4 read_sensor(4, 1, 1)
#define VSR5 read_sensor(5, 1, 1)
#define VSR6 read_sensor(6, 1, 1)
#define VSR7 read_sensor(7, 1, 1)
#define VSR8 read_sensor(0, 3, 1)
#define VSR9 read_sensor(1, 3, 1)
#define VSR10 read_sensor(2, 3, 1)
#define Vcon read_sensor(3, 3, 1)
#define VSFR read_sensor(4, 3, 1)
#define Vfree1 read_sensor(5, 3, 1)

#define color_L color(1)
#define color_R color(2)
#define color_F color(3)
#define LEFT 0
#define RIGHT 1

#define intersectionL ((SM || SL1 || SR1) && SL10)
#define intersectionR ((SM || SL1 || SR1) && SR10)

// EEPROM addresses
#define spd_address 150
#define T90_address 152
#define range_address 154
#define DN_address 156
#define DE_address 158
#define DS_address 160
#define DW_address 162
#define basket_up_address 164
#define basket_normal_address 166
#define arm_normal_address 168
#define arm_down_address 170
#define arm_dropping_address 172
#define gripper_close_address 174
#define gripper_open_address 176

#define range EEPROM_read_int(range_address)
#define buz_on digitalWrite(35, 1)
#define buz_off digitalWrite(35, 0)
#define LED_on digitalWrite(13, 1)
#define LED_off digitalWrite(13, 0)

#define SBL digitalRead(37)
#define SBR digitalRead(38)

#define VL53L0X_ADDRESS 0x29
#define VL53L0X_REG_SYSRANGE_START 0x00
#define VL53L0X_REG_RESULT_RANGE_VAL 0x1E

void beep(int num);
#define shooter_on digitalWrite(12, 1)
#define shooter_off digitalWrite(12, 0)

#define VL_Left vl(2)
#define VL_Right vl(1)
#define VL_Front vl(3)

#define Front_distance ultrasonic()

const int cmps_address = 0x60;

void shoot();
void go(int left, int right);
int ultrasonic();
void avoid_obstacle (int obs_direction);
int cmps(int select);
void ev_zone();


void EEPROM_write_int(int address, int number);
int EEPROM_read_int(int address);

int read_sensor(char sensorNum, char pinNum, char outputMode);

int red, green, blue, clear, color_out;
int left_card=WHITE;
int right_card=WHITE;
int direction=Left;
long duration, cm;
int touch_count=0;
int ball_num=0,redroom_dir=0,fifth=0,s_ball=0,b_ball=0,victim_checked,farz,both_touched,ev_ball,pich_sakoo,found_dep,ev_deg,found_deg,no_side,its_not_obs;


// these characters are used to define eeprom room numbers
static char red_left_r = 20, red_left_g = 22, red_left_b = 24, red_left_c = 26;
static char green_left_r = 28, green_left_g = 30, green_left_b = 32, green_left_c = 34;
static char blue_left_r = 36, blue_left_g = 38, blue_left_b = 40, blue_left_c = 42;
static char yellow_left_r = 44, yellow_left_g = 46, yellow_left_b = 48, yellow_left_c = 50;
static char silver_left_r = 52, silver_left_g = 54, silver_left_b = 56, silver_left_c = 58;

static char red_right_r = 60, red_right_g = 62, red_right_b = 64, red_right_c = 66;
static char green_right_r = 68, green_right_g = 70, green_right_b = 72, green_right_c = 74;
static char blue_right_r = 76, blue_right_g = 78, blue_right_b = 80, blue_right_c = 82;
static char yellow_right_r = 84, yellow_right_g = 86, yellow_right_b = 88, yellow_right_c = 90;
static char silver_right_r = 92, silver_right_g = 94, silver_right_b = 96, silver_right_c = 98;
static char red_front_r = 100, red_front_g = 102, red_front_b = 104, red_front_c = 106;
static char green_front_r = 108, green_front_g = 110, green_front_b = 112, green_front_c = 114;
char barband[4];

char color(char select);
void color_calib(void);
void menu_setup(void);
void menu_sensor(void);
void menu_motor(void);
void menu_color(void);
void menu(void);
void menu_init();

