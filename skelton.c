#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "env.h"
#include "skelton.h"
#include "module.h"
typedef struct skelton_priv{

    int var;
    int *arr;

}skelton_priv_t;

static int 
_init( skelton_info_t *s ){

    assert(s);

    skelton_priv_t *p;

    s->priv = (void *) malloc (sizeof(struct skelton_priv) );

    if( !s->priv )
        goto priv_fail;

    p = (skelton_priv_t *) s->priv;

    p->var =500;
    p->arr = (int *) malloc( sizeof(int) * s->config.param1 );

    if( !p->arr )
      goto priv_arr_fail;    

    /* module configuration */
    strcpy( s->m_info.config.name, s->config.name );
    s->m_info.config.param1 = s->config.param1;
    s->m_info.config.param2 = s->config.param2;
    s->m_info.config.m_var  = 0;

    module_interface->init(&s->m_info);

    return 0;

priv_arr_fail:
    free(s->priv);
priv_fail:
    free(s);

    return -1;
}

static void
_run( skelton_info_t *s_info){

   int ret1;
   float ret2;
   
   ret1 = module_interface->func1( &s_info->m_info );

   printf("Ret1 = %d\n", ret1);
   
   ret2 = module_interface->func2( &s_info->m_info );

   printf("Ret2 = %2f\n", ret2);

}

static void
_delete( skelton_info_t *s ){

    skelton_priv_t *p;

    module_interface->destroy(&s->m_info);

    p = (skelton_priv_t *) s->priv;
    free( p->arr );
    free( s->priv );
}

static float
_func1( module_info_t *m, float param ){

   skelton_info_t *s = SYS_CONTAINER_OF( m, skelton_info_t, m_info );
   skelton_priv_t *p = (skelton_priv_t *)s->priv;

   return p->var * param;
}


static skelton_interface_t _funcs = {
   _init,
   _run,
   _delete,
   _func1,
};

skelton_interface_t *skelton_funcs = &_funcs;

int
main(){

   skelton_info_t s;

   /*skelton configuration*/
   strcpy( s.config.name, "uoft" );
   s.config.param1 = 20;
   s.config.param2 = 0.5; 

   /*skelton initialization*/
   skelton_funcs->init(&s);

   skelton_funcs->run(&s);

   skelton_funcs->destroy(&s);
   return 0;
}
