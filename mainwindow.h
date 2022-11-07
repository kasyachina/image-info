#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <map>

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

    void tableItemClicked(int row, int column);

private:
    std::map<QString, QString> compression;
    void AppendDataIntoTable(const QStringList &list);
    const int messageTimeout = 5000;
    std::map<QString, QString> fileNames;
    QString lastDir = "/";
    Ui::MainWindow *ui;
    QStringList dirFilter;
};
#endif // MAINWINDOW_H
