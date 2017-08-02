
#include "common.h"

#pragma warning(disable:4996)
#pragma warning(disable:4267)


long *bslist;
long *islandlist;
long islandNum;
char xml_path[100];

int debugMode = DEBUG_OFF;

char seg1[100];
char seg2[100];
char seg3[100];
char seg4[100];
char seg5[100];
char seg6[100];
char seg7[100];
char seg8[100];
char seg9[100];
char seg10[100];


/****************************************************************/
/* void usage( void )											*/
/*																*/
/* This function will be called when the user supplies the "-?"	*/
/* switch at the command line, or if the user supplies an un-	*/
/* recognized switch at the command line. It will print out the	*/
/* list of accepted command line switches and a basic			*/
/* description of the program.									*/
/****************************************************************/
void usage(char *program_name)
{
	printf( "\n%s\n\n",program_name );
	printf( "utility to process CEPRI_build_display\n\n" );
	printf( " usage:CEPRI_build_display -p [xml file path and name]\n\n" );
	printf( " -d: run application in debug mode,must be first\n" );
	printf( " -?: print usage to screen\n" );
	printf( " -p: path of .xml file\n" );


	exit( 0 );
}

/****************************************************************/
/* int processCommandLine( int argc, char** argv )		*/
/*																*/
/* This function will process the command line arguments and	*/
/* set the necessary global variables.							*/
/****************************************************************/
int processCommandLine( int argc, char** argv )
{
	int argIdx, strIdx, stringLength;

	if(argc <= 1)
		usage(argv[0]);

	/* for each of the necessary arguments */
	for ( argIdx = 1; argIdx < argc; argIdx++ )
	{

		if ( '-' != argv[ argIdx ][ 0 ] )
			usage(argv[0]);

		stringLength = strlen( argv[ argIdx ] );

		for ( strIdx = 1; strIdx < stringLength; strIdx++ )  
		{
			switch( argv[ argIdx ][ strIdx ] )
			{

				/* 'd' switch means activate debug mode */
			case 'd':
				debugMode = DEBUG_ON;
				break;

				/* '?' means usage function */
			case '?':
				usage(argv[0]);
				break;

			case 'p':
				if(input_path(argv[++argIdx]) == FAIL)	//需++argindx，不能argidx+1； 或者osi_string_copy
					//usage(argv[0]);
				//osi_string_copy(xmlpath,argv[++argIdx],sizeof(xmlpath);
				break;

				/* unhandled parameter; use usage() function */
			default:
				//usage(argv[0]);
				break;
			}
		}
	}

	return TRUE;
}
/****************************************************************/
/* get rand value from x to y	*/
/****************************************************************/
long get_rand(long x,long y)
{
	srand((unsigned)time(NULL));
	
	return x+rand()%(y-x+1);
}

//************************************
// Description:  read 
// Returns:  	 OSI_RECORD
// Parameter:	 char * argv
//************************************
int input_path()
{
	char buff[1000];
	FILE *fp = fopen("d:\\BPA\\config.ini","r");
	if(fp == NULL)
	{
		printf("\n can not open config.ini");
	}
	fgets(buff,1000,fp);
	strcpy(xml_path,buff);
	fclose(fp);
	//long ret = TRUE;
	//if(argv == NULL || strlen(argv) == 0)
	//	ret = FAIL;
	//else 
	//{
	//	if(debugMode == DEBUG_ON)
	//	{
	//		printf("xml name and path:%s\n",argv);
	//	}
	//	strcpy(xml_path,argv);
	//}

	//return ret;
}



char * left(char *dst,char *src, int n)  
{  
	char *p = src;  
	char *q = dst;  
	int len = strlen(src);  
	if(n>len) n = len;  
	while(n--) *(q++) = *(p++);  
	*(q++)='\0'; 
	return dst;  
}  

extern int posdata(FILE *fp,char *data)
{
	char buffer[2000];
	rewind(fp);
	while(!feof(fp))
	{
		if(fgets(buffer,2000,fp)==NULL) break;
		if(strstr(buffer,data)) return 1;
	}

	return 0;
}


int isarg(char *arg,long argc,char **argv)
{
	long i;
	for(i=1;i<argc;i++)
		if(!strcmp(arg,argv[i])) return 1;
	return 0;
}


/**
* change the format of seconds to date YY-MM-DD hh-mm-ss
@ param string		date
@ simtie			seconds from OSI DB
*/
void osi_datetime(char *string,time_t simtime)
{
	struct tm *ttime;
	long year;
	long mth ;
	long day;
	long hour;
	long min; 
	long sec;
	/*osi_simtime(&simtime);*/
	ttime=localtime(&(simtime));
	year=ttime->tm_year+1900;
	mth =ttime->tm_mon+1;
	day =ttime->tm_mday;
	hour=ttime->tm_hour;
	min =ttime->tm_min; 
	sec =ttime->tm_sec;
	sprintf(string,"%02ld-%02ld-%ld %02ld:%02ld:%02ld",year,mth,day,hour,min,sec);
	
	return;
}

/**
* change the format of seconds to date YY-MM-DD
@ param string		date
@ simtie			seconds from OSI DB
*/
void osi_date_string(char *string,time_t simtime)
{
	struct tm *ttime;
	long year;
	long mth ;
	long day;
	long hour;
	long min; 
	long sec;
	/*osi_simtime(&simtime);*/
	ttime=localtime(&(simtime));
	year=ttime->tm_year+1900;
	mth =ttime->tm_mon+1;
	day =ttime->tm_mday;
	hour=ttime->tm_hour;
	min =ttime->tm_min; 
	sec =ttime->tm_sec;
	sprintf(string,"%02ld-%02ld-%02ld",year,mth,day);
	
	return;
}

/**
* get the hours
@ simtie			seconds from OSI DB
@ return			hours
*/
int osi_date_hour(time_t simtime)
{
	struct tm *ttime;
	int year;
	int mth ;
	int day;
	int hour;
	int min; 
	int sec;
	hour = 0;
	/*osi_simtime(&simtime);*/
	ttime=localtime(&(simtime));
	year=ttime->tm_year+1900;
	mth =ttime->tm_mon+1;
	day =ttime->tm_mday;
	hour=ttime->tm_hour;
	min =ttime->tm_min; 
	sec =ttime->tm_sec;
	
	return hour;
}


long getdate_year(char *date_str)
{
	char datebuf[100];
	char *token;
	strcpy(datebuf,date_str);
	token=strtok(datebuf,seps_date);
	if(token!=NULL) return atol(token);

	return 0;
}

long getdate_mth(char *date_str)
{
	char datebuf[100];
	char *token;
	strcpy(datebuf,date_str);
	token=strtok(datebuf,seps_date);
	token=strtok(NULL,seps_date);
	if(token!=NULL) return atol(token);

	return 0;
}

//************************************
// Description:  读取双引号之间的字符串
// Returns:  	 long
// Parameter:	 char * dqm
//************************************

long getdate_day(char *date_str)
{
	char datebuf[100];
	char *token;
	strcpy(datebuf,date_str);
	token=strtok(datebuf,seps_date);
	token=strtok(NULL,seps_date);
	token=strtok(NULL,seps_date);
	if(token!=NULL) return atol(token);

	return 0;
}
//************************************
// Description:  从字符串p1复制m个字符到字符串p2
// Returns:  	 void
// Parameter:	 char * p1
// Parameter:	 char * p2
// Parameter:	 int m
//************************************
void copystr(char *p1,char *p2,int m)  
{  
	int n;  
	n=0;  
	while(n<m-1)  
	{  
		n++;  
		p1++;  
	}  
	while(*p1!='\0')  
	{  
		*p2=*p1;  
		p1++;  
		p2++;  
	}  
	*p2='\0';  

}  
//************************************
// Description:  get program name form ori_name_str except the exe's path
// Returns:  	 FAIL or true
// Parameter:	 char * last_name_str	program name
// Parameter:	 char * ori_name_str	argv[0]
//************************************
int getProgramName(char **last_name_str,char *ori_name_str)
{
	char buff[1000];
	char *name;
	strcpy(buff,ori_name_str);
	name=strrchr(buff,0x5C); //查找最后一个"\"后面的字符(包括"\"在内)，指针name指向"\....", 0x5C == "\"
	*last_name_str = strtok(name,seps_date);
	if(last_name_str != NULL)
		return TRUE;
	else
		return FAIL;
}

int getdate_time_hour(char *date_str)
{
	char *p;
	int str;
	int rethour;
	char buffer[1000];
	char *delim = " :";
	strcpy(buffer,date_str);
	strtok(buffer, delim);
	str = 0;
	p = strtok(NULL, delim);
	rethour = atoi(p);

	return rethour;
}

int getdate_time_day(char *date_str)
{
	char *p;
	int str;
	int rethour;
	char buffer[1000];
	char *delim = "-";
	strcpy(buffer,date_str);
	strtok(buffer, delim);
	str = 0;
	p = strtok(NULL, delim);
	rethour = atoi(p);

	return rethour;
}

void getdate_time(char *crrdatetime)
{
	long year;
	long mth;
	long day;
	long hour;
	long min;
	long sec;
	char crrdate[100];
	char crrtime[100];
	struct tm *local;
	time_t t=time(NULL);
	local=localtime(&t);
	year=local->tm_year+1900;
	mth =local->tm_mon+1;
	day =local->tm_mday;
	hour=local->tm_hour;
	min =local->tm_min;
	sec =local->tm_sec;
	sprintf(crrdate,"%02ld/%02ld/%ld",mth,day,year);
	sprintf(crrtime,"%02ld:%02ld:%02ld",hour,min,sec);
	sprintf(crrdatetime,"%s %s",crrdate,crrtime);

	return;
}

/**
* Calculate topology
  @param lineDate		line linked list
  @param bstpData	    node linked list
  @param islandlist			island list
  @param islandnum		the max island
*/
int tp_island(struct linestr *lineData,struct bstpstr **bstpData,long **bslist,long **islandlist,long *islandNum)
{  
	long nodeNum=0;
	long bstpNum=0;
	/*long islandNum=0;*/
	coding_tp(lineData,&(*bslist),&nodeNum);  	//calculate node number and put the node into "bslist" in order.
	if(COM_SUCCESS!=form_bstp(*bslist,&(*bstpData),nodeNum,&bstpNum))
		return COM_FAIL;//bstpData->i = bslist[i]
	bstp_island(&lineData,&*bstpData,bstpNum);           
	//bstp_island1(&*bstpData,bstpNum);
	bstp_islandnum(*bstpData,&*islandlist,&(*islandNum));
	
	return COM_SUCCESS;
}
void coding_tp(struct linestr *lineData,long **bslist,long *nodeNum)
{
	long n;
	long ii;
	struct fspar *te;
	struct linestr *lp;
	long *temp;
	long ik;
	long jk;
	n=0;
	lp=lineData;
	temp=NULL;
	/*(*islandlist)=calloc(1, sizeof(long));*/
	(*bslist)=calloc(1,sizeof(long));
	makespar(&te,101);

	while(lp!=NULL)
	{
		ik=lookup_hash(te,lp->i%100+1,lp->i);
		jk=lookup_hash(te,lp->j%100+1,lp->j);
		if(ik==NO)
		{ 
			n++;
			temp=(long *)realloc((*bslist),(n+1)* sizeof(long));
			(*bslist)=temp; 
			(*bslist)[n]=abs(lp->i);
			ii=(*bslist)[n]%100+1;
			(te)[ii].n++;
			sparmem(te,ii);
			te[ii].value[te[ii].n]=(*bslist)[n];
			te[ii].index[te[ii].n]=n;
		}
		if(jk==NO)
		{
			n++; 
			temp=(long *)realloc((*bslist),(n+1)* sizeof(long));
			(*bslist)=temp; 
			(*bslist)[n]=abs(lp->j); 
			ii=(*bslist)[n]%100+1;
			(te)[ii].n++;
			sparmem(te,ii);
			te[ii].value[te[ii].n]=(*bslist)[n];
			te[ii].index[te[ii].n]=n;
		}
		lp=lp->next;
	}
	
	*nodeNum=n;
	freespar(te,101);
	return;
}

void bstp_island(struct linestr  ** lineData,struct bstpstr  ** bstpData,long bstpNum)
{
	long tmplist[MAXNODE];
	long n,island=0,i,j;
	struct bstpstr *bp=*bstpData;
	while(bp!=NULL)
	{
		if(bp->island==0)
		{
			island++;
			island_bsfun(*lineData,tmplist,&n,bp->i); //find the tree of IEEE-30 //n is the numbers  of the tree branch//tmplist is the node of the tree.//
			for(i=1;i<=n;i++)
			{
				j=tmplist[i];
			}
			update(&*bstpData,tmplist,n,island,bstpNum,&*lineData); // set bstpData->island =1;
		}
		bp=bp->next;
	}
	
	return;
}
void bstp_islandnum(struct bstpstr  *bstpData,long **islandlist,long *islandNum)
{
	long n=0;
	struct bstpstr *bp=bstpData;
	long *temp=NULL;
	(*islandlist)=calloc(1, sizeof(long));
	while(bp!=NULL)
	{
		long k=lookup_tp((*islandlist),bp->island,n);
		if(k==NO)
		{
			n++;
			temp=(long *)realloc((*islandlist),(n+1)* sizeof(long));
			(*islandlist)=temp; 
			(*islandlist)[n]=bp->island;
		}
		bp=bp->next;
	}
	*islandNum=n;
	return;
}
void bstp_island1(struct bstpstr **bstpData,long bstpNum)
{
	struct bstpstr *bp=*bstpData;
	long imax=maxisland_fun(&*bstpData,bstpNum);

	while(bp!=NULL)
	{
		if(bp->island==imax) bp->island=-1;
		bp=bp->next;
	}
	
	return;
}

int form_bstp(long * bslist,struct bstpstr **bstpData,long nodeNum,long *bstpNum)
{
	long i;
	*bstpData=NULL;
	*bstpNum=nodeNum;
	for(i=1;i<=nodeNum;i++)
	{
		struct bstpstr * bp=(struct bstpstr *)malloc(sizeof(struct bstpstr ));
		if(bp==NULL)
		{
			if(debugMode == DEBUG_ON)
				printf("\nError --- %ld",__LINE__); 
			return COM_FAIL; 
		}
		memset(bp,0,sizeof(struct bstpstr ));
		bp->i=bslist[i];
		bp->next=*bstpData;
		*bstpData=bp;

	}
	
	reverse_bp(&*bstpData);
	return COM_SUCCESS;
}
void sparmem_f(struct fspar *s,long i,long nmax)
{
	double *vp=(double *)realloc(s[i].value,(nmax+1)*sizeof(double));
	long   *ip=(long *)realloc(s[i].index,(nmax+1)*sizeof(long));
	if(vp==NULL)
	{ 
		if(debugMode == DEBUG_ON)
			printf("\nError --- %ld",__LINE__); 
		exit(0); 
	}
	if(ip==NULL)
	{
		if(debugMode == DEBUG_ON)
			printf("\nError --- %ld",__LINE__); 
		exit(0); 
	}
	s[i].nmax =nmax;
	s[i].value=vp;
	s[i].index=ip;

	return;
}
void freespar(struct fspar *s,long m)
{
	long i;
	if(s==NULL) return;
	for(i=0;i<m;i++)
	{
		free(s[i].value);
		free(s[i].index);
	}	free(s);
	s=NULL;

	return;
}
void sparmem(struct fspar *s,long i)
{
	long nmax=ceil10(s[i].n);
	if(nmax!=s[i].nmax)
	{
		double *vp=(double *)realloc(s[i].value,nmax*sizeof(double));
		long   *ip=(long *)realloc(s[i].index,nmax*sizeof(long));
		if(vp==NULL){ printf("\nError --- %ld",__LINE__); exit(0); }
		if(ip==NULL){ printf("\nError --- %ld",__LINE__); exit(0); }
		s[i].nmax =nmax;
		s[i].value=vp;
		s[i].index=ip;
	}

	return;
}
long lookup_hash(struct fspar *s,long n,long v0)
{ 
	long i;
	for(i=1;i<=s[n].n;i++)
	{
		if(s[n].value[i]-v0<SMLL&&s[n].value[i]-v0>-SMLL) return s[n].index[i];
	}
	
	return NO;
}
void makespar(struct fspar **s,long m)
{
	long i;
	*s=(struct fspar *)calloc(m,sizeof(struct fspar));
	if(*s==NULL){ printf("\nError --- %ld",__LINE__); exit(0); }
	for(i=0;i<m;i++)
	{
		(*s)[i].value=NULL;
		(*s)[i].index=NULL;
		(*s)[i].nmax =0;
		(*s)[i].n    =0;
	}		
	
	return;
}
void update(struct bstpstr **bstpData,long *tmplist,long n,long island,long bstpNum,struct linestr **lineData)
{
	long i;
	struct bstpstr *bp=*bstpData;
	struct linestr *lp=*lineData;
	struct fspar *te;
	makespar(&te,101);
	for(i=1;i<=n;i++)
	{
		long ii=(tmplist)[i]%100+1;
		(te)[ii].n++;
		sparmem(te,ii);
		te[ii].value[te[ii].n]=(tmplist)[i];
		te[ii].index[te[ii].n]=i;
	}
	for(i=1;i<=bstpNum;i++)
	{
		/*long k=lookup_tp(tmplist,bp->i,n);*/
		long k=lookup_hash(te,bp->i%100+1,bp->i);
		if(k!=NO) 
			bp->island=island;
		bp=bp->next;
	}
	while(lp)
	{	
		long k=lookup_hash(te,lp->i%100+1,lp->i);
		if(k!=NO) 
			lp->island=island;

		lp = lp->next;
	}

	freespar(te,101);
	return;
}
void island_bsfun(struct linestr *lineData,long *tmplist,long *n,long ibs)
{
	struct linestr *lp;
	long n0,nt,ii;
	struct fspar *te;
	makespar(&te,101);
	(tmplist)[1]=ibs;
	ii=(tmplist)[1]%100+1;
	(te)[ii].n++;
	sparmem(te,ii);
	te[ii].value[te[ii].n]=(tmplist)[1];
	te[ii].index[te[ii].n]=1;
	nt=1;
L01:
	lp=lineData;
	n0=nt;
	while(lp!=NULL)
	{
		/*long ik=lookup_tp(tmplist,lp->i,nt);
		long jk=lookup_tp(tmplist,lp->j,nt);*/
		long ik=lookup_hash(te,lp->i%100+1,lp->i);
		long jk=lookup_hash(te,lp->j%100+1,lp->j);
		if(ik!=NO && jk==NO)
		{ 
			nt++; (tmplist)[nt]=abs(lp->j); 
			ii=(tmplist)[nt]%100+1;
			(te)[ii].n++;
			sparmem(te,ii);
			te[ii].value[te[ii].n]=(tmplist)[nt];
			te[ii].index[te[ii].n]=nt;
		}
		if(ik==NO && jk!=NO)
		{ 
			nt++; (tmplist)[nt]=abs(lp->i); 
			ii=(tmplist)[nt]%100+1;
			(te)[ii].n++;
			sparmem(te,ii);
			te[ii].value[te[ii].n]=(tmplist)[nt];
			te[ii].index[te[ii].n]=nt;
		}
		lp=lp->next;
	}

	if(nt>n0) goto L01;
	*n=nt;
	freespar(te,101);
	return;
}
long lookup_tp(long *v,long v0,long n)
{ 
	long i;
	for(i=1;i<=n;i++)
		/*if(v[i]==abs(v0))*/
		if(v[i]==v0)
			return i;
	
	return NO;
}
long maxisland_fun(struct bstpstr **bstpData,long bstpNum)
{
	long max_bsnum=0;
	long imax=0;
	long i;
	struct bstpstr *bp=*bstpData;
	for(i=1;i<=bstpNum;i++,bp=bp->next)
	{
		long island=bp->island;
		long bsnum=bsnumStat(island,&*bstpData);
		if(bsnum>max_bsnum)
		{
			max_bsnum=bsnum;
			imax=island;
		}
	}

	return imax;
}
void reverse_bp(struct bstpstr **bstpData)
{
	struct bstpstr * next;
	struct bstpstr * front=NULL;
	while (*bstpData!=NULL) 
	{
		next = (*bstpData)->next;
		(*bstpData)->next = front;
		front = *bstpData;
		*bstpData=next;
	}
	*bstpData = front;
	return;
}

long bsnumStat(long island,struct bstpstr **bstpData)
{
	long ret=0;
	struct bstpstr *bp=*bstpData;
	while(bp!=NULL)
	{
		if(bp->island==island) ret++;
		bp=bp->next;
	}
	return ret;
}

void strsegSpace(char *seg,char *string,long k)
{
	char linebuf[1000];
	char q1str[100];
	char q2str[100];
	char *token;
	long i;
	strcpy(linebuf,string);
	initqstr(q1str,linebuf);
	initqstr(q2str,linebuf+(strstr(string,q1str)-string)+strlen(q1str));
	initstr(seg);

	token=strtok(linebuf,seps_space);
	if(token!=NULL)
		if(isqstr(token)) token=q1str;
	for(i=1;i<k;i++)
	{
		if(token!=NULL) token=strtok(NULL,seps_space);
		if(token!=NULL)
			if(isqstr(token)) token=q2str;
	}	if(token!=NULL) strcpy(seg,token);

	return;
}

//************************************
// Description:  以双引号作为分隔符
// Returns:  	 void
// Parameter:	 char * seg
// Parameter:	 char * string
// Parameter:	 long k
//************************************
void strsegDqm(char *seg,char *string,long k)
{
	char linebuf[1000];
	char q1str[100];
	char q2str[100];
	char *token;
	long i;
	strcpy(linebuf,string);
	initqstr(q1str,linebuf);
	initqstr(q2str,linebuf+(strstr(string,q1str)-string)+strlen(q1str));
	initstr(seg);

	token=strtok(linebuf,seps_space);
	if(token!=NULL)
		if(isqstr(token)) token=q1str;
	for(i=1;i<k;i++)
	{
		if(token!=NULL) token=strtok(NULL,seps_dqm);
		if(token!=NULL)
			if(isqstr(token)) token=q2str;
	}	if(token!=NULL) strcpy(seg,token);

	return;
}


int isqstr(char *string)
{
	long i;
	long n=strlen(string);
	for( i=0;i<n;i++)
		if(string[i]!='\'') return FAIL;
	if(n==0) return FAIL;
	/////////////////////////////////////////////////////////////

	return TRUE;
}

void initqstr(char *qstr,char *string)
{
	char *cp1;
	char *cp2;
	initstr(qstr);
	cp1=strstr(string,"\'");
	cp2=NULL;
	if(cp1!=NULL) cp2=strstr(cp1+1,"\'");
	if(cp2!=NULL)
	{
		long n=cp2-cp1+1;
		strncpy(qstr,cp1,n);
		strcut(qstr,n);
		memset(cp1,'\'',n);
	}
	/////////////////////////////////////////////////////////////

	return;
}
void initstr(char *string)
{
	string[0]='\0';
	return;
}
void strcut(char *string,long n)
{
	string[n]='\0';
	return;
}


