#include<xc.h>
#include"can_header.h"



void main(void) {
    

    
   TRISBbits.RB0 = 0;   /* RB0 is connected to LED */
   PORTBbits.RB0 = 0;   /* LED off*/



  System_Init();     /* Initializing Interrupts and all */
   CAN_Init();        /* Initializing CAN */
   CAN_set_baud(250); /* Setting Baud rate as 250 kbps */
   
   CAN_RX_Config();   /* Initializing CAN RX */
   
   



  while(1)
   {

      if(CAN_RX_FLAG)
       {
           CAN_RX_FLAG = 0;
           CAN_Read();
           led_blink();
           if (CAN_RX_ID== 0x100)
           {
               if(CAN_RX_Buff[0] == 0xaa)
                    CAN_Send_msg(1,8,0x5f,"Received");  /* Transmitting the data whatever received */
           }
       }
           

   }
    return;
}



/* Interrupt Service Routine */
void __interrupt() ISR1()
{
    if(PIR3bits.RXB0IF) /* Checking CAN RX Interrupt Flag */
    {
        //PORTBbits.RB1 = ~PORTBbits.RB1;     /* Toggle LED1 */
        PIR3bits.RXB0IF = 0;                /* Clearing RX Interrupt Flag */
        CAN_RX_FLAG = 1;                    /* Setting the Flag */
        led_blink();
    }
}