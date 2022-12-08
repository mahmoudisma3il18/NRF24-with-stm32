/*
Author : Mahmoud Ismail
Date   : 11/9/2022
*/

#ifndef _NRF_H_
#define _NRF_H_

/*----------------------------- Includes ----------------------------------*/
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_gpio.h"


/*------------------------ Global Varaibles ----------------------------------*/

extern SPI_HandleTypeDef hspi1;


/*-------------------------- Definitions --------------------------------------*/


/* Private defines -----------------------------------------------------------*/
#define LED_Pin GPIO_PIN_13
#define LED_GPIO_Port GPIOC
#define CSN_Pin GPIO_PIN_0
#define CSN_GPIO_Port GPIOB
#define CE_Pin GPIO_PIN_1
#define CE_GPIO_Port GPIOB

#define  NRF_Handler &hspi1

/* Memory Map */
#define CONFIG_REG      0x00
#define EN_AA_REG       0x01
#define EN_RXADDR_REG   0x02
#define SETUP_AW_REG    0x03
#define SETUP_RETR_REG  0x04
#define RF_CH_REG       0x05
#define RF_SETUP_REG    0x06
#define STATUS_REG      0x07
#define OBSERVE_TX_REG  0x08
#define CD_REG          0x09
#define RX_ADDR_P0_REG  0x0A
#define RX_ADDR_P1_REG  0x0B
#define RX_ADDR_P2_REG  0x0C
#define RX_ADDR_P3_REG  0x0D
#define RX_ADDR_P4_REG  0x0E
#define RX_ADDR_P5_REG  0x0F
#define TX_ADDR_REG     0x10
#define RX_PW_P0_REG    0x11
#define RX_PW_P1_REG    0x12
#define RX_PW_P2_REG    0x13
#define RX_PW_P3_REG    0x14
#define RX_PW_P4_REG    0x15
#define RX_PW_P5_REG    0x16
#define FIFO_STATUS_REG 0x17
#define DYNPD_REG	      0x1C
#define FEATURE_REG	    0x1D

/* Instruction Mnemonics */
#define R_REGISTER    0x00
#define W_REGISTER    0x20
#define REGISTER_MASK 0x1F
#define ACTIVATE      0x50
#define R_RX_PL_WID   0x60
#define R_RX_PAYLOAD  0x61
#define W_TX_PAYLOAD  0xA0
#define W_ACK_PAYLOAD 0xA8
#define FLUSH_TX      0xE1
#define FLUSH_RX      0xE2
#define REUSE_TX_PL   0xE3
#define NOP           0xFF


#define TRUE          0x01
#define FALSE         0x00

/*------------------------ Functions -----------------------------------------*/

/*
-Description : SPI Chip Select 
*/
void HAL_NRF24_CS_select(void);

/*
-Description : SPI Chip UnSelect 
*/
void HAL_NRF24_CS_unSelect(void);

/*
-Description : Chip Enable Activates RX or TX mode
*/
void HAL_NRF24_CE_enable(void);

/*
-Description : Chip Disable  RX or TX mode
*/
void HAL_NRF24_CE_disable(void);

/*
-Description : Send byte of data to speicfic register
*/
void HAL_NRF24_writeReg(uint8_t Reg,uint8_t Data);

/*
-Description : Send multiple byte of data to speicfic register
*/
void HAL_NRF24_writeRegMulti(uint8_t Reg , uint8_t *Data,uint8_t sizeOfData);

/*
-Description : Read byte of Data from specific Reg
*/
uint8_t HAL_NRF24_readReg(uint8_t Reg);

/*
-Description : Read multi bytes of Data from specific Reg
*/
void HAL_NRF24_readRegMulti(uint8_t Reg,uint8_t *Data,uint8_t sizeOfData);

/*
-Description : Send command to NRF
*/
void HAL_NRF24_sendCommand(uint8_t command);

/*
-Description : Intialize NRF
*/
void HAL_NRF24_init(void);

/*
-Description : Config Regitsers for TX mode
*/
void HAL_NRF24_TXModeConfig(uint8_t *Address,uint8_t Channel);

/*
-Description : Transmit Data through NRF
*/
void HAL_NRF24_transmitData(uint8_t *Data);

/*
-Description : Config Regitsers for RX mode
*/
void HAL_NRF24_RXModeConfig(uint8_t *Address,uint8_t Channel);

/*
-Description : Return True if data is available in FIFO, else returns FALSE
*/
uint8_t HAL_NRF24_isDataAvailable(uint8_t pipeNumber);

/*
-Description : Recive Data in buffer from NRF
*/
void HAL_NRF24_receiveData(uint8_t *Data);

/*
-Description : Reset Regitsers values
*/
void HAL_NRF24_resetRegister(uint8_t Reg);

#endif /* NRF24L01.h */