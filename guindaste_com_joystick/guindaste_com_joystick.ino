byte relay1;
byte relay2;
byte relay3;
byte relay4;
byte newrelay1;
byte newrelay2;
byte newrelay3;
byte newrelay4;
int botz = 0;
int state_y1 = 0;
int state_y2 = 0;

const int pin_stop1 = 11; //lado da luz
const int pin_stop2 = 10; //lado oposto da luz
const int pin_stop_cima = 9;

const int pin_emagnet = 2;
const int pin_relay1 = 3;
const int pin_relay2 = 4;
const int pin_relay3 = 5;
const int pin_relay4  = 6;

const int pin_x = A1;
const int pin_y = A2;
const int pin_z = 12;

int x, y;
int z;
int stop_cima;
int L1, L2;


void setup()
{
  pinMode (pin_stop1, INPUT);
  pinMode (pin_stop2, INPUT);
  pinMode (pin_stop_cima, INPUT);
  pinMode (pin_z, INPUT_PULLUP);

  pinMode (pin_emagnet, OUTPUT);
  pinMode (pin_relay1, OUTPUT);
  pinMode (pin_relay2, OUTPUT);
  pinMode (pin_relay3, OUTPUT);
  pinMode (pin_relay4, OUTPUT);

  digitalWrite (pin_emagnet, LOW);
  digitalWrite (pin_relay1, HIGH);
  digitalWrite (pin_relay2, HIGH);
  digitalWrite (pin_relay3, HIGH);
  digitalWrite (pin_relay4, HIGH);

  Serial.begin (115200);
}


void read_input(void)
{
  if (digitalRead(pin_z) == LOW) z = 1; else z = 0;
  if (digitalRead(pin_stop1) == LOW) L1 = 1; else L1 = 0;
  if (digitalRead(pin_stop2) == LOW) L2 = 1; else L2 = 0;
  if (digitalRead(pin_stop_cima) == LOW) stop_cima = 1; else stop_cima = 0;
  x = analogRead(pin_x);
  y = analogRead(pin_y);
}
void loop()
{
  read_input();
  
  //IMAN
  if ((botz == 0) && z)
    botz = 1;
  else if ((botz == 1) && !z)
    botz = 2;
  else if (botz == 2 && z)
    botz = 3;
  else if ((botz == 3) && !z)
    botz = 0;



  //EIXO X
  if (x <= 500) //ANTI-HORARIO
  {
    relay3 = LOW;
    relay4 = HIGH;
  }

  else if (x >= 520) //HORARIO
  {
    relay3 = HIGH;
    relay4 = LOW;
  }

  else
  {
    relay3 = HIGH;
    relay4 = HIGH;
  }
  
  

  //EIXO Y
    if ((y>=520) && (!stop_cima))
    {
      relay1 = LOW;
      relay2 = HIGH;
      newrelay1=relay1;
      newrelay2=relay2;
    }

    else if ((y>=520) && (stop_cima) && (state_y2==0))
      state_y1=1;

    else if ((state_y1==1) && (y<=505) && (stop_cima))
      state_y1=2;

    /*else if ((state_y1==2) && (stop_cima) )
      state_y1=1;
      */
    
    else if ((state_y1==2) && (!stop_cima))
      state_y1=0;
  

  
 //OTHER SIDE
   else if ((y<=505) && (!stop_cima))
    {
      relay1 = HIGH;
      relay2 = LOW;
      newrelay3=relay1;
      newrelay4=relay2;
    }

    else if ((y<=505) && (stop_cima) && (state_y1==0))
      state_y2=1;

    else if ((state_y2==1) && (y>=520) && (stop_cima))
    {
      state_y2=2;
      
    }
      

    /*else if ((state_y2==2) && (stop_cima))
      state_y2=1;*/
    
    else if ((state_y2==2) && (!stop_cima))
      state_y2=0;
   
    
    else 
    {
      relay1 = HIGH;
      relay2 = HIGH;
    }
    


  //SAÍDAS
  if ((state_y2==1) || (state_y1==1))
  {
    relay1=HIGH;
    relay2=HIGH;
  }

  if (state_y1==2)
  {
    relay1 = newrelay2;
    relay2 = newrelay1;
  }
  
  if (state_y2==2) 
  {
    relay1 = newrelay4;
    relay2 = newrelay3;
  }
      
  if (L1)
  {
    relay3 = HIGH;
    relay4 = HIGH;

    if (x > 520) //HORARIO
    {
      relay3 = HIGH;
      relay4 = LOW;
    }
  }

  if (L2)
  {
    relay3 = HIGH;
    relay4 = HIGH;

    if (x <= 500) //ANTI-HORARIO
    {
      relay3 = LOW;
      relay4 = HIGH;
    }
  }

 
  
  digitalWrite (pin_relay1, relay1);
  digitalWrite (pin_relay2, relay2);
  digitalWrite (pin_relay3, relay3);
  digitalWrite (pin_relay4, relay4);




  if ((botz == 2) || (botz == 3))
    digitalWrite (pin_emagnet, HIGH);
  else if ((botz == 0) || (botz == 1))
    digitalWrite (pin_emagnet, LOW);



  Serial.println ("X");
  Serial.print (x ); Serial.print (" R1 "); Serial.print(relay1 ); Serial.print(" R2 "); Serial.print(relay2);
  Serial.print ("\n");
  Serial.println ("Y");
  Serial.print (y ); Serial.print (" R3 "); Serial.print (relay3 ); Serial.print (" R4 "); Serial.print(relay4);
  Serial.print("\n");
  Serial.print("state_y1: "); Serial.print(state_y1);  Serial.print("\n");
  Serial.print("state_y2: "); Serial.print(state_y2);  Serial.print("\n");
  Serial.print("stop_cima: "); Serial.print(stop_cima); Serial.print("\n");
  Serial.print("lado da luz: "); Serial.print(pin_stop1); Serial.print("\n");
  Serial.print("lado oposto da luz: "); Serial.print(pin_stop2); Serial.print("\n");


  Serial.print (botz);
  Serial.print("\n");
  Serial.print ("botao:" ); Serial.print(z);
  Serial.print("\n");


  delay(100);

}
