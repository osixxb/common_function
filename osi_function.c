/***************************************************
Author:		 Xiubin xiao
Version: 	 1.0
Date: 		 2016-09-09 13:39:55
Description:

****************************************************/
#include "osi_function.h"
#include "common.h"

//#define __OSI_REAL_MAIN

char program_name[1000];
char osipath[100];
char respath[100];

//************************************
// Description:  theaterLog
// Returns:  	 OSI_RECORD
// Parameter:	 OSI_INT16 mode
// Parameter:	 ...
//************************************
OSI_RECORD osi_theaterLog( OSI_INT16 mode,... )
{
	char message[ MAX_MESSAGE_LENGTH ] = {0};
	OSI_STRING format;
	va_list marker;

	/* use va to grab the message argument(s) */
	va_start( marker, mode );
	format = va_arg( marker, OSI_STRING );
	vsprintf( message, format, marker );
	va_end( marker );

	/* if LOG_AND_PRINT mode, print message to the console */
	if ( LOG_AND_PRINT == mode )
		printf( "%s\n", message );

	/* log message */
	if ( OSI_SUCCESS != osi_syslog_ext( program_name, message ) )
		printf( "Could not log message to %s\n", program_name );

	return 0;
}


OSI_RECORD osi_programStart(char *argv)
{
	char *program_name_[1];
	if(getenv("OSI")==NULL) 
	{
		osi_theaterLog(LOG_AND_PRINT,"The environment variable of OSI is error");
		return OSI_FAIL;
		exit(1);
	}

	if(getenv("OSI")!=NULL)
		strcpy(osipath,getenv("OSI"));
	sprintf(respath,"%s\\report",osipath);

	//osi_theaterLog(LOG_AND_PRINT,"CEPRI_build_display start");
	
	getProgramName(program_name_,argv);
	strcpy(program_name,program_name_[0]);
	DBMS_init(program_name);


	//strcpy(program_name,"CEPRI_build_display");
	//osi_string_copy(program_name,argv,sizeof(program_name));

	return OSI_SUCCESS;
}

//************************************
// Description:  关闭数据库，清楚零时内存
// Returns:  	 OSI_RETCODE
//************************************
OSI_RETCODE ProgCleanup()
{

	return OSI_SUCCESS;
}