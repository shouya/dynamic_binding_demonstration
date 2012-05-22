#include <stdlib.h>

#include "signal.h"

#include "calc_object.h"

void init_calc_object(calc_object_t* obj) {
  g_object* base, *this;

  base = &obj->objbase;
  this = (g_object*)obj;

  init_object(base);

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
  add_signal(base, "error");

  connect(this, "set_num1", &impl_set_num1);
  connect(this, "set_num2", &impl_set_num2);
  connect(this, "set_op", &impl_set_op);
  connect(this, "set_result", &impl_set_result);
  connect(this, "get_result", &impl_get_result);
  connect(this, "do_eval", &impl_eval);
  connect(this, "do_plus", &impl_do_plus);
  connect(this, "do_minus", &impl_do_minus);
  connect(this, "do_multiply", &impl_do_multiply);
  connect(this, "do_divide", &impl_do_divide);
}

void destroy_calc_object(calc_object_t* obj) {
  destroy_object(&obj->objbase);
}

void set_num1(calc_object_t* obj, int num) {
  emit(obj, "set_num1", &num);
}

void set_num2(calc_object_t* obj, int num) {
  emit(obj, "set_num2", &num);
}

void set_op(calc_object_t* obj, char op) {
  emit(obj, "set_op", &op);
}

void eval(calc_object_t* obj) {
  emit(obj, "do_eval", NULL);
}

void get_result(calc_object_t* obj, int* val_to_return) {
  emit(obj, "get_result", val_to_return);
}


/* implement functions */
void impl_set_num1(calc_object_t* obj, const int* num) {
  obj->num1 = *num;
}
void impl_set_num2(calc_object_t* obj, const int* num) {
  obj->num2 = *num;
}
void impl_set_op(calc_object_t* obj, const char* op) {
  obj->op = *op;
}
void impl_eval(calc_object_t* obj) {
  switch (obj->op) {
    case '+':
      emit(obj, "do_plus", NULL);
      break;
    case '-':
      emit(obj, "do_minus", NULL);
      break;
    case '*':
      emit(obj, "do_multiply", NULL);
      break;
    case '/':
      emit(obj, "do_divide", NULL);
      break;
    default:
      emit(obj, "error", "operator invalid!");
  }
}

void impl_set_result(calc_object_t* obj, const int* result) {
  obj->result = *result;
}

void impl_get_result(calc_object_t* obj, int* valptr) {
  if (valptr == 0) emit(obj, "error", "cannot send result into a null-ptr.");
  *valptr = obj->result;
}

void impl_do_plus(calc_object_t* obj) {
  int result = obj->num1 + obj->num2;
  emit(obj, "set_result", &result);
}

void impl_do_minus(calc_object_t* obj) {
  int result = obj->num1 - obj->num2;
  emit(obj, "set_result", &result);
}

void impl_do_multiply(calc_object_t* obj) {
  int result = obj->num1 * obj->num2;
  emit(obj, "set_result", &result);
}

void impl_do_divide(calc_object_t* obj) {
  int result;
  if (obj->num2 == 0) {
    emit(obj, "error", "cannot divide by zero!");
    return;
  }

  result = obj->num1 - obj->num2;
  emit(obj, "set_result", &result);
}
