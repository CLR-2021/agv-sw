/******************************************************************************
 * @file    app_cfg.h
 * @author  Mahmoud Karam (ma.karam272@gmail.com)
 * @brief   Configuration header file for \ref app.c
 * @version 1.0.0
 * @date    2022-03-20
 * @copyright Copyright (c) 2022
 ******************************************************************************/
#ifndef APP_CFG_H
#define APP_CFG_H

#define NAVIGATION_MODE_BUTTON   BUTTON_0    /*!< Button used to navigate between modes is connected to BUTTON_0 */
#define ITEM_PICKUP_BUTTON       BUTTON_1    /*!< Button used to pick up an item is connected to BUTTON_1 */

#define NEON_LED  LED_0                      /*!< LED_0 is connected to the NEON_LED */

typedef enum{
   DEFAULT_COLUMN = 0,                       /*!< Default column of the robot at reset */
   CLIENT_COLUMN  = 0,                       /*!< Column of the client                 */
   CHARGER_COLUMN = 0,                       /*!< Column of the charger                */
}COLUMN_t;

typedef enum{
   CLIENT_ROW     = 0,                       /*!< Row of the client                    */
   DEFAULT_ROW    = 1,                       /*!< Default row of the robot at reset    */
   CHARGER_ROW    = 2,                       /*!< Row of the charger                   */
}ROW_t;

#define OBSTACLE_DISTANCE_THRESHOLD  100     /*!< Distance threshold in cm for obstacle avoidance */

#define NUM_OF_COLUMNS  2                    /*!< Number of columns on the arena       */
#define NUM_OF_ROWS     2                    /*!< Number of rows on the arena          */


#endif     /* APP_CFG_H  */