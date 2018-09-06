
int CS = 0;

const int ContextToneTestPin = 3; 
const int CSpin3 = 4; //CS checking LED, anymaze

int US = 0;


const int EXstartpin = 10; //Experiment start pin
const int ContextIndicatePin = 12;


int context_test = 0;

unsigned long timer = 0;
long hab = 10000; //habituation ms
int hstate = 0;
int test=0;
int prob;
int isi;
int trial=0;
unsigned long starttime;
long context = 120000; //context ms
int prev_state = 0;



int EX = 0; //Ex begin

int sV = 1023; //Switch sensor value


void setup() {
  // put your setup code here, to run once:


  pinMode(ContextToneTestPin, INPUT);
  pinMode(CSpin3, OUTPUT);
  pinMode(ContextIndicatePin, OUTPUT);


  
  pinMode(EXstartpin, OUTPUT);

 
  
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

 context_test = digitalRead(ContextToneTestPin);  //Check if it is context tone test

 while(context_test == 0) //if it is not conetxt tone test
 {

  digitalWrite(ContextIndicatePin, LOW);
 // read the analog in value:

 if(prev_state == 0 ||  prev_state == 2)
 {
  Serial.println("Chasing mode");
  prev_state = 1;
   EX = 0;
 }
  sV = analogRead(A0);


  if (sV > 1020) //no_switch_off everything
  {
  
  digitalWrite(CSpin3, LOW);

 
  if (CS == 1)
  {
    Serial.println("y");
    Serial.println("CS OFF");
    CS = 0;
  }

  if (US == 1)
  {
  Serial.println("s");  //send xbee serial to robot_stop
  delay(5);
  US = 0; // to send serial only once
  }
  }


  if (sV < 5) //switch1_yellow _ CS on
  {
  
  digitalWrite(CSpin3, HIGH);
  if(CS ==0)
  {
  Serial.println("t");
  Serial.println(" CS ON");
  CS =1;
  }
  }

  if (sV >135 && sV < 143) // switch2_red _ US Clockwise on
{
  

  if (US == 0)
  {
  Serial.println("w");  //send xbee serial to robot_clockwise
  delay(5);
  Serial.println(" US ON CLOCKWISE");
  delay(5);
  US = 1; // to send serial only once
  }  
  }

  
  if (sV >320 && sV < 328) // switch3_blue _ US CounterClockwise on
{
  

  if (US == 0)
  {
  Serial.println("x");  //send xbee serial to robot_counterclockwise
  delay(5);
  Serial.println(" US ON COUNTERCLOCKWISE");
  delay(5);
  US = 1; // to send serial only once
  }  
  }








if (sV >498 && sV < 503) // switch4_green _ forced stop
{
  
  Serial.println("s");  //send xbee serial stop
  delay(5);
  Serial.println("s");  //send xbee serial stop
  delay(5);
  Serial.println("s");  //send xbee serial stop
  delay(5);
  
  }

 



if (sV >733 && sV < 741) // switch5_white experiment schedule begin
{ EX = 1;
 Serial.println("s");
 delay(5);}


while(EX == 1) //no manual control when experiment begins
{ //for example
  
  timer = millis()-starttime; // clock
      
        prob = random(1,101); //generate random number from 1 to 100
        isi = random(15,26);// generate random number from 15 to 20
        isi = isi * 1000;// change to ms
        trial = trial +1; //count trial
        US = 0;
        
        
        
        
if (hstate == 0)
{
   starttime = millis();
   timer = millis()-starttime; // clock
   Serial.print(timer);
   Serial.println(" HAB START");
    digitalWrite(EXstartpin, HIGH);
    delay(hab);
    digitalWrite(EXstartpin,LOW);
    
  hstate = 1;
  }
  
        Serial.print(timer);
        Serial.print(" TRIAL ");
        Serial.println(trial);
      
      if(trial <= 20)
      {
            
          
         timer = millis()-starttime;
          Serial.print(timer);
          Serial.println("t");
           Serial.println(" CS ON");
          
          digitalWrite(CSpin3, HIGH);
        delay(2500); // CS_only duration
        
                 
        timer = millis()-starttime;
          Serial.print(timer);
          
           if(prob <= 50)
           {
           Serial.println(" US CLOCKWISE");

        

          if (US == 0)
         {
            Serial.println("w");  //send xbee serial to robot_clockwise
            US = 1; // to send serial only once
           }  

      
           }

           
            if(50<prob)
            {
              Serial.println(" US COUNTER CLOCKWISE");

        

          if (US == 0)
         {
            Serial.println("x");  //send xbee serial to robot_counter clockwise
            US = 1; // to send serial only once
           } 
           
            }
            
  delay(2500); // US duration (co-terminating with CS)
  Serial.println("s");  //send xbee serial to robot_clockwise
  Serial.println("y");
  
  digitalWrite(CSpin3, LOW);// edited, important

  
  US = 0;
  
        timer = millis()-starttime;
        Serial.print(timer);
        Serial.println(" CS US OFF");
  
     
     
        timer = millis()-starttime; // clock
          Serial.print(timer);
           Serial.println(" ISI START");
          delay(isi);
      }
      
      if(trial == 20)
      {
        Serial.print(timer);
        Serial.println(" END TEST");
        
       EX = 0; //break experiment
        
      }
    }



context_test = digitalRead(ContextToneTestPin);  //Check if it is context tone test
    
}






while(context_test == 1)
{

  digitalWrite(ContextIndicatePin, HIGH);
   // read the analog in value:


 if(prev_state == 0 || prev_state == 1)
 {
  Serial.println("Con_ex one es mode");
  prev_state = 2;
  EX = 0;
 }


 
  sV = analogRead(A0);


  if (sV > 1020) //no_switch_off everything
  {
  
  digitalWrite(CSpin3, LOW);


  if (CS == 1)
  {
    Serial.println("y");
    Serial.println("CS OFF");
    CS = 0;
  }

  if (US == 1)
  {
  Serial.println("s");  //send xbee serial to robot_stop
  delay(5);
  US = 0; // to send serial only once
  }
  }


  if (sV < 5) //switch1_yellow _ CS on
  {
 
  digitalWrite(CSpin3, HIGH);
  if(CS ==0)
  {
     Serial.println("t");
  Serial.println(" CS ON");
  CS =1;
  }
  }

  if (sV >135 && sV < 143) // switch2_red _ US Clockwise on
{

  }

  
  if (sV >320 && sV < 328) // switch3_blue _ US CounterClockwise on
{
  
  }








if (sV >498 && sV < 503) // switch4_green _ forced stop
{
  
  Serial.println("s");  //send xbee serial stop
  delay(5);
  Serial.println("s");  //send xbee serial stop
  delay(5);
  Serial.println("s");  //send xbee serial stop
  delay(5);
  
  }

 



if (sV >733 && sV < 741) // switch5_white experiment schedule begin
{ EX = 1;
 Serial.println("s");
 delay(5);}


while(EX == 1) //no manual control when experiment begins
{ //for example
  
  timer = millis()-starttime; // clock
      
        
        isi = 20000;// change to ms
        trial = trial +1; //count trial
        
        
        
        
if (hstate == 0)
{
   starttime = millis();
   timer = millis()-starttime; // clock
   Serial.print(timer);
   Serial.println(" CONTEXT AND TONE TEST START");
    digitalWrite(EXstartpin, HIGH);
    delay(context);
    digitalWrite(EXstartpin,LOW);
    
    
  hstate = 1;
  }
  
        Serial.print(timer);
        Serial.print(" TRIAL ");
        Serial.println(trial);
      
      if(trial <= 3)
      {
            
          
         timer = millis()-starttime;
          Serial.print(timer);
           Serial.println("t");
           Serial.println(" CS ON");
          
          digitalWrite(CSpin3, HIGH);
        delay(20000); // CS_only duration

  Serial.println("s"); 
  Serial.println("y");  
 
  digitalWrite(CSpin3, LOW);// edited, important
  
  
   
        timer = millis()-starttime;
        Serial.print(timer);
        Serial.println(" CS OFF");
  
     
     
        timer = millis()-starttime; // clock
          Serial.print(timer);
           Serial.println(" ISI START");
          delay(isi);
      }
      
      if(trial == 3)
      {
        Serial.print(timer);
        Serial.println(" END TEST");
        
       EX = 0; //break experiment
        
      }
    }

    context_test = digitalRead(ContextToneTestPin);  //Check if it is context tone test
    
}



}
