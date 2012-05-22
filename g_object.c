#include <stdlib.h>
#include <string.h>

#include "signal.h"



void init_object(g_object* obj) {
  obj->num_signals = 0;
  obj->sigtbl = NULL;
}

void destroy_object(g_object* obj) {
  signal_t* p = obj->sigtbl;
  while (p - obj->sigtbl < obj->num_signals) {
    free_signal(p);
    ++p;
  }
  free((signal_t*)obj->sigtbl);
}

int add_signal(g_object* obj, const char* signame) {
  signal_t* p = obj->sigtbl;

  while (p - obj->sigtbl < obj->num_signals) {
    if (strcmp(signame, p->signame) == 0)
      return ERR_SIGNAL_ALREADY_EXSIST;
    ++p;
  }

  ++obj->num_signals;
  obj->sigtbl = realloc(obj->sigtbl, obj->num_signals * sizeof(signal_t));

  p = obj->sigtbl + obj->num_signals - 1;

  p->signame = calloc(strlen(signame) + 1, sizeof(char));
  strcpy((char*)p->signame, signame);

  p->num_handlers = 0;
  
  return 0;
}

int del_signal(g_object* obj, const char* signame) {
  signal_t* p = get_signal(obj, signame);

  if (p == 0) return ERR_SIGNAL_NOT_FOUND;

  /* shift one position */
  memmove(p, /* destination */
          p + 1, /* source */
          obj->num_signals - (p - obj->sigtbl + 1)); /* length: remain */
  --obj->num_signals;

  return 0;
}

signal_t* get_signal(g_object* obj, const char* signame) {
  signal_t* p = obj->sigtbl;
  while (p - obj->sigtbl < obj->num_signals) {
    if (strcmp(signame, p->signame) == 0) {
      return p;
    }
    ++p;
  }
  return NULL;
}
