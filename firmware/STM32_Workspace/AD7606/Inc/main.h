/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define DB2_Pin GPIO_PIN_2
#define DB2_GPIO_Port GPIOE
#define DB3_Pin GPIO_PIN_3
#define DB3_GPIO_Port GPIOE
#define DB4_Pin GPIO_PIN_4
#define DB4_GPIO_Port GPIOE
#define DB5_Pin GPIO_PIN_5
#define DB5_GPIO_Port GPIOE
#define DB6_Pin GPIO_PIN_6
#define DB6_GPIO_Port GPIOE
#define USER_Btn_Pin GPIO_PIN_13
#define USER_Btn_GPIO_Port GPIOC
#define DEBUG1_Pin GPIO_PIN_9
#define DEBUG1_GPIO_Port GPIOF
#define MCO_Pin GPIO_PIN_0
#define MCO_GPIO_Port GPIOH
#define RMII_MDC_Pin GPIO_PIN_1
#define RMII_MDC_GPIO_Port GPIOC
#define RMII_REF_CLK_Pin GPIO_PIN_1
#define RMII_REF_CLK_GPIO_Port GPIOA
#define RMII_MDIO_Pin GPIO_PIN_2
#define RMII_MDIO_GPIO_Port GPIOA
#define RMII_CRS_DV_Pin GPIO_PIN_7
#define RMII_CRS_DV_GPIO_Port GPIOA
#define RMII_RXD0_Pin GPIO_PIN_4
#define RMII_RXD0_GPIO_Port GPIOC
#define RMII_RXD1_Pin GPIO_PIN_5
#define RMII_RXD1_GPIO_Port GPIOC
#define LD1_Pin GPIO_PIN_0
#define LD1_GPIO_Port GPIOB
#define DB7_Pin GPIO_PIN_7
#define DB7_GPIO_Port GPIOE
#define DB8_Pin GPIO_PIN_8
#define DB8_GPIO_Port GPIOE
#define DB9_Pin GPIO_PIN_9
#define DB9_GPIO_Port GPIOE
#define DB10_Pin GPIO_PIN_10
#define DB10_GPIO_Port GPIOE
#define DB11_Pin GPIO_PIN_11
#define DB11_GPIO_Port GPIOE
#define DB12_Pin GPIO_PIN_12
#define DB12_GPIO_Port GPIOE
#define DB13_Pin GPIO_PIN_13
#define DB13_GPIO_Port GPIOE
#define DB14_Pin GPIO_PIN_14
#define DB14_GPIO_Port GPIOE
#define DB15_Pin GPIO_PIN_15
#define DB15_GPIO_Port GPIOE
#define RMII_TXD1_Pin GPIO_PIN_13
#define RMII_TXD1_GPIO_Port GPIOB
#define LD3_Pin GPIO_PIN_14
#define LD3_GPIO_Port GPIOB
#define STLK_RX_Pin GPIO_PIN_8
#define STLK_RX_GPIO_Port GPIOD
#define STLK_TX_Pin GPIO_PIN_9
#define STLK_TX_GPIO_Port GPIOD
#define RESET_Pin GPIO_PIN_2
#define RESET_GPIO_Port GPIOG
#define BUSY_Pin GPIO_PIN_3
#define BUSY_GPIO_Port GPIOG
#define USB_PowerSwitchOn_Pin GPIO_PIN_6
#define USB_PowerSwitchOn_GPIO_Port GPIOG
#define USB_OverCurrent_Pin GPIO_PIN_7
#define USB_OverCurrent_GPIO_Port GPIOG
#define OS0_Pin GPIO_PIN_8
#define OS0_GPIO_Port GPIOC
#define OS1_Pin GPIO_PIN_9
#define OS1_GPIO_Port GPIOC
#define USB_SOF_Pin GPIO_PIN_8
#define USB_SOF_GPIO_Port GPIOA
#define USB_VBUS_Pin GPIO_PIN_9
#define USB_VBUS_GPIO_Port GPIOA
#define USB_ID_Pin GPIO_PIN_10
#define USB_ID_GPIO_Port GPIOA
#define USB_DM_Pin GPIO_PIN_11
#define USB_DM_GPIO_Port GPIOA
#define USB_DP_Pin GPIO_PIN_12
#define USB_DP_GPIO_Port GPIOA
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define OS2_Pin GPIO_PIN_10
#define OS2_GPIO_Port GPIOC
#define RANGE_Pin GPIO_PIN_11
#define RANGE_GPIO_Port GPIOC
#define CV_A_B_Pin GPIO_PIN_12
#define CV_A_B_GPIO_Port GPIOC
#define DEBUG2_Pin GPIO_PIN_1
#define DEBUG2_GPIO_Port GPIOD
#define RD_Pin GPIO_PIN_2
#define RD_GPIO_Port GPIOD
#define FRST_Pin GPIO_PIN_6
#define FRST_GPIO_Port GPIOD
#define CS_Pin GPIO_PIN_7
#define CS_GPIO_Port GPIOD
#define RMII_TX_EN_Pin GPIO_PIN_11
#define RMII_TX_EN_GPIO_Port GPIOG
#define RMII_TXD0_Pin GPIO_PIN_13
#define RMII_TXD0_GPIO_Port GPIOG
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB
#define LD2_Pin GPIO_PIN_7
#define LD2_GPIO_Port GPIOB
#define DB0_Pin GPIO_PIN_0
#define DB0_GPIO_Port GPIOE
#define DB1_Pin GPIO_PIN_1
#define DB1_GPIO_Port GPIOE
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/