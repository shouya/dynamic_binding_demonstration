/* header guard generate by genheader.pl */
#ifndef _signal_h_
#define _signal_h_

#include "g_object.h"

typedef void (*handler_t)(g_object* sender, void* data);

struct _signal_t {
  const char* signame;
  int num_handlers;
  const handler_t* handlers;
};

/* interface for user calls */
#define connect(sender, signal, handler)                                \
  _connect((g_object*)sender, (const char*)signal, (handler_t)handler)
#define disconnect(sender, signal, handler)                             \
  _disconnect((g_object*)sender, (const char*)signal, (handler_t)handler)
#define disconnect_all(sender, signal)                          \
  _disconnect_all((g_object*)sender, (const char*)signal)

#define emit(sender, signal, data)                              \
  _emit((g_object*)sender, (const char*)signal, (void*)data)

/* begin internal implement */
int _connect(g_object* sender, const char* signal, handler_t handler);
int _disconnect(g_object* sender, const char* signal, handler_t handler);
int _disconnect_all(g_object* sender, const char* signal);
int _emit(g_object* sender, const char* signal, void* data);

void free_signal(signal_t* signal);

/* end internal implement */



#endif /* _signal_h_ */
