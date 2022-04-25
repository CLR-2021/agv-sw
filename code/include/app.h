/******************************************************************************
 * @file    app.h
 * @author  Mahmoud Karam (ma.karam272@gmail.com)
 * @brief   Types and APIs for application \ref app.c
 * @version 1.0.0
 * @date    2022-03-20
 * @copyright Copyright (c) 2022
 ******************************************************************************/
#ifndef APP_H
#define APP_H

/*----------------------------------------------------------------------------*/
/*                               TYPEDEFs                                     */
/*----------------------------------------------------------------------------*/

/******************************************************************************
 * @brief Navigation modes of the robot.
 * @details The robot can be in one of the following modes:
 * - Manual mode: The robot is controlled by the user either by the joystick or the mobile app.
 * - Autonomous mode: The robot moves autonomously by the sensors.
 *****************************************************************************/
typedef enum{
   AUTONOMOUS_MODE,                    /*!< Autonomous mode    */
   MANUAL_MODE,                        /*!< Manual mode        */
}NAVIGATION_MODE_t;

/******************************************************************************
 * @brief Different states of the robot.
 * @details The robot can be in one of the following states:
 * - Available: The robot is available to receive commands.
 * - Processing: The robot is processing a command (e.g. processing an order to get an item). 
 *               It is not available to receive commands until the current command is completed.
 * - Charging: The robot is charging. It is not available to receive commands until the charging is completed.
 * - Obstacle: The robot is in an obstacle. It is not available to receive commands until the obstacle is removed.
 *****************************************************************************/
typedef enum{
   ROBOT_AVAILABLE,                    /*!< Available state    */
   ROBOT_PROCESSING_OEDER,             /*!< Processing state   */
   ROBOT_CHARGING,                     /*!< Charging state     */
   ROBOT_OBSTACLE_AVOIDANCE,           /*!< Obstacle state     */
}ROBOT_STATE_t;

/******************************************************************************
 * @brief Availability of new orders.
 * @details The order can either be:
 * - Received: The order has been received and is ready to be processed.
 * - Not received: The order has not been received yet.
 *****************************************************************************/
typedef enum{
   NO_ORDER_RECIEVED,                  /*!< No order received  */
   ORDER_RECIEVED,                     /*!< Order received     */
}ORDER_AVAILABILITY_t;

/******************************************************************************
 * @brief Different states of the order.
 * @details The order can be in one of the following states:
 * - Processing: The order is being processed. The robot is on its way to the shelf to get the item.
 * - Out for delivery: The order is out for delivery. The robot has picked the shelf and is on its way to the client.
 * - Delivered: The order has been delivered to the client and is ready to be picked up.
 * - Going back: The client has picked the item, hence the robot will return the shelf to its original position.
 * - Returned: The robot has returned the shelf to its original position.
 *****************************************************************************/
typedef enum{
   ORDER_PROCESSING,                   /*!< Processing state                       */
   ORDER_OUT_FOR_DELIVER,              /*!< Out for delivery state                 */
   ORDER_DELIVERED,                    /*!< Delivered state                        */
   ORDER_GOING_BACK,                   /*!< Going back state                       */
   ORDER_RETURNED,                     /*!< Returned state                         */
}ORDER_TRACKING_t;

/******************************************************************************
 * @brief Pickup state of the item. If the client has picked up the item or not.
 * @details The item can be in one of the following states:
 * - Picked up: The item has been picked up by the client.
 * - Not picked up: The item has not been picked up by the client.
 *****************************************************************************/
typedef enum{
   CLIENT_PICKUP_NO,                   /*!< Not picked up state                    */
   CLIENT_PICKUP_YES,                  /*!< Picked up state                        */
}CLIENT_PICKUP_t;

/******************************************************************************
 * @brief Information of an order.
 * @details The order is composed of the following information:
 * - Order ID: The ID of the order.
 * - Availability: If the order has been received or not.
 * - Column: The column coordinate of the order.
 * - Row: The row coordinate of the order.
 * - Tracking state: states of the order, member of \ref ORDER_TRACKING_t.
 *****************************************************************************/
typedef struct{
   ORDER_AVAILABILITY_t    recievedOrNot;
   COLUMN_t                column;
   ROW_t                   row;
   ORDER_TRACKING_t        deliveryState;
}ORDER_INFO_t;

/******************************************************************************
 * @brief Orientation of the robot face.
 * @details The robot can be in one of the following orientations:
 * - North: The robot is facing north.
 * - East: The robot is facing east.
 * - South: The robot is facing south.
 * - West: The robot is facing west. 
 *****************************************************************************/
typedef enum{
   NORTH = 0,
   EAST  = 90,
   SOUTH = 180,
   WEST  = 270,
}ORIENTATION_t;






/*----------------------------------------------------------------------------*/
/*                               Prototypes                                   */
/*----------------------------------------------------------------------------*/
NAVIGATION_MODE_t checkAutoOrManualNavigation(void);
void autonomousMode(void);
void manualNavigation(void);
void monitorBattery(void);
void handleOrder(ORDER_INFO_t order);
ORDER_INFO_t getOrderInfo(void);
void navigate(COLUMN_t column, ROW_t row);
void navigateColumn(COLUMN_t column);
void navigateRow(const ROW_t row);
void modifyOrientation(const ORIENTATION_t orientation);
STATE_t onTrack(void);
STATE_t onLeftSmooth(void);
STATE_t onLeftSharp(void);
STATE_t onRightSmooth(void);
STATE_t onRightSharp(void);
void gotoNextJunction(void);
void sendPosition(const COLUMN_t column, const ROW_t row);
BOOL_t onJunction(void);
BOOL_t onObstacle(void);
void sendRobotState(const ROBOT_STATE_t robotState);
void sendOrderTrackInfo(const ORDER_TRACKING_t orderTrackInfo);
void waitForClientPickup(void);
STATE_t MASTER_PickItem(void);
u8 readSerial(void);
void avoidObstacle(void);


#endif     /* APP_H  */