#ifndef MODULE_H
#define MODULE_H

struct module_config{
    char name[100];

    int param1;
    float param2;

}module_config_t;

struct module_info{

    module_config_t config;

    module_callback_t callback;

    void *priv;

}module_info_t;

struct module_alg{

    int (*func1)( module_info_t *info );

}module_alg_t;
#endif
