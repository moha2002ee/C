#include "Time.h"
#include "iomanip"


namespace planning
{

  // ***** Constructeurs *****
  Time::Time() noexcept
  {
    #ifdef DEBUG
    cout << "<<< Time : Constructeur par defaut >>>" << endl;
    #endif
    setHour(0);
    setMinute(0);
  }
  Time::Time(int h, int m)
  {
    #ifdef DEBUG
    cout << "<<< Time : Constructeur d'initialisation >>>" << endl;
    #endif
    setHour(h);
    setMinute(m);
  }
  Time::Time(int m)
  {
    int hourTemp = m / 60;
    int minuteTemp = m % 60;
    setHour(hourTemp);
    setMinute(minuteTemp);
  }
  Time::Time(const Time& e) noexcept
  {
    #ifdef DEBUG
    cout << "<<< Time : Constructeur de copie >>>" << endl;
    #endif
    setHour(e.hour);
    setMinute(e.minute);
  }

  // ***** Destructeur *****
  Time::~Time()
  {
    #ifdef DEBUG
    cout << "<<< Time : Destructeur >>>" << endl;
    #endif
  }

  // ***** getXXX / setXXX *****
  int Time::getHour() const noexcept{ return hour;}
  int Time::getMinute() const noexcept{ return minute;} 
  void Time::setHour(int h)
  {
    if(h < 0 || h > 24) throw TimeException("---Heure saisie invalide---", TimeException::INVALID_HOUR);
    hour = h;
  }
  void Time::setMinute(int m)
  { 
    if(m < 0 || m > 59) throw TimeException("---Minute saisie invalide---", TimeException::INVALID_MINUTE);
    minute = m;

  }

  // ***** Autres methodes de l'interface *****
  void Time::display() const noexcept
  {
    cout << "Time/Duree : " << setfill('0') << setw(2) << hour << "h" 
    << setfill('0') << setw(2)<< minute << endl;
  }

  string Time::toString() const noexcept{
    ostringstream oss;
    oss << setfill('0') << setw(2) << hour << "h" 
    << setfill('0') << setw(2)<< minute;
    return oss.str();
  }
  Time& Time::operator=(const Time& t) noexcept
  {
    setHour(t.hour);
    setMinute(t.minute);

    return(*this);
  }
  Time Time::operator+(int m)
  {
    Time temp(*this);  
    temp.minute = (temp.hour * 60) + temp.minute;
    temp.minute = temp.minute + m;
    if(temp.minute > 24*60 || temp.minute < 0){throw TimeException("---Erreur OVERFLOW---", TimeException::OVERFLOW);}
    Time tp(temp.minute);
    return tp;
  }
  Time operator+(int m, const Time& t)
  {
    Time temp(t);
    return temp + m;
  }
  Time Time::operator+(const Time& t2)
  {
    Time temp(*this);
    int m = (t2.hour * 60) + t2.minute;
    return temp + m;
  }
  Time Time::operator-(int m)
  {
    Time temp(*this);  
    temp.minute = (temp.hour * 60) + temp.minute;
    temp.minute = temp.minute - m;
    if(temp.minute > 24*60 || temp.minute < 0){throw TimeException("---Erreur OVERFLOW---", TimeException::OVERFLOW);}
    Time tp(temp.minute);
    return tp;
  }
  Time operator-(int m, const Time& t)
  {
    Time temp(t);
    Time tp(m / 60, m % 60);

    return tp - temp;
  }
  Time Time::operator-(const Time& t2)
  {
    Time temp(*this);
    
    int m = (t2.hour * 60) + t2.minute;
    return temp - m;

  }
  int Time::operator<(const Time& t) noexcept{ 
    return compT(t) == -1;
  }
  int Time::operator>(const Time& t) noexcept{
    return compT(t) == 1;
  }
  int Time::operator==(const Time& t) noexcept{
    return compT(t) == 0;
  }
  int Time::compT(const Time& t) noexcept
  {
    if (hour < t.hour) return -1;
    if (hour > t.hour) return 1;
    if (minute < t.minute) return -1;
    if (minute > t.minute) return 1;
    return 0; 
  }
  ostream& operator<<(ostream& o, const Time& t) noexcept
  {
    o << "<Time>" << endl;
    o << "<hour>" << endl;
    o << t.hour << endl;
    o << "</hour>" << endl;
    o << "<minute>" << endl;
    o << t.minute << endl;
    o << "</minute>" << endl;
    o << "</Time>";
    return o;
  }
  istream& operator>>(istream& i, Time& t)
  {
    string sHour, sMinute, tag;
    getline(i, tag);
    getline(i, tag);
    getline(i, sHour);
    getline(i, tag);
    getline(i, tag);
    getline(i, sMinute);
    getline(i, tag);
    getline(i, tag);

    t.setHour(stoi(sHour));
    t.setMinute(stoi(sMinute));
    return i;
  }
  Time Time::operator++()
  {
    (*this) = (*this) + 30;
    return (*this);
  }
  Time Time::operator++(int)
  {
    Time temp(*this);
    (*this) = (*this) + 30;
    return temp;
  }
  Time Time::operator--()
  {
    (*this) = (*this) - 30;
    return (*this);
  }
  Time Time::operator--(int)
  {
    Time temp(*this);
    (*this) = (*this) - 30;
    return temp;
  }

}