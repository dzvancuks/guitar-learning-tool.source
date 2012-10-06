/********************************************************************************
** Form generated from reading UI file 'Scholar.ui'
**
** Created: Sat 6. Oct 13:26:22 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCHOLAR_H
#define UI_SCHOLAR_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QGraphicsView>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSlider>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Scholar
{
public:
    QAction *actionOpen;
    QAction *actionHelp;
    QAction *actionAbout;
    QAction *actionExit;
    QAction *actionTuner;
    QAction *actionOptions;
    QWidget *centralwidget;
    QRadioButton *ScholarGuitarSignal;
    QFrame *ScholarControlFrame;
    QPushButton *ScholarPlayState;
    QSlider *ScholarBPM;
    QLabel *ScholarBPMlbl;
    QLabel *ScholarMetronomeLbl;
    QRadioButton *ScholarMetronomeOn;
    QRadioButton *ScholarMetronomeOff;
    QLineEdit *ScholarBPMvalue;
    QGraphicsView *ScholarMainView;
    QFrame *ScholarSoundEffecrFrame1;
    QFrame *ScholarSoundEffecrFrame2;
    QFrame *ScholarSoundEffecrFrame3;
    QSlider *ScholarVolumeLvl;
    QFrame *ScholarBgSoundFrame;
    QRadioButton *ScholarBgSoundOn;
    QRadioButton *ScholarBgSoundOff;
    QLabel *ScholarBGMusicLbl;
    QLabel *ScholarBGMusicNameLbl;
    QFrame *ScholarAudioVisualHelperFrame;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuTools;
    QMenu *menu;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Scholar)
    {
        if (Scholar->objectName().isEmpty())
            Scholar->setObjectName(QString::fromUtf8("Scholar"));
        Scholar->resize(1000, 500);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Scholar->sizePolicy().hasHeightForWidth());
        Scholar->setSizePolicy(sizePolicy);
        Scholar->setMinimumSize(QSize(1000, 500));
        Scholar->setMaximumSize(QSize(1000, 500));
        actionOpen = new QAction(Scholar);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        actionHelp = new QAction(Scholar);
        actionHelp->setObjectName(QString::fromUtf8("actionHelp"));
        actionAbout = new QAction(Scholar);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        actionExit = new QAction(Scholar);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        actionTuner = new QAction(Scholar);
        actionTuner->setObjectName(QString::fromUtf8("actionTuner"));
        actionOptions = new QAction(Scholar);
        actionOptions->setObjectName(QString::fromUtf8("actionOptions"));
        centralwidget = new QWidget(Scholar);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        ScholarGuitarSignal = new QRadioButton(centralwidget);
        ScholarGuitarSignal->setObjectName(QString::fromUtf8("ScholarGuitarSignal"));
        ScholarGuitarSignal->setGeometry(QRect(10, 390, 16, 17));
        ScholarGuitarSignal->setCheckable(true);
        ScholarGuitarSignal->setChecked(false);
        ScholarControlFrame = new QFrame(centralwidget);
        ScholarControlFrame->setObjectName(QString::fromUtf8("ScholarControlFrame"));
        ScholarControlFrame->setGeometry(QRect(160, 360, 291, 71));
        ScholarControlFrame->setFrameShape(QFrame::StyledPanel);
        ScholarControlFrame->setFrameShadow(QFrame::Raised);
        ScholarPlayState = new QPushButton(ScholarControlFrame);
        ScholarPlayState->setObjectName(QString::fromUtf8("ScholarPlayState"));
        ScholarPlayState->setGeometry(QRect(10, 20, 75, 23));
        ScholarBPM = new QSlider(ScholarControlFrame);
        ScholarBPM->setObjectName(QString::fromUtf8("ScholarBPM"));
        ScholarBPM->setGeometry(QRect(120, 30, 101, 20));
        ScholarBPM->setMinimum(20);
        ScholarBPM->setMaximum(240);
        ScholarBPM->setValue(80);
        ScholarBPM->setOrientation(Qt::Horizontal);
        ScholarBPMlbl = new QLabel(ScholarControlFrame);
        ScholarBPMlbl->setObjectName(QString::fromUtf8("ScholarBPMlbl"));
        ScholarBPMlbl->setGeometry(QRect(120, 0, 31, 21));
        ScholarMetronomeLbl = new QLabel(ScholarControlFrame);
        ScholarMetronomeLbl->setObjectName(QString::fromUtf8("ScholarMetronomeLbl"));
        ScholarMetronomeLbl->setGeometry(QRect(230, 0, 61, 16));
        ScholarMetronomeOn = new QRadioButton(ScholarControlFrame);
        ScholarMetronomeOn->setObjectName(QString::fromUtf8("ScholarMetronomeOn"));
        ScholarMetronomeOn->setGeometry(QRect(230, 20, 51, 17));
        ScholarMetronomeOff = new QRadioButton(ScholarControlFrame);
        ScholarMetronomeOff->setObjectName(QString::fromUtf8("ScholarMetronomeOff"));
        ScholarMetronomeOff->setGeometry(QRect(230, 40, 51, 17));
        ScholarMetronomeOff->setChecked(true);
        ScholarBPMvalue = new QLineEdit(ScholarControlFrame);
        ScholarBPMvalue->setObjectName(QString::fromUtf8("ScholarBPMvalue"));
        ScholarBPMvalue->setGeometry(QRect(150, 0, 51, 20));
        ScholarMainView = new QGraphicsView(centralwidget);
        ScholarMainView->setObjectName(QString::fromUtf8("ScholarMainView"));
        ScholarMainView->setGeometry(QRect(0, 40, 991, 281));
        ScholarMainView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        ScholarMainView->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        ScholarMainView->setInteractive(false);
        ScholarSoundEffecrFrame1 = new QFrame(centralwidget);
        ScholarSoundEffecrFrame1->setObjectName(QString::fromUtf8("ScholarSoundEffecrFrame1"));
        ScholarSoundEffecrFrame1->setGeometry(QRect(550, 350, 71, 91));
        ScholarSoundEffecrFrame1->setFrameShape(QFrame::StyledPanel);
        ScholarSoundEffecrFrame1->setFrameShadow(QFrame::Raised);
        ScholarSoundEffecrFrame2 = new QFrame(centralwidget);
        ScholarSoundEffecrFrame2->setObjectName(QString::fromUtf8("ScholarSoundEffecrFrame2"));
        ScholarSoundEffecrFrame2->setGeometry(QRect(660, 350, 71, 91));
        ScholarSoundEffecrFrame2->setFrameShape(QFrame::StyledPanel);
        ScholarSoundEffecrFrame2->setFrameShadow(QFrame::Raised);
        ScholarSoundEffecrFrame3 = new QFrame(centralwidget);
        ScholarSoundEffecrFrame3->setObjectName(QString::fromUtf8("ScholarSoundEffecrFrame3"));
        ScholarSoundEffecrFrame3->setGeometry(QRect(770, 350, 71, 91));
        ScholarSoundEffecrFrame3->setFrameShape(QFrame::StyledPanel);
        ScholarSoundEffecrFrame3->setFrameShadow(QFrame::Raised);
        ScholarVolumeLvl = new QSlider(centralwidget);
        ScholarVolumeLvl->setObjectName(QString::fromUtf8("ScholarVolumeLvl"));
        ScholarVolumeLvl->setGeometry(QRect(960, 350, 20, 91));
        ScholarVolumeLvl->setValue(50);
        ScholarVolumeLvl->setOrientation(Qt::Vertical);
        ScholarBgSoundFrame = new QFrame(centralwidget);
        ScholarBgSoundFrame->setObjectName(QString::fromUtf8("ScholarBgSoundFrame"));
        ScholarBgSoundFrame->setGeometry(QRect(10, 10, 491, 21));
        ScholarBgSoundFrame->setFrameShape(QFrame::StyledPanel);
        ScholarBgSoundFrame->setFrameShadow(QFrame::Raised);
        ScholarBgSoundOn = new QRadioButton(ScholarBgSoundFrame);
        ScholarBgSoundOn->setObjectName(QString::fromUtf8("ScholarBgSoundOn"));
        ScholarBgSoundOn->setGeometry(QRect(70, 0, 41, 21));
        ScholarBgSoundOff = new QRadioButton(ScholarBgSoundFrame);
        ScholarBgSoundOff->setObjectName(QString::fromUtf8("ScholarBgSoundOff"));
        ScholarBgSoundOff->setGeometry(QRect(130, 0, 41, 21));
        ScholarBgSoundOff->setChecked(true);
        ScholarBGMusicLbl = new QLabel(ScholarBgSoundFrame);
        ScholarBGMusicLbl->setObjectName(QString::fromUtf8("ScholarBGMusicLbl"));
        ScholarBGMusicLbl->setGeometry(QRect(10, 0, 61, 21));
        ScholarBGMusicNameLbl = new QLabel(ScholarBgSoundFrame);
        ScholarBGMusicNameLbl->setObjectName(QString::fromUtf8("ScholarBGMusicNameLbl"));
        ScholarBGMusicNameLbl->setGeometry(QRect(180, 0, 301, 21));
        ScholarAudioVisualHelperFrame = new QFrame(centralwidget);
        ScholarAudioVisualHelperFrame->setObjectName(QString::fromUtf8("ScholarAudioVisualHelperFrame"));
        ScholarAudioVisualHelperFrame->setEnabled(false);
        ScholarAudioVisualHelperFrame->setGeometry(QRect(760, 40, 231, 271));
        ScholarAudioVisualHelperFrame->setFrameShape(QFrame::StyledPanel);
        ScholarAudioVisualHelperFrame->setFrameShadow(QFrame::Raised);
        Scholar->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Scholar);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1000, 21));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuTools = new QMenu(menubar);
        menuTools->setObjectName(QString::fromUtf8("menuTools"));
        menu = new QMenu(menubar);
        menu->setObjectName(QString::fromUtf8("menu"));
        Scholar->setMenuBar(menubar);
        statusbar = new QStatusBar(Scholar);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        Scholar->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuTools->menuAction());
        menubar->addAction(menu->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuTools->addAction(actionTuner);
        menuTools->addSeparator();
        menuTools->addAction(actionOptions);
        menu->addAction(actionHelp);
        menu->addAction(actionAbout);

        retranslateUi(Scholar);
        QObject::connect(actionExit, SIGNAL(triggered()), Scholar, SLOT(close()));

        QMetaObject::connectSlotsByName(Scholar);
    } // setupUi

    void retranslateUi(QMainWindow *Scholar)
    {
        Scholar->setWindowTitle(QApplication::translate("Scholar", "Scholar", 0, QApplication::UnicodeUTF8));
        actionOpen->setText(QApplication::translate("Scholar", "Open", 0, QApplication::UnicodeUTF8));
        actionHelp->setText(QApplication::translate("Scholar", "Help", 0, QApplication::UnicodeUTF8));
        actionAbout->setText(QApplication::translate("Scholar", "About", 0, QApplication::UnicodeUTF8));
        actionExit->setText(QApplication::translate("Scholar", "Exit", 0, QApplication::UnicodeUTF8));
        actionTuner->setText(QApplication::translate("Scholar", "Tuner", 0, QApplication::UnicodeUTF8));
        actionOptions->setText(QApplication::translate("Scholar", "Options", 0, QApplication::UnicodeUTF8));
        ScholarGuitarSignal->setText(QString());
        ScholarPlayState->setText(QApplication::translate("Scholar", "Paused", 0, QApplication::UnicodeUTF8));
        ScholarBPMlbl->setText(QApplication::translate("Scholar", "BPM:", 0, QApplication::UnicodeUTF8));
        ScholarMetronomeLbl->setText(QApplication::translate("Scholar", "Metronome", 0, QApplication::UnicodeUTF8));
        ScholarMetronomeOn->setText(QApplication::translate("Scholar", "On", 0, QApplication::UnicodeUTF8));
        ScholarMetronomeOff->setText(QApplication::translate("Scholar", "Off", 0, QApplication::UnicodeUTF8));
        ScholarBPMvalue->setInputMask(QApplication::translate("Scholar", "990; ", 0, QApplication::UnicodeUTF8));
        ScholarBPMvalue->setText(QString());
        ScholarBPMvalue->setPlaceholderText(QApplication::translate("Scholar", "20..240", 0, QApplication::UnicodeUTF8));
        ScholarBgSoundOn->setText(QApplication::translate("Scholar", "On", 0, QApplication::UnicodeUTF8));
        ScholarBgSoundOff->setText(QApplication::translate("Scholar", "Off", 0, QApplication::UnicodeUTF8));
        ScholarBGMusicLbl->setText(QApplication::translate("Scholar", "BG music:", 0, QApplication::UnicodeUTF8));
        ScholarBGMusicNameLbl->setText(QString());
        menuFile->setTitle(QApplication::translate("Scholar", "File", 0, QApplication::UnicodeUTF8));
        menuTools->setTitle(QApplication::translate("Scholar", "Tools", 0, QApplication::UnicodeUTF8));
        menu->setTitle(QApplication::translate("Scholar", "?", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Scholar: public Ui_Scholar {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCHOLAR_H
