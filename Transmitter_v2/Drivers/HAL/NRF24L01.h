/*
Author : Mahmoud Ismail
Date   : 19/12/2022
*/

#ifndef _NRF_H_
#define _NRF_H_

/*----------------------------- Includes ----------------------------------*/
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_gpio.h"
#include "stdint.h"


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
#define CONFIG_REG      (uint8_t)0x00  //Configuration Register
#define EN_AA_REG       (uint8_t)0x01  //Enable ‘Auto Acknowledgment’
#define EN_RXADDR_REG   (uint8_t)0x02  //Enabled RX Addresses
#define SETUP_AW_REG    (uint8_t)0x03  //Setup of Address Widths
#define SETUP_RETR_REG  (uint8_t)0x04  //Setup of Automatic Retransmission
#define RF_CH_REG       (uint8_t)0x05  //RF Channel
#define RF_SETUP_REG    (uint8_t)0x06  //RF Setup Register
#define STATUS_REG      (uint8_t)0x07  //Status Register
#define OBSERVE_TX_REG  (uint8_t)0x08  //Transmit observe register
#define CD_REG          (uint8_t)0x09  //Carrier Detect
#define RX_ADDR_P0_REG  (uint8_t)0x0A  //Receive address data pipe 0.
#define RX_ADDR_P1_REG  (uint8_t)0x0B  //Receive address data pipe 1.
#define RX_ADDR_P2_REG  (uint8_t)0x0C  //Receive address data pipe 2.
#define RX_ADDR_P3_REG  (uint8_t)0x0D  //Receive address data pipe 3.
#define RX_ADDR_P4_REG  (uint8_t)0x0E  //Receive address data pipe 4.
#define RX_ADDR_P5_REG  (uint8_t)0x0F  //Receive address data pipe 5.
#define TX_ADDR_REG     (uint8_t)0x10  //Transmit address.
#define RX_PW_P0_REG    (uint8_t)0x11  //Number of bytes recived in pipe 0
#define RX_PW_P1_REG    (uint8_t)0x12  //Number of bytes recived in pipe 1
#define RX_PW_P2_REG    (uint8_t)0x13  //Number of bytes recived in pipe 2
#define RX_PW_P3_REG    (uint8_t)0x14  //Number of bytes recived in pipe 3
#define RX_PW_P4_REG    (uint8_t)0x15  //Number of bytes recived in pipe 4
#define RX_PW_P5_REG    (uint8_t)0x16  //Number of bytes recived in pipe 5
#define FIFO_STATUS_REG (uint8_t)0x17  //FIFO Status Register
#define DYNPD_REG	      (uint8_t)0x1C  //Enable dynamic payload length
#define FEATURE_REG	    (uint8_t)0x1D  //Feature Register
#define ALL_REG         (uint8_t)0xFF  //To rese All regs

/* Instruction Mnemonics */
#define R_REGISTER    (uint8_t)0x00  //Read command
#define W_REGISTER    (uint8_t)0x20  //Write command
#define ACTIVATE      (uint8_t)0x50  //Lock/unlock exclusive features
#define R_RX_PL_WID   (uint8_t)0x60  //Read RX-payload width for the top 
#define R_RX_PAYLOAD  (uint8_t)0x61  //Read RX-payload
#define W_TX_PAYLOAD  (uint8_t)0xA0  //Write TX-payload
#define W_ACK_PAYLOAD (uint8_t)0xA8  //Used in RX mode.
#define FLUSH_TX      (uint8_t)0xE1  //Flush TX FIFO, used in TX mode 
#define FLUSH_RX      (uint8_t)0xE2  //Flush RX FIFO, used in RX mode
#define REUSE_TX_PL   (uint8_t)0xE3  //Reuse last transmitted payload
#define NOP           (uint8_t)0xFF  // No Operation


/*Register Mask Definitions*/
#define REGISTER_MASK (uint8_t)0x1F  //Mask bits[4:0] for CMD_RREG and CMD_WREG commands
#define CRC_MASK      (uint8_t)0x0C  //Mask for CRC Bits [3:2] in CONFIG Reg 
#define RF_PWR_MASK   (uint8_t)0x06  //Mask for RF Power Bits [2:1] in RF_SETUP Reg
#define RX_P_NO_MASK  (uint8_t)0x0E  //Mask for Data pipe number bits [3:1] in STATUS Reg
#define RF_DR_MASK    (uint8_t)0x08  //Mask for Air Data Rate bits [3] in RF_SETUP Reg
#define EN_RX_MASK    (uint8_t)0x3F  //Mask to enable data pipes bits [5:1] in EN_RXADDR Reg
#define RX_PW_MASK    (uint8_t)0x3F  //Mask for size of bytes in payload [5:1]
#define RX_FIFO_MASK  (uint8_t)0x03  //Mask for RX fifo Bits [1:0] in FIFO_STATUS Reg
#define TX_FIFO_MASK  (uint8_t)0x30  //Mask for TX Fifo bits [5:4] in FIFO_STATUS Reg
#define SETUP_AW_MASK (uint8_t)0x03  //Mask Address Widths  bits [1:0] in SETUP_AW Reg



/*Regitser Bits definitions */
#define PRIM_RX_BIT   (uint8_t)0x01 //RX,TX contro
#define PWR_UP_BIT    (uint8_t)0x02 //Power up or Power down in CONFIG Reg


#define TRUE          0x01
#define FALSE         0x00


/*------------------------- Enums ---------------------------------------------*/

//  Data Rate
typedef enum {
	DataRate_1Mbps = (uint8_t)0x00,
	DataRate_2Mbps = (uint8_t)0x08
}NRF24_DataRate;


// Output Power
typedef enum {
	OutputPower_18dBm = (uint8_t)0x00,
	OutputPower_12dBm = (uint8_t)0x02,
	OutputPower_6dBm  = (uint8_t)0x04,
	OutputPower_0dBm  = (uint8_t)0x06
}NRF24_OutputPower;


// Power Control
typedef enum {
	PowerControl_PowerUp   = (uint8_t)0x02,
	PowerControl_PowerDown = (uint8_t)0x00
}NRF24_PowerControl;


// Transceiver Mode
typedef enum {
	TransceiverMode_TX = (uint8_t)0x00,
	TransceiverMode_RX = (uint8_t)0x01
}NRF24_TransceiverMode;

/*
// RX Pipe Adresses and TX
typedef enum {
	
}
*/

// Status of RX Fifo
typedef enum {
	StatusRXFifo_Empty = (uint8_t)0x01, //RX FIFO empty. 
  StatusRXFifo_Full  = (uint8_t)0x02, // The RX FIFO is full
	StatusRXFifo_Data  = (uint8_t)0x00, // The RX FIFO contains data and available locations
	StatusRXFifo_Error = (uint8_t)0x03  // Impossible state: RX FIFO cannot be empty and full at the same time
}NRF24_StatusRXFifo;



// Status of the TX FIFO
typedef enum {
	StatusTXFifo_Data   = (uint8_t)0x00, // The TX FIFO contains data and available locations
	StatusTXFifo_Empty  = (uint8_t)0x01, // The TX FIFO is empty
	StatusTXFifo_Full   = (uint8_t)0x02, // The TX FIFO is full
	StatusTXFifo_Error  = (uint8_t)0x03  // Impossible state: TX FIFO cannot be empty and full at the same time
}NRF24_StatusTXFifo;


// Result of RX FIFO reading
typedef enum {
	nRF24_RX_PIPE0  = (uint8_t)0x00, // Packet received from the PIPE#0
	nRF24_RX_PIPE1  = (uint8_t)0x01, // Packet received from the PIPE#1
	nRF24_RX_PIPE2  = (uint8_t)0x02, // Packet received from the PIPE#2
	nRF24_RX_PIPE3  = (uint8_t)0x03, // Packet received from the PIPE#3
	nRF24_RX_PIPE4  = (uint8_t)0x04, // Packet received from the PIPE#4
	nRF24_RX_PIPE5  = (uint8_t)0x05, // Packet received from the PIPE#5
	nRF24_RX_EMPTY  = (uint8_t)0xff  // The RX FIFO is empty
} NRF24_RXResult;
	




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

/*
-Description : Set data rate to be sent
*/
void HAL_NRF24_setDataRate(NRF24_DataRate dataRate);

/*
-Description : Set Addreses width
*/
void HAL_NRF24_setAddrsWidth(uint8_t sizeOfAdressesWidthInBytes);


/*
-Description : Set Channel Number
*/
void HAL_NRF24_setRFChannel(uint8_t channelNumber);

/*
-Description : To power up or power down NRF
*/
void HAL_NRF24_setPowerMode(NRF24_PowerControl powerControl);


/*
-Description : to setup mode RX or TX
*/
void HAL_NRF24_setOperationalMode(NRF24_TransceiverMode transceiverMode);

/*
-Description : to setup output power of TX antetna
*/
void HAL_NRF24_setTXPower(NRF24_OutputPower outputPowerOfAntena);

#endif /* NRF24L01.h */