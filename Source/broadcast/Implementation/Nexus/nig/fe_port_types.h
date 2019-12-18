/********************************************************************
 *********************************************************************
 *
 *  File        :  fe_port_types.h
 *
 *  Project     :  $ProjectName$
 *
 *  ProjectVer  :  $ProjectRevision$
 *
 *  Description :  NIG abstraction for generic types header file
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
 *****************************************************************************
 **
 ** \file           fe_port_types.h
 **
 ** \par            Deduces core types from platform configuration.
 **
 ** \author         James Bragg
 **
 ** \date           10 October 2008
 **
 ** \note           Defines the common definitions accross the NIG module.
 **
 **
 *****************************************************************************
 */

#ifndef __FE_PORT_TYPES_H__
#define __FE_PORT_TYPES_H__

/* If using gnu c make 64bit values available by default. */
#ifdef   __GNUC__

/* Enable NFE_UInt64 support. */
#ifndef  NFE_PLATFORM_SUPPORTS_UINT_64
#define  NFE_PLATFORM_SUPPORTS_UINT_64
#endif

/* Enable NFE_Int64 support. */
#ifndef  NFE_PLATFORM_SUPPORTS_INT_64
#define  NFE_PLATFORM_SUPPORTS_INT_64
#endif

#endif

/* Unsigned int sizes */

/*! \def NFE_UNSIGNED_CHAR_SIZE
    Defines the size of an unsigned char.  */
#define  NFE_UNSIGNED_CHAR_SIZE      1

/*! \def NFE_UNSIGNED_SHORT_SIZE
    Defines the size of an unsigned short. */
#define  NFE_UNSIGNED_SHORT_SIZE     2

/*! \def NFE_UNSIGNED_INT_SIZE
    Defines the size of an unsigned int. */
#define  NFE_UNSIGNED_INT_SIZE       4

/*! \def NFE_UNSIGNED_LONG_SIZE
    Defines the size of an unsigned long. */
#define  NFE_UNSIGNED_LONG_SIZE      4

/*! \def NFE_UNSIGNED_LONG_LONG_SIZE
    Defines the size of an unsigned long long */
#define  NFE_UNSIGNED_LONG_LONG_SIZE 8

/* Signed int sizes */

/*! \def NFE_SIGNED_CHAR_SIZE
    Defines the size of a signed char. */
#define  NFE_SIGNED_CHAR_SIZE        1

/*! \def NFE_SIGNED_SHORT_SIZE
    Defines the size of a signed short. */
#define  NFE_SIGNED_SHORT_SIZE       2

/*! \def NFE_SIGNED_INT_SIZE
    Defines the size of a signed int. */
#define  NFE_SIGNED_INT_SIZE         4

/*! \def NFE_SIGNED_LONG_SIZE
    Defines the size of a signed long. */
#define  NFE_SIGNED_LONG_SIZE        4

/*! \def NFE_SIGNED_LONG_LONG_SIZE
    Defines the size of a signed long long. */
#define  NFE_SIGNED_LONG_LONG_SIZE   8

/*! \def NFE_TYPES_UINT_08_SIZE
    Specifies required byte size of an 8bit unsigned int. */
#define  NFE_TYPES_UINT_08_SIZE     1

/*! \def NFE_TYPES_UINT_16_SIZE
    Specifies required byte size of a 16bit unsigned int. */
#define  NFE_TYPES_UINT_16_SIZE     2

/*! \def NFE_TYPES_UINT_32_SIZE
    Specifies required byte size of a 32bit unsigned int. */
#define  NFE_TYPES_UINT_32_SIZE     4

/*! \def NFE_TYPES_UINT_64_SIZE
    Specifies required byte size of a 64bit unsigned int. */
#define  NFE_TYPES_UINT_64_SIZE     8

/*! \def NFE_TYPES_SINT_08_SIZE
    Specifies required byte size of an 8bit signed int. */
#define  NFE_TYPES_SINT_08_SIZE     1

/*! \def NFE_TYPES_SINT_16_SIZE
    Specifies required byte size of a 16bit signed int. */
#define  NFE_TYPES_SINT_16_SIZE     2

/*! \def NFE_TYPES_SINT_32_SIZE
    Specifies required byte size of a 32bit signed int. */
#define  NFE_TYPES_SINT_32_SIZE     4

/*! \def NFE_TYPES_SINT_64_SIZE
    Specifies required byte size of a 64bit signed int. */
#define  NFE_TYPES_SINT_64_SIZE     8

/****************************************************************************
 * Specified the names of the types.                                        *
 ***************************************************************************/

/*! \def NFE_TYPES_UINT_08_TYPEDEF
    Specifies the name of the 8bit unsigned integer type. */
#define  NFE_TYPES_UINT_08_TYPEDEF  NFE_UInt8

/*! \def NFE_TYPES_UINT_16_TYPEDEF
    Specifies the name of the 16bit unsigned integer type. */
#define  NFE_TYPES_UINT_16_TYPEDEF  NFE_UInt16

/*! \def NFE_TYPES_UINT_32_TYPEDEF
    Specifies the name of the 32bit unsigned integer type. */
#define  NFE_TYPES_UINT_32_TYPEDEF  NFE_UInt32

/*! \def NFE_TYPES_UINT_64_TYPEDEF
    Specifies the name of the 64bit unsigned integer type. */
#define  NFE_TYPES_UINT_64_TYPEDEF  NFE_UInt64

/*! \def NFE_TYPES_SINT_08_TYPEDEF
    Specifies the name of the 8bit signed integer type. */
#define  NFE_TYPES_SINT_08_TYPEDEF  NFE_Int8

/*! \def NFE_TYPES_SINT_16_TYPEDEF
    Specifies the name of the 16bit signed integer type. */
#define  NFE_TYPES_SINT_16_TYPEDEF  NFE_Int16

/*! \def NFE_TYPES_SINT_32_TYPEDEF
    Specifies the name of the 32bit signed integer type. */
#define  NFE_TYPES_SINT_32_TYPEDEF  NFE_Int32

/*! \def NFE_TYPES_SINT_64_TYPEDEF
    Specifies the name of the 64bit signed integer type. */
#define  NFE_TYPES_SINT_64_TYPEDEF  NFE_Int64

/*! \def NFE_TYPES_UCHAR_TYPEDEF
    Specifies the name of the unsigned character type. */
#define  NFE_TYPES_UCHAR_TYPEDEF    NFE_UChar

/*! \def NFE_TYPES_SCHAR_TYPEDEF
    Specifies the name of the signed character type. */
#define  NFE_TYPES_SCHAR_TYPEDEF    NFE_SChar

/*! \def NFE_TYPES_CHAR_TYPEDEF
    Specifies the name of the basic character type. */
#define  NFE_TYPES_CHAR_TYPEDEF     NFE_Char

/*! \def NFE_TYPES_STRING_TYPEDEF
    Specifies the name of the string type. */
#define  NFE_TYPES_STRING_TYPEDEF   NFE_String

/****************************************************************************
 * Define the types - Unsigned 8bit integer.                                *
 ***************************************************************************/

#ifdef  NFE_UINT_8
#undef  NFE_UINT_8
#endif

#define NFE_REQUIRED_SIZE              NFE_TYPES_UINT_08_SIZE

#if     NFE_UNSIGNED_CHAR_SIZE      == NFE_REQUIRED_SIZE
#define NFE_UINT_8 unsigned char
#elif   NFE_UNSIGNED_SHORT_SIZE     == NFE_REQUIRED_SIZE
#define NFE_UINT_8 unsigned short int
#elif   NFE_UNSIGNED_INT_SIZE       == NFE_REQUIRED_SIZE
#define NFE_UINT_8 unsigned int
#elif   NFE_UNSIGNED_LONG_SIZE      == NFE_REQUIRED_SIZE
#define NFE_UINT_8 unsigned long int
#elif   NFE_UNSIGNED_LONG_LONG_SIZE == NFE_REQUIRED_SIZE
#ifdef _MSC_VER
#define NFE_UINT_8 unsigned __int64
#else
#define NFE_UINT_8 unsigned long long int
#endif
#endif

#ifndef NFE_UINT_8
#error  UNABLE_TO_ASSIGN_NFE_UINT_8
#endif

/* Define Min & Max Values & cast macro */

/*! \def NFE_UINT8_CAST(x) Casts a value to a NFE_UInt8. */
#define  NFE_UINT8_CAST(x) ((NFE_UINT_8)(x))

/*! \def NFE_UINT8_MIN Represents the minimum value for a NFE_UInt8. */
#define  NFE_UINT8_MIN NFE_UINT8_CAST(0x00)

/*! \def NFE_UINT8_MAX Represents the maximum value for a NFE_UInt8. */
#define  NFE_UINT8_MAX NFE_UINT8_CAST(0xff)

/* Support legacy MIN and MAX defines and cast. */

#define NFE_UINT_8_CAST(x) NFE_UINT8_CAST(x)

#define NFE_UINT_8_MIN NFE_UINT8_MIN
#define NFE_UINT_8_MAX NFE_UINT8_MAX

#ifdef  NFE_TYPES_UINT_08_TYPEDEF
typedef NFE_UINT_8 NFE_TYPES_UINT_08_TYPEDEF;
#endif

#undef  NFE_REQUIRED_SIZE

/****************************************************************************
 * Define the types - Unsigned 16bit integer.                               *
 ***************************************************************************/

#ifdef  NFE_UINT_16
#undef  NFE_UINT_16
#endif

#define NFE_REQUIRED_SIZE              NFE_TYPES_UINT_16_SIZE

#if     NFE_UNSIGNED_CHAR_SIZE      == NFE_REQUIRED_SIZE
#define NFE_UINT_16 unsigned char
#elif   NFE_UNSIGNED_SHORT_SIZE     == NFE_REQUIRED_SIZE
#define NFE_UINT_16 unsigned short int
#elif   NFE_UNSIGNED_INT_SIZE       == NFE_REQUIRED_SIZE
#define NFE_UINT_16 unsigned int
#elif   NFE_UNSIGNED_LONG_SIZE      == NFE_REQUIRED_SIZE
#define NFE_UINT_16 unsigned long int
#elif   NFE_UNSIGNED_LONG_LONG_SIZE == NFE_REQUIRED_SIZE
#ifdef _MSC_VER
#define NFE_UINT_16 unsigned __int64
#else
#define NFE_UINT_16 unsigned long long int
#endif
#endif

#ifndef NFE_UINT_16
#error  UNABLE_TO_ASSIGN_NFE_UINT_16
#endif

/* Define min & max values, and cast macro */

/*! \def NFE_UINT16_CAST(x) Performs a cast to a NFE_UInt16. */
#define  NFE_UINT16_CAST(x) ((NFE_UINT_16)(x))

/*! \def NFE_UINT16_MIN Represents the minimum value for a NFE_UInt16. */
#define  NFE_UINT16_MIN NFE_UINT16_CAST(0x0000)
/*! \def NFE_UINT16_MAX Represents the maximum value for a NFE_UInt16. */
#define  NFE_UINT16_MAX NFE_UINT16_CAST(0xffff)

/* Support legacy min and max values and cast. */

#define NFE_UINT_16_CAST(x) NFE_UINT16_CAST(x)

#define NFE_UINT_16_MIN NFE_UINT16_MIN
#define NFE_UINT_16_MAX NFE_UINT16_MAX

#ifdef  NFE_TYPES_UINT_16_TYPEDEF
typedef NFE_UINT_16 NFE_TYPES_UINT_16_TYPEDEF;
#endif

#undef  NFE_REQUIRED_SIZE

/****************************************************************************
 * Define the types - Unsigned 32bit integer.                               *
 ***************************************************************************/

#ifdef  NFE_UINT_32
#undef  NFE_UINT_32
#endif

#define NFE_REQUIRED_SIZE              NFE_TYPES_UINT_32_SIZE

#if     NFE_UNSIGNED_CHAR_SIZE      == NFE_REQUIRED_SIZE
#define NFE_UINT_32 unsigned char
#elif   NFE_UNSIGNED_SHORT_SIZE     == NFE_REQUIRED_SIZE
#define NFE_UINT_32 unsigned short int
#elif   NFE_UNSIGNED_INT_SIZE       == NFE_REQUIRED_SIZE
#define NFE_UINT_32 unsigned int
#elif   NFE_UNSIGNED_LONG_SIZE      == NFE_REQUIRED_SIZE
#define NFE_UINT_32 unsigned long int
#elif   NFE_UNSIGNED_LONG_LONG_SIZE == NFE_REQUIRED_SIZE
#ifdef _MSC_VER
#define NFE_UINT_32 unsigned __int64
#else
#define NFE_UINT_32 unsigned long long int
#endif
#endif

#ifndef NFE_UINT_32
#error  UNABLE_TO_ASSIGN_NFE_UINT_32
#endif

/* Define min & max values, and cast macro. */

/*! \def NFE_UINT32_CAST(x) Performs a cast to a NFE_UInt32. */
#define  NFE_UINT32_CAST(x) ((NFE_UINT_32)(x))

/*! \def NFE_UINT32_MIN Represents the minimum value for a NFE_UInt32. */
#define  NFE_UINT32_MIN NFE_UINT32_CAST(0x00000000)
/*! \def NFE_UINT32_MAX Represents the maximum value for a NFE_UInt32. */
#define  NFE_UINT32_MAX NFE_UINT32_CAST(0xffffffff)

/* Support legacy min and max values and cast. */

#define NFE_UINT_32_CAST(x) NFE_UINT32_CAST(x)

#define NFE_UINT_32_MIN NFE_UINT32_MIN
#define NFE_UINT_32_MAX NFE_UINT32_MAX

#ifdef  NFE_TYPES_UINT_32_TYPEDEF
typedef NFE_UINT_32 NFE_TYPES_UINT_32_TYPEDEF;
#endif

#undef  NFE_REQUIRED_SIZE

/****************************************************************************
 * Define the types - Unsigned 64bit integer.                               *
 ***************************************************************************/

#ifdef  NFE_UINT_64
#undef  NFE_UINT_64
#endif

#define NFE_REQUIRED_SIZE              NFE_TYPES_UINT_64_SIZE

#if     NFE_UNSIGNED_CHAR_SIZE      == NFE_REQUIRED_SIZE
#define NFE_UINT_64 unsigned char
#elif   NFE_UNSIGNED_SHORT_SIZE     == NFE_REQUIRED_SIZE
#define NFE_UINT_64 unsigned short int
#elif   NFE_UNSIGNED_INT_SIZE       == NFE_REQUIRED_SIZE
#define NFE_UINT_64 unsigned int
#elif   NFE_UNSIGNED_LONG_SIZE      == NFE_REQUIRED_SIZE
#define NFE_UINT_64 unsigned long int
#elif   NFE_UNSIGNED_LONG_LONG_SIZE == NFE_REQUIRED_SIZE
#ifdef _MSC_VER
#define NFE_UINT_64 unsigned __int64
#else
#define NFE_UINT_64 unsigned long long int
#endif
#endif

#ifndef NFE_UINT_64
#error  UNABLE_TO_ASSIGN_NFE_UINT_64
#endif

/* Define min & max values, and cast macro. */

/*! \def NFE_UINT64_CAST(x) Performs a cast to a NFE_UInt64. */
#define  NFE_UINT64_CAST(x) ((NFE_UINT_64)(x))

/*! \def NFE_UINT64_MIN Represents the minimum value for a NFE_UInt64. */
#define  NFE_UINT64_MIN NFE_UINT64_CAST(0x0000000000000000ULL)
/*! \def NFE_UINT64_MAX Represents the maximum value for a NFE_UInt64. */
#define  NFE_UINT64_MAX NFE_UINT64_CAST(0xffffffffffffffffULL)

/* Support legacy min and max values and cast. */

#define NFE_UINT_64_CAST(x) NFE_UINT16_CAST(x)

#define NFE_UINT_64_MIN NFE_UINT64_MIN
#define NFE_UINT_64_MAX NFE_UINT64_MAX

#ifdef  NFE_TYPES_UINT_64_TYPEDEF
typedef NFE_UINT_64 NFE_TYPES_UINT_64_TYPEDEF;
#endif

#undef  NFE_REQUIRED_SIZE

/****************************************************************************
 * Define the types - Signed 8bit integer.                                  *
 ***************************************************************************/

#ifdef  NFE_SINT_8
#undef  NFE_SINT_8
#endif

#define NFE_REQUIRED_SIZE            NFE_TYPES_SINT_08_SIZE

#if     NFE_SIGNED_CHAR_SIZE      == NFE_REQUIRED_SIZE
#define NFE_SINT_8 signed char
#elif   NFE_SIGNED_SHORT_SIZE     == NFE_REQUIRED_SIZE
#define NFE_SINT_8 signed short int
#elif   NFE_SIGNED_INT_SIZE       == NFE_REQUIRED_SIZE
#define NFE_SINT_8 signed int
#elif   NFE_SIGNED_LONG_SIZE      == NFE_REQUIRED_SIZE
#define NFE_SINT_8 signed long int
#elif   NFE_SIGNED_LONG_LONG_SIZE == NFE_REQUIRED_SIZE
#ifdef _MSC_VER
#define NFE_SINT_8 signed __int64
#else
#define NFE_SINT_8 signed long long int
#endif
#endif

#ifndef NFE_SINT_8
#error  UNABLE_TO_ASSIGN_NFE_SINT_8
#endif

/* Define min & max values, and cast macro. */

/*! \def NFE_INT8_CAST(x) Performs a cast to a NFE_Int8. */
#define  NFE_INT8_CAST(x) ((NFE_SINT_8)(x))

/*! \def NFE_INT8_MIN Represents the minimum value for a NFE_Int8. */
#define  NFE_INT8_MIN NFE_INT8_CAST(0x80)
/*! \def NFE_INT8_MAX Represents the maximum value for a NFE_Int8. */
#define  NFE_INT8_MAX NFE_INT8_CAST(0x7f)

/* Support legacy min and max values and cast. */

#define NFE_INT_8_CAST(x) NFE_INT8_CAST(x)

#define NFE_INT_8_MIN NFE_INT8_MIN
#define NFE_INT_8_MAX NFE_INT8_MAX

#ifdef  NFE_TYPES_SINT_08_TYPEDEF
typedef NFE_SINT_8 NFE_TYPES_SINT_08_TYPEDEF;
#endif

#undef  NFE_REQUIRED_SIZE

/****************************************************************************
 * Define the types - Signed 16bit integer.                                 *
 ***************************************************************************/

#ifdef  NFE_SINT_16
#undef  NFE_SINT_16
#endif

#define NFE_REQUIRED_SIZE            NFE_TYPES_SINT_16_SIZE

#if     NFE_SIGNED_CHAR_SIZE      == NFE_REQUIRED_SIZE
#define NFE_SINT_16 signed char
#elif   NFE_SIGNED_SHORT_SIZE     == NFE_REQUIRED_SIZE
#define NFE_SINT_16 signed short int
#elif   NFE_SIGNED_INT_SIZE       == NFE_REQUIRED_SIZE
#define NFE_SINT_16 signed int
#elif   NFE_SIGNED_LONG_SIZE      == NFE_REQUIRED_SIZE
#define NFE_SINT_16 signed long int
#elif   NFE_SIGNED_LONG_LONG_SIZE == NFE_REQUIRED_SIZE
#ifdef _MSC_VER
#define NFE_SINT_16 signed __int64
#else
#define NFE_SINT_16 signed long long int
#endif
#endif

#ifndef NFE_SINT_16
#error  UNABLE_TO_ASSIGN_NFE_SINT_16
#endif

/* Define min & max values, and cast macro. */

/*! \def NFE_INT16_CAST(x) Performs a cast to a NFE_Int16. */
#define  NFE_INT16_CAST(x) ((NFE_SINT_16)(x))

/*! \def NFE_INT16_MIN Represents the minimum value for a NFE_Int16. */
#define  NFE_INT16_MIN NFE_INT16_CAST(0x8000)
/*! \def NFE_INT16_MAX Represents the maximum value for a NFE_Int16. */
#define  NFE_INT16_MAX NFE_INT16_CAST(0x7fff)

/* Support legacy min and max values and cast. */

#define NFE_INT_16_CAST(x) NFE_INT16_CAST(x)

#define NFE_INT_16_MIN NFE_INT16_MIN
#define NFE_INT_16_MAX NFE_INT16_MAX

#ifdef  NFE_TYPES_SINT_16_TYPEDEF
typedef NFE_SINT_16 NFE_TYPES_SINT_16_TYPEDEF;
#endif

#undef  NFE_REQUIRED_SIZE

/****************************************************************************
 * Define the types - Signed 32bit integer.                                 *
 ***************************************************************************/

#ifdef  NFE_SINT_32
#undef  NFE_SINT_32
#endif

#define NFE_REQUIRED_SIZE            NFE_TYPES_SINT_32_SIZE

#if     NFE_SIGNED_CHAR_SIZE      == NFE_REQUIRED_SIZE
#define NFE_SINT_32 signed char
#elif   NFE_SIGNED_SHORT_SIZE     == NFE_REQUIRED_SIZE
#define NFE_SINT_32 signed short int
#elif   NFE_SIGNED_INT_SIZE       == NFE_REQUIRED_SIZE
#define NFE_SINT_32 signed int
#elif   NFE_SIGNED_LONG_SIZE      == NFE_REQUIRED_SIZE
#define NFE_SINT_32 signed long int
#elif   NFE_SIGNED_LONG_LONG_SIZE == NFE_REQUIRED_SIZE
#ifdef _MSC_VER
#define NFE_SINT_32 signed __int64
#else
#define NFE_SINT_32 signed long long int
#endif
#endif

#ifndef NFE_SINT_32
#error  UNABLE_TO_ASSIGN_NFE_SINT_32
#endif

/* Define min & max values, and cast macro. */

/*! \def NFE_INT32_CAST(x) Performs a cast to a NFE_Int32. */
#define  NFE_INT32_CAST(x) ((NFE_SINT_32)(x))

/*! \def NFE_INT32_MIN Represents the minimum value for a NFE_Int32. */
#define  NFE_INT32_MIN NFE_INT32_CAST(0x80000000)
/*! \def NFE_INT32_MAX Represents the maximum value for a NFE_Int32. */
#define  NFE_INT32_MAX NFE_INT32_CAST(0x7fffffff)

/* Support legacy min and max values and cast. */

#define NFE_INT_32_CAST(x) NFE_INT32_CAST(x)

#define NFE_INT_32_MIN NFE_INT32_MIN
#define NFE_INT_32_MAX NFE_INT32_MAX

#ifdef  NFE_TYPES_SINT_32_TYPEDEF
typedef NFE_SINT_32 NFE_TYPES_SINT_32_TYPEDEF;
#endif

#undef  NFE_REQUIRED_SIZE

/****************************************************************************
 * Define the types - Signed 64bit integer.                                 *
 ***************************************************************************/

#ifdef  NFE_SINT_64
#undef  NFE_SINT_64
#endif

#define NFE_REQUIRED_SIZE            NFE_TYPES_SINT_64_SIZE

#if     NFE_SIGNED_CHAR_SIZE      == NFE_REQUIRED_SIZE
#define NFE_SINT_64 signed char
#elif   NFE_SIGNED_SHORT_SIZE     == NFE_REQUIRED_SIZE
#define NFE_SINT_64 signed short int
#elif   NFE_SIGNED_INT_SIZE       == NFE_REQUIRED_SIZE
#define NFE_SINT_64 signed int
#elif   NFE_SIGNED_LONG_SIZE      == NFE_REQUIRED_SIZE
#define NFE_SINT_64 signed long int
#elif   NFE_SIGNED_LONG_LONG_SIZE == NFE_REQUIRED_SIZE
#ifdef _MSC_VER
#define NFE_SINT_64 signed __int64
#else
#define NFE_SINT_64 signed long long int
#endif
#endif

#ifndef NFE_SINT_64
#error  UNABLE_TO_ASSIGN_NFE_SINT_64
#endif

/*! \def NFE_INT64_CAST(x) Performs a cast to a NFE_Int64. */
#define  NFE_INT64_CAST(x) ((NFE_SINT_64)(x))

/*! \def NFE_INT64_MIN Represents the minimum value for a NFE_Int64. */
#define  NFE_INT64_MIN NFE_INT64_CAST(0x8000000000000000LL)
/*! \def NFE_INT64_MAX Represents the maximum value for a NFE_Int64. */
#define  NFE_INT64_MAX NFE_INT64_CAST(0x7fffffffffffffffLL)

/* Support legacy min and max values and cast. */

#define NFE_INT_64_CAST(x) NFE_INT64_CAST(x)

#define NFE_INT_64_MIN NFE_INT64_MIN
#define NFE_INT_64_MAX NFE_INT64_MAX

#ifdef  NFE_TYPES_SINT_64_TYPEDEF
typedef NFE_SINT_64 NFE_TYPES_SINT_64_TYPEDEF;
#endif

#undef  NFE_REQUIRED_SIZE

/****************************************************************************
 * Define the types - unsigned character.                                   *
 ***************************************************************************/
typedef unsigned char NFE_TYPES_UCHAR_TYPEDEF;

/****************************************************************************
 * Define the types - signed character.                                     *
 ***************************************************************************/
typedef signed char   NFE_TYPES_SCHAR_TYPEDEF;

/****************************************************************************
 * Define the types - default character.                                    *
 ***************************************************************************/
typedef char          NFE_TYPES_CHAR_TYPEDEF;

/****************************************************************************
 * Define the types - string.                                               *
 ***************************************************************************/
#define NFE_String    char*
#define NFE_STRING_NULL ((NFE_String)(NFE_NULL))

/****************************************************************************
 * Define the types - boolean.                                              *
 ***************************************************************************/
/*!
\typedef NFE_Int32 NFE_Bool
\brief             Represents truth values.
 **/
typedef  NFE_Int32 NFE_Bool;

/*! def  NFE_TRUE_VALUE  The value for true. */
#define  NFE_TRUE_VALUE  (0==0)
/*! def  NFE_FALSE_VALUE The value for true. */
#define  NFE_FALSE_VALUE (!(NFE_TRUE_VALUE))

/*! \def NFE_TRUE  Defines boolean true. */
#define  NFE_TRUE  ((NFE_Bool)(NFE_TRUE_VALUE))
/*! \def NFE_FALSE Defines boolean false. */
#define  NFE_FALSE ((NFE_Bool)(NFE_FALSE_VALUE))

/****************************************************************************
 * Define the types - void.                                              *
 ***************************************************************************/

/*! \def NFE_Void          Defines void in the namespace for consistency. */
#define  NFE_Void          void

/*! \def NFE_VOID(x)       Performs a cast to a NFE_Void* */
#define  NFE_VOID(x)       ((NFE_Void *)(x))

/*! \def NFE_VOID_REF(x)   Performs a cast to a NFE_Void** */
#define  NFE_VOID_REF(x)   ((NFE_Void **)(x))

#ifdef __cplusplus
/*! \def NFE_NULL          Defines the platform NULL reNFErence. */
#define  NFE_NULL          (0)
#else
/*! \def NFE_NULL          Defines the platform NFE_Void* NULL reNFErence. */
#define  NFE_NULL          NFE_VOID(0)
#endif

#endif /* not __NFE_PORT_TYPES_H__ */

/*fe_port_types.h*/
