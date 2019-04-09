#ifndef TEACHERWIDGET_H
#define TEACHERWIDGET_H

#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QStringList>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>

class TeacherWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TeacherWidget(QWidget *parent = nullptr);

signals:
    void close_Btn_Clicked();

public slots:
    void on_Pass_Btn_Clicked();
    void on_Reject_Btn_Clicked();
    void on_Save_Btn_Clicked();
    void on_Close_Btn_Clicked();

public:
    void readReseverFile();                 //读取文件
    void getUserPasswd(const QString str);  //获取登录人信息

private:
    void createWidget();
    void createLayout();

    QString userStr;

    QListWidget *entireListWgt;

    QPushButton *passBtn;
    QPushButton *rejectBtn;
    QPushButton *saveBtn;
    QPushButton *closeBtn;

    QGroupBox *teacherGbx;
};

#endif // TEACHERWIDGET_H
