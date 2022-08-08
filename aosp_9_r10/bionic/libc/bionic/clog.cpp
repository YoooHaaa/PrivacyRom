

#include <unistd.h>
#include <string.h>
#include <async_safe/log.h>


#include<execinfo.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>


#define CINFO   1
#define CERROR  2
#define CSIZE   100


void clog_write(int type, const char* tag, const char* msg){
	if (type == INFO){
		CLOGI(tag, msg);
	}else{
		CLOGE(tag, msg);
	}
}


void cloge(const char* tag, const char* msg){
	int pid = getpid();
	char tmp[32] = {0};
	void *buffer[100];
    char **strings;
    int nptrs;

	sprintf(tmp, "Pid:%d", pid);
    nptrs = backtrace(buffer, CSIZE);
    strings = backtrace_symbols(buffer, nptrs);
 
 	clog_write(CERROR, tag, "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++start");
	clog_write(CERROR, tag, "Type:Native");
	clog_write(CERROR, tag, tmp);
	clog_write(CERROR, tag, msg);
	clog_write(CERROR, tag, "stackTrace:");
    if (strings == NULL) {
    	clog_write(CERROR, tag, "NULL");
    }else{
    	for(j = 0; j < nptrs; j++)
			clog_write(CERROR, tag, strings[j]);
    	free(strings);
    }
	clog_write(CERROR, tag, "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++end\n");
}



void clogi(const char* tag, const char* msg){
	int pid = getpid();
	char tmp[32] = {0};
	void *buffer[100];
    char **strings;
    int nptrs;

	sprintf(tmp, "Pid:%d", pid);
    nptrs = backtrace(buffer, CSIZE);
    strings = backtrace_symbols(buffer, nptrs);
 
 	clog_write(CINFO, tag, "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++start");
	clog_write(CINFO, tag, "Type:Native");
	clog_write(CINFO, tag, tmp);
	clog_write(CINFO, tag, msg);
	clog_write(CINFO, tag, "stackTrace:");
    if (strings == NULL) {
    	clog_write(CINFO, tag, "NULL");
    }else{
    	for(j = 0; j < nptrs; j++)
			clog_write(CINFO, tag, strings[j]);
    	free(strings);
    }
	clog_write(CINFO, tag, "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++end\n");
}











