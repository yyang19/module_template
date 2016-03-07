#include "env.h"
#include "skelton.h"

typedef struct skelton_priv{

    int var;
    int *arr;

}skelton_priv_t;

skelton_t *
skelton_new( char *name, int config1, float config2 ){

    skelton *s = (skelton *) malloc (sizeof(struct skelton) );
    if( !s )
       return NULL;

    strcpy( s->name, name );
    s->param1 = confgi1;
    s->param2 = config2; 

    s->priv = (void *) malloc (sizeof(struct skelton_priv) );
    if( !s->priv ){
        free(s);
        return NULL;
    }

    s->priv->var = 0;
    s->priv->arr = (int *) malloc( sizeof(int) * config1 );

    if( !s->priv->arr ){
        free(s->priv);
        free(s);
        return NULL;
    }


    return s;
}

void
skelton_delete( skelton *s ){

    free( s->priv->arr );
    free( s->priv );
    free( s );
}
