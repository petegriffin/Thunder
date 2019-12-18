/********************************************************************
 *********************************************************************
 *
 *  File        :  nfe_control.h
 *
 *  Project     :  $ProjectName$
 *
 *  ProjectVer  :  $ProjectRevision$
 *
 *  Description :  NIG frontend control interface header file
 *
 *  Notes       :
 *
 *  Author      :  $Author: kumars6 $
 *
 *  Status      :  $State: Exp $
 *
 *  Revision    :  $Revision: 1.23 $
 *
 *  Copyright   :  (c) 2006-2017 Arris Enterprises, LLC. All rights
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

#ifndef __NFE_CONTROL_H_
#define __NFE_CONTROL_H_

#include "nfe_platform.h"

#ifdef __cplusplus
extern "C"
{
#endif

/*forward declare the following enum types to allow usage in control structure and union*/


/**   \brief Stream Type
   DVB-T2 stream type
*/
typedef enum _tag_NFE_DVBT2_C_StreamType
{
   NFE_DVBT2_C_STREAM_TYPE_TS    = 0,  /*!< Transport Stream only*/
   NFE_DVBT2_C_STREAM_TYPE_GS    = 1,  /*!< Generic Stream only*/
   NFE_DVBT2_C_STREAM_TYPE_TS_GS = 2   /*!< Mixed Transport and Generic Stream*/
} NFE_DVBT2_C_StreamType;


/**   \brief FEC Frame size
   DVB-T2 FEC frame size
*/
typedef enum _tag_NFE_DVBT2_C_FECType
{
   NFE_DVBT2_C_FEC_TYPE_LDPC_16K = 0,  /*!< Short FEC frame length*/
   NFE_DVBT2_C_FEC_TYPE_LDPC_64K = 1   /*!< Long FEC frame length*/
} NFE_DVBT2_C_FECType;


/**   \brief s1 Type
   DVB-T2 s1 signalling type
*/
typedef enum _tag_NFE_DVBT2_C_s1Type
{
   NFE_DVBT2_C_S1_TYPE_SISO      = 0,  /*!< Single I/p, Single O/p*/
   NFE_DVBT2_C_S1_TYPE_MISO      = 1,  /*!< Multiple I/p, single O/p*/
   NFE_DVBT2_C_S1_TYPE_NOT_DVBT2 = 2   /*!< Non-DVB-T2 type S1 signalling*/
} NFE_DVBT2_C_s1Type;


/**   \brief s2 Type
   DVB-T2 s2 signalling type (equivalent to FFT size)
*/
typedef enum _tag_NFE_DVBT2_C_s2Type
{
   NFE_DVBT2_C_S2_TYPE_2K_ANY    = 0,  /*!< 2K any guard*/
   NFE_DVBT2_C_S2_TYPE_8K_DVBT   = 1,  /*!< 8K DVBT guard*/
   NFE_DVBT2_C_S2_TYPE_4K_ANY    = 2,  /*!< 4K any guard*/
   NFE_DVBT2_C_S2_TYPE_1K_ANY    = 3,  /*!< 1K any guard*/
   NFE_DVBT2_C_S2_TYPE_16K_ANY   = 4,  /*!< 16K any guard*/
   NFE_DVBT2_C_S2_TYPE_32K_DVBT  = 5,  /*!< 32K DVBT guard*/
   NFE_DVBT2_C_S2_TYPE_8K_DVBT2  = 6,  /*!< 8K DVBT2 guard*/
   NFE_DVBT2_C_S2_TYPE_32K_DVBT2 = 7   /*!< 32K DVBT2 guard*/
} NFE_DVBT2_C_s2Type;


/**   \brief PAPR setting
   DVB-T2 Peak to Average Power Reduction setting
*/
typedef enum _tag_NFE_DVBT2_C_papr
{
   NFE_DVBT2_C_PAPR_NONE   = 0,  /*!< No Peak to Average Power Reduction*/
   NFE_DVBT2_C_PAPR_ACE    = 1,  /*!< Peak to Average Power Reduction with 'ace' scheme*/
   NFE_DVBT2_C_PAPR_TR     = 2,  /*!< Peak to Average Power Reduction with 'tr' scheme*/
   NFE_DVBT2_C_PAPR_TR_ACE = 3   /*!< Peak to Average Power Reduction with both 'ace' and 'tr' schemes*/
} NFE_DVBT2_C_papr;


/**   \brief Pilot Pattern
   DVB-T2 pilot pattern
*/
typedef enum _tag_NFE_DVBT2_C_PilotPattern
{
   NFE_DVBT2_C_PP1 = 0, /*!< Pilot Pattern 1*/
   NFE_DVBT2_C_PP2 = 1, /*!< Pilot Pattern 2*/
   NFE_DVBT2_C_PP3 = 2, /*!< Pilot Pattern 3*/
   NFE_DVBT2_C_PP4 = 3, /*!< Pilot Pattern 4*/
   NFE_DVBT2_C_PP5 = 4, /*!< Pilot Pattern 5*/
   NFE_DVBT2_C_PP6 = 5, /*!< Pilot Pattern 6*/
   NFE_DVBT2_C_PP7 = 6, /*!< Pilot Pattern 7*/
   NFE_DVBT2_C_PP8 = 7  /*!< Pilot Pattern 8*/
} NFE_DVBT2_C_PilotPattern;


/**   \brief PLP Type
   DVB-T2 Physical Layer Pipe type
*/
typedef enum _tag_NFE_DVBT2_C_PlpType
{
   NFE_DVBT2_C_PLP_TYPE_COMMON = 0, /*!< Common PLP type*/
   NFE_DVBT2_C_PLP_TYPE_DATA1  = 1, /*!< Data 1 PLP type*/
   NFE_DVBT2_C_PLP_TYPE_DATA2  = 2  /*!< Data 2 PLP type*/
} NFE_DVBT2_C_PlpType;


/**   \brief PLP PayloadType
   DVB-T2 Physical Layer Pipe payload type
*/
typedef enum _tag_NFE_DVBT2_C_PlpPayloadType
{
   NFE_DVBT2_C_PLP_PAYLOAD_TYPE_GFPS = 0, /*!< Generic Fixed-Length Packetised PLP payload*/
   NFE_DVBT2_C_PLP_PAYLOAD_TYPE_GCS  = 1, /*!< Generic Continuous Stream PLP payload*/
   NFE_DVBT2_C_PLP_PAYLOAD_TYPE_GSE  = 2, /*!< Generic Stream Encapsulation PLP payload*/
   NFE_DVBT2_C_PLP_PAYLOAD_TYPE_TS   = 3  /*!< Transport Stream PLP payload*/
} NFE_DVBT2_C_PlpPayloadType;


/**   \brief FFT size
   FFT size (for COFDM type signals)
*/
typedef enum _tag_NFE_C_FFTSize
{
   NFE_C_FFT_2K      = 0,  /*!< 2k  FFT*/
   NFE_C_FFT_4K      = 1,  /*!< 4k  FFT (for DVB-H)*/
   NFE_C_FFT_8K      = 2,  /*!< 8k  FFT*/
   NFE_C_FFT_16K     = 3,  /*!< 16k FFT (DVB-T2)*/
   NFE_C_FFT_32K     = 4,  /*!< 32k FFT (DVB-T2)*/
   NFE_C_FFT_1K      = 5,  /*!< 1k  FFT (DVB-T2)*/
   NFE_C_FFT_8K_EXT  = 6,  /*!< 8k  FFT extended (DVB-T2)*/
   NFE_C_FFT_16K_EXT = 7,  /*!< 16k FFT extended (DVB-T2)*/
   NFE_C_FFT_32K_EXT = 8,  /*!< 32k FFT extended (DVB-T2)*/
   NFE_C_FFT_AUTO    = 9   /*!< auto or unknown FFT size*/
} NFE_C_FFTSize;


/**   \brief Bandwidth
   Signal bandwidth (for COFDM type signals)
*/
typedef enum _tag_NFE_C_Bandwidth
{
   NFE_C_BW_8MHZ   = 0, /*!< 8MHz   bandwidth*/
   NFE_C_BW_7MHZ   = 1, /*!< 7MHz   bandwidth*/
   NFE_C_BW_6MHZ   = 2, /*!< 6MHz   bandwidth*/
   NFE_C_BW_5MHZ   = 3, /*!< 5MHz   bandwidth (DVB-T2)*/
   NFE_C_BW_10MHZ  = 4, /*!< 10MHz  bandwidth (DVB-T2)*/
   NFE_C_BW_1_7MHZ = 5  /*!< 1.7MHz bandwidth (DVB-T2)*/
} NFE_C_Bandwidth;


/**   \brief Guard Interval
   Guard Interval (for COFDM type signals)
*/
typedef enum _tag_NFE_C_Guardband
{
   NFE_C_GUARD_32     = 0, /*!< 1/32   guard interval*/
   NFE_C_GUARD_16     = 1, /*!< 1/16   guard interval*/
   NFE_C_GUARD_8      = 2, /*!< 1/8    guard interval*/
   NFE_C_GUARD_4      = 3, /*!< 1/4    guard interval*/
   NFE_C_GUARD_128    = 4, /*!< 1/128  guard interval (DVB-T2)*/
   NFE_C_GUARD_19_256 = 5, /*!< 19/128 guard interval (DVB-T2)*/
   NFE_C_GUARD_19_128 = 6, /*!< 19/256 guard interval (DVB-T2)*/
   NFE_C_GUARD_AUTO   = 7  /*!< auto or unknown guard interval*/
} NFE_C_Guardband;

typedef NFE_UInt32 NFE_C_CodeRate; /*!< defined as per NFE_CodeRate*/

typedef NFE_UInt32 NFE_C_Modulation; /*!< defined as per NFE_Modulation*/


/**   \brief Calibration Status
   Power Reporting Calibration Status (for US cable or DOCSIS type applications)
*/
typedef enum _tag_NFE_CalStatus
{
   NFE_CAL_BUSY = 0,             /*!< Calibration in progress*/
   NFE_CAL_COMPLETE,             /*!< Calibration complete*/
   NFE_CAL_FAIL_TUNE,            /*!< Calibration failed at tuning step*/
   NFE_CAL_FAIL_SETUP,           /*!< Calibration failed at setup step*/
   NFE_CAL_FAIL_INITIAL_SWEEP,   /*!< Calibration failed during initial sweep*/
   NFE_CAL_FAIL_SWEEP,           /*!< Calibration failed during power sweep*/
   NFE_CAL_FAIL_RFGAIN,          /*!< Calibration failed as rf gain is out of allowable range*/
   NFE_CAL_FAIL_NVRAM,           /*!< Calibration failed writing results to nvram*/
   NFE_CAL_FAIL_TEMPERATURE      /*!< Calibration failed as temperature is out of allowable range*/
}
NFE_CalStatus;


/**   \brief Calibration Type (Extended)
   Extended Power Reporting Calibration Type (for US cable or DOCSIS type applications)
*/
typedef enum _tag_NFE_ExtCalType
{
   NFE_EXTCAL_DS = 0,   /*!< downstream path calibration*/
   NFE_EXTCAL_USLOW,    /*!< upstream (low freq) path calibration*/
   NFE_EXTCAL_USHIGH,   /*!< upstream (high freq) path calibration*/
   NFE_EXTCAL_USMID2,   /*!< upstream (mid 2 freq) path calibration*/
   NFE_EXTCAL_USMID3,   /*!< upstream (mid 3 freq) path calibration*/
   NFE_EXTCAL_USMID4,   /*!< upstream (mid 4 freq) path calibration*/
   NFE_EXTCAL_UNKNOWN   /*!< unknown or unspecified calibration path*/
}
NFE_ExtCalType;

#define NFE_EXTCAL_USMID0  NFE_EXTCAL_USLOW
#define NFE_EXTCAL_USMID1  NFE_EXTCAL_USHIGH


/**   \brief Control Command
   Enum for any non - generic commands
   Not all will be applicable tO any given implementation
*/
typedef enum __tag_NFE_Control_Command
{
   NFE_Control_SetBERWindow = 1,       /*!< Sets the BER window */
   NFE_Control_SetSpiralSearch,        /*!< Enables/disables the spiral search */
   NFE_Control_GetSignalLevel,         /*!< Gets the current signa level*/
   NFE_Control_GetAttenuatorState,     /*!< Gets the current attenuator state (if applicable)*/
   NFE_Control_SetAttenuatorState,     /*!< Sets the current attenuator state (if applicable)*/
   NFE_Control_SetAGC,                 /*!< Sets the given AGC state (if applicable)*/
   NFE_Control_GetAGC,                 /*!< Gets the given AGC state (if applicable)*/
   NFE_Control_GetSetAGC,              /*!< Gets then sets the given AGC state (if applicable)*/
   NFE_Control_FreezeAGC,              /*!< Freezes the given AGC (if applicable)*/
   NFE_Control_GetLNAChipRev,          /*!< Gets the LNA chip revision (if applicable)*/
   NFE_Control_WriteToDemod,           /*!< Direct write to demodulator device*/
   NFE_Control_ReadFromDemod,          /*!< Direct read from demodulator device*/
   NFE_Control_GetStingerFSM,          /*!< Get 'Stinger' device finite state machine value (deprecated)*/
   NFE_Control_WriteToTuner,           /*!< Direct write to tuner device*/
   NFE_Control_ReadFromTuner,          /*!< Direct read from tuner device*/
   NFE_Control_SwitchXtalState,        /*!< Switch crystal setup*/
   NFE_Control_ReportEqualiserCoeffs,  /*!< Return equaliser corefficients (if applicable)*/
   NFE_Control_GetMultipathCondition,  /*!< Return general multipath condition metric*/
   NFE_Control_SetGPIO,                /*!< Set GPIO state (on frontend device)*/
   NFE_Control_GetGPIO,                /*!< Get GPIO state or value (on frontend device)*/
   NFE_Control_bcmWriteConfig,         /*!< Write Broadcom frontend config word*/
   NFE_Control_bcmReadConfig,          /*!< Read Broadcom frontend config word*/
   NFE_Control_enableTunerBufferedClk, /*!< Enable tuner o/p clock buffer (if applicable)*/
   NFE_Control_Calibrate,              /*!< Start FE power reporting calibration process*/
   NFE_Control_SetCalibrationData,     /*!< Set FE power reporting calibration data*/
   NFE_Control_GetCalibrationData,     /*!< Get FE power reporting calibration data*/
   NFE_Control_SelectInput,            /*!< Select RF i/p*/

   NFE_Control_GetDvbT2L1PreInfo,      /*!< DVB-T2 pre-L1 signalling info*/
   NFE_Control_GetDvbT2L1PostInfo,     /*!< DVB-T2 post-L1 signalling info*/
   NFE_Control_GetDvbT2PlpIds,         /*!< DVB-T2 PLP identifier list*/
   NFE_Control_GetDvbT2ActivePlpInfo,  /*!< DVB-T2 current PLP signalling info*/
   NFE_Control_CheckForNoDvbT2Signal,  /*!< check to see if DVB-T2 signal is present or not for early no lock decision*/
   NFE_Control_CheckForNoDvbTSignal,   /*!< check to see if DVB-T signal is present or not for early no lock decision*/

   NFE_Control_GetDieTemp,             /*!< Get frontend device temperature (if applicable)*/
   NFE_Control_GetSupplyVoltage,       /*!< Get frontend device supply voltage (if applicable - usually for Broadcom AVS-equipped devices only - in millivolts)*/

   NFE_Control_GetBERWindow,           /*!< Gets the BER current window in milliseconds*/
   NFE_Control_GetCurrUncorrErrs,      /*!< Gets current uncorrected errors from HW */

   NFE_Control_LastEntry
}
NFE_Control_Command;


/**   \brief Get Signal Level Argument
   Argument for Get Signal Level command
   Parameter struct for NFE_Control_GetSignalLevel
*/
typedef struct _tag_NFE_Control_GetSignalLevel_Arg
{
   NFE_UInt8 level; /*!< in 'CDI' units*/
}
NFE_Control_GetSignalLevel_Arg;


/**   \brief Attenuator State Argument
   Argument for Get/Set Attenuator State commands
   Parameter struct for NFE_Control_GetAttenuatorState
*/
typedef struct _tag_NFE_Control_AttenuatorState_Arg
{
   NFE_Bool on;
}
NFE_Control_AttenuatorState_Arg;


/**   \brief Get/Set AGC Argument
   Argument for Get/Set AGC commands
   Parameter struct for NFE_Control_SetAGC and NFE_Control_GetAGC
*/
typedef struct _tag_NFE_Control_GetSetAGC_Arg
{
   NFE_UInt8  agcId;    /*!< zero-indexed identifier of which AGC loop is being modified*/
   NFE_UInt32 agcVal;   /*!< encoding of value is device dependent*/
}
NFE_Control_GetSetAGC_Arg;


/**   \brief Freeze AGC Argument
   Argument for Freeze AGC command
   Parameter struct for NFE_Control_FreezeAGC
*/
typedef struct _tag_NFE_Control_FreezeAGC_Arg
{
   NFE_UInt8 agcId;  /*!< zero-indexed identifier of which AGC loop is being modified*/
   NFE_Bool  freeze; /*!< true = freeze, false = run*/
}
NFE_Control_FreezeAGC_Arg;


/**   \brief Get Chip Revision Argument
   Argument for Get Chip Revision command
   Parameter struct for NFE_Control_GetLNAChipRev and NFE_Control_GetTunerChipRev
*/
typedef struct _tag_NFE_Control_GetChipRev_Arg
{
   NFE_UInt32 chipRev; /*!< encoding is device and vendor specific*/
}
NFE_Control_GetChipRev_Arg;


/**   \brief Set BER Window Argument
   Argument for Set BER Window command
   Parameter struct for NFE_Control_SetBERWindow
*/
typedef struct _tag_NFE_Control_SetBERWindow_Arg
{
   NFE_UInt32 berWindow; /*!< in whole seconds*/
}
NFE_Control_SetBERWindow_Arg;

/**   \brief Get current Uncorrected packet errors from HW
   Argument for Get Uncorrected packet errors command
   Parameter struct for NFE_Control_GetCurrUncorrectedErrors
*/
typedef struct _tag_NFE_Control_GetCurrUncorrErrs_Arg
{
   NFE_UInt32 uncorrectedErrors; /* Current uncorrected errors */
}
NFE_Control_GetCurrUncorrErrs_Arg;


/**   \brief Get BER Window Argument
   Argument for Get BER Window command
   Parameter struct for NFE_Control_GetBERWindow
*/
typedef struct _tag_NFE_Control_GetBERWindow_Arg
{
   NFE_UInt32 berWindow; /*!< in whole seconds*/
}
NFE_Control_GetBERWindow_Arg;


/**   \brief Set Spiral Search Argument
   Argument for Set Spiral search command
   Parameter struct for NFE_Control_SetSpiralSearch
*/
typedef struct _tag_NFE_Control_SetSpiralSearch_Arg
{
   NFE_Bool enable;
}
NFE_Control_SetSpiralSearch_Arg;


/**   \brief Write to Demod Argument
   Argument for Write to Demod command
   Parameter struct for NFE_Control_WriteToDemod
*/
typedef struct _tag_NFE_Control_WriteToDemod_Arg
{
   NFE_UInt32  length;  /*!< number of bytes*/
   NFE_UInt32  reg;     /*!< register address*/
   NFE_UInt8  *data;    /*!< data array pointer*/
}
NFE_Control_WriteToDemod_Arg;


/**   \brief Read from Demod Argument
   Argument for Read from Demod command
   Parameter struct for NFE_Control_ReadFromDemod
*/
typedef struct _tag_NFE_Control_ReadFromDemod_Arg
{
   NFE_UInt32  length;  /*!< number of bytes*/
   NFE_UInt32  reg;     /*!< register address*/
   NFE_UInt8  *data;    /*!< data array pointer*/
}
NFE_Control_ReadFromDemod_Arg;


/**   \brief Get Stinger FSM Argument
   Argument for Get Stinger FSM command
   Parameter struct for NFE_Control_GetStingerFSM
*/
typedef struct _tag_NFE_Control_GetStingerFSM_Arg
{
   NFE_Char fsm[128];
}
NFE_Control_GetStingerFSM_Arg;


/**   \brief Write to Tuner Argument
   Argument for Write to Tuner command
   Parameter struct for NFE_Control_WriteToTuner
*/
typedef struct _tag_NFE_Control_WriteToTuner_Arg
{
   NFE_UInt32  length;  /*!< number of bytes*/
   NFE_UInt32  reg;     /*!< register address*/
   NFE_UInt8  *data;    /*!< data array pointer*/
}
NFE_Control_WriteToTuner_Arg;


/**   \brief Read from Tuner Argument
   Argument for Read from Tuner command
   Parameter struct for NFE_Control_ReadFromTuner
*/
typedef struct _tag_NFE_Control_ReadFromTuner_Arg
{
   NFE_UInt32  length;  /*!< number of bytes*/
   NFE_UInt32  reg;     /*!< register address*/
   NFE_UInt8  *data;    /*!< data array pointer*/
}
NFE_Control_ReadFromTuner_Arg;


/**   \brief Control Switch State Argument
   Argument for Control Switch State command
   Parameter struct for NFE_Control_SwitchXtalState
*/
typedef struct _tag_NFE_Control_SwitchXtalState_Arg
{
   NFE_Bool on;
}
NFE_Control_SwitchXtalState_Arg;


/**   \brief Report Equaliser Coefficients Argument
   Argument for Report Equaliser Coefficients command
   Parameter struct for NFE_Control_GetEqualiserCoeffs
*/
typedef struct _tag_NFE_Control_ReportEqualiserCoeffs_Arg
{
   NFE_Bool enable; /*!< often large overhead reporting these coefficients, so have facility to enable/disable the process*/
}
NFE_Control_ReportEqualiserCoeffs_Arg;


/**   \brief Get Multipath Condition Argument
   Argument for Get Multipath Condition command
   Parameter struct for FE_Control_GetMultipathCondition
*/
typedef struct _tag_NFE_Control_GetMultipathCondition_Arg
{
   NFE_UInt8 estimate; /*!< 0 to 100%, 0% = no multipath, 100% = unusable*/
}
NFE_Control_GetMultipathCondition_Arg;


/**   \brief Set GPIO Argument
   Argument for Set GPIO command
   Parameter struct for NFE_Control_SetGPIO
*/
typedef struct _tag_NFE_Control_SetGPIO_Arg
{
   NFE_UInt32 pin;      /*!< device specific pin identifier*/
   NFE_Bool   status;   /*!< true = high, false = low*/
}
NFE_Control_SetGPIO_Arg;


/**   \brief Get GPIO Argument
   Argument for Get GPIO command
   Parameter struct for NFE_Control_GetGPIO
*/
typedef struct _tag_NFE_Control_GetGPIO_Arg
{
   NFE_UInt32 pin;      /*!< device specific pin identifier*/
   NFE_Bool   status;   /*!< true = high, false = low*/
}
NFE_Control_GetGPIO_Arg;


/**   \brief Broadcom Config Argument
   Argument for Broadcom frontend config commands
   Parameter struct for NFE_Control_bcmWriteConfig and NFE_Control_bcmReadConfig
*/
typedef struct _tag_NFE_Control_BcmConfig_Arg
{
   NFE_UInt8 setup_n; /*!< setup id*/
   NFE_UInt8 data;    /*!< actual value to read/write*/
}
NFE_Control_BcmConfig_Arg;


/**   \brief Enable Tuner Buffered Clock Output Argument
   Argument for Enable Tuner Buffered clock Output command
   Parameter struct for NFE_Control_enableTunerBufferedClk
*/
typedef struct _tag_NFE_Control_enableTunerBufferedClk_Arg
{
   NFE_Bool enable;
}
NFE_Control_enableTunerBufferedClk_Arg;


/**   \brief Calibrate Argument
   Argument for Calibrate command
   Parameter struct for NFE_Control_Calibrate
*/
typedef struct _tag_NFE_Control_Calibrate_Arg
{
   NFE_UInt8 refSignalLevel; /*!< reference signal level in whole dBm*/
}
NFE_Control_Calibrate_Arg;


/**   \brief Calibration Data Argument
   Argument for Get and Set Calibration Data commands
   Parameter struct for NFE_Control_SetCalibrationData and NFE_Control_GetCalibrationData
*/
typedef struct _tag_NFE_Control_CalibrationData_Arg
{
   NFE_CalStatus  calStatus;  /*!< calibration status for a given entry*/
   NFE_Int32      calOffset;  /*!< calibration offset in tenths of a dB for a given entry*/
}
NFE_Control_CalibrationData_Arg;


/**   \brief Select Input Argument
   Argument for Set Input command
   Parameter struct for NFE_Control_selectInput
   Note this is equivalent to the NFE_setAssocLnb method
*/
typedef struct _tag_NFE_Control_SelectInput_Arg
{
   NFE_UInt32 input; /*!< zero-indexed physical RF inputs*/
}
NFE_Control_SelectInput_Arg;


/**   \brief Get Die Temp Argument
   Argument for Get Die Temp command
   Parameter struct for NFE_Control_GetDieTemp
*/
typedef struct _tag_NFE_Control_GetDieTemp_Arg
{
   NFE_UInt32 dieTemp; /*!< tenths of a degree C*/
}
NFE_Control_GetDieTemp_Arg;


/**   \brief Get Supply Voltage Argument
   Argument for Get Supply Voltage command
   Parameter struct for NFE_Control_GetSupplyVoltage
*/
typedef struct _tag_NFE_Control_GetSupplyVoltage_Arg
{
   NFE_UInt32 supplyVoltage; /*!< millivolts*/
}
NFE_Control_GetSupplyVoltage_Arg;


/**   \brief Get DVBT2 pre L1 Info Argument
   Argument for Get DVBT2 pre L1 Info command
   Parameter struct for NFE_Control_GetDvbT2L1PreInfo
   Some implementations won't be able to populate all fields
*/
typedef struct _tag_NFE_Control_GetDvbT2L1PreInfo_Arg
{
   NFE_DVBT2_C_StreamType   streamType;         /*!< see NFE_DVBT2_C_StreamType definition*/
   NFE_UInt8                bwExt;              /*!< true if bandwidth extension in use*/
   NFE_DVBT2_C_s1Type       s1Signalling;       /*!< see NFE_DVBT2_C_s1Type definition*/
   NFE_DVBT2_C_s2Type       s2Signalling;       /*!< see NFE_DVBT2_C_s2Type definition*/
   NFE_UInt8                mixedSignalling;    /*!< true if mixed signalling in use*/
   NFE_UInt8                l1RepFlag;          /*!< true if L1 is repeated*/
   NFE_C_FFTSize            fftSize;            /*!< see NFE_C_FFTSize definition*/
   NFE_C_Guardband          guardInterval;      /*!< see NFE_C_Guardband definition*/
   NFE_DVBT2_C_papr         papr;               /*!< see NFE_DVBT2_C_papr definition*/
   NFE_DVBT2_C_PilotPattern pilotPattern;       /*!< see NFE_DVBT2_C_PilotPattern definition*/
   NFE_C_Modulation         l1Modulation;       /*!< see NFE_C_Modulation definition - modulation of L1 portion*/
   NFE_C_CodeRate           l1CodeRate;         /*!< see NFE_C_CodeRate definition - code rate of L1 portion*/
   NFE_DVBT2_C_FECType      l1FecType;          /*!< see NFE_DVBT2_C_FECType definition - fec type of L1 portion*/
   NFE_UInt32               l1PostSize;         /*!< post L1 field size in bytes*/
   NFE_UInt32               l1PostInfoSize;     /*!< post L1 info size in bytes*/
   NFE_UInt8                txIdAvailability;   /*!< true if transmitter id is available*/
   NFE_UInt16               cellId;             /*!< cell identifier*/
   NFE_UInt16               networkId;          /*!< network identifier*/
   NFE_UInt16               systemId;           /*!< system identifier*/
   NFE_UInt8                numFrames;          /*!< frame size*/
   NFE_UInt16               numDataSymbols;     /*!< number of data symbols per frame*/
   NFE_UInt8                regenFlag;          /*!< true if regenerated signal (i.e a retransmission)*/
   NFE_UInt8                l1PostExt;          /*!< true if post L1 signal region is extended*/
   NFE_UInt8                numRfFreqs;         /*!< number of linked RF frequencys*/
   NFE_UInt8                rfIndex;            /*!< index of current received frequency in list of linked frequencys*/
   NFE_UInt16               reserved;           /*!< currently unused*/
   NFE_UInt32               crc32;              /*!< basic CRC of signalling info used by decoder*/
}
NFE_Control_GetDvbT2L1PreInfo_Arg;


/**   \brief Get DVBT2 post L1 Info Argument
   Argument for Get DVBT2 post L1 Info command
   Parameter struct for NFE_Control_GetDvbT2L1PostInfo
   Some implementations won't be able to populate all fields
*/
typedef struct _tag_NFE_Control_GetDvbT2L1PostInfo_Arg
{
   NFE_UInt16 subSlicesPerFrame; /*!< sub-slices per frame*/
   NFE_UInt8  numPlp;            /*!< number of PLPs per signal*/
   NFE_UInt8  numAux;            /*!< number of auxillary streams per signal*/
   NFE_UInt8  auxConfigRfu;      /*!< auxillary stream configuration*/
   /*this section may need duplicating for use beyond 'TFS' - numRfFreqs entries*/
   NFE_UInt8  rfIndex;           /*!< current RF index*/
   NFE_UInt8  frequency;         /*!< current RF freqeuncy corresponding to the above index*/
   /*future extension frames*/
   NFE_UInt8  fefType;           /*!< Future Extension Frame type*/
   NFE_UInt32 fefLength;         /*!< Future Extension Frame length in bytes*/
   NFE_UInt8  fefInterval;       /*!< interval between consecutive Future Extension Frames*/

   NFE_UInt16 Reserved2;         /*!< unused*/
   /*this section may need duplicating for multiple Aux streams - numAux entries*/
   NFE_UInt8  auxRfu;            /*!< auxillary stream RF inditifier*/
}
NFE_Control_GetDvbT2L1PostInfo_Arg;


/**   \brief Get DVBT2 PLP identifiers Argument
   Argument for Get DVBT2 PLP ids command
   Parameter struct for NFE_Control_GetDvbT2PlpIds
*/
typedef struct _tag_NFE_Control_GetDvbT2PlpIds_Arg
{
   NFE_UInt32 numPlps;     /*!< number of PLPs in the stream*/
   NFE_UInt8  plpIds[256]; /*!< zero-indexed array containing their identifiers*/
}
NFE_Control_GetDvbT2PlpIds_Arg;


/**   \brief Get DVBT2 active PLP information Argument
   Argument for Get DVBT2 active PLP info command
   Parameter struct for NFE_Control_GetDvbT2ActivePlpInfo
   Some implementations won't be able to populate all fields
*/
typedef struct _tag_NFE_Control_GetDvbT2ActivePlpInfo_Arg
{
   NFE_UInt8                  plpId;                  /*!< identifier of active PLP*/
   NFE_DVBT2_C_PlpType        plpType;                /*!< type of active PLP - see NFE_DVBT2_C_PlpType definition*/
   NFE_DVBT2_C_PlpPayloadType plpPayloadType;         /*!< payload type of actie PLP - see NFE_DVBT2_C_PlpPayloadType definition*/
   NFE_UInt8                  ffFlag;                 /*!< frame flag*/
   NFE_UInt8                  firstRfIndex;           /*!< RF index PLP starts from (if applicable)*/
   NFE_UInt8                  firstFrameIndex;        /*!< Frame index PLP starts from (if applicable)*/
   NFE_UInt8                  plpGroupId;             /*!< PLP group identifier (if applicable)*/
   NFE_C_CodeRate             plpCodeRate;            /*!< active PLP code rate - see NFE_C_CodeRate definition*/
   NFE_C_Modulation           plpModulation;          /*!< active PLP modulation scheme - see NFE_C_Modulation*/
   NFE_UInt8                  plpRotation;            /*!< true if active PLP constellation is rotated*/
   NFE_DVBT2_C_FECType        plpFecType;             /*!< active PLP fec type - see NFE_DVBT2_C_FECType definition*/
   NFE_UInt16                 plpNumBlocksMax;        /*!< number of blocks making up the active PLP*/
   NFE_UInt8                  frameInterval;          /*!< repeat interval of the assocaited frame*/
   NFE_UInt8                  timeInterleaverLength;  /*!< time interleaver length*/
   NFE_UInt8                  timeInterleaverType;    /*!< time interleaver type*/
   NFE_UInt8                  inBandFlag;             /*!< true if all relevant signalling is associated with this PLP*/
   NFE_UInt16                 Reserved1;              /*!< unused*/
}
NFE_Control_GetDvbT2ActivePlpInfo_Arg;


/**   \brief Check for no DVBT2 signal Argument
   Argument for Check for no DVBT2 signal command
   Parameter struct for NFE_Control_CheckForNoDvbT2Signal
*/
typedef struct _tag_NFE_Control_CheckForNoDvbT2Signal_Arg
{
   NFE_Bool noSignalCondition1; /*!<option for 3 different on signal condition tests*/
   NFE_Bool noSignalCondition2; /*!<these might be appropriate only for different times from the start of acquisition*/
   NFE_Bool noSignalCondition3; /*!<no assumption about implementation*/
}
NFE_Control_CheckForNoDvbT2Signal_Arg;


/**   \brief Check for no DVBT signal Argument
   Argument for Check for no DVBT signal command
   Parameter struct for NFE_Control_CheckForNoDvbTSignal
*/
typedef struct _tag_NFE_Control_CheckForNoDvbTSignal_Arg
{
   NFE_Bool noSignalCondition1; /*!<option for 3 different on signal condition tests*/
   NFE_Bool noSignalCondition2; /*!<these might be appropriate only for different times from the start of acquisition*/
   NFE_Bool noSignalCondition3; /*!<no assumption about implementation*/
}
NFE_Control_CheckForNoDvbTSignal_Arg;


/**   \brief Extended Calibration Argument
   Argument for extended Calibration command
   Parameter structs for NFE_Control_CalibrateExt (Full Extended Calibration Method)
*/
typedef struct _tag_NFE_Control_CalibrateExt_Arg
{
   NFE_ExtCalType    calType;    /*!< DS/US1/US2*/
   NFE_UInt8         tuner;      /*!< Tuner index (DS) or Channel Index (US)*/
   NFE_UInt32        length;     /*!< 15 for DS, 21 for USHI/USLO*/
   NFE_Int16        *data;       /*!< Offsets in centi-dB*/
}
NFE_Control_CalibrateExt_Arg;


/**   \brief NFE Control Argument
   NFE_Control_Arg
   Union for any non-generic command parameter structures
   Not all will be applicable tO any given implementation
*/
typedef union __tag_NFE_Control_Arg
{
   NFE_Control_SetBERWindow_Arg              stSetBerWindow;            /*!< set BER window*/
   NFE_Control_SetSpiralSearch_Arg           stSetSpiralSearch;         /*!< spiral search*/
   NFE_Control_GetSignalLevel_Arg            stGetSignalLevel;          /*!< signal level*/
   NFE_Control_AttenuatorState_Arg           stAttenuatorState;         /*!< attenuator state*/
   NFE_Control_GetSetAGC_Arg                 stGetSetAgc;               /*!< agc value*/
   NFE_Control_FreezeAGC_Arg                 stFreezeAgc;               /*!< agc freeze/run*/
   NFE_Control_GetChipRev_Arg                stGetChipRev;              /*!< chip revision*/
   NFE_Control_WriteToDemod_Arg              stWriteToDemod;            /*!< write to demodulator*/
   NFE_Control_ReadFromDemod_Arg             stReadFromDemod;           /*!< read from demodulator*/
   NFE_Control_GetStingerFSM_Arg             stGetStingerFSM;           /*!< 'Stinger' FSM value*/
   NFE_Control_WriteToTuner_Arg              stWriteToTuner;            /*!< write to tuner*/
   NFE_Control_ReadFromTuner_Arg             stReadFromTuner;           /*!< read from tuner*/
   NFE_Control_SwitchXtalState_Arg           stSwitchXtalState;         /*!< switch crystal state*/
   NFE_Control_ReportEqualiserCoeffs_Arg     stReportEqualiserCoeffs;   /*!< enable/disable equaliser coefficent reporting*/
   NFE_Control_GetMultipathCondition_Arg     stGetMultipathCondition;   /*!< multipath condition estimate*/
   NFE_Control_SetGPIO_Arg                   stSetGPIO;                 /*!< set frontend device GPIO value*/
   NFE_Control_GetGPIO_Arg                   stGetGPIO;                 /*!< get frontend device GPIO value*/
   NFE_Control_BcmConfig_Arg                 stBcmConfig;               /*!< get/sw Broadcom frontend configuation word*/
   NFE_Control_enableTunerBufferedClk_Arg    stEnableTunerBufferedClk;  /*!< enable/disable tuner buffered clock output*/
#if NFE_SUPPORT_EXTENDED_CAL
   NFE_Control_CalibrateExt_Arg              stCalibrateExt;            /*!< extended calibration*/
#else
   NFE_Control_Calibrate_Arg                 stCalibrate;               /*!< legacy calibration*/
   NFE_Control_CalibrationData_Arg           stCalibrationData;         /*!< legacy calibration data*/
#endif
   NFE_Control_SelectInput_Arg               stSelectInput;             /*!< RF input selection*/

   NFE_Control_GetDvbT2L1PreInfo_Arg         stGetDvbT2L1PreInfo;       /*!< DVB-T2 pre-L1 signalling info*/
   NFE_Control_GetDvbT2L1PostInfo_Arg        stGetDvbT2L1PostInfo;      /*!< DVB-T2 post-L1 signalling info*/
   NFE_Control_GetDvbT2PlpIds_Arg            stGetDvbT2PlpIds;          /*!< DVB-T2 PLP identifier array*/
   NFE_Control_GetDvbT2ActivePlpInfo_Arg     stGetDvbT2ActivePlpInfo;   /*!< DVB-T2 active PLP info*/
   NFE_Control_CheckForNoDvbT2Signal_Arg     stCheckForNoDvbT2Signal;   /*!< DVB-T2 no signal check*/
   NFE_Control_CheckForNoDvbTSignal_Arg      stCheckForNoDvbTSignal;    /*!< DVB-T no signal check*/

   NFE_Control_GetDieTemp_Arg                stGetDieTemp;              /*!< get die temperature*/
   NFE_Control_GetSupplyVoltage_Arg          stGetSupplyVoltage;        /*!< get AVS voltage*/

   NFE_Control_GetBERWindow_Arg              stGetBerWindow;            /*!< get BER window*/
   NFE_Control_GetCurrUncorrErrs_Arg         stGetCurrUncorrErrs;       /*!< get current uncorrected errors*/   
}
NFE_Control_Arg;

#ifdef __cplusplus
}
#endif

#endif /* __NFE_CONTROL_H_ */

/*fe_control.h*/
