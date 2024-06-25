#include <stdio.h> 
//#include "variables.h"
#include "str_rout.h"
//#include "SST25FlashDrv.h"
//#include "var_system.h"

uint8_t GetHexDigit(uint8_t hex_digit);

uint8_t *Num1ToStr(uint8_t d)
{
	static uint8_t str[2];
	str[0] = '0'+d;
	str[1]=0;
	return str;
}


uint8_t *Num2ToStr(uint16_t d)
{
	static uint8_t str[3];

	str[0] = '0';
	while(d >= 10){ d-=10; str[0]++; }
	str[1] = '0'+d;
	str[2]=0; 
	return str;
}

uint8_t *Num3ToStr(uint32_t d)
{
	static uint8_t str[4];
        //uint8_t *str;
	str[0] = '0';
	while(d >= 100){ d-=100; str[0]++; }
	str[1] = '0';
	while(d >= 10){ d-=10; str[1]++; }
	str[2] = '0'+d;
	str[3]=0;
	return str;
}

uint8_t *Num0_999ToStrSpace(uint32_t d)
{
	static uint8_t str[4],s;
        //unsigned uint8_t s;
        if (d>=100)
        {
            str[0]='0';
            while(d >= 100){ d-=100; str[0]++; }
            str[1] = '0';
            while(d >= 10){ d-=10;str[1]++; }
            str[2] = '0'+d;
            str[3]=0;
        }
        else
        {
            if (d>=10)
            {
                 s='0';
                 while(d >= 10){ d-=10; s++; str[0]=s; }
                 str[1] = '0' + d;
                 str[2]=0;
                 str[3]=0;
            }
            else
            {
                str[0]= '0'+d;
                str[1]=0;
                str[2]=0;
                str[3]=0;
            }
        }
	
	return str;
}

uint8_t *Num0_9999ToStrSpace(uint32_t d)
{
	static uint8_t str[5];
        uint8_t s;
        //unsigned char s;
        if (d>=1000)
        {
            str[0]='0';
            while(d >= 1000){ d-=1000; str[0]++; }
            str[1] = '0';
            while(d >= 100){ d-=100;str[1]++; }
            str[2] = '0';
            while(d >= 10){ d-=10;str[2]++; }
            str[3]='0'+d;
            str[4]=0;
        }
        else
        {
          if (d>=100)
          {
              str[0]='0';
              while(d >= 100){ d-=100; str[0]++; }
              str[1] = '0';
              while(d >= 10){ d-=10;str[1]++; }
              str[2] = '0'+d;
              str[3]=0;
              str[4]=0;
          }
          else
          {
              if (d>=10)
              {
                   s='0';
                   while(d >= 10){ d-=10; s++; str[0]=s; }
                   str[1] = '0' + d;
                   str[2]=0;
                   str[3]=0;
                   str[4]=0;
              }
              else
              {
                  str[0]= '0'+d;
                  str[1]=0;
                  str[2]=0;
                  str[3]=0;
                  str[4]=0;
              }
          }
	
        }
	
	return str;
}

uint8_t *Num0_999_m_ToStrSpace(uint32_t d)
{
	static uint8_t str[6];
        uint8_t s;
        //unsigned char s;
        if (d>=100)
        {
            str[0]='0';
            while(d >= 100){ d-=100; str[0]++; }
            str[1] = '0';
            while(d >= 10){ d-=10;str[1]++; }
            str[2] = '0'+d;
            str[3]=' ';
            str[4]='%';
            str[5]=0;
        }
        else
        {
            if (d>=10)
            {
                 s='0';
                 while(d >= 10){ d-=10; s++; str[0]=s; }
                 str[1] = '0' + d;
                 str[2]=' ';
                 str[3]='%';
                 str[4]=0;
                 str[5]=0;
            }
            else
            {
                str[0]= '0'+d;
                str[1]=' ';
                str[2]='%';
                str[3]=0;
                str[4]=0;
                str[5]=0;
            }
        }
	
	return str;
}

uint8_t *Num0_999_m_ToStr_no_Space(uint32_t d)
{
	static uint8_t str[5];
        uint8_t s;
        //unsigned char s;
        if (d>=100)
        {
            str[0]='0';
            while(d >= 100){ d-=100; str[0]++; }
            str[1] = '0';
            while(d >= 10){ d-=10;str[1]++; }
            str[2] = '0'+d;
            str[3]='%';
            str[4]=0;
        }
        else
        {
            if (d>=10)
            {
                 s='0';
                 while(d >= 10){ d-=10; s++; str[0]=s; }
                 str[1] = '0' + d;
                 str[2]='%';
                 str[3]=0;
                 str[4]=0;
            }
            else
            {
                str[0]= '0'+d;
                str[1]='%';
                str[2]=0;
                str[3]=0;
                str[4]=0;
            }
        }
	
	return str;
}

uint8_t *Num0_9999_m_ToStrSpace(uint32_t d)
{
	static uint8_t str[7];
        uint8_t s;
        //unsigned char s;
        if (d>=1000)
        {
            str[0]='0';
            while(d >= 1000){ d-=1000; str[0]++; }
            str[1] = '0';
            while(d >= 100){ d-=100;str[1]++; }
            str[2] = '0';
            while(d >= 10){ d-=10;str[2]++; }
            str[3]='0'+d;
            str[4]=' ';
            str[5]='m';
            str[6]=0;
        }
        else
        {
          if (d>=100)
          {
              str[0]='0';
              while(d >= 100){ d-=100; str[0]++; }
              str[1] = '0';
              while(d >= 10){ d-=10;str[1]++; }
              str[2] = '0'+d;
              str[3]=' ';
              str[4]='m';
              str[5]=0;
              str[6]=0;
          }
          else
          {
              if (d>=10)
              {
                   s='0';
                   while(d >= 10){ d-=10; s++; str[0]=s; }
                   str[1] = '0' + d;
                   str[2]=' ';
                   str[3]='m';
                   str[4]=0;
                   str[5]=0;
                   str[6]=0;
              }
              else
              {
                  str[0]= '0'+d;
                  str[1]=' ';
                  str[2]='m';
                  str[3]=0;
                  str[4]=0;
                  str[5]=0;
                  str[6]=0;
              }
          }
	
        }
	
	return str;
}

uint8_t *Num0_9999_m_ToStr_no_Space(uint32_t d)
{
	static uint8_t str[6];
        uint8_t s;
        //unsigned char s;
        if (d>=1000)
        {
            str[0]='0';
            while(d >= 1000){ d-=1000; str[0]++; }
            str[1] = '0';
            while(d >= 100){ d-=100;str[1]++; }
            str[2] = '0';
            while(d >= 10){ d-=10;str[2]++; }
            str[3]='0'+d;
            str[4]='m';
            str[5]=0;
        }
        else
        {
          if (d>=100)
          {
              str[0]='0';
              while(d >= 100){ d-=100; str[0]++; }
              str[1] = '0';
              while(d >= 10){ d-=10;str[1]++; }
              str[2] = '0'+d;
              str[3]='m';
              str[4]=0;
              str[5]=0;
          }
          else
          {
              if (d>=10)
              {
                   s='0';
                   while(d >= 10){ d-=10; s++; str[0]=s; }
                   str[1] = '0' + d;
                   str[2]='m';
                   str[3]=0;
                   str[4]=0;
                   str[5]=0;
              }
              else
              {
                  str[0]= '0'+d;
                  str[1]='m';
                  str[2]=0;
                  str[3]=0;
                  str[4]=0;
                  str[5]=0;
              }
          }
	
        }
	
	return str;
}

uint8_t *Num4ToStr(uint32_t d)
{
	static uint8_t str[5];

	str[0] = '0';
	while(d >= 1000){ d-=1000; str[0]++; }
	str[1] = '0';
	while(d >= 100){ d-=100; str[1]++; }
	str[2] = '0';
	while(d >= 10){ d-=10; str[2]++; }
	str[3] = '0'+d;
	str[4]=0;
	return str;
}

uint8_t *Num5ToStr(uint32_t d)
{
	static uint8_t str[6];

	str[0] = '0';
	while(d >= 10000){ d-=10000; str[0]++; }
	str[1] = '0';
	while(d >= 1000){ d-=1000; str[1]++; }
	str[2] = '0';
	while(d >= 100){ d-=100; str[2]++; }
	str[3] = '0';
        while(d >= 10){ d-=10; str[3]++; }
        str[4] = '0'+d;
	str[5]=0;
	return str;
}





/*
// Тая функция връща 4 цифров стринг, като една от цифрите може да мига
// номера на мигащата цивра се задава като параметър
// при параметър 0 не мига нищо, - при 1 - първата цифра /най-лявата/, при 2 следващата и т.н.
char *Num4ToStr_BlinkOneDigit(unsigned int d, unsigned char blink_digit)
{
	static char str[5];               

	str[0] = '0';
	while(d >= 1000){ d-=1000; str[0]++; }
	if(blink_digit == 1 && blink_ticks&0x20) str[0] = ' ';

	str[1] = '0';
	while(d >= 100){ d-=100; str[1]++; }
	if(blink_digit == 2 && blink_ticks&0x20) str[1] = ' ';

	str[2] = '0';
	while(d >= 10){ d-=10; str[2]++; }
	if(blink_digit == 3 && blink_ticks&0x20) str[2] = ' ';

	str[3] = '0'+d;
	if(blink_digit == 4 && blink_ticks&0x20) str[3] = ' ';

	str[4]=0;
	return str;
}
*/


uint8_t *Num_uIntToStr(uint32_t d)
{
	static uint8_t str[6];

	str[0] = '0';
	while(d >= 10000){ d-=10000; str[0]++; }
	str[1] = '0';
	while(d >= 1000){ d-=1000; str[1]++; }
	str[2] = '0';
	while(d >= 100){ d-=100; str[2]++; }
	str[3] = '0';
	while(d >= 10){ d-=10; str[3]++; }
	str[4] = '0'+d;
	str[5]=0;
	return str;
}


uint8_t *NumHexToStr(uint8_t d)
{
	static uint8_t str[3];

	str[0] = GetHexDigit(d>>4);
	str[1] = GetHexDigit(d&0x0F);
	str[2]=0;
	return str;
}

uint8_t *U32HexToStr(uint32_t d)
{
  
	static uint8_t str[9];
        str[0]=GetHexDigit((uint8_t)(d>>28)&0x0000000F);
        str[1]=GetHexDigit((uint8_t)(d>>24)&0x0000000F);
	str[2]=GetHexDigit((uint8_t)(d>>20)&0x0000000F);
        str[3]=GetHexDigit((uint8_t)(d>>16)&0x0000000F);
        str[4]=GetHexDigit((uint8_t)(d>>12)&0x0000000F);
        str[5]=GetHexDigit((uint8_t)(d>>8)&0x0000000F);
        str[6]=GetHexDigit((uint8_t)(d>>4)&0x0000000F);
        str[7]=GetHexDigit((uint8_t)d&0x0000000F);
        //str[7]=HexToChar((char)d&0x0000000F);
        str[8]=0;
	return str;
}

/*
char HexToChar (unsigned char d)
{
  unsigned char result;
  switch (d)
  {
  case 0:
    result= '0';
    break;
  case 1:
    result= '1';
    break;
    case 2:
    result=  '2';
    break;
    case 3:
    result= '3';
    break;
    case 4:
    result= '4';
    break;
    case 5:
    result= '5';
    break;
    case 6:
    result= '6';
    break;
    case 7:
    result= '7';
    break;
    case 8:
    result= '8';
    break;
    case 9:
    result= '9';
    break;
    case 10:
    result= 'A';
    break;
    case 11:
    result= 'B';
    break;
    case 12:
    result= 'C';
    break;
    case 13:
    result= 'D';
    break;
    case 14:
    result= 'E';
    break;
    case 15:
    result= 'F';
    break;
  }
  return result;
}
*/
//ot chislo 0-15 vrashta simvol ot 0 do F
uint8_t GetHexDigit(uint8_t hex_digit)
{
	if(hex_digit < 10) return('0' + hex_digit);
	else return( '7' + hex_digit );
}

//ot simvol 0-F vrashta chislo 0-15
uint8_t CharToHex (uint8_t ch)
{
  uint8_t ret;
  if (ch<='9') ret=(ch-'0');
  else ret=(ch-'7');
  return ret;
}

uint8_t CharToHex_ (uint8_t ch)
{
  uint8_t ret;
  if((ch>='0') && (ch<='9')) ret=ch-'0';
  switch (ch)
  {
  case 'A':
    ret=10;
    break;
  case 'a':
    ret=10;
    break;  
  case 'B':
    ret=11;
    break;
  case 'b':
    ret=11;
    break;
  case 'C':
    ret=12;
    break;
  case 'c':
    ret=12;
    break;
  case 'D':
    ret=13;
    break;
  case 'd':
    ret=13;
    break;
  case 'E':
    ret=14;
    break;
  case 'e':
    ret=14;
    break;
  case 'F':
    ret=15;
    break;
  case 'f':
    ret=15;
    break;
  }
  return ret;
}

const uint8_t *OnOffString(uint8_t status)
{
	if(status) return " ON";
	else return "OFF";
}

const uint8_t *YesNo(uint8_t d)
{
	if(d) return "YES";
	else return " NO";
}


const uint8_t *YesNo2(uint8_t d)
{
	if(d) return " YES ";
	else return " NO ";
}

uint8_t CharToInt (uint8_t ch)
{
  if (ch>47)  return ch-48;
  else return 0;
}



