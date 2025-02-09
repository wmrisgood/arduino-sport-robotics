#include "sport_DXL2023.h"
#include "sport_definitions.h"
#include "sport_menu.h"



void setup()
{

  robot_setup();

  //eeprom set in code
  T90=136;spd=255;range_value=20;
  EEPROM_write_int(T90_address, T90);
  EEPROM_write_int(spd_address, spd);
  EEPROM_write_int(range_address, range_value);
  
  //compass eeprom
  DN=96,DE=188,DS=277;
  EEPROM_write_int(DN_address, DN);
  EEPROM_write_int(DE_address, DE);
  EEPROM_write_int(DS_address, DS);

  // servo positions
  basket_up=275,basket_normal=500,arm_normal=660,arm_down=190,arm_dropping=800,gripper_close=900,gripper_open=590;
  EEPROM_write_int(basket_up_address, basket_up);
  EEPROM_write_int(basket_normal_address, basket_normal);
  EEPROM_write_int(arm_normal_address, arm_normal);
  EEPROM_write_int(arm_down_address, arm_down);
  EEPROM_write_int(arm_dropping_address, arm_dropping);
  EEPROM_write_int(gripper_close_address, gripper_close);
  EEPROM_write_int(gripper_open_address, gripper_open);

  //ev zone setup
  barband[0]=0;barband[1]=0;barband[2]=0;barband[3]=0;
  
  menu();
  //move_arm(arm_normal,500);move_gripper(gripper_open,500);delay(1500);
  go(60,60);
  while ((SM + SL1 + SL2 + SL3 + SL4 + SL5 + SL6 + SR1 + SR2 + SR3 + SR4 + SR5 + SR6) > 5);
  move(forward,T90/2);
}




void loop(){
  linefollow();
  //sensecolor(); 
   color_detection();
}