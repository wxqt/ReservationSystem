#ifndef ADMINWIDGET_H
#define ADMINWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QListWidget>
#include <QListWidgetItem>
#include <QFile>
#include <QTextStream>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QGroupBox>

class AdminWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AdminWidget(QWidget *parent = nullptr);

signals:
    void btnCancel_Clicked();

public slots:
    void on_btnAddStu_Clicked();
    void on_btnDelStu_Clicked();
    void on_btnAddTea_Clicked();
    void on_btnDelTea_Clicked();
    void on_btnAddEng_Clicked();
    void on_btnDelEng_Clicked();

    void on_btnSave_Clicked();
    void on_btnCancel_Clicked();

public:
    void saveFile();
    void openFile();

private:

    void createWidget();
    void createLayout();

    QLabel *labStuName;
    QLabel *labStuPasswd;
    QLabel *labTeaName;
    QLabel *labTeaPasswd;
    QLabel *labEngName;
    QLabel *labEngNum;

    QLineEdit *leStuName;
    QLineEdit *leStuPasswd;
    QLineEdit *leTeaName;
    QLineEdit *leTeaPasswd;
    QLineEdit *leEngName;
    QLineEdit *leEngNum;

    QPushButton *btnAddStu;
    QPushButton *btnDelStu;
    QPushButton *btnAddTea;
    QPushButton *btnDelTea;
    QPushButton *btnAddEng;
    QPushButton *btnDelEng;

    QPushButton *btnSave;
    QPushButton *btnCancel;

    QListWidget *listStu;
    QListWidget *listTea;
    QListWidget *listEng;

    QGroupBox *studentBox;
    QGroupBox *teacherBox;
    QGroupBox *engineRoomBox;

    QGridLayout *stuInputLay;
    QHBoxLayout *stuBtnLay;
    QVBoxLayout *stuMainLay;

    QGridLayout *teaInputLay;
    QHBoxLayout *teaBtnLay;
    QVBoxLayout *teaMainLay;

    QGridLayout *engInputLay;
    QHBoxLayout *engBtnLay;
    QVBoxLayout *engMainLay;

    QHBoxLayout *bottomLay;
    QHBoxLayout *mainLay;
    QVBoxLayout *mainLayout;
};

#endif // ADMINWIDGET_H
