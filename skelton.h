#ifndef SKELTON_H
#define SKELTON_H

#include "module.h"

typedef struct skelton_config{
    char name[100];

    int param1;
    float param2;

}skelton_config_t;

typedef struct skelton_callback{


}skelton_callback_t;

typedef struct skelton_info{

    skelton_config_t config;

    skelton_callback_t callback;

    module_info_t m_info;

    void *priv;

}skelton_info_t;

typedef struct skelton_interface{

    int (*init)( skelton_info_t *info );
    void (*run)( skelton_info_t *info );
    void (*destroy)( skelton_info_t *info );

}skelton_interface_t;

extern skelton_interface_t *skelton_funcs;

#endif
