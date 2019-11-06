#include "dftl.h"
#include <getopt.h>

uint32_t MAXCACHINGPAGE;

uint32_t demand_get_parameter(int argc, char **argv);
struct algorithm demand_ftl={
	.argument_set=demand_get_parameter,// it must be null
	.create=demand_create,//this function is called when the program start
	.destroy=demand_destroy,//this function is called when the program end
	.read=demand_read,//a page read
	.write=demand_write,//a page write
	.remove=NULL,//it must be null,
};
/*
 
 all functions which have return value return zero;
 
 */
uint32_t demand_create (lower_info* li,blockmanager *bm, algorithm *algo){

	return 0;
}

void demand_destroy (lower_info* li,  algorithm *algo){

	
}

uint32_t demand_read(request *const req){

	return 0;
}

uint32_t demand_write(request *const req){

	return 0;
}
uint32_t demand_remove(request *const req){

	return 0;
}

/*Don't edit this function*/
uint32_t demand_get_parameter(int argc, char **argv){
	bool isset=false;
	int c;
	while((c=getopt(argc,argv,"d"))!=-1){
		switch(c){
			case 'd':
				isset=true;
				MAXCACHINGPAGE=atoi(argv[optind]);
				break;
			default:
				break;
		}
	}

	if(!isset) MAXCACHINGPAGE=SHOWINGSIZE/K/PAGESIZE/10*2; //default caching is 20% of PFTL

	printf("DFTL LOG :: caching map max:%d\n",MAXCACHINGPAGE);
	return 1;
}
