/********************************************************************************
** Form generated from reading UI file 'Tuner.ui'
**
** Created: Sat 5. Jan 20:07:31 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TUNER_H
#define UI_TUNER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QFrame>
#include <QtGui/QGraphicsView>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Tuner
{
public:
    QAction *actionTumerDone;
    QPushButton *TunerDone;
    QFrame *TunerDataFrame;
    QGraphicsView *TunerVisual;
    QLabel *TunerFreq;
    QLabel *TunerNote;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QComboBox *TunerGuitarMenu;

    void setupUi(QDialog *Tuner)
    {
        if (Tuner->objectName().isEmpty())
            Tuner->setObjectName(QString::fromUtf8("Tuner"));
        Tuner->resize(450, 400);
        Tuner->setMinimumSize(QSize(450, 400));
        Tuner->setMaximumSize(QSize(450, 400));
        actionTumerDone = new QAction(Tuner);
        actionTumerDone->setObjectName(QString::fromUtf8("actionTumerDone"));
        TunerDone = new QPushButton(Tuner);
        TunerDone->setObjectName(QString::fromUtf8("TunerDone"));
        TunerDone->setGeometry(QRect(120, 340, 201, 31));
        TunerDataFrame = new QFrame(Tuner);
        TunerDataFrame->setObjectName(QString::fromUtf8("TunerDataFrame"));
        TunerDataFrame->setGeometry(QRect(10, 40, 431, 281));
        TunerDataFrame->setFrameShape(QFrame::StyledPanel);
        TunerDataFrame->setFrameShadow(QFrame::Raised);
        TunerVisual = new QGraphicsView(TunerDataFrame);
        TunerVisual->setObjectName(QString::fromUtf8("TunerVisual"));
        TunerVisual->setGeometry(QRect(185, 1, 241, 211));
        TunerFreq = new QLabel(TunerDataFrame);
        TunerFreq->setObjectName(QString::fromUtf8("TunerFreq"));
        TunerFreq->setGeometry(QRect(80, 230, 101, 41));
        QFont font;
        font.setPointSize(18);
        TunerFreq->setFont(font);
        TunerNote = new QLabel(TunerDataFrame);
        TunerNote->setObjectName(QString::fromUtf8("TunerNote"));
        TunerNote->setGeometry(QRect(240, 230, 51, 41));
        QFont font1;
        font1.setPointSize(22);
        TunerNote->setFont(font1);
        TunerNote->setFrameShadow(QFrame::Plain);
        gridLayoutWidget = new QWidget(TunerDataFrame);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(0, 0, 181, 211));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        TunerGuitarMenu = new QComboBox(Tuner);
        TunerGuitarMenu->setObjectName(QString::fromUtf8("TunerGuitarMenu"));
        TunerGuitarMenu->setGeometry(QRect(10, 10, 161, 22));

        retranslateUi(Tuner);
        QObject::connect(TunerDone, SIGNAL(clicked()), Tuner, SLOT(close()));

        QMetaObject::connectSlotsByName(Tuner);
    } // setupUi

    void retranslateUi(QDialog *Tuner)
    {
        Tuner->setWindowTitle(QApplication::translate("Tuner", "Tuner", 0, QApplication::UnicodeUTF8));
        actionTumerDone->setText(QApplication::translate("Tuner", "TumerDone", 0, QApplication::UnicodeUTF8));
        TunerDone->setText(QApplication::translate("Tuner", "Done", 0, QApplication::UnicodeUTF8));
        TunerFreq->setText(QString());
        TunerNote->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Tuner: public Ui_Tuner {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TUNER_H
