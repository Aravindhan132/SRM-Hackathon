unsigned char val[90],x,i1;
unsigned int a;

void setup() 
{
  Serial.begin(9600);
  delay(500);delay(500);
  gsm_init();   
}

void loop() 
{   
   a++;
   delay(500);
   if(a>30)
   {
      MSG_Send();
       a=0;
   }
   //Serial.print(a);
}

void serialEvent() 
{
  while(Serial.available()) 
  {  
    val[x] = Serial.read();
    if(val[0]!='$'){x=0;goto last;}
    else if(val[0]=='$'&&val[1]!='G'){x=1;goto last;}
    else if(val[0]=='$'&&val[1]=='G'&&val[2]!='P'){x=2;goto last;}
    else if(val[0]=='$'&&val[1]=='G'&&val[2]=='P'&&val[3]!='R'){x=3;goto last;}
    else if(val[0]=='$'&&val[1]=='G'&&val[2]=='P'&&val[3]=='R'&&val[4]!='M'){x=4;goto last;}
    else if(val[0]=='$'&&val[1]=='G'&&val[2]=='P'&&val[3]=='R'&&val[4]=='M'&&val[5]!='C'){if(x<60)x++;goto last;}    		
    last:;
  }  
}

void gsm_init()
{
  Serial.write("AT");
  Serial.write(0x0d);Serial.write(0x0a);
  delay(500); 
  
  Serial.write("AT+CMGF=1");
  Serial.write(0x0d);Serial.write(0x0a);
  delay(400);
  
  Serial.write("AT+CNMI=2,2,0,0,0");
  Serial.write(0x0d);Serial.write(0x0a);
  delay(500);
}

void MSG_Send()
{
  Serial.write("AT+CMGS=");
  Serial.write('"');
  Serial.write("7402600361");
  Serial.write('"');  
  Serial.write(0x0d);Serial.write(0x0a);
  delay(500);
  
  
  Serial.print("SRM University");
  Serial.write(0x0d);Serial.write(0x0a);
  delay(500);
  
  Serial.print("https://www.google.com/maps/?q=");delay(500);
  for(i1=0;i1<12;i1++){Serial.write(val[i1+19]);delay(100);}
  Serial.write(0x0d);Serial.write(0x0a);
  Serial.print(",");
  for(i1=0;i1<12;i1++){Serial.write(val[i1+32]);delay(100);}
  Serial.write(0x0d);Serial.write(0x0a);
  delay(500);
  
 
  
  Serial.write(0x1a);
  delay(100);
  Serial.print("This Project is done by Tech_Narvi");
  delay(100);
  
  
  
 
}