#ifndef __H_LINFO__
#define __H_LINFO__
#include "../include/container.h"
#include "threading.h"
//alogrithm layer
extern struct algorithm __normal;
extern struct algorithm __badblock;
extern struct algorithm __demand;
extern struct algorithm page_ftl;
extern struct algorithm algo_lsm;
extern struct algorithm demand_ftl;

//device layer
extern struct lower_info memio_info;
extern struct lower_info aio_info;
extern struct lower_info net_info;
extern struct lower_info my_posix; //posix, posix_memory,posix_async
extern struct lower_info no_info;

//block manager
extern struct blockmanager base_bm;
extern struct blockmanager pt_bm;

static void layer_info_mapping(master_processor *mp,int argc, char **argv){
#if defined(posix) || defined(posix_async) || defined(posix_memory)
	mp->li=&my_posix;
#elif defined(bdbm_drv)
	mp->li=&memio_info;
#elif defined(network)
	mp->li=&net_info;
#elif defined(linux_aio)
	mp->li=&aio_info;
#elif defined(no_dev)
	mp->li=&no_info;
#endif

#ifdef normal
	mp->algo=&__normal;
#elif defined(Page_ftl)
	mp->algo=&page_ftl;
#elif defined(dftl) || defined(ctoc) || defined(dftl_test) || defined(ctoc_batch) || defined(hash_dftl)
	mp->algo=&__demand;
#elif defined(demand)
	mp->algo=&__demand;
#elif defined(Lsmtree)
	mp->algo=&algo_lsm;
#elif defined(badblock)
	mp->algo=&__badblock;
#elif defined(DFTL)
	mp->algo=&demand_ftl;
#endif
	
	mp->bm=&base_bm;

	mp->li->create(mp->li,mp->bm);

	mp->bm->create(mp->bm,mp->li);

	if(mp->algo->argument_set){
		mp->algo->argument_set(argc,argv);
	}
	mp->algo->create(mp->li,mp->bm,mp->algo);
}
#endif
