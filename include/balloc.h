#ifndef _BALLOC_H
#define _BALLOC_H

/*
 * Block Memory Allocator
 * 04.2004 aralbrec
 *
 * Complements or replaces the standard C library's malloc allocator.  The standard
 * C library's malloc functions manage a single contiguous block of memory from
 * which requests for variable-sized blocks of memory are satisfied.  Because those
 * sizes are variable, over the course of the program running external fragmentation
 * can become an issue.  This is a situation where there are lots of small available
 * chunks of memory available within the large block, but memory requests can no
 * longer be satisfied because none of those chunks, taken individually, are large
 * enough.  Managing such a memory block for any size memory requests also adds to
 * running time overhead.
 *
 * A block memory allocator is designed to be quick, solve the external fragmentation
 * issue and be able to make use of free memory scattered around the memory map.
 * The allocator manages up to 127 memory queues, with each queue containing a list
 * of memory blocks of the same size.  A memory request requests a block of memory
 * from a specific queue, retrieving a block of known size.  The size of blocks in
 * each queue and the number of queues are something you decide --- you are
 * responsible for initializing the queues by adding free memory to them.  That
 * free memory can be bits and pieces scattered around your memory map (10 bytes
 * from here, 356 bytes from there, etc).
 *
 * Read the discussion under "BAQTBL" below to learn how to declare the queue table.
 * Use ba_Init to clear the queues to empty and ba_AddMem to add memory to those
 * queues.  ba_BestFit can return blocks of memory of at least a certain size --
 * see the source for comments.
 *
 * - maximum of 127 memory queues
 * - minimum block size is 2 bytes
 * - actual memory used for each block is size+1 bytes
 *   (one hidden byte is used to identify the queue a block belongs to)
 */

typedef unsigned char uchar;
typedef unsigned int uint;

/*
 * BAQTBL is a macro that declares the queue table statically.
 * "numq" is the number of memory queues that will be managed.
 *
 * An alternative is to declare the location of the queue table
 * in memory using some inline assembler in your main.c file:
 *
 *    #asm
 *       XDEF _ba_qtbl
 *       DEFC _ba_qtbl = addr
 *    #endasm
 *
 * The table will not then be compiled as part of the final binary.
 *
 * One of these declarations must be performed once in your main.c file.
 */

#define BAQTBL(numq)  uchar ba_qtbl[numq*2];

extern void __LIB__ __FASTCALL__ ba_Init(uchar numq /* >=1 */);
extern void __LIB__ *ba_AddMem(uchar q, uchar numblocks /* >=1 */, uint size /* >=2 */, void *addr);
extern uint __LIB__ __FASTCALL__ ba_BlockCount(uchar q);
extern void __LIB__ __FASTCALL__ *ba_Malloc(uchar q);
extern void __LIB__ __FASTCALL__ ba_Free(void *addr);
extern void __LIB__ *ba_BestFit(uchar q, uchar numq /* >=1 */);

#endif
