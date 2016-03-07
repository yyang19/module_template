#ifndef SKELTON_H
#define SKELTON_H

struct skelton_config{
    char name[100];

    int param1;
    float param2;

}skelton_config_t;

struct skelton_callback{


}skelton_callback_t;

struct skelton_info{

    skelton_config_t config;

    skelton_callback_t callback;

    void *priv;

}skelton_info_t;

struct skelton_alg{

    int (*func1)( skelton_info_t *info );

}skelton_alg_t;
#endif
