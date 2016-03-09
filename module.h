#ifndef MODULE_H
#define MODULE_H

typedef struct module_info module_info_t;

typedef struct module_config{
   
    char name[100];
    int param1;
    float param2;
    int m_var;

}module_config_t;

typedef struct module_callback{
   float (*cb_skelton) (module_info_t *info, float param);
}module_callback_t;

typedef struct module_info{

    module_config_t config;

    module_callback_t callback;

    void *priv;

}module_info_t;

typedef struct module_interface{

    int (*init)( module_info_t *info );
    void(*destroy)( module_info_t *info );
    int (*func1)( module_info_t *info );
    float (*func2)( module_info_t *info );

}module_interface_t;

extern module_interface_t *module_interface;

#endif
