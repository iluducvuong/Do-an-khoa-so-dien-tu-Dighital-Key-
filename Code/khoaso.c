#include <khoaso.h>
#use delay(clock=20000000)
#use rs232(baud=9600,xmit=PIN_C6,rcv=PIN_C7,stream=GSM)
#define sensor PIN_C0
#define LCD_ENABLE_PIN  PIN_D5                       
#define LCD_RS_PIN PIN_D6 
#define LCD_RW_PIN PIN_D7
#define LCD_DATA4 PIN_B4
#define LCD_DATA5 PIN_B5
#define LCD_DATA6 PIN_B6
#define LCD_DATA7 PIN_B7
#include <lcd.c>
const char key[16] ={'1', '4', '7', '*','2', '5', '8', '0','3', '6', '9', '#',' ', ' ', ' ', ' '};
void quetcot(unsigned char col)
{
        output_high(pin_a0);
        output_high(pin_a1);
        output_high(pin_a2);
        output_high(pin_a3);
        output_high(pin_a4);
        output_high(pin_a5);
        output_high(pin_e0);
        output_high(pin_e1);
        if(col==0)output_low(pin_a4);
        if(col==1)output_low(pin_a5);
        if(col==2)output_low(pin_e0);
        if(col==3)output_low(pin_e1);
}
unsigned char quetphim()
{ 
  unsigned char c=0,r=0xFF;
  for (c=0;c<4;c++)
  {
   quetcot(c);
   while (input(pin_a3)==0) r=c*4+0;
   while (input(pin_a2)==0) r=c*4+1;
   while (input(pin_a1)==0) r=c*4+2;
   while (input(pin_a0)==0) r=c*4+3;
  }
  return r;
}
void khoitao()
{
   output_high(pin_c5);
   printf("AT");
   putc(13);
   delay_ms(500);
   printf("ATE0");
   putc(13);
   delay_ms(500);
   printf("AT&3");
   putc(13);
   delay_ms(500);   
   printf("AT+CSCS=\"GSM\"");
   putc(13);
   delay_ms(500);
   printf("AT+CMGF=1");
   putc(13);
   delay_ms(500);
   printf("AT+CNMI=2,1,0,0,0");
   putc(13);
   delay_ms(500);
}
void baodong()
{
   printf("ATD%c%c%c%c%c%c%c%c%c%c;",read_eeprom(0x10),read_eeprom(0x11),read_eeprom(0x12),read_eeprom(0x13),read_eeprom(0x14),read_eeprom(0x15),read_eeprom(0x16),read_eeprom(0x17),read_eeprom(0x18),read_eeprom(0x19));
   putc(13);
   delay_ms(15000);
   printf("ATH");
   putc(13);
   output_low(pin_c5);
   delay_ms(5000);
}
void main()
{
   int a=0,sai=0,count=0,dmk=0,solan=0;
   char mk[6]={},new1[6]={},new2[6]={};
   unsigned char phim;
   /*for(int i=0;i<=5;i++)
   {      
      write_eeprom(0x00+i,0x31+i);
   }
   write_eeprom(0x010,0x30);
   write_eeprom(0x011,0x39);
   write_eeprom(0x012,0x32);
   write_eeprom(0x013,0x33);
   write_eeprom(0x014,0x35);
   write_eeprom(0x015,0x30);
   write_eeprom(0x016,0x30);
   write_eeprom(0x017,0x38);
   write_eeprom(0x018,0x33);
   write_eeprom(0x019,0x33);*/
   lcd_init();
   lcd_putc("Nhap mat khau:");
   while(TRUE)
   {
      output_high(pin_c4);
      phim=quetphim();
      if(phim!=0xFF && phim!=12 && phim!=13 && phim!=14 && phim!=15)
      {
       delay_ms(5);
       if(phim!=0xFF && phim!=12 && phim!=13 && phim!=14 && phim!=15)
       {
          if (a==0)
          {
            mk[0]=key[phim];
            lcd_gotoxy(6,2);
            printf(lcd_putc,"%c",key[phim]);
            delay_ms(300);
            lcd_gotoxy(6,2);
            lcd_putc("*");
          }
          if (a==1)
          {
            mk[1]=key[phim];
            lcd_gotoxy(7,2);
            printf(lcd_putc,"%c",key[phim]);
            delay_ms(300);
            lcd_gotoxy(7,2);
            lcd_putc("*");
          }
          if (a==2)
          {
            mk[2]=key[phim];
            lcd_gotoxy(8,2);
            printf(lcd_putc,"%c",key[phim]);
            delay_ms(300);
            lcd_gotoxy(8,2);
            lcd_putc("*");
          }
          if (a==3)
          {
            mk[3]=key[phim];
            lcd_gotoxy(9,2);
            printf(lcd_putc,"%c",key[phim]);
            delay_ms(300);
            lcd_gotoxy(9,2);
            lcd_putc("*");
          }
          if (a==4)
          {
            mk[4]=key[phim];
            lcd_gotoxy(10,2);
            printf(lcd_putc,"%c",key[phim]);
            delay_ms(300);
            lcd_gotoxy(10,2);
            lcd_putc("*");
          }
          if (a==5)
          {
            mk[5]=key[phim];
            lcd_gotoxy(11,2);
            printf(lcd_putc,"%c",key[phim]);
            delay_ms(300);
            lcd_gotoxy(11,2);
            lcd_putc("*");
            count=1;
          }
          a++;
      }
      }
   if (count==1 && phim==15 && dmk==0)
   {
      delay_ms(5);
      if(count==1 && phim==15 && dmk==0)
      {
      if (mk[0]==read_eeprom(0x00) && mk[1]==read_eeprom(0x01) && mk[2]==read_eeprom(0x02) && mk[3]==read_eeprom(0x03) && mk[4]==read_eeprom(0x04) && mk[5]==read_eeprom(0x05))
      {
         lcd_putc('\f');
         lcd_putc("Cua da mo");
         lcd_gotoxy(10,2);
         lcd_putc("Moi vao!");
         output_high(pin_c3);
         a=0;
         delay_ms(2000);
         output_low(pin_c3);
         count=0;
      }
      else
      {
         lcd_putc('\f');
         lcd_putc("Mat khau sai");
         lcd_gotoxy(1,2);
         lcd_putc("Moi ban nhap lai");
         delay_ms(2000);
         lcd_putc('\f');
         lcd_putc("Nhap mat khau:");
         a=0;
         count=0;
         sai++;
      }
      }
   }
   if(phim==12)
   {
      DELAY_MS(5);
      if(phim==12)
      {
         if(a==1)
         {
            lcd_gotoxy(6,2);
            lcd_putc(" ");
            a--;
         }
         if(a==2)
         {
            lcd_gotoxy(7,2);
            lcd_putc(" ");
            a--;
         }
         if(a==3)
         {
            lcd_gotoxy(8,2);
            lcd_putc(" ");
            a--;
         }
         if(a==4)
         {
            lcd_gotoxy(9,2);
            lcd_putc(" ");
            a--;
         }
         if(a==5)
         {
            lcd_gotoxy(10,2);
            lcd_putc(" ");
            a--;
         }
         if(a>=6)
         {
            lcd_gotoxy(11,2);
            lcd_putc(" ");
            a=5;
         }
         
      }
   }
   if (sai==5)
   {
      output_high(pin_c5);
      a=0;
      count=0;
      khoitao();
      baodong();
      sai=0;
      output_low(pin_c5);
   }
      if(phim==14)
      {
         delay_ms(5);
         if(phim==14)
         {
            output_high(pin_c2);
            lcd_putc('\f');
            lcd_putc("Cua da dong");
            delay_ms(2000);
            output_low(pin_c2);
            lcd_putc('\f');
            lcd_putc("Nhap mat khau:");
            a=0;count=0;
         }
      }
      if(phim==13)
      {
         delay_ms(5);
         if(phim==13)
         {
            a=0;
            dmk=1;
            lcd_putc('\f');
            lcd_gotoxy(1,1);
            lcd_putc("Mat khau cu");
         }
      }
      if(count==1 && dmk==1 && phim==15 && solan==0)
      {
         delay_ms(5);
         if(count==1 && dmk==1 && phim==15 && solan==0)
         {
         if (mk[0]==read_eeprom(0x00) && mk[1]==read_eeprom(0x01) && mk[2]==read_eeprom(0x02) && mk[3]==read_eeprom(0x03) && mk[4]==read_eeprom(0x04) && mk[5]==read_eeprom(0x05))
         {
            lcd_putc('\f');
            lcd_gotoxy(1,1);
            lcd_putc("Mat khau moi");
            lcd_gotoxy(1,2);
            lcd_putc("Lan1:");
            solan=1;
            count=0;
            a=0;
         }
         else
         {
           lcd_putc('\f');
           lcd_putc("Sai mat khau");
           delay_ms(2000);
           lcd_putc('\f');
           lcd_putc("Nhap mat khau");
           sai++;
           count=0;
           a=0;
         }
         }
      }
      if(count==1 && solan==1 && phim==15)
      {
         delay_ms(5);
         if(count==1 && solan==1 && phim==15)
         {
            lcd_putc('\f');
            lcd_gotoxy(1,1);
            lcd_putc("Mat khau moi");
            lcd_gotoxy(1,2);
            lcd_putc("Lan2:");
            solan++;
            count=0;
            a=0;
         }
      }
      if(solan==1 && count==1)
      {
         new1[0]=mk[0];
         new1[1]=mk[1];
         new1[2]=mk[2];
         new1[3]=mk[3];
         new1[4]=mk[4];
         new1[5]=mk[5];
      }
      if(solan==2 && count==1)
      {
         new2[0]=mk[0];
         new2[1]=mk[1];
         new2[2]=mk[2];
         new2[3]=mk[3];
         new2[4]=mk[4];
         new2[5]=mk[5];
      }
      if(solan==2 && count==1 && phim==15)
      {
         delay_ms(5);
         if(solan==2 && count==1 && phim==15)
         {
         if(new1[0]==new2[0] && new1[1]==new2[1] && new1[2]==new2[2] && new1[3]==new2[3] && new1[4]==new2[4] && new1[5]==new2[5])
         {
            lcd_putc('\f');
            lcd_putc("Doi mat khau");
            lcd_gotoxy(7,2);
            lcd_putc("thanh cong");
            for(int k=0;k<=5;k++)
            {
               write_eeprom(0x00+k,new1[k]);
            }
            delay_ms(2000);
            lcd_putc('\f');
            lcd_putc("Nhap mat khau");
            a=0;
            count=0;
            dmk=0;
            solan=0;
            sai=0;
         }
         else
         {
            lcd_putc('\f');
            lcd_putc("Doi mat khau");
            lcd_gotoxy(9,2);
            lcd_putc("that bai");
            delay_ms(2000);\
            lcd_putc('\f');
            lcd_putc("Nhap mat khau");
            a=0;
            count=0;
            dmk=0;
            solan=0;
            sai=0;
         }
         }
      }
   }
 }
