#include "mainwindow.h"
#include "ui_mainwindow.h"

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

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent, Qt::FramelessWindowHint)
    , ui(new Ui::MainWindow())
{
    ui->setupUi(this);

    auto helper = new FramelessHelper(this);
    helper->setDraggableMargins(3, 3, 3, 3);
    helper->setMaximizedMargins(3, 3, 3, 3);
    helper->setTitleBarHeight(60);

    helper->addExcludeItem(ui->minimizeButton);
    helper->addExcludeItem(ui->maximizeButton);
    helper->addExcludeItem(ui->closeButton);

    helper->addExcludeItem(ui->menuBar);
    helper->addExcludeItem(ui->helpMenu);
    helper->addExcludeItem(ui->editMenu);
    helper->addExcludeItem(ui->fileMenu);

    helper->addExcludeItem(ui->themeColor_0);
    helper->addExcludeItem(ui->themeColor_1);
    helper->addExcludeItem(ui->themeColor_2);
    helper->addExcludeItem(ui->themeColor_3);
    helper->addExcludeItem(ui->themeColor_4);
    helper->addExcludeItem(ui->themeColor_5);

    connect(ui->minimizeButton, &QPushButton::clicked,
            helper, &FramelessHelper::triggerMinimizeButtonAction);
    connect(ui->maximizeButton, &QPushButton::clicked,
            helper, &FramelessHelper::triggerMaximizeButtonAction);
    connect(ui->closeButton, &QPushButton::clicked,
            helper, &FramelessHelper::triggerCloseButtonAction);
    connect(helper, &FramelessHelper::maximizedChanged,
            this, &MainWindow::updateMaximizeButton);

    ui->maximizeButton->setIcon(QIcon(QStringLiteral(":/res/maximize-button1.png")));

    MainUiThemeGet();
    MainUiThemeSet(theme->themeCurrentCnt);
    MainUiThemeCtrlInit();





    QTimer::singleShot(100, this, &MainWindow::syncPosition);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateMaximizeButton(bool maximized)
{
    if (maximized) {
        ui->maximizeButton->setIcon(QIcon(QStringLiteral(":/res/maximize-button2.png")));
        ui->maximizeButton->setToolTip(tr("向下还原"));
    } else {
        ui->maximizeButton->setIcon(QIcon(QStringLiteral(":/res/maximize-button1.png")));
        ui->maximizeButton->setToolTip(tr("最大化"));
    }
}


void MainWindow::syncPosition()
{
    QWindow *window = windowHandle();
    QScreen *screen = window->screen();

    window->setX(screen->availableGeometry().width() / 2 + 10);
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}


void MainWindow::MainUiThemeCtrlInit(void)
{
    connect(ui->themeColor_0,&QPushButton::clicked,this,&MainWindow::MainUiThemeChange);
    connect(ui->themeColor_1,&QPushButton::clicked,this,&MainWindow::MainUiThemeChange);
    connect(ui->themeColor_2,&QPushButton::clicked,this,&MainWindow::MainUiThemeChange);
    connect(ui->themeColor_3,&QPushButton::clicked,this,&MainWindow::MainUiThemeChange);
    connect(ui->themeColor_4,&QPushButton::clicked,this,&MainWindow::MainUiThemeChange);
    connect(ui->themeColor_5,&QPushButton::clicked,this,&MainWindow::MainUiThemeChange);

    ui->themeColor_0->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->themeColor_1->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->themeColor_2->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->themeColor_3->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->themeColor_4->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->themeColor_5->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(ui->themeColor_0,&QPushButton::customContextMenuRequested,this,&MainWindow::MainUiThemeConfig);
    connect(ui->themeColor_1,&QPushButton::customContextMenuRequested,this,&MainWindow::MainUiThemeConfig);
    connect(ui->themeColor_2,&QPushButton::customContextMenuRequested,this,&MainWindow::MainUiThemeConfig);
    connect(ui->themeColor_3,&QPushButton::customContextMenuRequested,this,&MainWindow::MainUiThemeConfig);
    connect(ui->themeColor_4,&QPushButton::customContextMenuRequested,this,&MainWindow::MainUiThemeConfig);
    connect(ui->themeColor_5,&QPushButton::customContextMenuRequested,this,&MainWindow::MainUiThemeConfig);
}

void MainWindow::MainUiThemeGet(void)
{
    theme = new UiTheme;

    QSettings* setting = new QSettings(QCoreApplication::applicationDirPath()+"/uiTheme.ini",QSettings::IniFormat);

    if(!(setting->contains("theme0/btc")&&setting->contains("theme5/itc")))
    {
        qDebug()<<"set default ini";
        setting->setValue("currentCnt/CNT","0");

        theme->setDefaultThemeColor();
        for(int i = 0; i < THEME_COLOR_MAX; i++)
        {
            setting->setValue(QString("theme%1").arg(i)+"/btc",theme->themeColor[i].buttonColor.name());
            setting->setValue(QString("theme%1").arg(i)+"/bkc",theme->themeColor[i].backColor.name());
            setting->setValue(QString("theme%1").arg(i)+"/txc",theme->themeColor[i].textColor.name());
            setting->setValue(QString("theme%1").arg(i)+"/bdc",theme->themeColor[i].bordorColor.name());
            setting->setValue(QString("theme%1").arg(i)+"/itc",theme->themeColor[i].itemColor.name());
        }
    }

    for(int i = 0; i < THEME_COLOR_MAX; i++)
    {
        theme->themeCurrentCnt = setting->value("currentCnt/CNT").value<int>();
        theme->themeColor[i].buttonColor = setting->value(QString("theme%1").arg(i)+"/btc").value<QColor>();
        theme->themeColor[i].backColor = setting->value(QString("theme%1").arg(i)+"/bkc").value<QColor>();
        theme->themeColor[i].textColor = setting->value(QString("theme%1").arg(i)+"/txc").value<QColor>();
        theme->themeColor[i].bordorColor = setting->value(QString("theme%1").arg(i)+"/bdc").value<QColor>();
        theme->themeColor[i].itemColor = setting->value(QString("theme%1").arg(i)+"/itc").value<QColor>();
    }



//    themeColor


}

void MainWindow::MainUiThemeSet(int i)
{
    if(theme != NULL)
    {
        if(i>=THEME_COLOR_MAX)
        {
            i = 0;
        }
        theme->themeSet(this,i);

        theme->SetThemeButtonTheme(this,ui->themeColor_0);
        theme->SetThemeButtonTheme(this,ui->themeColor_1);
        theme->SetThemeButtonTheme(this,ui->themeColor_2);
        theme->SetThemeButtonTheme(this,ui->themeColor_3);
        theme->SetThemeButtonTheme(this,ui->themeColor_4);
        theme->SetThemeButtonTheme(this,ui->themeColor_5);

        QSettings* setting = new QSettings(QCoreApplication::applicationDirPath()+"/uiTheme.ini",QSettings::IniFormat);
        setting->setValue("currentCnt/CNT",QString("%1").arg(i));
    }
}

void MainWindow::MainUiThemeChange(void)
{
    auto btn = qobject_cast<QPushButton *>(sender());
    int idx = btn->objectName().at(11).cell()-'0';
    if(idx>THEME_COLOR_MAX)
    {
        idx = 0;
    }
    MainUiThemeSet(idx);
}

void MainWindow::MainUiThemeConfig(const QPoint &pos)
{
    qDebug()<<"config theme";
    static themeCfgForm* wCache;
    static int cntCache;

    auto cnt = qobject_cast<QPushButton *>(sender());

    if(wCache!=NULL)
    {
        wCache->close();
    }

    extern int GlobThemeCnt;

    GlobThemeCnt = cnt->objectName().at(11).cell()-'0';

    themeCfgForm* w = new themeCfgForm();
    wCache = w;
    connect(w,&themeCfgForm::Ui_Change_Confirmed,this,[=]{
        MainUiThemeGet();
        MainUiThemeSet(GlobThemeCnt);
        qDebug()<<"signal recive";
    });
    w->show();


}
