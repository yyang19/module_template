#ifndef skeleton_H
#define skeleton_H

#include "module.h"

typedef struct skeleton_config{
    char name[100];

    int param1;
    float param2;

}skeleton_config_t;

typedef struct skeleton_callback{


}skeleton_callback_t;

typedef struct skeleton_info{

    skeleton_config_t config;

    skeleton_callback_t callback;

    module_info_t m_info;

    void *priv;

}skeleton_info_t;

typedef struct skeleton_interface{

    int (*init)( skeleton_info_t *info );
    void (*run)( skeleton_info_t *info );
    void (*destroy)( skeleton_info_t *info );

}skeleton_interface_t;

extern skeleton_interface_t *skeleton_funcs;

#endif
