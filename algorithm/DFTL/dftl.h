#include "../../include/container.h"


uint32_t demand_create (lower_info*,blockmanager *, algorithm *);
void demand_destroy (lower_info*,  algorithm *);
uint32_t demand_read(request *const);
uint32_t demand_write(request *const);
uint32_t demand_remove(request *const);
void *demand_end_req(algo_req*);
