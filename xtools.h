#ifndef XTOOLS_H
#define XTOOLS_H

#include <QMainWindow>

namespace Ui {
class XTools;
}

class XTools : public QMainWindow
{
    Q_OBJECT

public:
    explicit XTools(QWidget *parent = 0);
    ~XTools();

private slots:
    void on_Load_clicked();

    void on_Backup_clicked();

    void on_Restore_clicked();

    void on_ScreenShot_clicked();

    void on_actionReload_triggered();

    void on_actionAbout_triggered();

    void on_actionExit_triggered();

    void on_pushButton_7_clicked();

private:
    Ui::XTools *ui;
};

#endif // XTOOLS_H
