 /********************************************************************
 *********************************************************************
 *
 *  File        :  nfe_api.h
 *
 *  Project     :  $ProjectName$
 *
 *  ProjectVer  :  $ProjectRevision$
 *
 *  Description :  NIG frontend interface header file
 *
 *  Notes       :
 *
 *  Author      :  $Author: rowe_j $
 *
 *  Status      :  $State: Exp $
 *
 *  Revision    :  $Revision: 1.57 $
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

/**
   \mainpage NFE driver API
   \section    purpose_sec    Purpose
   The main purpose of this document is to define the interface needed to drive any frontend module with the NFE device drivers.
\n
   \section    scope_sec      Scope
   This document may apply only for the products using NFE interface for frontend drivers
\n
   \section    feature_sec    Features
   This API interface provides a unique set of features/IF for Pace STBs application middlewares and predominantly ease the integration job 
   when ever new development/porting happens. The unique features provided by NFE module are like
\n
   - Common frontend interface for most of the Pace Products
   - Common frontend interface for most of the Pace software applications and boot loaders
   - Common frontend interface for most of the Pace H/W test applications used to validate the frontend performances
   - Handle all the below complexities
      - State machine to maintain the H/W states 
      - Send appropriate asynchronous events to the registered api callbacks with respect to the instances without blocking the CPU
      - The CPU/System performance is improved especially when multiple frontends are supported by H/W
      - Multi frontend support at a time (DVB-S/S2, DVB-T/T2, etc .... )
      - Auto Carrier Detection (Ex: Only Freq & list of symbols for satellite searching)
      - DVB-T/C Frequency Scanning with lot of reliable and efficient algorithms
      - Input mapping when H/W has more than one input
      - Signal Strength & Quality Calibration on H/W Specific
      - CENELEC standards support for Unicable LNB
      - Support for SaTCR devices
\n
   \section    frontend_fun_sec Frontend Functions
   All frontend functionalities are implemented and given access through the below NFE apis.
\n
   \li #NFE_subsysInit
   \li #NFE_subsysDestruct
   \li #NFE_lookup
   \li #NFE_registerCallback
   \li #NFE_tune
   \li #NFE_startScan
   \li #NFE_nextScan
   \li #NFE_stop
   \li #NFE_getStatus
   \li #NFE_getDiagnostics
   \li #NFE_getModes
   \li #NFE_getHwInfo
   \li #NFE_getHwVersions
   \li #NFE_getAssocLNB
   \li #NFE_setAssocLNB
   \li #NFE_setStandbyMode
   \li #NFE_control
\n
   \section lnb_fun_sec LNB Functions
   All lnb functionalities are implemented and given access through the below apis.
\n
   \li #NLNB_lookup
   \li #NLNB_registerCallback
   \li #NLNB_setPower
   \li #NLNB_setPolarisation
   \li #NLNB_setTone
   \li #NLNB_setLoopThrough
   \li #NLNB_sendDiseqcMessage
   \li #NLNB_receiveDiseqcMessage
   \li #NLNB_isShortCircuit
   \li #NLNB_control
   \li #NLNB_sendSatCRMessage
   \li #NLNB_setStandbyMode
\n
   \section    revision_sec    Document Revision
   The document revision explains the changes done in different revisions.

   1.2
   ===
   Various formatting improvements, minor corrections and inclusion of descriptions in 'control' headers

   1.1
   ===
   DVB-S2x support is added and updated

   1.0
   ===
   The very first cut off this document.
*/



/** \page nfe_archi NFE Architecture
    The NFE module level architecture and high level architectures are explained below.

    \section module_level_arch_sec   Module Level Architecture
    The below diagram shows where the NFE drivers will sit and who are going to access it. If you noticed the boot loader is optional user for NFE drivers. Due to space
    contraints in flash some projects may go with broadcom delivery by skipping NFE. But most of the projects boot loader also will go with NFE. The testtask is further
    used for factory validation which is very important in the process of certifying H/W performance and quality.
\n
    \image html nfe_module_level_architecture.png NFE Module Level Architecture
\n
    \section high_level_arch_sec   High Level Architecture
    The high level architecture explains the NFE drivers major blocks and the communication flow between blocks. The interface api send reqested info to the
    respective modules. Finally the frontend state machine receive the request and process it and will return the values to the caller. It also will take care
    the asynchronous events to the called to notify the driver events like LOCKED / NOT LOCKED / LOST LOCK.
\n
    \image html nfe_high_level_architecture.png NFE High Level Architecture

    \section statemachine_sec   Frontend State Machine
    The state machine is the heart for NFE module. Because it will directly affect the performance of the device. This is the one will receive the request from
    users and execute the functinalities in the efficient manner. That means without blocking the caller the requested action should be performed by the state
    machine and the results should be communcated to caller asynchronously.

    \image html nfe_state_machine.png NFE State Machine
\n
    The state machine has following states\n
    States             | Info
    :------------------|:--------------------------------------------------------------------------------------------------------
     <b>INIT</b>       | After a successful init
     <b>STANDBY</b>    | When the device is in Standby
     <b>IDLE</b>       | When the device is not in any action
     <b>TUNING</b>     | After a successful tuning without any error or continuously tuning to recover Lost Lock / Not Lock
     <b>LOCKED</b>     | After a successful lock
     <b>SCANNING</b>   | After a successful scanning

    The state machine raise following asynchronous events to the caller\n
    Asynchronous Events                         | Info
    :-------------------------------------------|:--------------------------------------------------------------------------------------------------------
    <b>NFE_EVENT_LOCKED</b>                     | Frontend locked event for either new tune request or recover from LOST LOCK condition
    <b>NFE_EVENT_ACQ_FAILED</b>                 | Frontend acquisition failed Event for new tune request
    <b>NFE_EVENT_LOST_LOCK</b>                  | Frontend lost lock Event when the signal is already successfully tuned and lost lock
    <b>NFE_EVENT_HARDWARE_INIT_SUCCEEDED</b>    | Frontend hardware init successfully happened
    <b>NFE_EVENT_HARDWARE_INIT_FAILED</b>       | Frontend hardware init failed
    <b>NFE_EVENT_HARDWARE_ERROR</b>             | Frontend hardware error found (I2C error ) - Depricated
    <b>NFE_EVENT_FREQUENCY_LIMIT</b>            | Frontend scanning algorithm reached end of search
    <b>NFE_EVENT_STOPPED</b>                    | Frontend module is successfully stopped
    <b>NFE_EVENT_SATCR_TONE_DETECT_COMPLETE</b> | SatCR Tone Detection completed, but not found any tone
    <b>NFE_EVENT_SATCR_TONE_DETECT_FOUND</b>    | SatCR Tone Detected
    <b>NFE_EVENT_TUNING</b>                     | Frontend tuning is invoked successfully, but it may fail/success to find carrier
    <b>NFE_EVENT_INCREMENT_SCAN_BAND</b>        | Frontend scanning is trying next carrier
    <b>NFE_EVENT_BER_READY</b>                  | New BER measurement is available

    \subsection init_state_subsec Init State
    The fesubsys init api will init all frontend modules configured for the respective project. It will configure all frontend hardwares (Tuner , Demods, LNA & LNB
    devices) and frontend NFE drivers. If it successfully inits it will send #NFE_EVENT_HARDWARE_INIT_SUCCEEDED event and all frontend tasks will go to Idle state,
    or it will send #NFE_EVENT_HARDWARE_INIT_FAILED event.
\n
    \subsection idle_state_subsec Idle State
    In idle state all frontend tasks are in idle and it will poll for the new action for every configured polling period which is set in fesubsys module.
    The NFE_Stop api brings state machine to idle state from any rest of the states at any time. The NFE_Stop notify the callers with #NFE_EVENT_STOPPED
    event at the end of successful stop. From the idle state the state machine either to to scanning process or tuning process based on the NFE request.
\n
    \subsection tuning_state_subsec Tuning State
    The NFE_Tune api moves state machine from idle sate to tuning state. Each time the NFE_Tune api sends #NFE_EVENT_TUNING event to caller to notify the tuning is
    invoked successfully. If the tuning request doesn't find the signal in the defined timeout period then it will send #NFE_EVENT_ACQ_FAILED event at the end of timeout
    and will be in the same state untill any new NFE request comes. If the retry option is enabled in fesubsys then it will try to send tune command to both tuner and
    demod continuously untill it gets successful lock. Else it stays their and wait for the lock without sendng any new commands to the tuner and demod.\n
    In satcr mode the NFE_Tune api is going find the CW carrier presence. If it detects it will send #NFE_EVENT_SATCR_TONE_DETECT_FOUND event and will move task state
    to Locked state else it will send #NFE_EVENT_SATCR_TONE_DETECT_COMPLETE event and stays in the same tuning state.
\n
    \subsection locked_state_subsec Locked State
    The NFE task will move to locked state from tuning state when it finds a valid requested signal. It will continuously monitor the lock and signal parameters
    change for the configured polling period. Once the lock is lost it will notify user with #NFE_EVENT_LOST_LOCK event and NFE task will go to tuning state.
    In tuning state it may try to send tune command again and again till lock found only when retune option is enabled in fesubsys. otherwise it will stay in
    tuning state and will monitor only signal lock without sending any new tune request.\n
    When the NFE task performs scanning and when it finds a valid signal then moves to locked state and wait for next scan or stop scan request.
    The get status and get diagnostic api's will return proper values only in this state.
\n
    \subsection scanning_state_subsec Scanning State
    The NFE_StartScan api move the NFE state machine from idle state to scanning state. In scanning state NFE task will try scanning from start frequency to end
    frequency and for each frequency it will try all scan table entries. Each time the scanning raises #NFE_EVENT_INCREMENT_SCAN_BAND event before moving to
    next frequency to notify scanning progress to the caller. If it finds a valid signal it raises #NFE_EVENT_LOCKED event and wait indefinitely for either stop
    or continue signal from user. The continue signal push the scanning process for next frequency. If the scanning process doesn't find any valid signal and
    it reaches end of frequency then it raises #NFE_EVENT_FREQUENCY_LIMIT event and will go to idle state.
\n
    \subsection standby_state_subsec Standby State
    The frontend hardware sets to standby mode, but the NFE task will be in the same state. But it should be moved to standby state this will keep the CPU
    in lower usage.
    Standby mode to normal mode should bring the statemachine to idle state, but actually it is always going to tuning state even though standby is
    requested in scanning state. I hope this should be corrected.
*/


/** \page nfe_abbr_termi Terminology - Abbreviations
    \section nfe_abbr_sec Abbreviations
    Abbreviation        | Info
    :-------------------|:--------------------------------------------------------------------------------------------------------
    <b>BER</b>          | Bit Error Rate
    <b>CW</b>           | Continuous Wave
    <b>DiSEqC</b>       | Digital Satellite Equipment Control
    <b>DSS</b>          | Digital Satellite Service
    <b>DVB</b>          | Digital Video Broadcasting
    <b>GCS</b>          | Generic Continuous Stream
    <b>GFPS</b>         | Generic Fixed-length Packetized Stream
    <b>GSE</b>          | Generic Stream Encapsulation
    <b>IB</b>           | In Band
    <b>IF</b>           | Intermediate Frequency
    <b>ISDB-T</b>       | Integrated Services Digital Broadcasting
    <b>LNB</b>          | Low-Noise Block
    <b>MISO</b>         | Multiple Input Single Output
    <b>NIG</b>          | Network Interface Group
    <b>NIM</b>          | Network Interface Module
    <b>OFDM</b>         | Orthogonol Frequency Division Modulation
    <b>OOB</b>          | Out Off Band
    <b>PAPR</b>         | Peak to Average Power Ratio
    <b>QAM</b>          | Quardrature Amplitude Modulation
    <b>QEF</b>          | Quasi Error Free
    <b>QPSK</b>         | Quardrature Phase Shift Keying
    <b>RF</b>           | Radio Frequency
    <b>SatCR</b>        | Satellite Control Receiver
    <b>SISO</b>         | Single Input Single Output
    <b>TS</b>           | Transport Stream
    <b>VSB</b>          | Vestegial Side Band
\n
\n
    \section nfe_term_sec Terminology
    \subsection ss_subsec  Signal Strength
    The strength/power of the wanted signal, it is represented in dBm or dBuV or dBmV. The NIG driver reports the signal power in the range of 0 to 255.
    The (0 to -127.5 dBm) signal power is scaled between (255 to 0).\n
    The NIG reported power level is derived from dBm by below formula
    \f{eqnarray*}{
    NIGReportedPowerLevel = \frac{(PowerLevel_In_dBm - 255)} {2}
    \f}
    The same way you can calculate the power level in dBm from NIG reported power level by below formula
    \f{eqnarray*}{
    PowerLevel_In_dBm = (NIGReportedPowerLevel \times 2) + 255
    \f}

    \image html signal_power.png Signal Power

    \subsection snr_subsec SNR
    The signal (wanted carrier) to noise (unwanted carrier) ratio, it will be represented in dB
    \image html snr.png SNR

    \subsection ber_subsec BER
    Bit error rate is the ratio between total number of bits taken in to consideration and number of error bits. The below diagram shows that
    the bit error rate can be calculated in three different places.\n
    <b>PreViterbi</b> Bitrate\n
    <b>PostViterbi</b> Bitrate or <b>PreRSBitrate</b>\n
    <b>PostRSBitrate</b> Bitrate\n
    \image html ber.png BER at different blocks
\n
*/

#ifndef __NFE_API_H_
#define __NFE_API_H_

#include "fe_port_types.h"
#include "fe_port_errorcodes.h"
#include "nfe_platform.h"
#include "nfe_control.h"
#if NFE_SUPPORT_LNB
#include "nlnb_api.h"
#endif /*#if NFE_SUPPORT_LNB*/
#ifdef __cplusplus
extern "C"
{
#endif

/*basic types*/
typedef NFE_UInt32 NFE_SymbolRate;        /*!< Units in Symbols/s*/
typedef NFE_UInt32 NFE_Frequency;         /*!< Units in Hz */
typedef NFE_Int32  NFE_Offset;            /*!< Units in Hz */
typedef NFE_UInt32 NFE_AGC;               /*!< AGC register value (i.e. direct register contents cast to NFE_UInt32)*/
typedef NFE_UInt32 NFE_LockTime;          /*!< Units in ms */
typedef NFE_UInt32 NFE_BER;               /*!< General BER type */
typedef NFE_UInt32 NFE_SNR;               /*!< Units in tenths of a dB, eg. 30.8dB would be stored as 308 (decimal) */
typedef NFE_UInt32 NFE_HwVersion;         /*!< Encoded numerical hardware version (eg chip revision info - implementation specific)*/

/* NFE_LockState - indicates where the specific frontend is in the acquisition cycle*/
typedef enum _tag_NFE_LockState
{
   NFE_LOCK_UNKNOWN    = -1,              /*!< Unknown State - error condition */
   NFE_NOT_LOCKED      =  0,              /*!< Frontend is not locked */
   NFE_LOCKED          =  1,              /*!< Frontend is Locked */
   NFE_BUSY            =  2,              /*!< Frontend module is busy - rarely used */
   NFE_FREQUENCY_LIMIT =  3,              /*!< NFE Scanning reached the End of Search */
   NFE_NO_SIGNAL       =  4               /*!< Pre Lock Check (Before trying FEC lock) itself failed */
} NFE_LockState;


/** \brief Frontend signal coderates

    The below list of coderates will be used
    Macro                   | Description
    :-----------------------|--------------------------------------------------------------------
    NFE_CODE_AUTO           | Use frontend auto FEC detection support
    NFE_CODE_1_2            | Tune only 1/2 FEC
    NFE_CODE_2_3            | Tune only 2/3 FEC
    NFE_CODE_3_5            | Tune only 3/5 FEC
    NFE_CODE_3_4            | Tune only 3/4 FEC
    NFE_CODE_4_5            | Tune only 4/5 FEC
    NFE_CODE_5_6            | Tune only 5/6 FEC
    NFE_CODE_6_7            | Tune only 6/7 FEC
    NFE_CODE_7_8            | Tune only 7/8 FEC
    NFE_CODE_8_9            | Tune only 8/9 FEC
    NFE_CODE_9_10           | Tune only 9/10 FEC
    NFE_CODE_1_4            | Tune only 1/4 FEC
    NFE_CODE_1_3            | Tune only 1/3 FEC
    NFE_CODE_2_5            | Tune only 2/5 FEC
    NFE_CODE_5_9            | Tune only 5/9 FEC
    NFE_CODE_7_9            | Tune only 7/9 FEC
    NFE_CODE_5_11           | Tune only 5/11 FEC
    NFE_CODE_8_15           | Tune only 8/15 FEC
    NFE_CODE_11_15          | Tune only 11/15 FEC
    NFE_CODE_13_18          | Tune only 13/18 FEC
    NFE_CODE_9_20           | Tune only 9/20 FEC
    NFE_CODE_11_20          | Tune only 11/20 FEC
    NFE_CODE_23_36          | Tune only 23/36 FEC
    NFE_CODE_25_36          | Tune only 25/36 FEC
    NFE_CODE_13_45          | Tune only 13/45 FEC
    NFE_CODE_26_45          | Tune only 26/45 FEC
    NFE_CODE_28_45          | Tune only 28/45 FEC
    NFE_CODE_32_45          | Tune only 32/45 FEC
    NFE_CODE_77_90          | Tune only 77/90 FEC
*/
typedef NFE_UInt32 NFE_CodeRate;
#define NFE_CODE_AUTO  0x00008000
#define NFE_CODE_1_2   0x00000001
#define NFE_CODE_2_3   0x00000002
#define NFE_CODE_3_5   0x00000004
#define NFE_CODE_3_4   0x00000008
#define NFE_CODE_4_5   0x00000010
#define NFE_CODE_5_6   0x00000020
#define NFE_CODE_6_7   0x00000040
#define NFE_CODE_7_8   0x00000080
#define NFE_CODE_8_9   0x00000100
#define NFE_CODE_9_10  0x00000200
#define NFE_CODE_1_4   0x00000400
#define NFE_CODE_1_3   0x00000800
#define NFE_CODE_2_5   0x00001000
#define NFE_CODE_5_9   0x00002000
#define NFE_CODE_7_9   0x00004000
#define NFE_CODE_5_11  0x00010000
#define NFE_CODE_8_15  0x00020000
#define NFE_CODE_11_15 0x00040000
#define NFE_CODE_13_18 0x00080000
#define NFE_CODE_9_20  0x00100000
#define NFE_CODE_11_20 0x00200000
#define NFE_CODE_23_36 0x00400000
#define NFE_CODE_25_36 0x00800000
#define NFE_CODE_13_45 0x01000000
#define NFE_CODE_26_45 0x02000000
#define NFE_CODE_28_45 0x04000000
#define NFE_CODE_32_45 0x08000000
#define NFE_CODE_77_90 0x10000000


/** \brief Frontend signal Modulation Schemes

    The below list of modulation schemes will be used
    Macro                   | Description
    :-----------------------|--------------------------------------------------------------------
    NFE_QAM_AUTO            | Use frontend auto QAM modulation detection for cable or terrestrial frontends
    NFE_BPSK                | Use only BPSK modulation
    NFE_QPSK                | Use only QPSK modulation
    NFE_8PSK                | Use only 8PSK modulation
    NFE_QAM_4               | Use only QAM-4 modulation
    NFE_QAM_8               | Use only QAM-8 modulation
    NFE_QAM_16              | Use only QAM-16 modulation
    NFE_QAM_32              | Use only QAM-32 modulation
    NFE_QAM_64              | Use only QAM-64 modulation
    NFE_QAM_128             | Use only QAM-128 modulation
    NFE_QAM_256             | Use only QAM-256 modulation
    NFE_QAM_1024            | Use only QAM-1024 modulation
    NFE_QAM_2048            | Use only QAM-2048 modulation
    NFE_VSB_8               | Use only VSB-8 modulation
    NFE_VSB_16              | Use only VSB-16 modulation
    NFE_DQPSK               | Use only DQPSK modulation
    NFE_PSK_AUTO            | Use frontend auto PSK modualation detection for satellite frontends
*/
typedef NFE_UInt32 NFE_Modulation;     /*signal modulation scheme*/
#define NFE_QAM_AUTO 0x00008000
#define NFE_BPSK     0x00000001
#define NFE_QPSK     0x00000002
#define NFE_8PSK     0x00000004
#define NFE_QAM_4    0x00000008
#define NFE_QAM_8    0x00000010
#define NFE_QAM_16   0x00000020
#define NFE_QAM_32   0x00000040
#define NFE_QAM_64   0x00000080
#define NFE_QAM_128  0x00000100
#define NFE_QAM_256  0x00000200
#define NFE_QAM_1024 0x00000400
#define NFE_QAM_2048 0x00000800
#define NFE_VSB_8    0x00001000
#define NFE_VSB_16   0x00002000
#define NFE_DQPSK    0x00010000
#define NFE_8APSK    0x00100000
#define NFE_16APSK   0x00200000
#define NFE_32APSK   0x00400000
#define NFE_64APSK   0x00800000
#define NFE_QAM_4096 0x01000000
#define NFE_PSK_AUTO 0x08000000

/** \brief DVB-S2 Frontend signal Pilots

    The DVB-S2 signal Pilot tone state
    Macro                   | Description
    :-----------------------|--------------------------------------------------------------------
    NFE_PILOT_UNKNOWN       | Unknown Pilot
    NFE_PILOT_OFF           | Pilot OFF for DVB-S2 carrier
    NFE_PILOT_ON            | Pilot ON for DVB-S2 carrier
*/
typedef NFE_UInt32 NFE_Pilot;          /* DVBS2 parameter - pilot tone state */
#define NFE_PILOT_UNKNOWN 0x8000
#define NFE_PILOT_OFF     0x0001
#define NFE_PILOT_ON      0x0002

/** \brief Frontend signal rolloff

    The RF signal rolloff factor
    Macro                   | Description
    :-----------------------|--------------------------------------------------------------------
    NFE_ROLLOFF_UNKNOWN     | Unknown Rolloff
    NFE_ROLLOFF_0_15        | Rolloff 0.15
    NFE_ROLLOFF_0_20        | Rolloff 0.20
    NFE_ROLLOFF_0_25        | Rolloff 0.25
    NFE_ROLLOFF_0_35        | Rolloff 0.35
    NFE_ROLLOFF_0_05        | Rolloff 0.05
    NFE_ROLLOFF_0_10        | Rolloff 0.10
*/
typedef NFE_UInt32 NFE_RollOff;        /* Mainly used for DVBS2 & DVBS2x - shaping filter scaling factor (defines steepness) */
#define NFE_ROLLOFF_UNKNOWN  0x8000
#define NFE_ROLLOFF_0_15     0x0001
#define NFE_ROLLOFF_0_20     0x0002
#define NFE_ROLLOFF_0_25     0x0004
#define NFE_ROLLOFF_0_35     0x0008
#define NFE_ROLLOFF_0_05     0x0010
#define NFE_ROLLOFF_0_10     0x0020

/** \brief Cable Frontend Annex config

    The cable frontend Annex configurations
    Macro                   | Description
    :-----------------------|--------------------------------------------------------------------
    NFE_ANNEXE_A_C          | DVB-C Annex A & C
    NFE_ANNEXE_B            | DVB-C Annex B
*/
typedef NFE_UInt32 NFE_Annexe;         /* Applies to cable and OOB type signals - detailed cable PHY spec*/
#define  NFE_ANNEXE_A_C  0x0001
#define  NFE_ANNEXE_B    0x0002


/** \brief Frontend signal spectrum

    The frontend signal spectrum configurations
    Macro                   | Description
    :-----------------------|--------------------------------------------------------------------
    NFE_SPECTRUM_UNKNOWN    | Unknown spectrum
    NFE_SPECTRUM_AUTO       | Auto lock to both Normal / Inverted spectrum
    NFE_SPECTRUM_NORMAL     | Normal spectrum
    NFE_SPECTRUM_INVERTED   | Inverted spectrum
*/
typedef NFE_UInt32 NFE_Spectrum;     /*signal spectrum sense*/
#define NFE_SPECTRUM_UNKNOWN  0x8000
#define NFE_SPECTRUM_AUTO     0x0000
#define NFE_SPECTRUM_NORMAL   0x0001
#define NFE_SPECTRUM_INVERTED 0x0002

/**   \brief FFT Size
   The FFT sizes for ofdm signals
*/
typedef enum _tag_NFE_FFTSize /* COFDM (eg. DVB-T & H) signal type parameter*/
{
   NFE_FFT_2K      = 0,                   /*!< Transmission mode 2K */
   NFE_FFT_4K      = 1,                   /*!< Transmission mode 4K for DVB-H */
   NFE_FFT_8K      = 2,                   /*!< Transmission mode 8K */
   NFE_FFT_16K     = 3,                   /*!< Transmission mode 16K for DVB-T2*/
   NFE_FFT_32K     = 4,                   /*!< Transmission mode 32K for DVB-T2*/
   NFE_FFT_1K      = 5,                   /*!< Transmission mode 1K for DVB-T2*/
   NFE_FFT_8K_EXT  = 6,                   /*!< Transmission mode 8K Extension for DVB-T2*/
   NFE_FFT_16K_EXT = 7,                   /*!< Transmission mode 16K Extension for DVB-T2*/
   NFE_FFT_32K_EXT = 8,                   /*!< Transmission mode 32K Extension for DVB-T2*/
   NFE_FFT_AUTO    = 9                    /*!< Transmission mode Auto */
} NFE_FFTSize;


/** \brief Frontend signal bandwidth

    The RF signal bandwidth for terrestrial signals
    Macro                   | Description
    :-----------------------|--------------------------------------------------------------------
    NFE_BW_8MHZ             | 8 MHz bandwidth
    NFE_BW_7MHZ             | 7 MHz bandwidth
    NFE_BW_6MHZ             | 6 MHz bandwidth
    NFE_BW_5MHZ             | 5 MHz bandwidth will be used in only DVB-T2
    NFE_BW_10MHZ            | 10 MHz bandwidth will be used in only DVB-T2
    NFE_BW_1_7MHZ           | 1.7 MHz bandwidth will be used in only DVB-T2
*/
typedef NFE_UInt32 NFE_Bandwidth;      /*COFDM (eg. DVB-T / DVB-T2) signal type parameter*/
#define NFE_BW_8MHZ   0x0001
#define NFE_BW_7MHZ   0x0002
#define NFE_BW_6MHZ   0x0004
#define NFE_BW_5MHZ   0x0008
#define NFE_BW_10MHZ  0x0010
#define NFE_BW_1_7MHZ 0x0020


typedef enum _tag_NFE_Guardband        /* COFDM (eg. DVB-T) signal type parameter */
{
   NFE_GUARD_32     = 0,                  /*!< Guard Interval 32 for DVB-T */
   NFE_GUARD_16     = 1,                  /*!< Guard Interval 16 for DVB-T */
   NFE_GUARD_8      = 2,                  /*!< Guard Interval 8 for DVB-T */
   NFE_GUARD_4      = 3,                  /*!< Guard Interval 4 for DVB-T */
   NFE_GUARD_128    = 4,                  /*!< Guard Interval 128 for DVB-T2 */
   NFE_GUARD_19_256 = 5,                  /*!< Guard Interval 19/256 for DVB-T2 */
   NFE_GUARD_19_128 = 6,                  /*!< Guard Interval 19/128 for DVB-T2 */
   NFE_GUARD_1_64   = 7,                  /*!< Guard Interval 1/64 for DVB-C2 */
   NFE_GUARD_AUTO   = 8                   /*!< Guard Interval Auto */
} NFE_Guardband;


typedef enum _tag_NFE_Alpha            /* COFDM (eg. DVB-T) signal type parameter - hiearchical modulation */
{
   NFE_ALPHA_NON_HIER = 0,                /*!< Non Hierarchical */
   NFE_ALPHA_1        = 1,                /*!< Alpha 1 */
   NFE_ALPHA_2        = 2,                /*!< Alpha 2 */
   NFE_ALPHA_4        = 3                 /*!< Alpha 4 */
} NFE_Alpha;


typedef enum _tag_NFE_TS_Priority      /* COFDM (eg. DVB-T) signal type parameter - hiearchical modulation */
{
   NFE_TS_PRIORITY_LOW  = 0,              /*!< DVB-T Low Priority */
   NFE_TS_PRIORITY_HIGH = 1               /*!< DVB-T High Priority */
} NFE_TS_Priority;


typedef enum _tag_NFE_DVBT2_StreamType
{
   NFE_DVBT2_STREAM_TYPE_TS    = 0,       /*!< DVB-T2 Stream type as Transport Stream (TS) only */
   NFE_DVBT2_STREAM_TYPE_GS    = 1,       /*!< DVB-T2 Stream type as Generic Stream (GS) only */
   NFE_DVBT2_STREAM_TYPE_TS_GS = 2        /*!< DVB-T2 Stream type as Mixed GS and TS Streams */
} NFE_DVBT2_StreamType;


typedef enum _tag_NFE_DVBT2_FECType
{
   NFE_DVBT2_FEC_TYPE_LDPC_16K = 0,       /*!< DVB-T2  */
   NFE_DVBT2_FEC_TYPE_LDPC_64K = 1        /*!< DVB-T2  */
} NFE_DVBT2_FECType;


typedef enum _tag_NFE_DVBT2_s1Type
{
   NFE_DVBT2_S1_TYPE_SISO      = 0,       /*!< DVB-T2 S1 Type is SISO */
   NFE_DVBT2_S1_TYPE_MISO      = 1,       /*!< DVB-T2 S1 Type is MISO */
   NFE_DVBT2_S1_TYPE_NOT_DVBT2 = 2        /*!< None DVB-T2 */
} NFE_DVBT2_s1Type;


typedef enum _tag_NFE_DVBT2_s2Type     /* DVB-T2 spec item definition */
{
   NFE_DVBT2_S2_TYPE_2K_ANY    = 0,       /*!< DVBT2 S2 Type 2K any Guard */
   NFE_DVBT2_S2_TYPE_8K_DVBT   = 1,       /*!< DVBT2 S2 Type 8K DVBT Guard */
   NFE_DVBT2_S2_TYPE_4K_ANY    = 2,       /*!< DVBT2 S2 Type 4K any Guard */
   NFE_DVBT2_S2_TYPE_1K_ANY    = 3,       /*!< DVBT2 S2 Type 1K any Guard */
   NFE_DVBT2_S2_TYPE_16K_ANY   = 4,       /*!< DVBT2 S2 Type 16K any Guard */
   NFE_DVBT2_S2_TYPE_32K_DVBT  = 5,       /*!< DVBT2 S2 Type 32K DVBT Guard */
   NFE_DVBT2_S2_TYPE_8K_DVBT2  = 6,       /*!< DVBT2 S2 Type 8K DVBT2 Guard */
   NFE_DVBT2_S2_TYPE_32K_DVBT2 = 7        /*!< DVBT2 S2 Type 32K DVBT2 Guard */
} NFE_DVBT2_s2Type;


typedef enum _tag_NFE_DVBT2_papr
{
   NFE_DVBT2_PAPR_NONE   = 0,             /*!< DVB-T2 PAPR None */
   NFE_DVBT2_PAPR_ACE    = 1,             /*!< DVB-T2 PAPR ACE Algorithm */
   NFE_DVBT2_PAPR_TR     = 2,             /*!< DVB-T2 PAPR TR */
   NFE_DVBT2_PAPR_TR_ACE = 3              /*!< DVB-T2 PAPR TR and ACE */
} NFE_DVBT2_papr;


typedef enum _tag_NFE_DVBT2_PilotPattern
{
   NFE_DVBT2_PP1 = 0,                     /*!< DVB-T2 Pilot Pattern 1 */
   NFE_DVBT2_PP2 = 1,                     /*!< DVB-T2 Pilot Pattern 2 */
   NFE_DVBT2_PP3 = 2,                     /*!< DVB-T2 Pilot Pattern 3 */
   NFE_DVBT2_PP4 = 3,                     /*!< DVB-T2 Pilot Pattern 4 */
   NFE_DVBT2_PP5 = 4,                     /*!< DVB-T2 Pilot Pattern 5 */
   NFE_DVBT2_PP6 = 5,                     /*!< DVB-T2 Pilot Pattern 6 */
   NFE_DVBT2_PP7 = 6,                     /*!< DVB-T2 Pilot Pattern 7 */
   NFE_DVBT2_PP8 = 7                      /*!< DVB-T2 Pilot Pattern 8 */
} NFE_DVBT2_PilotPattern;


typedef enum _tag_NFE_DVBT2_PlpType
{
   NFE_DVBT2_PLP_TYPE_COMMON = 0,         /*!< DVB-T2 PLP type COMMON */
   NFE_DVBT2_PLP_TYPE_DATA1  = 1,         /*!< DVB-T2 PLP type DATA 1 */
   NFE_DVBT2_PLP_TYPE_DATA2  = 2          /*!< DVB-T2 PLP type DATA 2 */
} NFE_DVBT2_PlpType;


typedef enum _tag_NFE_DVBT2_PlpPayloadType
{
   NFE_DVBT2_PLP_PAYLOAD_TYPE_GFPS = 0,   /*!< DVB-T2 PLP payload Generic Fixed-length Packetized Stream (GFPS) */
   NFE_DVBT2_PLP_PAYLOAD_TYPE_GCS  = 1,   /*!< DVB-T2 PLP payload Generic Continuous Stream (GCS) */
   NFE_DVBT2_PLP_PAYLOAD_TYPE_GSE  = 2,   /*!< DVB-T2 PLP payload Generic Stream Encapsulation (GSE) */
   NFE_DVBT2_PLP_PAYLOAD_TYPE_TS   = 3    /*!< DVB-T2 PLP payload Transport Stream */
} NFE_DVBT2_PlpPayloadType;


typedef enum _tag_NFE_StandbyMode      /* Frontend standby level, this may not be supported by all frontends */
{
   NFE_STANDBY_OFF               = 0,     /*!< Normal Power on State */
   NFE_STANDBY_LOOPTHROUGH       = 1,     /*!< Standby with Loopthrough enabled */
   NFE_STANDBY_NORMAL            = 254,   /*!< Standby Recoverable, Low power mode supported by chip */
   NFE_STANDBY_DEEP              = 255    /*!< Standby, May be non-recoverable, H/W reset and re init may be required */
} NFE_StandbyMode;


typedef struct _tag_NFE_EquCoeffs      /* Adaptive equaliser coefficents - only appropriate for cable signals */
{
   NFE_UInt16 real;
   NFE_UInt16 imaginary;
} NFE_EquCoeffs;

/** \brief Frontend Mode

    The different frontend mode supported
    Macro                           | Description
    :-------------------------------|--------------------------------------------------------------------
    NFE_MODE_DVBS                   | Frontend mode Satellite DVB-S
    NFE_MODE_DVBS2                  | Frontend mode Satellite DVB-S2
    NFE_MODE_DVBS2X                 | Frontend mode Satellite DVB-S2X
    NFE_MODE_DSS                    | Frontend mode Satellite DSS
    NFE_MODE_CABLE_INBAND_ANNEXE_A  | Frontend mode Cable Annex A
    NFE_MODE_CABLE_INBAND_ANNEXE_B  | Frontend mode Cable Annex B
    NFE_MODE_CABLE_OOB_A            | Frontend mode Cable Out Off Band A
    NFE_MODE_CABLE_OOB_B            | Frontend mode Cable Out Off Band B
    NFE_MODE_DVBT                   | Frontend mode Terrestrial DVB-T
    NFE_MODE_ATSC                   | Frontend mode Terrestrial ATSC
    NFE_MODE_ISDBT                  | Frontend mode Terrestrial ISDB-T
    NFE_MODE_SATCR_TONE_DETECT      | Frontend mode Satellite SATCR Mode
    NFE_MODE_DVBT2                  | Frontend mode Terrestrial DVB-T2
    NFE_MODE_DVBC2                  | Frontend mode Cable DVB-C2
*/
typedef NFE_UInt32 NFE_Mode;           /* Bitfield describing supported frontend mode(s), eg cable, satellite etc */
#define NFE_MODE_DVBS                  0x00001
#define NFE_MODE_DVBS2                 0x00002
#define NFE_MODE_DSS                   0x00004
#define NFE_MODE_DVBS2X                0x00008
#define NFE_MODE_CABLE_INBAND_ANNEXE_A 0x00010
#define NFE_MODE_CABLE_INBAND_ANNEXE_B 0x00020
#define NFE_MODE_CABLE_OOB_A           0x00040
#define NFE_MODE_CABLE_OOB_B           0x00080
#define NFE_MODE_DVBT                  0x01000
#define NFE_MODE_ATSC                  0x02000
#define NFE_MODE_ISDBT                 0x04000
#define NFE_MODE_SATCR_TONE_DETECT     0x08000
#define NFE_MODE_DVBT2                 0x10000
#define NFE_MODE_DVBC2                 0x20000

#if NFE_SUPPORT_CDI_18_FEATURES
/*Features supported by the Frontend: Required for CDI_ISSUE18 and >*/

/** \brief Frontend Mode

    Features supported by the Frontend: Required for CDI_ISSUE18 and later
    Macro                          | Description
    :------------------------------|--------------------------------------------------------------------
    NFE_FEATURE_PREVITERBI         | To enable Pre-Viterbi BER
    NFE_FEATURE_PER                | To enable BER reporting
    NFE_FEATURE_SNR                | To enable SNR reporting
    NFE_FEATURE_FAST_LOCK_FAIL     | Indicates whether can report no-signal more quickly than standard timeout
    NFE_FEATURE_MULTIMODE_SCAN     | Indicates whether can scan multiple modes simultaneously
    NFE_FEATURE_SCAN_NO_CLOSE      | Indicates if the scan operation needs to be explictly closed on completion or not
*/
typedef NFE_UInt32 NFE_Feature;        /* Bitfield describing supported frontend features */
#define NFE_FEATURE_PREVITERBI         0x0001
#define NFE_FEATURE_PER                0x0002
#define NFE_FEATURE_SNR                0x0004
#define NFE_FEATURE_FAST_LOCK_FAIL     0x0008
#define NFE_FEATURE_MULTIMODE_SCAN     0x0010
#define NFE_FEATURE_SCAN_NO_CLOSE      0x0020
#endif /*#if NFE_SUPPORT_CDI_18_FEATURES*/

/** \brief Frontend Handle to identify a frontend instance uniquely
*/
typedef NFE_Void *NFE_Handle;          /* The method of uniquely identifying a frontend */


/*valid NFE events*/
typedef enum
{
   NFE_EVENT_LOCKED = 1,                  /*!< Frontend locked event for either new tune request or recover from LOST LOCK condition */
   NFE_EVENT_ACQ_FAILED,                  /*!< Frontend acquisition failed Event for new tune request */
   NFE_EVENT_LOST_LOCK,                   /*!< Frontend lost lock Event when the signal is already successfully tuned and lost lock */
   NFE_EVENT_HARDWARE_INIT_SUCCEEDED,     /*!< Frontend hardware init successfully happened */
   NFE_EVENT_HARDWARE_INIT_FAILED,        /*!< Frontend hardware init failed */
   NFE_EVENT_HARDWARE_ERROR,              /*!< Frontend hardware error found (I2C error ) - Depricated */
   NFE_EVENT_FREQUENCY_LIMIT,             /*!< Frontend scanning algorithm reached end of search */
   NFE_EVENT_STOPPED,                     /*!< Frontend module is successfully stopped */
#if NFE_SUPPORT_SATCR_TONE
   NFE_EVENT_SATCR_TONE_DETECT_COMPLETE,  /*!< SatCR Tone Detection completed, but not found any tone */
   NFE_EVENT_SATCR_TONE_DETECT_FOUND,     /*!< SatCR Tone Detected */
#endif
   NFE_EVENT_TUNING,                      /*!< Frontend tuning is invoked successfully, but it may fail/success to find carrier */
   NFE_EVENT_INCREMENT_SCAN_BAND,         /*!< Frontend scanning is trying next carrier */
#if NFE_SUPPORT_BER_READY_EVENT
   NFE_EVENT_BER_READY,                   /*!< Frontend BER aynchronous ready status intimation to caller */
#endif
   NFE_EVENT_LAST                         /*!< Unused - placeholder to give out of range test value*/
} NFE_Event;


typedef NFE_UInt32 NFE_AsyncID;           /*!< Unique request identifier to map the asynchronous events againt with request */


/** \brief Frontend Event Callback funtion
    \param [out] handleFE  Frontend handle
    \param [out] event     Any one of the frontend event
    \param [out] asyncID   Frontend Request ID to associate events
    \param [out] user      User data pointer which is passed in NFE_registerCallback api
    <b>Description :</b>\n
     Callback will be called to notify NFE events to the application or middleware.
*/
typedef NFE_Void(*NFE_EventCallback)(NFE_Handle handleFE, NFE_Event event, NFE_AsyncID asyncID, NFE_Void *user);


/*tune params - specific to each frontend/signal type*/
typedef struct
{
   NFE_Frequency  frequency;            /*!< Requested satellite IF frequency in Hz */
   NFE_Spectrum   spectrum;             /*!< Requested spectrum  */
   NFE_SymbolRate symbolRate;           /*!< Requested symbolrate in Symbols/sec */
   NFE_CodeRate   codeRate;             /*!< Requested coderate */
} NFE_DvbsTune;


typedef struct
{
   NFE_Frequency  frequency;            /*!< Requested satellite IF frequency in Hz */
   NFE_Spectrum   spectrum;             /*!< Requested spectrum */
   NFE_Modulation modulation;           /*!< Requested modulation */
   NFE_SymbolRate symbolRate;           /*!< Requested symbolrate in Symbols/sec */
   NFE_CodeRate   codeRate;             /*!< Requested coderate */
   NFE_Pilot      pilot;                /*!< Requested pilot */
   NFE_RollOff    rollOff;              /*!< Requested rolloff */
} NFE_Dvbs2Tune;

typedef struct
{
   NFE_Frequency  frequency;          /*in Hz*/
   NFE_Spectrum   spectrum;
   NFE_Modulation modulation;
   NFE_SymbolRate symbolRate;         /*in Symbols/s*/
   NFE_CodeRate   codeRate;
   NFE_Bool       linear;             /*enable mod/cod for linear channels*/
   NFE_Pilot      pilot;
   NFE_RollOff    rollOff;
} NFE_Dvbs2xTune;

typedef struct
{
   NFE_Frequency  frequency;            /*!< Requested satellite IF frequency in Hz */
   NFE_Spectrum   spectrum;             /*!< Requested spectrum */
   NFE_SymbolRate symbolRate;           /*!< Requested symbolrate in Symbols/sec */
   NFE_CodeRate   codeRate;             /*!< Requested coderate */
} NFE_DssTune;


typedef struct
{
   NFE_Frequency  frequency;            /*!< Requested frequency in Hz */
   NFE_Spectrum   spectrum;             /*!< Requested spectrum */
   NFE_SymbolRate symbolRate;           /*!< Requested symbolrate in Symbols/sec */
   NFE_Modulation modulation;           /*!< Requested modulation */
} NFE_CableIbTune;


typedef struct
{
   NFE_Frequency  frequency;            /*!< Requested frequency in Hz */
   NFE_Spectrum   spectrum;             /*!< Requested spectrum */
   NFE_SymbolRate symbolRate;           /*!< Requested symbolrate in Symbols/sec */
} NFE_CableOobTune;


typedef struct
{
   NFE_Frequency   frequency;           /*!< Requested frequency in Hz */
   NFE_Spectrum    spectrum;            /*!< Requested spectrum */
   NFE_Bandwidth   bw;                  /*!< Requested bandwidth */
   NFE_CodeRate    codeRate;            /*!< Requested coderate */
   NFE_Modulation  modType;             /*!< Requested modulation type */
   NFE_FFTSize     fftSize;             /*!< Requested transmisson mode */
   NFE_Guardband   guardBand;           /*!< Requested guard interval */
   NFE_Alpha       alpha;               /*!< Requested alpha */
   NFE_TS_Priority tsPriority;          /*!< Requested TS priority */
} NFE_DvbtTune;


typedef struct
{
   NFE_Frequency  frequency;            /*!< Requested frequency in Hz */
   NFE_Spectrum   spectrum;             /*!< Requested spectrum */
   NFE_Bandwidth  bw;                   /*!< Requested bandwidth, a BLIND acquisition should only require these first 3 parameters*/
   NFE_UInt8      plpId;                /*!< Requested PLP ID to recover the specific PLP, unless isBlindTune is set*/
   NFE_Bool       isBlindTune;          /*!< If TRUE the tune will o/p the 'first' PLP bydefault in the list, or it will use the above PLP id */
} NFE_Dvbt2Tune;


typedef struct
{
   NFE_Frequency  frequency;            /*!< Requested frequency in Hz */
   NFE_Spectrum   spectrum;             /*!< Requested spectrum */
   NFE_Modulation modulation;           /*!< Requested modulation */
} NFE_AtscTune;


typedef struct
{
   NFE_Frequency frequency;            /*!< Requested SatCR tone frequency in Hz */
   NFE_Frequency width;                /*!< Requested width of tone */
} NFE_SatCRTune;


typedef struct
{
   NFE_Frequency frequency;            /*!< Requested frequency in Hz */
   NFE_Spectrum  spectrum;             /*!< Requested spectrum */
   NFE_Bandwidth bw;                   /*!< Requested bandwidth */
   NFE_FFTSize   fftSize;              /*!< Requested transmission mode */
   NFE_Guardband guardBand;            /*!< Requested gurad interval */
} NFE_IsdbtTune;


typedef union
{
#if NFE_SUPPORT_SATELLITE
   NFE_DvbsTune        dvbs;            /*!< Satellite DVB-S Tuning parameters */
   NFE_Dvbs2Tune       dvbs2;           /*!< Satellite DVB-S2 Tuning parameters */
   NFE_Dvbs2xTune      dvbs2x;          /*!< Satellite DVB-S2x Tuning parameters */
   NFE_DssTune         dss;             /*!< Satellite DSS Tuning parameters */
#endif
#if NFE_SUPPORT_CABLE
   NFE_CableIbTune     cabIb;           /*!< Cable DVB-C inband Tuning parameters */
   NFE_CableOobTune    cabOob;          /*!< Cable DVB-C outoff band Tuning parameters */
#endif
#if NFE_SUPPORT_DVBT
   NFE_DvbtTune        dvbt;            /*!< Terrestrial DVB-T Tuning parameters */
#endif
#if NFE_SUPPORT_DVBT2
   NFE_Dvbt2Tune       dvbt2;           /*!< Terrestrial DVB-T2 Tuning parameters */
#endif
#if NFE_SUPPORT_ATSC
   NFE_AtscTune        atsc;            /*!< Terrestrial ATSC Tuning parameters */
#endif
#if NFE_SUPPORT_SATCR_TONE
   NFE_SatCRTune       satCR;           /*!< Satellite SatCR Tuning parameters */
#endif
#if NFE_SUPPORT_ISDBT
   NFE_IsdbtTune       isdbt;           /*!< Terrestrial ISDB-T Tuning parameters */
#endif
} NFE_TuneEntries;


typedef struct
{
   NFE_Mode        mode;                /*!< Frontend mode (DVB-S/S2/C/T/T2,.. etc ) */
   NFE_TuneEntries tune;                /*!< Frontend tuning params respective for the above mentioned frontend mode */
} NFE_Tune;


/* Scan control */
/* each ScanEntry lists one signal type to search for, i.e. only one of each bitfield type can be set*/
typedef struct
{
   NFE_SymbolRate symbolRate;           /*!< Requested symbolrate in Symbols/sec */
   NFE_CodeRate   codeRate;             /*!< Requested coderate */
   NFE_Spectrum   spectrum;             /*!< Requested spectrum */
} NFE_DvbsScanEntry;


typedef struct
{
   NFE_SymbolRate symbolRate;           /*!< Requested symbolrate in Symbols/sec */
   NFE_CodeRate   codeRate;             /*!< Requested coderate */
   NFE_Modulation modulation;           /*!< Requested modulation */
   NFE_Pilot      pilot;                /*!< Requested pilot */
   NFE_RollOff    rollOff;              /*!< Requested rolloff */
   NFE_Spectrum   spectrum;             /*!< Requested spectrum */
} NFE_Dvbs2ScanEntry;


typedef struct
{
   NFE_SymbolRate symbolRate;           /*!< Requested symbolrate in Symbols/sec */
   NFE_CodeRate   codeRate;             /*!< Requested coderate */
   NFE_Modulation modulation;           /*!< Requested modulation */
   NFE_Pilot      pilot;                /*!< Requested pilot */
   NFE_RollOff    rollOff;              /*!< Requested rolloff */
   NFE_Spectrum   spectrum;             /*!< Requested spectrum */
   NFE_Bool       linear;               /*!< Enable mod/cod for linear channels */
} NFE_Dvbs2xScanEntry;


typedef struct
{
   NFE_SymbolRate symbolRate;           /*!< Requested symbolrate in Symbols/sec */
   NFE_CodeRate   codeRate;             /*!< Requested coderate */
   NFE_Spectrum   spectrum;             /*!< Requested spectrum */
} NFE_DssScanEntry;


typedef struct
{
   NFE_SymbolRate symbolRate;           /*!< Requested symbolrate in Symbols/sec */
   NFE_Modulation modulation;           /*!< Requested modulation */
   NFE_Spectrum   spectrum;             /*!< Requested spectrum */
} NFE_CabIbScanEntry;

/* There is only ever ONE entry for a scan involving these following two modes */
typedef struct
{
   NFE_Modulation modulation;           /*!< Requested modulation */
   NFE_Spectrum   spectrum;             /*!< Requested spectrum */
} NFE_AtscScanEntry;


typedef struct
{
   NFE_Bandwidth  bw;                   /*!< Requested bandwidth */
   NFE_Spectrum   spectrum;             /*!< Requested spectrum */
} NFE_DvbtScanEntry;


typedef struct
{
   NFE_Bandwidth  bw;                   /*!< Requested bandwidth */
   NFE_Spectrum   spectrum;             /*!< Requested spectrum */
} NFE_Dvbt2ScanEntry;


typedef struct
{
   NFE_Bandwidth  bw;                   /*!< Requested bandwidth */
   NFE_Spectrum   spectrum;             /*!< Requested spectrum */
} NFE_IsdbtScanEntry;


typedef union
{
#if NFE_SUPPORT_SATELLITE
   NFE_DvbsScanEntry   dvbs;             /*!< Satellite DVB-S Scanning parameters */
   NFE_Dvbs2ScanEntry  dvbs2;            /*!< Satellite DVB-S2 Scanning parameters */
   NFE_Dvbs2xScanEntry dvbs2x;           /*!< Satellite DVB-S2x Scanning parameters */
   NFE_DssScanEntry    dss;              /*!< Satellite DSS Scanning parameters */
#endif
#if NFE_SUPPORT_CABLE
   NFE_CabIbScanEntry  cabIb;            /*!< Cable DVB-C Inband Scanning parameters */
#endif
#if NFE_SUPPORT_ATSC
   NFE_AtscScanEntry   atsc;             /*!< Terrestrial ATSC Scanning parameters */
#endif
#if NFE_SUPPORT_DVBT
   NFE_DvbtScanEntry   dvbt;             /*!< Terrestrial DVB-T Scanning parameters */
#endif
#if NFE_SUPPORT_DVBT2
   NFE_Dvbt2ScanEntry  dvbt2;            /*!< Terrestrial DVB-T2 Scanning parameters */
#endif
#if NFE_SUPPORT_ISDBT
   NFE_IsdbtScanEntry  isdbt;            /*!< Terrestrial ISDB-T Scanning parameters */
#endif
} NFE_ScanEntries;


typedef struct
{
   NFE_Mode        mode;                /*!< Frontend mode (DVB-S/S2/C/T/T2,.. etc ) */
   NFE_ScanEntries scan;                /*!< Frontend scanning params respective for the above mentioned frontend mode */
} NFE_ScanEntry;


/*status params - specific to each frontend/signal type*/
typedef struct
{
   NFE_LockState  lockState;            /*!< Frontend lock status */
   NFE_Frequency  carrierFrequency;     /*!< Frontend locked exact carrier frequency in Hz, including frequency offset */
   NFE_Spectrum   spectrum;             /*!< Locked signal spectrum sense */
   NFE_SymbolRate symbolRate;           /*!< Locked signal symbolrate in Symbols/sec, including symbol offset */
   NFE_CodeRate   codeRate;             /*!< Locked signal code rate */
} NFE_DvbsStatus;


typedef struct
{
   NFE_LockState   lockState;           /*!< Frontend lock status */
   NFE_Frequency   carrierFrequency;    /*!< Frontend locked exact carrier frequency in Hz, including frequency offset */
   NFE_Spectrum    spectrum;            /*!< Locked signal spectrum sense */
   NFE_SymbolRate  symbolRate;          /*!< Locked signal symbolrate in Symbols/sec, including symbol offset */
   NFE_CodeRate    codeRate;            /*!< Locked signal code rate */
   NFE_Modulation  modulation;          /*!< Locked signal modulation */
   NFE_Pilot       pilot;               /*!< Locked signal pilot status */
   NFE_RollOff     rollOff;             /*!< Locked signal rolloff factor */
} NFE_Dvbs2Status;


typedef struct
{
   NFE_LockState  lockState;            /*!< Frontend lock status */
   NFE_Frequency  carrierFrequency;     /*!< Frontend locked exact carrier frequency in Hz, including frequency offset */
   NFE_Spectrum   spectrum;             /*!< Locked signal spectrum sense */
   NFE_SymbolRate symbolRate;           /*!< Locked signal symbolrate in Symbols/sec, including symbol offset */
   NFE_CodeRate   codeRate;             /*!< Locked signal code rate */
   NFE_Modulation modulation;           /*!< Locked signal modulation */
   NFE_Pilot      pilot;                /*!< Locked signal pilot status */
   NFE_RollOff    rollOff;              /*!< Locked signal rolloff factor */
   NFE_Bool       linear;               /*!< Locked signal mod/cod for linear channels which is enabled */
} NFE_Dvbs2xStatus;


typedef struct
{
   NFE_LockState  lockState;            /*!< Frontend lock status */
   NFE_Frequency  carrierFrequency;     /*!< Frontend locked exact carrier frequency in Hz, including frequency offset */
   NFE_Spectrum   spectrum;             /*!< Locked signal spectrum sense */
   NFE_SymbolRate symbolRate;           /*!< Locked signal symbolrate in Symbols/sec, including symbol offset */
   NFE_CodeRate   codeRate;             /*!< Locked signal code rate */
} NFE_DssStatus;


typedef struct
{
   NFE_LockState  lockState;            /*!< Frontend lock status */
   NFE_Frequency  carrierFrequency;     /*!< Frontend locked exact carrier frequency in Hz, including frequency offset */
   NFE_Spectrum   spectrum;             /*!< Locked signal spectrum sense */
   NFE_SymbolRate symbolRate;           /*!< Locked signal symbolrate in Symbols/sec, including symbol offset */
   NFE_Modulation modulation;           /*!< Locked signal modulation */
} NFE_CableIbStatus;


typedef struct
{
   NFE_LockState  lockState;            /*!< Frontend lock status */
   NFE_UInt32     carrierFrequency;     /*!< Frontend locked exact carrier frequency in Hz, including frequency offset */
   NFE_Spectrum   spectrum;             /*!< Locked signal spectrum sense */
   NFE_SymbolRate symbolRate;           /*!< Locked signal symbolrate in Symbols/sec, including symbol offset */
} NFE_CableOobStatus;


typedef struct
{
   NFE_LockState   lockState;           /*!< Frontend lock status */
   NFE_Frequency   carrierFrequency;    /*!< Frontend locked exact carrier frequency in Hz, including frequency offset */
   NFE_Spectrum    spectrum;            /*!< Locked signal spectrum sense */
   NFE_Bandwidth   bw;                  /*!< Locked signal bandwidth */
   NFE_CodeRate    codeRate;            /*!< Locked signal coderate */
   NFE_Modulation  modulation;          /*!< Locked signal modulation */
   NFE_FFTSize     fftSize;             /*!< Locked signal transmission mode */
   NFE_Guardband   guardBand;           /*!< Locked signal guard interval */
   NFE_UInt16      cellId;              /*!< Locked signal DVB-T CELL ID */
   NFE_Alpha       alpha;               /*!< Locked signal alpha */
   NFE_TS_Priority tsPriority;          /*!< Locked signal TS Priority */
} NFE_DvbtStatus;


typedef struct
{
   NFE_LockState           lockState;        /*!< Frontend lock status */
   NFE_Frequency           carrierFrequency; /*!< Frontend locked exact carrier frequency in Hz, including frequency offset */
   NFE_Spectrum            spectrum;         /*!< Locked signal spectrum sense */
   NFE_Bandwidth           bw;               /*!< Locked signal bandwidth */
   NFE_CodeRate            codeRate;         /*!< Code rate of current locked PLP */
   NFE_Modulation          modulation;       /*!< Modulation scheme of current locked PLP */
   NFE_FFTSize             fftSize;          /*!< Transmission mode of entire DVB-T2 signal*/
   NFE_Guardband           guardBand;        /*!< Gurad band of entire DVB-T2 signal*/
   NFE_UInt16              cellId;           /*!< DVB-T2 CELL ID */
   NFE_UInt8               plpId;            /*!< Current locked PLP ID */
   NFE_DVBT2_PilotPattern  pilotPattern;     /*!< Current pilot pattern*/
   NFE_DVBT2_papr          paprPattern;      /*!< Current papr mode*/
   NFE_DVBT2_s1Type        TxSy;             /*!< Current S1 type MISO/SISO */
   NFE_UInt8               rotation;         /*!< Current constellation rotated status */
} NFE_Dvbt2Status;


typedef struct
{
   NFE_LockState  lockState;            /*!< Frontend lock status */
   NFE_Frequency  carrierFrequency;     /*!< Frontend locked exact carrier frequency in Hz, including frequency offset */
   NFE_Spectrum   spectrum;             /*!< Locked signal spectrum sense */
   NFE_Modulation modulation;           /*!< Locked signal modulation */
} NFE_AtscStatus;


typedef struct
{
   NFE_Bool      found;                /*!< SatCR tone found status */
   NFE_Frequency tone;                 /*!< SatCR tone frequency in Hz */
} NFE_SatCRStatus;


typedef struct
{
   NFE_LockState  lockState;           /*!< Frontend lock status */
   NFE_Frequency  carrierFrequency;    /*!< Frontend locked exact carrier frequency in Hz, including frequency offset */
   NFE_Spectrum   spectrum;            /*!< Locked signal spectrum sense */
   NFE_Bandwidth  bw;                  /*!< Locked signal bandwidth */
   NFE_CodeRate   codeRateA;           /*!< Locked ISDB-T Layer A coderate */
   NFE_CodeRate   codeRateB;           /*!< Locked ISDB-T Layer B coderate */
   NFE_CodeRate   codeRateC;           /*!< Locked ISDB-T Layer C coderate */
   NFE_Modulation modulationA;         /*!< Locked ISDB-T Layer A modulation */
   NFE_Modulation modulationB;         /*!< Locked ISDB-T Layer B modulation */
   NFE_Modulation modulationC;         /*!< Locked ISDB-T Layer C modulation */
   NFE_UInt8      TimeInterA;          /*!< Locked ISDB-T Layer A Time interleaver */
   NFE_UInt8      TimeInterB;          /*!< Locked ISDB-T Layer B Time interleaver */
   NFE_UInt8      TimeInterC;          /*!< Locked ISDB-T Layer C Time interleaver */
   NFE_FFTSize    fftSize;             /*!< Locked transmission mode */
   NFE_Guardband  guardBand;           /*!< Locked guard interval */
} NFE_IsdbtStatus;


typedef union
{
#if NFE_SUPPORT_SATELLITE
   NFE_DvbsStatus        dvbs;          /*!< Satellite DVB-S signal status */
   NFE_Dvbs2Status       dvbs2;         /*!< Satellite DVB-S2 signal status */
   NFE_Dvbs2xStatus      dvbs2x;        /*!< Satellite DVB-S2x signal status */
   NFE_DssStatus         dss;           /*!< Satellite DSS signal status */
#endif
#if NFE_SUPPORT_CABLE
   NFE_CableIbStatus     cabIb;         /*!< Cable DVB-C In Band signal status */
   NFE_CableOobStatus    cabOob;        /*!< Cable DVB-C Out Off Band signal status */

#endif
#if NFE_SUPPORT_DVBT
   NFE_DvbtStatus        dvbt;          /*!< Terrestrial DVB-T signal status */
#endif
#if NFE_SUPPORT_DVBT2
   NFE_Dvbt2Status       dvbt2;         /*!< Terrestrial DVB-T2 signal status */
#endif
#if NFE_SUPPORT_ATSC
   NFE_AtscStatus        atsc;          /*!< Terrestrial ATSC signal status */
#endif
#if NFE_SUPPORT_SATCR_TONE
   NFE_SatCRStatus       satCR;         /*!< Satellite SatCR signal status */
#endif
#if NFE_SUPPORT_ISDBT
   NFE_IsdbtStatus       isdbt;         /*!< Terrestrial ISDB-T signal status */
#endif
} NFE_StatusEntries;


typedef struct
{
   NFE_Mode          mode;              /*!< Frontend mode (DVB-S/S2/C/T/T2,.. etc ) */
   NFE_Mode          last_tuned_mode;   /*!< Last tuned mode to be exposed to applicaiton*/
   NFE_StatusEntries status;            /*!< Frontend signal status, respective for the above mentioned frontend mode */
} NFE_Status;


#if NFE_SUPPORT_CDI_18_ERROR_STATS
/*Error Statistics data. Contains all possible error data for DVB-S S2 DSS */

typedef struct
{
   NFE_Bool valid;
   NFE_BER  berWindow;
   NFE_BER  corrCount;
   NFE_BER  unCorrCount;
} NFE_ErrorInnerLoop;


typedef struct
{
   NFE_Bool valid;
   NFE_BER  pktWindow;
   NFE_BER  corrPktCount;
   NFE_BER  unCorrPktCount;
} NFE_ErrorOuterLoop;


typedef struct
{
   NFE_BER            preLoopErrors;
   NFE_ErrorInnerLoop innerLoop;
   NFE_ErrorOuterLoop outerLoop;
} NFE_ErrorStats;
#endif /*#if NFE_SUPPORT_CDI_18_ERROR_STATS*/


/*diagnostics params - specific to each frontend/signal type*/
typedef struct
{
   NFE_LockState lockState;             /*!< Frontend lock status */
   NFE_LockTime  acquisitionTime;       /*!< Signal acquisition time in ms */
   NFE_LockTime  notLockedTime;         /*!< If fail to lock, this gives how long it took to decide no lock in ms*/
   NFE_Offset    demodOffset;           /*!< IF freq error resolved purely in demod in Hz */
   NFE_Offset    lnbOffset;             /*!< Freq error caused purely by the LNB in Hz */
   NFE_SNR       sigNoise;              /*!< SNR estimate in tenths of a dB */
   NFE_AGC       demodAGC;              /*!< Raw AGC register value from demod */
   NFE_UInt8     signalLevel;           /*!< SignalLevel in .5dBm steps. The values are scaled between (0 to 255) [0 = -127.5dBm, 255 = 0dBm]*/
   NFE_BER       berWindow;             /*!< Num of bits used for BER Calculation */
   NFE_BER       rsCorrectedBer;        /*!< The number of errors corrected by RS block (Post Viterbi / Pre RS)*/
   NFE_BER       rsUncorrected;         /*!< RS Uncorrected error packet count */
   NFE_BER       berReadyCount;         /*!< BER Ready count */
   NFE_BER       preViterbiCnt;         /*!< The number of errors occured before Viterbi block */
#if NFE_SUPPORT_CDI_18_ERROR_STATS
   NFE_ErrorStats errorStats;           /*!< NDS Specific error formats */
#endif
} NFE_DvbsDiagnostics;


typedef struct
{
   NFE_LockState lockState;             /*!< Frontend lock status */
   NFE_LockTime  acquisitionTime;       /*!< Signal acquisition time in ms */
   NFE_LockTime  notLockedTime;         /*!< If fail to lock, this gives how long it took to decide no lock in ms*/
   NFE_Offset    demodOffset;           /*!< IF freq error resolved purely in demod in Hz */
   NFE_Offset    lnbOffset;             /*!< Freq error caused purely by the LNB in Hz */
   NFE_SNR       sigNoise;              /*!< SNR estimate in tenths of a dB */
   NFE_AGC       demodAGC;              /*!< Raw AGC register value from demod */
   NFE_UInt8     signalLevel;           /*!< SignalLevel in .5dBm steps. The values are scaled between (0 to 255) [0 = -127.5dBm, 255 = 0dBm]*/
   NFE_BER       berWindow;             /*!< Num of bits used for BER Calculation */
   NFE_BER       rsUncorrected;         /*!< RS Uncorrected error packet count */
   NFE_BER       berReadyCount;         /*!< BER Ready count */
#if NFE_SUPPORT_CDI_18_ERROR_STATS
   NFE_ErrorStats errorStats;           /*!< NDS Specific error formats */
#endif
} NFE_Dvbs2Diagnostics;


typedef struct
{
   NFE_LockState lockState;             /*!< Frontend lock status */
   NFE_LockTime  acquisitionTime;       /*!< Signal acquisition time in ms */
   NFE_LockTime  notLockedTime;         /*!< If fail to lock, this gives how long it took to decide no lock in ms*/
   NFE_Offset    demodOffset;           /*!< IF freq error resolved purely in demod in Hz */
   NFE_Offset    lnbOffset;             /*!< Freq error caused purely by the LNB in Hz */
   NFE_SNR       sigNoise;              /*!< SNR estimate in tenths of a dB */
   NFE_AGC       demodAGC;              /*!< Raw AGC register value from demod */
   NFE_UInt8     signalLevel;           /*!< SignalLevel in .5dBm steps. The values are scaled between (0 to 255) [0 = -127.5dBm, 255 = 0dBm]*/
   NFE_BER       berWindow;             /*!< Num of bits used for BER Calculation */
   NFE_BER       rsCorrectedBer;        /*!< The number of errors corrected by RS block (Post Viterbi / Pre RS)*/
   NFE_BER       rsUncorrected;         /*!< RS Uncorrected error packet count */
   NFE_BER       berReadyCount;         /*!< BER Ready count */
#if NFE_SUPPORT_CDI_18_ERROR_STATS
   NFE_ErrorStats errorStats;           /*!< NDS Specific error formats */
#endif
} NFE_Dvbs2xDiagnostics;


typedef struct
{
   NFE_LockState lockState;             /*!< Frontend lock status */
   NFE_LockTime  acquisitionTime;       /*!< Signal acquisition time in ms */
   NFE_LockTime  notLockedTime;         /*!< If fail to lock, this gives how long it took to decide no lock in ms*/
   NFE_Offset    demodOffset;           /*!< IF freq error resolved purely in demod in Hz */
   NFE_Offset    lnbOffset;             /*!< Freq error caused purely by the LNB in Hz */
   NFE_SNR       sigNoise;              /*!< SNR estimate in tenths of a dB */
   NFE_AGC       demodAGC;              /*!< Raw AGC register value from demod */
   NFE_UInt8     signalLevel;           /*!< SignalLevel in .5dBm steps. The values are scaled between (0 to 255) [0 = -127.5dBm, 255 = 0dBm]*/
   NFE_BER       berWindow;             /*!< Num of bits used for BER Calculation */
   NFE_BER       rsCorrectedBer;        /*!< The number of errors corrected by RS block (Post Viterbi / Pre RS)*/
   NFE_BER       rsUncorrected;         /*!< RS Uncorrected error packet count */
   NFE_BER       berReadyCount;         /*!< BER Ready count */
#if NFE_SUPPORT_CDI_18_ERROR_STATS
   NFE_ErrorStats errorStats;           /*!< NDS Specific error formats */
#endif
} NFE_DssDiagnostics;


typedef struct
{
   NFE_LockState  lockState;           /*!< Frontend lock status */
   NFE_LockTime   acquisitionTime;     /*!< Signal acquisition time in ms */
   NFE_LockTime   notLockedTime;       /*!< If fail to lock, this gives how long it took to decide no lock in ms*/
   NFE_Offset     demodOffset;         /*!< IF freq error resolved purely in demod in Hz */
   NFE_SNR        sigNoise;            /*!< SNR estimate in tenths of a dB */
   NFE_UInt8      signalLevel;         /*!< SignalLevel in .5dBm steps. The values are scaled between (0 to 255) [0 = -127.5dBm, 255 = 0dBm]*/
   NFE_BER        rsCorrectedBer;      /*!< The number of errors corrected by RS block (Post Viterbi / Pre RS)*/
   NFE_BER        rsCorrectedCount;    /*!< Required only for ENGINEWARE */
   NFE_BER        rsUncorrected;       /*!< RS Uncorrected error packet count */
   NFE_BER        rsCECAccumulated;    /*!< Required only for ENGINEWARE */
   NFE_BER        rsUECAccumulated;    /*!< Required only for ENGINEWARE */
   NFE_BER        rsSyncLosses;        /*!< Required only for ENGINEWARE */
   NFE_UInt32     numEqualizerCoeffs;
   NFE_EquCoeffs *equalizerCoeffs;
   NFE_BER        berWindow;           /*!< Num of seconds BER is calculated over*/
   NFE_BER        berReadyCount;       /*!< BER Ready count */
#if NFE_SUPPORT_CDI_18_ERROR_STATS
   NFE_ErrorStats errorStats;          /*!< NDS Specific error formats */
#endif
} NFE_CableIbDiagnostics;


typedef struct
{
   NFE_LockState  lockState;           /*!< Frontend lock status */
   NFE_LockTime   acquisitionTime;     /*!< Signal acquisition time in ms */
   NFE_LockTime   notLockedTime;       /*!< If fail to lock, this gives how long it took to decide no lock in ms*/
   NFE_Offset     demodOffset;         /*!< IF freq error resolved purely in demod in Hz */
   NFE_SNR        sigNoise;            /*!< SNR estimate in tenths of a dB */
   NFE_UInt8      signalLevel;         /*!< SignalLevel in .5dBm steps. The values are scaled between (0 to 255) [0 = -127.5dBm, 255 = 0dBm]*/
   NFE_BER        berWindow;           /*!< Num of seconds BER is calculated over*/
   NFE_BER        rsCorrectedBer;      /*!< The number of errors corrected by RS block (Post Viterbi / Pre RS)*/
   NFE_BER        rsCorrectedCount;    /*!< Required only for ENGINEWARE */
   NFE_BER        rsUncorrected;       /*!< RS Uncorrected error packet count */
   NFE_BER        rsCECAccumulated;    /*!< Required only for ENGINEWARE */
   NFE_BER        rsUECAccumulated;    /*!< Required only for ENGINEWARE */
   NFE_BER        rsSyncLosses;        /*!< Required only for ENGINEWARE */
   NFE_BER        berReadyCount;       /*!< BER Ready count */
#if NFE_SUPPORT_CDI_18_ERROR_STATS
   NFE_ErrorStats errorStats;          /*!< NDS Specific error formats */
#endif
} NFE_CableOobDiagnostics;


typedef struct
{
   NFE_LockState lockState;             /*!< Frontend lock status */
   NFE_LockTime  acquisitionTime;       /*!< Signal acquisition time in ms */
   NFE_LockTime  notLockedTime;         /*!< If fail to lock, this gives how long it took to decide no lock in ms*/
   NFE_Offset    demodOffset;           /*!< IF freq error resolved purely in demod in Hz */
   NFE_SNR       sigNoise;              /*!< SNR estimate in tenths of a dB */
   NFE_AGC       demodAGC;              /*!< Raw AGC register value from demod*/
   NFE_UInt8     signalLevel;           /*!< SignalLevel in .5dBm steps. The values are scaled between (0 to 255) [0 = -127.5dBm, 255 = 0dBm]*/
   NFE_BER       berWindow;             /*!< Num of seconds BER is calculated over*/
   NFE_BER       demodBer;              /*!< Viterbi estimate of channel BER*/
   NFE_BER       rsCorrectedBer;        /*!< The number of errors corrected by RS block (Post Viterbi / Pre RS)*/
   NFE_BER       rsUncorrected;         /*!< RS Uncorrected error packet count */
   NFE_BER       berReadyCount;         /*!< BER Ready count */
#if NFE_SUPPORT_CDI_18_ERROR_STATS
   NFE_ErrorStats errorStats;           /*!< NDS Specific error formats */
#endif
} NFE_DvbtDiagnostics;


typedef struct
{
   NFE_LockState lockState;             /*!< Frontend lock status */
   NFE_LockTime  acquisitionTime;       /*!< Signal acquisition time in ms */
   NFE_LockTime  notLockedTime;         /*!< If fail to lock, this gives how long it took to decide no lock in ms*/
   NFE_Offset    demodOffset;           /*!< IF freq error resolved purely in demod in Hz */
   NFE_SNR       sigNoise;              /*!< SNR estimate in tenths of a dB */
   NFE_AGC       demodAGC;              /*!< Raw AGC register value from demod*/
   NFE_UInt8     signalLevel;           /*!< SignalLevel in .5dBm steps. The values are scaled between (0 to 255) [0 = -127.5dBm, 255 = 0dBm]*/
   NFE_BER       berWindow;             /*!< Num of seconds BER is calculated over */
   NFE_BER       rsCorrectedBer;        /*!< The number of errors corrected by RS block (Post Viterbi / Pre RS)*/
   NFE_BER       rsUncorrected;         /*!< RS Uncorrected error packet count */
   NFE_BER       berReadyCount;         /*!< BER Ready count */
#if NFE_SUPPORT_CDI_18_ERROR_STATS
   NFE_ErrorStats errorStats;           /*!< NDS Specific error formats */
#endif
} NFE_Dvbt2Diagnostics;


typedef struct
{
   NFE_LockState lockState;             /*!< Frontend lock status */
   NFE_LockTime  acquisitionTime;       /*!< Signal acquisition time in ms */
   NFE_LockTime  notLockedTime;         /*!< If fail to lock, this gives how long it took to decide no lock in ms*/
   NFE_Offset    demodOffset;           /*!< IF freq error resolved purely in demod in Hz */
   NFE_SNR       sigNoise;              /*!< SNR estimate in tenths of a dB */
   NFE_AGC       demodAGC;              /*!< Raw AGC register value from demod */
   NFE_UInt8     signalLevel;           /*!< SignalLevel in .5dBm steps. The values are scaled between (0 to 255) [0 = -127.5dBm, 255 = 0dBm]*/
   NFE_BER       berWindow;             /*!< Num of bits BER is calculated over */
   NFE_BER       rsCorrectedBer;        /*!< The number of errors corrected by RS block (Post Viterbi / Pre RS)*/
   NFE_BER       rsUncorrected;         /*!< RS Uncorrected error packet count */
} NFE_AtscDiagnostics;


typedef struct
{
   NFE_LockState lockState;            /*!< Over all Frontend lock status */
   NFE_LockState lockStateA;           /*!< ISDB-T Layer A lock status */
   NFE_LockState lockStateB;           /*!< ISDB-T Layer B lock status */
   NFE_LockState lockStateC;           /*!< ISDB-T Layer C lock status */
   NFE_UInt8     segmentA;             /*!< Number of segments in ISDB-T Layer A */
   NFE_UInt8     segmentB;             /*!< Number of segments in ISDB-T Layer B */
   NFE_UInt8     segmentC;             /*!< Number of segments in ISDB-T Layer C */
   NFE_LockTime  acquisitionTime;      /*!< Signal acquisition time in ms */
   NFE_LockTime  notLockedTime;        /*!< If fail to lock, this gives how long it took to decide no lock in ms*/
   NFE_Offset    demodOffset;          /*!< IF freq error resolved purely in demod in Hz */
   NFE_SNR       sigNoise;             /*!< SNR estimate in tenths of a dB */
   NFE_AGC       demodAGC;             /*!< Raw AGC register value from demod */
   NFE_UInt8     signalLevel;          /*!< SignalLevel in .5dBm steps. The values are scaled between (0 to 255) [0 = -127.5dBm, 255 = 0dBm]*/
   NFE_BER       berWindowA;           /*!< Num of seconds BER is calculated over for layer A */
   NFE_BER       berWindowB;           /*!< Num of seconds BER is calculated over for layer B */
   NFE_BER       berWindowC;           /*!< Num of seconds BER is calculated over for layer C */
   NFE_BER       uncorrectedA;         /*!< RS Uncorrected error packet count for layer A */
   NFE_BER       uncorrectedB;         /*!< RS Uncorrected error packet count for layer B */
   NFE_BER       uncorrectedC;         /*!< RS Uncorrected error packet count for layer C */
   NFE_BER       correctedA;           /*!< The number of errors corrected by RS block (Post Viterbi / Pre RS) for layer A */
   NFE_BER       correctedB;           /*!< The number of errors corrected by RS block (Post Viterbi / Pre RS) for layer B */
   NFE_BER       correctedC;           /*!< The number of errors corrected by RS block (Post Viterbi / Pre RS) for layer C */
   NFE_BER       berReadyCount;        /*!< BER Ready count */
   NFE_Bool      ewsAlarm;             /*!< Earthquake Warning System Alarm */
} NFE_IsdbtDiagnostics;


typedef union
{
#if NFE_SUPPORT_SATELLITE
   NFE_DvbsDiagnostics        dvbs;     /*!< Satellite DVB-S signal diagnostic info */
   NFE_Dvbs2Diagnostics       dvbs2;    /*!< Satellite DVB-S2 signal diagnostic info */
   NFE_Dvbs2xDiagnostics      dvbs2x;   /*!< Satellite DVB-S2x signal diagnostic info */
   NFE_DssDiagnostics         dss;      /*!< Satellite DSS signal diagnostic info */
#endif
#if NFE_SUPPORT_CABLE
   NFE_CableIbDiagnostics     cabIb;    /*!< Cable DVB-C In Band signal diagnostic info */
   NFE_CableOobDiagnostics    cabOob;   /*!< Cable DVB-C Out Off Band signal diagnostic info */
#endif
#if NFE_SUPPORT_DVBT
   NFE_DvbtDiagnostics        dvbt;     /*!< Terrestrial DVB-T signal diagnostic info */
#endif
#if NFE_SUPPORT_DVBT2
   NFE_Dvbt2Diagnostics       dvbt2;    /*!< Terrestrial DVB-T2 signal diagnostic info */
#endif
#if NFE_SUPPORT_ATSC
   NFE_AtscDiagnostics        atsc;     /*!< Terrestrial ATSC signal diagnostic info */
#endif
#if NFE_SUPPORT_ISDBT
   NFE_IsdbtDiagnostics       isdbt;    /*!< Terrestrial ISDB-T signal diagnostic info */
#endif
} NFE_DiagnosticsEntries;


typedef struct
{
   NFE_Mode               mode;         /*!< Frontend mode (DVB-S/S2/C/T/T2,.. etc ) */
   NFE_DiagnosticsEntries diags;        /*!< Frontend signal diagnostic info, respective for the above mentioned frontend mode */
} NFE_Diagnostics;


/*capabilities, i.e. what is supported - specific to each frontend/signal type*/
typedef struct
{
   NFE_Frequency   frequencyMin;        /*!< Frontend supported minimum frequency limit in Hz */
   NFE_Frequency   frequencyMax;        /*!< Frontend supported maximum frequency limit in Hz */
   NFE_SymbolRate  symbolRateMin;       /*!< Frontend supported minimum symbolrate limit in Symbols/sec */
   NFE_SymbolRate  symbolRateMax;       /*!< Frontend supported maximum symbolrate limit in Symbols/sec */
   NFE_CodeRate    codeRates;           /*!< Frontend supported code rates */
   NFE_UInt8       powerMin;            /*!< Frontend supported minimum power level reporting */
   NFE_UInt8       powerMax;            /*!< Frontend supported maximum power level reporting */
   NFE_SNR         snrMin;              /*!< Frontend supported minimum SNR reporting in tenths of a dB*/
   NFE_SNR         snrMax;              /*!< Frontend supported maximum SNR reporting in tenths of a dB*/
   NFE_UInt8       numLnbConnections;
   NFE_UInt8      *connectionIds;
} NFE_DvbsCaps;


typedef struct
{
   NFE_Frequency   frequencyMin;        /*!< Frontend supported minimum frequency limit in Hz */
   NFE_Frequency   frequencyMax;        /*!< Frontend supported maximum frequency limit in Hz */
   NFE_SymbolRate  symbolRateMin;       /*!< Frontend supported minimum symbolrate limit in Symbols/sec */
   NFE_SymbolRate  symbolRateMax;       /*!< Frontend supported maximum symbolrate limit in Symbols/sec */
   NFE_CodeRate    codeRates;           /*!< Frontend supported code rates */
   NFE_Modulation  modulations;         /*!< Frontend supported supported modulation schemes */
   NFE_UInt8       powerMin;            /*!< Frontend supported minimum power level reporting */
   NFE_UInt8       powerMax;            /*!< Frontend supported maximum power level reporting */
   NFE_SNR         snrMin;              /*!< Frontend supported minimum SNR reporting in tenths of a dB*/
   NFE_SNR         snrMax;              /*!< Frontend supported maximum SNR reporting in tenths of a dB*/
   NFE_UInt8       numLnbConnections;   /*!< Frontend supported number of LNB connections */
   NFE_UInt8      *connectionIds;       /*!< Frontend supported LNB connection IDs */
} NFE_Dvbs2Caps;


typedef struct
{
   NFE_Frequency   frequencyMin;        /*!< Frontend supported minimum frequency limit in Hz */
   NFE_Frequency   frequencyMax;        /*!< Frontend supported maximum frequency limit in Hz */
   NFE_SymbolRate  symbolRateMin;       /*!< Frontend supported minimum symbolrate limit in Symbols/sec */
   NFE_SymbolRate  symbolRateMax;       /*!< Frontend supported maximum symbolrate limit in Symbols/sec */
   NFE_CodeRate    codeRates;           /*!< Frontend supported code rates */
   NFE_Modulation  modulations;         /*!< Frontend supported supported modulation schemes */
   NFE_UInt8       powerMin;            /*!< Frontend supported minimum power level reporting */
   NFE_UInt8       powerMax;            /*!< Frontend supported maximum power level reporting */
   NFE_SNR         snrMin;              /*!< Frontend supported minimum SNR reporting in tenths of a dB*/
   NFE_SNR         snrMax;              /*!< Frontend supported maximum SNR reporting in tenths of a dB*/
   NFE_UInt8       numLnbConnections;   /*!< Frontend supported number of LNB connections */
   NFE_UInt8      *connectionIds;       /*!< Frontend supported LNB connection IDs */
} NFE_Dvbs2xCaps;


typedef struct
{
   NFE_Frequency   frequencyMin;        /*!< Frontend supported minimum frequency limit in Hz */
   NFE_Frequency   frequencyMax;        /*!< Frontend supported maximum frequency limit in Hz */
   NFE_SymbolRate  symbolRateMin;       /*!< Frontend supported minimum symbolrate limit in Symbols/sec */
   NFE_SymbolRate  symbolRateMax;       /*!< Frontend supported maximum symbolrate limit in Symbols/sec */
   NFE_CodeRate    codeRates;           /*!< Frontend supported code rates */
   NFE_UInt8       powerMin;            /*!< Frontend supported minimum power level reporting */
   NFE_UInt8       powerMax;            /*!< Frontend supported maximum power level reporting */
   NFE_SNR         snrMin;              /*!< Frontend supported minimum SNR reporting in tenths of a dB*/
   NFE_SNR         snrMax;              /*!< Frontend supported maximum SNR reporting in tenths of a dB*/
   NFE_UInt8       numLnbConnections;
   NFE_UInt8      *connectionIds;
} NFE_DssCaps;


typedef struct
{
   NFE_Frequency   frequencyMin;        /*!< Frontend supported minimum frequency limit in Hz */
   NFE_Frequency   frequencyMax;        /*!< Frontend supported maximum frequency limit in Hz */
   NFE_SymbolRate  symbolRateMin;       /*!< Frontend supported minimum symbolrate limit in Symbols/sec */
   NFE_SymbolRate  symbolRateMax;       /*!< Frontend supported maximum symbolrate limit in Symbols/sec */
   NFE_Modulation  modulations;         /*!< Frontend supported supported modulation schemes */
   NFE_UInt8       powerMin;            /*!< Frontend supported minimum power level reporting */
   NFE_UInt8       powerMax;            /*!< Frontend supported maximum power level reporting */
   NFE_SNR         snrMin;              /*!< Frontend supported minimum SNR reporting in tenths of a dB*/
   NFE_SNR         snrMax;              /*!< Frontend supported maximum SNR reporting in tenths of a dB*/
} NFE_CabIbCaps;


typedef struct
{
   NFE_Frequency  frequencyMin;         /*!< Frontend supported minimum frequency limit in Hz */
   NFE_Frequency  frequencyMax;         /*!< Frontend supported maximum frequency limit in Hz */
   NFE_SymbolRate symbolRateMin;        /*!< Frontend supported minimum symbolrate limit in Symbols/sec */
   NFE_SymbolRate symbolRateMax;        /*!< Frontend supported maximum symbolrate limit in Symbols/sec */
   NFE_UInt8       powerMin;            /*!< Frontend supported minimum power level reporting */
   NFE_UInt8       powerMax;            /*!< Frontend supported maximum power level reporting */
   NFE_SNR         snrMin;              /*!< Frontend supported minimum SNR reporting in tenths of a dB*/
   NFE_SNR         snrMax;              /*!< Frontend supported maximum SNR reporting in tenths of a dB*/
} NFE_CabOobCaps;


typedef struct
{
   NFE_Frequency   frequencyMin;        /*!< Frontend supported minimum frequency limit in Hz */
   NFE_Frequency   frequencyMax;        /*!< Frontend supported maximum frequency limit in Hz */
   NFE_CodeRate    codeRates;           /*!< Frontend supported code rates */
   NFE_Modulation  modulations;         /*!< Frontend supported supported modulation schemes */
   NFE_Bandwidth   bandwidths;          /*!< Frontend supported bandwidths */
   NFE_UInt8       powerMin;            /*!< Frontend supported minimum power level reporting */
   NFE_UInt8       powerMax;            /*!< Frontend supported maximum power level reporting */
   NFE_SNR         snrMin;              /*!< Frontend supported minimum SNR reporting in tenths of a dB*/
   NFE_SNR         snrMax;              /*!< Frontend supported maximum SNR reporting in tenths of a dB*/
} NFE_DvbtCaps;


typedef struct
{
   NFE_Frequency   frequencyMin;        /*!< Frontend supported minimum frequency limit in Hz */
   NFE_Frequency   frequencyMax;        /*!< Frontend supported maximum frequency limit in Hz */
   NFE_Bandwidth   bandwidths;          /*!< Frontend supported bandwidths */
   NFE_UInt8       powerMin;            /*!< Frontend supported minimum power level reporting */
   NFE_UInt8       powerMax;            /*!< Frontend supported maximum power level reporting */
   NFE_SNR         snrMin;              /*!< Frontend supported minimum SNR reporting in tenths of a dB*/
   NFE_SNR         snrMax;              /*!< Frontend supported maximum SNR reporting in tenths of a dB*/
} NFE_Dvbt2Caps;


typedef struct
{
   NFE_Frequency   frequencyMin;        /*!< Frontend supported minimum frequency limit in Hz */
   NFE_Frequency   frequencyMax;        /*!< Frontend supported maximum frequency limit in Hz */
   NFE_Modulation  modulations;         /*!< Frontend supported supported modulation schemes */
   NFE_UInt8       powerMin;            /*!< Frontend supported minimum power level reporting */
   NFE_UInt8       powerMax;            /*!< Frontend supported maximum power level reporting */
   NFE_SNR         snrMin;              /*!< Frontend supported minimum SNR reporting in tenths of a dB*/
   NFE_SNR         snrMax;              /*!< Frontend supported maximum SNR reporting in tenths of a dB*/
} NFE_AtscCaps;


typedef struct
{
   NFE_Frequency  frequencyMin;         /*!< Frontend supported minimum frequency limit in Hz */
   NFE_Frequency  frequencyMax;         /*!< Frontend supported maximum frequency limit in Hz */
   NFE_Modulation modulations;          /*!< Frontend supported supported modulation schemes */
   NFE_UInt8      powerMin;             /*!< Frontend supported minimum power level reporting */
   NFE_UInt8      powerMax;             /*!< Frontend supported maximum power level reporting */
   NFE_SNR        snrMin;               /*!< Frontend supported minimum SNR reporting in tenths of a dB*/
   NFE_SNR        snrMax;               /*!< Frontend supported maximum SNR reporting in tenths of a dB*/
} NFE_IsdbtCaps;


typedef struct
{
#if NFE_SUPPORT_SATELLITE
   NFE_DvbsCaps      dvbs;              /*!< Satellite DVB-S signal capabilities */
   NFE_Dvbs2Caps     dvbs2;             /*!< Satellite DVB-S2 signal capabilities */
   NFE_Dvbs2xCaps    dvbs2x;            /*!< Satellite DVB-S2x signal capabilities */
   NFE_DssCaps       dss;               /*!< Satellite DSS signal capabilities */
#endif
#if NFE_SUPPORT_CABLE
   NFE_CabIbCaps     cabIb;             /*!< Cable DVB-C In Band signal capabilities */
   NFE_CabOobCaps    cabOob;            /*!< Cable DVB-C Out Off Band signal capabilities */
#endif
#if NFE_SUPPORT_DVBT
   NFE_DvbtCaps      dvbt;              /*!< Terrestrial DVB-T signal capabilities */
#endif
#if NFE_SUPPORT_DVBT2
   NFE_Dvbt2Caps     dvbt2;             /*!< Terrestrial DVB-T2 signal capabilities */
#endif
#if NFE_SUPPORT_ATSC
   NFE_AtscCaps      atsc;              /*!< Terrestrial ATSC signal capabilities */
#endif
#if NFE_SUPPORT_ISDBT
   NFE_IsdbtCaps     isdbt;             /*!< Terrestrial ISDB-T signal capabilities */
#endif
} NFE_CapabilitiesEntries;


typedef struct
{
   NFE_Mode                mode;       /*!< Frontend mode (DVB-S/S2/C/T/T2,.. etc ) */
#if NFE_SUPPORT_CDI_18_FEATURES
   NFE_Feature             features;   /*!< Bitwise OR value of Features supported by frontend */
#endif
   NFE_CapabilitiesEntries caps;       /*!< Frontend supported capabilities, respective for the above mentioned frontend mode */    
} NFE_HwInfo;


typedef struct
{
   NFE_HwVersion           demod;      /*!< Demod Chip raw revision/version register Info */
   NFE_HwVersion           tuner;      /*!< Tuner Chip raw revision/version register Info */
} NFE_HwVersions;


#define CONVERSION_DBUV_TO_DBMV     -60
#define CONVERSION_DBUV_TO_DBM      -109

#define CONVERSION_DBMV_TO_DBUV      60
#define CONVERSION_DBMV_TO_DBM      -49

#define CONVERSION_DBM_TO_DBUV       109
#define CONVERSION_DBM_TO_DBMV       49


/** \brief frontend modules initialization

    \param [in]  priv   Any input from user can be passed via this argument to give application info which is
    requried for subsys intialization
     \n\n
    <b>Description :</b>\n
      This is the very first api call to intialize NFE module as well the frontend hardware and software drivers
      configured for the specific project.
      \n\n 
    <b>Execution condition :</b>\n
      This is the very first api should be called by application or middleware only once before start to access
      any of the frontend functionalities
      \n\n
    <b>Returned value :</b>\n
      #NFE_ERRORCODE    Any error code from the enum
      \n\n
*/
NFE_ERRORCODE NFE_subsysInit        (  NFE_Void *priv );


/** \brief frontend modules destruction

    <b>Description :</b>\n
      This api should be called to destruct all the frontend modules and the all frontend calles are invalid once the destruction is success.
      \n\n
    <b>Execution condition :</b>\n
      This is the very last api should be called by application or middleware when they don't want to use any frontend functionalities there after.
      \n\n
    <b>Returned value :</b>\n
      #NFE_ERRORCODE    Any error code from the enum
      \n\n
*/
NFE_ERRORCODE NFE_subsysDestruct    (  NFE_Void );


/** \brief Retrieves frontend handle

    \param  [in]     globalFE Frontend numeric index as defined per project
    \param  [out]    handleFE Frontend handle for the requested frontend for further access
    \n\n
    <b>Description :</b>\n
      The numerically indexed frontend handle will be retrieved from the internal driver for further frotnend access.
      \n\n
    <b>Execution condition :</b>\n
      Once the frontend subsys init is successful, this will return the proper handle otherwise it will return error
      \n\n
    <b>Returned value :</b>\n
      #NFE_ERRORCODE    Any error code from the enum
      \n\n
*/
NFE_ERRORCODE NFE_lookup            (  NFE_UInt32 globalFE,
                                       NFE_Handle *handleFE );

/** \brief Registers a callback for frontend events

    \param  [in]     callback Callback function to be called when ever the frontend event has come
    \param  [out]    user     User data to be passed back to the caller in the event raise
    \n\n
    <b>Description :</b>\n
      This event callback will be raised for all frontend specific events for all frontend devices
      \n\n
    <b>Execution condition :</b>\n
      Once the frontend subsys init is successful, this will register the callback api with frontend drivers
      \n\n
    <b>Returned value :</b>\n
      #NFE_ERRORCODE    Any error code from the enum
      \n\n
*/
NFE_ERRORCODE NFE_registerCallback  (  NFE_EventCallback    callback,
                                       NFE_Void            *user );


/** \brief Tune frontend

    \param  [in]     handleFE Respective frontend handle
    \param  [in]     tune     Tuning parameters for the specific frontend
    \param  [out]    asyncID  Request Id to the caller to trace the asynchronous events for the requested tuning action
    \n\n
    <b>Description :</b>\n
      The tunning will be performed in background for the specified frontend with the given tuning parameters. This api is A non blocking api, so caller can
      continue other tasks after this api call. The same time they can trace the asynchronous events based on the asyncID returned in this api. The following
      asynchronous events will be sent to to caller for the tuning operation.\n\n
      #NFE_EVENT_LOCKED carrier found\n
      #NFE_EVENT_ACQ_FAILED no carrier found\n
      Every time the NFE_Tune api sends #NFE_EVENT_TUNING event to notify user the tuning operation is invoked successfully.
    \n\n
      In satcr mode the NFE_Tune api is going find the CW carrier presence. If it detects CW tone it will send #NFE_EVENT_SATCR_TONE_DETECT_FOUND event
      else it will send #NFE_EVENT_SATCR_TONE_DETECT_COMPLETE event. The actual satcr tuning will be done by caller through diseqc send message api.
    <b>Execution condition :</b>\n
      Once the frontend subsys init is successful, this api will tune the frontend.
      \n\n
    <b>Returned value :</b>\n
      #NFE_ERRORCODE    Any error code from the enum
      \n\n
*/
NFE_ERRORCODE NFE_tune              (  NFE_Handle   handleFE,
                                       NFE_Tune    *tune,
                                       NFE_AsyncID *asyncID );


/** \brief Stop Tuning/Scanning

    \param  [in]     handleFE Respective frontend handle
    \param  [out]    asyncID  Request Id to the caller to trace the asynchronous events for the requested tuning action
    \n\n
    <b>Description :</b>\n
      Stop the frontend and put it in idle state. If the frontend is processing some action that will be aborted
      forcibly and put it in Idle state.
      \n\n
    <b>Execution condition :</b>\n
      Once the frontend subsys init is successful, this api will be used to stop tune/scan at any point of time.
      \n\n
    <b>Returned value :</b>\n
      #NFE_ERRORCODE    Any error code from the enum
      \n\n
*/
NFE_ERRORCODE NFE_stop              (  NFE_Handle   handleFE,
                                       NFE_AsyncID *asyncID );


/** \brief Start Scanning

    \param  [in]     handleFE       Respective frontend handle
    \param  [in]     startFreq      Carrier search Start frequency
    \param  [in]     stopFreq       Carrier search Stop frequency
    \param  [in]     scanTable      Pointer to the scan table which has mode specific scanning configurations
    \param  [in]     numEntries     Number of entries in the scan table
    \param  [out]    asyncID  Request Id to the caller to trace the asynchronous events for the requested scanning action
    \n\n
    <b>Description :</b>\n
      The scanning will be performed in background for the given range of frequencies. Each entry in the table will be tried for each frequency
      and when ever the carrier is detected it will be notified to the caller with aynchronous event #NFE_EVENT_LOCKED. To proceed further the
      caller should call #NFE_nextScan, which will continue the requested scan process till end of search. The possible asynchronous events are as
      follows\n\n
      #NFE_EVENT_LOCKED carrier found\n
      #NFE_EVENT_FREQUENCY_LIMIT the end of search\n\n
    <b>Execution condition :</b>\n
      Once the frontend subsys init is successful.
      \n\n
    <b>Returned value :</b>\n
      #NFE_ERRORCODE    Any error code from the enum
      \n\n
*/
NFE_ERRORCODE NFE_startScan         (  NFE_Handle     handleFE,
                                       NFE_Frequency  startFreq,
                                       NFE_Frequency  stopFreq,
                                       NFE_ScanEntry *scanTable,
                                       NFE_UInt32     numEntries, /*length of scan table*/
                                       NFE_AsyncID   *asyncID );


/** \brief Continue Scanning

    \param  [in]     handleFE    Respective frontend handle
    \param  [out]    asyncID     Request Id to the caller to trace the asynchronous events for the requested scanning action    
    \n\n
    <b>Description :</b>\n
      Continue the current scanning after it detects the carrier and stops. The possible asynchronous events are as follows\n\n
      #NFE_EVENT_LOCKED next carrier found\n
      #NFE_EVENT_FREQUENCY_LIMIT end of search\n\n
    <b>Execution condition :</b>\n
      Once the frontend subsys init is successful.
      \n\n
    <b>Returned value :</b>\n
      #NFE_ERRORCODE    Any error code from the enum
      \n\n
*/
NFE_ERRORCODE NFE_nextScan          (  NFE_Handle   handleFE,
                                       NFE_AsyncID *asyncID );


/** \brief Get Frontend Status

    \param  [in]     handleFE    Respective frontend handle
    \param  [out]    status      Status of the requested frontend
    \n\n
    <b>Description :</b>\n
      Return the current status of the requested frontend. If it is locked then only the returned parameters are valid otherwise neglect it\n
    <b>Execution condition :</b>\n
      Once the frontend subsys init is successful.
      \n\n
    <b>Returned value :</b>\n
      #NFE_ERRORCODE    Any error code from the enum
      \n\n
*/
NFE_ERRORCODE NFE_getStatus         (  NFE_Handle  handleFE,
                                       NFE_Status *status );


/** \brief Get Frontend Diagnostics

    \param  [in]     handleFE    Respective frontend handle
    \param  [out]    diags       Diagnostic info of the requested frontend
    \n\n
    <b>Description :</b>\n
      Return the current diagnostic info of the requested frontend. If it is locked then only the return parameters are valid otherwise neglect it.\n
    <b>Execution condition :</b>\n
      Once the frontend subsys init is successful.
      \n\n
    <b>Returned value :</b>\n
      #NFE_ERRORCODE    Any error code from the enum
      \n\n
*/
NFE_ERRORCODE NFE_getDiagnostics    (  NFE_Handle       handleFE,
                                       NFE_Diagnostics *diags );


/** \brief Get Frontend Modes

    \param  [in]     handleFE    Respective frontend handle
    \param  [out]    modes       Supported frontend modes
    \n\n
    <b>Description :</b>\n
      Return supported frontend modes for the requested frontend handle
    <b>Execution condition :</b>\n
      Once the frontend subsys init is successful.
      \n\n
    <b>Returned value :</b>\n
      #NFE_ERRORCODE    Any error code from the enum
      \n\n
*/
NFE_ERRORCODE NFE_getModes          (  NFE_Handle   handleFE,
                                       NFE_Mode *modes );


/** \brief Get Frontend Hardware Info

    \param  [in]     handleFE    Respective frontend handle
    \param  [out]    info        Get hw info
    \n\n
    <b>Description :</b>\n
      Return the requested frontend hw spcific capabilities like the range of frequency supported, range of symbol rate supported, etc
    <b>Execution condition :</b>\n
      Once the frontend subsys init is successful.
      \n\n
    <b>Returned value :</b>\n
      #NFE_ERRORCODE    Any error code from the enum
      \n\n
*/
NFE_ERRORCODE NFE_getHwInfo         (  NFE_Handle  handleFE,
                                       NFE_HwInfo *info );

/* NFE_getHwVersions */
/* Retrieves the hardware version(s) of the specified frontend  (demod and/or tuner)*/
NFE_ERRORCODE NFE_getHwVersions     (  NFE_Handle        handleFE,
                                       NFE_HwVersions   *versions );

#if NFE_SUPPORT_LNB
/** \brief Get LNB Handle Associated with Frontend

    \param  [in]     handleFE    Respective frontend handle
    \param  [out]    handleLNB   Associated LNB handle
    \n\n
    <b>Description :</b>\n
      Return the associated LNB handle for the requested frontend.
    <b>Execution condition :</b>\n
      Once the frontend subsys init is successful.
      \n\n
    <b>Returned value :</b>\n
      #NFE_ERRORCODE    Any error code from the enum
      \n\n
*/
NFE_ERRORCODE NFE_getAssocLNB       (  NFE_Handle   handleFE,
                                       NLNB_Handle *handleLNB );


/** \brief Set LNB Handle with Frontend

    \param  [in]     handleFE    Respective frontend handle
    \param  [in]     handleLNB   LNB handle to be associated
    \n\n
    <b>Description :</b>\n
      Set the given LNB handle to the requested frontend handle. So further request to any frontend access will go through via this connected LNB.
    <b>Execution condition :</b>\n
      Once the frontend subsys init is successful.
      \n\n
    <b>Returned value :</b>\n
      #NFE_ERRORCODE    Any error code from the enum
      \n\n
*/
NFE_ERRORCODE NFE_setAssocLNB       (  NFE_Handle   handleFE,
                                       NLNB_Handle  handleLNB );
#endif /*#if NFE_SUPPORT_LNB*/

/** \brief Set Frontend Standby mode 

    \param  [in]     handleFE       Respective frontend handle
    \param  [out]    standbyMode    Standby mode to be set
    \n\n
    <b>Description :</b>\n
      Set the requested frontend devices in to stanby mode specified in the input argument. Deep standby mode may be irrecoverable for some implementations
      so subsys init is must to reover the hardware from stanby mode to normal mode.\n
    <b>Execution condition :</b>\n
      Once the frontend subsys init is successful.
      \n\n
    <b>Returned value :</b>\n
      #NFE_ERRORCODE    Any error code from the enum
      \n\n
*/
NFE_ERRORCODE NFE_setStandbyMode    (  NFE_Handle       handleFE,
                                       NFE_StandbyMode  standbyMode );


/** \brief Frontend Control

    \param  [in]       handleFE       Respective frontend handle
    \param  [in]       command        The control command
    \param  [in,out]   args           The data for the command and the response to be sent to the caller
    \n\n
    <b>Description :</b>\n
      Some of the frontend device specific functions are implemented in the control command. The args will input some additional data for the command
      as well output the command response to the caller. This is a blocking call.
    <b>Execution condition :</b>\n
      Once the frontend subsys init is successful.
      \n\n
    <b>Returned value :</b>\n
      #NFE_ERRORCODE    Any error code from the enum
      \n\n
*/
NFE_ERRORCODE NFE_control           (  NFE_Handle           handleFE,
                                       NFE_Control_Command  command,
                                       NFE_Control_Arg     *args);



#ifdef __cplusplus
}
#endif

#endif /*#define __NFE_API_H_*/

/*nfe_api.h*/
