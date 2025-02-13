#include <string>
#include <sstream>
#include <ostream>  
#include "Schedulable.h"

using namespace std;

class Group : public Schedulable
{
    friend ostream& operator<<(ostream& o, const Group& g);

private:
    string name;

public:
    Group();
    Group(int i, string n);
    Group(const Group &g) = default;

    ~Group() = default;

    void setName(string n);

    string getName() const;

    string toString() const override;
    string tuple() const override;

    Group &operator=(const Group &g);
};
