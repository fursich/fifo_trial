#include "ruby.h"

static VALUE rb_cLifo;
static VALUE rb_cElement;

static VALUE
rb_lifo_initialize(VALUE self)
{
    rb_iv_set(self, "@length", INT2FIX(0));
    rb_iv_set(self, "@last", Qnil);
    return self;
}

static VALUE
rb_lifo_element_initialize(int argc, VALUE *argv, VALUE self) {
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
rb_lifo_get_value(VALUE self)
{
    VALUE last;
    last = rb_iv_get(self, "@last");
    return rb_iv_get(last, "@value");
}

static VALUE
rb_lifo_push(VALUE self, VALUE next_value)
{
    long length;
    VALUE next_obj;
    VALUE argv[2];

    argv[0] = next_value;
    argv[1] = rb_iv_get(self, "@last");
    next_obj = rb_class_new_instance(2, argv, rb_cElement);

    rb_iv_set(self, "@last", next_obj);

    length = NUM2INT(rb_iv_get(self, "@length"));
    rb_iv_set(self, "@length", INT2FIX(length + 1));

    return self;
}

static VALUE
rb_lifo_pop(VALUE self)
{
    long length;
    VALUE last_obj, parent_obj;

    length = NUM2INT(rb_iv_get(self, "@length"));
    if (length == 0) {
      return Qnil;
    }
    rb_iv_set(self, "@length", INT2FIX(length - 1));

    last_obj = rb_iv_get(self, "@last");
    parent_obj = rb_iv_get(last_obj, "@parent");
    rb_iv_set(self, "@last", parent_obj);

    return rb_iv_get(last_obj, "@value");
}

void
Init_lifo(void)
{
    rb_cLifo = rb_define_class("Lifo", rb_cObject);
    rb_define_method(rb_cLifo, "initialize", rb_lifo_initialize, 0);

    rb_define_attr(rb_cLifo, "length", 1, 0);
    rb_define_attr(rb_cLifo, "last", 1, 0);
    rb_define_method(rb_cLifo, "value", rb_lifo_get_value, 0);
    rb_define_method(rb_cLifo, "push", rb_lifo_push, 1);
    rb_define_method(rb_cLifo, "pop", rb_lifo_pop, 0);

    rb_cElement = rb_define_class_under(rb_cLifo, "Element", rb_cObject);
    rb_define_method(rb_cElement, "initialize", rb_lifo_element_initialize, -1);
}   
