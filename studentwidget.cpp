#include "studentwidget.h"
#include <QDebug>

StudentWidget::StudentWidget(QWidget *parent) : QWidget(parent)
{
    this->setWindowTitle(tr("学生"));
    this->resize(800, 450);

    createWidget();
    createLayout();
}

void StudentWidget::on_btnReserve_Clicked()
{
    // 增加预约
    QString strEngine = cbxEngine->itemText(cbxEngine->currentIndex());
    QString strWeek = cbxWeek->itemText(cbxWeek->currentIndex());
    QString strDay = cbxPeriod->itemText(cbxPeriod->currentIndex());
    QString strStatus = "待审核...";

    QString strReserve = strWeek + "\t" + strDay + "\t" + strUser + "\t" + strEngine.split(" ").at(0) + "\t" + strStatus;

    listEntire->addItem(strReserve);
    listSelf->addItem(strReserve);
}

void StudentWidget::on_btnCancel_Clicked()
{
    // 删除本用户预约选中的行的项内容
    QList<QListWidgetItem *> list = listSelf->selectedItems();

    if(list.size() == 0)
        return;
    QListWidgetItem *item = list[0];
    listSelf->takeItem(listSelf->row(item));

    // 删除全部预约中本用户的内容
    for (int i = listEntire->count() - 1; i >= 0; i--)
    {
        if (listEntire->item(i)->text().split("\t").at(2) == strUser)
            listEntire->takeItem(i);
    }

    // 读出本用户剩下的项
    QStringList lastStrList;
    for (int i = 0; i < listSelf->count(); i++)
    {
        lastStrList << listSelf->item(i)->text();
    }

    // 本用户的内容重新添加到全部预约
    for (int i = 0; i < listSelf->count(); i++)
    {
        listEntire->addItem(listSelf->item(i)->text());
    }
}

void StudentWidget::on_btnSave_Clicked()
{
    saveFile();
    this->close();
    emit btn_Close_Clicked();
}

void StudentWidget::on_btnClose_Clicked()
{
    this->close();
    emit btn_Close_Clicked();
}

void StudentWidget::getUserPasswd(const QString str)
{
    strUser = str;
}

void StudentWidget::readEngine()
{
    cbxEngine->clear();
    QFile engineFile("./data/engine.txt");
    if (!engineFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QTextStream in(&engineFile);
    QStringList engList;
    while (!in.atEnd())
    {
        engList <<  in.readLine();
    }

    engineFile.close();
    cbxEngine->addItems(engList);
}

void StudentWidget::readFile()
{

    listEntire->clear();
    listSelf->clear();

    //读取文件 全部预约
    QFile resReadFile("./data/reserve.txt");
    if (!resReadFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QTextStream resReadStream(&resReadFile);
    while (!resReadStream.atEnd())
    {
        listEntire->addItem(resReadStream.readLine());
    }
    resReadFile.close();

    //读取文件 用户预约
    QFile resReadFile2("./data/reserve.txt");
    if (!resReadFile2.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QTextStream resReadStream2(&resReadFile2);
    while (!resReadStream2.atEnd())
    {
        QString line = resReadStream2.readLine();
        if (line.split("\t").at(2) == strUser)
        {
            listSelf->addItem(line);
        }
    }
    resReadFile2.close();
}

void StudentWidget::saveFile()
{
    QFile resSaveFile("./data/reserve.txt");
    resSaveFile.resize("./data/reserve.txt", 0);
    if (!resSaveFile.open(QIODevice::ReadWrite | QIODevice::Text))
        return;
    QTextStream out(&resSaveFile);

    for (int i = 0; i < listEntire->count(); i++)
    {
        QString line = listEntire->item(i)->text();
        out << line << "\n";
    }
    resSaveFile.close();
}

void StudentWidget::createWidget()
{
    strListWeek << "星期一" << "星期二" << "星期三"
                << "星期四" << "星期五";

    labEngine = new QLabel(tr("选择机房: "));
    labWeek = new QLabel(tr("选择星期: "));
    labPeriod = new QLabel(tr("选择时间: "));

    cbxEngine = new QComboBox;

    cbxWeek = new QComboBox;
    cbxWeek->addItems(strListWeek);

    cbxPeriod = new QComboBox;
    cbxPeriod->addItem("上午");
    cbxPeriod->addItem("下午");

    btnReserve = new QPushButton(tr("预约"));
    connect(btnReserve, &QPushButton::clicked, this, &StudentWidget::on_btnReserve_Clicked);

    btnCancel = new QPushButton(tr("取消"));
    connect(btnCancel, &QPushButton::clicked, this, &StudentWidget::on_btnCancel_Clicked);

    btnSave = new QPushButton(tr("保存"));
    connect(btnSave, &QPushButton::clicked, this, &StudentWidget::on_btnSave_Clicked);

    btnClose = new QPushButton(tr("退出"));
    connect(btnClose, &QPushButton::clicked, this, &StudentWidget::on_btnClose_Clicked);

    listSelf = new QListWidget;
    listEntire = new QListWidget;

    gbxSelf = new QGroupBox(tr("我的预约"));
    gbxEntire = new QGroupBox(tr("全部预约"));
}

void StudentWidget::createLayout()
{
    QGridLayout *leftTopLay = new QGridLayout;
    leftTopLay->addWidget(labEngine, 0, 0);
    leftTopLay->addWidget(cbxEngine, 1, 0);
    leftTopLay->addWidget(labWeek, 2, 0);
    leftTopLay->addWidget(cbxWeek, 3, 0);
    leftTopLay->addWidget(labPeriod, 4, 0);
    leftTopLay->addWidget(cbxPeriod, 5, 0);

    QHBoxLayout *btnTopLay = new QHBoxLayout;
    btnTopLay->addWidget(btnReserve, 1);
    btnTopLay->addStretch(1);
    btnTopLay->addWidget(btnCancel, 1);

    QHBoxLayout *btnBottomLay = new QHBoxLayout;
    btnBottomLay->addWidget(btnSave);
    btnBottomLay->addStretch(1);
    btnBottomLay->addWidget(btnClose);

    QVBoxLayout *leftLay = new QVBoxLayout;
    leftLay->addLayout(leftTopLay, 1);
    leftLay->addStretch(1);
    leftLay->addLayout(btnTopLay, 1);
    leftLay->addStretch(9);
    leftLay->addLayout(btnBottomLay, 1);

    QHBoxLayout *rightTopLay = new QHBoxLayout;
    rightTopLay->addWidget(listSelf);

    QHBoxLayout *rightBottomLay = new QHBoxLayout;
    rightBottomLay->addWidget(listEntire);

    gbxSelf->setLayout(rightTopLay);
    gbxEntire->setLayout(rightBottomLay);

    QVBoxLayout *rightLay = new QVBoxLayout;
    rightLay->addWidget(gbxSelf);
    rightLay->addWidget(gbxEntire);

    QHBoxLayout *mainLay = new QHBoxLayout(this);
    mainLay->addLayout(leftLay, 1);
    mainLay->addLayout(rightLay, 9);
}
