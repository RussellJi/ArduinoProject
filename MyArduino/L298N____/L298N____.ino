/*此示例必须与Blinker app联动，下载方式和更多相关资料请访问https://blinker.app/   */

//更多资料欢迎访问我们的官网 http://openjumper.cn/ 或联系邮箱 support@openjumper.com
//https://openjumper.taobao.com/ --OPENJUMPER官方店铺
//https://shop555818949.taobao.com/ --OPENJUMPER企业店铺
#define BLINKER_PRINT Serial
#define BLINKER_WIFI

#include <Blinker.h>

char auth[] = "460628c361a5";
char ssid[] = "mostfun";
char pswd[] = "18038083873";

#define IN4 D7
#define IN3 D6
#define IN1 D4
#define IN2 D5

#define tap_time 300
#define press_time 3000
#define press_time_zy 1000

unsigned long t = 0;
unsigned long timeout = 2000;

#define BUTTON_0 "btn-t"
#define BUTTON_1 "btn-s"
#define BUTTON_2 "btn-x"
#define BUTTON_3 "btn-z"
#define BUTTON_4 "btn-y"

#define Txt_1 "tex"

BlinkerText Text1(Txt_1);
BlinkerButton Button0(BUTTON_0);
BlinkerButton Button1(BUTTON_1);
BlinkerButton Button2(BUTTON_2);
BlinkerButton Button3(BUTTON_3);
BlinkerButton Button4(BUTTON_4);

void button0_callback(const String &state)
{
  t = millis();
  timeout = 2000;
  key_parse(0);
}

void button1_callback(const String &state)
{
  t = millis();
  if (state == BLINKER_CMD_BUTTON_TAP)
  {
    timeout = tap_time;
    key_parse(1);
  }
  else if (state == BLINKER_CMD_BUTTON_PRESSED)
  {
    timeout = press_time;
    key_parse(5);
  }
  else if (state == BLINKER_CMD_BUTTON_RELEASED)
    key_parse(0);
}
void button2_callback(const String &state)
{
  t = millis();
  if (state == BLINKER_CMD_BUTTON_TAP)
  {
    timeout = tap_time;
    key_parse(2);
  }
  else if (state == BLINKER_CMD_BUTTON_PRESSED)
  {
    timeout = press_time;
    key_parse(6);
  }
  else if (state == BLINKER_CMD_BUTTON_RELEASED)
    key_parse(0);
}
void button3_callback(const String &state)
{
  t = millis();
  if (state == BLINKER_CMD_BUTTON_TAP)
  {
    timeout = tap_time;
    key_parse(3);
  }
  else if (state == BLINKER_CMD_BUTTON_PRESSED)
  {
    timeout = press_time_zy;
    key_parse(7);
  }
  else if (state == BLINKER_CMD_BUTTON_RELEASED)
    key_parse(0);
}
void button4_callback(const String &state)
{
  t = millis();
  if (state == BLINKER_CMD_BUTTON_TAP)
  {
    timeout = tap_time;
    key_parse(4);
  }
  else if (state == BLINKER_CMD_BUTTON_PRESSED)
  {
    timeout = press_time_zy;
    key_parse(8);
  }
  else if (state == BLINKER_CMD_BUTTON_RELEASED)
    key_parse(0);
}

void key_parse(uint8_t car_mode)
{
  uint8_t L_PWM = 0;
  uint8_t R_PWM = 0;
  bool L_DIR = 0;
  bool R_DIR = 0;
  switch (car_mode)
  {
    case 1: //上tap
      L_PWM = 127;
      R_PWM = 127;
      L_DIR = 1;
      R_DIR = 1;
      break;
    case 2: //下
      L_PWM = 127;
      R_PWM = 127;
      L_DIR = 0;
      R_DIR = 0;
      break;
    case 3: //左
      L_PWM = 127;
      R_PWM = 127;
      L_DIR = 0;
      R_DIR = 1;
      break;
    case 4: //右
       L_PWM = 127;
      R_PWM = 127;
      L_DIR = 1;
      R_DIR = 0;
      break;

    case 5: //上press
      L_PWM = 127;
      R_PWM = 127;
      L_DIR = 1;
      R_DIR = 1;
      break;
    case 6: //下
      L_PWM = 127;
      R_PWM = 127;
      L_DIR = 0;
      R_DIR = 0;
      break;
    case 7: //左
      L_PWM = 127;
      R_PWM = 127;
      L_DIR = 0;
      R_DIR = 1;
      break;
    case 8: //右
      L_PWM = 127;
      R_PWM = 127;
      L_DIR = 1;
      R_DIR = 0;
      break;

      // case 9://左上press
      // break;
      // case 10://左下
      // break;
      // case 11://右上
      // break;
      // case 12://右下
      // break;
  }
  analogWrite(IN3, L_PWM);
  analogWrite(IN2, R_PWM);
  digitalWrite(IN4, L_DIR);
  digitalWrite(IN1, R_DIR);
  Text1.print("run time", t);
}

void blinker_car_init()
{
  pinMode(IN4, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN1, OUTPUT);
  analogWrite(IN3, 255);
  analogWrite(IN2, 255);
  digitalWrite(IN4, 1);
  digitalWrite(IN1, 1);
  //  pinMode(C_BAR_PIN, INPUT_PULLUP);
}
void blinker_car_control(uint8_t cl_pwm, bool cl_dir, uint8_t cr_pwm, bool cr_dir)
{
  digitalWrite(IN4, cl_dir);
  digitalWrite(IN1, cr_dir);
  analogWrite(IN3, cl_pwm);
  analogWrite(IN2, cr_pwm);
}
/*
  void blinker_car_detect()
  {
    if (!digitalRead(C_BAR_PIN)) {
        if (!isWarn) {
            Blinker.vibrate();
            isWarn = true;
            car_os_time = millis();
        }
        else if (millis() - car_os_time >= 5000) {
            isWarn = false;
        }
    }
    else {
        isWarn = false;
    }
  }
*/
void setup()
{
  analogWriteRange(255);
  blinker_car_init();

  Serial.begin(115200);
  BLINKER_DEBUG.stream(Serial);
  Blinker.begin(auth, ssid, pswd);
  Button0.attach(button0_callback);
  Button1.attach(button1_callback);
  Button2.attach(button2_callback);
  Button3.attach(button3_callback);
  Button4.attach(button4_callback);
}

void loop()
{
  Blinker.run();
  if ((millis() - t) > timeout)
  {
    t = millis();
    timeout = 2000;
    blinker_car_init();
    //Serial.println("timeout");
  }
  //   blinker_car_detect();
  /*#if defined(BLINKER_CAR_DEBUG)
    BLINKER_LOG4("L_PWM: ", L_PWM, "  | L_DIR: ", L_DIR);
    BLINKER_LOG4("R_PWM: ", R_PWM, "  | R_DIR: ", R_DIR);
    Blinker.delay(2000);
    #endif*/
}
