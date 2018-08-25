#include "ruby.h"

static VALUE rb_cFifo;
static VALUE rb_cNode;

static VALUE
rb_fifo_initialize(VALUE self)
{
    rb_iv_set(self, "@length", INT2FIX(0));
    rb_iv_set(self, "@first_node", Qnil);
    rb_iv_set(self, "@last_node", Qnil);
    return self;
}

static VALUE
rb_fifo_node_initialize(int argc, VALUE *argv, VALUE self) {
    VALUE v;

    if (argc == 0) {
      rb_raise(rb_eArgError, "Not enough arguments. You need to pass a value to store to initialize the element.");
    }

    rb_scan_args(argc, argv, "10", &v);
    rb_iv_set(self, "@value", v);
    return self;
}

static VALUE
rb_fifo_get_front(VALUE self)
{
    VALUE first_node;
    first_node = rb_iv_get(self, "@first_node");
    return rb_iv_get(first_node, "@value");
}

static VALUE
rb_fifo_get_back(VALUE self)
{
    VALUE last_node;
    last_node = rb_iv_get(self, "@last_node");
    return rb_iv_get(last_node, "@value");
}

static VALUE
rb_fifo_enqueue(VALUE self, VALUE new_value)
{
    long length;
    VALUE new_node, last_node;

    new_node = rb_class_new_instance(1, &new_value, rb_cNode);

    length = NUM2INT(rb_iv_get(self, "@length"));
    if (length == 0) {
        rb_iv_set(self, "@first_node", new_node);
        rb_iv_set(self, "@last_node", new_node);
    } else {
        last_node = rb_iv_get(self, "@last_node");
        rb_iv_set(last_node, "@next", new_node);
        rb_iv_set(self, "@last_node", new_node);
    }

    rb_iv_set(self, "@length", INT2FIX(length + 1));
    return self;
}

static VALUE
rb_fifo_dequeue(VALUE self)
{
    long length;
    VALUE old_node, child_node;

    length = NUM2INT(rb_iv_get(self, "@length"));
    if (length == 0) {
      return Qnil;
    }

    old_node = rb_iv_get(self, "@first_node");
    child_node = rb_iv_get(old_node, "@next");
    rb_iv_set(self, "@first_node", child_node);

    if (length == 1) {
        rb_iv_set(self, "@last_node", Qnil);
    }
    rb_iv_set(self, "@length", INT2FIX(length - 1));

    return rb_iv_get(old_node, "@value");
}

void
Init_fifo(void)
{
    rb_cFifo = rb_define_class("Fifo", rb_cObject);
    rb_define_method(rb_cFifo, "initialize", rb_fifo_initialize, 0);

    rb_define_attr(rb_cFifo, "length", 1, 0);
    rb_define_method(rb_cFifo, "front", rb_fifo_get_front, 0);
    rb_define_method(rb_cFifo, "back", rb_fifo_get_back, 0);
    rb_define_method(rb_cFifo, "enqueue", rb_fifo_enqueue, 1);
    rb_define_method(rb_cFifo, "dequeue", rb_fifo_dequeue, 0);

    rb_cNode = rb_define_class_under(rb_cFifo, "Node", rb_cObject);
    rb_define_method(rb_cNode, "initialize", rb_fifo_node_initialize, -1);
}   
