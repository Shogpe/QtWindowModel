#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QPalette>
#include <QObject>
#include <QFont>


#define C_DARK   "#555555"
#define C_PINK   "#EAA0AC"
#define C_VIOLAT "#705060"
#define C_RED    "#806050"
#define C_LIGHT  "#ffffff"

static const themeColor_T themeColorDefault[THEME_COLOR_MAX]
{
    themeColor_T{QColor("#555555"),QColor("#555555"),QColor("#E0E0E0"),QColor("#A0A0A0"),QColor("#303030")},
    themeColor_T{QColor("#f0c2a2"),QColor("#f0c2a2"),QColor("#f5f3f2"),QColor("#c0a292"),QColor("#c09282")},
    themeColor_T{QColor("#7d929f"),QColor("#7d929f"),QColor("#ecebc2"),QColor("#dcdba2"),QColor("#bcbb92")},
    themeColor_T{QColor("#ddbb99"),QColor("#ddbb99"),QColor("#535164"),QColor("#434154"),QColor("#333144")},
    themeColor_T{QColor("#d4e5ef"),QColor("#d4e5ef"),QColor("#e67762"),QColor("#d66752"),QColor("#c65742")},
    themeColor_T{QColor("#efefef"),QColor("#efefef"),QColor("#88abda"),QColor("#78bbca"),QColor("#68abba")},
};

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

static QColor colorRevers(QColor c)
{
    QColor res;
    res.setRed(255-c.red());
    res.setGreen(255-c.green());
    res.setBlue(255-c.blue());
    return res;
}

static QColor colorDiffer(QColor c,int n)
{
    QColor res;
    if(c.red()+n>255)
    {
        res.setRed(255);
    }
    else if(c.red()+n<0)
    {
        res.setRed(0);
    }
    else
    {
        res.setRed(c.red()+n);
    }


    if(c.green()+n>255)
    {
        res.setGreen(255);
    }
    else if(c.green()+n<0)
    {
        res.setGreen(0);
    }
    else
    {
        res.setGreen(c.green()+n);
    }

    if(c.blue()+n>255)
    {
        res.setBlue(255);
    }
    else if(c.blue()+n<0)
    {
        res.setBlue(0);
    }
    else
    {
        res.setBlue(c.blue()+n);
    }

    return res;
}
#define BTN_HOVER_DIFF   8
#define BTN_PRESS_DIFF  -35
#define BTN_BORDR_DIFF  -50
#define BTN_C_CODE_0(c)  (colorDiffer(c,0).name())
#define BTN_C_CODE_B(c)  (colorDiffer(c,BTN_BORDR_DIFF).name())
#define BTN_C_CODE_H(c)  (colorDiffer(c,BTN_HOVER_DIFF).name())
#define BTN_C_CODE_P(c)  (colorDiffer(c,BTN_PRESS_DIFF).name())

#define C_REVERSE(c)     (colorRevers(c))

void UiTheme::setDefaultThemeColor(void)
{
    for(int i = 0; i<THEME_COLOR_MAX; i++)
    {
        themeColor[i] = themeColorDefault[i];
    }
}



void UiTheme::SetAllButtonTheme(QWidget *w)
{
    QColor txc = themeColor[themeCurrentCnt].textColor;
    QColor btc = themeColor[themeCurrentCnt].buttonColor;

    QString ss = w->styleSheet();

    ss = ss+QString("QPushButton{border-style: none;color: %1;}"
                    "QPushButton{background-color: %2;}"
                    "QPushButton:hover{background-color: %3;}"
                    "QPushButton:pressed{background-color: %4;}").arg(txc.name()).arg(BTN_C_CODE_0(btc)).arg(BTN_C_CODE_H(btc)).arg(BTN_C_CODE_P(btc));

    w->setStyleSheet(QString(""));
    w->setStyleSheet(ss);

}

void UiTheme::SetTitleButtonTheme(QWidget *w, QPushButton *btn)
{
    QColor txc = themeColor[themeCurrentCnt].textColor;
    QColor btc = themeColor[themeCurrentCnt].buttonColor;
    QColor bkc = themeColor[themeCurrentCnt].backColor;

    QString objN = btn->objectName();

    QString tBarBtnSS  = QString("#%1 {border-style: none;color: %2;background-color: transparent;border-radius: 0px;}\n").arg(objN).arg(txc.name());
            tBarBtnSS += QString("#%1:hover {border-style: none;color: %2; border-style: none;background-color: %3;}\n").arg(objN).arg(txc.name()).arg(BTN_C_CODE_H(bkc));
            tBarBtnSS += QString("#%1:pressed{border-style: none;color: %2;background-color: %3;}\n").arg(objN).arg(txc.name()).arg(BTN_C_CODE_P(btc));

    QString ss = w->styleSheet();
    ss += tBarBtnSS;

    w->setStyleSheet(QString(""));
    w->setStyleSheet(ss);

}

void UiTheme::SetThemeButtonTheme(QWidget *w, QPushButton *btn)
{
    QString objN = btn->objectName();
    char idx = objN.at(11).cell()-'0';

    if(uint8_t(idx) > 5)
    {
        idx = 0;
    }
    QColor txc = themeColor[uint8_t(idx)].textColor;
    QColor bkc = themeColor[uint8_t(idx)].backColor;

    QString tBarBtnSS  = QString("#%1 {border-style: none;background-color: %2;border-radius: 0px;border-radius: 2px;}\n").arg(objN).arg(bkc.name());
            tBarBtnSS += QString("#%1:hover {border: 2px solid %2;background-color: %3;border-radius: 9px;}\n").arg(objN).arg(txc.name()).arg(bkc.name());
            tBarBtnSS += QString("#%1:pressed{border: 7px solid %2;background-color: %3;border-radius: 9px;}\n").arg(objN).arg(bkc.name()).arg(txc.name());

    QString ss = w->styleSheet();
    ss += tBarBtnSS;

    w->setStyleSheet(QString(""));
    w->setStyleSheet(ss);

}


void UiTheme::SetAllSpinTheme(QWidget *w)
{
    QColor txc = themeColor[themeCurrentCnt].textColor;
    QColor itc = themeColor[themeCurrentCnt].itemColor;

    QString ss = w->styleSheet();

    ss = ss + QString("QSpinBox{border-style: none;color: %1;background-color:%2;}").arg(txc.name()).arg(itc.name());

    w->setStyleSheet(QString(""));
    w->setStyleSheet(ss);
}

void UiTheme::SetAllSliderTheme(QWidget *w)
{
    QColor txc = themeColor[themeCurrentCnt].textColor;
    QColor itc = themeColor[themeCurrentCnt].textColor;

    QString ss = w->styleSheet();

    ss = ss+QString("QSlider::handle:horizontal{height: 10px;  width: 10px;margin: 0px -2px 0px -2px;border-radius: 4px;"
                    "background: %1;border: 2px solid %2;}QSlider{border: 0px;}").arg(itc.name()).arg(txc.name());
    ss = ss+QString("QSlider::handle:vertical{height: 10px;  width: 10px;margin: 0px -2px 0px -2px;border-radius: 4px;"
                    "background: %1;border: 2px solid %2;}QSlider{border: 0px;}").arg(itc.name()).arg(txc.name());
    w->setStyleSheet(QString(""));
    w->setStyleSheet(ss);
}

void UiTheme::SetAllLabelTheme(QWidget *w)
{
    QColor txc = themeColor[themeCurrentCnt].textColor;

    QString ss = w->styleSheet();

    ss = ss+QString("QLabel{border-style: none;color: %1;}").arg(txc.name());

    w->setStyleSheet(QString(""));
    w->setStyleSheet(ss);
}

void UiTheme::SetAllGroupTheme(QWidget *w)
{
    QColor txc = themeColor[themeCurrentCnt].textColor;
    QColor bdc = themeColor[themeCurrentCnt].bordorColor;

    QString ss = w->styleSheet();

    ss = ss+QString("QGroupBox{border: 2px solid %1;color: %2;}").arg(bdc.name()).arg(txc.name());

    w->setStyleSheet(QString(""));
    w->setStyleSheet(ss);

}

void UiTheme::SetAllEditorTheme(QWidget *w)
{
    QColor txc = themeColor[themeCurrentCnt].textColor;
    QColor bdc = themeColor[themeCurrentCnt].bordorColor;
    QColor bkc = themeColor[themeCurrentCnt].backColor;

    QString ss = w->styleSheet();

    ss = ss+QString("QLineEdit{border: 2px solid %1;color: %2;background: %3;}").arg(bdc.name()).arg(txc.name()).arg(bkc.name());

    w->setStyleSheet(QString(""));
    w->setStyleSheet(ss);

}


void UiTheme::SetAllLineTheme(QWidget *w)
{
    QColor txc = themeColor[themeCurrentCnt].textColor;
    QColor bdc = themeColor[themeCurrentCnt].bordorColor;
    QColor bkc = themeColor[themeCurrentCnt].backColor;

    QString ss = w->styleSheet();

    QList <QFrame *> lineList = w->findChildren<QFrame *>();
    foreach(QFrame * l, lineList)
    {
        if(l->objectName().left(4) == "line")
        {
            ss = ss+QString("#%1{background: %2;}").arg(l->objectName()).arg(bdc.name());
        }
    }

    w->setStyleSheet(QString(""));
    w->setStyleSheet(ss);

}

void UiTheme::SetAllCheckboxTheme(QWidget *w)
{
    QColor txc = themeColor[themeCurrentCnt].textColor;
    QColor bdc = themeColor[themeCurrentCnt].bordorColor;
    QColor bkc = themeColor[themeCurrentCnt].backColor;

    QString ss = w->styleSheet();

    ss = ss+QString("QCheckBox{border-style: none;color: %1;}").arg(txc.name());
    ss = ss+QString("QRadioButton{border-style: none;color: %1;}").arg(txc.name());

    w->setStyleSheet(QString(""));
    w->setStyleSheet(ss);

}

void UiTheme::themeSet(QWidget* w, int i)
{
    themeCurrentCnt = i;
    w->setStyleSheet(QString(""));
    QColor  btc = themeColor[themeCurrentCnt].buttonColor;
    QColor  bkc = themeColor[themeCurrentCnt].backColor;
    QColor  txc = themeColor[themeCurrentCnt].textColor;
    QColor  bdc = themeColor[themeCurrentCnt].bordorColor;
    QColor  itc = themeColor[themeCurrentCnt].itemColor;

    qDebug()<<btc.name()<<" - "<<bkc.name()<<" - "<<txc.name()<<" - "<<bdc.name()<<" - "<<itc.name();
//    //字体
//    QFont font = QFont("Microsoft YaHei",10);
//    w->setFont(font);

    //主窗口
    QPalette MainW;
    MainW.setBrush(QPalette::Window,QBrush(bkc));
    w->setPalette(MainW);


    //标题栏的三个按键
    QString tBarBtnSS = w->styleSheet();
    tBarBtnSS  = QString("\n#minimizeButton {image: url(:/res/minimize-button1.png);}\n");
    tBarBtnSS += QString("\n#minimizeButton, #maximizeButton {background-color: transparent;border-radius: 0px;}\n");
    tBarBtnSS += QString("\n#minimizeButton:hover, #maximizeButton:hover {border-style: none;background-color: %1;}\n").arg(BTN_C_CODE_H(bkc));
    tBarBtnSS += QString("\n#minimizeButton:pressed, #maximizeButton:pressed {border-style: none;background-color: %1;}\n").arg(BTN_C_CODE_P(bkc));
    tBarBtnSS += QString("\n#closeButton {image: url(:/res/close-button1.png);background-color: transparent;border-radius: 0px;}\n");
    tBarBtnSS += QString("\n#closeButton:hover {image: url(:/res/close-button2.png);border-style: none;background-color: #e81123;}\n");
    tBarBtnSS += QString("\n#closeButton:pressed {image: url(:/res/close-button2.png);border-style: none;background-color: #8c0a15;}\n");

    //标题栏的菜单栏
    tBarBtnSS += QString("QMenuBar{background-color:%1;}").arg(bkc.name());
    tBarBtnSS += QString("QMenuBar::item{background-color:%1;color:%2;}\n").arg(bkc.name()).arg(txc.name());
    tBarBtnSS += QString("QMenuBar::item:hover{background-color:%1;color:%2;}\n").arg(BTN_C_CODE_H(bkc)).arg(txc.name());
    tBarBtnSS += QString("QMenuBar::item:selected{background-color:%1;color:%2;}\n").arg(BTN_C_CODE_H(bkc)).arg(txc.name());
    tBarBtnSS += QString("QMenu{background-color:%1;border:none;}\n").arg(bkc.name());
    tBarBtnSS += QString("QMenu::item{padding:5px 20px;border: %1;background-color:%1;color:%2;}\n").arg(bkc.name()).arg(txc.name());
    tBarBtnSS += QString("QMenu::item:hover{background-color:%1;color:%2;}\n").arg(BTN_C_CODE_H(bkc)).arg(txc.name());
    tBarBtnSS += QString("QMenu::item:selected{background-color:%1;color:%2;}\n").arg(BTN_C_CODE_H(bkc)).arg(txc.name());

    tBarBtnSS += QString("\n#icoTitle {background-image: url(:/res/main.jpg);}\n");
    tBarBtnSS += QString("\n#paintAera {background-color: %1;}\n").arg(itc.name());
    w->setStyleSheet(QString(""));
    w->setStyleSheet(tBarBtnSS);

    SetAllButtonTheme(w);
    SetAllSpinTheme(w);
    SetAllLabelTheme(w);
    SetAllSliderTheme(w);
    SetAllGroupTheme(w);
    SetAllEditorTheme(w);
    SetAllLineTheme(w);
    SetAllCheckboxTheme(w);
}




UiTheme::UiTheme()
{
    themeCurrentCnt = 0;
}


UiTheme::~UiTheme()
{


}


