/********************************************************************
 *********************************************************************
 *
 *  File        :  fe_port_mathh
 *
 *  Project     :  $ProjectName$
 *
 *  ProjectVer  :  $ProjectRevision$
 *
 *  Description :  NIG abstraction for maths functions header file
 *
 *  Notes       :
 *
 *  Author      :  $Author: rowe_j $
 *
 *  Status      :  $State: Exp $
 *
 *  Revision    :  $Revision: 1.5 $
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

#ifndef __FE_PORT_MATH_H_
#define __FE_PORT_MATH_H_

#include "fe_port_types.h"

#ifdef __cplusplus
extern "C"
{
#endif


NFE_UInt32 NFE_Port_MulDiv32(NFE_UInt32 numerator1, NFE_UInt32 numerator2, NFE_UInt32 divisor);

NFE_Int32  NFE_Port_Log10fix(NFE_UInt32 x, NFE_UInt8 precision);


#ifdef __cplusplus
}
#endif


#endif /* __FE_PORT_MATH_H_ */

/*fe_port_math.h*/
