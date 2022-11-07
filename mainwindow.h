#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_selectFolderButton_clicked();

    void on_selectSingleFileButton_clicked();

    void on_selectMultipleFilesButton_clicked();

    void on_clearButton_clicked();

private:
    void PutDataIntoTable(const QStringList &list);
    QStringList fileNames;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
