#include "loginwidget.h"
#include <QDebug>

LoginWidget::LoginWidget(QWidget *parent) : QWidget(parent)
{
    this->resize(400, 300);

    createWidget();
    createLayout();

    //接收来自 管理员 教师 学生 界面的退出信号
    connect(&admin, &AdminWidget::btnCancel_Clicked, this, &LoginWidget::on_admin_btnCancel_Clicked);
    connect(&student, &StudentWidget::btn_Close_Clicked, this, &LoginWidget::on_student_btnClose_Clicked);
    connect(&teacher, &TeacherWidget::close_Btn_Clicked, this, &LoginWidget::on_teacher_btnClose_Clicked);
}

LoginWidget::~LoginWidget()
{

}

void LoginWidget::on_btnLogin_Clicked()
{
    //管理员登录
    if (cbxSelect->currentIndex() == 0)
    {
        if (leName->text() == "admin" && lePasswd->text() == "admin")
        {
            this->close();
            admin.openFile();   //管理员界面读取文件
            admin.show();
            lePasswd->clear();
        }
        else {
            QMessageBox::warning(this, tr("Warning"), tr("用户名密码错误!"));
        }
    }

    //教师登录
    else if (cbxSelect->currentIndex() == 1)
    {
        QFile userFile("./data/teacher.txt");
        if (!userFile.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QMessageBox::warning(this, tr("Warning"), tr("没有创建用户!"));
            return;
        }

        QTextStream in(&userFile);
        while (!in.atEnd())
        {
            QString line = in.readLine();

            if (leName->text() != line.split(" ").at(0) && lePasswd->text() != line.split(" ").at(1))
                continue;

            if (leName->text() == line.split(" ").at(0) && lePasswd->text() == line.split(" ").at(1))
            {
                this->close();
                teacher.getUserPasswd(line.split(" ").at(0));   //将用户名传给老师对象
                teacher.readReseverFile();      //教师对象读取预约文件
                teacher.show();
                lePasswd->clear();

                userFile.close();
                return;
            }
        }

        userFile.close();
        QMessageBox::warning(this, tr("Warning"), tr("用户名密码错误!"));
    }

    //学生登录
    else if (cbxSelect->currentIndex() == 2)
    {
        QFile userFile("./data/student.txt");
        if (!userFile.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QMessageBox::warning(this, tr("Warning"), tr("没有创建用户!"));
            return;
        }

        QTextStream in(&userFile);
        while (!in.atEnd())
        {
            QString line = in.readLine();

            if (leName->text() != line.split(" ").at(0) && lePasswd->text() != line.split(" ").at(1))
                continue;

            if (leName->text() == line.split(" ").at(0) && lePasswd->text() == line.split(" ").at(1))
            {
                this->close();
                student.getUserPasswd(line.split(" ").at(0));
                student.readEngine();   //学生对象读取机房文件
                student.readFile();     //读取预约文件
                student.show();
                lePasswd->clear();

                userFile.close();
                return;
            }
        }

        userFile.close();
        QMessageBox::warning(this, tr("Warning"), tr("用户名密码错误!"));
    }
}

void LoginWidget::on_btnClose_Clicked()
{
    this->close();
}

void LoginWidget::on_admin_btnCancel_Clicked()
{
    this->show();
}

void LoginWidget::on_student_btnClose_Clicked()
{
    this->show();
}

void LoginWidget::on_teacher_btnClose_Clicked()
{
    this->show();
}

void LoginWidget::createWidget()
{
    QFont font;
    font.setPointSize(24);

    labTitle = new QLabel(tr("机房预约系统"));
    labTitle->setFont(font);

    labName = new QLabel(tr("用户名: "));
    labPasswd = new QLabel(tr("密码: "));
    labSelect = new QLabel(tr("帐户: "));

    leName = new QLineEdit;
    lePasswd = new QLineEdit;
    lePasswd->setEchoMode(QLineEdit::Password);

    cbxSelect = new QComboBox;
    cbxSelect->addItem(tr("管理员"));
    cbxSelect->addItem(tr("教师"));
    cbxSelect->addItem(tr("学生"));

    btnLogin = new QPushButton(tr("登录"));
    btnLogin->setDefault(true);
    btnLogin->setAutoDefault(true);
    connect(btnLogin, &QPushButton::clicked, this, &LoginWidget::on_btnLogin_Clicked);

    btnClose = new QPushButton(tr("退出"));
    connect(btnClose, &QPushButton::clicked, this, &LoginWidget::on_btnClose_Clicked);

    QDir dir;
    if (!dir.exists("./data"))
        {
            dir.mkpath("./data");
        }
}

void LoginWidget::createLayout()
{
    titleLayout = new QHBoxLayout;
    titleLayout->addStretch(1);
    titleLayout->addWidget(labTitle);
    titleLayout->addStretch(1);

    inputLayout = new QGridLayout;
    inputLayout->addWidget(labName, 0, 0);
    inputLayout->addWidget(leName, 0, 1);
    inputLayout->addWidget(labPasswd, 1, 0);
    inputLayout->addWidget(lePasswd, 1, 1);
    inputLayout->addWidget(labSelect, 2, 0);
    inputLayout->addWidget(cbxSelect, 2, 1);

    btnLayuot = new QHBoxLayout;
    btnLayuot->addStretch(1);
    btnLayuot->addWidget(btnLogin, 1);
    btnLayuot->addStretch(2);
    btnLayuot->addWidget(btnClose, 1);
    btnLayuot->addStretch(1);

    mainLayout = new QVBoxLayout(this);
    mainLayout->addStretch(1);
    mainLayout->addLayout(titleLayout);
    mainLayout->addStretch(1);
    mainLayout->addLayout(inputLayout, 1);
    mainLayout->addStretch(1);
    mainLayout->addLayout(btnLayuot, 1);
    mainLayout->addStretch(1);
}
