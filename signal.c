#include <stdlib.h>
#include <string.h> /* memmove */

#include "signal.h"

void free_signal(signal_t* signal) {
  free((char*)signal->signame);
  free((handler_t*)signal->handlers);
  signal->num_handlers = 0;
}

int _connect(g_object* sender, const char* signal, handler_t handler) {
  signal_t* p;
  const handler_t* ph;

  p = get_signal(sender, signal);

  if (p == NULL) return ERR_SIGNAL_NOT_FOUND; /* no such signal */
  ph = p->handlers;

  while (ph - p->handlers < p->num_handlers) {
    if (*ph == handler) return ERR_HANDLER_ALREADY_EXSIST;
    ++ph;
  }

  ++p->num_handlers;
  p->handlers = realloc((handler_t*)p->handlers,
                        sizeof(handler_t) * p->num_handlers);

  *(handler_t*)(p->handlers + p->num_handlers - 1) = handler;
  
  return 0;
}

int _disconnect(g_object* sender, const char* signal, handler_t handler) {
  signal_t* p;
  handler_t* ph;

  p = get_signal(sender, signal);

  if (p == NULL) return ERR_SIGNAL_NOT_FOUND; /* no such signal */
  ph = (handler_t*)p->handlers;

  while (ph - p->handlers < p->num_handlers) {
    if (*ph == handler) {
      memmove(ph, /* destination */
              ph + 1, /* source */
              p->num_handlers - (ph - p->handlers) - 1); /* length: remain */
      --p->num_handlers;
      
      return 0;
    }
    ++ph;
  }
  return ERR_HANDLER_NOT_FOUND;
}

int _disconnect_all(g_object* sender, const char* signal) {
  signal_t* p = get_signal(sender, signal);
  if (p == NULL) return ERR_SIGNAL_NOT_FOUND; /* no such signal */

  free((handler_t*)p->handlers);
  p->handlers = NULL;
  p->num_handlers = 0;

  return 0;
}


int _emit(g_object* sender, const char* signal, void* data) {
  const signal_t* p;
  const handler_t* ph;

  p = get_signal(sender, signal);

  if (p == NULL) return ERR_SIGNAL_NOT_FOUND; /* no such signal */
  if (p->handlers == NULL) return 0;
  
  ph = p->handlers;

  while (ph - p->handlers < p->num_handlers) {
    if (*ph != NULL) {
      (*(handler_t)(*ph))(sender, data); /* call handler */
    }

    ++ph;
  }

  return 0;
}
