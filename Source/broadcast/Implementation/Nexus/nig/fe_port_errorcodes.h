/********************************************************************
 *********************************************************************
 *
 *  File        :  fe_port_errorcodes.h
 *
 *  Project     :  $ProjectName$
 *
 *  ProjectVer  :  $ProjectRevision$
 *
 *  Description :  NIG abstraction error defines header file
 *
 *  Notes       :
 *
 *  Author      :  $Author: rowe_j $
 *
 *  Status      :  $State: Exp $
 *
 *  Revision    :  $Revision: 1.3 $
 *
 *  Copyright   :  2006-2017 Arris Enterprises, LLC. All rights
 *                 reserved.
 *
 *                 This program is confidential and proprietary to
 *                 Arris Enterprises, LLC. (ARRIS), and may not be copied,
 *                 reproduced, modified, disclosed to others, published
 *                 or used, in whole or in part, without the express
 *                 prior permission of ARRIS.
 *
 *********************************************************************
 ********************************************************************/

/*!
******************************************************************************
**
** \file       fe_port_errorcodes.h
**
** Standard return codes:
**
** NFE_RETURN_OK           : The function completed successfully.
**
** NFE_ERROR_HEINOUS       : An underlying function returned an error.
**
** NFE_ERROR_NOT_INIT      : The driver is not in the correct initialisation
                             state.
**
** NFE_ERROR_PARAM         : A parameter value is incorrect.
**
** NFE_ERROR_NOT_SUPPORTED : The function is not supported in this
                             implementation of the driver.
**
** \author     James Bragg.
** \date       10/10/08
**
*****************************************************************************/

#ifndef __FE_PORT_ERRORCODES_H__
#define __FE_PORT_ERRORCODES_H__

#include "fe_port_types.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*!
\typedef NFE_ERRORCODE
\brief   An enumeration that defines the possible error codes
*/
typedef enum _tag_NFE_ERRORCODE
{
   NFE_RETURN_OK                    = 0,   /*!< Standard types */
   NFE_ERROR_NOT_INIT,
   NFE_ERROR_PARAM,
   NFE_ERROR_MEMORY,
   NFE_ERROR_HEINOUS,
   NFE_ERROR_STANDBY,
   NFE_ERROR_UNEXPECTED_RETURN,
   NFE_ERROR_NOT_SUPPORTED,
   NFE_ERROR_TASK_ID,                      /*!< OS related errors */
   NFE_ERROR_NOT_SUSPENDED,
   NFE_ERROR_LOCKED,
   NFE_ERROR_DISABLED,
   NFE_ERROR_CONTROL,
   NFE_ERROR_HEAP_ID,
   NFE_ERROR_QUEUE_ID,
   NFE_ERROR_QUEUE_NAME,
   NFE_ERROR_QUEUE_FULL,
   NFE_ERROR_NO_MESSAGE,
   NFE_ERROR_TIMER_ID,
   NFE_ERROR_TIMER_NAME,
   NFE_ERROR_TIMEOUT,
   NFE_ERROR_TIMER,
   NFE_ERROR_MUTEX_ID,
   NFE_ERROR_MUTEX_NAME,
   NFE_ERROR_SEM_ID,
   NFE_ERROR_SEM_NAME,
   NFE_ERROR_ISR_NOT_INSTALLED,
   NFE_ERROR_ISR_ALREADY_INSTALLED,
   NFE_ERROR_OPEN,                         /*!< Device related errors */
   NFE_ERROR_NOT_OPEN,
   NFE_ERROR_CLOSE,
   NFE_ERROR_BUSY,
   NFE_ERROR_ABORT,
   NFE_ERROR_BUFFER_OVERFLOW,              /*!< Buffer related errors */
   NFE_ERROR_BUFFER_FULL,
   NFE_ERROR_NO_DATA,
   NFE_ERROR_FULL,
   NFE_ERROR_DATA,
   NFE_ERROR_BUF,
   NFE_ERROR_BUFF_TOO_SMALL,
   NFE_ERROR_BUFFER_LOCKED,
   NFE_ERROR_TOO_MUCH_DATA,
   NFE_ERROR_UTIL_BUFFER_EMPTY,
   NFE_ERROR_UTIL_BUF_NOT_FULL,
   NFE_ERROR_UTIL_BUF_NOT_EMPTY,
   NFE_ERROR_LIST_EMPTY,                   /*!< List related errors */
   NFE_ERROR_LIST_FULL,
   NFE_ERROR_NOT_FOUND,
   NFE_ERROR_PROPERTY_NOT_FOUND,           /*!< Property related errors */
   NFE_ERROR_PROPERTY_NOT_WRITEABLE,
   NFE_ERROR_PROPERTY_NOT_READABLE,
   NFE_ERROR_BAD_HANDLE,                   /*!< AV Driver errors */
   NFE_ERROR_BAD_POSITION,
   NFE_ERROR_BAD_SIZE,
   NFE_ERROR_BAD_PROPERTIES,
   NFE_ERROR_BAD_SRC_HANDLE,
   NFE_ERROR_BAD_DEST_HANDLE,
   NFE_ERROR_REGION_SIZE,
   NFE_ERROR_REGION_OVERLAP,
   NFE_ERROR_REGION_NOT_VISIBLE,
   NFE_ERROR_BAD_OFFSCREEN_HANDLE,
   NFE_ERROR_BAD_ONSCREEN_HANDLE,
   NFE_ERROR_NO_CURSOR,
   NFE_ERROR_BAD_PLANES,
   NFE_ERROR_NOT_ACTIVE,
   NFE_ERROR_NO_AUDIO_PLAYING,
   NFE_ERROR_NO_AUDIO,
   NFE_ERROR_NO_STREAM,
   NFE_ERROR_VIDEO_NOT_PLAYING,
   NFE_ERROR_VIDEO_NOT_PAUSED,
   NFE_ERROR_NO_VIDEO,
   NFE_ERROR_NO_PCR_PLAY,
   NFE_ERROR_INVALID_COORDINATES,
   NFE_ERROR_NO_FRAME_BUFFERED,
   NFE_ERROR_INVALID_SCALING,
   NFE_ERROR_BAD_PTS,
   NFE_ERROR_EXPIRED,
   NFE_ERROR_HARDWARE,
   NFE_ERROR_UNSUPPORTED_FORMAT,
   NFE_ERROR_ROWOP,                        /*!< Graphics errors */
   NFE_ERROR_BATCH,
   NFE_ERROR_PLAY,                         /*!< Teletext errors */
   NFE_ERROR_NO_CLIP_PLAYING,              /*!< PCM errors */
   NFE_ERROR_NO_CLIP_PAUSED,
   NFE_ERROR_INVALID_CLIP,
   NFE_ERROR_CARD_REMOVED,                 /*!< Card driver errors */
   NFE_ERROR_CARD_ERR,
   NFE_ERROR_CARD_COMMS,
   NFE_ERROR_BAD_PID,                      /*!< TSI errors */
   NFE_ERROR_BAD_PES_TYPE,
   NFE_ERROR_INVALID_PES_TYPE,
   NFE_ERROR_NO_DEMUX,
   NFE_ERROR_NO_DESCRAMBLER,
   NFE_ERROR_BAD_PESID,
   NFE_ERROR_NO_FILTER,
   NFE_ERROR_BAD_FILTER,
   NFE_ERROR_BAD_FILTER_SIZE,
   NFE_ERROR_BAD_OFFSET,
   NFE_ERROR_TOO_MANY_EVENTS,
   NFE_ERROR_BAD_EVENT,
   NFE_ERROR_NO_RESOURCE,
   NFE_ERROR_BAD_DESID,
   NFE_ERROR_BAD_PCR_ID,
   NFE_ERROR_DEREGISTER,                   /*!< RCU/FPKey errors */
   NFE_ERROR_FLASH_BAD_ADDR,               /*!< Flash errors */
   NFE_ERROR_FLASH_SECTORS,
   NFE_ERROR_FLASH_BAD_SECTORS,
   NFE_ERROR_FLASH_UNPROTECT,
   NFE_ERROR_FLASH_PROTECT,
   NFE_ERROR_FLASH_ERASE,
   NFE_ERROR_FLASH_PROG,
   NFE_ERROR_RECORD,                       /*!< NVM errors */
   NFE_ERROR_SUBRECORD,
   NFE_ERROR_SAME,
   NFE_ERROR_CORRUPT,
   NFE_ERROR_SCAN,                         /*!< FE errors */
   NFE_ERROR_NO_CHANNEL_PLAN,
   NFE_ERROR_ROUTE_UNSUPPORTED,            /*!< AV route errors */
   NFE_ERROR_NO_SERVICE,                   /*!< DVB subtitle errors */
   NFE_ERROR_NOT_STARTED,
   NFE_ERROR_NOT_STOPPED,
   NFE_ERROR_INVALID_PID,
   NFE_ERROR_INVALID_ID,
   NFE_ERROR_MULTIPLE_PTS,
   NFE_ERROR_DISCONTINUITY,
   NFE_ERROR_PTS_LATE,
   NFE_ERROR_MAX_OPENS_EXCEEDED,           /*!< PVR related errors */
   NFE_ERROR_MAX_SPEED_EXCEEDED,
   NFE_ERROR_MIN_SPEED_EXCEEDED,
   NFE_ERROR_OFFSET_EXCEEDED,
   NFE_ERROR_ALREADY_STARTED,
   NFE_ERROR_ALREADY_STOPPED,
   NFE_ERROR_ALREADY_INIT,                 /* Modem related error codes */
   NFE_LAST_ERROR_CODE                     /*!< THIS MUST ALWAYS BE THE LAST ERROR
                                            CODE */
} NFE_ERRORCODE;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __FE_PORT_ERRORCODES_H__ */

/*fe_port_errorcodes.h*/
