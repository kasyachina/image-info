#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGridLayout>
#include <QFileDialog>
#include <QFileInfo>
#include <QDebug>
//#include <exiv2/exiv2.hpp>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QGridLayout *g = new QGridLayout(this->centralWidget());
    g -> addWidget(ui -> selectSingleFileButton, 0, 0, 1, 1);
    g -> addWidget(ui -> selectMultipleFilesButton, 0, 1, 1, 1);
    g -> addWidget(ui -> selectFolderButton, 0, 2, 1, 1);
    g -> addWidget(ui -> clearButton, 0, 3, 1, 1);
    g -> addWidget(ui -> dataHolder, 1, 0, 4, 4);
    ui -> dataHolder -> setColumnCount(5);
    ui -> dataHolder -> setHorizontalHeaderLabels({"имя", "размер", "разрешение", "глубина цвета", "сжатие"});
    ui -> dataHolder -> horizontalHeader() -> setSectionResizeMode(QHeaderView::Stretch);
    statusBar()->showMessage("Ничего не выбрано");
    setWindowTitle("Характеристики изображений");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_selectFolderButton_clicked()
{
    QDir newDir(QFileDialog::getExistingDirectory(this, "Выберите папку", lastDir));
    if (!newDir.isEmpty())
    {
        QFileInfoList fileList(newDir.entryInfoList(QDir::Filter::Files));
        QStringList filepaths;
        for (const auto& x : fileList)
        {
            filepaths.append(x.absoluteFilePath());
        }
        AppendDataIntoTable(filepaths);
        statusBar()->showMessage("Выбрана папка: " + newDir.dirName() + ", добавлено " + QString::number(filepaths.size()) + " файлов");
    }
}

void MainWindow::on_selectSingleFileButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Выбрать изображение", lastDir, "Выбрать изображения (*.jpg *.gif *.tif *.bmp *.png *.pcx)");
    if (!fileName.isNull())
    {
        AppendDataIntoTable({fileName});
        statusBar()->showMessage("Добавлен 1 файл", messageTimeout);
    }
}

void MainWindow::on_selectMultipleFilesButton_clicked()
{
    QStringList newFileNames = QFileDialog::getOpenFileNames(this, "Выбрать изображения", lastDir, "Выбрать изображения (*.jpg *.gif *.tif *.bmp *.png *.pcx)");
    if (!newFileNames.isEmpty())
    {
         AppendDataIntoTable(newFileNames);
         statusBar()->showMessage("Добавлено " + QString::number(newFileNames.size()) + " файлов", messageTimeout);
    }
}
void MainWindow::AppendDataIntoTable(const QStringList &list)
{
    fileNames.append(list);
    int pos = ui -> dataHolder -> rowCount();
    ui -> dataHolder -> setRowCount(pos + list.size());
    for (int i = 0; i < list.size(); ++i)
    {
        //Exiv2::Image::AutoPtr image = Exiv2::ImageFactory::open("");
        /*image->readMetadata();
        Exiv2::ExifData &exifData = image->exifData();
        /Exiv2::ExifData::const_iterator end = exifData.end();
        for (Exiv2::ExifData::const_iterator it = exifData.begin(); it != end; ++it)
        {
            std::cout << it->key() << ' ' << it -> value() << "\n";
        }*/
        QFileInfo info(list[i]);
        lastDir = info.absolutePath();
        QImage image(list[i]);
        if (!image.isNull())
        {
            ui -> dataHolder -> setItem(pos + i, 0, new QTableWidgetItem(info.fileName()));
            ui -> dataHolder -> setItem(pos + i, 1, new QTableWidgetItem(QString::number(image.size().width()) + " X " + QString::number(image.size().height())));
            //qDebug() << image.dotsPerMeterX() << ' ' << image.dotsPerMeterY();
            ui -> dataHolder -> setItem(pos + i, 2, new QTableWidgetItem(QString::number(static_cast<int>(std::min(image.dotsPerMeterX(), image.dotsPerMeterY()) / 39.37))));
            ui -> dataHolder -> setItem(pos + i, 3, new QTableWidgetItem(QString::number(image.depth())));
        }
    }
}
void MainWindow::on_clearButton_clicked()
{
    QList<QTableWidgetItem*> selectedItems = ui -> dataHolder -> selectedItems();
    if (selectedItems.size() == 0)
    {
        if (ui -> dataHolder -> rowCount() != 0)
        {
            statusBar() -> showMessage("Удалено " + QString::number(ui -> dataHolder -> rowCount()) + " файлов", messageTimeout);
            ui -> dataHolder -> clearContents();
            ui -> dataHolder -> setRowCount(0);
        }
        else
        {
            statusBar() -> showMessage("Нечего удалять", messageTimeout);
        }
    }
}

