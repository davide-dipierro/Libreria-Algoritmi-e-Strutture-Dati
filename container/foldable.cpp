
#include <stdexcept>

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */


template<typename Data>
bool FoldableContainer<Data>::Exists(const Data& valore) const noexcept {
    bool result=false; // Inizializzato a false
    this->Fold( // Vengono iterati tutti gli elementi del container
        [this, valore](const Data& dat, void* result){
            *((bool*)result) |= (dat==valore); // Viene verificato ciascun elemento (dat) con valore ed eseguito l'OR con result
        }
    , &result // result viene passato come parametro (accumulatore) alla funzione Fold
    );
    return result; // Viene restituito result
}

/* ************************************************************************** */

}
