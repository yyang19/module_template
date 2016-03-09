#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "env.h"
#include "skeleton.h"
#include "module.h"

static module_callback_t _module_cb;

typedef struct skeleton_priv{

    int var;
    int *arr;

}skeleton_priv_t;

static int 
_init( skeleton_info_t *s ){

    assert(s);

    skeleton_priv_t *p;

    s->priv = (void *) malloc (sizeof(struct skeleton_priv) );

    if( !s->priv )
        goto priv_fail;

    p = (skeleton_priv_t *) s->priv;

    p->var =500;
    p->arr = (int *) malloc( sizeof(int) * s->config.param1 );

    if( !p->arr )
      goto priv_arr_fail;    

    /* module configuration */
    strcpy( s->m_info.config.name, s->config.name );
    s->m_info.config.param1 = s->config.param1;
    s->m_info.config.param2 = s->config.param2;
    s->m_info.config.m_var  = 0;

    /* module callback function */
    s->m_info.callback = _module_cb;

    module_interface->init(&s->m_info);

    return 0;

priv_arr_fail:
    free(s->priv);
priv_fail:
    free(s);

    return -1;
}

static void
_run( skeleton_info_t *s_info){

   int ret1;
   float ret2;
   
   ret1 = module_interface->func1( &s_info->m_info );

   printf("Ret1 = %d\n", ret1);
   
   ret2 = module_interface->func2( &s_info->m_info );

   printf("Ret2 = %2f\n", ret2);

}

static void
_delete( skeleton_info_t *s ){

    skeleton_priv_t *p;

    module_interface->destroy(&s->m_info);

    p = (skeleton_priv_t *) s->priv;
    free( p->arr );
    free( s->priv );
}

static float
_func1( module_info_t *m, float param ){

   skeleton_info_t *s = SYS_CONTAINER_OF( m, skeleton_info_t, m_info );
   skeleton_priv_t *p = (skeleton_priv_t *)s->priv;

   return p->var * param;
}


static skeleton_interface_t _funcs = {
   _init,
   _run,
   _delete,
};

static module_callback_t _module_cb = {
    _func1
};

skeleton_interface_t *skeleton_funcs = &_funcs;

int
main(){

   skeleton_info_t s;

   /*skeleton configuration*/
   strcpy( s.config.name, "uoft" );
   s.config.param1 = 20;
   s.config.param2 = 0.5; 

   /*skeleton initialization*/
   skeleton_funcs->init(&s);

   skeleton_funcs->run(&s);

   skeleton_funcs->destroy(&s);
   return 0;
}
