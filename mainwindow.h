#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "uiTheme.h"
#include "FramelessHelper.h"
#include "themecfgform.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT
//基础ui
public:
    explicit MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();

protected:
    void updateMaximizeButton(bool maximized);
    void paintEvent(QPaintEvent *event) final;
private:
    Ui::MainWindow *ui;
private:
    void syncPosition();

public:
//主题相关
    UiTheme* theme;
    void MainUiThemeGet(void);
    void MainUiThemeSet(int i);

    void MainUiThemeCtrlInit(void);

private slots:
    void MainUiThemeChange(void);
    void MainUiThemeConfig(const QPoint &pos);



};

#endif // MAINWINDOW_H
