#include <SparkFunMPU9250-DMP.h>
#include <Wire.h>

#ifdef defined(SAMD)
 #define SerialPort SerialUSB
#else
  #define SerialPort Serial
#endif

MPU9250_DMP imu0, imu1, imu2, imu3, imu4, imu5, imu6, imu7, imu8, imu9, imu10, imu11, imu12, imu13;

float yaw0, yaw1, yaw2, yaw3, yaw4, yaw5, yaw6, yaw7, yaw8, yaw9, yaw10, yaw11, yaw12, yaw13, 
      pitch0, pitch1, pitch2, pitch3, pitch4, pitch5, pitch6, pitch7, pitch8, pitch9, pitch10, pitch11, pitch12, pitch13, 
      roll0, roll1, roll2, roll3, roll4, roll5, roll6, roll7, roll8, roll9, roll10, roll11, roll12, roll13;

float dt = 0.01;

double compAngleX0, compAngleX1, compAngleX2, compAngleX3, compAngleX4, compAngleX5, compAngleX6, compAngleX7, compAngleX8, compAngleX9, compAngleX10, compAngleX11, compAngleX12, compAngleX13,
       compAngleY0, compAngleY1, compAngleY2, compAngleY3, compAngleY4, compAngleY5, compAngleY6, compAngleY7, compAngleY8, compAngleY9, compAngleY10, compAngleY11, compAngleY12, compAngleY13,
       compAngleZ0, compAngleZ1, compAngleZ2, compAngleZ3, compAngleZ4, compAngleZ5, compAngleZ6, compAngleZ7, compAngleZ8, compAngleZ9, compAngleZ10, compAngleZ11, compAngleZ12, compAngleZ13,
       gyroXrate0, gyroXrate1, gyroXrate2, gyroXrate3, gyroXrate4, gyroXrate5, gyroXrate6, gyroXrate7, gyroXrate8, gyroXrate9, gyroXrate10, gyroXrate11, gyroXrate12, gyroXrate13,
       gyroYrate0, gyroYrate1, gyroYrate2, gyroYrate3, gyroYrate4, gyroYrate5, gyroYrate6, gyroYrate7, gyroYrate8, gyroYrate9, gyroYrate10, gyroYrate11, gyroYrate12, gyroYrate13,
       gyroZrate0, gyroZrate1, gyroZrate2, gyroZrate3, gyroZrate4, gyroZrate5, gyroZrate6, gyroZrate7, gyroZrate8, gyroZrate9, gyroZrate10, gyroZrate11, gyroZrate12, gyroZrate13;
       

       

void TCA0(uint8_t bus)
{
  if (bus > 7) return;
  Wire.beginTransmission(0x71);
  Wire.write(0);  // no channel selected
  Wire.endTransmission();
  Wire.beginTransmission(0x70);  // TCA0 address is 0x70
  Wire.write(1 << bus);          // send byte to select bus
  Wire.endTransmission();
}

void TCA1(uint8_t bus)
{
  if (bus > 7) return;
  Wire.beginTransmission(0x70);
  Wire.write(0);  // no channel selected
  Wire.endTransmission();
  Wire.beginTransmission(0x71);  // TCA1 address is 0x71
  Wire.write(1 << bus);          // send byte to select bus
  Wire.endTransmission();
}

void setup() 
{
  SerialPort.begin(115200);
  Wire.begin();
  Wire.setClock(400000);
  initSensor();
  Serial.println("CLEARDATA");
  Serial.println("LABEL,R1X,R1Y,R1Z,R2X,R2Y,R2Z,R3X,R3Y,R3Z,R4X,R4Y,R4Z,R5X,R5Y,R5Z,R6X,R6Y,R6Z,R7X,R7Y,R7Z,L1X,L1Y,L1Z,L2X,L2Y,L2Z,L3X,L3Y,L3Z,L4X,L4Y,L4Z,L5X,L5Y,L5Z,L6X,L6Y,L6Z,L7X,L7Y,L7Z");
}

void loop() 
{
  TCA0(7);
  if ( imu0.fifoAvailable() )
  {
    if ( imu0.dmpUpdateFifo() == INV_SUCCESS)
    {
      imu0.computeEulerAngles();
      float GX0 = imu0.calcGyro(imu0.gx);
      float GY0 = imu0.calcGyro(imu0.gy);
      float GZ0 = imu0.calcGyro(imu0.gz);
      gyroXrate0 = imu0.gx/131;
      gyroYrate0 = imu0.gy/131;
      gyroZrate0 = imu0.gz/131;
      roll0 = imu0.roll;
      pitch0 = imu0.pitch;
      yaw0 = imu0.yaw;
      compAngleX0 = 0.9*(compAngleX0+gyroXrate0*dt)+0.1*roll0;
      compAngleY0 = 0.9*(compAngleY0+gyroYrate0*dt)+0.1*pitch0;
      compAngleZ0 = 0.9*(compAngleZ0+gyroZrate0*dt)+0.1*yaw0;
      SerialPort.print("DATA,");
      SerialPort.print(String(compAngleX0) + "," + String(compAngleY0) + "," + String(compAngleZ0) + ",");
      imu0.resetFifo();
    }
  }
  TCA0(6);
  if ( imu1.fifoAvailable() )
  {
    if ( imu1.dmpUpdateFifo() == INV_SUCCESS)
    {
      imu1.computeEulerAngles();
      //float GX1 = imu1.calcGyro(imu1.gx);
      //float GY1 = imu1.calcGyro(imu1.gy);
      //float GZ1 = imu1.calcGyro(imu1.gz);
      gyroXrate1 = imu1.gx/131;
      gyroYrate1 = imu1.gy/131;
      gyroZrate1 = imu1.gz/131;
      roll1 = imu1.roll;
      pitch1 = imu1.pitch;
      yaw1 = imu1.yaw;
      compAngleX1 = 0.9*(compAngleX1+gyroXrate1*dt)+0.1*roll1;
      compAngleY1 = 0.9*(compAngleY1+gyroYrate1*dt)+0.1*pitch1;
      compAngleZ1 = 0.9*(compAngleZ1+gyroZrate1*dt)+0.01*yaw1;
      SerialPort.print(String(compAngleX1) + "," + String(compAngleY1) + "," + String(compAngleZ1) + ",");
      imu1.resetFifo();
    }
  }
  TCA0(5);
  if ( imu2.fifoAvailable() )
  {
    if ( imu2.dmpUpdateFifo() == INV_SUCCESS)
    {
      imu2.computeEulerAngles();
      float GX2 = imu2.calcGyro(imu2.gx);
      float GY2 = imu2.calcGyro(imu2.gy);
      float GZ2 = imu2.calcGyro(imu2.gz);
      gyroXrate2 = imu2.gx/131;
      gyroYrate2 = imu2.gy/131;
      gyroZrate2 = imu2.gz/131;
      roll2 = imu2.roll;
      pitch2 = imu2.pitch;
      yaw2 = imu2.yaw;
      compAngleX2 = 0.9*(compAngleX2+gyroXrate2*dt)+0.1*roll2;
      compAngleY2 = 0.9*(compAngleY2+gyroYrate2*dt)+0.1*pitch2;
      compAngleZ2 = 0.9*(compAngleZ2+gyroZrate2*dt)+0.1*yaw2;
       SerialPort.print(String(compAngleX2) + "," + String(compAngleY2) + "," + String(compAngleZ2) + ",");
      imu2.resetFifo();
    }
  }
  TCA0(4);
  if ( imu3.fifoAvailable() )
  {
    if ( imu3.dmpUpdateFifo() == INV_SUCCESS)
    {
      imu3.computeEulerAngles();
      float GX3 = imu3.calcGyro(imu3.gx);
      float GY3 = imu3.calcGyro(imu3.gy);
      float GZ3 = imu3.calcGyro(imu3.gz);
      gyroXrate3 = imu3.gx/131;
      gyroYrate3 = imu3.gy/131;
      gyroZrate3 = imu3.gz/131;
      roll3 = imu3.roll;
      pitch3 = imu3.pitch;
      yaw3 = imu3.yaw;
      compAngleX3 = 0.9*(compAngleX3+gyroXrate3*dt)+0.1*roll3;
      compAngleY3 = 0.9*(compAngleY3+gyroYrate3*dt)+0.1*pitch3;
      compAngleZ3 = 0.9*(compAngleZ3+gyroZrate3*dt)+0.1*yaw3;
      SerialPort.print(String(compAngleX3) + "," + String(compAngleY3) + "," + String(compAngleZ3) + ",");
      imu3.resetFifo();
    }
  }
  TCA0(3);
  if ( imu4.fifoAvailable() )
  {
    if ( imu4.dmpUpdateFifo() == INV_SUCCESS)
    {
      imu4.computeEulerAngles();
      float GX4 = imu4.calcGyro(imu4.gx);
      float GY4 = imu4.calcGyro(imu4.gy);
      float GZ4 = imu4.calcGyro(imu4.gz);
      gyroXrate4 = imu4.gx/131;
      gyroYrate4 = imu4.gy/131;
      gyroZrate4 = imu4.gz/131;
      roll4 = imu4.roll;
      pitch4 = imu4.pitch;
      yaw4 = imu4.yaw;
      compAngleX4 = 0.9*(compAngleX4+gyroXrate4*dt)+0.1*roll4;
      compAngleY4 = 0.9*(compAngleY4+gyroYrate4*dt)+0.1*pitch4;
      compAngleZ4 = 0.9*(compAngleZ4+gyroZrate4*dt)+0.1*yaw4;
      SerialPort.print(String(compAngleX4) + "," + String(compAngleY4) + "," + String(compAngleZ4) + ",");
      imu4.resetFifo();
    }
  }
  TCA0(2);
  if ( imu5.fifoAvailable() )
  {
    if ( imu5.dmpUpdateFifo() == INV_SUCCESS)
    {
      imu5.computeEulerAngles();
      float GX5 = imu5.calcGyro(imu5.gx);
      float GY5 = imu5.calcGyro(imu5.gy);
      float GZ5 = imu5.calcGyro(imu5.gz);
      gyroXrate5 = imu5.gx/131;
      gyroYrate5 = imu5.gy/131;
      gyroZrate5 = imu5.gz/131;
      roll5 = imu5.roll;
      pitch5 = imu5.pitch;
      yaw5 = imu5.yaw;
      compAngleX5 = 0.9*(compAngleX5+gyroXrate5*dt)+0.1*roll5;
      compAngleY5 = 0.9*(compAngleY5+gyroYrate5*dt)+0.1*pitch5;
      compAngleZ5 = 0.9*(compAngleZ5+gyroZrate5*dt)+0.1*yaw5;
      SerialPort.print(String(compAngleX5) + "," + String(compAngleY5) + "," + String(compAngleZ5) + ",");
      imu5.resetFifo();
    }
  }
  TCA0(1);
  if ( imu6.fifoAvailable() )
  {
    if ( imu6.dmpUpdateFifo() == INV_SUCCESS)
    {
      imu6.computeEulerAngles();
      float GX6 = imu6.calcGyro(imu6.gx);
      float GY6 = imu6.calcGyro(imu6.gy);
      float GZ6 = imu6.calcGyro(imu6.gz);
      gyroXrate6 = imu6.gx/131;
      gyroYrate6 = imu6.gy/131;
      gyroZrate6 = imu6.gz/131;
      roll6 = imu6.roll;
      pitch6 = imu6.pitch;
      yaw6 = imu6.yaw;
      compAngleX6 = 0.9*(compAngleX6+gyroXrate6*dt)+0.1*roll6;
      compAngleY6 = 0.9*(compAngleY6+gyroYrate6*dt)+0.1*pitch6;
      compAngleZ6 = 0.9*(compAngleZ6+gyroZrate6*dt)+0.1*yaw6;
      SerialPort.print(String(compAngleX6) + "," + String(compAngleY6) + "," + String(compAngleZ6) + ",");
      imu6.resetFifo();
    }
  }
  /////////////////////////////////////////////////////////////////////
  TCA1(2);
  if ( imu7.fifoAvailable() )
  {
    if ( imu7.dmpUpdateFifo() == INV_SUCCESS)
    {
      imu7.computeEulerAngles();
      float GX7 = imu7.calcGyro(imu7.gx);
      float GY7 = imu7.calcGyro(imu7.gy);
      float GZ7 = imu7.calcGyro(imu7.gz);
      gyroXrate7 = imu7.gx/131;
      gyroYrate7 = imu7.gy/131;
      gyroZrate7 = imu7.gz/131;
      roll7 = imu7.roll;
      pitch7 = imu7.pitch;
      yaw7 = imu7.yaw;
      compAngleX7 = 0.9*(compAngleX7+gyroXrate7*dt)+0.1*roll7;
      compAngleY7 = 0.9*(compAngleY7+gyroYrate7*dt)+0.1*pitch7;
      compAngleZ7 = 0.9*(compAngleZ7+gyroZrate7*dt)+0.1*yaw7;
      SerialPort.print(String(compAngleX7) + "," + String(compAngleY7) + "," + String(compAngleZ7) + ",");
      imu7.resetFifo();
    }
  }
  TCA1(3);
  if ( imu8.fifoAvailable() )
  {
    if ( imu8.dmpUpdateFifo() == INV_SUCCESS)
    {
      imu8.computeEulerAngles();
      float GX8 = imu8.calcGyro(imu8.gx);
      float GY8 = imu8.calcGyro(imu8.gy);
      float GZ8 = imu8.calcGyro(imu8.gz);
      gyroXrate8 = imu8.gx/131;
      gyroYrate8 = imu8.gy/131;
      gyroZrate8 = imu8.gz/131;
      roll8 = imu8.roll;
      pitch8 = imu8.pitch;
      yaw8 = imu8.yaw;
      compAngleX8 = 0.9*(compAngleX8+gyroXrate8*dt)+0.1*roll8;
      compAngleY8 = 0.9*(compAngleY8+gyroYrate8*dt)+0.1*pitch8;
      compAngleZ8 = 0.9*(compAngleZ8+gyroZrate8*dt)+0.18*yaw8;
      SerialPort.print(String(compAngleX8) + "," + String(compAngleY8) + "," + String(compAngleZ8) + ",");
      imu8.resetFifo();
    }
  }
  TCA1(4);
  if ( imu9.fifoAvailable() )
  {
    if ( imu9.dmpUpdateFifo() == INV_SUCCESS)
    {
      imu9.computeEulerAngles();
      float GX9 = imu9.calcGyro(imu9.gx);
      float GY9 = imu9.calcGyro(imu9.gy);
      float GZ9 = imu9.calcGyro(imu9.gz);
      gyroXrate9 = imu9.gx/131;
      gyroYrate9 = imu9.gy/131;
      gyroZrate9 = imu9.gz/131;
      roll9 = imu9.roll;
      pitch9 = imu9.pitch;
      yaw9 = imu9.yaw;
      compAngleX9 = 0.9*(compAngleX9+gyroXrate9*dt)+0.1*roll9;
      compAngleY9 = 0.9*(compAngleY9+gyroYrate9*dt)+0.1*pitch9;
      compAngleZ9 = 0.9*(compAngleZ9+gyroZrate9*dt)+0.1*yaw9;
      SerialPort.print(String(compAngleX9) + "," + String(compAngleY9) + "," + String(compAngleZ9) + ",");
      imu9.resetFifo();
    }
  }
  TCA1(5);
  if ( imu10.fifoAvailable() )
  {
    if ( imu10.dmpUpdateFifo() == INV_SUCCESS)
    {
      imu10.computeEulerAngles();
      float GX10 = imu10.calcGyro(imu10.gx);
      float GY10 = imu10.calcGyro(imu10.gy);
      float GZ10 = imu10.calcGyro(imu10.gz);
      gyroXrate10 = imu10.gx/131;
      gyroYrate10 = imu10.gy/131;
      gyroZrate10 = imu10.gz/131;
      roll10 = imu10.roll;
      pitch10 = imu10.pitch;
      yaw10 = imu10.yaw;
      compAngleX10 = 0.9*(compAngleX10+gyroXrate10*dt)+0.1*roll10;
      compAngleY10 = 0.9*(compAngleY10+gyroYrate10*dt)+0.1*pitch10;
      compAngleZ10 = 0.9*(compAngleZ10+gyroZrate10*dt)+0.1*yaw10;
      SerialPort.print(String(compAngleX10) + "," + String(compAngleY10) + "," + String(compAngleZ10) + ",");
      imu10.resetFifo();
    }
  }
  TCA1(6);
  if ( imu11.fifoAvailable() )
  {
    if ( imu11.dmpUpdateFifo() == INV_SUCCESS)
    {
      imu11.computeEulerAngles();
      float GX11 = imu11.calcGyro(imu11.gx);
      float GY11 = imu11.calcGyro(imu11.gy);
      float GZ11 = imu11.calcGyro(imu11.gz);
      gyroXrate11 = imu11.gx/131;
      gyroYrate11 = imu11.gy/131;
      gyroZrate11 = imu11.gz/131;
      roll11 = imu11.roll;
      pitch11 = imu11.pitch;
      yaw11 = imu11.yaw;
      compAngleX11 = 0.9*(compAngleX11+gyroXrate11*dt)+0.1*roll11;
      compAngleY11 = 0.9*(compAngleY11+gyroYrate11*dt)+0.1*pitch11;
      compAngleZ11 = 0.9*(compAngleZ11+gyroZrate11*dt)+0.1*yaw11;
      SerialPort.print(String(compAngleX11) + "," + String(compAngleY11) + "," + String(compAngleZ11) + ",");
      imu11.resetFifo();
    }
  }
  TCA1(7);
  if ( imu12.fifoAvailable() )
  {
    if ( imu12.dmpUpdateFifo() == INV_SUCCESS)
    {
      imu12.computeEulerAngles();
      float GX12 = imu12.calcGyro(imu12.gx);
      float GY12 = imu12.calcGyro(imu12.gy);
      float GZ12 = imu12.calcGyro(imu12.gz);
      gyroXrate12 = imu12.gx/131;
      gyroYrate12 = imu12.gy/131;
      gyroZrate12 = imu12.gz/131;
      roll12 = imu12.roll;
      pitch12 = imu12.pitch;
      yaw12 = imu12.yaw;
      compAngleX12 = 0.9*(compAngleX12+gyroXrate12*dt)+0.1*roll12;
      compAngleY12 = 0.9*(compAngleY12+gyroYrate12*dt)+0.1*pitch12;
      compAngleZ12 = 0.9*(compAngleZ12+gyroZrate12*dt)+0.1*yaw12;
      SerialPort.print(String(compAngleX12) + "," + String(compAngleY12) + "," + String(compAngleZ12) + ",");
      imu12.resetFifo();
    }
  }
  TCA1(1);
  if ( imu13.fifoAvailable() )
  {
    if ( imu13.dmpUpdateFifo() == INV_SUCCESS)
    {
      imu13.computeEulerAngles();
      float GX13 = imu13.calcGyro(imu13.gx);
      float GY13 = imu13.calcGyro(imu13.gy);
      float GZ13 = imu13.calcGyro(imu13.gz);
      gyroXrate13 = imu13.gx/131;
      gyroYrate13 = imu13.gy/131;
      gyroZrate13 = imu13.gz/131;
      roll13 = imu13.roll;
      pitch13 = imu13.pitch;
      yaw13 = imu13.yaw;
      compAngleX13 = 0.9*(compAngleX13+gyroXrate13*dt)+0.1*roll13;
      compAngleY13 = 0.9*(compAngleY13+gyroYrate13*dt)+0.1*pitch13;
      compAngleZ13 = 0.9*(compAngleZ13+gyroZrate13*dt)+0.1*yaw13;
      SerialPort.println(String(compAngleX13) + "," + String(compAngleY13) + "," + String(compAngleZ13));
      imu13.resetFifo();
    }
  }
}

void initSensor(){
  TCA0(7);
  if (imu0.begin() != INV_SUCCESS)
  {
    while (1)
    {
      SerialPort.println("MPU-R 1 Failed");
      delay(5000);
    }
  }
  imu0.dmpBegin(DMP_FEATURE_6X_LP_QUAT | DMP_FEATURE_GYRO_CAL, 10);
  TCA0(6);
  if (imu1.begin() != INV_SUCCESS)
  {
    while (1)
    {
      SerialPort.println("MPU-R 2 Failed");
      delay(5000);
    }
  }
  imu1.dmpBegin(DMP_FEATURE_6X_LP_QUAT | DMP_FEATURE_GYRO_CAL, 10);
  TCA0(5);
  if (imu2.begin() != INV_SUCCESS)
  {
    while (1)
    {
      SerialPort.println("MPU-R 3 Failed");
      delay(5000);
    }
  }
  imu2.dmpBegin(DMP_FEATURE_6X_LP_QUAT | DMP_FEATURE_GYRO_CAL, 10);
  TCA0(4);
  if (imu3.begin() != INV_SUCCESS)
  {
    while (1)
    {
      SerialPort.println("MPU-R 4 Failed");
      delay(5000);
    }
  }
  imu3.dmpBegin(DMP_FEATURE_6X_LP_QUAT | DMP_FEATURE_GYRO_CAL, 10);
  TCA0(3);
  if (imu4.begin() != INV_SUCCESS)
  {
    while (1)
    {
      SerialPort.println("MPU-R 5 Failed");
      delay(5000);
    }
  }
  imu4.dmpBegin(DMP_FEATURE_6X_LP_QUAT | DMP_FEATURE_GYRO_CAL, 10);
  TCA0(2);
  if (imu5.begin() != INV_SUCCESS)
  {
    while (1)
    {
      SerialPort.println("MPU-R 6 Failed");
      delay(5000);
    }
  }
  imu5.dmpBegin(DMP_FEATURE_6X_LP_QUAT | DMP_FEATURE_GYRO_CAL, 10);
  TCA0(1);
  if (imu6.begin() != INV_SUCCESS)
  {
    while (1)
    {
      SerialPort.println("MPU-R 7 Failed");
      delay(5000);
    }
  }
  imu6.dmpBegin(DMP_FEATURE_6X_LP_QUAT | DMP_FEATURE_GYRO_CAL, 10);
///////////////////////////////////////////////////////////////////////////////////////////////////////////
  TCA1(2);
  if (imu7.begin() != INV_SUCCESS)
  {
    while (1)
    {
      SerialPort.println("MPU-L 1 Failed");
      delay(5000);
    }
  }
  imu7.dmpBegin(DMP_FEATURE_6X_LP_QUAT | DMP_FEATURE_GYRO_CAL, 10);
  TCA1(3);
  if (imu8.begin() != INV_SUCCESS)
  {
    while (1)
    {
      SerialPort.println("MPU-L 2 Failed");
      delay(5000);
    }
  }
  imu8.dmpBegin(DMP_FEATURE_6X_LP_QUAT | DMP_FEATURE_GYRO_CAL, 10);
  TCA1(4);
  if (imu9.begin() != INV_SUCCESS)
  {
    while (1)
    {
      SerialPort.println("MPU-L 3 Failed");
      delay(5000);
    }
  }
  imu9.dmpBegin(DMP_FEATURE_6X_LP_QUAT | DMP_FEATURE_GYRO_CAL, 10);
  TCA1(5);
  if (imu10.begin() != INV_SUCCESS)
  {
    while (1)
    {
      SerialPort.println("MPU-L 4 Failed");
      delay(5000);
    }
  }
  imu10.dmpBegin(DMP_FEATURE_6X_LP_QUAT | DMP_FEATURE_GYRO_CAL, 10);
  TCA1(6);
  if (imu11.begin() != INV_SUCCESS)
  {
    while (1)
    {
      SerialPort.println("MPU-L 5 Failed");
      delay(5000);
    }
  }
  imu11.dmpBegin(DMP_FEATURE_6X_LP_QUAT | DMP_FEATURE_GYRO_CAL, 10);
  TCA1(7);
  if (imu12.begin() != INV_SUCCESS)
  {
    while (1)
    {
      SerialPort.println("MPU-L 6 Failed");
      delay(5000);
    }
  }
  imu12.dmpBegin(DMP_FEATURE_6X_LP_QUAT | DMP_FEATURE_GYRO_CAL, 10);
  TCA1(1);
  if (imu13.begin() != INV_SUCCESS)
  {
    while (1)
    {
      SerialPort.println("MPU-L 7 Failed");
      delay(5000);
    }
  }
  imu13.dmpBegin(DMP_FEATURE_6X_LP_QUAT | DMP_FEATURE_GYRO_CAL, 10);
}
