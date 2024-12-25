#include "Schedulable.h"
namespace planning
{
   int Schedulable::currentId = 1;

  Schedulable::Schedulable(){
    id = 1;
  }
  Schedulable::Schedulable(int id){
    setId(id);
  }
  void Schedulable::setId(int id){
    this->id = id;
  }
  int Schedulable::getId() const {
    return id;
  }
}
