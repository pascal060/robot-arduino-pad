#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>

#include <Adafruit_MotorShield.h>


String BTdata;  // modif type;
char S_Speed[3]="0", S_Angle[3]="0";
String S_Speed2,S_Angle2;
String sens;
int Speed, Angle;
int Delta_D_F, Delta_G_F;
int Delta_D_B, Delta_G_B;
double Delta;


int i,j,k=0;

SoftwareSerial BTSerial(2,3);

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *AdaDCMotor_1 = AFMS.getMotor(1);
double SpeedAdaDCMotor_1 = 0;
Adafruit_DCMotor *AdaDCMotor_2 = AFMS.getMotor(2);
double SpeedAdaDCMotor_2 = 0;


void setup(){
    BTSerial.begin(9600);
    Serial.begin(9600);
    AFMS.begin();
    BTSerial.setTimeout(10);
    Serial.println("setup fini");

}


void loop(){
    if(BTSerial.available()){
        BTdata = String(BTSerial.readString());

        i=0, j=0;   
        if((BTdata[i])==('R')){
            while (BTdata[i]!='A') {
              i++; 
              if(BTdata[i]!='A') S_Speed[i-1]=BTdata[i]; //Serial.print(BTdata[i])
            }
            S_Speed[i-1]='\0';
            S_Speed2=S_Speed;
            //Serial.print(S_Speed);
            //Serial.print("         ");
            while (BTdata[i]!='\0' && BTdata[i]!='R') {
              i++; 
              if(BTdata[i]!='\0' & BTdata[i]!='R') S_Angle[j]=BTdata[i]; //Serial.print(BTdata[i])
              j++;
            }
            S_Angle[j-1]='\0';
            S_Angle2=S_Angle;
            //Serial.print(S_Angle);
            //Serial.print("         ");
            //Serial.println(BTdata);           
        }

Speed=S_Speed2.toInt();
Angle=S_Angle2.toInt();
if(Angle>0 && Angle<180) {sens = "BACKWARD";} else {sens = "FORWARD";}

            /*Serial.print(Speed);
            Serial.print("         ");
            Serial.print(Angle);
            Serial.print("         ");
            Serial.print(BTdata);
            Serial.print("         ");
            Serial.println(sens);*/

            if(Angle>=0 && Angle<90) Delta_D_B=90-Angle; else Delta_D_B=0;
            if(Angle>=90 && Angle<180) Delta_G_B=Angle-90; else Delta_G_B=0;
            if(Angle>=181 && Angle<270) Delta_G_F=270-Angle; else Delta_G_F=0;
            if(Angle>=270 && Angle<360) Delta_D_F=Angle-270; else Delta_D_F=0;

                        
            /*Serial.print(Delta_D_B);
            Serial.print("         ");
            Serial.print(Delta_G_B);
            Serial.print("         ");
            Serial.print(Delta_G_F);
            Serial.print("         ");
            Serial.print(Delta_D_F);
            Serial.print("         ");*/
            
if (Speed==0)
{
  AdaDCMotor_1->run(RELEASE);
  AdaDCMotor_2->run(RELEASE);
}
else
{
if(sens=="FORWARD"){
  if(Angle>=181 && Angle<270){
  SpeedAdaDCMotor_1 =double(Speed); 
  SpeedAdaDCMotor_2 =double(Speed)*((90.0-double(Delta_G_F))/90.0);
  /*Serial.print(SpeedAdaDCMotor_1);
  Serial.print("         ");
  Serial.println(SpeedAdaDCMotor_2);*/
  AdaDCMotor_1->setSpeed(SpeedAdaDCMotor_1);
  AdaDCMotor_2->setSpeed(SpeedAdaDCMotor_2);
  AdaDCMotor_1->run(FORWARD);
  AdaDCMotor_2->run(FORWARD);}
}
if(sens=="FORWARD"){
  if(Angle>=270 && Angle<360){
  SpeedAdaDCMotor_2 =double(Speed); 
  SpeedAdaDCMotor_1 =double(Speed)*((90.0-double(Delta_D_F))/90.0);
  /*Serial.print(SpeedAdaDCMotor_1);
  Serial.print("         ");
  Serial.println(SpeedAdaDCMotor_2);*/
  AdaDCMotor_1->setSpeed(SpeedAdaDCMotor_1);
  AdaDCMotor_2->setSpeed(SpeedAdaDCMotor_2);
  AdaDCMotor_1->run(FORWARD);
  AdaDCMotor_2->run(FORWARD);}
}
if(sens=="BACKWARD"){
  if(Angle>=0 && Angle<90){
  SpeedAdaDCMotor_1 =double(Speed); 
  SpeedAdaDCMotor_2 =double(Speed)*((90.0-double(Delta_D_B))/90.0);
  /*Serial.print(SpeedAdaDCMotor_1);
  Serial.print("         ");
  Serial.println(SpeedAdaDCMotor_2);*/
  AdaDCMotor_1->setSpeed(SpeedAdaDCMotor_1);
  AdaDCMotor_2->setSpeed(SpeedAdaDCMotor_2);
  AdaDCMotor_1->run(BACKWARD);
  AdaDCMotor_2->run(BACKWARD);}
}
if(sens=="BACKWARD"){
  if(Angle>=90 && Angle<180){
  SpeedAdaDCMotor_2 =double(Speed); 
  SpeedAdaDCMotor_1 =double(Speed)*((90.0-double(Delta_G_B))/90.0);
  /*Serial.print(SpeedAdaDCMotor_1);
  Serial.print("         ");
  Serial.println(SpeedAdaDCMotor_2);*/
  AdaDCMotor_1->setSpeed(SpeedAdaDCMotor_1);
  AdaDCMotor_2->setSpeed(SpeedAdaDCMotor_2);
  AdaDCMotor_1->run(BACKWARD);
  AdaDCMotor_2->run(BACKWARD);}
}



}

}
} 
