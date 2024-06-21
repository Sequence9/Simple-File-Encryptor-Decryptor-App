#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QPropertyAnimation>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    statusBar()->showMessage("Ready");

    // Set tooltips
    ui->browseButton->setToolTip("Browse and select a file to encrypt or decrypt.");
    ui->encryptButton->setToolTip("Encrypt the selected file using the provided key.");
    ui->decryptButton->setToolTip("Decrypt the selected file using the provided key.");
    ui->keyEdit->setToolTip("Enter the key to be used for encryption or decryption.");
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_browseButton_clicked() {
    inputFilePath = QFileDialog::getOpenFileName(this, "Open File", "", "All Files (*)");
    if (!inputFilePath.isEmpty()) {
        ui->filePathEdit->setText(inputFilePath);
        statusBar()->showMessage("File selected: " + inputFilePath);
    }
}

void MainWindow::on_encryptButton_clicked() {
    QString key = ui->keyEdit->text();
    if (key.isEmpty() || inputFilePath.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please enter a key and select a file.");
        return;
    }
    QString outputFilePath = QFileDialog::getSaveFileName(this, "Save Encrypted File", "", "All Files (*)");
    if (!outputFilePath.isEmpty()) {
        try {
            FileEncryptor encryptor(key.toStdString());
            encryptor.encryptFile(inputFilePath.toStdString(), outputFilePath.toStdString(), [this](int progress) {
                QMetaObject::invokeMethod(this, "updateProgress", Qt::QueuedConnection, Q_ARG(int, progress));
            });
            showAnimatedMessage("File encrypted successfully.");
            statusBar()->showMessage("File encrypted: " + outputFilePath);
        } catch (const std::runtime_error &e) {
            QMessageBox::critical(this, "Error", e.what());
            statusBar()->showMessage("Encryption failed");
        }
    }
}

void MainWindow::on_decryptButton_clicked() {
    QString key = ui->keyEdit->text();
    if (key.isEmpty() || inputFilePath.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please enter a key and select a file.");
        return;
    }
    QString outputFilePath = QFileDialog::getSaveFileName(this, "Save Decrypted File", "", "All Files (*)");
    if (!outputFilePath.isEmpty()) {
        try {
            FileEncryptor encryptor(key.toStdString());
            encryptor.decryptFile(inputFilePath.toStdString(), outputFilePath.toStdString(), [this](int progress) {
                QMetaObject::invokeMethod(this, "updateProgress", Qt::QueuedConnection, Q_ARG(int, progress));
            });
            showAnimatedMessage("File decrypted successfully.");
            statusBar()->showMessage("File decrypted: " + outputFilePath);
        } catch (const std::runtime_error &e) {
            QMessageBox::critical(this, "Error", e.what());
            statusBar()->showMessage("Decryption failed");
        }
    }
}

void MainWindow::updateProgress(int value) {
    ui->progressBar->setValue(value);
}

void MainWindow::showAnimatedMessage(const QString &message) {
    statusBar()->showMessage(message);
    QPropertyAnimation *animation = new QPropertyAnimation(statusBar(), "windowOpacity");
    animation->setDuration(1000);
    animation->setStartValue(0.0);
    animation->setEndValue(1.0);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}
