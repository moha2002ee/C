#include "Event.h"
#include "Timing.h"

namespace planning
{
    int Event::currentCode = 1;
    // ***** Constructeurs *****
    Event::Event()
    {
        #ifdef DEBUG
        cout << ">>> Event : constructeur par defaut <<<" << endl;
        #endif
        code = 0;
        title = nullptr;
        timing = nullptr;
        setTitle("---");

    }
    Event::Event(int c, const char* t)
    {
        #ifdef DEBUG
        cout << ">>> Event : constructeur d'initialisation <<<" << endl;
        #endif
        setCode(c);
        title = nullptr;
        timing = nullptr;
        setTitle(t);

        
    }
    Event::Event(const Event& e)
    {
        #ifdef DEBUG
        cout << ">>> Event : constructeur de copie <<<" << endl;
        #endif
        setCode(e.getCode());
        title = nullptr;
        timing = nullptr;
        setTitle(e.getTitle());
        setTiming(e.getTiming());

    }

    // ***** Destructeur *****
    Event::~Event()
    {
        #ifdef DEBUG
        cout << ">>> Event: destructeur <<<" << endl;
        #endif
        if (title) delete title;
        if (timing) delete timing;
    }

    // ***** getXXX / setXXX *****
    void Event::setCode(int c)
    {
        if(c < 1) return;
        code = c;
    }
    void Event::setTitle(const char* t)
    {
        if (t == nullptr) return;
        if (title) delete title;
        title = new char[strlen(t) + 1];
        strcpy(title, t);
    }
    void Event::setTiming(const Timing& tm)
    {
        if(timing) delete timing;
        timing = new Timing(tm);
    }

    int Event::getCode() const
    {
        return code;
    }
    const char* Event::getTitle() const
    {
        return title;
    }
    Timing Event::getTiming() const
    {
        if(timing == nullptr) throw TimingException("---Evenement non planifié---", TimingException::NO_TIMING);
        return *timing;
    }

    // ***** Autres methodes de l'interface *****
    void Event::display() const
    {
        cout << "Event (" << code << ") :" << title << endl;
        if (timing)
        {
            timing->display();
        }
        else
        {
            cout << "Timing non planifié" << endl;  
        }
        
    }
    string Event::toString() const
    {
        ostringstream oss;
        oss << code << ";" << title << ";";
        if (timing != nullptr)
        {
            oss << timing->toString();
        }
        else{oss << "Timing non planifié";}
        return oss.str();
    }
    Event& Event::operator=(const Event& e)
    {
     setCode(e.code);
     setTitle(e.title);

    return(*this);
    }
    ostream& operator<<(ostream& o, const Event& e)
    {
        o << "<Event>" << endl;
        o << "<code>" << endl;
        o << e.code << endl;
        o << "</code>" << endl;
        o << "<title>" << endl;
        o << e.title << endl;
        o << "</title>" << endl;

        if(e.timing != nullptr)
        {
            o << "<timing>" << endl;
            o << *(e.timing) << endl;
            o << "</timing>"<< endl;
        } 
        o << "</Event>";
        return o;


    }
    istream& operator>>(istream& i, Event& e)
    {

        string sCode, sTitle, tag;
        Timing tempTiming;
        getline(i, tag);
        getline(i, tag);
        getline(i, sCode);
        getline(i, tag);
        getline(i, tag);
        getline(i, sTitle);
        getline(i, tag);
        getline(i, tag);
        if(tag == "<timing>")
        {
            i >> tempTiming;
            e.setTiming(tempTiming);
            getline(i, tag);
            getline(i, tag);
        }
        
        e.setCode(stoi(sCode));
        e.setTitle(sTitle.c_str());

        
        
        return i;
    }
}

