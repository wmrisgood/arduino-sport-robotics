// menu 16
void move(int direction, int lenth, int speed);
unsigned int vl(char xv);
void handle_color();
void get_out();

void beep(int num) {
  for (int i = 0; i < num; i++) {
    buz_on;
    delay(50);
    buz_off;
    delay(50);
  }
}
void move_arm(int pos, int speed) {
  AX(11, pos, speed);
  AX(10, 1023 - pos, speed);
}

void shoot() {
  shooter_on;
  delay(200);
  shooter_off;
  delay(200);
}
void linefollow_Red() {
  int spd = EEPROM_read_int(spd_address);
  if (SM == 1) go(spd, spd);

  else if (SL1) go(spd * 0.5, spd * 1.1);
  else if (SR1) go(spd * 1.1, spd * 0.5);

  else if (SL2) go(-spd * 0.5, spd * 1.2);
  else if (SR2) go(spd * 1.2, -spd * 0.5);

  else if (SL3) go(-spd * 0.7, spd);
  else if (SR3) go(spd, -spd * 0.7);

  else if (SL4) go(-spd * 0.9, spd);
  else if (SR4) go(spd, -spd * 0.9);

  else if (SL5) go(-spd, spd);
  else if (SR5) go(spd, -spd);

  else if (SL6) go(-spd, spd);
  else if (SR6) go(spd, -spd);

  else if (SL7) go(-spd, spd);
  else if (SR7) go(spd, -spd);

  else if (SL8) go(-spd, spd);
  else if (SR8) go(spd, -spd);

  else if (SL9) go(-spd, spd);
  else if (SR9) go(spd, -spd);
  if (color_L == RED || color_R == RED) {
    go(0, 0);
    beep(5);
    while (1)
      ;
  }
  handle_color();
  if (Front_distance < 100) avoid_obstacle(Left);
  delay(20);


  /*
  if ((SM + SL1 + SL2 + SL3 + SL4 + SL5 + SL6 + SR1 + SR2 + SR3 + SR4 + SR5 + SR6) > 9) {
    lcd.clear();
    lcd.print("End");
    while (true) {
      go(0, 0);
      beep(10);
    }
  }
  */
}
void linefollow() {
  if (SM == HIGH) {
    go(255, 255);
  } else if (SR1 == HIGH) {
    go(220, 120);
  } else if (SR2 == HIGH) {
    go(255, 85);
  } else if (SR3 == HIGH) {
    go(255, -105);
  } else if (SR4 == HIGH) {
    go(255, -175);
  } else if (SR5 == HIGH) {
    go(255, -255);
  } else if (SR6 == HIGH) {
    go(255, -255);
  } else if (SL1 == HIGH) {
    go(155, 255);
  } else if (SL2 == HIGH) {
    go(85, 255);
  } else if (SL3 == HIGH) {
    go(-105, 255);
  } else if (SL4 == HIGH) {
    go(-175, 255);
  } else if (SL5 == HIGH) {
    go(-255, 255);
  } else if (SL6 == HIGH) {
    go(-255, 255);
  } else {
    go(255, 255);
  }
}
void linefollow_item() {
  int spd = EEPROM_read_int(spd_address);

  if (SL10 && SM) {
    move(forward, T90 / 8, 100);
    move(Left, T90 * 0.8, 100);
    go(-spd * 1.5, spd * 0.35);
  } else if (SR10 && SM) {
    move(forward, T90 / 8, 100);
    move(Right, T90 * 0.8, 100);
    go(spd * 0.35, -spd * 1.5);
  }

  if (SM == 1) go(spd, spd);

  if (SL10) {
    move(forward, T90 / 8, 100);
    move(Left, T90 * 0.8, 100);
    go(-spd * 1.5, spd * 0.35);
  } else if (SR10) {
    move(forward, T90 / 8, 100);
    move(Right, T90 * 0.8, 100);
    go(spd * 0.35, -spd * 1.5);
  }

  else if (SL1) go(spd * 0.5, spd * 1.1);
  else if (SR1) go(spd * 1.1, spd * 0.5);

  else if (SL2) go(-spd * 0.5, spd * 1.2);
  else if (SR2) go(spd * 1.2, -spd * 0.5);

  else if (SL3) go(-spd * 0.7, spd);
  else if (SR3) go(spd, -spd * 0.7);

  else if (SL4) go(-spd * 0.9, spd);
  else if (SR4) go(spd, -spd * 0.9);

  else if (SL5) go(-spd, spd);
  else if (SR5) go(spd, -spd);

  else if (SL6) go(-spd, spd);
  else if (SR6) go(spd, -spd);

  else if (SL7) go(-spd, spd);
  else if (SR7) go(spd, -spd);

  else if (SL8) go(-spd, spd);
  else if (SR8) go(spd, -spd);

  else if (SL9) go(-spd, spd);
  else if (SR9) go(spd, -spd);
}
void go(int left, int right) {
  left = -left;
  right = -right;

  if (left > 255)
    left = 255;
  if (left < -255)
    left = -255;
  if (right > 255)
    right = 255;
  if (right < -255)
    right = -255;

  if (left <= 0) {
    digitalWrite(2, LOW);
    analogWrite(3, -left);
  } else if (left > 0) {
    digitalWrite(2, HIGH);
    analogWrite(3, -left);
  }

  if (right <= 0) {
    digitalWrite(4, LOW);
    analogWrite(5, -right);
  }

  else if (right > 0) {
    digitalWrite(4, HIGH);
    analogWrite(5, -right);
  }
}


void EEPROM_write_int(int address, int number) {
  EEPROM.write(address, number >> 8);
  EEPROM.write(address + 1, number & 0xFF);
}

int EEPROM_read_int(int address) {
  int result = 0;
  result = (EEPROM.read(address) << 8) + EEPROM.read(address + 1);
  return result;
}

int read_sensor(char sensorNum, char pinNum, char outputMode) {
  int output = 0;
  byte n1 = sensorNum & 0b0001;
  byte n2 = (sensorNum & 0b0010) / 2;
  byte n3 = (sensorNum & 0b0100) / 4;

  digitalWrite(MUX_A, n1);
  digitalWrite(MUX_B, n2);
  digitalWrite(MUX_C, n3);
  if (outputMode == 0)  // digital Mode
  {
    if (pinNum == 0)
      output = digitalRead(A0);
    else if (pinNum == 1)
      output = digitalRead(A1);
    else if (pinNum == 2)
      output = digitalRead(A2);
    else if (pinNum == 3)
      output = digitalRead(A3);
  } else if (outputMode == 1)  // analog Mode
  {
    if (pinNum == 0)
      output = analogRead(A0);
    else if (pinNum == 1)
      output = analogRead(A1);
    else if (pinNum == 2)
      output = analogRead(A2);
    else if (pinNum == 3)
      output = analogRead(A3);
    output = output * 5 / 102.3;
  }
  return output;
}

void colortest() {
  unsigned char low_byte, high_byte;
  digitalWrite(MUX_C, LOW);
  digitalWrite(MUX_B, LOW);
  digitalWrite(MUX_A, LOW);
  delayMicroseconds(10);

  Wire.beginTransmission(57);  // transmit to device #57 (0x39)
  Wire.write(byte(0x80));
  Wire.write(byte(3));  // power
  Wire.endTransmission();

  Wire.beginTransmission(57);  // transmit to device #57 (0x39)
  Wire.write(byte(0x8F));
  Wire.write(byte(1));  // gain
  Wire.endTransmission();

  Wire.beginTransmission(57);  // transmit to device #57 (0x39)
  Wire.write(byte(0x94));      // address of first data
  Wire.endTransmission();

  Wire.requestFrom(57, 8);
  if (8 <= Wire.available())  // if 8 bytes were received
  {
    low_byte = Wire.read();
    high_byte = Wire.read();
    clear = high_byte * 255 + low_byte;

    low_byte = Wire.read();
    high_byte = Wire.read();
    red = high_byte * 255 + low_byte;

    low_byte = Wire.read();
    high_byte = Wire.read();
    green = high_byte * 255 + low_byte;

    low_byte = Wire.read();
    high_byte = Wire.read();
    blue = (high_byte * 255 + low_byte) - 10;
  }

  if (green > red && green > blue) {
    AX(11, 600, 100);
    delay(1000);
    AX(11, 800, 100);
    delay(1000);
  }
  delay(500);
}

char color(char select) {
  unsigned char low_byte, high_byte;
  if (select == 1)  // left
  {
    digitalWrite(MUX_C, LOW);
    digitalWrite(MUX_B, LOW);
    digitalWrite(MUX_A, LOW);
    //  Serial.print("left color:  ");
  } else if (select == 2)  // right
  {
    digitalWrite(MUX_C, LOW);
    digitalWrite(MUX_B, LOW);
    digitalWrite(MUX_A, HIGH);
    //  Serial.print("right color:  ");
  } else {
    digitalWrite(MUX_A, HIGH);  //front
    digitalWrite(MUX_B, HIGH);
    digitalWrite(MUX_C, LOW);
  }
  delayMicroseconds(10);

  Wire.beginTransmission(57);  // transmit to device #57 (0x39)
  Wire.write(byte(0x80));
  Wire.write(byte(3));  // power
  Wire.endTransmission();

  Wire.beginTransmission(57);  // transmit to device #57 (0x39)
  Wire.write(byte(0x8F));
  Wire.write(byte(1));  // gain
  Wire.endTransmission();

  Wire.beginTransmission(57);  // transmit to device #57 (0x39)
  Wire.write(byte(0x94));      // address of first data
  Wire.endTransmission();

  Wire.requestFrom(57, 8);
  if (8 <= Wire.available())  // if 8 bytes were received
  {
    low_byte = Wire.read();
    high_byte = Wire.read();
    clear = high_byte * 255 + low_byte;

    low_byte = Wire.read();
    high_byte = Wire.read();
    red = high_byte * 255 + low_byte;

    low_byte = Wire.read();
    high_byte = Wire.read();
    green = high_byte * 255 + low_byte;

    low_byte = Wire.read();
    high_byte = Wire.read();
    blue = (high_byte * 255 + low_byte) - 10;
  }

  if (select == 1)  // left
  {
    if (red > green && red > blue && red < EEPROM_read_int(red_left_r) + range && red > EEPROM_read_int(red_left_r) - range && green < EEPROM_read_int(red_left_g) + range && green > EEPROM_read_int(red_left_g) - range && blue < EEPROM_read_int(red_left_b) + range && blue > EEPROM_read_int(red_left_b) - range && clear < EEPROM_read_int(red_left_c) + range && clear > EEPROM_read_int(red_left_c) - range)
      color_out = RED;

    //else if (green > red && green > blue && red < EEPROM_read_int(green_left_r) + range && red > EEPROM_read_int(green_left_r) - range && green > EEPROM_read_int(green_left_g)-range/2 && green < EEPROM_read_int(green_left_g) + range && blue < EEPROM_read_int(green_left_b) + range && blue > EEPROM_read_int(green_left_b) - range /*&& clear < EEPROM_read_int(green_left_c) + range*/ && clear > EEPROM_read_int(green_left_c) - range/2)
    else if (green > red && green > blue && red < EEPROM_read_int(green_left_r) + range && red > EEPROM_read_int(green_left_r) - range && green < EEPROM_read_int(green_left_g) + range && green > EEPROM_read_int(green_left_g) - range && blue < EEPROM_read_int(green_left_b) + range && blue > EEPROM_read_int(green_left_b) - range && clear < EEPROM_read_int(green_left_c) + range && clear > EEPROM_read_int(green_left_c) - range) { color_out = GREEN; }  //beep(1);}

    else if (blue > red && blue > green && red < EEPROM_read_int(blue_left_r) + range && red > EEPROM_read_int(blue_left_r) - range && green < EEPROM_read_int(blue_left_g) + range && green > EEPROM_read_int(blue_left_g) - range && blue < EEPROM_read_int(blue_left_b) + range && blue > EEPROM_read_int(blue_left_b) - range && clear < EEPROM_read_int(blue_left_c) + range && clear > EEPROM_read_int(blue_left_c) - range)
      color_out = BLUE;

    else if (red < EEPROM_read_int(yellow_left_r) + range && red > EEPROM_read_int(yellow_left_r) - range && green < EEPROM_read_int(yellow_left_g) + range && green > EEPROM_read_int(yellow_left_g) - range && blue < EEPROM_read_int(yellow_left_b) + range && blue > EEPROM_read_int(yellow_left_b) - range && clear < EEPROM_read_int(yellow_left_c) + range && clear > EEPROM_read_int(yellow_left_c) - range)
      color_out = YELLOW;

    else if (
      red <= (EEPROM_read_int(silver_left_r) + range) && red >= (EEPROM_read_int(silver_left_r) - range) && green >= (EEPROM_read_int(silver_left_g) - range) && green <= (EEPROM_read_int(silver_left_g) + range) && blue >= (EEPROM_read_int(silver_left_b) - range) && blue <= (EEPROM_read_int(silver_left_b) + range) && clear <= (EEPROM_read_int(silver_left_c) + range) && clear >= (EEPROM_read_int(silver_left_c) - range)) {
      color_out = SILVER;
    }

    else
      color_out = WHITE;

    return color_out;
  } else if (select == 2)  // right
  {
    if (red > green && red > blue && red < EEPROM_read_int(red_right_r) + range && red > EEPROM_read_int(red_right_r) - range && green < EEPROM_read_int(red_right_g) + range && green > EEPROM_read_int(red_right_g) - range && blue < EEPROM_read_int(red_right_b) + range && blue > EEPROM_read_int(red_right_b) - range && clear < EEPROM_read_int(red_right_c) + range && clear > EEPROM_read_int(red_right_c) - range)
      color_out = RED;
    //else if (green > red && green > blue && red < EEPROM_read_int(green_right_r) + range && red > EEPROM_read_int(green_right_r) - range && green > EEPROM_read_int(green_right_g)-range/2 && green < EEPROM_read_int(green_right_g) + range && blue < EEPROM_read_int(green_right_b) + range && blue > EEPROM_read_int(green_right_b) - range /*&&  clear < EEPROM_read_int(green_right_c) + range */ && clear > EEPROM_read_int(green_right_c) - range/2)
    else if (green > red && green > blue && red < EEPROM_read_int(green_right_r) + range && red > EEPROM_read_int(green_right_r) - range && green < EEPROM_read_int(green_right_g) + range && green > EEPROM_read_int(green_right_g) - range && blue < EEPROM_read_int(green_right_b) + range && blue > EEPROM_read_int(green_right_b) - range && clear < EEPROM_read_int(green_right_c) + range && clear > EEPROM_read_int(green_right_c) - range)
      color_out = GREEN;

    else if (blue > red && blue > green && red < EEPROM_read_int(blue_right_r) + range && red > EEPROM_read_int(blue_right_r) - range && green < EEPROM_read_int(blue_right_g) + range && green > EEPROM_read_int(blue_right_g) - range && blue < EEPROM_read_int(blue_right_b) + range && blue > EEPROM_read_int(blue_right_b) - range && clear < EEPROM_read_int(blue_right_c) + range && clear > EEPROM_read_int(blue_right_c) - range)
      color_out = BLUE;

    else if (red < EEPROM_read_int(yellow_right_r) + range && red > EEPROM_read_int(yellow_right_r) - range && green < EEPROM_read_int(yellow_right_g) + range && green > EEPROM_read_int(yellow_right_g) - range && blue < EEPROM_read_int(yellow_right_b) + range && blue > EEPROM_read_int(yellow_right_b) - range && clear < EEPROM_read_int(yellow_right_c) + range && clear > EEPROM_read_int(yellow_right_c) - range)
      color_out = YELLOW;

    else if (
      red <= (EEPROM_read_int(silver_right_r) + range) && red >= (EEPROM_read_int(silver_right_r) - range) && green >= (EEPROM_read_int(silver_right_g) - range) && green <= (EEPROM_read_int(silver_right_g) + range) && blue >= (EEPROM_read_int(silver_right_b) - range) && blue <= (EEPROM_read_int(silver_right_b) + range) && clear <= (EEPROM_read_int(silver_right_c) + range) && clear >= (EEPROM_read_int(silver_right_c) - range)) {
      color_out = SILVER;
    }

    else
      color_out = WHITE;

    return color_out;
  } else if (select == 3)  // front
  {
    if (red > green && red > blue && red < EEPROM_read_int(red_front_r) + range && red > EEPROM_read_int(red_front_r) - range && green < EEPROM_read_int(red_front_g) + range && green > EEPROM_read_int(red_front_g) - range && blue < EEPROM_read_int(red_front_b) + range && blue > EEPROM_read_int(red_front_b) - range && clear < EEPROM_read_int(red_front_c) + range && clear > EEPROM_read_int(red_front_c) - range)
      color_out = RED;

    else if (green > red && green > blue && red < EEPROM_read_int(green_front_r) + range && red > EEPROM_read_int(green_front_r) - range && green < EEPROM_read_int(green_front_g) + range && green > EEPROM_read_int(green_front_g) - range && blue < EEPROM_read_int(green_front_b) + range && blue > EEPROM_read_int(green_front_b) - range && clear < EEPROM_read_int(green_front_c) + range && clear > EEPROM_read_int(green_front_c) - range)
      color_out = GREEN;

    else
      color_out = WHITE;

    return color_out;
  }
  // delay(5);
}

void color_calib(void) {
  static char page = 1, last_page = 12;
  char red_l_calibrated = 0, red_r_calibrated = 0, grn_l_calibrated = 0, grn_r_calibrated = 0, blu_l_calibrated = 0, blu_r_calibrated = 0, yel_l_calibrated = 0, yel_r_calibrated = 0, sil_l_calibrated = 0, sil_r_calibrated = 0, red_f_calibrated = 0, grn_f_calibrated = 0;

  lcd.clear();
  while (1) {
    if (next_page == 0) {
      while (next_page == 0)
        ;
      page++;
      if (page > last_page)
        page = 1;
      lcd.clear();
    }

    if (previuse_page == 0) {
      while (previuse_page == 0)
        ;
      page--;
      if (page < 1)
        page = last_page;
      lcd.clear();
    }

    if (start == 0) {
      lcd.clear();
      delay(200);
    }  // baraye inke age 2 bar khastim calib konim motevajeh beshim

    if (page <= 4) {
      lcd.setCursor(3, 0);
      lcd.print("RED left    ");
      if (red_l_calibrated == 1)
        lcd.print("done");

      lcd.setCursor(3, 1);
      lcd.print("RED right   ");
      if (red_r_calibrated == 1)
        lcd.print("done");

      lcd.setCursor(3, 2);
      lcd.print("Green left  ");
      if (grn_l_calibrated == 1)
        lcd.print("done");

      lcd.setCursor(3, 3);
      lcd.print("Green right ");
      if (grn_r_calibrated == 1)
        lcd.print("done");

      lcd.setCursor(0, page - 1);
      lcd.print("-> ");
    } else if (page <= 8) {
      lcd.setCursor(3, 0);
      lcd.print("BLUE left   ");
      if (blu_l_calibrated == 1)
        lcd.print("done");

      lcd.setCursor(3, 1);
      lcd.print("BLUE right  ");
      if (blu_r_calibrated == 1)
        lcd.print("done");

      lcd.setCursor(3, 2);
      lcd.print("YELLOW left ");
      if (yel_l_calibrated == 1)
        lcd.print("done");

      lcd.setCursor(3, 3);
      lcd.print("YELLOW right ");
      if (yel_r_calibrated == 1)
        lcd.print("done");

      lcd.setCursor(0, page - 5);
      lcd.print("-> ");
    } else {
      lcd.setCursor(3, 0);
      lcd.print("SILVER left  ");
      if (sil_l_calibrated == 1)
        lcd.print("done");

      lcd.setCursor(3, 1);
      lcd.print("SILVER right ");
      if (sil_r_calibrated == 1)
        lcd.print("done");

      lcd.setCursor(3, 2);
      lcd.print("Green Front ");
      if (grn_f_calibrated == 1)
        lcd.print("done");

      lcd.setCursor(3, 3);
      lcd.print("Red Front");
      if (red_f_calibrated == 1)
        lcd.print("done");

      lcd.setCursor(0, page - 9);
      lcd.print("-> ");
    }

    if (page == 1)  // -> red left
    {
      if (start == 0) {
        color_L;
        // EEPROM_read_int(red_left_r) = red;
        // EEPROM_read_int(red_left_g) = green;
        // EEPROM_read_int(red_left_b) = blue;
        // EEPROM_read_int(red_left_c) = clear;
        EEPROM_write_int(red_left_r, red);
        EEPROM_write_int(red_left_g, green);
        EEPROM_write_int(red_left_b, blue);
        EEPROM_write_int(red_left_c, clear);
        red_l_calibrated = 1;
      }
    } else if (page == 2)  // red right
    {
      if (start == 0) {
        color_R;
        EEPROM_write_int(red_right_r, red);
        EEPROM_write_int(red_right_g, green);
        EEPROM_write_int(red_right_b, blue);
        EEPROM_write_int(red_right_c, clear);
        red_r_calibrated = 1;
      }
    }

    else if (page == 3)  // grn left
    {
      if (start == 0) {
        color_L;
        EEPROM_write_int(green_left_r, red);
        EEPROM_write_int(green_left_g, green);
        EEPROM_write_int(green_left_b, blue);
        EEPROM_write_int(green_left_c, clear);
        grn_l_calibrated = 1;
      }
    } else if (page == 4)  // grn right
    {
      if (start == 0) {
        color_R;
        EEPROM_write_int(green_right_r, red);
        EEPROM_write_int(green_right_g, green);
        EEPROM_write_int(green_right_b, blue);
        EEPROM_write_int(green_right_c, clear);
        grn_r_calibrated = 1;
      }
    }

    else if (page == 5)  // blu left
    {
      if (start == 0) {
        color_L;
        EEPROM_write_int(blue_left_r, red);
        EEPROM_write_int(blue_left_g, green);
        EEPROM_write_int(blue_left_b, blue);
        EEPROM_write_int(blue_left_c, clear);
        blu_l_calibrated = 1;
      }
    } else if (page == 6)  // blu right
    {
      if (start == 0) {
        color_R;
        EEPROM_write_int(blue_right_r, red);
        EEPROM_write_int(blue_right_g, green);
        EEPROM_write_int(blue_right_b, blue);
        EEPROM_write_int(blue_right_c, clear);
        blu_r_calibrated = 1;
      }
    }

    else if (page == 7)  // yelow left
    {
      if (start == 0) {
        color_L;
        EEPROM_write_int(yellow_left_r, red);
        EEPROM_write_int(yellow_left_g, green);
        EEPROM_write_int(yellow_left_b, blue);
        EEPROM_write_int(yellow_left_c, clear);
        yel_l_calibrated = 1;
      }
    } else if (page == 8)  // yelow right
    {
      if (start == 0) {
        color_R;
        EEPROM_write_int(yellow_right_r, red);
        EEPROM_write_int(yellow_right_g, green);
        EEPROM_write_int(yellow_right_b, blue);
        EEPROM_write_int(yellow_right_c, clear);
        yel_r_calibrated = 1;
      }
    }

    else if (page == 9)  // sil left
    {
      if (start == 0) {
        color_L;
        EEPROM_write_int(silver_left_r, red);
        EEPROM_write_int(silver_left_g, green);
        EEPROM_write_int(silver_left_b, blue);
        EEPROM_write_int(silver_left_c, clear);
        sil_l_calibrated = 1;
      }
    } else if (page == 10)  // sil right
    {
      if (start == 0) {
        color_R;
        EEPROM_write_int(silver_right_r, red);
        EEPROM_write_int(silver_right_g, green);
        EEPROM_write_int(silver_right_b, blue);
        EEPROM_write_int(silver_right_c, clear);
        sil_r_calibrated = 1;
      }
    } else if (page == 11)  // grn front
    {
      if (start == 0) {
        color_F;
        EEPROM_write_int(green_front_r, red);
        EEPROM_write_int(green_front_g, green);
        EEPROM_write_int(green_front_b, blue);
        EEPROM_write_int(green_front_c, clear);
        grn_f_calibrated = 1;
      }
    } else if (page == 12)  // red front
    {
      if (start == 0) {
        color_F;
        EEPROM_write_int(red_front_r, red);
        EEPROM_write_int(red_front_g, green);
        EEPROM_write_int(red_front_b, blue);
        EEPROM_write_int(red_front_c, clear);
        red_f_calibrated = 1;
      }
    }
  }
}

void menu_setup(void) {
  static char page = 1, last_page = 8;
  int spd = EEPROM_read_int(spd_address);
  int T90 = EEPROM_read_int(T90_address);
  int range_value = EEPROM_read_int(range_address);
  int DN = EEPROM_read_int(DN_address);
  int DE = EEPROM_read_int(DE_address);
  int DS = EEPROM_read_int(DS_address);
  int ev_s_ball = EEPROM_read_int(DW_address);

  lcd.clear();

  while (1) {
    if (next_page == 0) {
      while (next_page == 0)
        ;
      delay(50);
      page++;
      if (page > last_page)
        page = 1;
      lcd.clear();
    }
    if (previuse_page == 0) {
      while (previuse_page == 0)
        ;
      delay(50);
      page--;
      if (page < 1)
        page = last_page;
      lcd.clear();
    }
    if (page < 5) {
      lcd.setCursor(2, 0);
      lcd.printf("speed     %3d ", spd);

      lcd.setCursor(2, 1);
      lcd.printf("T90       %3d ", T90);

      lcd.setCursor(2, 2);
      lcd.printf("calib rng %3d ", range);

      lcd.setCursor(2, 3);
      lcd.printf("reset memory   ");

      lcd.setCursor(0, page - 1);
      lcd.print(">");
    } else if (page < 9) {

      lcd.setCursor(2, 0);
      lcd.printf("DN  %d  deg: %d ", DN, deg);

      lcd.setCursor(2, 1);
      lcd.printf("DE  %d ", DE);

      lcd.setCursor(2, 2);
      lcd.printf("DS  %d ", DS);

      lcd.setCursor(2, 3);
      lcd.printf("ev_s_ball  %d ", ev_s_ball);

      lcd.setCursor(0, page - 5);
      lcd.print(">");
    }

    if (page == 1)  // spd
    {
      if (increase == 0) {
        delay(120);
        spd += 10;
        if (spd > 255)
          spd = 255;
        EEPROM_write_int(spd_address, spd);
      } else if (decrease == 0) {
        delay(120);
        spd -= 10;
        if (spd < 10)
          spd = 10;
        EEPROM_write_int(spd_address, spd);
      } else if (start == 0) {
        go(spd, spd);
        while (start == 0)
          ;
        go(0, 0);
        EEPROM_write_int(spd_address, spd);
      }
    } else if (page == 2)  // T90
    {
      if (increase == 0) {
        delay(200);
        T90 += 1;
        EEPROM_write_int(T90_address, T90);
      } else if (decrease == 0) {
        delay(200);
        T90 -= 1;
        EEPROM_write_int(T90_address, T90);
      } else if (start == 0) {
        while (start == 0)
          ;
        lcd.clear();
        EEPROM_write_int(T90_address, T90);
        move(Left, T90, 200);
      }
    } else if (page == 3)  // range
    {
      if (increase == 0) {
        delay(100);
        range_value += 1;
        if (range_value > 80)
          range_value = 80;
        EEPROM_write_int(range_address, range_value);
      } else if (decrease == 0) {
        delay(100);
        range_value -= 1;
        if (range_value < 5)
          range_value = 5;
        EEPROM_write_int(range_address, range_value);
      }
    } else if (page == 4)  // reset memory
    {
      if (start == 0) {
        lcd.clear();
        while (start == 0)
          ;
        for (int i = 0; i < 200; i++)
          EEPROM.write(i, 0);
      }
    } else if (page == 5)  // DN
    {
      if (start == 0) {
        while (start == 0)
          ;
        DN = deg;
        EEPROM_write_int(DN_address, DN);
      }
    } else if (page == 6)  // DE
    {
      if (start == 0) {
        while (start == 0)
          ;
        DE = deg;
        EEPROM_write_int(DE_address, DE);
      }
    } else if (page == 7)  // DS
    {
      if (start == 0) {
        while (start == 0)
          ;
        DS = deg;
        EEPROM_write_int(DS_address, DS);
      }
    } else if (page == 8)  // DW
    {
      if (start == 0) {
        while (start == 0)
          ;
        ev_s_ball = 0;
        EEPROM_write_int(DW_address, ev_s_ball);
      }
    }
  }
}
long microsecondsToMillimeters(long microseconds) {
  return microseconds * 10 / 29 / 2;
}
void menu_sensor(void) {
  static char page = 1, last_page = 6;
  lcd.clear();
  while (1) {
    if (next_page == 0) {
      while (next_page == 0)
        ;
      delay(50);
      page++;
      if (page > last_page)
        page = 1;
      lcd.clear();
    }
    if (previuse_page == 0) {
      while (previuse_page == 0)
        ;
      delay(50);
      page--;
      if (page < 1)
        page = last_page;
      lcd.clear();
    }
    if (increase == 0)
      go(40, 40);
    else if (decrease == 0)
      go(-40, -40);
    else
      go(0, 0);

    ///////////////

    if (page == 1) {
      lcd.setCursor(0, 0);
      lcd.printf("%d       %d      %d", SL10, SM, SR10);

      lcd.setCursor(0, 1);
      lcd.printf("   %d%d%d    %d%d%d   ", SL3, SL2, SL1, SR1, SR2, SR3);

      lcd.setCursor(0, 2);
      lcd.printf("%d%d%d  ENC=%3d %d%d%d", SL6, SL5, SL4, cnt / 100, SR4, SR5, SR6);

      lcd.setCursor(0, 3);
      lcd.printf("%d%d%d", SL9, SL8, SL7);

      lcd.setCursor(13, 3);
      lcd.printf("%d%d%d", SR7, SR8, SR9);

      lcd.setCursor(4, 3);
      if (color_L == RED)
        lcd.print("RED ");
      else if (color_L == GREEN)
        lcd.print("GRN ");
      else if (color_L == BLUE)
        lcd.print("BLU ");
      else if (color_L == YELLOW)
        lcd.print("YEL ");
      else if (color_L == SILVER)
        lcd.print("SIL ");
      else
        lcd.print("WHT ");

      lcd.setCursor(9, 3);
      if (color_R == RED)
        lcd.print("RED");
      else if (color_R == GREEN)
        lcd.print("GRN");
      else if (color_R == BLUE)
        lcd.print("BLU");
      else if (color_R == YELLOW)
        lcd.print("YEL");
      else if (VSR6 < 0.9)
        lcd.print("SIL");
      else
        lcd.print("WHT");

      if (start == 0) {
        TCNT1 = 0;
        cnt = 0;
        //puls_cnt = 0;
      }
    } else if (page == 2)  // V left
    {
      lcd.setCursor(0, 0);
      lcd.printf("L10=%02d        %02d", VSL10, VSM);

      lcd.setCursor(5, 1);
      lcd.printf("%02d  %02d  %02d", VSL3, VSL2, VSL1);

      lcd.setCursor(2, 2);
      lcd.printf("%02d  %02d  %02d ", VSL6, VSL5, VSL4);

      lcd.setCursor(0, 3);
      lcd.printf("%02d  %02d  %02d ", VSL9, VSL8, VSL7);
    } else if (page == 3)  // V right
    {
      lcd.setCursor(0, 0);
      lcd.printf("%02d        R10=%02d", VSM, VSR10);

      lcd.setCursor(2, 1);
      lcd.printf("%02d  %02d  %02d ", VSR1, VSR2, VSR3);

      lcd.setCursor(4, 2);
      lcd.printf("%02d  %02d  %02d ", VSR4, VSR5, VSR6);

      lcd.setCursor(6, 3);
      lcd.printf("%02d  %02d  %02d ", VSR7, VSR8, VSR9);
    } else if (page == 4)  // switches
    {
      lcd.setCursor(0, 0);
      lcd.printf("SL=%d con=%d SR=%d", SFL, con, SFR);

      lcd.setCursor(0, 1);
      lcd.printf("obs = %d = %02d ", obs, Vobs);

      lcd.setCursor(0, 2);
      lcd.printf("ball=%d = %02d ", ball, Vball);

      lcd.setCursor(0, 3);
      lcd.printf("SBL=%d  SBR=%d  ", SBL, SBR);
    } else if (page == 5)  // distance
    {
      lcd.setCursor(0, 0);
      lcd.printf("Front: %d", Front_distance);
      lcd.setCursor(0, 1);
      lcd.printf("     VL_F=%d  ", VL_Front);
      lcd.setCursor(0, 2);
      lcd.printf("VL_L=%d VL_R=%d ", VL_Left, VL_Right);
      delay(200);
      lcd.clear();
    } else if (page == 6)  // compass
    {
      lcd.setCursor(0, 0);
      lcd.printf("deg: %d pi: %d ro: %d", deg, pitch, role);
    }
  }
}

void menu_motor(void) {
  static char page = 1, last_page = 8;
  signed int spd = 0;
  lcd.clear();
  int basket_up = EEPROM_read_int(basket_up_address);
  int basket_normal = EEPROM_read_int(basket_normal_address);
  int arm_normal = EEPROM_read_int(arm_normal_address);
  int arm_down = EEPROM_read_int(arm_down_address);
  int arm_dropping = EEPROM_read_int(arm_dropping_address);
  int gripper_close = EEPROM_read_int(gripper_close_address);
  int gripper_open = EEPROM_read_int(gripper_open_address);

  while (1) {
    if (next_page == 0) {
      while (next_page == 0)
        ;
      delay(50);
      page++;
      if (page > last_page)
        page = 1;
      lcd.clear();
    }

    if (previuse_page == 0) {
      while (previuse_page == 0)
        ;
      delay(50);
      page--;
      if (page < 1)
        page = last_page;
      lcd.clear();
    }

    if (page == 1)  // go
    {
      lcd.setCursor(0, 0);
      lcd.printf("go(%4d,%4d) ", spd, spd);
      if (increase == 0) {
        spd += 50;
        delay(400);
      } else if (decrease == 0) {
        spd -= 50;
        delay(400);
      } else
        spd = 0;

      if (spd > 255)
        spd = 255;
      if (spd < -255)
        spd = -255;

      go(spd, spd);
    } else if (page == 2)  // AX Basket ID=10
    {
      lcd.setCursor(0, 0);
      lcd.printf("Basket up %d %4d", 10, basket_up);
      if (start == 0) {
        EEPROM_write_int(basket_up_address, basket_up);
        AX(10, basket_up, 150);

      } else if (increase == 0) {
        delay(50);
        if (basket_up < 520)
          basket_up += 5;
      } else if (decrease == 0) {
        delay(50);

        if (basket_up > 250)
          basket_up -= 5;
      }

    } else if (page == 3)  // AX Basket Normal ID=10
    {
      lcd.setCursor(0, 0);
      lcd.printf("Basket normal %d %4d", 10, basket_normal);
      if (start == 0) {
        EEPROM_write_int(basket_normal_address, basket_normal);
        AX(10, basket_normal, 150);
      } else if (increase == 0) {
        delay(50);
        if (basket_normal < 520)
          basket_normal += 5;
      } else if (decrease == 0) {
        delay(50);

        if (basket_normal > 250)
          basket_normal -= 5;
      }

    } else if (page == 4)  // AX Arm Normal ID=11
    {
      lcd.setCursor(0, 0);
      lcd.printf("arm normal %d %4d", 10, arm_normal);
      if (start == 0) {
        AX(11, arm_normal, 150);
        EEPROM_write_int(arm_normal_address, arm_normal);
      } else if (increase == 0) {
        delay(50);
        if (arm_normal < 800)
          arm_normal += 5;
      } else if (decrease == 0) {
        delay(50);

        if (arm_normal > 150)
          arm_normal -= 5;
      }

    } else if (page == 5)  // AX Arm down ID=11
    {
      lcd.setCursor(0, 0);
      lcd.printf("arm_down %d %4d", 10, arm_down);
      if (start == 0) {
        EEPROM_write_int(arm_down_address, arm_down);
        AX(11, arm_down, 150);
      } else if (increase == 0) {
        delay(50);
        if (arm_down < 800)
          arm_down += 5;
      } else if (decrease == 0) {
        delay(50);

        if (arm_down > 150)
          arm_down -= 5;
      }

    } else if (page == 6)  // AX Arm dropping ID=11
    {
      lcd.setCursor(0, 0);
      lcd.printf("arm_dropping %d %4d", 10, arm_dropping);
      if (start == 0) {
        EEPROM_write_int(arm_dropping_address, arm_dropping);
        AX(11, arm_dropping, 150);
      } else if (increase == 0) {
        delay(50);
        if (arm_dropping < 1000)
          arm_dropping += 5;
      } else if (decrease == 0) {
        delay(50);

        if (arm_dropping > 300)
          arm_dropping -= 5;
      }

    } else if (page == 7)  // XL Gripper close 30 and 31
    {
      lcd.setCursor(0, 0);
      lcd.printf("gripper_close %d %4d", 10, gripper_close);
      if (start == 0) {
        EEPROM_write_int(gripper_close_address, gripper_close);
        XL_Gripper(30, gripper_close, 100);
        delay(50);
        XL_Gripper(31, 1023 - gripper_close + xl_error, 100);
      } else if (increase == 0) {
        delay(50);
        if (gripper_close < 890)
          gripper_close += 5;
      } else if (decrease == 0) {
        delay(50);

        if (gripper_close > 570)
          gripper_close -= 5;
      }
    } else if (page == 8)  // XL Gripper open 30 and 31
    {
      lcd.setCursor(0, 0);
      lcd.printf("gripper_open %d %4d", 10, gripper_open);
      if (start == 0) {
        EEPROM_write_int(gripper_open_address, gripper_open);
        XL_Gripper(30, gripper_open, 100);
        delay(50);
        XL_Gripper(31, 1023 - gripper_open + xl_error, 100);
      } else if (increase == 0) {
        delay(50);
        if (gripper_open < 890)
          gripper_open += 5;
      } else if (decrease == 0) {
        delay(50);

        if (gripper_open > 570)
          gripper_open -= 5;
      }
    }
  }
}

void menu_color(void) {
  static char page = 1, last_page = 8;
  lcd.clear();
  while (1) {
    if (next_page == 0) {
      while (next_page == 0)
        ;
      page++;
      if (page > last_page)
        page = 1;
      lcd.clear();
    }
    if (previuse_page == 0) {
      while (previuse_page == 0)
        ;
      page--;
      if (page == 0)
        page = last_page;
      lcd.clear();
    }
    if (increase == 0)
      go(40, 40);
    else if (decrease == 0)
      go(-40, -40);
    else
      go(0, 0);

    if (page == 1) {
      lcd.setCursor(0, 0);
      lcd.print("APDS left: ");

      lcd.setCursor(0, 1);
      lcd.print("  RED  GRN  BLU  CLR");

      lcd.setCursor(0, 2);
      lcd.printf(" %4d %4d %4d %4d", red, green, blue, clear);
      delay(100);
      if (color_L == RED) {
        lcd.setCursor(12, 0);
        lcd.print("RED   ");
        lcd.setCursor(0, 3);
        lcd.printf("M%4d %4d %4d %4d", EEPROM_read_int(red_left_r), EEPROM_read_int(red_left_g), EEPROM_read_int(red_left_b), EEPROM_read_int(red_left_c));
      } else if (color_L == GREEN) {
        lcd.setCursor(12, 0);
        lcd.print("GREEN ");
        lcd.setCursor(0, 3);
        lcd.printf("M%4d %4d %4d %4d", EEPROM_read_int(green_left_r), EEPROM_read_int(green_left_g), EEPROM_read_int(green_left_b), EEPROM_read_int(green_left_c));
      } else if (color_L == BLUE) {
        lcd.setCursor(12, 0);
        lcd.print("BLUE  ");
        lcd.setCursor(0, 3);
        lcd.printf("M%4d %4d %4d %4d", EEPROM_read_int(blue_left_r), EEPROM_read_int(blue_left_g), EEPROM_read_int(blue_left_b), EEPROM_read_int(blue_left_c));
      } else if (color_L == YELLOW) {
        lcd.setCursor(12, 0);
        lcd.print("YELLOW");
        lcd.setCursor(0, 3);
        lcd.printf("M%4d %4d %4d %4d", EEPROM_read_int(yellow_left_r), EEPROM_read_int(yellow_left_g), EEPROM_read_int(yellow_left_b), EEPROM_read_int(yellow_left_c));
      } else if (color_L == SILVER) {
        lcd.setCursor(12, 0);
        lcd.print("SILVER");
        lcd.setCursor(0, 3);
        lcd.printf("M%4d %4d %4d %4d", EEPROM_read_int(silver_left_r), EEPROM_read_int(silver_left_g), EEPROM_read_int(silver_left_b), EEPROM_read_int(silver_left_c));
      } else if (color_L == WHITE) {
        lcd.setCursor(12, 0);
        lcd.print("WHITE ");
        lcd.setCursor(0, 3);
        lcd.print("                    ");
      }
    } else if (page == 2)  // APDS Right
    {
      lcd.setCursor(0, 0);
      lcd.print("APDS Right: ");
      lcd.setCursor(0, 1);
      lcd.print("  RED  GRN  BLU ");

      lcd.setCursor(0, 2);
      lcd.printf(" %4d %4d %4d %4d", red, green, blue, clear);

      lcd.setCursor(12, 0);
      if (color_R == RED) {
        lcd.setCursor(12, 0);
        lcd.print("RED ");
        lcd.setCursor(0, 3);
        lcd.printf("M%4d %4d %4d %4d ", EEPROM_read_int(red_right_r), EEPROM_read_int(red_right_g), EEPROM_read_int(red_right_b), EEPROM_read_int(red_right_c));
      } else if (color_R == GREEN) {
        lcd.setCursor(12, 0);
        lcd.print("GRN ");
        lcd.setCursor(0, 3);
        lcd.printf("M%4d %4d %4d %4d ", EEPROM_read_int(green_right_r), EEPROM_read_int(green_right_g), EEPROM_read_int(green_right_b), EEPROM_read_int(green_right_c));
      } else if (color_R == BLUE) {
        lcd.setCursor(12, 0);
        lcd.print("BLUE");
        lcd.setCursor(0, 3);
        lcd.printf("M%4d %4d %4d %4d", EEPROM_read_int(blue_right_r), EEPROM_read_int(blue_right_g), EEPROM_read_int(blue_right_b), EEPROM_read_int(blue_right_c));
      } else if (color_R == YELLOW) {
        lcd.setCursor(12, 0);
        lcd.print("YELLOW");
        lcd.setCursor(0, 3);
        lcd.printf("M%4d %4d %4d ", EEPROM_read_int(yellow_right_r), EEPROM_read_int(yellow_right_g), EEPROM_read_int(yellow_right_b), EEPROM_read_int(yellow_right_c));
      } else if (color_R == SILVER) {
        lcd.setCursor(12, 0);
        lcd.print("SIL ");
        lcd.setCursor(0, 3);
        lcd.printf("M%4d %4d %4d %4d", EEPROM_read_int(silver_right_r), EEPROM_read_int(silver_right_g), EEPROM_read_int(silver_right_b), EEPROM_read_int(silver_right_c));
      } else if (color_R == WHITE) {
        lcd.setCursor(12, 0);
        lcd.print("WHT ");
        lcd.setCursor(0, 3);
        lcd.print("                    ");
      }
    } else if (page == 3)  // memory RED
    {
      lcd.setCursor(0, 0);
      lcd.print("memory RED:  ");

      lcd.setCursor(0, 1);
      lcd.print("  RED  GRN  BLU ");

      lcd.setCursor(0, 2);
      lcd.printf("L%4d %4d %4d ", EEPROM_read_int(red_left_r), EEPROM_read_int(red_left_g), EEPROM_read_int(red_left_b));

      lcd.setCursor(0, 3);
      lcd.printf("R%4d %4d %4d ", EEPROM_read_int(red_right_r), EEPROM_read_int(red_right_g), EEPROM_read_int(red_right_b));
    } else if (page == 4)  // memory GREEN
    {
      lcd.setCursor(0, 0);
      lcd.print("memory GRN:  ");

      lcd.setCursor(0, 1);
      lcd.print("  RED  GRN  BLU ");

      lcd.setCursor(0, 2);
      lcd.printf("L%4d %4d %4d ", EEPROM_read_int(green_left_r), EEPROM_read_int(green_left_g), EEPROM_read_int(green_left_b));

      lcd.setCursor(0, 3);
      lcd.printf("R%4d %4d %4d ", EEPROM_read_int(green_right_r), EEPROM_read_int(green_right_g), EEPROM_read_int(green_right_b));
    } else if (page == 5)  // memory BLUE
    {
      lcd.setCursor(0, 0);
      lcd.print("memory BLU:  ");

      lcd.setCursor(0, 1);
      lcd.print("  RED  GRN  BLU ");

      lcd.setCursor(0, 2);
      lcd.printf("L%4d %4d %4d ", EEPROM_read_int(blue_left_r), EEPROM_read_int(blue_left_g), EEPROM_read_int(blue_left_b));

      lcd.setCursor(0, 3);
      lcd.printf("R%4d %4d %4d ", EEPROM_read_int(blue_right_r), EEPROM_read_int(blue_right_g), EEPROM_read_int(blue_right_b));
    } else if (page == 6)  // memory Yellow
    {
      lcd.setCursor(0, 0);
      lcd.print("memory Yel:  ");

      lcd.setCursor(0, 1);
      lcd.print("  RED  GRN  BLU ");

      lcd.setCursor(0, 2);
      lcd.printf("L%4d %4d %4d ", EEPROM_read_int(yellow_left_r), EEPROM_read_int(yellow_left_g), EEPROM_read_int(yellow_left_b));

      lcd.setCursor(0, 3);
      lcd.printf("R%4d %4d %4d ", EEPROM_read_int(yellow_right_r), EEPROM_read_int(yellow_right_g), EEPROM_read_int(yellow_right_b));
    } else if (page == 7)  // memory Silver
    {
      lcd.setCursor(0, 0);
      lcd.print("memory Silver:  ");

      lcd.setCursor(0, 1);
      lcd.print("  RED  GRN  BLU ");

      lcd.setCursor(0, 2);
      lcd.printf("L%4d %4d %4d %4d", EEPROM_read_int(silver_left_r), EEPROM_read_int(silver_left_g), EEPROM_read_int(silver_left_b), EEPROM_read_int(silver_left_c));

      lcd.setCursor(0, 3);
      lcd.printf("R%4d %4d %4d %4d", EEPROM_read_int(silver_right_r), EEPROM_read_int(silver_right_g), EEPROM_read_int(silver_right_b), EEPROM_read_int(silver_right_c));
    } else if (page == 8)  // APDS Front
    {
      lcd.setCursor(0, 0);
      lcd.print("APDS Front: ");
      lcd.setCursor(0, 1);
      lcd.print("  RED  GRN  BLU ");

      lcd.setCursor(0, 2);
      lcd.printf(" %4d %4d %4d %4d", red, green, blue, clear);

      lcd.setCursor(12, 0);
      if (color_F == RED) {
        lcd.setCursor(12, 0);
        lcd.print("RED ");
        lcd.setCursor(0, 3);
        lcd.printf("M%4d %4d %4d %4d ", EEPROM_read_int(red_front_r), EEPROM_read_int(red_front_g), EEPROM_read_int(red_front_b), EEPROM_read_int(red_front_c));
      } else if (color_F == GREEN) {
        lcd.setCursor(12, 0);
        lcd.print("GRN ");
        lcd.setCursor(0, 3);
        lcd.printf("M%4d %4d %4d %4d ", EEPROM_read_int(green_front_r), EEPROM_read_int(green_front_g), EEPROM_read_int(green_front_b), EEPROM_read_int(green_front_c));
      } else if (color_F == WHITE) {
        lcd.setCursor(12, 0);
        lcd.print("WHT ");
        lcd.setCursor(0, 3);
        lcd.print("                    ");
      }
    }
  }
}

void menu(void) {
  static unsigned char page = 1, last_page = 6;
  int battery;
  lcd.clear();
  lcd.print("Error: check switch");

  lcd.setCursor(0, 1);
  lcd.printf("SBL=%d   SBR=%d", SBL, SBR);

  lcd.setCursor(0, 3);
  lcd.printf("p_p=%d next_p=%d Ent=%d", previuse_page, next_page, start);

  if (start == 0 || next_page == 0 || previuse_page == 0 || SBL == 0 || SBR == 0)
    beep(10);
  lcd.clear();
  while (1) {
    if (next_page == 0) {
      while (next_page == 0)
        ;
      delay(50);
      page++;
      if (page > last_page)
        page = 1;
      lcd.clear();
    }
    if (previuse_page == 0) {
      while (previuse_page == 0)
        ;
      delay(50);
      page--;
      if (page < 1)
        page = last_page;
      lcd.clear();
    }
    if (page <= 4) {
      lcd.setCursor(2, 0);
      lcd.print("Start ");
      lcd.setCursor(2, 1);
      lcd.print("Test Sensor   ");
      lcd.setCursor(2, 2);
      lcd.print("Setup         ");
      lcd.setCursor(2, 3);
      lcd.print("Test Color    ");
      lcd.setCursor(0, page - 1);
      lcd.print("> ");
    } else if (page > 4) {
      lcd.setCursor(2, 0);
      lcd.print("Test Motor   ");
      lcd.setCursor(2, 1);
      lcd.print("color calib ");
      lcd.setCursor(0, page - 5);
      lcd.print("> ");
    }

    if (page == 1)  // start
    {
      if (start == 0) {
        while (start == 0)
          ;
        lcd.clear();

        lcd.print("Rescue Team");
        beep(1);
        break;
      }
      battery = analogRead(A7);
      battery = (battery * 5 / 102.3) * 3.1;
      lcd.setCursor(8, 0);
      lcd.printf("bat=%3d ", battery);

      if (battery < 105) {
        LED_on;
        delay(50);
        LED_off;
        delay(50);
      }
    } else if (page == 2)  // Test Sensor
    {
      if (start == 0) {
        while (start == 0)
          ;
        menu_sensor();
      }
    } else if (page == 3)  // Setup
    {
      if (start == 0) {
        while (start == 0)
          ;
        menu_setup();
      }
    } else if (page == 4)  // Test Color
    {
      if (start == 0) {
        lcd.clear();
        while (start == 0)
          ;
        menu_color();
      }
    } else if (page == 5)  // Test Motor
    {
      if (start == 0) {
        while (start == 0)
          ;
        menu_motor();
      }
    } else if (page == 6)  // color calibration
    {
      if (start == 0) {
        lcd.clear();
        while (start == 0)
          ;
        delay(200);
        color_calib();
      }
    }
  }
}

void robot_setup() {
  TCCR1A = 0;  // Clear the register
  // Set the Timer/Counter 1 Mode to "Normal" mode
  TCCR1A |= (0 << WGM10) | (0 << WGM11);
  TCCR1B |= (0 << WGM12) | (0 << WGM13);
  // Set the Timer/Counter 1 clock source to "External Crystal Oscillator"
  TCCR1B |= (1 << CS12) | (0 << CS11) | (0 << CS10);
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(6, INPUT_PULLUP);
  pinMode(35, OUTPUT);
  pinMode(37, INPUT_PULLUP);  // sbl
  pinMode(38, INPUT_PULLUP);  // sbr
  pinMode(start_pin, INPUT_PULLUP);
  pinMode(next_page_pin, INPUT_PULLUP);
  pinMode(previuse_page_pin, INPUT_PULLUP);
  pinMode(increase_pin, INPUT_PULLUP);
  pinMode(decrease_pin, INPUT_PULLUP);
  pinMode(MUX_A, OUTPUT);
  pinMode(MUX_B, OUTPUT);
  pinMode(MUX_C, OUTPUT);

  Wire.begin();
  Serial.begin(115200);
  dxl_init(115200);
  lcd.begin(20, 4);
  delay(800);
}
void get_back(void) {
  int T90 = EEPROM_read_int(T90_address);

  while (!(intersectionL && intersectionR) && color_L == WHITE && color_R == WHITE) {
    linefollow();
  }
  if (direction == Left) {
    move(forward, T90 / 3, 150);
    move(Left, T90 / 1.3, 150);
    move(forward, T90 / 3, 150);
  } else if (direction == Right) {
    move(forward, T90 / 3, 150);
    move(Right, T90 / 1.3, 150);
    move(forward, T90 / 3, 150);
  }
  go(60, 60);
}
void wlift() {
  int T90 = EEPROM_read_int(T90_address);
  int gripper_close = EEPROM_read_int(gripper_close_address);
  int gripper_open = EEPROM_read_int(gripper_open_address);
  int inter_cnt = 0;  //intersection counting
  delay(50);
  move_arm(800, 400);
  delay(500);
  go(80, 80);
  while (1) {
    lcd.clear();
    lcd.print(inter_cnt);
    linefollow();
    if (intersectionL && intersectionR) {
      if (inter_cnt == 0) {
        go(50, 50);
        while (intersectionL && intersectionR)
          ;
        inter_cnt += 1;
      } else if (inter_cnt == 1) {
        go(0, 0);
        inter_cnt = 2;
      } else if (inter_cnt == 3) {
        inter_cnt += 1;
      }
    }
    if (inter_cnt == 2) {
      move(Back, T90 / 2, 100);
      move_arm(345, 500);
      delay(300);  //arm_normal
      move(forward, T90 / 5, 50);
      beep(3);
      lcd.print(inter_cnt);
      lcd.clear();
      lcd.print("picking up");
      move_arm(780, 200);  //PICKUP
      delay(1500);
      move(forward, T90 / 2, 100);
      inter_cnt += 1;
    }
    if (inter_cnt >= 4) {
      go(0, 0);
      move(Back, T90 / 13, 60);
      lcd.clear();
      lcd.print("putting down");
      move_arm(345, 200);  //Dropping the weight
      delay(3000);
      move(Back, T90 * 1.5, 100);
      move(Left, T90 * 2, 150);
      get_back();
      break;
    }
  }
}

int cmps(int select) {
  int degree, pi, rol;

  digitalWrite(MUX_A, HIGH);  //switching the multiplaxer
  digitalWrite(MUX_B, HIGH);
  digitalWrite(MUX_C, LOW);

  Wire.beginTransmission(cmps_address);
  Wire.write(0x02);  // Register address for desired data (adjust as needed)
  Wire.endTransmission();

  Wire.requestFrom(cmps_address, 4);  // Request 4 bytes of data

  if (Wire.available() >= 4) {
    degree = Wire.read();
    degree = (degree << 8) | Wire.read();
    degree /= 10;  // Adjust scaling if needed
    degree -= DN;  // Replace DN with your offset value (if applicable)

    pi = Wire.read();
    pi = pi * 180 / 255;

    rol = Wire.read();
    rol = rol * 180 / 255;
  }

  if (degree < 0) {
    degree += 360;
  }


  if (select == 1) {
    return degree;
  } else if (select == 2) {
    return pi;
  } else {
    return rol;
  }
}

void turnto(int degd) {
  int speed, degdif;
  unsigned int T = 0;
  speed = 80;
  lcd.clear();
  while (T < 5) {
    degdif = deg - degd;  // diffrence
    if (degdif <= -180)
      degdif += 360;
    if (degdif >= 180)
      degdif -= 360;
    lcd.setCursor(0, 0);
    lcd.printf("turning=%3d degree", degdif);
    if (degdif >= 80 || degdif <= -80)
      speed = 120;
    else if ((degdif < 80 && degdif >= 45) || (degdif > -80 && degdif <= -45))
      speed = 100;
    else if ((degdif < 45 && degdif >= 15) || (degdif > -45 && degdif <= -15)) {
      speed = 80;
    } else if ((degdif < 15 && degdif >= 0) || (degdif > -15 && degdif <= 0)) {
      speed = 60;
    }

    if ((degdif <= -3 && degdif > -180) || (degdif < 360 && degdif > 180) || (degdif < 720 && degdif > 540)) {
      go(speed, speed * -1);  // turn right
      T = 0;
    } else if ((degdif >= 3 && degdif < 180) || (degdif > 360 && degdif < 540) || (degdif > -360 && degdif < -180)) {
      go(speed * -1, speed);  // turn left
      T = 0;
    } else break;
    T++;
  }
  go(0, 0);
}

unsigned int vl_double_check(char xv) {
  unsigned int vl_dis = 1;

  // Your pin manipulation logic here if needed

  // Select the appropriate sensor
  if (xv == 1) {
    // Set MUX pins to select sensor 1
    // B11 Right
    digitalWrite(MUX_A, LOW);
    digitalWrite(MUX_B, HIGH);
    digitalWrite(MUX_C, LOW);
  } else if (xv == 2) {
    // Set MUX pins to select sensor 2
    // B13 Left
    digitalWrite(MUX_A, LOW);
    digitalWrite(MUX_B, LOW);
    digitalWrite(MUX_C, HIGH);
  } else if (xv == 3) {
    // Set MUX pins to select sensor 2
    // B13 Left
    digitalWrite(MUX_A, HIGH);
    digitalWrite(MUX_B, HIGH);
    digitalWrite(MUX_C, LOW);
  }
  // Send command to start distance measurement
  Wire.beginTransmission(VL53L0X_ADDRESS);
  Wire.write(VL53L0X_REG_SYSRANGE_START);
  Wire.write(0x01);
  Wire.endTransmission();

  // Delay for measurement completion
  delay(10);  // Adjust delay if needed

  // Request distance measurement
  Wire.beginTransmission(VL53L0X_ADDRESS);
  Wire.write(VL53L0X_REG_RESULT_RANGE_VAL);
  Wire.endTransmission(false);

  // Read distance measurement (2 bytes)
  Wire.requestFrom(VL53L0X_ADDRESS, 2);
  if (Wire.available() >= 2) {
    byte distance_msb = Wire.read();
    byte distance_lsb = Wire.read();
    vl_dis = ((unsigned int)distance_msb << 8) | distance_lsb;
  }

  // Your additional processing logic here

  return vl_dis;
}
unsigned int vl(char xv) {
  unsigned int vl_dis = 1;

  // Your pin manipulation logic here if needed

  // Select the appropriate sensor
  if (xv == 1) {
    // Set MUX pins to select sensor 1
    // B11 Right
    digitalWrite(MUX_A, LOW);
    digitalWrite(MUX_B, HIGH);
    digitalWrite(MUX_C, LOW);
  } else if (xv == 2) {
    // Set MUX pins to select sensor 2
    // B13 Left
    digitalWrite(MUX_A, LOW);
    digitalWrite(MUX_B, LOW);
    digitalWrite(MUX_C, HIGH);
  } else if (xv == 3) {
    // Set MUX pins to select sensor 2
    // B13 Left
    digitalWrite(MUX_A, HIGH);
    digitalWrite(MUX_B, HIGH);
    digitalWrite(MUX_C, LOW);
  }
  // Send command to start distance measurement
  Wire.beginTransmission(VL53L0X_ADDRESS);
  Wire.write(VL53L0X_REG_SYSRANGE_START);
  Wire.write(0x01);
  Wire.endTransmission();

  // Delay for measurement completion
  delay(10);  // Adjust delay if needed

  // Request distance measurement
  Wire.beginTransmission(VL53L0X_ADDRESS);
  Wire.write(VL53L0X_REG_RESULT_RANGE_VAL);
  Wire.endTransmission(false);

  // Read distance measurement (2 bytes)
  Wire.requestFrom(VL53L0X_ADDRESS, 2);
  if (Wire.available() >= 2) {
    byte distance_msb = Wire.read();
    byte distance_lsb = Wire.read();
    vl_dis = ((unsigned int)distance_msb << 8) | distance_lsb;
  }

  // Your additional processing logic here
  if (vl_dis == 20) {
    delay(10);
    return vl_double_check(xv);
  } else return vl_dis;
}
void football() {
  int T90 = EEPROM_read_int(T90_address);
  int arm_dropping = EEPROM_read_int(arm_dropping_address);
  int arm_normal = EEPROM_read_int(arm_normal_address);
  while (1) {
    linefollow();
    if (intersectionL && intersectionR) {
      go(0, 0);
      move(Back, T90 / 8, 100);
      beep(3);
      
        move(Right, T90 / 6, 100);
        move(forward, T90 / 4, 60);
        move_arm(550, 1000);
        delay(1000);
        move_arm(100, 500);
        delay(1000);
        move(Back, T90 / 6, 100);
        move(Left, T90 * 2, 150);
        go(60, 60);
        break;
      
    }
  }

  get_back();
}
void track(int round, int direction) {
  int track_rounds = 0;
  int track_direction = Left;  //clockwise is right ccw is left
  int inter_cnt = 0;           //intersection counting
  int T90 = EEPROM_read_int(T90_address);
  track_rounds = round;
  track_direction = direction;
  while (1) {
    linefollow();
    if (intersectionL && intersectionR) {
      move(forward, T90 / 4, 100);
      if (direction == Right) {
        move(Right, T90, 100);
      } else {
        move(Left, T90, 100);
      }
      move(forward, T90 / 6, 100);

      go(60, 60);
      while (inter_cnt < track_rounds) {
        linefollow();
        if (intersectionL || intersectionR) {
          while (intersectionL && intersectionR)
            ;
          move(forward, T90 / 3, 100);
          inter_cnt += 1;
          lcd.clear();
          lcd.print(inter_cnt);
        }
      }
      move(Back, T90 / 3, 100);
      move(Left, T90 * 2, 100);
      go(60, 60);
      inter_cnt = 0;
      direction = Left;
      while (inter_cnt < 1) {
        linefollow();
        if (intersectionL || intersectionR) {
          while (intersectionL && intersectionR)
            ;
          move(forward, T90 / 4, 100);
          inter_cnt += 1;
          lcd.clear();
          lcd.print(inter_cnt);
        }
      }
      move(forward, T90 / 6, 100);
      if (direction = Right) {
        move(Right, T90, 100);
      } else {
        move(Left, T90, 100);
      }
      move(forward, T90 / 2, 100);
      break;
    }
  }
  get_back();
}
void archery() {
  int arm_dropping = EEPROM_read_int(arm_dropping_address);
  int T90 = EEPROM_read_int(T90_address);
  while (!intersectionL && !intersectionR) {
    linefollow();
  }
  go(0, 0);
  beep(3);
  XL_Gripper(31, 100, 1000);
  delay(1);
  delay(2000);
  move(Back, T90 / 4, 120);
  move(Left, T90 * 2, 120);
  go(60, 60);
  get_back();
}
void obstacle() {
  int T90 = EEPROM_read_int(T90_address);
  int inter_cnt = 0;  //intersection counting
  while (!intersectionL && !intersectionR) {
    linefollow();
  }
  go(0, 0);
  inter_cnt = 1;
  beep(2);
  move(forward, T90 / 8, 100);

  while (1) {
    go(100, 100);
    if (intersectionL && intersectionR) {
      go(60, 60);
      while (intersectionL || intersectionR)
        ;
      move(forward, T90 / 4, 60);
      inter_cnt += 1;
    }
    if (inter_cnt == 3) {

      move(Back, T90 * 2.2, 150);
      move(Left, T90 * 1.9, 150);
      go(60, 60);
      break;
    }
    if (inter_cnt == 2) {
      move(forward, T90 / 3, 100);
      move(Back, T90 * 1.7, 150);
      move(Left, T90 * 1.9, 150);
      go(60, 60);
      break;
    }
  }
  get_back();
}
void move(int direction, int lenth, int speed = 180) {
  switch (direction) {
    case forward:
      cnt = 0;
      while (cnt / 100 < lenth) {
        go(speed, speed);
      }
      go(0, 0);
      break;
    case Left:
      cnt = 0;
      while (cnt / 100 < lenth) {
        go(-speed, speed);
      }
      go(0, 0);
      break;
    case Right:
      cnt = 0;
      while (cnt / 100 < lenth) {
        go(speed, -speed);
      }
      go(0, 0);
      break;
    case Back:
      cnt = 0;
      while (cnt / 100 < lenth) {
        go(-speed, -speed);
      }
      go(0, 0);
      break;
  }
}


void sensecolor() {
  int T90 = EEPROM_read_int(T90_address);
  int inter_detected = false;
  int deadend_detected = false;
  if (color_L == RED) {
    go(-250, 250);
    delay(2000);
    go(0, 0);
    delay(2000);
  }
  if (color_R == RED) {
    go(-250, 250);
    delay(2000);
    go(0, 0);
    delay(2000);
  }
}
/*
void sensecolor(){
  int T90 = EEPROM_read_int(T90_address);
  int inter_detected = false;
  int deadend_detected = false;
  if(color_L==RED){
    go(-250,250); delay(2000);
    go(0,0); delay(2000);
  }
  if(color_R==RED){
    go(-250,250); delay(2000);
    go(0,0); delay(2000);
  }
}
*/
void color_detection() {
  int T90 = EEPROM_read_int(T90_address);
  int inter_detected = false;
  int deadend_detected = false;
  left_card = color_L;
  right_card = color_R;
  if (left_card != WHITE) {
    if (left_card == GREEN) {
        go(0, 0);
        beep(1);
      if (color_L == GREEN) {
        lcd.clear();
        lcd.print("Football");
        move(forward,T90/5,100);
        move(Left,T90,150);
        football();
      }
    }
    if (left_card == SILVER) {
      go(0, 0);
      if (color_L == SILVER) {
        lcd.clear();
        lcd.print("Obstacle");
        move(forward,T90/5,100);
        move(Left,T90,150);
        obstacle();
      }
    }
    if (left_card == BLUE) {
      go(0, 0);
      if (color_L == BLUE) {
        lcd.clear();
        lcd.print("weight lift");
        move(forward,T90/5,100);
        move(Left,T90,150);
        wlift();
      }
    }
    if (left_card == RED) {
      go(0, 0);
      if (color_L == RED) {
        lcd.clear();
        lcd.print("Trck");
        move(forward,T90/5,100);
        move(Left,T90,150);
        track(4,Left);
      }
    }
    if (left_card == YELLOW) {
      go(0, 0);
      if (color_L == YELLOW) {
        lcd.clear();
        lcd.print("archery");
        move(forward,T90/5,100);
        move(Left,T90,150);
        archery();
      }
    }
  }
  else if (right_card != WHITE) {
    if (right_card == GREEN) {
        go(0, 0);
        beep(1);
      if (color_R == GREEN) {
        lcd.clear();
        lcd.print("Football");
        move(forward,T90/5,100);
        move(Left,T90,150);
        football();
      }
    }
    if (right_card == SILVER) {
      go(0, 0);
      if (color_R == SILVER) {
        lcd.clear();
        lcd.print("Obstacle");
        move(forward,T90/5,100);
        move(Left,T90,150);
        obstacle();
      }
    }
    if (right_card == BLUE) {
      go(0, 0);
      if (color_R == BLUE) {
        lcd.clear();
        lcd.print("weight lift");
        move(forward,T90/5,100);
        move(Left,T90,150);
        wlift();
      }
    }
    if (right_card == RED) {
      go(0, 0);
      if (color_R == RED) {
        lcd.clear();
        lcd.print("Trck");
        move(forward,T90/5,100);
        move(Left,T90,150);
        track(4,Left);
      }
    }
    if (right_card == YELLOW) {
      go(0, 0);
      if (color_R == YELLOW) {
        lcd.clear();
        lcd.print("archery");
        move(forward,T90/5,100);
        move(Left,T90,150);
        archery();
      }
    }
  }
}
int ultrasonic() {
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(pingPin, LOW);
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
  return microsecondsToMillimeters(duration);
  delay(25);
}
void avoid_obstacle(int obs_direction) {
  int SLS = SL1 + SL2 + SL3;
  int SRS = SR1 + SR2 + SR3;
  int i = 0, time = 0, x = 0;
  int T90 = EEPROM_read_int(T90_address);
  go(0, 0);
  while (1) {
    delay(15);
    if (Front_distance <= 110)
      go(-30, -30);
    else if (Front_distance >= 140 && Front_distance < 160)
      go(30, 30);
    else if (Front_distance > 110 && Front_distance < 140) {
      go(0, 0);
      delay(100);
      break;
    }
    delay(5);
    if (time++ > 400 || Front_distance > 160) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("break");
      break;
    }
    lcd.setCursor(0, 0);
    lcd.printf("Front_distance=%3d  time=%3d  ", Front_distance, time);
  }

  if (Front_distance < 145) {
    if (obs_direction == Right)  // Right
    {
      go(100, -100);
      while (Front_distance < 150)
        ;
      move(Right, 60, 100);
      move(forward, 30, 100);
      cnt = 0;
      i = 0;
      while (!SL5 && !SL4) {
        i++;
        if (i >= 500) break;
        if (VL_Left < 140 && VL_Left > 80)
          go(60 * 1.8, 250);
        else
          go(60, 250);
      }
      move(forward, T90 / 5, 100);
      move(Right, T90 * 0.7, 100);
      x = 0;
      i = 0;
      go(50, 50);
      delay(50);
    }

    else  // Left
    {
      go(-100, 100);
      while (Front_distance < 150)
        ;
      move(Left, 60, 100);
      move(forward, 30, 100);
      cnt = 0;
      i = 0;
      while (!SR5 && !SR4) {
        i++;
        if (i >= 500) break;
        if (VL_Right < 140 && VL_Right > 80)
          go(250, 60 * 1.8);
        else
          go(250, 60);
      }
      move(forward, T90 / 5, 100);
      move(Left, T90 * 0.7, 100);
      x = 0;
      i = 0;
      go(50, 50);
      delay(50);
    }
  } else go(spd, spd);
}

void move_basket(int pos, int speed) {
  AX(10, pos, speed);
}

void move_gripper(int pos, int speed) {
  XL_Gripper(30, pos, speed);
  delay(1);
  XL_Gripper(31, 1023 - pos + xl_error, speed);
}
void rotation_motor(int pos) {
  if (pos == 0) AX(20, 90, 400);
  else if (pos == 1) AX(20, 400, 400);
  else if (pos == 2) AX(20, 715, 400);
  else if (pos == 3) AX(20, 1022, 400);
}
int rotate(int type) {
  int i;
  //#asm("cli")
  for (i = 0; i <= 3; i++) {
    if (barband[i] == type) {
      rotation_motor(i);
      //#asm("sei")
      return i;
    }
  }
  //#asm("sei")
  return 10;
}

void victim(void) {
  int uuu;
  int spd = EEPROM_read_int(spd_address);
  if (fifth == 1 && ball == 0) {
    move_arm(arm_down, 400);
    move_gripper(gripper_open, 800);
    fifth = 0;
  } else if (fifth == 0 && ball == 1) {
    //delay(30);
    lcd.clear();
    lcd.print("masdoom");
    //delay(80);
    move_gripper(gripper_close, 1000);
    if (ball == 1) victim_checked = 1;
    else victim_checked = 0;
    if (ball == 1) {
      if (rotate(0) != 10) {
        delay(5);
        rotate(0);
        delay(150);
        go(-100, -100);
        delay(500);
        move_arm(arm_dropping, 600);
        delay(800);
        go(0, 0);
        delay(200);
        if (victim_checked == 1) {
          if (con == 0) {
            farz = conductive;
            lcd.print("conductive");
          } else {
            farz = inconductive;
          }
          move_gripper(gripper_open, 800);
          delay(900);
          if (obs == 1) {
            if (farz == conductive) {
              barband[rotate(0)] = 1;
              delay(500);
              s_ball++;
              ball_num++;
              delay(50);
            } else {
              barband[rotate(0)] = 2;
              delay(500);
              b_ball++;
              ball_num++;
              delay(50);
            }
          }
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.printf(" s=%d   b=%d  ", s_ball, b_ball);
          lcd.setCursor(0, 1);
          lcd.printf(" 1=%d 2=%d  3=%d  4=%d ", barband[0], barband[1], barband[2], barband[3]);
          move_arm(arm_down, 400);
          delay(700);
          if (VSR10 <= silver_voltage_R || VSL10 <= silver_voltage_L || SM) {
            move(Back, 75, 100);
            if (redroom_dir == Right) {
              pich_sakoo = 0;
              if (VL_Right > 165) {
                move(Right, T90, 100);
              } else {
                move(Left, T90, 100);
              }

              //if((ev_ball>0 && ball_num>=1)||(ball_num>=2));
              //else redroom_dir=Left;
            } else {
              pich_sakoo = 0;
              if (VL_Left > 170) {
                move(Left, T90, 100);
              } else {
                move(Right, T90, 100);
              }
              //if((ev_ball>0 && ball_num>=1)||(ball_num>=2));
              // else redroom_dir=Right;
            }
          }
        } else {
          move_arm(arm_down, 400);
          move_gripper(gripper_open, 500);
          delay(200);
        }

      } else if (rotate(0) == 10) {
        //delay(150);
        ball_num++;
        fifth = 1;
        if (con == 0) {
          s_ball++;
        } else {
          b_ball++;
        }
      }
      go(spd, spd);
      get_out();  //exit after picking up
    } else {
      move_arm(arm_down, 400);
      move_gripper(gripper_open, 500);
      delay(200);
    }
    correct = 0;
    both_touched = 0;
  }
}
void silver(void) {
  if (VSR10 <= silver_voltage_R || VSL10 <= silver_voltage_L || SM) {
    move(Back, 75, 100);
    if (redroom_dir == Right) {
      pich_sakoo = 0;
      if (VL_Right > 165) {
        move(Right, T90, 100);
      } else {
        move(Left, T90, 100);
      }

      //if((ev_ball>0 && ball_num>=1)||(ball_num>=2));
      //else redroom_dir=Left;
    } else {
      pich_sakoo = 0;
      if (VL_Left > 170) {
        move(Left, T90, 100);
      } else {
        move(Right, T90, 100);
      }
      //if((ev_ball>0 && ball_num>=1)||(ball_num>=2));
      // else redroom_dir=Right;
    }
  }
}
void come_down(void) {
  int T90 = EEPROM_read_int(T90_address);
  if (SM + SL1 + SL2 + SR1 + SR2 + SL3 + SL4 + SR4 + SL5 + SR6 + SL7 + SR7 > 6) {
    move_arm(arm_normal, 500);
    delay(400);
    move(Back, 50, 100);
    if (VL_Left < 150 && VL_Left != 20) move(Right, T90 / 2.5, 100);
    else if (VL_Right < 150 && VL_Right != 20) move(Left, T90 / 2.5, 100);
    move(Back, 30, 100);
    move_arm(arm_down, 500);
  }
}
void correction(char direction) {
  int T90 = EEPROM_read_int(T90_address);
  int t = 0, m = 0, l_touch = 0, r_touch = 0, dance = 0;
  char obs_check_time = 0;
  while (1) {
    t++;
    if (t > 2000) {
      correct = 0;
      both_touched = 0;
      break;
    }
    delay(1);
    victim();
    come_down();
    if (direction == forward) {
      if (SFL && SFR) {
        obs_check_time = 0;
        correct = 1;
        both_touched = 1;
        go(0, 0);
        break;
      }

      else if (SFL == 0 && SFR == 0) {
        go(250, 250);
        both_touched = 0;
        correct = 0;
        if (obs) {
          its_not_obs = 0;
          break;
        }
      } else if (SFL == 0 && SFR == 1) {

        t++;
        lcd.clear();
        lcd.print("correct L");
        go(255, -120);
        both_touched = 0;
        correct = 1;
        its_not_obs = 1;
        if (t > 3000)

        {

          move(Back, 40);
          move(Left, T90 * 2);
          //move(forward,35);move(Right,T90);
          t = 0;
        }
      }

      else if (SFL == 1 && SFR == 0) {

        t++;
        lcd.clear();
        lcd.print("correct R");

        go(-120, 255);
        both_touched = 0;
        correct = 1;
        its_not_obs = 1;
        if (t > 3000) {

          move(Back, 40);
          move(Right, T90 * 2);
          //move(forward,35);move(Left,T90);
          t = 0;
        }
      } else both_touched = 0;
      silver();
    } else if (direction == Back) {
      if (VSR10 <= silver_voltage_R || VSL10 <= silver_voltage_L) {
        go(spd, spd);
        delay(250);
        break;
      }
      if (t > 3500) break;
      if (SBL && SBR) {
        go(0, 0);
        break;
      } else if (SBL == 0 && SBR == 0) {
        go(-500, -500);
        if (VSR10 <= silver_voltage_R || VSL10 <= silver_voltage_L) {
          go(spd, spd);
          delay(250);
          break;
        }
      }

      else if (SBL == 0 && SBR == 1)
        go(-500, 50);

      else if (SBL == 1 && SBR == 0)
        go(50, -500);

    }

    else if (direction == sides) {
      if (VL_Right <= 100 && VL_Right != 20)  //change
      {

        if (VL_Right <= 100 && VL_Right != 20)  //try 100change(120)
        {
          while (dance < 3) {  //try 3 or 2change
            go(-250, -250);
            delay(100);
            go(-250, 250);
            delay(200);
            go(250, 250);
            delay(100);
            go(250, -250);
            delay(200);
            dance++;
          }
          dance = 0;
          side_check = 1;
        }
      } else if (VL_Left <= 100 && VL_Left != 20)  //try 100change(120)
      {
        if (VL_Left <= 100 && VL_Left != 20)  //change
        {
          while (dance < 3) {  //try3or2change
            go(-250, -250);
            delay(100);
            go(250, -250);
            delay(200);
            go(250, 250);
            delay(100);
            go(-250, 250);
            delay(200);
            dance++;
          }
          dance = 0;
          side_check = 1;
        }
      } else {
        side_check = 0;
      }

      break;
    }
  }
}
void superteam() {
  int T90 = EEPROM_read_int(T90_address);
  int touch_time = 0;
  int spd = EEPROM_read_int(spd_address);
  go(0, 0);
  while (!SFL && !SFR)
    ;
  touch_count++;
  while (touch_time < 1000) {
    touch_time++;
    delay(10);
    if (SFL || SFR) {
      while (SFL || SFR)
        ;
      touch_count++;
      delay(500);
    }
  }
  if (touch_count > 3) touch_count = 3;
  move(forward, T90 * 2);  //change
  go(spd, spd);
  move_arm(arm_dropping, 300);
  while (!SFL && !SFR) {
    linefollow();
    handle_color();
    delay(15);
  }
  delay(250);  //change
  go(0, 0);
  move_basket(basket_up, 500);
  delay(800);
  move_basket(basket_normal, 350);
  delay(300);

  while (1)
    ;
}
void get_out(void) {
  int T90 = EEPROM_read_int(T90_address);
  int spd = EEPROM_read_int(spd_address);
  int arm_normal = EEPROM_read_int(arm_normal_address);
  int ev_s_ball = EEPROM_read_int(DW_address);
  int dance = 0;
  int i = 0, time = 0, x = 0;
  lcd.clear();
  lcd.print("exit");
  //ev_ball=1;x_ball=0;//temporary

  //move(Back,100);
  //move(Left,T90);
  while (1) {
    go(spd, spd);
    i++;
    if (SFL || SFR) {


      if (i < 150)  //250?300?
      {
        correction(forward);
        delay(10);
        move(Back, 50);
        move(Left, T90 * 0.9, 250);  //T90/2?

      } else {
        correction(forward);
        //go(-30,0);
        //delay(100);
        //move(Back,30);
        //go(0,-30);
        //delay(100)
        delay(10);
        move(Back, 80);  //60?40?
        move(Left, T90 * 0.8, 250);
        i = 0;
      }



    } else if (VSR10 <= silver_voltage_R || VSL10 <= silver_voltage_L) {
      move(Back, 50);
      move(Left, T90);
      move(forward, 100);
    }

    else if (SM || SR1 || SL1 || SR2) {
      move(Back, T90 * 1.5);  //change
      superteam();
      //if(obs){move(Back,50);move(Right,T90/2);}
      /*
            else{
              move(Back,80);
              go(-250,-250);delay(100);
              go(-250,250);delay(200);
              go(250,250);delay(100);
              go(250,-250);delay(200);
              
            }
            if(VL_Right<160){
              if(VL_Right<160 && VL_Right!=20)
              move(Left,T90/2);
              move(forward,T90/2.5);
              move(Right,T90/1.2);
            }
            move_arm(arm_normal,500);
            move(forward,T90,100);
                go(50,50);
                delay(50);
            */


    } else if (obs) {
      move(Back, 50);
      move(Right, T90 / 2);
    }
  }
}
void check_while(void) {
  int save_ENC, x;
  int basket_up = EEPROM_read_int(basket_up_address);
  int basket_normal = EEPROM_read_int(basket_normal_address);
  int arm_normal = EEPROM_read_int(arm_normal_address);
  int arm_down = EEPROM_read_int(arm_down_address);
  int arm_dropping = EEPROM_read_int(arm_dropping_address);
  int gripper_close = EEPROM_read_int(gripper_close_address);
  int gripper_open = EEPROM_read_int(gripper_open_address);
  int T90 = EEPROM_read_int(T90_address);
  int spd = EEPROM_read_int(spd_address);
  int ev_s_ball = EEPROM_read_int(DW_address);
  check_while_finished = 0;
  lcd.clear();
  lcd.print("check while");

  cnt = 0;
  go(100, 100);
  while (cnt / 100 <= 85)  //80change
  {
    if (ball == 1 && fifth == 0) {
      save_ENC = cnt / 100;
      victim();
      go(spd, spd);
      move(forward, T90 / 1.5);
      cnt = save_ENC;
    }
    if (obs) {
      move(Back, 25, 100);

      check_while_finished = 0;
      break;
    } else if (SFL == 1 || SFR == 1) {
      correction(forward);
      go(0, 0);
      lcd.setCursor(0, 1);
      lcd.printf("dis= %5d   ", VL_Front);
      delay(150);
      if (correct == 1) {
        if (VL_Front > 102 && VL_Front != 500)  //ev_point
        {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.printf("dis=%4d;sb:%d;evs:%d", VL_Front, s_ball, ev_s_ball);
          lcd.setCursor(0, 1);
          lcd.printf("bb=%d;evb:%d;bn:%d", b_ball, ev_b_ball, ball_num);
          lcd.setCursor(0, 2);
          lcd.printf("clr=%4d;1:%d;2:%d;3:%d;4:%d", color_F, barband[0], barband[1], barband[2], barband[3]);
          if ((VL_Front > 102) && color_F == GREEN && s_ball > 0) {
            while (1) {
              if (fifth == 1) {
                if (conductive == 1) {
                  ev_s_ball++;
                  s_ball--;
                  EEPROM_write_int(DW_address, ev_s_ball);
                  ball_num--;
                  move(Back, 30);
                  move_arm(500, 600);
                  delay(300);
                  move(forward, 50);
                  move_gripper(gripper_open, 700);
                  delay(500);
                  move(Back, 70);
                  go(0, 0);
                  move_arm(arm_down, 500);
                  delay(200);
                  correction(forward);
                  go(0, 0);
                  fifth = 0;
                }
              }
              if (rotate(1) != 10) {
                delay(50);
                ev_s_ball++;
                EEPROM_write_int(DW_address, ev_s_ball);
                s_ball--;
                ball_num--;
                barband[rotate(1)] = 0;
                delay(700);
                move_basket(basket_up, 500);
                delay(800);
                move_basket(basket_normal, 350);
                delay(300);
              } else break;
            }
            ev_ball = ev_s_ball + ev_b_ball;

            move(Back, 25);
            if (first_touched == Left) {
              move(Right, T90);
              redroom_dir = Right;
            } else {
              move(Left, T90); /*pich_sakoo=1; */
              redroom_dir = Left;
            }
            no_side = 1;
          } else if ((VL_Front > 102) && color_F == RED && b_ball > 0 && ev_s_ball > 1) {
            while (1) {
              if (fifth == 1) {
                if (conductive == 0) {

                  ev_b_ball++;
                  b_ball--;
                  ball_num--;
                  move(Back, 25);
                  move_arm(500, 600);
                  delay(300);
                  move(forward, 30);
                  move_gripper(gripper_open, 600);
                  delay(500);
                  move(Back, 60);
                  go(0, 0);
                  move_arm(arm_down, 500);
                  delay(200);
                  correction(forward);
                  go(0, 0);
                  fifth = 0;
                }
              }
              if (rotate(2) != 10) {
                delay(50);
                ev_b_ball++;
                b_ball--;
                ball_num--;
                barband[rotate(2)] = 0;
                delay(700);
                move_basket(basket_up, 500);
                delay(800);
                move_basket(basket_normal, 350);
                delay(300);
              } else break;
            }
            ev_ball = ev_s_ball + ev_b_ball;
            move(Back, 25);
            if (first_touched == Left) {
              move(Right, T90);
              redroom_dir = Right;
            } else {
              move(Left, T90); /*pich_sakoo=1; */
              redroom_dir = Left;
            }
            no_side = 1;
          } else {
            if (ball_num > 0 || s_ball > 0 || b_ball > 0) {
              delay(20);
              if ((VL_Front > 102) && color_F == GREEN && s_ball > 0) {
                while (1) {
                  if (fifth == 1) {
                    if (conductive == 1) {
                      ev_s_ball++;
                      s_ball--;
                      EEPROM_write_int(DW_address, ev_s_ball);
                      ball_num--;
                      move(Back, 30);
                      move_arm(500, 600);
                      delay(300);
                      move(forward, 50);
                      move_gripper(gripper_open, 700);
                      delay(500);
                      move(Back, 70);
                      go(0, 0);
                      move_arm(arm_down, 500);
                      delay(200);
                      correction(forward);
                      go(0, 0);
                      fifth = 0;
                    }
                  }
                  if (rotate(1) != 10) {
                    delay(50);
                    ev_s_ball++;
                    EEPROM_write_int(DW_address, ev_s_ball);
                    s_ball--;
                    ball_num--;
                    barband[rotate(1)] = 0;
                    delay(700);
                    move_basket(basket_up, 500);
                    delay(800);
                    move_basket(basket_normal, 350);
                    delay(300);
                  } else break;
                }
                ev_ball = ev_s_ball + ev_b_ball;
                move(Back, 25);
                if (first_touched == Left) {
                  move(Right, T90);
                  redroom_dir = Right;
                } else {
                  move(Left, T90); /*pich_sakoo=1; */
                  redroom_dir = Left;
                }
                no_side = 1;
              } else if ((VL_Front > 102) && color_F == RED && b_ball > 0 && ev_s_ball > 1) {
                while (1) {
                  if (fifth == 1) {
                    if (conductive == 0) {

                      ev_b_ball++;
                      b_ball--;
                      ball_num--;
                      move(Back, 25);
                      move_arm(500, 600);
                      delay(300);
                      move(forward, 30);
                      move_gripper(gripper_open, 600);
                      delay(500);
                      move(Back, 60);
                      go(0, 0);
                      move_arm(arm_down, 500);
                      delay(200);
                      correction(forward);
                      go(0, 0);

                      fifth = 0;
                    }
                  }
                  if (rotate(2) != 10) {
                    delay(50);
                    ev_b_ball++;
                    b_ball--;
                    ball_num--;
                    barband[rotate(2)] = 0;
                    delay(700);
                    move_basket(basket_up, 500);
                    delay(800);
                    move_basket(basket_normal, 350);
                    delay(300);
                  } else break;
                }
                ev_ball = ev_s_ball + ev_b_ball;
                move(Back, 25);
                if (first_touched == Left) {
                  move(Right, T90);
                  redroom_dir = Right;
                } else {
                  move(Left, T90); /*pich_sakoo=1; */
                  redroom_dir = Left;
                }
                no_side = 1;
              } else {
                move(Back, 25);
                if (first_touched == Left) {
                  move(Right, T90);
                  redroom_dir = Right;
                } else {
                  move(Left, T90); /*pich_sakoo=1; */
                  redroom_dir = Left;
                }
              }
            }

            else {
              move(Back, 25);
              if (first_touched == Left) {
                move(Right, T90);
                redroom_dir = Right;
              } else {
                move(Left, T90); /*pich_sakoo=1; */
                redroom_dir = Left;
              }
            }
          }

        } else  //wall
        {
          lcd.clear();
          lcd.print("wall 3");
          check_while_finished = 1;
          correction(sides);
          move(Back, 25);
          if (redroom_dir == Right) {
            move(Right, T90);
            move(Back, 10);  //redroom_dir=left;
            go(-spd, spd);
            delay(210);
            go(0, 0);
            //correction(back);
            delay(100);

          } else if (redroom_dir == Left) {
            move(Left, T90);
            move(Back, 10);  //redroom_dir=right;
            go(spd, -spd);
            delay(210);
            go(0, 0);
            delay(100);

            //correction(back);
          }
        }

      } else {
        lcd.clear();
        lcd.print("wall 4");
        check_while_finished = 1;
        correction(sides);
        move(Back, 25);
        if (redroom_dir == Right) {
          move(Right, T90);
          move(Back, 10);  //redroom_dir=left;
          go(-spd, spd);
          delay(210);
          go(0, 0);
          //correction(back);
          delay(100);

        } else if (redroom_dir == Left) {
          move(Left, T90);
          move(Back, 10);  //redroom_dir=right;
          go(spd, -spd);
          delay(210);
          go(0, 0);
          delay(100);

          //correction(back);
        }
      }

      break;
    }
    if (VSR10 <= silver_voltage_R || VSL10 <= silver_voltage_L || SM) {
      move(Back, 75);
      if (redroom_dir == Right) {
        if (VL_Right > 170) move(Right, T90 * 2);
        else {
          move(Left, T90 * 2);
          redroom_dir = Left;
        }
      } else if (redroom_dir == Left) {
        if (VL_Left > 170) move(Left, T90 * 2);
        else {
          move(Right, T90 * 2);
          redroom_dir = Right;
        }
      }
      check_while_finished = 1;
      break;
    } else check_while_finished = 0;
  }
}
void contact(void) {
  int near_wall_right, near_wall_left, i = 0;
  int basket_up = EEPROM_read_int(basket_up_address);
  int basket_normal = EEPROM_read_int(basket_normal_address);
  int arm_normal = EEPROM_read_int(arm_normal_address);
  int arm_down = EEPROM_read_int(arm_down_address);
  int arm_dropping = EEPROM_read_int(arm_dropping_address);
  int gripper_close = EEPROM_read_int(gripper_close_address);
  int gripper_open = EEPROM_read_int(gripper_open_address);
  int T90 = EEPROM_read_int(T90_address);
  int ev_s_ball = EEPROM_read_int(DW_address);
  lcd.clear();
  lcd.print("contact");
  if (obs)  //if obstacle is being seen
  {
    lcd.clear();
    lcd.print("OBS");
    victim();
    if (SFL == 0 && SFR == 0) {
      move(Back, 30);
      correction(sides);
      if (redroom_dir == Right) {

        move(Right, T90, spd);
        go(spd, spd);
        if (ev_ball >= 2 && b_ball >= 1)  //(s_ball>=2|| b_ball>=2 || fifth==1)change
        {
          if (VL_Left < 135 && VL_Left != 20) {
            go(100, 100);
            i = 0;
            while (VL_Left < 135 && i < 200) {
              i++;
              delay(3);
              victim();
              if (VSR10 <= silver_voltage_R || VSL10 <= silver_voltage_L || SM) {
                move(Back, 75);
                break;
              }
              if (SFL || SFR) break;
            }
            if (SFL == 1 || SFR == 1) {
              go(spd, spd);
              check_while();
              move(Left, T90);
            } else {
              move(Back, 20);
              move(Left, T90 * 2);
            }
          } else {
            go(150, 150);
            cnt = 0;
            i = 0;
            while (cnt / 100 <= 40 && i < 200) {
              i++;
              delay(3);
              victim();
              if (VSR10 <= silver_voltage_R || VSL10 <= silver_voltage_L || SM) {
                move(Back, 75);
                break;
              }
              if (SFL || SFR) break;
            }
            if (SFL == 1 || SFR == 1) {
              go(spd, spd);
              check_while();
              move(Left, T90 * 0.85);
            } else {
              move(Back, 25);
              move(Left, T90 * 2);
            }
          }
        } else {
          check_while();
          if (check_while_finished == 0) {
            move(Right, T90, spd);
            redroom_dir = Left;
          }
        }

      } else if (redroom_dir == Left) {
        move(Left, T90, spd);
        go(spd, spd);
        if (ev_ball >= 2 && b_ball >= 1)  //(s_ball>=2|| b_ball>=2 || fifth==1)change
        {
          if (VL_Right < 135 && VL_Right != 20) {
            go(100, 100);
            i = 0;
            while (VL_Right < 135 && i < 200) {
              i++;
              delay(3);
              victim();
              if (VSR10 <= silver_voltage_R || VSL10 <= silver_voltage_L || SM) {
                move(Back, 75);
                break;
              }
              if (SFL || SFR) break;
            }
            if (SFL == 1 || SFR == 1) {
              go(spd, spd);
              check_while();
              move(Right, T90);
            } else {
              move(Back, 20);
              move(Right, T90 * 2);
            }
          } else {
            go(150, 150);
            cnt = 0;
            i = 0;
            while (cnt / 100 <= 40 && i < 200) {
              i++;
              delay(3);
              victim();
              if (VSR10 <= silver_voltage_R || VSL10 <= silver_voltage_L || SM) {
                move(Back, 75);
                break;
              }
              if (SFL || SFR) break;
            }
            if (SFL == 1 || SFR == 1) {
              go(spd, spd);
              check_while();
              move(Right, T90 * 0.85);
            } else {
              move(Back, 25);
              move(Right, T90 * 2);
            }
          }
        } else {
          check_while();
          if (check_while_finished == 0) {
            move(Left, T90, spd);
            redroom_dir = Right;
          }
        }
      }
    }
    redroom_time = 0;
  } else if (SFL || SFR)  //if bumpers pressed
  {
    if (SFL) first_touched = Left;
    else if (SFR) first_touched = Right;
    correction(forward);
    if (correct == 1)  // ev-point and wall
    {
      //correction(sides);
      //if(side_check==1){correction(forward);} //temp
      go(0, 0);
      delay(100);
      if (VL_Front > 102 && VL_Front != 500)  //ev_point
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.printf("dis=%4d;sb:%d;evs:%d", VL_Front, s_ball, ev_s_ball);
        lcd.setCursor(0, 1);
        lcd.printf("bb=%d;evb:%d;bn:%d", b_ball, ev_b_ball, ball_num);
        lcd.setCursor(0, 2);
        lcd.printf("clr=%4d;1:%d;2:%d;3:%d;4:%d", color_F, barband[0], barband[1], barband[2], barband[3]);
        if ((VL_Front > 102) && color_F == GREEN && s_ball > 0) {
          while (1) {
            if (fifth == 1) {
              if (conductive == 1) {
                ev_s_ball++;
                s_ball--;
                EEPROM_write_int(DW_address, ev_s_ball);
                ball_num--;
                move(Back, 30);
                move_arm(500, 600);
                delay(300);
                move(forward, 50);
                move_gripper(gripper_open, 700);
                delay(500);
                move(Back, 70);
                go(0, 0);
                move_arm(arm_down, 500);
                delay(200);
                correction(forward);
                go(0, 0);
                fifth = 0;
              }
            }
            if (rotate(1) != 10) {
              delay(50);
              ev_s_ball++;
              EEPROM_write_int(DW_address, ev_s_ball);
              s_ball--;
              ball_num--;
              barband[rotate(1)] = 0;
              delay(700);
              move_basket(basket_up, 500);
              delay(800);
              move_basket(basket_normal, 350);
              delay(300);
            } else break;
          }
          ev_ball = ev_s_ball + ev_b_ball;
          move(Back, 25);
          if (first_touched == Left) {
            move(Right, T90 * 1.55);
            redroom_dir = Right;
          }  //change0
          else {
            move(Left, T90 * 1.55); /*pich_sakoo=1; */
            redroom_dir = Left;
          }
          no_side = 1;  //change0
        } else if ((VL_Front > 102) && color_F == RED && b_ball > 0 && ev_s_ball > 1) {
          while (1) {
            if (fifth == 1) {
              if (conductive == 0) {
                ev_b_ball++;
                b_ball--;
                ball_num--;
                move(Back, 25);
                move_arm(500, 600);
                delay(300);
                move(forward, 30);
                move_gripper(gripper_open, 600);
                delay(500);
                move(Back, 60);
                go(0, 0);
                move_arm(arm_down, 500);
                delay(200);
                correction(forward);
                go(0, 0);
                fifth = 0;
              }
            }
            if (rotate(2) != 10) {
              delay(50);
              ev_b_ball++;
              b_ball--;
              ball_num--;
              barband[rotate(2)] = 0;
              delay(700);
              move_basket(basket_up, 500);
              delay(800);
              move_basket(basket_normal, 350);
              delay(300);
            } else break;
          }
          ev_ball = ev_s_ball + ev_b_ball;
          move(Back, 25);
          if (first_touched == Left) {
            move(Right, T90 * 1.55);
            redroom_dir = Right;
          }  //change0
          else {
            move(Left, T90 * 1.55); /*pich_sakoo=1; */
            redroom_dir = Left;
          }
          no_side = 1;  //change0
        } else {
          if (ball_num > 0 || s_ball > 0 || b_ball > 0) {
            delay(20);
            if ((VL_Front > 102) && color_F == GREEN && s_ball > 0) {
              while (1) {
                if (fifth == 1) {
                  if (conductive == 1) {
                    ev_s_ball++;
                    s_ball--;
                    EEPROM_write_int(DW_address, ev_s_ball);
                    ball_num--;
                    move(Back, 30);
                    move_arm(500, 600);
                    delay(300);
                    move(forward, 50);
                    move_gripper(gripper_open, 700);
                    delay(500);
                    move(Back, 70);
                    go(0, 0);
                    move_arm(arm_down, 500);
                    delay(200);
                    correction(forward);
                    go(0, 0);
                    fifth = 0;
                  }
                }
                if (rotate(1) != 10) {
                  delay(50);
                  ev_s_ball++;
                  EEPROM_write_int(DW_address, ev_s_ball);
                  s_ball--;
                  ball_num--;
                  barband[rotate(1)] = 0;
                  delay(700);
                  move_basket(basket_up, 500);
                  delay(800);
                  move_basket(basket_normal, 350);
                  delay(300);
                } else break;
              }
              ev_ball = ev_s_ball + ev_b_ball;
              move(Back, 25);
              if (first_touched == Left) {
                move(Right, T90 * 1.55);
                redroom_dir = Right;
              } else {
                move(Left, T90 * 1.55); /*pich_sakoo=1; */
                redroom_dir = Left;
              }
              no_side = 1;
            } else if ((VL_Front > 102) && color_F == RED && b_ball > 0 && ev_s_ball > 1) {
              while (1) {
                if (fifth == 1) {
                  if (conductive == 0) {

                    ev_b_ball++;
                    b_ball--;
                    ball_num--;
                    move(Back, 25);
                    move_arm(500, 600);
                    delay(300);
                    move(forward, 30);
                    move_gripper(gripper_open, 600);
                    delay(500);
                    move(Back, 60);
                    go(0, 0);
                    move_arm(arm_down, 500);
                    delay(200);
                    correction(forward);
                    go(0, 0);
                  }
                  fifth = 0;
                }
                if (rotate(2) != 10) {
                  delay(50);
                  ev_b_ball++;
                  b_ball--;
                  ball_num--;
                  barband[rotate(2)] = 0;
                  delay(700);
                  move_basket(basket_up, 500);
                  delay(800);
                  move_basket(basket_normal, 350);
                  delay(300);
                } else break;
              }
              ev_ball = ev_s_ball + ev_b_ball;
              move(Back, 25);
              if (first_touched == Left) {
                move(Right, T90);
                redroom_dir = Right;
              } else {
                move(Left, T90); /*pich_sakoo=1; */
                redroom_dir = Left;
              }
              no_side = 1;
            } else {
              move(Back, 25);
              if (first_touched == Left) {
                move(Right, T90);
                redroom_dir = Right;
              } else {
                move(Left, T90); /*pich_sakoo=1; */
                redroom_dir = Left;
              }
            }

          } else {
            move(Back, 25);
            if (first_touched == Left) {
              move(Right, T90);
              redroom_dir = Right;
            } else {
              move(Left, T90); /*pich_sakoo=1; */
              redroom_dir = Left;
            }
          }
        }
        get_out();
      } else  //wall
      {
        lcd.clear();
        lcd.print("wall 1");
        move(Back, 50);
        if (redroom_dir == Right) {
          if (ev_ball >= 2 && b_ball >= 1)  //(s_ball>=2 || b_ball>=2)change
          {
            move(Right, T90 * 0.9);
          } else {
            if (VL_Right <= 120 && VL_Right != 20) {
              redroom_dir = Left;
              correction(sides);
              move(Back, 15);
              move(Left, T90);
            } else {
              move(Right, T90);
            }
            go(spd, spd);
            check_while();
            if (check_while_finished == 0) {
              if (redroom_dir == Left) {
                move(Left, T90);
                redroom_dir = Right;
              } else {
                move(Right, T90);
                redroom_dir = Left;
              }
            }
          }
        } else if (redroom_dir == Left) {
          if (ev_ball >= 2 && b_ball >= 1)  //(s_ball>=2 || b_ball>=2)change
          {
            move(Left, T90 * 0.9);
          } else {
            if (VL_Left <= 120 && VL_Left != 20) {
              redroom_dir = Right;
              correction(sides);
              move(Back, 15);
              move(Right, T90);
            } else {
              move(Left, T90);
            }
            go(spd, spd);
            check_while();
            if (check_while_finished == 0) {
              if (redroom_dir == Right) {
                move(Right, T90);
                redroom_dir = Left;
              } else {
                move(Left, T90);
                redroom_dir = Right;
              }
            }
          }
        }
        check_while_finished = 0;
      }

    } else if (!its_not_obs)  //obstacle
    {
      victim();
      if (SFL == 0 && SFR == 0) {
        move(Back, 30);
        if (redroom_dir == Right) {
          move(Right, T90, spd);
          go(spd, spd);
          if (ev_ball >= 2 && b_ball >= 1)  //(s_ball>=2|| b_ball>=2 || fifth==1)change
          {
            if (VL_Left < 135 && VL_Left != 20) {
              go(100, 100);
              i = 0;
              while (VL_Left < 135 && i < 200) {
                i++;
                delay(3);
                victim();
                if (VSR10 <= silver_voltage_R || VSL10 <= silver_voltage_L || SM) {
                  move(Back, 75);
                  break;
                }
                if (SFL || SFR) break;
              }
              if (SFL == 1 || SFR == 1) {
                go(spd, spd);
                check_while();
                move(Left, T90);
              } else {
                move(Back, 20);
                move(Left, T90 * 2);
              }
            } else {
              go(150, 150);
              cnt = 0;
              i = 0;
              while (cnt / 100 <= 40 && i < 200) {
                i++;
                delay(3);
                victim();
                if (VSR10 <= silver_voltage_R || VSL10 <= silver_voltage_L || SM) {
                  move(Back, 75);
                  break;
                }
                if (SFL || SFR) break;
              }
              if (SFL == 1 || SFR == 1) {
                go(spd, spd);
                check_while();
                move(Left, T90 * 0.85);
              } else {
                move(Back, 25);
                move(Left, T90 * 2);
              }
            }
          } else {
            check_while();
            if (check_while_finished == 0) {
              move(Right, T90, spd);
              redroom_dir = Left;
            }
          }

        } else if (redroom_dir == Left) {
          move(Left, T90, spd);
          go(spd, spd);
          if (ev_ball >= 2 && b_ball >= 1)  //(s_ball>=2|| b_ball>=2 || fifth==1)change
          {
            if (VL_Right < 135 && VL_Right != 20) {
              go(100, 100);
              i = 0;
              while (VL_Right < 135 && i < 200) {
                i++;
                delay(3);
                victim();
                if (VSR10 <= silver_voltage_R || VSL10 <= silver_voltage_L || SM) {
                  move(Back, 75);
                  break;
                }
                if (SFL || SFR) break;
              }
              if (SFL == 1 || SFR == 1) {
                go(spd, spd);
                check_while();
                move(Right, T90);
              } else {
                move(Back, 20);
                move(Right, T90 * 2);
              }
            } else {
              go(150, 150);
              cnt = 0;
              i = 0;
              while (cnt / 100 <= 40 && i < 200) {
                i++;
                delay(3);
                victim();
                if (VSR10 <= silver_voltage_R || VSL10 <= silver_voltage_L || SM) {
                  move(Back, 75);
                  break;
                }
                if (SFL || SFR) break;
              }
              if (SFL == 1 || SFR == 1) {
                go(spd, spd);
                check_while();
                move(Right, T90 * 0.85);
              } else {
                move(Back, 25);
                move(Right, T90 * 2);
              }
            }
          } else {
            check_while();
            if (check_while_finished == 0) {
              move(Left, T90, spd);
              redroom_dir = Right;
            }
          }
        }
      }
      redroom_time = 0;

    } else  //wall
    {
      lcd.clear();
      lcd.print("wall 2");
      //if(side_check==1){correction(forward);}
      move(Back, 50);
      if (redroom_dir == Right) {
        if (ev_ball >= 2 && b_ball >= 1)  //(s_ball>=2 || b_ball>=2)
        {
          move(Right, T90 * 0.9);
        } else {
          if (VL_Right <= 120 && VL_Right != 20) {
            redroom_dir = Left;
            correction(sides);
            move(Back, 15);
            move(Left, T90);
          } else {
            move(Right, T90);
          }
          go(spd, spd);
          check_while();
          if (check_while_finished == 0) {
            if (redroom_dir == Left) {
              move(Left, T90);
              redroom_dir = Right;
            } else {
              move(Right, T90);
              redroom_dir = Left;
            }
          }
        }

      } else if (redroom_dir == Left) {
        if (ev_ball >= 2 && b_ball >= 1)  //(s_ball>=2 || b_ball>=2)change
        {
          move(Left, T90 * 0.9);
        } else {
          if (VL_Left <= 120 && VL_Left != 20) {
            redroom_dir = Right;
            correction(sides);
            move(Back, 15);
            move(Right, T90);
          } else {
            move(Left, T90);
          }
          go(spd, spd);
          check_while();
          if (check_while_finished == 0) {
            if (redroom_dir == Right) {
              move(Right, T90);
              redroom_dir = Left;
            } else {
              move(Left, T90);
              redroom_dir = Right;
            }
          }
        }
      }
      check_while_finished = 0;
    }
    redroom_time = 0;
  }
}
void ev_zone(void) {
  ball_num = 0;
  move(Back, 25, 50);
  move_basket(basket_normal, 400);
  move_arm(arm_down, 400);
  delay(500);
  rotate(0);
  move(forward, 55, 100);
  delay(200);
  //if(VL_Right<VL_Left && VL_Right!=20 && VL_Left!=20)redroom_dir=Left;
  //else
  redroom_dir = Right;
  if (VSR10 <= 0.3 || VSL10 <= 0.3) move(forward, 20, 100);
  while (1) {
    lcd.setCursor(0, 1);
    lcd.printf("dis= %5d   ", VL_Front);
    go(spd, spd);
    victim();
    if (SFL || SFR || obs) { contact(); }
    silver();
    redroom_time++;
    come_down();
  }
}
