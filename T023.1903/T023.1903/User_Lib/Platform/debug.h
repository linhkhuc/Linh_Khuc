/** @file    debug.h
  * @author  minhneo
  * @website git/minhngocha
  * @ide     Keil uVision
  * @brief   debug library for STM32
  */

#ifndef _DEBUG_H_
#define _DEBUG_H_

/*********************************************************************************
 * INCLUDE
 */
 
#include "stdint.h"
#include "stdio.h"
/*********************************************************************************
 * GLOBAL FUNCTION
 */
extern void bdg_printf(uint8_t debug_level);
extern char buf_debug[128];
extern uint8_t len_debug;
/*********************************************************************************
 * DEFINE
 */

/**
 * @brief Debug level
 */
#define DEBUG_LEVEL_OFF                                     0
#define DEBUG_LEVEL_ERROR                                   1
#define DEBUG_LEVEL_WARNING                                 2
#define DEBUG_LEVEL_INFO                                    3
#define DEBUG_COMMNET                                       100
/**
 * @brief Debug function
 */
#ifndef DEBUG_LEVEL
#define DEBUG_LEVEL DEBUG_LEVEL_OFF
#endif

#if(DEBUG_LEVEL == DEBUG_LEVEL_OFF)
#define DEBUG_ERROR(...)
#define DEBUG_WARNING(...)
#define DEBUG_INFO(...)
#define DEBUG(...)
#endif

#if(DEBUG_LEVEL == DEBUG_LEVEL_ERROR)
#define DEBUG(...)                               len_debug = sprintf(buf_debug, __VA_ARGS__);\
                                                 bdg_printf(DEBUG_COMMNET);
#define DEBUG_ERROR(...)                         len_debug = sprintf(buf_debug, __VA_ARGS__);\
                                                 bdg_printf(DEBUG_LEVEL_ERROR);
#define DEBUG_WRANING(...)
#define DEBUG_INFO(...)
#endif

#if(DEBUG_LEVEL == DEBUG_LEVEL_WARNING)
#define DEBUG(...)                               len_debug = sprintf(buf_debug, __VA_ARGS__);\
                                                 bdg_printf(DEBUG_COMMNET);
#define DEBUG_ERROR(...)                         len_debug = sprintf(buf_debug, __VA_ARGS__);\
                                                 bdg_printf(DEBUG_LEVEL_ERROR);
#define DEBUG_WARNING(...)                       len_debug = sprintf(buf_debug, __VA_ARGS__);\
                                                 bdg_printf(DEBUG_LEVEL_WARNING);
#define DEBUG_INFO(...)
#endif

#if(DEBUG_LEVEL == DEBUG_LEVEL_INFO)
#define DEBUG(...)                               len_debug = sprintf(buf_debug, __VA_ARGS__);\
                                                 bdg_printf(DEBUG_COMMNET);
#define DEBUG_ERROR(...)                         len_debug = sprintf(buf_debug, __VA_ARGS__);\
                                                 bdg_printf(DEBUG_LEVEL_ERROR);
#define DEBUG_WARNING(...)                       len_debug = sprintf(buf_debug, __VA_ARGS__);\
                                                 bdg_printf(DEBUG_LEVEL_WARNING);
#define DEBUG_INFOR(...)                         len_debug = sprintf(buf_debug, __VA_ARGS__);\
                                                 bdg_printf(DEBUG_LEVEL_INFO);
#endif

/*********************************************************************************
 * FUNCTION
 */

/**
 * @brief 
 * 
 * @param
 * @retval
 */
void DEBUG_Start(void);

/**
 * @brief 
 * 
 * @param
 * @retval
 */
void DEBUG_Clear(void);
#endif /* _DEBUG_H_ */
