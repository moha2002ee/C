#include "Timetable.h"

Timetable Timetable::instance;

int Timetable::addClassroom(const string& name,int seatingCapacity){
     cout << "---Classroom: constructeur d'initialisation" << endl; 

     classrooms.insert(Classroom(Schedulable::currentId, name, seatingCapacity));
     Schedulable::currentId++;
     return classrooms.size();
} 
void Timetable::displayClassrooms() const{
     cout << "contenu classrooms: " << endl;

     for (set<Classroom>::const_iterator it = classrooms.cbegin(); it != classrooms.cend(); it++){
          cout << it->toString() << endl;
     }
}
Classroom Timetable::findClassroomByIndex(int index) const{
     int currentIndex = 0;
     for (set<Classroom>::const_iterator it = classrooms.cbegin(); it != classrooms.cend(); it++){
          if(currentIndex == index) return *it;

          currentIndex++;
     }
     throw std::out_of_range("Index hors limites");

}
Classroom Timetable::findClassroomById(int id) const
{
     
     for (auto it = classrooms.cbegin(); it != classrooms.cend(); ++it)
     {
          if(it->getId() == id)
          {
               return *it;
          }
     }
     throw std::out_of_range("Identifiant non trouvé");
}

void Timetable::deleteClassroomByIndex(int index)
{
     int currentIndex = 0;
     for (auto it = classrooms.begin(); it != classrooms.end(); ++it)
     {
          if(currentIndex == index)
          {
               classrooms.erase(it);
               return;
          }

          ++currentIndex;
     }
     throw std::out_of_range("Index hors limites");
}

void Timetable::deleteClassroomById(int id)
{
     for (auto it = classrooms.begin(); it != classrooms.end(); ++it)
     {
          if(it->getId() == id)
          {
               classrooms.erase(it);
               return;
          }
     }
     throw std::out_of_range("Identifiant non trouvé");
}

bool Timetable::isClassroomAvailable(int id, const Timing& timing)
{
     for (auto it = courses.begin(); it != courses.end(); it++)
     {
          if (it->getClassroomId() == id && it->getTiming().intersect(timing))
          {
           return false;
          }
     }
     return true;
}

int Timetable::addProfessor(const string& lastName,const string& firstName)
{
     cout << "---Professor: constructeur d'initialisation" << endl; 

     professors.insert(Professor(Schedulable::currentId, lastName, firstName));

     ++Schedulable::currentId;
     return professors.size();

}

void Timetable::displayProfessors() const
{
     cout << "contenu professors: " << endl;

     for (auto it = professors.cbegin(); it != professors.cend(); ++it)
     {
          cout << it->toString() << endl;
     } 
}

Professor Timetable::findProfessorByIndex(int index) const
{
     int currentIndex = 0;
     for (auto it = professors.cbegin(); it != professors.cend(); ++it)
     {
          if(currentIndex == index)
          {
               return *it;
          }

          ++currentIndex;
     }
     throw std::out_of_range("Index hors limites");
}

Professor Timetable::findProfessorById(int id) const
{
     for (auto it = professors.cbegin(); it != professors.cend(); ++it)
     {
          if(it->getId() == id)
          {
               return *it;
          }
     }
     throw std::out_of_range("Identifiant non trouvé");
}

void Timetable::deleteProfessorByIndex(int index)
{
     int currentIndex = 0;
     for (auto it = professors.begin(); it != professors.end(); ++it)
     {
          if (currentIndex == index)
          {
               professors.erase(it);
               return;
          }

          ++currentIndex;
     }
     throw std::out_of_range("Index hors limite");
}

void Timetable::deleteProfessorById(int id)
{
     for (auto it = professors.begin(); it != professors.end(); ++it)
     {
          if (it->getId() == id)
          {
               professors.erase(it);
               return;
          }
     }
     throw std::out_of_range("Identificant non trouvé");
}

bool Timetable::isProfessorAvailable(int id, const Timing& timing)
{
     for (auto it = courses.begin(); it != courses.end(); it++)
     {
          if (it->getProfessorId() == id && it->getTiming().intersect(timing))
          {
           return false;
          }
     }
     return true;
}

int Timetable::addGroup(const string& name)
{
     cout << "---Group: constructeur d'initialisation" << endl; 

     groups.insert(Group(Schedulable::currentId, name));

     ++Schedulable::currentId;
     return groups.size();
}

void Timetable::displayGroups() const
{
    cout << "contenu groups: " << endl;

     for (auto it = groups.cbegin(); it != groups.cend(); ++it)
     {
          cout << it->toString() << endl;
     }  
}

Group Timetable::findGroupByIndex(int index) const
{
     int currentIndex = 0;

     for (auto it = groups.cbegin() ; it != groups.cend(); ++it)
     {
          if (currentIndex == index)
          {
               return *it;
          }

          ++currentIndex;
     }
     throw std::out_of_range("Index hors limites");
}

Group Timetable::findGroupById(int id) const
{
     for (auto it = groups.cbegin() ; it != groups.cend(); ++it)
     {
          if (it->getId() == id)
          {
               return *it;
          }
     }
     throw std::out_of_range("Index hors limites");
}

void Timetable::deleteGroupByIndex(int index)
{
     int currentIndex = 0;

     for (auto it = groups.begin(); it != groups.end(); ++it)
     {
          if (currentIndex == index)
          {
               groups.erase(it);
               return;
          }

          ++currentIndex;
     }
     throw std::out_of_range("Index hors limite");
}

void Timetable::deleteGroupById(int id)
{
     for (auto it = groups.begin(); it != groups.end(); ++it)
     {
          if (it->getId() == id)
          {
               groups.erase(it);
               return;
          }
     }
     throw std::out_of_range("Identificant non trouvé");
}

bool Timetable::isGroupAvailable(int id, const Timing& timing)
{
     if (courses.empty())
     {
        cout << "Aucun cours dans la liste." << endl;
        return true; // Si aucun cours, le groupe est disponible
     }

     for (auto it = courses.cbegin(); it != courses.cend(); ++it)
     {
          cout << "id prof :" << it->getProfessorId() << endl;
          cout << "id local :" << it->getClassroomId() << endl;

          const auto& groupIds = it->getGroupsIds();
          if (groupIds.empty())
          {
            cout << "Aucun groupe associé à ce cours." << endl;
            continue; // Passer au prochain cours
          }

          for (auto groupId = groupIds.cbegin(); groupId != groupIds.cend(); ++groupId)
          {
               
               cout << "id groupe :" << *groupId << endl;

               if (*groupId == id && it->getTiming().intersect(timing))
               {
                cout << "Conflit détecté pour le groupe " << id << " avec l'horaire donné." << endl;
                return false;
               }
          }
     }

    return true; 
}

void Timetable::deleteCourseById(int code)
{
   for (auto it = courses.begin(); it != courses.end(); ++it)
     {
          if (it->getCode() == code)
          {
               courses.erase(it);
               return;
          }
     }
     throw std::out_of_range("Identificant non trouvé");
}


Timetable& Timetable::getInstance()
{
     return instance;
}


set<Classroom> Timetable::getClassrooms() const
{
     return classrooms;
}

set<Professor> Timetable::getProfessors() const
{
     return professors;
}

set<Group> Timetable::getGroups() const
{
     return groups;
} 
list<Course> Timetable::getCourses()  const
{
     return courses;
} 

void Timetable::save(const string& timetableName)
{
     int id = Schedulable::currentId;
     int code = Event::currentCode;

     string NomFichier;
     NomFichier = timetableName + "_config.dat";
     ofstream fichier(NomFichier, ios::binary);
     if (!fichier)
     {
          std::cerr << "Erreur d'ouverture du fichier...\n";
          return;
     }
     fichier.write((char*)&id, sizeof(int));
     fichier.write((char*)&code, sizeof(int));
     fichier.flush();
     fichier.close();

     cout  << "currentId : " << id << endl;
     cout  << "currentCode : " << code << endl;

     NomFichier = timetableName + "_professors.xml";
     XmlFileSerializer<Professor> professorSerializer(NomFichier,XmlFileSerializer<Professor>::WRITE,"_professors");
     for (auto it = professors.cbegin(); it != professors.cend(); ++it)
     {
       professorSerializer.write(*it);
     }

     NomFichier = timetableName + "_groups.xml";
     XmlFileSerializer<Group> groupSerializer(NomFichier,XmlFileSerializer<Group>::WRITE,"_groups");
     for (auto it = groups.cbegin(); it != groups.cend(); ++it)
     {
       groupSerializer.write(*it);
     }

     NomFichier = timetableName + "_classrooms.xml";
     XmlFileSerializer<Classroom> classroomSerializer(NomFichier,XmlFileSerializer<Classroom>::WRITE,"_classrooms");
     for (auto it = classrooms.cbegin(); it != classrooms.cend(); ++it)
     {
       classroomSerializer.write(*it);
     }

     NomFichier = timetableName + "_courses.xml";
     XmlFileSerializer<Course> courseSerializer(NomFichier,XmlFileSerializer<Course>::WRITE,"_courses");
     for (auto it = courses.begin(); it != courses.end(); it++)
     {
          courseSerializer.write(*it);
               
     }
     
}

void Timetable::load(const string& timetableName)
{
     bool end;
     string fichierConfig = timetableName + "_config.dat";
     string fichierProfessors = timetableName + "_professors.xml";
     string fichierGroups = timetableName + "_groups.xml";
     string fichierClassrooms= timetableName + "_classrooms.xml";
     string fichierCourses = timetableName + "_courses.xml";
     ifstream fichier(fichierConfig, ios::binary);
     if (!fichier)
     {    
          std::cerr << "Erreur d'ouverture du fichier...\n";
          return;
     }
     fichier.read((char*)&Schedulable::currentId, sizeof(int));
     fichier.read((char*)&Event::currentCode, sizeof(int));

     cout  << "currentId : " << Schedulable::currentId << endl;
     cout  << "currentCode : " << Event::currentCode << endl;

     classrooms.clear();
     professors.clear();
     groups.clear();
     courses.clear();
     XmlFileSerializer<Professor> professorSerializer(fichierProfessors,XmlFileSerializer<Professor>::READ);
     cout << "Debut de lecture..." << endl;

     end = false;
     while(!end)
     {
          try
          {
               professors.insert(professorSerializer.read());
          }catch(const XmlFileSerializerException& e){
               if (e.getCode() == XmlFileSerializerException::END_OF_FILE)
               { 
                    end = true;
                    cout << "Fin de fichier atteinte." << endl;
               }
               else
               {
                    cout << "Erreur : " << e.getMessage() << " (code = " << e.getCode() << ")" << endl;
               }
          }

     }
     cout << "Fin de lecture." << endl;

     XmlFileSerializer<Group> groupSerializer(fichierGroups,XmlFileSerializer<Group>::READ,"_groups");
     cout << "Debut de lecture..." << endl;

     end = false;
     while(!end)
     {
          try
          {
               groups.insert(groupSerializer.read());
          }catch(const XmlFileSerializerException& e){
               if (e.getCode() == XmlFileSerializerException::END_OF_FILE)
               { 
                    end = true;
                    cout << "Fin de fichier atteinte." << endl;
               }
               else
               {
                    cout << "Erreur : " << e.getMessage() << " (code = " << e.getCode() << ")" << endl;
               }
          }

     }
     cout << "Fin de lecture." << endl;
    
     XmlFileSerializer<Classroom> classroomSerializer(fichierClassrooms,XmlFileSerializer<Classroom>::READ,"_classrooms");
     cout << "Debut de lecture..." << endl;

     end = false;
     while(!end)
     {
          try
          {
               classrooms.insert(classroomSerializer.read());
          }catch(const XmlFileSerializerException& e){
               if (e.getCode() == XmlFileSerializerException::END_OF_FILE)
               { 
                    end = true;
                    cout << "Fin de fichier atteinte." << endl;
               }
               else
               {
                    cout << "Erreur : " << e.getMessage() << " (code = " << e.getCode() << ")" << endl;
               }
          }

     }
     cout << "Fin de lecture." << endl;
    
     XmlFileSerializer<Course> courseSerializer(fichierCourses,XmlFileSerializer<Course>::READ,"_courses");
     cout << "Debut de lecture..." << endl;

     end = false;
     while(!end)
     {
          try
          {
               courses.push_back(courseSerializer.read());
               
          }catch(const XmlFileSerializerException& e){
               if (e.getCode() == XmlFileSerializerException::END_OF_FILE)
               { 
                    end = true;
                    cout << "Fin de fichier atteinte." << endl;
               }
               else
               {
                    cout << "Erreur : " << e.getMessage() << " (code = " << e.getCode() << ")" << endl;
               }
          }

     }
     cout << "Fin de lecture." << endl;

} 


void Timetable::schedule(Course& c, const Timing& t)
{
     cout << "isProfessorAvailable" << endl;
     if(!isProfessorAvailable(c.getProfessorId(), t))
          throw TimingException("---professeur pas disponible---", TimingException::NO_TIMING);
     cout << "isClassroomAvailable" << endl;

     if(!isClassroomAvailable(c.getClassroomId(), t))
          throw TimingException("---local pas disponible---", TimingException::NO_TIMING);
     cout << "isGroupAvailable" << endl;

     for (auto groupId : c.getGroupsIds())
     {
          if (!isGroupAvailable(groupId, t))
          {
               throw TimingException("---groupe pas disponible---", TimingException::NO_TIMING);
          }
     }
     c.setCode(Event::currentCode);
     Event::currentCode++;
     cout << "currentCode : " << Event::currentCode << endl;

     c.setTiming(t);

     courses.push_back(c);
     cout << "ajout course fait "<< endl;
}

string Timetable::tuple(const Course& c)
{
     cout << "entre dans la boucle de courses "<< endl;
     for(auto it = courses.cbegin(); it != courses.cend(); ++it)
     {
          if (it->getCode() == c.getCode())
          {      
               cout << "a trouve le cours avec le code correspondant "<< endl;

               string tmp;

               tmp += to_string(it->getCode()) + ";";

               tmp += it->getTiming().getDay() + ";";

               tmp += it->getTiming().getStart().toString()  + ";";

               tmp += it->getTiming().getDuration().toString()  + ";";

               tmp += findClassroomById(c.getClassroomId()).getName() + ";";

               tmp += string(it->getTitle()) + ";";

               tmp += findProfessorById(c.getProfessorId()).toString() + ";";

          
               for (int groupId : c.getGroupsIds())
               {
                    tmp += findGroupById(groupId).toString()+ " ";      
               }
              

              return tmp;
          }
 
          
     }   
     throw std::out_of_range("Objet course non trouvé");

     

}
