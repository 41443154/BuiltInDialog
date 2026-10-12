#ifndef CBUILDINDLG_H
#define CBUILDINDLG_H

#include <QDialog>
#include <QtWidgets>
class CBuildinDlg : public QDialog
{
    Q_OBJECT

public:
    explicit CBuildinDlg(QWidget *parent = nullptr);
    ~CBuildinDlg() override;

private:
    QTextEdit* displayTextEdit;
    QPushButton* colorPushBtn;
    QPushButton* errorPushBtn;
    QPushButton* filePushBtn;
    QPushButton* fontPushBtn;
    QPushButton* inputPushBtn;
    QPushButton* pagePushBtn;
    QPushButton* progressPushBtn;
    QPushButton* printPushBtn;
    QPushButton *colorTextPushBtn;
private slots:
    void doPushBtn();
};
#endif // CBUILDINDLG_H
