#include "teacherwidget.h"
#include <QDebug>

TeacherWidget::TeacherWidget(QWidget *parent) : QWidget(parent)
{
    this->setWindowTitle(tr("教师"));
    this->resize(800, 450);

    createWidget();
    createLayout();

    readReseverFile();
}

// 通过审核
void TeacherWidget::on_Pass_Btn_Clicked()
{
    QStringList strList;

    for (int i = 0; i < 4; i++)   // 4为"\t"后文本个数
    {
        //将列表视图中当前行每隔一个"\t"的内容加入字符串列表
        strList << entireListWgt->item(entireListWgt->currentRow())->text().split("\t").at(i);
    }
    //删除列表视图当前行的项
    entireListWgt->takeItem(entireListWgt->currentRow());

    QString str;

    for (int i = 0; i < strList.count(); i++)
    {
        //将字符串列表中的内容分别写入到字符串中 并加上"\t"
        str += strList[i] + "\t";
    }
    str.append("审核通过");     //字符串再加上最后一项内容

    //列表视图添加一个项
    entireListWgt->addItem(str);
}

// 驳回审核 代码同上
void TeacherWidget::on_Reject_Btn_Clicked()
{
//    QString str = entireListWgt->item(entireListWgt->currentRow())->text();
    QStringList strList;

    for (int i = 0; i < 4; i++)
    {
        strList << entireListWgt->item(entireListWgt->currentRow())->text().split("\t").at(i);
    }
    entireListWgt->takeItem(entireListWgt->currentRow());

    QString str;

    for (int i = 0; i < strList.count(); i++)
    {
        str += strList[i] + "\t";
    }
    str.append("审核未通过");

    entireListWgt->addItem(str);
}

// 列表视图中的内容保存到文件
void TeacherWidget::on_Save_Btn_Clicked()
{
    QFile saveFile("./data/reserve.txt");
    saveFile.open(QIODevice::WriteOnly | QIODevice::Text);

    QTextStream out(&saveFile);

    for (int i = 0; i < entireListWgt->count(); i++)
    {
        out << entireListWgt->item(i)->text() << "\n";
    }

    saveFile.close();
    this->close();
    emit close_Btn_Clicked();
}

void TeacherWidget::on_Close_Btn_Clicked()
{
    this->close();
    emit close_Btn_Clicked();
}

void TeacherWidget::readReseverFile()
{
    entireListWgt->clear();

    QFile reseverFile("./data/reserve.txt");
    if (!reseverFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QTextStream in(&reseverFile);
    while (!in.atEnd()) {
        entireListWgt->addItem(in.readLine());
    }

    reseverFile.close();
}

void TeacherWidget::getUserPasswd(const QString str)
{
    userStr = str;
}

void TeacherWidget::createWidget()
{
    entireListWgt = new QListWidget;

    passBtn = new QPushButton(tr("通过"));
    connect(passBtn, &QPushButton::clicked, this, &TeacherWidget::on_Pass_Btn_Clicked);

    rejectBtn = new QPushButton(tr("驳回"));
    connect(rejectBtn, &QPushButton::clicked, this, &TeacherWidget::on_Reject_Btn_Clicked);

    saveBtn = new QPushButton(tr("保存"));
    connect(saveBtn, &QPushButton::clicked, this, &TeacherWidget::on_Save_Btn_Clicked);

    closeBtn = new QPushButton(tr("退出"));
    connect(closeBtn, &QPushButton::clicked, this, &TeacherWidget::on_Close_Btn_Clicked);
}

void TeacherWidget::createLayout()
{
    QHBoxLayout *topLay = new QHBoxLayout;
    topLay->addWidget(entireListWgt, 1);

    teacherGbx = new QGroupBox(tr("全部预约"));
    teacherGbx->setLayout(topLay);

    QHBoxLayout *bottomLay = new QHBoxLayout;
    bottomLay->addWidget(passBtn, 1);
    bottomLay->addStretch(1);
    bottomLay->addWidget(rejectBtn, 1);
    bottomLay->addStretch(5);
    bottomLay->addWidget(saveBtn, 1);
    bottomLay->addStretch(1);
    bottomLay->addWidget(closeBtn, 1);

    QVBoxLayout *mainLay = new QVBoxLayout(this);
    mainLay->addWidget(teacherGbx, 1);
    mainLay->addSpacing(20);
    mainLay->addLayout(bottomLay, 1);
}
