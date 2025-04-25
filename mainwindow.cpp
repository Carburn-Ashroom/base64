#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "translate.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setFixedSize(size());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_encrypt_clicked()
{
    if (ui->multiline->checkState() == Qt::Unchecked) {
        Trans::Encrypt enc {ui->text->toPlainText()};
        ui->password->setPlainText(enc.get());
    }
    else {
        QStringList text {ui->text->toPlainText().split('\n')};
        QString pass;
        QTextStream t_str {&pass};
        for (auto& p : text) {
            Trans::Encrypt enc {p};
            t_str << enc.get() << '\n';
        }
        pass.removeLast();
        ui->password->setPlainText(pass);
    }
}

void MainWindow::on_decrypt_clicked()
{
    QStringList pass {ui->password->toPlainText().split('\n')};
    QString text;
    QTextStream t_str {&text};
    for (auto& p : pass) {
        try {
            Trans::Decrypt dec {p};
            t_str << dec.get() << '\n';
        }
        catch (Trans::Table_404_error) {
            t_str << tr("密码中含有无效字符\n");
        }
        catch (Bit::Length_error) {
            t_str << tr("密码长度有误\n");
        }
    }
    text.removeLast();
    ui->text->setPlainText(text);
}
