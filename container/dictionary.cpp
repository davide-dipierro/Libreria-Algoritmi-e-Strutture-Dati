
#include <stdexcept>

/* ************************************************************************** */

namespace lasd { 

/* ************************************************************************** */

template<typename Data>
bool DictionaryContainer<Data>::InsertAll(const MappableContainer<Data>& cont){ // Inserimento da un MappableContainer
    bool result = true; // Inizializzato a true
    cont.Map( // Vengono iterati gli elementi del container attraverso la funzione Map
        [this, &result] (const Data& dat) {
            result &= Insert(dat); // Se tutti gli inserimenti (per lvalue) vanno a buon fine, l'AND restituisce true
        }
    ); // La funzione richiede un solo parametro
    return result; // Restituzione del valore
}

template<typename Data>
bool DictionaryContainer<Data>::InsertAll(MutableMappableContainer<Data>&& cont){ // Inserimento da un MutableMappableContainer
    bool result = true;
    cont.Map(
        [this, &result] (Data& dat) {
            result &= Insert(std::move(dat)); // Se tutti gli inserimenti (per rvalue) vanno a buon fine, l'AND restituisce true
        }
    );
    return result;
}

template<typename Data>
bool DictionaryContainer<Data>::RemoveAll(const MappableContainer<Data>& cont){ // Rimozione da un MappableContainer
    bool result = true;
    cont.Map(
        [this, &result] (const Data& dat) {
            result &= Remove(dat); // Se tutte le rimozioni vanno a buon fine l'AND restituisce true
        }
    );
    return result;
}

template<typename Data>
bool DictionaryContainer<Data>::InsertSome(const MappableContainer<Data>& cont){ // Inserimento da un MappableContainer
    bool result = false; // Inizializzato a false
    cont.Map(
        [this, &result] (const Data& dat) { // Se almeno un inserimento (lvalue) va a buon fine l'OR restituisce true
            result |= Insert(dat);
        }
    );
    return result;
}

template<typename Data>
bool DictionaryContainer<Data>::InsertSome(MutableMappableContainer<Data>&& cont){ // Inserimento da un MutableMappableContainer
    bool result = false;
    cont.Map(
        [this, &result] (Data& dat) {
            result |= Insert(std::move(dat)); // Se almeno un inserimento (rvalue) va a buon fine l'OR restituisce true
        }
    );
    return result;
}

template<typename Data>
bool DictionaryContainer<Data>::RemoveSome(const MappableContainer<Data>& cont){ // Rimozione da un MappableContainer
    bool result = false;
    cont.Map(
        [this, &result] (const Data& dat) {
            result |= Remove(dat); // Se almeno una rimozione va  abuon fine l'OR restituisce true
        }
    );
    return result;
}

/* ************************************************************************** */

}
