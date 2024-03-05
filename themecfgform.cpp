#include "themecfgform.h"
#include "ui_themecfgform.h"
#include "FramelessHelper.h"
#include "themecfgform.h"
#include <QTimer>
#include <QWindow>
#include <QScreen>
#include <QPainter>
#include <QStyle>
#include <QStyleOption>
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QSettings>
#include <QColorDialog>

int GlobThemeCnt = 0;

themeCfgForm::themeCfgForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::themeCfgForm)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    setWindowModality(Qt::WindowModal );
    auto helper = new FramelessHelper(this);
//    helper->setDraggableMargins(3, 3, 3, 3);
//    helper->setMaximizedMargins(3, 3, 3, 3);
    helper->setTitleBarHeight(30);

    helper->addExcludeItem(ui->closeButton);

    connect(ui->closeButton, &QPushButton::clicked,
            helper, &FramelessHelper::triggerCloseButtonAction);



    SubUiThemeGet();
    SubUiThemeSet(theme->themeCurrentCnt);


//    ui->widget_2->setLayout(new QGridLayout);
    QColorDialog* c = new QColorDialog(ui->colorWidget);

    c->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    c->setOption(QColorDialog::NoButtons,true);
    c->move(0,0);

    connect(ui->btcSet, &QPushButton::clicked,this,[=]{ColorSet(c->currentColor());});
    connect(ui->bkcSet, &QPushButton::clicked,this,[=]{ColorSet(c->currentColor());});
    connect(ui->txcSet, &QPushButton::clicked,this,[=]{ColorSet(c->currentColor());});
    connect(ui->bdcSet, &QPushButton::clicked,this,[=]{ColorSet(c->currentColor());});
    connect(ui->itcSet, &QPushButton::clicked,this,[=]{ColorSet(c->currentColor());});
    connect(ui->confirm,&QPushButton::clicked,this,[=]{ColorSet(c->currentColor());});

    connect(ui->btcs,&QLineEdit::textChanged,this,&themeCfgForm::ColorChanged);
    connect(ui->bkcs,&QLineEdit::textChanged,this,&themeCfgForm::ColorChanged);
    connect(ui->txcs,&QLineEdit::textChanged,this,&themeCfgForm::ColorChanged);
    connect(ui->bdcs,&QLineEdit::textChanged,this,&themeCfgForm::ColorChanged);
    connect(ui->itcs,&QLineEdit::textChanged,this,&themeCfgForm::ColorChanged);

    connect(ui->btcs,&QLineEdit::cursorPositionChanged,this,[=]{c->setCurrentColor(QColor(ui->btcs->text()));});
    connect(ui->bkcs,&QLineEdit::cursorPositionChanged,this,[=]{c->setCurrentColor(QColor(ui->bkcs->text()));});
    connect(ui->txcs,&QLineEdit::cursorPositionChanged,this,[=]{c->setCurrentColor(QColor(ui->txcs->text()));});
    connect(ui->bdcs,&QLineEdit::cursorPositionChanged,this,[=]{c->setCurrentColor(QColor(ui->bdcs->text()));});
    connect(ui->itcs,&QLineEdit::cursorPositionChanged,this,[=]{c->setCurrentColor(QColor(ui->itcs->text()));});


    c->show();
}

themeCfgForm::~themeCfgForm()
{
    delete ui;
}

void themeCfgForm::SubUiThemeGet(void)
{
    theme = new UiTheme;

    QSettings* setting = new QSettings(QCoreApplication::applicationDirPath()+"/uiTheme.ini",QSettings::IniFormat);
    //theme->themeCurrentCnt = setting->value("currentCnt/CNT").value<int>();
    theme->themeCurrentCnt = GlobThemeCnt;
    for(int i = 0; i < THEME_COLOR_MAX; i++)
    {

        theme->themeColor[i].buttonColor = setting->value(QString("theme%1").arg(i)+"/btc").value<QColor>();
        theme->themeColor[i].backColor = setting->value(QString("theme%1").arg(i)+"/bkc").value<QColor>();
        theme->themeColor[i].textColor = setting->value(QString("theme%1").arg(i)+"/txc").value<QColor>();
        theme->themeColor[i].bordorColor = setting->value(QString("theme%1").arg(i)+"/bdc").value<QColor>();
        theme->themeColor[i].itemColor = setting->value(QString("theme%1").arg(i)+"/itc").value<QColor>();
    }



//    themeColor


}

void themeCfgForm::uiThemeConfrim(void)
{
    QSettings* setting = new QSettings(QCoreApplication::applicationDirPath()+"/uiTheme.ini",QSettings::IniFormat);


    setting->setValue("currentCnt/CNT",QString("%1").arg(theme->themeCurrentCnt));
    for(int i = 0; i < THEME_COLOR_MAX; i++)
    {
        setting->setValue(QString("theme%1").arg(i)+"/btc",theme->themeColor[i].buttonColor.name());
        setting->setValue(QString("theme%1").arg(i)+"/bkc",theme->themeColor[i].backColor.name());
        setting->setValue(QString("theme%1").arg(i)+"/txc",theme->themeColor[i].textColor.name());
        setting->setValue(QString("theme%1").arg(i)+"/bdc",theme->themeColor[i].bordorColor.name());
        setting->setValue(QString("theme%1").arg(i)+"/itc",theme->themeColor[i].itemColor.name());
    }

    emit Ui_Change_Confirmed();

}

void themeCfgForm::SubUiThemeSet(int i)
{
    if(theme != NULL)
    {
        if(i>=THEME_COLOR_MAX)
        {
            i = 0;
        }
        theme->themeSet(this,i);
        theme->themeSet(ui->widget,i);

        QSettings* setting = new QSettings(QCoreApplication::applicationDirPath()+"/uiTheme.ini",QSettings::IniFormat);
        setting->setValue("currentCnt/CNT",QString("%1").arg(i));
        this->ui->btcs->setText(theme->themeColor[i].buttonColor.name());
        this->ui->bkcs->setText(theme->themeColor[i].backColor.name());
        this->ui->txcs->setText(theme->themeColor[i].textColor.name());
        this->ui->bdcs->setText(theme->themeColor[i].bordorColor.name());
        this->ui->itcs->setText(theme->themeColor[i].itemColor.name());
    }
}

void themeCfgForm::ColorPadSet(void)
{
    auto line = qobject_cast<QLineEdit *>(sender());

    if(line == NULL)
    {
        return;
    }




}






void themeCfgForm::ColorSet(const QColor color)
{
    auto btn = qobject_cast<QPushButton *>(sender());

    if(btn == NULL)
    {
        return;
    }

    if(btn->objectName() == "confirm")
    {
        uiThemeConfrim();
        this->close();
    }
    else if(btn->objectName() == "btcSet")
    {
        ui->btcs->setText(color.name());
    }
    else if(btn->objectName() == "bkcSet")
    {
        ui->bkcs->setText(color.name());
    }
    else if(btn->objectName() == "txcSet")
    {
        ui->txcs->setText(color.name());
    }
    else if(btn->objectName() == "bdcSet")
    {
        ui->bdcs->setText(color.name());
    }
    else if(btn->objectName() == "itcSet")
    {
        ui->itcs->setText(color.name());
    }

}


void themeCfgForm::ColorChanged(void)
{
    auto line = qobject_cast<QLineEdit *>(sender());

    if(line == NULL)
    {
        return;
    }


    if(line->text().at(0).cell() == '#'
       &&line->text().right(6).toInt()>=0x0
       &&line->text().right(6).toInt()<=0xffffff)
    {
        if(line->objectName() == "btcs")
        {
            theme->themeColor[theme->themeCurrentCnt].buttonColor = QColor(ui->btcs->text());
        }
        else if(line->objectName() == "bkcs")
        {
            theme->themeColor[theme->themeCurrentCnt].backColor   = QColor(ui->bkcs->text());
        }
        else if(line->objectName() == "txcs")
        {
            theme->themeColor[theme->themeCurrentCnt].textColor   = QColor(ui->txcs->text());
        }
        else if(line->objectName() == "bdcs")
        {
            theme->themeColor[theme->themeCurrentCnt].bordorColor = QColor(ui->bdcs->text());
        }
        else if(line->objectName() == "itcs")
        {
            theme->themeColor[theme->themeCurrentCnt].itemColor   = QColor(ui->itcs->text());
        }

        theme->themeSet(this,theme->themeCurrentCnt);
        theme->themeSet(ui->widget,theme->themeCurrentCnt);
    }

}


