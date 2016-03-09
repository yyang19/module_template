#include <stdlib.h>
#include <string.h>
#include "env.h"
#include "module.h"
#include <assert.h>

typedef struct module_priv{

    int mod_var;
    int *mod_arr;

}module_priv_t;

static int
_my_module_init( module_info_t *info ){

    module_priv_t *p;

    assert(info);
    
    info->priv = (void *) malloc (sizeof(module_priv_t) );

    if( !info->priv )
       return -1;

    p = (module_priv_t *) info->priv;
    p->mod_arr = (int *)malloc( sizeof(int)*info->config.param1);

    if( !p->mod_arr ){
      free( info->priv );
      return -1;
    }

    return 0;    
}

static void
_my_module_destroy( module_info_t *info ){
    
    module_priv_t *p = (module_priv_t *) info->priv;
    
    free( p->mod_arr );
    free( info->priv );
}

static int
_my_module_func1( module_info_t *info ) {
   
   module_priv_t *priv = (module_priv_t *) info->priv;
   return priv->mod_var;
}

static float
_my_module_func2( module_info_t *info ) {
   return info->callback.cb_skeleton( info, info->config.param2 );
}


static module_interface_t _mi = {
   _my_module_init,
   _my_module_destroy,
   _my_module_func1,
   _my_module_func2,
};

module_interface_t *module_interface = &_mi;
