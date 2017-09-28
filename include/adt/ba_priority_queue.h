
// automatically generated by m4 from headers in proto subdir


#ifndef __ADT_BA_PRIORITY_QUEUE_H__
#define __ADT_BA_PRIORITY_QUEUE_H__

#include <stddef.h>

// DATA STRUCTURES

typedef struct ba_priority_queue_s
{

   void       *compar;
   void       *data;
   size_t      size;
   size_t      capacity;

} ba_priority_queue_t;

extern size_t __LIB__ ba_priority_queue_capacity(ba_priority_queue_t *q) __smallc __z88dk_fastcall;


extern void __LIB__ ba_priority_queue_clear(ba_priority_queue_t *q) __smallc __z88dk_fastcall;


extern void __LIB__ *ba_priority_queue_data(ba_priority_queue_t *q) __smallc __z88dk_fastcall;


extern void __LIB__ ba_priority_queue_destroy(ba_priority_queue_t *q) __smallc __z88dk_fastcall;


extern int __LIB__ ba_priority_queue_empty(ba_priority_queue_t *q) __smallc __z88dk_fastcall;


extern ba_priority_queue_t __LIB__ *ba_priority_queue_init(void *p,void *data,size_t capacity,void *compar) __smallc;
extern ba_priority_queue_t __LIB__ *ba_priority_queue_init_callee(void *p,void *data,size_t capacity,void *compar) __smallc __z88dk_callee;
#define ba_priority_queue_init(a,b,c,d) ba_priority_queue_init_callee(a,b,c,d)


extern int __LIB__ ba_priority_queue_pop(ba_priority_queue_t *q) __smallc __z88dk_fastcall;


extern int __LIB__ ba_priority_queue_push(ba_priority_queue_t *q,int c) __smallc;
extern int __LIB__ ba_priority_queue_push_callee(ba_priority_queue_t *q,int c) __smallc __z88dk_callee;
#define ba_priority_queue_push(a,b) ba_priority_queue_push_callee(a,b)


extern int __LIB__ ba_priority_queue_resize(ba_priority_queue_t *q,size_t n) __smallc;
extern int __LIB__ ba_priority_queue_resize_callee(ba_priority_queue_t *q,size_t n) __smallc __z88dk_callee;
#define ba_priority_queue_resize(a,b) ba_priority_queue_resize_callee(a,b)


extern size_t __LIB__ ba_priority_queue_size(ba_priority_queue_t *q) __smallc __z88dk_fastcall;


extern int __LIB__ ba_priority_queue_top(ba_priority_queue_t *q) __smallc __z88dk_fastcall;



#endif