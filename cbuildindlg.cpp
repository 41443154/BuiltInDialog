#include "cbuildindlg.h"
#include <QtPrintSupport/qprinter.h>
#include <QtPrintSupport/qpagesetupdialog.h>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrintPreviewDialog>
#include <QColorDialog>
#include <QTextCursor>
#include <QTextCharFormat>

CBuildinDlg::CBuildinDlg(QWidget *parent)
    : QDialog(parent)
{
    QGridLayout* gridLayout = new QGridLayout;

    displayTextEdit = new QTextEdit (QStringLiteral ("Qt的標準通用對話盒"));
    colorPushBtn = new QPushButton (QStringLiteral("顏色對話盒"));
    errorPushBtn = new QPushButton (QStringLiteral("錯誤訊息盒"));
    filePushBtn  = new QPushButton (QStringLiteral("檔案對話盒"));
    fontPushBtn = new QPushButton (QStringLiteral("字體對話盒"));
    inputPushBtn = new QPushButton (QStringLiteral("輸入對話盒"));
    pagePushBtn = new QPushButton (QStringLiteral("頁面設定對話盒"));
    progressPushBtn = new QPushButton (QStringLiteral("進度對話盒"));
    printPushBtn = new QPushButton (QStringLiteral("列印對話盒"));
    colorTextPushBtn = new QPushButton(QStringLiteral("更改文字顏色"));


    gridLayout->addWidget(colorPushBtn,0,0,1,1);
    gridLayout->addWidget(errorPushBtn,0,1,1,1);
    gridLayout->addWidget(filePushBtn,0,2,1,1);

    gridLayout->addWidget(fontPushBtn,1,0,1,1);
    gridLayout->addWidget(inputPushBtn,1,1,1,1);
    gridLayout->addWidget(pagePushBtn,1,2,1,1);

    gridLayout->addWidget(progressPushBtn,2,0,1,1);
    gridLayout->addWidget(printPushBtn,2,1,1,1);
    gridLayout->addWidget(colorTextPushBtn,2,2,1,1);

    gridLayout->addWidget(displayTextEdit,3,0,3,3);

    setLayout (gridLayout);
    setWindowTitle (QStringLiteral("內建對話盒展示"));
    resize (400,300);

    connect (colorPushBtn, SIGNAL (clicked()),this, SLOT (doPushBtn()));
    connect (errorPushBtn, SIGNAL (clicked()),this, SLOT (doPushBtn()));
    connect (filePushBtn, SIGNAL (clicked()),this, SLOT (doPushBtn()));
    connect (fontPushBtn, SIGNAL (clicked()),this, SLOT (doPushBtn()));
    connect (inputPushBtn, SIGNAL (clicked()),this, SLOT (doPushBtn()));
    connect (progressPushBtn, SIGNAL(clicked()), this, SLOT (doPushBtn()));
    connect (pagePushBtn, SIGNAL (clicked()), this, SLOT (doPushBtn()));
    connect (printPushBtn, SIGNAL (clicked()), this, SLOT (doPushBtn()));
    connect (colorTextPushBtn, SIGNAL (clicked()), this, SLOT (doPushBtn()));
}

void CBuildinDlg:: doPushBtn()
    {
    QPushButton* btn = qobject_cast<QPushButton*>(sender());
    if (btn == colorPushBtn)
    {
        QPalette palette=displayTextEdit->palette();
        const QColor& color=QColorDialog::getColor(palette.color (QPalette:: Base),this, QStringLiteral ("設定背景顏色"));
        if (color.isValid())
        {
            palette.setColor (QPalette:: Base, color);
            displayTextEdit->setPalette (palette);
        }
    }
    if (btn == errorPushBtn)
    {
    QErrorMessage box (this);
    box.setWindowTitle (QStringLiteral("錯誤訊息盒"));
    box.showMessage (QStringLiteral("錯誤訊息盒實例xx:"));
    box.showMessage (QStringLiteral("錯誤訊息盒實例yy"));
    box.showMessage (QStringLiteral("錯誤訊息盒實例zz:"));
    box.exec();
    }
    if (btn == filePushBtn)
    {
        QString fileName = QFileDialog::getOpenFileName(
            this,
            QStringLiteral("打開檔案"),
            QStringLiteral("."),
            QStringLiteral("任何檔案 (*.*);;文字檔 (*.txt);;XML檔 (*.xml)")
            );

        displayTextEdit->setText(fileName);
    }
    if (btn == fontPushBtn)
    {
        bool ok;
        const QFont font = QFontDialog::getFont(
            &ok,
            displayTextEdit->font(),
            this,
            QStringLiteral("字體對話盒")
            );

        if (ok)
            displayTextEdit->setFont(font);
    }
    if (btn == inputPushBtn)
    {
        bool ok;

        QString text = QInputDialog::getText(
            this,
            QStringLiteral("輸入對話盒"),
            QStringLiteral("輸入文字"),
            QLineEdit::Normal,
            QDir::home().dirName(),
            &ok
            );

        if (ok && !text.isEmpty())
            displayTextEdit->setText(text);
    }

    if (btn == pagePushBtn)
    {
        QPrinter printer(QPrinter::HighResolution);

        QPageSetupDialog dlg(&printer, this);

        dlg.setWindowTitle(QStringLiteral("頁面設定話方塊"));

        if (dlg.exec() == QDialog::Accepted)
        {
            // 使用者按下確定後執行
        }
    }

    if (btn == progressPushBtn)
    {
        QProgressDialog progress(
            QStringLiteral("正在複製檔案..."),
            QStringLiteral("取消"),
            0, 10000, this
            );

        progress.setWindowTitle(QStringLiteral("進度對話方塊"));
        progress.show();

        for (int i = 0; i < 10000; i++)
        {
            progress.setValue(i);
            qApp->processEvents();

            if (progress.wasCanceled())
                break;

            qDebug() << i;
        }

        if (!progress.wasCanceled())
            progress.setValue(10000);
    }

    if (btn == printPushBtn)
    {
        QPrinter printer(QPrinter::HighResolution);

        QPrintDialog dialog(&printer, this);

        if (dialog.exec() != QDialog::Accepted)
            return;

        displayTextEdit->print(&printer);
    }


    if (btn == colorTextPushBtn)
    {
        QColor color = QColorDialog::getColor(
            displayTextEdit->textColor(),
            this,
            QStringLiteral("選擇文字顏色")
            );

        if (color.isValid())
        {
            QTextCursor cursor = displayTextEdit->textCursor();

            cursor.select(QTextCursor::Document);

            QTextCharFormat format;
            format.setForeground(color);

            cursor.mergeCharFormat(format);
            cursor.clearSelection();

            displayTextEdit->setTextCursor(cursor);
            displayTextEdit->setTextColor(color);
        }
    }






    }


CBuildinDlg::~CBuildinDlg() = default;
