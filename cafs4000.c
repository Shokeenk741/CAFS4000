#include <stdio.h>
#include <sys/types.h> // open
#include <sys/stat.h>  // open
#include <fcntl.h>     // open
#include <unistd.h>    // read/write usleep
#include <stdlib.h>    // exit
#include <inttypes.h>  // uint8_t, etc
#include <linux/i2c-dev.h> // I2C bus definitions
#include <sys/ioctl.h>
#include <inttypes.h>  // uint8_t, etc

int fd;
int address = 0x50;

float flow()
{

	if (ioctl(fd, I2C_SLAVE, address) < 0) {
		 printf("Error: Couldn't find device on address!\n");
	}
	uint8_t readBuf[2];
	if (read(fd, readBuf, 2) != 2) {
      		perror("Read conversion failure");
	}
   	float val = ((readBuf[0] << 8) | readBuf[1])/100.00;

	return val;
}

int main() {

  if ((fd = open("/dev/i2c-1", O_RDWR)) < 0) {
    printf("Error: Couldn't open device! %d\n", fd);
  }



  while(1){

	printf("flow %f\n",flow());
        usleep(50000);

   }



  return 0;

}

/*
#include"IIC_Master.h"
#define SDA PA0
#define SCL PA1
Unsigned int IIC_RX_Buf[5],IIC_TX_Buf[5];
bit ErrorBit;

Void I2C_Init(void)
{
    SDA_INPUT=0;
    SCL_INPUT=0;
    SDA=1;
    SCL=1;
}

 
Void I2C_Start(void){
    SDA=1;
    Delay_Us(1);
    SCL=1;
    Delay_Us(1);
    SDA=0;
    Delay_Us(1);
    SCL=0;
    Delay_Us(1);
    
}
 
void I2C_Stop(void)
{
    SCL=0;
    Delay_Us(1);
    SDA=0;
    Delay_Us(1);
    SCL=1;
    Delay_Us(1);
    SDA=1;
    Delay_Us(1);
}
//------------------------------------------------ -------------------------------
void I2C_ACK(void)
{
    SDA=0;
    Delay_Us(1);
    SCL=1;
    Delay_Us(1);
    SCL=0;
    Delay_Us(1);
}
//------------------------------------------------ -------------------------------
void I2C_NoAck(void)
{
    SDA=1;
    Delay_Us(1);
    SCL=1;
    Delay_Us(1);
    SCL=0;
    Delay_Us(1);
}
//------------------------------------------------ -------------------------------
Unsigned int I2C_ReadByte(void)
{
    Unsigned int ucValue=0;
    Unsigned int ucIndex;
   
    
    SDA=1;
    Delay_Us(1);
    SDA_INPUT=1;
    Delay_Us(1);
    for (ucIndex = 0; ucIndex < 8; ucIndex++ ) {
        ucValue <<= 1;
        SCL=0;
        Delay_Us(1);
        SCL=1;
        Delay_Us(1);
        if(IIC_DAT==1)
        {
          ucValue = ucValue |0x01;
            
        }
      else
        { 
         ucValue = ucValue & 0xfe;
            
        }
        Delay_Us(1);
        SCL=0;
        Delay_Us(1);
    }
    SDA_INPUT=0;
    Delay_Us(1);
    return ucValue;
//WillSDAset as output
}
//------------------------------------------------ -------------------------------
void I2C_WriteByte( unsigned int ucData )
{
    u8i;
    for( i = 0; i < 8; i++ ) {
        SCL=0;
        Delay_Us(1);
        if((ucData & 0x80) == 0x80) {
            SDA=1;
            Delay_Us(1);
        }
        else
        {
            SDA=0;
            Delay_Us(1);
        }
        SCL=1;
        Delay_Us(1);
        SCL=0;
        Delay_Us(1);
        ucData <<= 1;
    }
    SCL=1;
    Delay_Us(1);
    ErrorBit = IIC_DAT;
    Delay_Us(1);
    SCL=0;
    Delay_Us(1);
}
void iic_master_proc(void) {
 
    Unsigned int count=5,i;
    I2C_Init();
    I2C_Start();
    I2C_WriteByte(0xa1);
    for(i = 0;i < count;i++)
    {
    //Write address 0XA1
        IIC_RX_Buf[i] = I2C_ReadByte();
        if(i < (count -1))
            I2C_ACK();
        else
            I2C_NoAck();
    }
    I2C_Stop();
}

*/
