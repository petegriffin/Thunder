#ifndef __NFE_PLATFORM_H
#define __NFE_PLATFORM_H

#ifdef __cplusplus
extern "C"
{
#endif

#define  NFE_SUPPORT_CABLE             0
#define  NFE_SUPPORT_DVBT              1
#define  NFE_SUPPORT_DVBT2             1

#define  NFE_SUPPORT_ATSC              0
#define  NFE_SUPPORT_CABLE_ANALOG      0
#define  NFE_SUPPORT_ISDBT             0
#define  NFE_SUPPORT_SATELLITE         0
#define  NFE_SUPPORT_LNB               0
#define  NFE_SUPPORT_SATCR             0

#define  NFE_SUPPORT_MOCA              0

#define  NFE_SUPPORT_CALIBRATION       0

#define  NFE_SUPPORT_FBC               0  /* enables FBC flags in device structs, used for calibration simplification */
#define  NFE_SUPPORT_LNA_AGC_QUERY     0  /* enables LNA gain queries, as well as copying of AGC register from 3255 to 3128 chip */
#if defined(FRONT_END_QAM)
   #define  NFE_SUPPORT_LEVEL_CORR     1  /*add/remove level correction to power estimate as required - assume freq estimate default requirement*/
#else
   #define  NFE_SUPPORT_LEVEL_CORR     0  /*add/remove level correction to power estimate as required - assume freq estimate default requirement*/
#endif
#define  NFE_SUPPORT_FREQ_SEARCH       0  /*used if need to extend freq acq range but not a satellite frontend*/
#define  NFE_SUPPORT_SPECTRUM_SEARCH   0  /*used if device or driver has no intrinsic unknown spectrum search*/
#define  NFE_SUPPORT_EXPLICIT_FE_STOP  0

#define  NFE_SUPPORT_BLUETOOTH          0

// NFE Debug level
#define NFE_DEBUG                      1

/*user space driver*/
#ifndef NFE_SRT_LINUX_USER
   #define NFE_SRT_LINUX_USER
#endif

#ifndef NFE_SRT_LINUX_MSGQ_IMPL
   #define NFE_SRT_LINUX_MSGQ_IMPL
#endif

/*USE_DEFAULT_EVENT_HANDLING set in subsys component*/
#include "fe_port_errorcodes.h"

#ifdef __cplusplus
}
#endif
#endif
/*nfe_platform.h*/
