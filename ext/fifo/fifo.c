#include "ruby.h"

static VALUE rb_cFifo;
static VALUE rb_cElement;

static VALUE
rb_fifo_initialize(VALUE self)
{
    rb_iv_set(self, "@depth", INT2FIX(0));
    rb_iv_set(self, "@last", Qnil);
    return self;
}

static VALUE
rb_fifo_element_initialize(int argc, VALUE *argv, VALUE self) {
    VALUE v, p;

    if (argc == 0) {
      rb_raise(rb_eArgError, "Not enough arguments. You need to pass a value to store to initialize the element.");
    }

    rb_scan_args(argc, argv, "11", &v, &p);

    rb_iv_set(self, "@value", v);
    rb_iv_set(self, "@parent", p);

    return self;
}

static VALUE
rb_fifo_get_value(VALUE self)
{
    VALUE last;
    last = rb_iv_get(self, "@last");
    return rb_iv_get(last, "@value");
}

static VALUE
rb_fifo_push(VALUE self, VALUE next_value)
{
    long depth;
    VALUE next_obj;
    VALUE argv[2];

    argv[0] = next_value;
    argv[1] = rb_iv_get(self, "@last");
    next_obj = rb_class_new_instance(2, argv, rb_cElement);

    rb_iv_set(self, "@last", next_obj);

    depth = NUM2INT(rb_iv_get(self, "@depth"));
    rb_iv_set(self, "@depth", INT2FIX(depth + 1));

    return self;
}

static VALUE
rb_fifo_pop(VALUE self)
{
    long depth;
    VALUE last_obj, parent_obj;

    depth = NUM2INT(rb_iv_get(self, "@depth"));
    if (depth == 0) {
      return Qnil;
    }
    rb_iv_set(self, "@depth", INT2FIX(depth - 1));

    last_obj = rb_iv_get(self, "@last");
    parent_obj = rb_iv_get(last_obj, "@parent");
    rb_iv_set(self, "@last", parent_obj);

    return rb_iv_get(last_obj, "@value");
}

void
Init_fifo(void)
{
    rb_cFifo = rb_define_class("Fifo", rb_cObject);
    rb_define_method(rb_cFifo, "initialize", rb_fifo_initialize, 0);

    rb_define_attr(rb_cFifo, "depth", 1, 0);
    rb_define_attr(rb_cFifo, "last", 1, 0);
    rb_define_method(rb_cFifo, "value", rb_fifo_get_value, 0);
    rb_define_method(rb_cFifo, "push", rb_fifo_push, 1);
    rb_define_method(rb_cFifo, "pop", rb_fifo_pop, 0);

    rb_cElement = rb_define_class_under(rb_cFifo, "Element", rb_cObject);
    rb_define_method(rb_cElement, "initialize", rb_fifo_element_initialize, -1);
}   
