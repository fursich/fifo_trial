#include "ruby.h"

static VALUE rb_cCLifo;
static VALUE rb_ccLifoNode;

struct cLifoNode {
    VALUE value;
    struct cLifoNode *next;
};

struct cLifoList {
    long length;
    struct cLifoNode *head;
};

static struct cLifoList * cLifoListTable[1]; //XXX FIXME オブジェクトごとにマップする、スレッドセーフになりたい

static struct cLifoList *
lifo_list_xmalloc()
{
    void *ptr;

    ptr = malloc(sizeof(struct cLifoList));
    if (ptr == NULL) {
        rb_raise(rb_eRuntimeError, "can't malloc");
    }

    return (struct cLifoList *) ptr;
}

static struct cLifoNode *
lifo_node_xmalloc()
{
    void *ptr;

    ptr = malloc(sizeof(struct cLifoNode));
    if (ptr == NULL) {
        rb_raise(rb_eRuntimeError, "can't malloc");
    }

    return (struct cLifoNode *) ptr;
}

static void
lifo_node_free(struct cLifoNode *node_p)
{
    free(node_p);
}

static struct cLifoNode *
init_lifo_node(VALUE value, struct cLifoNode *next_node)
{
    struct cLifoNode *node_p;

    node_p = lifo_node_xmalloc();

    node_p->value = value;
    node_p->next = next_node;

    return node_p;
}

static struct cLifoList *
init_lifo_list(VALUE self)
{
    struct cLifoList *list_p;

    list_p = lifo_list_xmalloc();

    list_p->length = 0;
    list_p->head = NULL;

    return list_p;
}

void
register_lifo_list(VALUE self, struct cLifoList *list)
{
    cLifoListTable[0] = list; // FIXME オブジェクトごとのマッピングをする
}

static struct cLifoList *
get_lifo_list(VALUE self) {
    return cLifoListTable[0]; // FIXME オブジェクトごとに保持する
}

static VALUE
rb_clifo_initialize(VALUE self)
{
    struct cLifoList *list_p;
    
    list_p = init_lifo_list(self);
    register_lifo_list(self, list_p);

    return self;
}

static VALUE
rb_clifo_get_value(VALUE self)
{
    struct cLifoList *list_p = get_lifo_list(self);

    return( list_p->head == NULL ? Qnil : list_p->head->value );
}

static VALUE
rb_clifo_get_length(VALUE self)
{
    struct cLifoList *list_p = get_lifo_list(self);

    // TODO lengthに上限をつくるか、INT2NUMにする
    return INT2FIX(list_p->length);
}


static VALUE
rb_clifo_push(VALUE self, VALUE next_value)
{
    struct cLifoList *list_p = get_lifo_list(self);
    struct cLifoNode *last_node_p = list_p->head;
    struct cLifoNode *new_node_p;

    // TODO lengthに上限をつくる（31　/ 63bit上限値）
    new_node_p = init_lifo_node(next_value, last_node_p);
    list_p->head = new_node_p;
    list_p->length++;
    rb_gc_mark(next_value); // TODO pop時に解放できる？要検討

    return self;
}

static VALUE
rb_clifo_pop(VALUE self)
{
    struct cLifoList *list_p = get_lifo_list(self);
    struct cLifoNode *last_node_p = list_p->head;
    VALUE last_value;

    if (list_p->length == 0) {
        return Qnil;
    }

    list_p->head = last_node_p->next;
    list_p->length--;

    last_value = last_node_p->value;
    lifo_node_free(last_node_p);
    return last_value;
}

void
Init_clifo(void)
{
    rb_cCLifo = rb_define_class("CLifo", rb_cObject);
    rb_define_method(rb_cCLifo, "initialize", rb_clifo_initialize, 0);

    rb_define_method(rb_cCLifo, "length", rb_clifo_get_length, 0);
    rb_define_method(rb_cCLifo, "value", rb_clifo_get_value, 0);
    rb_define_method(rb_cCLifo, "push", rb_clifo_push, 1);
    rb_define_method(rb_cCLifo, "pop", rb_clifo_pop, 0);

    rb_ccLifoNode = rb_define_class_under(rb_cCLifo, "cLifoNode", rb_cData);
}   
