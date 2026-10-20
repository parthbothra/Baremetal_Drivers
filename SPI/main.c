#include<stdio.h>
#include<stdint.h>
#include "spi.h"

//Bus mode
#define SPI_BUS_CONFIG_FD 0
#define SPI_BUS_CONFIG_HD 1
#define SPI_BUS_CONFIG_SIMPLEX_RXONLY 2

//dff mode
#define SPI_DFF_8BITS 0
#define SPI_DFF_16BITS 1


//API 
void SPI_periclockcontrol(spi_regdef_t *pSPIx,uint8_t Enordi);

void SPI_init(spi_handle_t *pSPIhandle){
uint32_t temreg = 0;
//1.Config device mode
temreg |= (pSPIhandle->spiconfig.SPI_devicemode <<2);

//2.Comfig the bus config
if(pSPIhandle->spiconfig.SPI_busconfig == SPI_BUS_CONFIG_FD){
    temreg &= ~(1<<15);

}
else if(pSPIhandle->spiconfig.SPI_busconfig == SPI_BUS_CONFIG_HD){
    temreg |= (1<<15);
}
else if(pSPIhandle->spiconfig.SPI_busconfig == SPI_BUS_CONFIG_SIMPLEX_RXONLY){
    temreg &= ~(1<<15);
    temreg |= (1<<10);
}
//3. Config the spi clock
pSPIhandle->spiconfig.SPI_sclspeed = pSPIhandle->spiconfig.SPI_sclspeed << 3;
temreg |= pSPIhandle->spiconfig.SPI_sclspeed;

//4. Config the dff
if(pSPIhandle->spiconfig.SPI_dff == SPI_DFF_8BITS){
    temreg |= (0<<11);
}
else{
    temreg &= ~(1<<11);
}

//5.config the cpol
if(pSPIhandle->spiconfig.SPI_cpol == 1){
    temreg |= (1<<1);
}
else{
    temreg &= ~(1<<1);
}

//6.config the cpha
if(pSPIhandle->spiconfig.SPI_cpha == 1){
    temreg |= (1<<0);
}
else{
    temreg &= ~(1<<0);
}

//7.config the ssm
if(pSPIhandle->spiconfig.SPI_ssm == 1){
    temreg |= (1<<9);
}
else{
    temreg &= ~(1<<9);
}
}

void SPI_deinit(spi_regdef_t *pSPIx);


void SPI_senddata(spi_regdef_t *pSPIx,uint8_t *pTXBuffer,uint32_t len){
    while(len > 0){
        //1.wait until TXE is set
        while(!(pSPIx->SPI_SR & (1<<1)));
        //2. check the dff bit
        if(pSPIx->SPI_CR1 & (1<<11)){
            //16bit dff
            pSPIx->SPI_DR = *((uint16_t*)pTXBuffer);
            len--;
            len--;
            (uint16_t*)pTXBuffer++;

        }
        else{
            //8bit dff
            pSPIx->SPI_DR = *pTXBuffer;
            len--;
            pTXBuffer++;
        }
    }
        
    
}


void SPI_receivedata(spi_regdef_t *pSPIx,uint8_t *pRXBuffer,uint32_t len){
    while(len > 0){
        //1.wait until RXE is set
        while(!(pSPIx->SPI_SR & (1<<0)));
        //2. check the dff bit
        if(pSPIx->SPI_CR1 & (1<<11)){
            //16bit dff
            *((uint16_t*)pRXBuffer) = pSPIx->SPI_DR;
            len--;
            len--;
            (uint16_t*)pRXBuffer++;

        }
        else{
            //8bit dff
            *pRXBuffer = pSPIx->SPI_DR;
            len--;
            pRXBuffer++;
        }
    }
}


//SPI IRQ configuration and ISR handling
uint8_t SPI_SendDataIT(spi_handle_t *pspihandle,uint8_t *pTxBuffer,uint8_t Len){

}