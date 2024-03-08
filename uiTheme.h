#ifndef UITHEME_H
#define UITHEME_H

#include <QColor>
#include <QWidget>
#include <QPushButton>
#include <QString>

typedef struct
{
    QColor buttonColor;
    QColor backColor;
    QColor textColor;
    QColor bordorColor;
    QColor itemColor;

    QColor titleColor;
    QColor PaintBackColor;
    QColor toolBarColor;
    QColor bottomColor;


}themeColor_T;
#define THEME_COLOR_MAX 6


class UiTheme
{

public:
    explicit UiTheme();
    virtual ~UiTheme();

public:

    themeColor_T themeColor[THEME_COLOR_MAX];
    int  themeCurrentCnt;
public:

    void themeSet(QWidget* w, int i);

    void SetAllButtonTheme(QWidget *w);
    void SetTitleButtonTheme(QWidget *w, QPushButton *btn);
    void SetThemeButtonTheme(QWidget *w, QPushButton *btn);

    void SetAllSpinTheme(QWidget *w);
    void SetAllSliderTheme(QWidget *w);
    void SetAllLabelTheme(QWidget *w);
    void SetAllGroupTheme(QWidget *w);
    void SetAllEditorTheme(QWidget *w);
    void SetAllLineTheme(QWidget *w);
    void SetAllCheckboxTheme(QWidget *w);





};




#endif // UITHEME_H
