#include "ruby.h"

static VALUE rb_cCFifo;
static VALUE rb_cFifoNode;

struct cFifoNode {
    VALUE value;
    struct cFifoNode *next;
};

struct cFifoList {
    long length;
    struct cFifoNode *front;
    struct cFifoNode *back;
};

static struct cFifoList * cFifoListTable[1]; //XXX FIXME オブジェクトごとにマップする、スレッドセーフになりたい

static struct cFifoList *
fifo_list_xmalloc()
{
    void *ptr;

    ptr = malloc(sizeof(struct cFifoList));
    if (ptr == NULL) {
        rb_raise(rb_eRuntimeError, "can't malloc");
    }

    return (struct cFifoList *) ptr;
}

static struct cFifoNode *
fifo_node_xmalloc()
{
    void *ptr;

    ptr = malloc(sizeof(struct cFifoNode));
    if (ptr == NULL) {
        rb_raise(rb_eRuntimeError, "can't malloc");
    }

    return (struct cFifoNode *) ptr;
}

static void
fifo_node_free(struct cFifoNode *node_p)
{
    free(node_p);
}

static struct cFifoNode *
init_fifo_node(VALUE value)
{
    struct cFifoNode *node_p;

    node_p = fifo_node_xmalloc();

    node_p->value = value;
    node_p->next = NULL;

    return node_p;
}

static struct cFifoList *
init_fifo_list(VALUE self)
{
    struct cFifoList *list_p;

    list_p = fifo_list_xmalloc();

    list_p->length = 0;
    list_p->front = NULL;
    list_p->back = NULL;

    return list_p;
}

void
register_fifo_list(VALUE self, struct cFifoList *list)
{
    cFifoListTable[0] = list; // FIXME オブジェクトごとのマッピングをする
}

static struct cFifoList *
get_fifo_list(VALUE self) {
    return cFifoListTable[0]; // FIXME オブジェクトごとに保持する
}

static VALUE
rb_cfifo_initialize(VALUE self)
{
    struct cFifoList *list_p;
    
    list_p = init_fifo_list(self);
    register_fifo_list(self, list_p);

    return self;
}

static VALUE
rb_cfifo_get_front(VALUE self)
{
    struct cFifoList *list_p = get_fifo_list(self);

    return( list_p->front == NULL ? Qnil : list_p->front->value );
}

static VALUE
rb_cfifo_get_back(VALUE self)
{
    struct cFifoList *list_p = get_fifo_list(self);

    return( list_p->back == NULL ? Qnil : list_p->back->value );
}

static VALUE
rb_cfifo_get_length(VALUE self)
{
    struct cFifoList *list_p = get_fifo_list(self);

    // TODO lengthに上限をつくるか、INT2NUMにする
    return INT2FIX(list_p->length);
}


static VALUE
rb_cfifo_enqueue(VALUE self, VALUE next_value)
{
    struct cFifoList *list_p = get_fifo_list(self);
    struct cFifoNode *back_node_p = list_p->back;
    struct cFifoNode *new_node_p;

    // TODO lengthに上限をつくる（31　/ 63bit上限値）
    new_node_p = init_fifo_node(next_value);

    if (list_p->length == 0) {
        list_p->front = new_node_p;
    } else {
        back_node_p->next = new_node_p;
    }

    list_p->back = new_node_p;
    list_p->length++;
    rb_gc_mark(next_value); // TODO pop時に解放できる？要検討

    return self;
}

static VALUE
rb_cfifo_dequeue(VALUE self)
{
    struct cFifoList *list_p = get_fifo_list(self);
    struct cFifoNode *front_node_p = list_p->front;
    VALUE last_value;

    if (list_p->length == 0) {
        return Qnil;
    }

    list_p->front = front_node_p->next;
    if (--list_p->length == 0) {
        list_p->back = NULL;
    }

    last_value = front_node_p->value;
    fifo_node_free(front_node_p);
    return last_value;
}

void
Init_cfifo(void)
{
    rb_cCFifo = rb_define_class("CFifo", rb_cObject);
    rb_define_method(rb_cCFifo, "initialize", rb_cfifo_initialize, 0);

    rb_define_method(rb_cCFifo, "length", rb_cfifo_get_length, 0);
    rb_define_method(rb_cCFifo, "front", rb_cfifo_get_front, 0);
    rb_define_method(rb_cCFifo, "back", rb_cfifo_get_back, 0);
    rb_define_method(rb_cCFifo, "enqueue", rb_cfifo_enqueue, 1);
    rb_define_method(rb_cCFifo, "dequeue", rb_cfifo_dequeue, 0);

    rb_cFifoNode = rb_define_class_under(rb_cCFifo, "cFifoNode", rb_cData);
}   
