/*
Author : Mahmoud Ismail
Date   : 19 / 12 / 2022
*/

/*--------------------------- Includes ---------------------------------------*/

#include "NRF24L01.h"


/*--------------------------- Functions --------------------------------------*/

/*
-Description : SPI Chip Select 
*/
void HAL_NRF24_CS_select(void)
{
	HAL_GPIO_WritePin(CSN_GPIO_Port,CSN_Pin,GPIO_PIN_RESET); // Select slave 
}


/*
-Description : SPI Chip UnSelect 
*/
void HAL_NRF24_CS_unSelect(void)
{
	HAL_GPIO_WritePin(CSN_GPIO_Port,CSN_Pin,GPIO_PIN_SET); // Unselect slave 
}


/*
-Description : Chip Enable Activates RX or TX mode
*/
void HAL_NRF24_CE_enable(void)
{
	HAL_GPIO_WritePin(CE_GPIO_Port,CE_Pin,GPIO_PIN_SET); // Enable NRF
}


/*
-Description : Chip Disable  RX or TX mode
*/
void HAL_NRF24_CE_disable(void)
{
	HAL_GPIO_WritePin(CE_GPIO_Port,CE_Pin,GPIO_PIN_RESET); // Disable NRF
}


/*
-Description : Send byte of data to speicfic register
*/
void HAL_NRF24_writeReg(uint8_t Reg,uint8_t Data)
{
	uint8_t buffer[2]; // buffer to hold data and register 
	buffer[0] = Reg | (1<<5); 
	buffer[1] = Data;
	
	//Pull CS low to select slave device 
	HAL_NRF24_CS_select();
	
	//Transmit Data and Regitser addreses
	HAL_SPI_Transmit(NRF_Handler,buffer,2,1000);
	
	//Pull CS High to realaese slave device
	HAL_NRF24_CS_unSelect();
	
	
}


/*
-Description : Send multiple byte of data to speicfic register
*/
void HAL_NRF24_writeRegMulti(uint8_t Reg , uint8_t *Data,uint8_t sizeOfData)
{
	uint8_t buffer; // buffer to hold data and register 
	buffer = Reg | (1<<5); 

	
	//Pull CS low to select slave device 
	HAL_NRF24_CS_select();
	
	//Transmit Data and Regitser addreses
	HAL_SPI_Transmit(NRF_Handler,&buffer,1,100);
	HAL_SPI_Transmit(NRF_Handler,Data,sizeOfData,1000);
	
	//Pull CS High to realaese slave device
	HAL_NRF24_CS_unSelect();
	
}


/*
-Description : Read byte of Data from specific Reg
*/
uint8_t HAL_NRF24_readReg(uint8_t Reg)
{
	uint8_t Data; // Varaible to Hold data
	
	//Pull CS low to select slave device 
	HAL_NRF24_CS_select();
	
	//Recive Data and Regitser addreses
	HAL_SPI_Transmit(NRF_Handler,&Reg,1,100);
	HAL_SPI_Receive(NRF_Handler,&Data,1,100);
	
	//Pull CS High to realaese slave device
	HAL_NRF24_CS_unSelect();
	
	return Data; 

}


/*
-Description : Read multi bytes of Data from specific Reg
*/
void HAL_NRF24_readRegMulti(uint8_t Reg,uint8_t *Data,uint8_t sizeOfData)
{
	
	
	//Pull CS low to select slave device 
	HAL_NRF24_CS_select();
	
	//Recive Data and Regitser addreses
	HAL_SPI_Transmit(NRF_Handler,&Reg,1,100);
	HAL_SPI_Receive(NRF_Handler,Data,sizeOfData,1000); // Returns data in pointer to char
	
	//Pull CS High to realaese slave device
	HAL_NRF24_CS_unSelect();
	

}


/*
-Description : Send command to NRF
*/
void HAL_NRF24_sendCommand(uint8_t command)
{
	
	
	//Pull CS low to select slave device 
	HAL_NRF24_CS_select();
	
	//Transmit Data and Regitser addreses
	HAL_SPI_Transmit(NRF_Handler,&command,1,100);
	
	//Pull CS High to realaese slave device
	HAL_NRF24_CS_unSelect();
	
}

/*
-Description : Reset Regitsers values
*/
void HAL_NRF24_resetRegister(uint8_t Reg)
{
	if (Reg == STATUS_REG)
	{
		HAL_NRF24_writeReg(STATUS_REG, 0x00);
	}

	else if (Reg == FIFO_STATUS_REG)
	{
		HAL_NRF24_writeReg(FIFO_STATUS_REG, 0x11);
	}

	else if (Reg == ALL_REG) 
	{
	HAL_NRF24_writeReg(CONFIG_REG, 0x08);
	HAL_NRF24_writeReg(EN_AA_REG, 0x3F);
	HAL_NRF24_writeReg(EN_RXADDR_REG, 0x03);
	HAL_NRF24_writeReg(SETUP_AW_REG, 0x03);
	HAL_NRF24_writeReg(SETUP_RETR_REG, 0x03);
	HAL_NRF24_writeReg(RF_CH_REG, 0x02);
	HAL_NRF24_writeReg(RF_SETUP_REG, 0x0E);
	HAL_NRF24_writeReg(STATUS_REG, 0x00);
	HAL_NRF24_writeReg(OBSERVE_TX_REG, 0x00);
	HAL_NRF24_writeReg(CD_REG, 0x00);
	uint8_t rx_addr_p0_def[5] = {0xE7, 0xE7, 0xE7, 0xE7, 0xE7};
	HAL_NRF24_writeRegMulti(RX_ADDR_P0_REG, rx_addr_p0_def, 5);
	uint8_t rx_addr_p1_def[5] = {0xC2, 0xC2, 0xC2, 0xC2, 0xC2};
	HAL_NRF24_writeRegMulti(RX_ADDR_P1_REG, rx_addr_p1_def, 5);
	HAL_NRF24_writeReg(RX_ADDR_P2_REG, 0xC3);
	HAL_NRF24_writeReg(RX_ADDR_P3_REG, 0xC4);
	HAL_NRF24_writeReg(RX_ADDR_P4_REG, 0xC5);
	HAL_NRF24_writeReg(RX_ADDR_P5_REG, 0xC6);
	uint8_t tx_addr_def[5] = {0xE7, 0xE7, 0xE7, 0xE7, 0xE7};
	HAL_NRF24_writeRegMulti(TX_ADDR_REG, tx_addr_def, 5);
	HAL_NRF24_writeReg(RX_PW_P0_REG, 0);
	HAL_NRF24_writeReg(RX_PW_P1_REG, 0);
	HAL_NRF24_writeReg(RX_PW_P2_REG, 0);
	HAL_NRF24_writeReg(RX_PW_P3_REG, 0);
	HAL_NRF24_writeReg(RX_PW_P4_REG, 0);
	HAL_NRF24_writeReg(RX_PW_P5_REG, 0);
	HAL_NRF24_writeReg(FIFO_STATUS_REG, 0x11);
	HAL_NRF24_writeReg(DYNPD_REG, 0);
	HAL_NRF24_writeReg(FEATURE_REG, 0);
	}
}


/*
-Description : Intialize NRF
*/
void HAL_NRF24_init(void)
{
	
	HAL_NRF24_CE_disable(); // Disable NRF before intlization 
	
	HAL_NRF24_resetRegister(ALL_REG); // Reset All Regs
	
	HAL_Delay(100);
	
	HAL_NRF24_writeReg(CONFIG_REG,0x00);
	
	HAL_NRF24_writeReg(EN_AA_REG,0x00); // Disable autoacknolgment
	
	HAL_NRF24_setRFChannel(0x00); // Channel number is choosen later
	
	HAL_NRF24_setDataRate(DataRate_250Kbps); // Air Data Rate : 2Mbps 
	
	HAL_NRF24_setAddrsWidth(5); // 5 Bytes width
	
	HAL_NRF24_writeReg(SETUP_RETR_REG,0x00); // Disable  Automatic Retransmission
	
	HAL_NRF24_CE_enable();  // Enable NRF after intlization 
	
}


/*
-Description : Config Regitsers for TX mode
*/
void HAL_NRF24_TXModeConfig(uint8_t *Address,uint8_t Channel)
{
	HAL_NRF24_CE_disable(); // Disable NRF before intlization 
	
	HAL_NRF24_setRFChannel(Channel); // Select the channel (0:6 bits of data)
	
	HAL_NRF24_setTXPower(OutputPower_0dBm); // 0ddBm max power
	
	HAL_NRF24_writeRegMulti(TX_ADDR_REG,Address,5); // Setup TX adresses
	
	HAL_NRF24_setOperationalMode(TransceiverMode_TX);
	
	HAL_NRF24_setPowerMode(PowerControl_PowerUp); //Power Up NRF
	
	HAL_NRF24_CE_enable(); // Enable NRF
}


/*
-Description : Transmit Data through NRF
*/
void HAL_NRF24_transmitData(uint8_t *Data)
{
	
	uint8_t cmd_to_send = W_TX_PAYLOAD;
	
	HAL_NRF24_CS_select();
	
	HAL_SPI_Transmit(NRF_Handler,&cmd_to_send,1,100); // Transmit Command
	
	HAL_SPI_Transmit(NRF_Handler,Data,32,1000); // Send 32 bytes of data
	
	HAL_NRF24_CS_unSelect();
	
	HAL_Delay(10);
	
	uint8_t fifoStatus = HAL_NRF24_readReg(FIFO_STATUS_REG); // Get fifo status of NRF
	
	if((fifoStatus & (1<<4)) && (!(fifoStatus &(1<<3)))) // To check that fifo is empty and data is sent
		{
			//cmd_to_send = FLUSH_TX;
			//HAL_NRF24_sendCommand(cmd_to_send);
			HAL_NRF24_resetRegister(FIFO_STATUS_REG); //  Reset FIFO
			HAL_GPIO_TogglePin(LED_GPIO_Port,LED_Pin); 
		}
			
}

/*
-Description : Config Regitsers for RX mode
*/
void HAL_NRF24_RXModeConfig(uint8_t *Address,uint8_t Channel)
{
	
	HAL_NRF24_CE_disable(); // Disable NRF before intlization 
	
	HAL_NRF24_resetRegister(STATUS_REG);
	
	HAL_NRF24_setRFChannel(Channel); // Select the channel (0:6 bits of data)
	
	uint8_t EN_RXADDRReg = HAL_NRF24_readReg(EN_RXADDR_REG);
	/*
	EN_RXADDRReg = EN_RXADDRReg | (1<<0);
	
	HAL_NRF24_writeReg(EN_RXADDR_REG,EN_RXADDRReg); // Enable Data pipe 1 
	
	HAL_NRF24_writeRegMulti(RX_ADDR_P0_REG,Address,5); // Setup RX Pipe1 adresses
	
	HAL_NRF24_writeReg(RX_PW_P0_REG,32); // 32 bytes payload
	
	*/
	
	EN_RXADDRReg = EN_RXADDRReg | (1<<2);
	
	HAL_NRF24_writeReg(EN_RXADDR_REG,EN_RXADDRReg); // Enable Data pipe 1 
	
	HAL_NRF24_writeRegMulti(RX_ADDR_P1_REG,Address,5); // Setup RX Pipe1 adresses
	
	HAL_NRF24_writeReg(RX_ADDR_P2_REG,'A');
	
	HAL_NRF24_writeReg(RX_PW_P2_REG,32); // 32 bytes payload
	
	HAL_NRF24_setOperationalMode(TransceiverMode_RX);
	
	HAL_NRF24_setPowerMode(PowerControl_PowerUp);
	
	HAL_NRF24_CE_enable(); // Enable NRF
	
}

/*
-Description : Return True if data is available in FIFO, else returns FALSE
*/
uint8_t HAL_NRF24_isDataAvailable(uint8_t pipeNumber)
{
	uint8_t statusReg = HAL_NRF24_readReg(STATUS_REG); // Read status Reg from NRF
	
	if((statusReg & (1<<6)) && (statusReg & (pipeNumber<<1))) // Chech if data availbe in fifo and in same pipe number
		{ 
			HAL_NRF24_writeReg(STATUS_REG,0x40); // Clear Fifo Flag
			HAL_GPIO_TogglePin(LED_GPIO_Port,LED_Pin);
			return TRUE;
		}
		
		return FALSE;
	
}

/*
-Description : Recive Data in buffer from NRF
*/
void HAL_NRF24_receiveData(uint8_t *Data)
{
	
	
//	HAL_NRF24_sendCommand(R_RX_PAYLOAD); // Write TX-payload: 1 – 32 bytes.
	
	uint8_t cmd_to_send = 0;
	
	HAL_NRF24_CS_select();
	
	cmd_to_send = R_RX_PAYLOAD;
	
	HAL_SPI_Transmit(NRF_Handler,&cmd_to_send,1,1000);
	
	HAL_SPI_Receive(NRF_Handler,Data,32,1000); // Send 32 bytes of data
	
	HAL_NRF24_CS_unSelect();
	
	HAL_Delay(1);
	
	cmd_to_send = FLUSH_RX;
	
	HAL_NRF24_sendCommand(cmd_to_send);
	
}



/*
-Description : Set data rate to be sent
*/
void HAL_NRF24_setDataRate(NRF24_DataRate dataRate)
{
	
	uint8_t reg;
	reg = HAL_NRF24_readReg(RF_SETUP_REG);
	reg &= (uint8_t)(~RF_DR_MASK);
	reg |= dataRate;
	HAL_NRF24_writeReg(RF_SETUP_REG,reg);

}


/*
-Description : Set Addreses width
*/
void HAL_NRF24_setAddrsWidth(uint8_t sizeOfAdressesWidthInBytes)
{
	HAL_NRF24_writeReg(SETUP_AW_REG,(uint8_t)(sizeOfAdressesWidthInBytes - 2U));
}


/*
-Description : Set Channel Number
*/
void HAL_NRF24_setRFChannel(uint8_t channelNumber)
{
	HAL_NRF24_writeReg(RF_CH_REG,channelNumber);
}


/*
-Description : To power up or power down NRF
*/
void HAL_NRF24_setPowerMode(NRF24_PowerControl powerControl)
{
	uint8_t reg;
	reg = HAL_NRF24_readReg(CONFIG_REG);
	
	if(powerControl == PowerControl_PowerUp)
		reg |= PWR_UP_BIT;
	else
		reg &= ~(PWR_UP_BIT);
	
	HAL_NRF24_writeReg(CONFIG_REG,reg);
	
}


/*
-Description : to setup mode RX or TX
*/
void HAL_NRF24_setOperationalMode(NRF24_TransceiverMode transceiverMode)
{
	uint8_t reg;
	reg = HAL_NRF24_readReg(CONFIG_REG);
	reg &= (uint8_t)(~PRIM_RX_BIT);
	reg |= (transceiverMode & PRIM_RX_BIT);
	HAL_NRF24_writeReg(CONFIG_REG,reg);
}


/*
-Description : to setup output power of TX antetna
*/

void HAL_NRF24_setTXPower(NRF24_OutputPower outputPowerOfAntena)
{
	uint8_t reg = HAL_NRF24_readReg(RF_SETUP_REG);
	reg &= ~(RF_PWR_MASK);
	reg |= outputPowerOfAntena;
	HAL_NRF24_writeReg(RF_SETUP_REG,reg);
}