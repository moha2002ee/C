#ifndef APPLICHORAIREWINDOW_H
#define APPLICHORAIREWINDOW_H

#include <QMainWindow>
#include <string>
#include <list>
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class ApplicHoraireWindow; }
QT_END_NAMESPACE

class ApplicHoraireWindow : public QMainWindow
{
    Q_OBJECT

public:
    ApplicHoraireWindow(QWidget *parent = nullptr);
    ~ApplicHoraireWindow();

    void addTupleTableProfessors(const string& tuple);
    void clearTableProfessors();
    int  getIndexProfessorSelection() const;

    void addTupleTableGroups(const string& tuple);
    void clearTableGroups();
    list<int> getIndexesGroupsSelection() const;

    void addTupleTableClassrooms(const string& tuple);
    void clearTableClassrooms();
    int  getIndexClassroomSelection() const;

    void addTupleTableCourses(const string& tuple);
    void clearTableCourses();

    string getProfessorLastName() const;
    void   setProfessorLastName(const string& lastName);
    string getProfessorFirstName() const;
    void   setProfessorFirstName(const string& firstName);

    string getGroupName() const;
    void   clearGroupName();

    string getClassroomName() const;
    void   setClassroomName(const string& name);

    string getDaySelection() const;
    int    getHourStart() const;
    void   clearHourStart();
    int    getMinuteStart() const;
    void   clearMinuteStart();
    int    getDuration() const;
    void   clearDuration();
    string getTitle() const;
    void   setTitle(const string& title);

    bool isDayChecked() const;
    void setDayChecked(bool b);
    bool isProfessorChecked() const;
    void setProfessorChecked(bool b);
    bool isGroupChecked() const;
    void setGroupChecked(bool b);
    bool isClassroomChecked() const;
    void setClassroomChecked(bool b);

    void   dialogMessage(const string& title,const string& message);
    void   dialogError(const string& title,const string& message);
    string dialogInputText(const string& title,const string& question);
    int    dialogInputInt(const string& title,const string& question);
    string dialogInputFileForLoad(const string& question);
    string dialogInputFileForSave(const string& question);

private slots:
    void on_pushButtonAjouterProfesseur_clicked();
    void on_pushButtonAjouterGroupe_clicked();
    void on_pushButtonAjouterLocal_clicked();
    void on_pushButtonSupprimerProfesseur_clicked();
    void on_pushButtonSupprimerGroupe_clicked();
    void on_pushButtonSupprimerLocal_clicked();
    void on_pushButtonPlanifier_clicked();
    void on_pushButtonSelectionner_clicked();
    void on_actionQuitter_triggered();
    void on_actionOuvrir_triggered();
    void on_actionNouveau_triggered();
    void on_actionEnregistrer_triggered();
    void on_actionSupprimerProfesseur_triggered();
    void on_actionSupprimerGroupe_triggered();
    void on_actionSupprimerLocal_triggered();
    void on_actionSupprimerCours_triggered();
    void on_actionImporterProfesseurs_triggered();
    void on_actionImporterGroupes_triggered();
    void on_actionImporterLocaux_triggered();
    void on_actionExporterProfesseur_triggered();
    void on_actionExporterGroupe_triggered();
    void on_actionExporterLocal_triggered();

private:
    Ui::ApplicHoraireWindow *ui;
};
#endif // APPLICHORAIREWINDOW_H
