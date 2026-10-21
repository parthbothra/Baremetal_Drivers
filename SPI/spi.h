#include<stdio.h>
#include<stdint.h>
typedef struct{
    uint32_t SPI_CR1;
    uint32_t SPI_CR2;
    uint32_t SPI_SR;
    uint32_t SPI_DR;
    uint32_t SPI_CRCPR;
    uint32_t SPI_RXCRCR;
    uint32_t SPI_TXCRCR;
    uint32_t SPI_I2SCFGR;
    uint32_t SPI_I2SPR;
}spi_regdef_t;

typedef struct{
    uint8_t SPI_devicemode;
    uint8_t SPI_busconfig;
    uint8_t SPI_sclspeed;
    uint8_t SPI_dff;
    uint8_t SPI_cpol;
    uint8_t SPI_cpha;
    uint8_t SPI_ssm;
}spi_config_t;

typedef struct{
    spi_regdef_t  *pSPIx;
    spi_config_t spiconfig;
    uint8_t *pTxBuffer;
    uint8_t *pRxBuffer;
    uint32_t TxLen;
    uint32_t RxLen;
    uint8_t TxState;
    uint8_t RxState;

}spi_handle_t;