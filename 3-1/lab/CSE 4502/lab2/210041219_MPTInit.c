#include "import.h"

/**
 * Initializes the page structures, moves to the kernel page structure (0),
 * and turns on the paging.
 */
void paging_init(unsigned int mbi_addr)
{
    pdir_init_kern(mbi_addr);
    set_pdir_base(0);
    enable_paging();
}
