#include "adminwidget.h"
#include <QDebug>

AdminWidget::AdminWidget(QWidget *parent) : QWidget(parent)
{
    this->setWindowTitle(tr("管理员"));
    createWidget();
    createLayout();
}

void AdminWidget::on_btnAddStu_Clicked()
{
    //添加学生列表视图项
    QString str = leStuName->text() + " " + leStuPasswd->text();
    listStu->addItem(str);
    leStuName->clear();
    leStuPasswd->clear();
}

void AdminWidget::on_btnDelStu_Clicked()
{
    //删除当前学生列表视图选中行
    listStu->takeItem(listStu->currentRow());
}

void AdminWidget::on_btnAddTea_Clicked()
{
    //添加教师列表视图项
    QString str = leTeaName->text() + " " + leTeaPasswd->text();
    listTea->addItem(str);
    leTeaName->clear();
    leTeaPasswd->clear();
}

void AdminWidget::on_btnDelTea_Clicked()
{
    //删除当前教师列表视图选中行
    listTea->takeItem(listTea->currentRow());
}

void AdminWidget::on_btnAddEng_Clicked()
{
    //添加机房列表视图项
    QString str = leEngName->text() + " -- " + leEngNum->text() + "人";
    listEng->addItem(str);
    leEngNum->clear();
    leEngName->clear();
}

void AdminWidget::on_btnDelEng_Clicked()
{
    //删除当前机房列表视图选中行
    listEng->takeItem(listEng->currentRow());
}

void AdminWidget::on_btnSave_Clicked()
{
    //保存到文件并退出界面
    saveFile();
    this->close();
    emit btnCancel_Clicked();
}

void AdminWidget::on_btnCancel_Clicked()
{
    //退出不保存
    this->close();
    emit btnCancel_Clicked();
}

void AdminWidget::saveFile()
{
    // 学生文件
    QFile stuFile("./data/student.txt");
    stuFile.resize("student.txt", 0);
    if (!stuFile.open(QIODevice::ReadWrite | QIODevice::Text))
        return;

    QTextStream stuStream(&stuFile);

    for(int i = 0; i < listStu->count(); i++)
    {
        QString line = listStu->item(i)->text();
        stuStream << line << "\n";
    }

    stuFile.close();

    // 教师文件
    QFile teaFile("./data/teacher.txt");
    teaFile.resize("./data/teacher.txt", 0);
    if (!teaFile.open(QIODevice::ReadWrite | QIODevice::Text))
        return;
    QTextStream teaStream(&teaFile);

    for(int i = 0; i < listTea->count(); i++)
    {
        QString line = listTea->item(i)->text();
        teaStream << line << "\n";
    }
    teaFile.close();

    // 机房文件
    QFile engFile("./data/engine.txt");
    engFile.resize("./data/engine.txt", 0);
    if (!engFile.open(QIODevice::ReadWrite | QIODevice::Text))
        return;
    QTextStream engStream(&engFile);

    for(int i = 0; i < listEng->count(); i++)
    {
        QString line = listEng->item(i)->text();
        engStream << line << "\n";
    }
    engFile.close();
}

void AdminWidget::openFile()
{
    // 学生文件
    QFile stuFile("./data/student.txt");
    if (!stuFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QTextStream stuStream(&stuFile);
    while (!stuStream.atEnd()) {
        listStu->addItem(stuStream.readLine());
    }
    stuFile.close();

    // 教师文件
    QFile teaFile("./data/teacher.txt");
    if (!teaFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QTextStream teaStream(&teaFile);
    while (!teaStream.atEnd()) {
        listTea->addItem(teaStream.readLine());
    }
    teaFile.close();

    // 机房文件
    QFile engFile("./data/engine.txt");
    if (!engFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QTextStream engStream(&engFile);
    while (!engStream.atEnd()) {
        listEng->addItem(engStream.readLine());
    }
    engFile.close();
}

void AdminWidget::createWidget()
{
    labStuName = new QLabel(tr("姓名: "));
    labStuPasswd = new QLabel(tr("密码: "));
    labTeaName = new QLabel(tr("姓名: "));
    labTeaPasswd = new QLabel(tr("密码: "));
    labEngName = new QLabel(tr("机房: "));
    labEngNum = new QLabel(tr("人数: "));

    leStuName = new QLineEdit;
    leStuPasswd = new QLineEdit;
    leTeaName = new QLineEdit;
    leTeaPasswd = new QLineEdit;
    leEngName = new QLineEdit;
    leEngNum = new QLineEdit;

    btnAddStu = new QPushButton(tr("添加"));
    connect(btnAddStu, &QPushButton::clicked, this, &AdminWidget::on_btnAddStu_Clicked);

    btnDelStu = new QPushButton(tr("删除"));
    connect(btnDelStu, &QPushButton::clicked, this, &AdminWidget::on_btnDelStu_Clicked);

    btnAddTea = new QPushButton(tr("添加"));
    connect(btnAddTea, &QPushButton::clicked, this, &AdminWidget::on_btnAddTea_Clicked);

    btnDelTea = new QPushButton(tr("删除"));
    connect(btnDelTea, &QPushButton::clicked, this, &AdminWidget::on_btnDelTea_Clicked);

    btnAddEng = new QPushButton(tr("添加"));
    connect(btnAddEng, &QPushButton::clicked, this, &AdminWidget::on_btnAddEng_Clicked);

    btnDelEng = new QPushButton(tr("删除"));
    connect(btnDelEng, &QPushButton::clicked, this, &AdminWidget::on_btnDelEng_Clicked);

    btnSave = new QPushButton(tr("保存"));
    connect(btnSave, &QPushButton::clicked, this, &AdminWidget::on_btnSave_Clicked);

    btnCancel = new QPushButton(tr("返回"));
    connect(btnCancel, &QPushButton::clicked, this, &AdminWidget::on_btnCancel_Clicked);

    listStu = new QListWidget;
    listTea = new QListWidget;
    listEng = new QListWidget;
}

void AdminWidget::createLayout()
{
    // 添加学生布局
    stuInputLay = new QGridLayout;
    stuInputLay->addWidget(labStuName, 0, 0);
    stuInputLay->addWidget(leStuName, 0, 1);
    stuInputLay->addWidget(labStuPasswd, 1, 0);
    stuInputLay->addWidget(leStuPasswd, 1, 1);

    stuBtnLay = new QHBoxLayout;
    stuBtnLay->addStretch(1);
    stuBtnLay->addWidget(btnAddStu);
    stuBtnLay->addStretch(1);
    stuBtnLay->addWidget(btnDelStu);
    stuBtnLay->addStretch(1);

    stuMainLay = new QVBoxLayout;
    stuMainLay->addLayout(stuInputLay);
    stuMainLay->addLayout(stuBtnLay);
    stuMainLay->addWidget(listStu);

    studentBox = new QGroupBox(tr("学生"));
    studentBox->setLayout(stuMainLay);

    // 添加老师布局
    teaInputLay = new QGridLayout;
    teaInputLay->addWidget(labTeaName, 0, 0);
    teaInputLay->addWidget(leTeaName, 0, 1);
    teaInputLay->addWidget(labTeaPasswd, 1, 0);
    teaInputLay->addWidget(leTeaPasswd, 1, 1);

    teaBtnLay = new QHBoxLayout;
    teaBtnLay->addStretch(1);
    teaBtnLay->addWidget(btnAddTea);
    teaBtnLay->addStretch(1);
    teaBtnLay->addWidget(btnDelTea);
    teaBtnLay->addStretch(1);

    teaMainLay = new QVBoxLayout;
    teaMainLay->addLayout(teaInputLay);
    teaMainLay->addLayout(teaBtnLay);
    teaMainLay->addWidget(listTea);

    teacherBox = new QGroupBox(tr("教师"));
    teacherBox->setLayout(teaMainLay);

    // 添加机房布局
    engInputLay = new QGridLayout;
    engInputLay->addWidget(labEngName, 0, 0);
    engInputLay->addWidget(leEngName, 0, 1);
    engInputLay->addWidget(labEngNum, 1, 0);
    engInputLay->addWidget(leEngNum, 1, 1);

    engBtnLay = new QHBoxLayout;
    engBtnLay->addStretch(1);
    engBtnLay->addWidget(btnAddEng);
    engBtnLay->addStretch(1);
    engBtnLay->addWidget(btnDelEng);
    engBtnLay->addStretch(1);

    engMainLay = new QVBoxLayout;
    engMainLay->addLayout(engInputLay);
    engMainLay->addLayout(engBtnLay);
    engMainLay->addWidget(listEng);

    engineRoomBox = new QGroupBox(tr("机房"));
    engineRoomBox->setLayout(engMainLay);

    bottomLay = new QHBoxLayout;
    bottomLay->addStretch(6);
    bottomLay->addWidget(btnSave, 1);
    bottomLay->addStretch(1);
    bottomLay->addWidget(btnCancel, 1);
    bottomLay->addStretch(1);


    // 主布局
    mainLay = new QHBoxLayout;
    mainLay->addWidget(studentBox);
    mainLay->addWidget(teacherBox);
    mainLay->addWidget(engineRoomBox);

    mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(mainLay);
    mainLayout->addLayout(bottomLay);
}


