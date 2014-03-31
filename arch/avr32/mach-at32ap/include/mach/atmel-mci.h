#ifndef __MACH_ATMEL_MCI_H
#define __MACH_ATMEL_MCI_H

#include <linux/dw_dmac.h>

struct mci_dma_data {
	struct dw_dma_slave	sdata;
};

#define	slave_data_ptr(s)	(&(s)->sdata)
#define find_slave_dev(s)	((s)->sdata.dma_dev)

#endif 
