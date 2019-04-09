#ifndef STUDENTWIDGET_H
#define STUDENTWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QListWidget>
#include <QListWidgetItem>
#include <QStringList>
#include <QList>
#include <QFile>
#include <QTextStream>
#include <QGroupBox>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>

class StudentWidget : public QWidget
{
    Q_OBJECT
public:
    explicit StudentWidget(QWidget *parent = nullptr);

signals:
    void btn_Close_Clicked();       //退出信号给到主界面

public slots:

    void on_btnReserve_Clicked();   //增加预约
    void on_btnCancel_Clicked();    //取消预约
    void on_btnSave_Clicked();      //保存文件
    void on_btnClose_Clicked();     //退出界面

public:
    void getUserPasswd(const QString str);  //获取登录人信息
    void readEngine();      //获取机房信息
    void readFile();        //获取预约文件
    void saveFile();        //保存信息到文件

private:

    void createWidget();
    void createLayout();

    QString strUser;        //登录人信息

    QLabel *labEngine;
    QLabel *labWeek;
    QLabel *labPeriod;

    QComboBox *cbxEngine;
    QComboBox *cbxWeek;
    QComboBox *cbxPeriod;

    QStringList strListWeek;//星期列表

    QPushButton *btnReserve;
    QPushButton *btnCancel;
    QPushButton *btnSave;
    QPushButton *btnClose;

    QListWidget *listSelf;
    QListWidget *listEntire;

    QGroupBox *gbxSelf;
    QGroupBox *gbxEntire;
};

#endif // STUDENTWIDGET_H
