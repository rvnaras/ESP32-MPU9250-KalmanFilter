#include <SparkFunMPU9250-DMP.h>
#include <Wire.h>

#ifdef defined(SAMD)
 #define SerialPort SerialUSB
#else
  #define SerialPort Serial
#endif

MPU9250_DMP imu;

float dt = 0.01;
float rollraw, pitchraw, yawraw;
double  comproll,
        comppitch,
        compyaw,
        gyroXrate,
        gyroYrate,
        gyroZrate;

void setup() 
{
  SerialPort.begin(115200);

  // Call imu.begin() to verify communication and initialize
  if (imu.begin() != INV_SUCCESS)
  {
    while (1)
    {
      SerialPort.println("Unable to communicate with MPU-9250");
      SerialPort.println("Check connections, and try again.");
      SerialPort.println();
      delay(5000);
    }
  }
  
  imu.dmpBegin(DMP_FEATURE_6X_LP_QUAT | // Enable 6-axis quat
               DMP_FEATURE_GYRO_CAL, // Use gyro calibration
              10); // Set DMP FIFO rate to 10 Hz
  // DMP_FEATURE_LP_QUAT can also be used. It uses the 
  // accelerometer in low-power mode to estimate quat's.
  // DMP_FEATURE_LP_QUAT and 6X_LP_QUAT are mutually exclusive
}

void loop() 
{
  // Check for new data in the FIFO
  if ( imu.fifoAvailable() )
  {
    // Use dmpUpdateFifo to update the ax, gx, mx, etc. values
    if ( imu.dmpUpdateFifo() == INV_SUCCESS)
    {
      // computeEulerAngles can be used -- after updating the
      // quaternion values -- to estimate roll, pitch, and yaw
      imu.computeEulerAngles();
      printIMUData();
    }
  }
}

void printIMUData(void)
{  
  // After calling dmpUpdateFifo() the ax, gx, mx, etc. values
  // are all updated.
  // Quaternion values are, by default, stored in Q30 long
  // format. calcQuat turns them into a float between -1 and 1
  
  rollraw = imu.roll;
  pitchraw = imu.pitch;
  yawraw = imu.yaw;
  gyroXrate = imu.gx/131;
  gyroYrate = imu.gy/131;
  gyroZrate = imu.gz/131;
  comproll = 0.9*(comproll+gyroXrate*dt)+0.1*rollraw;
  comppitch = 0.9*(comppitch+gyroYrate*dt)+0.1*pitchraw;
  compyaw = 0.9*(compyaw+gyroZrate*dt)+0.1*yawraw;

  SerialPort.println("R/P/Y: " + String(rollraw) + ","+ String(pitchraw) + "," + String(yawraw));
  SerialPort.println("Comp R/P/Y: " + String(comproll) + ","+ String(comppitch) + "," + String(compyaw));
  SerialPort.println();
}
