#ifndef OSI_COMMON_H_
#define OSI_COMMON_H_
#include <stdio.h>		/* standard C library */
#include <stdlib.h>		/* standard C library */
#include <string.h>		/* standard C library */
#include <ctype.h>
#include <io.h>
#include <math.h>
#include <time.h>		/* standard C library */

#include "osilib.h"		/* OSI library for common routines */
#include "scadaapi.h"	/* OSI library for SCADA API */
#include "syslib.h"		/* OSI library for system routines */
#include "alarms.h"		/* OSI library for ALARMS routines */
#include "dbms.h"		/* OSI library for DBMS routines */
#include "ositypes.h"

#define MAX_MESSAGE_LENGTH	200			/* maximum length of a log message, in chars */
#define LOG_AND_PRINT		0			/* used with theaterLog() when you want to both log and print messages */
#define LOG_ONLY			1			/* used with theaterLog() when you want to log without printing messages */

OSI_RECORD osi_theaterLog( OSI_INT16 mode, ... );
OSI_RECORD osi_programStart(char *program_name);
OSI_RETCODE ProgCleanup();
extern char program_name[1000];
extern char osipath[100];
extern char respath[100];

#endif