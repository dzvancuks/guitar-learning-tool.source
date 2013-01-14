/********************************************************************************
** Form generated from reading UI file 'Tutor.ui'
**
** Created: Sat 5. Jan 20:07:31 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TUTOR_H
#define UI_TUTOR_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
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
#include <QtGui/QSpinBox>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Tutor
{
public:
    QAction *actionNew;
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionSave_As;
    QAction *actionExit;
    QAction *actionOptions;
    QAction *actionHelp;
    QAction *actionAbout;
    QAction *actionScholar;
    QWidget *centralwidget;
    QGraphicsView *TutorMainView;
    QFrame *TutorBgSoundFrame;
    QLabel *TutorBGMusicLbl;
    QLabel *ScholarBGMusicNameLbl;
    QPushButton *TutorBGMusicSelectBtn;
    QSlider *TutorVolumeLvl;
    QFrame *TutorVideoFrame;
    QLabel *TutorVideoLbl;
    QLabel *TutorVideoNameLbl;
    QPushButton *TutorVideoSelectBtn;
    QFrame *TutorEditorFrame;
    QFrame *TrackEditFrame;
    QLabel *TrackLbl;
    QLabel *TrackBeatCountLbl;
    QLabel *TrackBeatLengthLbl;
    QLabel *TrackBPMLbl;
    QSpinBox *TrackBeatCountVal;
    QSpinBox *TrackBeatLengthVal;
    QSpinBox *TrackBPMVal;
    QLabel *TrackClefLbl;
    QComboBox *TrackClefVal;
    QPushButton *TrackPlayBtn;
    QFrame *BarEditFrame;
    QLabel *BarLbl;
    QPushButton *BarAddBtn;
    QPushButton *BarRemoveBtn;
    QPushButton *BarShiftLeftBtn;
    QPushButton *BarShiftRightBtn;
    QLabel *BarRepeatStartLbl;
    QCheckBox *BarRepeatStartVal;
    QLabel *BarRepeatCountLbl;
    QSpinBox *BarRepeatCountVal;
    QLabel *BarChordLbl;
    QLineEdit *BarChordVal;
    QLabel *BarRepeatNextEndLbl;
    QCheckBox *BarRepeatNextEndVal;
    QPushButton *BarPlayBtn;
    QFrame *NoteEditFrame;
    QLabel *NoteLbl;
    QLabel *NoteLengthLbl;
    QSpinBox *NoteLengthVal;
    QLabel *NoteExtensionLbl;
    QSpinBox *NoteExtensionVal;
    QLabel *NoteContinueLbl;
    QCheckBox *NoteContinueVal;
    QCheckBox *NoteSlideVal;
    QLabel *NoteSlideLbl;
    QCheckBox *NoteVibratoVal;
    QLabel *NoteVibratoLbl;
    QFrame *NoteHOPOFrame;
    QLabel *NotePOLbl;
    QLabel *NoteHOLbl;
    QRadioButton *NoteHORadio;
    QRadioButton *NotePORadio;
    QRadioButton *NoteHOPOOffRadio;
    QLabel *NoteUngrouppingLbl;
    QLabel *NoteGrouppingLbl;
    QSpinBox *NoteGrouppingVal;
    QSpinBox *NoteUngrouppingVal;
    QPushButton *NoteAddBtn;
    QPushButton *NoteRemoveBtn;
    QPushButton *NoteShiftRightBtn;
    QPushButton *NoteShiftLeftBtn;
    QFrame *ToneFrame;
    QLabel *ToneLbl;
    QPushButton *ToneAddBtn;
    QPushButton *ToneRemoveBtn;
    QPushButton *ToneDownBtn;
    QPushButton *ToneUpBtn;
    QLabel *ToneStringLbl;
    QComboBox *ToneStringVal;
    QLabel *ToneRestLbl;
    QCheckBox *ToneRestVal;
    QPushButton *NotePlayBtn;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuTools;
    QMenu *menu;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Tutor)
    {
        if (Tutor->objectName().isEmpty())
            Tutor->setObjectName(QString::fromUtf8("Tutor"));
        Tutor->resize(1000, 500);
        Tutor->setMinimumSize(QSize(1000, 500));
        Tutor->setMaximumSize(QSize(1000, 500));
        actionNew = new QAction(Tutor);
        actionNew->setObjectName(QString::fromUtf8("actionNew"));
        actionOpen = new QAction(Tutor);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        actionSave = new QAction(Tutor);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        actionSave_As = new QAction(Tutor);
        actionSave_As->setObjectName(QString::fromUtf8("actionSave_As"));
        actionExit = new QAction(Tutor);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        actionOptions = new QAction(Tutor);
        actionOptions->setObjectName(QString::fromUtf8("actionOptions"));
        actionHelp = new QAction(Tutor);
        actionHelp->setObjectName(QString::fromUtf8("actionHelp"));
        actionAbout = new QAction(Tutor);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        actionScholar = new QAction(Tutor);
        actionScholar->setObjectName(QString::fromUtf8("actionScholar"));
        centralwidget = new QWidget(Tutor);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        TutorMainView = new QGraphicsView(centralwidget);
        TutorMainView->setObjectName(QString::fromUtf8("TutorMainView"));
        TutorMainView->setGeometry(QRect(0, 40, 991, 281));
        TutorMainView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        TutorMainView->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        TutorMainView->setInteractive(true);
        TutorBgSoundFrame = new QFrame(centralwidget);
        TutorBgSoundFrame->setObjectName(QString::fromUtf8("TutorBgSoundFrame"));
        TutorBgSoundFrame->setGeometry(QRect(10, 10, 461, 21));
        TutorBgSoundFrame->setFrameShape(QFrame::StyledPanel);
        TutorBgSoundFrame->setFrameShadow(QFrame::Raised);
        TutorBGMusicLbl = new QLabel(TutorBgSoundFrame);
        TutorBGMusicLbl->setObjectName(QString::fromUtf8("TutorBGMusicLbl"));
        TutorBGMusicLbl->setGeometry(QRect(0, 0, 61, 21));
        ScholarBGMusicNameLbl = new QLabel(TutorBgSoundFrame);
        ScholarBGMusicNameLbl->setObjectName(QString::fromUtf8("ScholarBGMusicNameLbl"));
        ScholarBGMusicNameLbl->setGeometry(QRect(150, 0, 301, 21));
        TutorBGMusicSelectBtn = new QPushButton(TutorBgSoundFrame);
        TutorBGMusicSelectBtn->setObjectName(QString::fromUtf8("TutorBGMusicSelectBtn"));
        TutorBGMusicSelectBtn->setGeometry(QRect(60, 0, 75, 23));
        TutorVolumeLvl = new QSlider(centralwidget);
        TutorVolumeLvl->setObjectName(QString::fromUtf8("TutorVolumeLvl"));
        TutorVolumeLvl->setGeometry(QRect(960, 350, 20, 91));
        TutorVolumeLvl->setValue(50);
        TutorVolumeLvl->setOrientation(Qt::Vertical);
        TutorVideoFrame = new QFrame(centralwidget);
        TutorVideoFrame->setObjectName(QString::fromUtf8("TutorVideoFrame"));
        TutorVideoFrame->setGeometry(QRect(510, 10, 461, 21));
        TutorVideoFrame->setFrameShape(QFrame::StyledPanel);
        TutorVideoFrame->setFrameShadow(QFrame::Raised);
        TutorVideoLbl = new QLabel(TutorVideoFrame);
        TutorVideoLbl->setObjectName(QString::fromUtf8("TutorVideoLbl"));
        TutorVideoLbl->setGeometry(QRect(10, 0, 51, 21));
        TutorVideoNameLbl = new QLabel(TutorVideoFrame);
        TutorVideoNameLbl->setObjectName(QString::fromUtf8("TutorVideoNameLbl"));
        TutorVideoNameLbl->setGeometry(QRect(150, 0, 301, 21));
        TutorVideoSelectBtn = new QPushButton(TutorVideoFrame);
        TutorVideoSelectBtn->setObjectName(QString::fromUtf8("TutorVideoSelectBtn"));
        TutorVideoSelectBtn->setGeometry(QRect(60, 0, 75, 23));
        TutorEditorFrame = new QFrame(centralwidget);
        TutorEditorFrame->setObjectName(QString::fromUtf8("TutorEditorFrame"));
        TutorEditorFrame->setGeometry(QRect(10, 330, 921, 121));
        TutorEditorFrame->setFrameShape(QFrame::StyledPanel);
        TutorEditorFrame->setFrameShadow(QFrame::Raised);
        TrackEditFrame = new QFrame(TutorEditorFrame);
        TrackEditFrame->setObjectName(QString::fromUtf8("TrackEditFrame"));
        TrackEditFrame->setGeometry(QRect(20, 0, 141, 121));
        TrackEditFrame->setFrameShape(QFrame::Box);
        TrackEditFrame->setFrameShadow(QFrame::Raised);
        TrackLbl = new QLabel(TrackEditFrame);
        TrackLbl->setObjectName(QString::fromUtf8("TrackLbl"));
        TrackLbl->setGeometry(QRect(10, 0, 61, 21));
        QFont font;
        font.setPointSize(10);
        font.setBold(true);
        font.setWeight(75);
        TrackLbl->setFont(font);
        TrackLbl->setTextFormat(Qt::AutoText);
        TrackLbl->setAlignment(Qt::AlignCenter);
        TrackBeatCountLbl = new QLabel(TrackEditFrame);
        TrackBeatCountLbl->setObjectName(QString::fromUtf8("TrackBeatCountLbl"));
        TrackBeatCountLbl->setGeometry(QRect(10, 30, 61, 16));
        TrackBeatCountLbl->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        TrackBeatLengthLbl = new QLabel(TrackEditFrame);
        TrackBeatLengthLbl->setObjectName(QString::fromUtf8("TrackBeatLengthLbl"));
        TrackBeatLengthLbl->setGeometry(QRect(10, 50, 61, 16));
        TrackBeatLengthLbl->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        TrackBPMLbl = new QLabel(TrackEditFrame);
        TrackBPMLbl->setObjectName(QString::fromUtf8("TrackBPMLbl"));
        TrackBPMLbl->setGeometry(QRect(10, 70, 61, 16));
        TrackBPMLbl->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        TrackBeatCountVal = new QSpinBox(TrackEditFrame);
        TrackBeatCountVal->setObjectName(QString::fromUtf8("TrackBeatCountVal"));
        TrackBeatCountVal->setGeometry(QRect(90, 30, 41, 20));
        TrackBeatCountVal->setMinimum(1);
        TrackBeatLengthVal = new QSpinBox(TrackEditFrame);
        TrackBeatLengthVal->setObjectName(QString::fromUtf8("TrackBeatLengthVal"));
        TrackBeatLengthVal->setGeometry(QRect(90, 50, 41, 20));
        TrackBeatLengthVal->setMinimum(1);
        TrackBeatLengthVal->setMaximum(64);
        TrackBeatLengthVal->setValue(1);
        TrackBPMVal = new QSpinBox(TrackEditFrame);
        TrackBPMVal->setObjectName(QString::fromUtf8("TrackBPMVal"));
        TrackBPMVal->setGeometry(QRect(90, 70, 41, 20));
        TrackBPMVal->setMinimum(20);
        TrackBPMVal->setMaximum(240);
        TrackBPMVal->setValue(80);
        TrackClefLbl = new QLabel(TrackEditFrame);
        TrackClefLbl->setObjectName(QString::fromUtf8("TrackClefLbl"));
        TrackClefLbl->setGeometry(QRect(10, 90, 61, 16));
        TrackClefLbl->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        TrackClefVal = new QComboBox(TrackEditFrame);
        TrackClefVal->setObjectName(QString::fromUtf8("TrackClefVal"));
        TrackClefVal->setGeometry(QRect(80, 90, 61, 16));
        TrackPlayBtn = new QPushButton(TrackEditFrame);
        TrackPlayBtn->setObjectName(QString::fromUtf8("TrackPlayBtn"));
        TrackPlayBtn->setEnabled(true);
        TrackPlayBtn->setGeometry(QRect(80, 0, 51, 20));
        BarEditFrame = new QFrame(TutorEditorFrame);
        BarEditFrame->setObjectName(QString::fromUtf8("BarEditFrame"));
        BarEditFrame->setEnabled(true);
        BarEditFrame->setGeometry(QRect(190, 0, 221, 121));
        BarEditFrame->setFrameShape(QFrame::Box);
        BarEditFrame->setFrameShadow(QFrame::Raised);
        BarLbl = new QLabel(BarEditFrame);
        BarLbl->setObjectName(QString::fromUtf8("BarLbl"));
        BarLbl->setGeometry(QRect(0, 0, 71, 21));
        BarLbl->setFont(font);
        BarLbl->setAlignment(Qt::AlignCenter);
        BarAddBtn = new QPushButton(BarEditFrame);
        BarAddBtn->setObjectName(QString::fromUtf8("BarAddBtn"));
        BarAddBtn->setGeometry(QRect(0, 30, 31, 23));
        BarRemoveBtn = new QPushButton(BarEditFrame);
        BarRemoveBtn->setObjectName(QString::fromUtf8("BarRemoveBtn"));
        BarRemoveBtn->setEnabled(false);
        BarRemoveBtn->setGeometry(QRect(40, 30, 31, 23));
        BarShiftLeftBtn = new QPushButton(BarEditFrame);
        BarShiftLeftBtn->setObjectName(QString::fromUtf8("BarShiftLeftBtn"));
        BarShiftLeftBtn->setEnabled(false);
        BarShiftLeftBtn->setGeometry(QRect(0, 60, 31, 23));
        BarShiftRightBtn = new QPushButton(BarEditFrame);
        BarShiftRightBtn->setObjectName(QString::fromUtf8("BarShiftRightBtn"));
        BarShiftRightBtn->setEnabled(false);
        BarShiftRightBtn->setGeometry(QRect(40, 60, 31, 23));
        BarRepeatStartLbl = new QLabel(BarEditFrame);
        BarRepeatStartLbl->setObjectName(QString::fromUtf8("BarRepeatStartLbl"));
        BarRepeatStartLbl->setEnabled(true);
        BarRepeatStartLbl->setGeometry(QRect(100, 30, 71, 16));
        BarRepeatStartLbl->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        BarRepeatStartVal = new QCheckBox(BarEditFrame);
        BarRepeatStartVal->setObjectName(QString::fromUtf8("BarRepeatStartVal"));
        BarRepeatStartVal->setEnabled(false);
        BarRepeatStartVal->setGeometry(QRect(190, 30, 16, 17));
        BarRepeatCountLbl = new QLabel(BarEditFrame);
        BarRepeatCountLbl->setObjectName(QString::fromUtf8("BarRepeatCountLbl"));
        BarRepeatCountLbl->setEnabled(true);
        BarRepeatCountLbl->setGeometry(QRect(100, 50, 71, 16));
        BarRepeatCountLbl->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        BarRepeatCountVal = new QSpinBox(BarEditFrame);
        BarRepeatCountVal->setObjectName(QString::fromUtf8("BarRepeatCountVal"));
        BarRepeatCountVal->setEnabled(false);
        BarRepeatCountVal->setGeometry(QRect(180, 50, 41, 16));
        BarRepeatCountVal->setMinimum(1);
        BarChordLbl = new QLabel(BarEditFrame);
        BarChordLbl->setObjectName(QString::fromUtf8("BarChordLbl"));
        BarChordLbl->setEnabled(true);
        BarChordLbl->setGeometry(QRect(20, 100, 46, 13));
        BarChordLbl->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        BarChordVal = new QLineEdit(BarEditFrame);
        BarChordVal->setObjectName(QString::fromUtf8("BarChordVal"));
        BarChordVal->setEnabled(false);
        BarChordVal->setGeometry(QRect(80, 100, 131, 16));
        BarChordVal->setMaxLength(20);
        BarRepeatNextEndLbl = new QLabel(BarEditFrame);
        BarRepeatNextEndLbl->setObjectName(QString::fromUtf8("BarRepeatNextEndLbl"));
        BarRepeatNextEndLbl->setEnabled(true);
        BarRepeatNextEndLbl->setGeometry(QRect(90, 70, 81, 16));
        BarRepeatNextEndLbl->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        BarRepeatNextEndVal = new QCheckBox(BarEditFrame);
        BarRepeatNextEndVal->setObjectName(QString::fromUtf8("BarRepeatNextEndVal"));
        BarRepeatNextEndVal->setGeometry(QRect(190, 70, 16, 17));
        BarPlayBtn = new QPushButton(BarEditFrame);
        BarPlayBtn->setObjectName(QString::fromUtf8("BarPlayBtn"));
        BarPlayBtn->setEnabled(true);
        BarPlayBtn->setGeometry(QRect(110, 0, 51, 20));
        NoteEditFrame = new QFrame(TutorEditorFrame);
        NoteEditFrame->setObjectName(QString::fromUtf8("NoteEditFrame"));
        NoteEditFrame->setEnabled(true);
        NoteEditFrame->setGeometry(QRect(450, 0, 451, 121));
        NoteEditFrame->setFrameShape(QFrame::Box);
        NoteEditFrame->setFrameShadow(QFrame::Raised);
        NoteLbl = new QLabel(NoteEditFrame);
        NoteLbl->setObjectName(QString::fromUtf8("NoteLbl"));
        NoteLbl->setEnabled(true);
        NoteLbl->setGeometry(QRect(0, 0, 81, 16));
        NoteLbl->setFont(font);
        NoteLbl->setAlignment(Qt::AlignCenter);
        NoteLengthLbl = new QLabel(NoteEditFrame);
        NoteLengthLbl->setObjectName(QString::fromUtf8("NoteLengthLbl"));
        NoteLengthLbl->setEnabled(true);
        NoteLengthLbl->setGeometry(QRect(5, 80, 51, 16));
        NoteLengthLbl->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        NoteLengthVal = new QSpinBox(NoteEditFrame);
        NoteLengthVal->setObjectName(QString::fromUtf8("NoteLengthVal"));
        NoteLengthVal->setEnabled(false);
        NoteLengthVal->setGeometry(QRect(60, 80, 41, 16));
        NoteLengthVal->setMinimum(1);
        NoteLengthVal->setMaximum(64);
        NoteExtensionLbl = new QLabel(NoteEditFrame);
        NoteExtensionLbl->setObjectName(QString::fromUtf8("NoteExtensionLbl"));
        NoteExtensionLbl->setEnabled(true);
        NoteExtensionLbl->setGeometry(QRect(5, 100, 51, 16));
        NoteExtensionLbl->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        NoteExtensionVal = new QSpinBox(NoteEditFrame);
        NoteExtensionVal->setObjectName(QString::fromUtf8("NoteExtensionVal"));
        NoteExtensionVal->setEnabled(false);
        NoteExtensionVal->setGeometry(QRect(60, 100, 41, 16));
        NoteExtensionVal->setMinimum(0);
        NoteExtensionVal->setMaximum(2);
        NoteExtensionVal->setValue(0);
        NoteContinueLbl = new QLabel(NoteEditFrame);
        NoteContinueLbl->setObjectName(QString::fromUtf8("NoteContinueLbl"));
        NoteContinueLbl->setEnabled(true);
        NoteContinueLbl->setGeometry(QRect(100, 30, 71, 16));
        NoteContinueLbl->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        NoteContinueVal = new QCheckBox(NoteEditFrame);
        NoteContinueVal->setObjectName(QString::fromUtf8("NoteContinueVal"));
        NoteContinueVal->setEnabled(false);
        NoteContinueVal->setGeometry(QRect(180, 30, 16, 17));
        NoteSlideVal = new QCheckBox(NoteEditFrame);
        NoteSlideVal->setObjectName(QString::fromUtf8("NoteSlideVal"));
        NoteSlideVal->setEnabled(false);
        NoteSlideVal->setGeometry(QRect(180, 50, 16, 17));
        NoteSlideLbl = new QLabel(NoteEditFrame);
        NoteSlideLbl->setObjectName(QString::fromUtf8("NoteSlideLbl"));
        NoteSlideLbl->setEnabled(true);
        NoteSlideLbl->setGeometry(QRect(100, 50, 71, 16));
        NoteSlideLbl->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        NoteVibratoVal = new QCheckBox(NoteEditFrame);
        NoteVibratoVal->setObjectName(QString::fromUtf8("NoteVibratoVal"));
        NoteVibratoVal->setEnabled(false);
        NoteVibratoVal->setGeometry(QRect(180, 70, 16, 17));
        NoteVibratoLbl = new QLabel(NoteEditFrame);
        NoteVibratoLbl->setObjectName(QString::fromUtf8("NoteVibratoLbl"));
        NoteVibratoLbl->setEnabled(true);
        NoteVibratoLbl->setGeometry(QRect(100, 70, 71, 16));
        NoteVibratoLbl->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        NoteHOPOFrame = new QFrame(NoteEditFrame);
        NoteHOPOFrame->setObjectName(QString::fromUtf8("NoteHOPOFrame"));
        NoteHOPOFrame->setEnabled(false);
        NoteHOPOFrame->setGeometry(QRect(160, 100, 101, 16));
        NoteHOPOFrame->setFrameShape(QFrame::StyledPanel);
        NoteHOPOFrame->setFrameShadow(QFrame::Raised);
        NotePOLbl = new QLabel(NoteHOPOFrame);
        NotePOLbl->setObjectName(QString::fromUtf8("NotePOLbl"));
        NotePOLbl->setGeometry(QRect(80, 0, 16, 16));
        NoteHOLbl = new QLabel(NoteHOPOFrame);
        NoteHOLbl->setObjectName(QString::fromUtf8("NoteHOLbl"));
        NoteHOLbl->setGeometry(QRect(0, 0, 16, 16));
        NoteHORadio = new QRadioButton(NoteHOPOFrame);
        NoteHORadio->setObjectName(QString::fromUtf8("NoteHORadio"));
        NoteHORadio->setGeometry(QRect(20, 0, 16, 17));
        NotePORadio = new QRadioButton(NoteHOPOFrame);
        NotePORadio->setObjectName(QString::fromUtf8("NotePORadio"));
        NotePORadio->setGeometry(QRect(60, 0, 16, 17));
        NoteHOPOOffRadio = new QRadioButton(NoteHOPOFrame);
        NoteHOPOOffRadio->setObjectName(QString::fromUtf8("NoteHOPOOffRadio"));
        NoteHOPOOffRadio->setGeometry(QRect(40, 0, 16, 17));
        NoteHOPOOffRadio->setChecked(true);
        NoteUngrouppingLbl = new QLabel(NoteEditFrame);
        NoteUngrouppingLbl->setObjectName(QString::fromUtf8("NoteUngrouppingLbl"));
        NoteUngrouppingLbl->setEnabled(true);
        NoteUngrouppingLbl->setGeometry(QRect(200, 60, 61, 16));
        NoteUngrouppingLbl->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        NoteGrouppingLbl = new QLabel(NoteEditFrame);
        NoteGrouppingLbl->setObjectName(QString::fromUtf8("NoteGrouppingLbl"));
        NoteGrouppingLbl->setEnabled(true);
        NoteGrouppingLbl->setGeometry(QRect(200, 40, 61, 16));
        NoteGrouppingLbl->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        NoteGrouppingVal = new QSpinBox(NoteEditFrame);
        NoteGrouppingVal->setObjectName(QString::fromUtf8("NoteGrouppingVal"));
        NoteGrouppingVal->setEnabled(false);
        NoteGrouppingVal->setGeometry(QRect(270, 40, 42, 16));
        NoteUngrouppingVal = new QSpinBox(NoteEditFrame);
        NoteUngrouppingVal->setObjectName(QString::fromUtf8("NoteUngrouppingVal"));
        NoteUngrouppingVal->setEnabled(false);
        NoteUngrouppingVal->setGeometry(QRect(270, 60, 42, 16));
        NoteAddBtn = new QPushButton(NoteEditFrame);
        NoteAddBtn->setObjectName(QString::fromUtf8("NoteAddBtn"));
        NoteAddBtn->setGeometry(QRect(10, 30, 31, 23));
        NoteRemoveBtn = new QPushButton(NoteEditFrame);
        NoteRemoveBtn->setObjectName(QString::fromUtf8("NoteRemoveBtn"));
        NoteRemoveBtn->setEnabled(false);
        NoteRemoveBtn->setGeometry(QRect(50, 30, 31, 23));
        NoteShiftRightBtn = new QPushButton(NoteEditFrame);
        NoteShiftRightBtn->setObjectName(QString::fromUtf8("NoteShiftRightBtn"));
        NoteShiftRightBtn->setEnabled(false);
        NoteShiftRightBtn->setGeometry(QRect(50, 50, 31, 23));
        NoteShiftLeftBtn = new QPushButton(NoteEditFrame);
        NoteShiftLeftBtn->setObjectName(QString::fromUtf8("NoteShiftLeftBtn"));
        NoteShiftLeftBtn->setEnabled(false);
        NoteShiftLeftBtn->setGeometry(QRect(10, 50, 31, 23));
        ToneFrame = new QFrame(NoteEditFrame);
        ToneFrame->setObjectName(QString::fromUtf8("ToneFrame"));
        ToneFrame->setEnabled(true);
        ToneFrame->setGeometry(QRect(320, 10, 111, 111));
        ToneFrame->setFrameShape(QFrame::Panel);
        ToneFrame->setFrameShadow(QFrame::Raised);
        ToneLbl = new QLabel(ToneFrame);
        ToneLbl->setObjectName(QString::fromUtf8("ToneLbl"));
        ToneLbl->setEnabled(true);
        ToneLbl->setGeometry(QRect(0, 0, 51, 16));
        QFont font1;
        font1.setPointSize(8);
        font1.setBold(true);
        font1.setWeight(75);
        ToneLbl->setFont(font1);
        ToneLbl->setAlignment(Qt::AlignCenter);
        ToneAddBtn = new QPushButton(ToneFrame);
        ToneAddBtn->setObjectName(QString::fromUtf8("ToneAddBtn"));
        ToneAddBtn->setGeometry(QRect(10, 40, 41, 23));
        ToneRemoveBtn = new QPushButton(ToneFrame);
        ToneRemoveBtn->setObjectName(QString::fromUtf8("ToneRemoveBtn"));
        ToneRemoveBtn->setGeometry(QRect(10, 60, 41, 23));
        ToneDownBtn = new QPushButton(ToneFrame);
        ToneDownBtn->setObjectName(QString::fromUtf8("ToneDownBtn"));
        ToneDownBtn->setGeometry(QRect(60, 60, 41, 23));
        ToneUpBtn = new QPushButton(ToneFrame);
        ToneUpBtn->setObjectName(QString::fromUtf8("ToneUpBtn"));
        ToneUpBtn->setGeometry(QRect(60, 40, 41, 23));
        ToneStringLbl = new QLabel(ToneFrame);
        ToneStringLbl->setObjectName(QString::fromUtf8("ToneStringLbl"));
        ToneStringLbl->setGeometry(QRect(10, 90, 31, 16));
        ToneStringVal = new QComboBox(ToneFrame);
        ToneStringVal->setObjectName(QString::fromUtf8("ToneStringVal"));
        ToneStringVal->setGeometry(QRect(50, 90, 51, 16));
        ToneStringVal->setMaxCount(12);
        ToneRestLbl = new QLabel(ToneFrame);
        ToneRestLbl->setObjectName(QString::fromUtf8("ToneRestLbl"));
        ToneRestLbl->setGeometry(QRect(20, 20, 31, 16));
        ToneRestVal = new QCheckBox(ToneFrame);
        ToneRestVal->setObjectName(QString::fromUtf8("ToneRestVal"));
        ToneRestVal->setEnabled(true);
        ToneRestVal->setGeometry(QRect(60, 20, 16, 17));
        NotePlayBtn = new QPushButton(NoteEditFrame);
        NotePlayBtn->setObjectName(QString::fromUtf8("NotePlayBtn"));
        NotePlayBtn->setEnabled(true);
        NotePlayBtn->setGeometry(QRect(160, 0, 51, 20));
        Tutor->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Tutor);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1000, 21));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuTools = new QMenu(menubar);
        menuTools->setObjectName(QString::fromUtf8("menuTools"));
        menu = new QMenu(menubar);
        menu->setObjectName(QString::fromUtf8("menu"));
        Tutor->setMenuBar(menubar);
        statusbar = new QStatusBar(Tutor);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        Tutor->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuTools->menuAction());
        menubar->addAction(menu->menuAction());
        menuFile->addAction(actionNew);
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSave);
        menuFile->addAction(actionSave_As);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuTools->addAction(actionScholar);
        menuTools->addSeparator();
        menuTools->addAction(actionOptions);
        menu->addAction(actionHelp);
        menu->addAction(actionAbout);

        retranslateUi(Tutor);
        QObject::connect(actionExit, SIGNAL(triggered()), Tutor, SLOT(close()));

        TrackClefVal->setCurrentIndex(0);
        ToneStringVal->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(Tutor);
    } // setupUi

    void retranslateUi(QMainWindow *Tutor)
    {
        Tutor->setWindowTitle(QApplication::translate("Tutor", "Tutor", 0, QApplication::UnicodeUTF8));
        actionNew->setText(QApplication::translate("Tutor", "New", 0, QApplication::UnicodeUTF8));
        actionOpen->setText(QApplication::translate("Tutor", "Open ...", 0, QApplication::UnicodeUTF8));
        actionSave->setText(QApplication::translate("Tutor", "Save", 0, QApplication::UnicodeUTF8));
        actionSave_As->setText(QApplication::translate("Tutor", "Save As ...", 0, QApplication::UnicodeUTF8));
        actionExit->setText(QApplication::translate("Tutor", "Exit", 0, QApplication::UnicodeUTF8));
        actionOptions->setText(QApplication::translate("Tutor", "Options", 0, QApplication::UnicodeUTF8));
        actionHelp->setText(QApplication::translate("Tutor", "Help", 0, QApplication::UnicodeUTF8));
        actionAbout->setText(QApplication::translate("Tutor", "About", 0, QApplication::UnicodeUTF8));
        actionScholar->setText(QApplication::translate("Tutor", "Scholar ...", 0, QApplication::UnicodeUTF8));
        TutorBGMusicLbl->setText(QApplication::translate("Tutor", "BG music:", 0, QApplication::UnicodeUTF8));
        ScholarBGMusicNameLbl->setText(QString());
        TutorBGMusicSelectBtn->setText(QApplication::translate("Tutor", "Select ...", 0, QApplication::UnicodeUTF8));
        TutorVideoLbl->setText(QApplication::translate("Tutor", "Video:", 0, QApplication::UnicodeUTF8));
        TutorVideoNameLbl->setText(QString());
        TutorVideoSelectBtn->setText(QApplication::translate("Tutor", "Select ...", 0, QApplication::UnicodeUTF8));
        TrackLbl->setText(QApplication::translate("Tutor", "Track", 0, QApplication::UnicodeUTF8));
        TrackBeatCountLbl->setText(QApplication::translate("Tutor", "Beat count:", 0, QApplication::UnicodeUTF8));
        TrackBeatLengthLbl->setText(QApplication::translate("Tutor", "Beat length:", 0, QApplication::UnicodeUTF8));
        TrackBPMLbl->setText(QApplication::translate("Tutor", "BPM:", 0, QApplication::UnicodeUTF8));
        TrackClefLbl->setText(QApplication::translate("Tutor", "Clef:", 0, QApplication::UnicodeUTF8));
        TrackClefVal->clear();
        TrackClefVal->insertItems(0, QStringList()
         << QApplication::translate("Tutor", "Treble", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Tutor", "Bass", 0, QApplication::UnicodeUTF8)
        );
        TrackPlayBtn->setText(QApplication::translate("Tutor", "> Play", 0, QApplication::UnicodeUTF8));
        BarLbl->setText(QApplication::translate("Tutor", "Bar", 0, QApplication::UnicodeUTF8));
        BarAddBtn->setText(QApplication::translate("Tutor", "Add", 0, QApplication::UnicodeUTF8));
        BarRemoveBtn->setText(QApplication::translate("Tutor", "Del", 0, QApplication::UnicodeUTF8));
        BarShiftLeftBtn->setText(QApplication::translate("Tutor", "<<", 0, QApplication::UnicodeUTF8));
        BarShiftRightBtn->setText(QApplication::translate("Tutor", ">>", 0, QApplication::UnicodeUTF8));
        BarRepeatStartLbl->setText(QApplication::translate("Tutor", "Repeat start", 0, QApplication::UnicodeUTF8));
        BarRepeatStartVal->setText(QString());
        BarRepeatCountLbl->setText(QApplication::translate("Tutor", "Repeat count", 0, QApplication::UnicodeUTF8));
        BarChordLbl->setText(QApplication::translate("Tutor", "Chord:", 0, QApplication::UnicodeUTF8));
        BarChordVal->setText(QString());
        BarRepeatNextEndLbl->setText(QApplication::translate("Tutor", "End on next bar", 0, QApplication::UnicodeUTF8));
        BarRepeatNextEndVal->setText(QString());
        BarPlayBtn->setText(QApplication::translate("Tutor", "> Play", 0, QApplication::UnicodeUTF8));
        NoteLbl->setText(QApplication::translate("Tutor", "Note", 0, QApplication::UnicodeUTF8));
        NoteLengthLbl->setText(QApplication::translate("Tutor", "Length", 0, QApplication::UnicodeUTF8));
        NoteExtensionLbl->setText(QApplication::translate("Tutor", "Extension", 0, QApplication::UnicodeUTF8));
        NoteContinueLbl->setText(QApplication::translate("Tutor", "Continue", 0, QApplication::UnicodeUTF8));
        NoteContinueVal->setText(QString());
        NoteSlideVal->setText(QString());
        NoteSlideLbl->setText(QApplication::translate("Tutor", "Slide", 0, QApplication::UnicodeUTF8));
        NoteVibratoVal->setText(QString());
        NoteVibratoLbl->setText(QApplication::translate("Tutor", "Vibrato", 0, QApplication::UnicodeUTF8));
        NotePOLbl->setText(QApplication::translate("Tutor", "PO", 0, QApplication::UnicodeUTF8));
        NoteHOLbl->setText(QApplication::translate("Tutor", "HO", 0, QApplication::UnicodeUTF8));
        NoteHORadio->setText(QString());
        NotePORadio->setText(QString());
        NoteHOPOOffRadio->setText(QString());
        NoteUngrouppingLbl->setText(QApplication::translate("Tutor", "Ungroupping", 0, QApplication::UnicodeUTF8));
        NoteGrouppingLbl->setText(QApplication::translate("Tutor", "Groupping", 0, QApplication::UnicodeUTF8));
        NoteAddBtn->setText(QApplication::translate("Tutor", "Add", 0, QApplication::UnicodeUTF8));
        NoteRemoveBtn->setText(QApplication::translate("Tutor", "Del", 0, QApplication::UnicodeUTF8));
        NoteShiftRightBtn->setText(QApplication::translate("Tutor", ">>", 0, QApplication::UnicodeUTF8));
        NoteShiftLeftBtn->setText(QApplication::translate("Tutor", "<<", 0, QApplication::UnicodeUTF8));
        ToneLbl->setText(QApplication::translate("Tutor", "Tone", 0, QApplication::UnicodeUTF8));
        ToneAddBtn->setText(QApplication::translate("Tutor", "Add", 0, QApplication::UnicodeUTF8));
        ToneRemoveBtn->setText(QApplication::translate("Tutor", "Del", 0, QApplication::UnicodeUTF8));
        ToneDownBtn->setText(QApplication::translate("Tutor", "Down", 0, QApplication::UnicodeUTF8));
        ToneUpBtn->setText(QApplication::translate("Tutor", "Up", 0, QApplication::UnicodeUTF8));
        ToneStringLbl->setText(QApplication::translate("Tutor", "String", 0, QApplication::UnicodeUTF8));
        ToneRestLbl->setText(QApplication::translate("Tutor", "Rest", 0, QApplication::UnicodeUTF8));
        ToneRestVal->setText(QString());
        NotePlayBtn->setText(QApplication::translate("Tutor", "> Play", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("Tutor", "File", 0, QApplication::UnicodeUTF8));
        menuTools->setTitle(QApplication::translate("Tutor", "Tools", 0, QApplication::UnicodeUTF8));
        menu->setTitle(QApplication::translate("Tutor", "?", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Tutor: public Ui_Tutor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TUTOR_H
