                  //Link Tutorial//
//https://www.youtube.com/watch?v=Lr5gvtXMCZQ&t=288s//

                //Perhitungan garis//
// m = [log(y2)-log(y1)]/[log(x2)-log(x1)];
//b =log(y) - m*log(x);

//#include <SimpleKalmanFilter.h>
//#define nilaiBasis 86.0  //nilai pembacaan sensor ketika udara bersih
//SimpleKalmanFilter simpleKalmanFilter(nilaiBasis, nilaiBasis, 0.01);

//MQ-6
#define Analog_PIN2 13
#define RLmq6 1
#define mCOmq6 -0.77110
#define bCOmq6 2.55167
#define nilaiBasismq6 86.0 

float VRLmq6 = 0;
float Rsmq6 = 0;
float Romq6 = 2.12;
//5.23
float Ratiomq6 = 0;
float COmq6 = 0;
float pembacaanSensorOmq6 = 86;

// Serial output refresh time
const long SERIAL_REFRESH_TIME = 100;
long refresh_time;

void setup() {
  Serial.begin(9600);
  delay(2000);
}

void loop() {
  //MQ-6
  // read a reference value from A0 and map it from 0 to 100
  float real_valuemq6 = analogRead(Analog_PIN2);
  // add a noise to the reference value and use as the measured value
  //float measured_valuemq6 = real_valuemq6 + random(-100,100)/nilaiBasis;
  // calculate the estimated value with Kalman Filter
  //float estimated_valuemq6 = simpleKalmanFilter.updateEstimate(measured_valuemq6);
  //Serial.print("estimated_valuemq6 = ");
  //Serial.println(estimated_valuemq6);
  //Serial.print("real_valuemq6 = ");
  //Serial.println(real_valuemq6);

  VRLmq6 = real_valuemq6* (3.3/4095.0);
  Rsmq6 = ((3.3/VRLmq6)-1) * RLmq6;

  //Kalibrasi nilai Ro = nilai udara bersih
  //Romq6 = Rsmq6/9.6;
  //Serial.print("Ro MQ-6 = ");
  //Serial.println(Romq6);

  Ratiomq6 =  Rsmq6/Romq6;
  COmq6 = pow(10, ((log10(Ratiomq6)-bCOmq6)/mCOmq6));

  //Serial.print("Nilai filter MQ-6 = ");
  //Serial.println(estimated_valuemq6);
  //Serial.print("nilai Real MQ-6 = ");
  //Serial.println(real_valuemq6);
  //Serial.print("Rs/Ro MQ-6 = ");
  //Serial.println(Ratiomq6);

  Serial.print("Konsentrasi CO MQ-6 = ");
  Serial.print(COmq6);
  Serial.println(" ppm");

  delay(2000);
}
