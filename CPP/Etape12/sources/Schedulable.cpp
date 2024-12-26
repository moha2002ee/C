#include "Schedulable.h"

namespace planning {

    // Initialisation du champ statique
    int Schedulable::currentId = 1;

    // --- Constructeurs ---
    Schedulable::Schedulable() {
        id = currentId++;  // Utilisation de currentId pour garantir l'unicité de l'ID
    }

    Schedulable::Schedulable(int id) {
        setId(id);
    }

    // --- Méthodes set/get ---
    void Schedulable::setId(int id) {
        this->id = id;
    }

    int Schedulable::getId() const {
        return id;
    }

}
