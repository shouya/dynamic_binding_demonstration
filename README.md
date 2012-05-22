##What is this
This project is a demonstration of the implement of signal/slot connection model like GTK+. Unlike Qt, this implement is written in pure C, and without any form of meta-programming.


##How do I use this
Sorry that you can't use this, as it is not a **practical** tool. It's only written for study use.

For check the result of the program, simply `make`, and then it will generate a binary file names `main`, and run it to see the result.


##Where should I start to read it
My advise is read from the start-up point -- main function in `main.c`.

Actually there I designed two demonstrations in the file, the `sample_demo` and the `calc_demo`. While the first one demonstrated a very simple signal connection with just destroy and some even handlers, with binding them all up dynamically and then calls. For much cooler hack, see the second one, which is a calculator with dynamic handler binding. The code performed some interesting stuff like dynamic binding changing and disconnection.

For the internal principle, you could check `g_object.c` to see how the object oriented model is implemented here and how the base of signal connection is.

For the detailed signal implement, actually it is just a self-maintained list inside an object, check `signal.c`, for these and relevant things.

Above the base, there are two object classes which are written for demonstration, they are `sample_object` and `calc_object`, separately for `sample_demo` and `calc_demo`.

Whole the project is just these, may it helps!

