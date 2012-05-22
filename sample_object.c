#include <stdlib.h> /* for NULL declation */

#include "signal.h"

#include "sample_object.h"

void init_sample_object(sample_object_t* obj_to_init) {
  g_object* base;
  if (obj_to_init == NULL) return;

  base = &obj_to_init->objbase;

  init_object(base);

  add_signal(base, "destroyed");
  add_signal(base, "an_event");
  add_signal(base, "print_event");
}


void destroy_sample_object(sample_object_t* obj_to_destroy) {
  g_object* base;

  if (obj_to_destroy == NULL) return;

  base = &obj_to_destroy->objbase;

  emit(obj_to_destroy, "destroyed", "I am going to die!!! hahhaha !!!");
  
  destroy_object(base);
}


void sample_event(sample_object_t* obj) {
  emit(obj, "an_event", "this is a custom event.");
}

void sample_print(sample_object_t* obj, const char* text_to_print) {
  emit(obj, "print_event", text_to_print);
}
