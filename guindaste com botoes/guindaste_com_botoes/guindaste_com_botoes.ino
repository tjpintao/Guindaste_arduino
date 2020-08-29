
int up, down, horario, anti_horario;

byte relay1=LOW;
byte relay2=LOW;
byte relay3=LOW;
byte relay4=LOW;


//PINS
const int pin_up = 10;
const int pin_down = 11;
const int pin_horario = 13;
const int pin_anti_horario = 12;

const int pin_relay1 = 3;
const int pin_relay2 = 4;
const int pin_relay3 = 5;
const int pin_relay4  = 6;

int vert=0; 
int hori=0;

void setup() 
{

  Serial.begin (115200); 

  //INPUT AND OUTPUT PINS
  pinMode (pin_up, INPUT_PULLUP);
  pinMode (pin_down, INPUT_PULLUP);
  pinMode (pin_horario, INPUT_PULLUP);
  pinMode (pin_anti_horario, INPUT_PULLUP);
  
  pinMode (pin_relay1, OUTPUT);
  pinMode (pin_relay2, OUTPUT);
  pinMode (pin_relay3, OUTPUT);
  pinMode (pin_relay4, OUTPUT);

  digitalWrite (pin_relay1, HIGH);
  digitalWrite (pin_relay2, HIGH);
  digitalWrite (pin_relay3, HIGH);
  digitalWrite (pin_relay4, HIGH);
   
}

void read_inputs(void)
{
  if (digitalRead (pin_up) == LOW) up=1; else up=0;
  if (digitalRead (pin_down) == LOW) down=1; else down=0;
  if (digitalRead (pin_horario) == LOW) horario=1; else horario=0;
  if (digitalRead (pin_anti_horario) == LOW) anti_horario=1; else anti_horario=0;
  
}


void loop() 
{
  read_inputs();
   
  //VERTICAL
    if (((!up) && (!down))|| (up && down)) 
      vert=0;
      
    else if (up && (!down)) 
      vert=1;

    else if ((!up) && down) 
      vert=-1;
  
  //HORIZONTAL

    if (((!horario) && (!anti_horario)) || (anti_horario && horario)) 
      hori=0;
      
    else if (horario && (!anti_horario)) 
      hori=1;

    else if ((!horario) && anti_horario) 
      hori=-1;
      
   
    
  //Saídas
   if (vert==0) 
   {
     relay1=HIGH;
     relay2=HIGH;
   }
   
   else if (vert==1) 
   {
    relay1=LOW;
    relay2=HIGH;
   }
  
   else if (vert==-1) 
   {
    relay1=HIGH;
    relay2=LOW;
   }

   if (hori==0) 
   {
     relay3=HIGH;
     relay4=HIGH;
   }
  
   else if (hori==1) 
   {
    relay3=LOW;
    relay4=HIGH;
   }
  
   else if (hori==-1) 
   {
    relay3=HIGH;
    relay4=LOW;
   }

   digitalWrite(pin_relay1, relay1);
   digitalWrite(pin_relay2, relay2);
   digitalWrite(pin_relay3, relay3);
   digitalWrite(pin_relay4, relay4);
   
  Serial.print("\n");
  Serial.println("VERTICAL");
  Serial.print(up);
  Serial.print(down);
  Serial.print(relay1);
  Serial.print(relay2);
  
  Serial.print("\n");
  
  Serial.println("HORIZONTAL");
  Serial.print(horario );
  Serial.print(anti_horario);
  Serial.print(relay3);
  Serial.print(relay4);
  
  //Serial.print("\n");
  delay(100);
}
