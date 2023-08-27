#define debug true

void reset(){
  pinMode(2,OUTPUT);digitalWrite(2,false); //Ground the reset line
}


const byte lights[]={3,4,6,7,9};

void setup() {
  pinMode(5,INPUT_PULLUP);
  pinMode(8,OUTPUT);
  pinMode(12,OUTPUT);
  Serial.begin(9600);

  pinMode(2,INPUT);digitalWrite(2,false);
  for(byte i=0;i<5;i++){
    pinMode(lights[i],OUTPUT);digitalWrite(lights[i],true);
    delay(100);digitalWrite(lights[i],false);
  }
}
const unsigned long minutes=60000; 
boolean btn;
boolean pump;
unsigned long offTime=0;
unsigned long downTime;
long timeLeft(){
    unsigned long a=millis();
    unsigned long b=offTime;
    if(b>a)return long(b-a);
    else return  -long(a-b);
}
void loop() {
  if(btn&&!digitalRead(5)){  //button just pressed down
    if(millis()>downTime+200){//more than 2 tenths of a second ago...
      downTime=millis();//  register time of press
      offTime=max(millis(),offTime)+1*minutes;//and add a minute to the timer
      btn=false;
    }
  }
  
  offTime=min(offTime,millis()+5*minutes);       //Cap it at 5 minutes.

  if( (millis()>millis()+1000*minutes) && timeLeft()<=0 )reset();//If the time is going to overflow, reset, but don't interfere with active chemical feed.

  for(byte i=0;i<5;i++){
    digitalWrite(lights[i],timeLeft()>(i*minutes) && timeLeft()>0);
  }
  
  pump=millis()<offTime;
  
  if((!btn && millis()>downTime+1000)){//override stop
    offTime=millis();
  }
  if(timeLeft()<0)offTime=millis();
  
  if(!btn)btn=digitalRead(5);
  digitalWrite(8,pump);
  digitalWrite(12,pump);
  if(debug)Serial.println(timeLeft());
}
