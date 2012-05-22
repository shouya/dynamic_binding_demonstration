/* header guard generate by genheader.pl */
#ifndef _g_object_h_
#define _g_object_h_

typedef struct _g_object_t g_object;
typedef struct _signal_t signal_t;

struct _g_object_t {
  int num_signals;
  signal_t* sigtbl;
};

#define ERR_SIGNAL_ALREADY_EXSIST 1
#define ERR_SIGNAL_NOT_FOUND 2
#define ERR_HANDLER_ALREADY_EXSIST 3
#define ERR_HANDLER_NOT_FOUND 4

void init_object(g_object* obj);
void destroy_object(g_object* obj);
int add_signal(g_object* obj, const char* signame);

signal_t* get_signal(g_object* obj, const char* signame);
int del_signal(g_object* obj, const char* signame);


#endif /* _g_object_h_ */
