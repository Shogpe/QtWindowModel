#ifndef THEMECFGFORM_H
#define THEMECFGFORM_H


#include <QWidget>
#include "uiTheme.h"

namespace Ui {
class themeCfgForm;
}

class themeCfgForm : public QWidget
{
    Q_OBJECT

public:
    explicit themeCfgForm(QWidget *parent = 0);
    ~themeCfgForm();
    UiTheme* theme;
private:
    Ui::themeCfgForm *ui;


    void SubUiThemeGet(void);
    void SubUiThemeSet(int i);
    void uiThemeConfrim(void);

private slots:
    void ColorSet(const QColor color);
    void ColorChanged(void);
    void ColorPadSet(void);


signals:
    void Ui_Change_Confirmed(void);
};

#endif // THEMECFGFORM_H
