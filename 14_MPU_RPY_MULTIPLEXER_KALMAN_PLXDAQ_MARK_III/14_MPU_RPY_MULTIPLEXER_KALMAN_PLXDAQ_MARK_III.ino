#include <Wire.h>
#include <SparkFunMPU9250-DMP.h>
#include <SimpleKalmanFilter.h>

MPU9250_DMP imu0, imu1, imu2, imu3, imu4, imu5, imu6, imu7, imu8, imu9, imu10, imu11, imu12, imu13;

SimpleKalmanFilter KF00(0.003, 0.003, 0.01),  KF01(0.003, 0.003, 0.01),  KF02(0.003, 0.003, 0.01),  
                   KF10(0.003, 0.003, 0.01),  KF11(0.003, 0.003, 0.01),  KF12(0.003, 0.003, 0.01),  
                   KF20(0.003, 0.003, 0.01),  KF21(0.003, 0.003, 0.01),  KF22(0.003, 0.003, 0.01),  
                   KF30(0.003, 0.003, 0.01),  KF31(0.003, 0.003, 0.01),  KF32(0.003, 0.003, 0.01),  
                   KF40(0.003, 0.003, 0.01),  KF41(0.003, 0.003, 0.01),  KF42(0.003, 0.003, 0.01),  
                   KF50(0.003, 0.003, 0.01),  KF51(0.003, 0.003, 0.01),  KF52(0.003, 0.003, 0.01),  
                   KF60(0.003, 0.003, 0.01),  KF61(0.003, 0.003, 0.01),  KF62(0.003, 0.003, 0.01), 
                   KF70(0.003, 0.003, 0.01),  KF71(0.003, 0.003, 0.01),  KF72(0.003, 0.003, 0.01),  
                   KF80(0.003, 0.003, 0.01),  KF81(0.003, 0.003, 0.01),  KF82(0.003, 0.003, 0.01),  
                   KF90(0.003, 0.003, 0.01),  KF91(0.003, 0.003, 0.01),  KF92(0.003, 0.003, 0.01),  
                   KF100(0.003, 0.003, 0.01), KF101(0.003, 0.003, 0.01), KF102(0.003, 0.003, 0.01), 
                   KF110(0.003, 0.003, 0.01), KF111(0.003, 0.003, 0.01), KF112(0.003, 0.003, 0.01), 
                   KF120(0.003, 0.003, 0.01), KF121(0.003, 0.003, 0.01), KF122(0.003, 0.003, 0.01), 
                   KF130(0.003, 0.003, 0.01), KF131(0.003, 0.003, 0.01), KF132(0.003, 0.003, 0.01); 

float R00,  P00,  Y00,
      R01,  P01,  Y01,
      R02,  P02,  Y02,
      R03,  P03,  Y03,
      R04,  P04,  Y04,
      R05,  P05,  Y05,
      R06,  P06,  Y06,
      R07,  P07,  Y07,
      R08,  P08,  Y08,
      R09,  P09,  Y09,
      R10,  P10,  Y10,
      R11,  P11,  Y11,
      R12,  P12,  Y12,
      R13,  P13,  Y13;   

float KFR00,  KFP01,  KFY02,
      KFR10,  KFP11,  KFY12,  
      KFR20,  KFP21,  KFY22,  
      KFR30,  KFP31,  KFY32,  
      KFR40,  KFP41,  KFY42,  
      KFR50,  KFP51,  KFY52,  
      KFR60,  KFP61,  KFY62,  
      KFR70,  KFP71,  KFY72,  
      KFR80,  KFP81,  KFY82,  
      KFR90,  KFP91,  KFY92,  
      KFR100, KFP101, KFY102, 
      KFR110, KFP111, KFY112, 
      KFR120, KFP121, KFY122,
      KFR130, KFP131, KFY132;
      
#ifdef defined(SAMD)
 #define SerialPort SerialUSB
#else
  #define SerialPort Serial
#endif

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
      R00 = imu0.roll;
      P00 = imu0.pitch;
      Y00 = imu0.yaw;
      KFR00 = KF00.updateEstimate(R00);
      KFP01 = KF01.updateEstimate(P00);
      KFY02 = KF02.updateEstimate(Y00);
      SerialPort.print("DATA,");
      SerialPort.print(String(KFR00, 2) + "," + String(KFP01, 2) + "," + String(KFY02, 2) + ",");
      imu0.resetFifo();
    }
  }

  TCA0(6);
  if ( imu1.fifoAvailable() )
  {
    if ( imu1.dmpUpdateFifo() == INV_SUCCESS)
    {
      imu1.computeEulerAngles();
      R01 = imu1.roll;
      P01 = imu1.pitch;
      Y01 = imu1.yaw;
      KFR10 = KF10.updateEstimate(R01);
      KFP11 = KF11.updateEstimate(P01);
      KFY12 = KF12.updateEstimate(Y01);
      SerialPort.print(String(KFR10, 2) + "," + String(KFP11, 2) + "," + String(KFY12, 2) + ",");
      imu1.resetFifo();
    }
  }

  TCA0(5);
  if ( imu2.fifoAvailable() )
  {
    if ( imu2.dmpUpdateFifo() == INV_SUCCESS)
    {
      imu2.computeEulerAngles();
      R02 = imu2.roll;
      P02 = imu2.pitch;
      Y02 = imu2.yaw;
      KFR20 = KF20.updateEstimate(R02);
      KFP21 = KF21.updateEstimate(P02);
      KFY22 = KF22.updateEstimate(Y02);
      SerialPort.print(String(KFR20, 2) + "," + String(KFP21, 2) + "," + String(KFY22, 2) + ",");
      imu2.resetFifo();
    }
  }

  TCA0(4);
  if ( imu3.fifoAvailable() )
  {
    if ( imu3.dmpUpdateFifo() == INV_SUCCESS)
    {
      imu3.computeEulerAngles();
      R03 = imu3.roll;
      P03 = imu3.pitch;
      Y03 = imu3.yaw;
      KFR30 = KF30.updateEstimate(R03);
      KFP31 = KF31.updateEstimate(P03);
      KFY32 = KF32.updateEstimate(Y03);
      SerialPort.print(String(KFR30, 2) + "," + String(KFP31, 2) + "," + String(KFY32, 2) + ",");
      imu3.resetFifo();
    }
  }

  TCA0(3);
  if ( imu4.fifoAvailable() )
  {
    if ( imu4.dmpUpdateFifo() == INV_SUCCESS)
    {
      imu4.computeEulerAngles();
      R04 = imu4.roll;
      P04 = imu4.pitch;
      Y04 = imu4.yaw;
      KFR40 = KF40.updateEstimate(R04);
      KFP41 = KF41.updateEstimate(P04);
      KFY42 = KF42.updateEstimate(Y04);
      SerialPort.print(String(KFR40, 2) + "," + String(KFP41, 2) + "," + String(KFY42, 2) + ",");
      imu4.resetFifo();
    }
  }

  TCA0(2);
  if ( imu5.fifoAvailable() )
  {
    if ( imu5.dmpUpdateFifo() == INV_SUCCESS)
    {
      imu5.computeEulerAngles();
      R05 = imu5.roll;
      P05 = imu5.pitch;
      Y05 = imu5.yaw;
      KFR50 = KF50.updateEstimate(R05);
      KFP51 = KF51.updateEstimate(P05);
      KFY52 = KF52.updateEstimate(Y05);
      SerialPort.print(String(KFR50, 2) + "," + String(KFP51, 2) + "," + String(KFY52, 2) + ",");
      imu5.resetFifo();
    }
  }

  TCA0(1);
  if ( imu6.fifoAvailable() )
  {
    if ( imu6.dmpUpdateFifo() == INV_SUCCESS)
    {
      imu6.computeEulerAngles();
      R06 = imu6.roll;
      P06 = imu6.pitch;
      Y06 = imu6.yaw;
      KFR60 = KF60.updateEstimate(R06);
      KFP61 = KF61.updateEstimate(P06);
      KFY62 = KF62.updateEstimate(Y06);
      SerialPort.print(String(KFR60, 2) + "," + String(KFP61, 2) + "," + String(KFY62, 2) + ",");
      imu6.resetFifo();
    }
  }
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  TCA1(2);
  if ( imu7.fifoAvailable() )
  {
    if ( imu7.dmpUpdateFifo() == INV_SUCCESS)
    {
      imu7.computeEulerAngles();
      R07 = imu7.roll;
      P07 = imu7.pitch;
      Y07 = imu7.yaw;
      KFR70 = KF70.updateEstimate(R07);
      KFP71 = KF71.updateEstimate(P07);
      KFY72 = KF72.updateEstimate(Y07);
      SerialPort.print(String(KFR70, 2) + "," + String(KFP71, 2) + "," + String(KFY72, 2) + ",");
      imu7.resetFifo();
    }
  }

  TCA1(3);
  if ( imu8.fifoAvailable() )
  {
    if ( imu8.dmpUpdateFifo() == INV_SUCCESS)
    {
      imu8.computeEulerAngles();
      R08 = imu8.roll;
      P08 = imu8.pitch;
      Y08 = imu8.yaw;
      KFR80 = KF80.updateEstimate(R08);
      KFP81 = KF81.updateEstimate(P08);
      KFY82 = KF82.updateEstimate(Y08);
      SerialPort.print(String(KFR80, 2) + "," + String(KFP81, 2) + "," + String(KFY82, 2) + ",");
      imu8.resetFifo();
    }
  }

  TCA1(4);
  if ( imu9.fifoAvailable() )
  {
    if ( imu9.dmpUpdateFifo() == INV_SUCCESS)
    {
      imu9.computeEulerAngles();
      R09 = imu9.roll;
      P09 = imu9.pitch;
      Y09 = imu9.yaw;
      KFR90 = KF90.updateEstimate(R09);
      KFP91 = KF91.updateEstimate(P09);
      KFY92 = KF92.updateEstimate(Y09);
      SerialPort.print(String(KFR90, 2) + "," + String(KFP91, 2) + "," + String(KFY92, 2) + ",");
      imu9.resetFifo();
    }
  }

  TCA1(5);
  if ( imu10.fifoAvailable() )
  {
    if ( imu10.dmpUpdateFifo() == INV_SUCCESS)
    {
      imu10.computeEulerAngles();
      R10 = imu10.roll;
      P10 = imu10.pitch;
      Y10 = imu10.yaw;
      KFR100 = KF00.updateEstimate(R10);
      KFP101 = KF01.updateEstimate(P10);
      KFY102 = KF02.updateEstimate(Y10);
      SerialPort.print(String(KFR100, 2) + "," + String(KFP101, 2) + "," + String(KFY102, 2) + ",");
      imu10.resetFifo();
    }
  }

  TCA1(6);
  if ( imu11.fifoAvailable() )
  {
    if ( imu11.dmpUpdateFifo() == INV_SUCCESS)
    {
      imu11.computeEulerAngles();
      R11 = imu11.roll;
      P11 = imu11.pitch;
      Y11 = imu11.yaw;
      KFR110 = KF110.updateEstimate(R11);
      KFP111 = KF111.updateEstimate(P11);
      KFY112 = KF112.updateEstimate(Y11);
      SerialPort.print(String(KFR110, 2) + "," + String(KFP111, 2) + "," + String(KFY112, 2) + ",");
      imu11.resetFifo();
    }
  }

  TCA1(7);
  if ( imu12.fifoAvailable() )
  {
    if ( imu12.dmpUpdateFifo() == INV_SUCCESS)
    {
      imu12.computeEulerAngles();
      R12 = imu12.roll;
      P12 = imu12.pitch;
      Y12 = imu12.yaw;
      KFR120 = KF120.updateEstimate(R12);
      KFP121 = KF121.updateEstimate(P12);
      KFY122 = KF122.updateEstimate(Y12);
      SerialPort.print(String(KFR120, 2) + "," + String(KFP121, 2) + "," + String(KFY122, 2) + ",");
      imu12.resetFifo();
    }
  }

  TCA1(1);
  if ( imu13.fifoAvailable() )
  {
    if ( imu13.dmpUpdateFifo() == INV_SUCCESS)
    {
      imu13.computeEulerAngles();
      R13 = imu13.roll;
      P13 = imu13.pitch;
      Y13 = imu13.yaw;
      KFR130 = KF130.updateEstimate(R13);
      KFP131 = KF131.updateEstimate(P13);
      KFY132 = KF132.updateEstimate(Y13);
      SerialPort.println(String(KFR130, 2) + "," + String(KFP131, 2) + "," + String(KFY132, 2));
      imu13.resetFifo();
    }
  }
}
void initSensor()
{
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
/////////////////////////////////////////////////////////////////////////////////////////
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
