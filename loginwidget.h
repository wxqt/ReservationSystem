#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H
#include "adminwidget.h"
#include "studentwidget.h"
#include "teacherwidget.h"

#include <QWidget>
#include <QObject>
#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QDir>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QVBoxLayout>

class LoginWidget : public QWidget
{
    Q_OBJECT
public:
    LoginWidget(QWidget *parent = nullptr);
    ~LoginWidget();

signals:

public slots:
    // 登录和退出槽
    void on_btnLogin_Clicked();
    void on_btnClose_Clicked();

    // 管理员 老师 学生 界面退出按钮信号的槽
    void on_admin_btnCancel_Clicked();
    void on_student_btnClose_Clicked();
    void on_teacher_btnClose_Clicked();

private:

    void createWidget();
    void createLayout();

    QLabel *labTitle;

    QLabel *labName;
    QLabel *labPasswd;
    QLabel *labSelect;

    QLineEdit *leName;
    QLineEdit *lePasswd;
    QComboBox *cbxSelect;

    QPushButton *btnLogin;
    QPushButton *btnClose;

    QHBoxLayout *titleLayout;
    QGridLayout *inputLayout;
    QHBoxLayout *btnLayuot;
    QVBoxLayout *mainLayout;

    // 学生 教师 机房 的对象
    AdminWidget admin;
    StudentWidget student;
    TeacherWidget teacher;
};

#endif // LOGINWIDGET_H
