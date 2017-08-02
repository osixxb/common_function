
#ifndef _COMMON_H_
#define _COMMON_H_

#include <stdio.h>		/* standard C library */
#include <stdlib.h>		/* standard C library */
#include <string.h>		/* standard C library */
#include <ctype.h>
#include <io.h>
#include <math.h>
#include <time.h>		/* standard C library */


#define MAXNODE 10000
#define CYCLE_SLEEP_TIME	1000		/* how long our daemon process sleeps after processing, in milliseconds */
#define DEBUG_OFF   0			/* use to disable debug mode (default) */
#define DEBUG_ON			1			/* use to activate debug mode */
#define MAX_MESSAGE_LENGTH	200			/* maximum length of a log message, in chars */
#define LOG_AND_PRINT		0			/* used with theaterLog() when you want to both log and print messages */
#define LOG_ONLY			1			/* used with theaterLog() when you want to log without printing messages */
#define THEATER_REPORT		"FeederSTLF"	/* the name of the report file used by this application */
#define seps_date ".-/\\"
#define seps_space " \""
#define seps_dqm "\""
#define NO     -1
#define SMLL    1.0E-5
#define ceil10(n)  (((n)/10+1)*10)
#define COM_FAIL	0
#define COM_SUCCESS	1
#define FAIL		0
#define TRUE		1

extern char xml_path[100];
extern int debugMode;
char start_time[100];
extern struct bstpstr *bstpData;
extern long *bslist;
extern long *islandlist;
extern long islandNum;
extern char seg1[100];
extern char seg2[100];
extern char seg3[100];
extern char seg4[100];
extern char seg5[100];
extern char seg6[100];
extern char seg7[100];
extern char seg8[100];
extern char seg9[100];
extern char seg10[100];
struct bstpstr//bs.topology
{
	struct bstpstr *next;
	long   i;
	long   ikv;
	long   island;
};
struct linestr//line data
{	
	struct linestr *next;	
	char   descr[100];
	char   Name[100];
	long   i;
	long   j;
	long  id;
	long  device_record;
	long  type_record;
	long  object_type;
	long ii;
	long istation;
	long pdevice;
	long island;

};

typedef struct fspar
{
	double *value;
	long   *index;
	long   nmax;
	long   n;
}FSPAR;

typedef struct 
{
   struct nodestr *nodeData;
   struct nodestr *nodeData0;
   struct weldstr *weldData;
   struct linestr *lineData;
   struct linestr *lineData0;
   struct valvestr *valveData;
   struct leakstr *leakData;
   struct blockstr *blockData;
   struct ndstr *ndData;
   struct Wavestr *WaveData;
   struct agastr *agaData;
   long leakNum;
   double punit_den;
   double punit_f;
   double punit_p;
   double punit_len;
   double punit_dia;
   double punit_rou;
   double punit_temp;
   long unit_f;
   double temp;
   long	fluid_pn;
   double flow_eps;
   double epsilon;
   double epsilonR;
   double eps;
   double v;
   double e;
   double z;
   double kr;
   double ga;
   long MAXiter;
		    double ittertime;	
   char time1[100];
		    struct tm *ttime;
		    double mol;
		    char manual[32];
   long inletNum;
   double peakload[288];
   long weldNum;
   long valveNum;
   long outletNum;
   long bendNum;
   long regulatorNum;
   long reducerNum;
   long pumpNum;
   long pipeNum;
   long comNum;
   long staNum;
   long areaNum;
   double den;
   double length;
   double tol_check;
   long	valve_reguNum;
   long   instance_number;
   double totalload[288];
   double Non_load[288];
   double load;
   double sound_speed;
   double accuracy;
   long dynamicSrc;
   long Dynamic_Flag;
   long Dynamic_Tag;
   long Flag_temp;
   long Flag_comp;
   long inital_Flag;
   long blockNum;
   double Gradient_Deplet;
   double accuracy_regulator_dyn;
   double accuracy_regulator_step;
   double cycle_time;
   double **openning;
	double  **Cv_value;
   double max_rand_percent;

}PIPE_MODEL_DATA;
typedef struct 
{
	struct bstpstr *bstpData;
	long *bslist;
	long *islandlist;
	long islandNum;
}PIPE_TP_RESULTS;

void usage(char *program_name);
int processCommandLine( int argc, char** argv );

extern int posdata(FILE *fp,char *data);
char * left(char *dst,char *src, int n);
void osi_datetime(char *string,time_t simtime);
void osi_date_string(char *string,time_t simtime);
void osi_date_int(int year,int mth,int day,time_t simtime);
long getdate_year(char *date_str);
long getdate_mth(char *date_str);
long getdate_day(char *date_str);
int getdate_time_hour(char *date_str);
int isarg(char *arg,long argc,char **argv);
void getdate_time(char *crrdatetime);
//int process_pipe_tp(PIPE_MODEL_DATA * model_data,PIPE_TP_RESULTS *results);
int tp_island(struct linestr *lineData,struct bstpstr **bstpData,long **bslist,long **islandlist,long *islandNum);
void coding_tp(struct linestr *lineData,long **bslist,long *nodeNum);
void bstp_islandnum(struct bstpstr  *bstpData,long **islandlist,long *islandNum);
void bstp_island1(struct bstpstr **bstpData,long bstpNum);
int form_bstp(long * bslist,struct bstpstr **bstpData,long nodeNum,long *bstpNum);
void sparmem_f(struct fspar *s,long i,long nmax);
void freespar(struct fspar *s,long m);
void sparmem(struct fspar *s,long i);
long lookup_hash(struct fspar *s,long n,long v0);
void makespar(struct fspar **s,long m);
void island_bsfun(struct linestr *lineData,long *tmplist,long *n,long ibs);
long lookup_tp(long *v,long v0,long n);
long maxisland_fun(struct bstpstr **bstpData,long bstpNum);
void reverse_bp(struct bstpstr **bstpData);
long bsnumStat(long island,struct bstpstr **bstpData);
int osi_date_hour(time_t simtime);
void bstp_island(struct linestr  ** lineData,struct bstpstr  ** bstpData,long bstpNum);
void update(struct bstpstr **bstpData,long *tmplist,long n,long island,long bstpNum,struct linestr **lineData);
//************************************
// Description:  read 
// Returns:  	 OSI_RECORD
// Parameter:	 char * argv
//************************************
int input_path();
int getProgramName(char **last_name_str,char *ori_name_str);
void initqstr(char *qstr,char *string);
void initstr(char *string);
void strcut(char *string,long n);

//************************************
// Description:  strsegDqm
// Returns:  	 void
// Parameter:	 char * seg
// Parameter:	 char * string
// Parameter:	 long k
//************************************
void strsegDqm(char *seg,char *string,long k);

//************************************
// Description:  ´Ó×Ö·û´®p1¸´ÖÆm¸ö×Ö·ûµ½×Ö·û´®p2
// Returns:  	 void
// Parameter:	 char * p1
// Parameter:	 char * p2
// Parameter:	 int m
//************************************
void copystr(char *p1,char *p2,int m);

/*************************************************** 
get rand value from x to y	
***************************************************/
long get_rand(long x,long y);

#endif