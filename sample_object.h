/* header guard generate by genheader.pl */
#ifndef _sample_object_h_
#define _sample_object_h_

#include "g_object.h"

typedef struct _sample_object_t {
  g_object objbase;
} sample_object_t;

/*  signals of sample_object_t
 * add_signal(base, "destroyed");
 * add_signal(base, "an_event");
 * add_signal(base, "print_event");
 */

void init_sample_object(sample_object_t* obj_to_init);
void destroy_sample_object(sample_object_t* obj_to_destroy);

void sample_event(sample_object_t* obj);
void sample_print(sample_object_t* obj, const char* text_to_print);


#endif /* _sample_object_h_ */
