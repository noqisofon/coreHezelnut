

struct chn_class {
    CHNMetaClass            is_a;

    struct chn_class*       super_class;

    const char*             name;

    int                     version;
    unsigned int            info;
    size_t                  instance_size;

    struct chn_ivar_list*   ivars;

    struct chn_method_list* methods;

    struct chn_sarray*      dtable;

    struct chn_class_list*  subclass_list;
    struct chn_class_list*  sibling_class;

    void* gc_object_type;
};


typedef struct chn_class_node {
    struct chn_class_node* next;

    const char* name;
    int length;

    Class is_a;
} *chn_class_node_ptr;
