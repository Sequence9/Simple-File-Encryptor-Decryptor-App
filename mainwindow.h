#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "FileEncryptor.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_browseButton_clicked();
    void on_encryptButton_clicked();
    void on_decryptButton_clicked();
    void updateProgress(int value);

private:
    Ui::MainWindow *ui;
    QString inputFilePath;
    void showAnimatedMessage(const QString &message);
};

#endif // MAINWINDOW_H
