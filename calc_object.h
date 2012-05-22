/* header guard generate by genheader.pl */
#ifndef _calc_object_h_
#define _calc_object_h_

typedef struct _calc_object_t {
  g_object objbase;
  int num1, num2, result;
  char op;
} calc_object_t;

/*
 signals:
  add_signal(base, "set_num1");
  add_signal(base, "set_num2");
  add_signal(base, "set_op");
  add_signal(base, "set_result");
  add_signal(base, "get_result");
  add_signal(base, "do_eval");
  add_signal(base, "do_plus");
  add_signal(base, "do_minus");
  add_signal(base, "do_multiply");
  add_signal(base, "do_divide");
  add_signal(base, "error");  for user handle 


 */

void init_calc_object(calc_object_t* obj);
void destroy_calc_object(calc_object_t* obj);

void set_num1(calc_object_t* obj, int num);
void set_num2(calc_object_t* obj, int num);
void set_op(calc_object_t* obj, char op);
void eval(calc_object_t* obj);

void get_result(calc_object_t* obj, int* val_to_return);

/* implement functions */
void impl_set_num1(calc_object_t* obj, const int* num);
void impl_set_num2(calc_object_t* obj, const int* num);
void impl_set_op(calc_object_t* obj, const char* op);
void impl_eval(calc_object_t* obj);
void impl_set_result(calc_object_t* obj, const int* result);
void impl_get_result(calc_object_t* obj, int* valptr);

void impl_do_plus(calc_object_t* obj);
void impl_do_minus(calc_object_t* obj);
void impl_do_multiply(calc_object_t* obj);
void impl_do_divide(calc_object_t* obj);


#endif /* _calc_object_h_ */
