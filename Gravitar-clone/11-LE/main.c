#include <stdio.h>
#include <assert.h>
#include "lista.h"

int main(void) {
    lista_t * super = lista_crear();
    assert (super != NULL);

    bool r;

    r = lista_agregar_al_final(super, "mate");
    assert(r);
    r = lista_agregar_al_final(super, "cafe");
    assert(r);
    r = lista_agregar_al_final(super, "harina");
    assert(r);
    r = lista_agregar_al_final(super, "palmitos");
    assert(r);

    size_t n = lista_largo(super);

    printf("la lista tiene %zd elementos\n", n);
}
