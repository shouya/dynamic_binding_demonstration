#include <stdio.h>
#include <math.h>

#include "signal.h"
#include "sample_object.h"
#include "calc_object.h"

void handler_destoryed(void);
void handler_another(g_object* sender, void* data);
void handler_print(g_object* sender, const char* data);
void handler_print_int(g_object* );

void calc_error_handler(calc_object_t* obj, const char* errstr);
void calc_plus_hacker(calc_object_t* obj);

void sample_demo(void);
void calc_demo(void);


sample_object_t obj1, obj2;
calc_object_t calc1, calc2;

int main(int argc, char** argv) {

  calc_demo();
  
  return 0;
}

void sample_demo(void) {
  init_sample_object(&obj1);
  init_sample_object(&obj2);

  connect(&obj1, "destroyed", &handler_destoryed);
  connect(&obj1, "destroyed", &handler_another);
  connect(&obj1, "print_event", &handler_print);
  connect(&obj2, "print_event", &handler_print);
  connect(&obj1, "an_event", &handler_another);
  connect(&obj2, "destroyed", &handler_print);

  
  sample_print(&obj1, "hello");
  sample_print(&obj2, "hi Shou!");
  sample_event(&obj1);
  
  puts("------- end program. destroying objects -------");
  
  destroy_sample_object(&obj1);
  destroy_sample_object(&obj2);
}

void calc_demo(void) {
  int result;
  
  init_calc_object(&calc1);
  init_calc_object(&calc2);


  set_num1(&calc1, 5);
  set_num2(&calc1, 10);
  set_op(&calc1, '+');
  eval(&calc1);
  get_result(&calc1, &result);

  printf("**first time: normally calc: 5+10 == %d**\n", result);


  set_num1(&calc1, 2);
  set_num2(&calc2, 3);
  set_op(&calc1, '#'); /* invalid operator */
  eval(&calc1);
  get_result(&calc1, &result);

  printf("**2nd time: use '#'(unhandled) operator, result: %d(no changed)**\n",
         result);

  
  connect(&calc1, "error", &calc_error_handler);
  eval(&calc1);

  printf("**3rd time: did you see the error handler works?**\n");

  
  /*  disconnect_all(&calc1, "do_plus");*/
  connect(&calc1, "do_plus", &calc_plus_hacker);
  set_num1(&calc1, 2);
  set_num2(&calc1, 10);
  set_op(&calc1, '+');
  eval(&calc1);
  get_result(&calc1, &result);

  printf("**4th time: hacked plus operation!! 2+10 == %d"
         "(actually it doing power)**\n", result);


  disconnect(&calc1, "do_plus", &calc_plus_hacker);
  eval(&calc1);
  get_result(&calc1, &result);
  
  printf("**5th time: disconnected hacker: now the result"
         "is normally back: %d**\n", result);
  
  
  destroy_calc_object(&calc1);
  destroy_calc_object(&calc2);
}

void handler_destoryed(void) {
  puts("some body will die soon, but i am blind, i don't know who's that.");
}
void handler_another(g_object* sender, void* data) {
  if (sender == (g_object*)&obj1) {
    printf("obj1 calls me send this data: %p\n", data);
  } else if (sender == (g_object*)&obj2) {
    printf("obj2 calls me send this data: %p\n", data);
  } else {
    printf("unkown object calls me!\n");
  }
}
void handler_print(g_object* sender, const char* data) {
  const char* sendername = NULL;
  if (sender == (g_object*)&obj1) sendername = "obj1";
  if (sender == (g_object*)&obj2) sendername = "obj2";
  
  printf("%s calls me print these: %s\n", sendername, data);
}

void calc_error_handler(calc_object_t* obj, const char* errstr) {
  printf("a calc object send me some error: %s\n", errstr);
}
void calc_plus_hacker(calc_object_t* obj) {
  /* hacks plus operation let power instead */
  puts("all your plus are belong to us now! hahahaaa!");
  obj->result = pow(obj->num1, obj->num2);
}
