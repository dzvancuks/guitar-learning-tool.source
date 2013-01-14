/* 
 * File:   EffectPump.cpp
 * Author: astral
 * 
 * Created on 25 Декабрь 2012 г., 19:44
 */

#include "EffectPump.h"
#include "Mixer.h"

EffectPump::EffectPump(QWidget *parent, AudioIO *audio, Mixer *mixer) : QWidget(parent) {
    this->audio = audio;
    this->mixer = mixer;
    
    data.resize(AUDIO_BUF_SIZE);
    processing = false;
    
    e1 = NULL;
    e2 = NULL;
    e3 = NULL;
    
    effects_frame1 = new QFrame(this);
    effects_frame1->setObjectName(QString::fromUtf8("EffectFrame1"));
    effects_frame1->setGeometry(QRect(0, 21, FX_VISUAL_X, FX_VISUAL_Y));
    effects_frame1->setFrameShape(QFrame::Panel);
    effects_frame1->setFrameShadow(QFrame::Raised);
    effects_layout_widget1 = new QWidget(effects_frame1);
    effects_layout_widget1->setObjectName(QString::fromUtf8("effects_layout_widget1"));
    effects_layout_widget1->setGeometry(QRect(0, 0, FX_VISUAL_X, FX_VISUAL_Y));
    effects_layout1 = new QGridLayout(effects_layout_widget1);
    effects_layout1->setObjectName(QString::fromUtf8("effects_layout1"));
    effects_layout1->setContentsMargins(0, 0, 0, 0);
    
    effects_frame2 = new QFrame(this);
    effects_frame2->setObjectName(QString::fromUtf8("EffectFrame2"));
    effects_frame2->setGeometry(QRect(FX_VISUAL_X + 10, 21, FX_VISUAL_X, FX_VISUAL_Y));
    effects_frame2->setFrameShape(QFrame::Panel);
    effects_frame2->setFrameShadow(QFrame::Raised);
    effects_layout_widget2 = new QWidget(effects_frame2);
    effects_layout_widget2->setObjectName(QString::fromUtf8("effects_layout_widget2"));
    effects_layout_widget2->setGeometry(QRect(0, 0, FX_VISUAL_X, FX_VISUAL_Y));
    effects_layout2 = new QGridLayout(effects_layout_widget2);
    effects_layout2->setObjectName(QString::fromUtf8("effects_layout2"));
    effects_layout2->setContentsMargins(0, 0, 0, 0);
    
    effects_frame3 = new QFrame(this);
    effects_frame3->setObjectName(QString::fromUtf8("EffectFrame3"));
    effects_frame3->setGeometry(QRect((FX_VISUAL_X + 10) * 2, 21, FX_VISUAL_X, FX_VISUAL_Y));
    effects_frame3->setFrameShape(QFrame::Panel);
    effects_frame3->setFrameShadow(QFrame::Raised);
    effects_layout_widget3 = new QWidget(effects_frame3);
    effects_layout_widget3->setObjectName(QString::fromUtf8("effects_layout_widget3"));
    effects_layout_widget3->setGeometry(QRect(0, 0, FX_VISUAL_X, FX_VISUAL_Y));
    effects_layout3 = new QGridLayout(effects_layout_widget3);
    effects_layout3->setObjectName(QString::fromUtf8("effects_layout3"));
    effects_layout3->setContentsMargins(0, 0, 0, 0);
    
    effects_list1 = new QComboBox();
    effects_list1->setObjectName(QString::fromUtf8("EffectList1"));
    effects_list1->setGeometry(QRect(0, 10, FX_VISUAL_X, 22));
    effects_layout1->addWidget(effects_list1);
    
    effects_list2 = new QComboBox(effects_frame2);
    effects_list2->setObjectName(QString::fromUtf8("EffectList2"));
    effects_list2->setGeometry(QRect(0, 10, FX_VISUAL_X, 22));
    effects_layout2->addWidget(effects_list2);
    
    effects_list3 = new QComboBox(effects_frame3);
    effects_list3->setObjectName(QString::fromUtf8("EffectList3"));
    effects_list3->setGeometry(QRect(0, 10, FX_VISUAL_X, 22));
    effects_layout3->addWidget(effects_list3);
    
    EnumerateEffects(effects_list1, 1);
    EnumerateEffects(effects_list2, 2);
    EnumerateEffects(effects_list3, 3);
    
    // Test
    //e1 = new EffectDistortion(effects_frame1);
    //e2 = new EffectEcho(effects_frame2);
}

EffectPump::EffectPump(const EffectPump& orig) {
}

EffectPump::~EffectPump() {
    UnloadAllEffects();
}

void EffectPump::FetchSound() {
    if (processing) return;
    if (!audio || !mixer) return;
    
    std::vector<float> in;
    
    processing = true;
    
    in = audio->GetSoundInput_safe();
    //assert (in.size() == AUDIO_BUF_SIZE);
    for (int i = 0; i < AUDIO_BUF_SIZE; i++) {
        data[i] = AMPLIFY * in[i]; 
    }
    
    if (e1) {
        e1->Process(&data);
    }
    if (e2) {
        e2->Process(&data);
    }
    if (e3) {
        e3->Process(&data);
    }
    
    mixer->QueueSound(data, this);
    
    processing = false;
}

void EffectPump::EnumerateEffects(QComboBox *list, int order) {
    if (!list) return;
    
    list->addItem("None");
    list->addItem("Distortion");
    list->addItem("Echo");
    switch (order) {
        case 1: QObject::connect(list, SIGNAL(currentIndexChanged(int)), this, SLOT(LoadEffect1(int))); break;
        case 2: QObject::connect(list, SIGNAL(currentIndexChanged(int)), this, SLOT(LoadEffect2(int))); break;
        case 3: QObject::connect(list, SIGNAL(currentIndexChanged(int)), this, SLOT(LoadEffect3(int))); break;
    }
}

Effect * EffectPump::SelectionParser(int i, QWidget *parent, QGridLayout *layout) {
    switch ((EffectTypes)i) {
        case DISTORTION:
            return new EffectDistortion(parent, layout);
        case ECHO:
            return new EffectEcho(parent, layout);
        default:
            return NULL;
    }
}

void EffectPump::LoadEffect1(int i) {
    if ((e1 = SelectionParser(i, effects_frame1, effects_layout1) )) {
        effects_layout1->removeItem(effects_layout1->itemAt(0));
        effects_list1->hide();
        e1->show();
        //QObject::connect(e1->close, SIGNAL(clicked()), this, SLOT(UnloadEffect1()));
    }
}
void EffectPump::LoadEffect2(int i) {
    if ((e2 = SelectionParser(i, effects_frame2, effects_layout2) )) {
        effects_layout2->removeItem(effects_layout2->itemAt(0));
        effects_list2->hide();
        e2->show();
        //QObject::connect(e2->close, SIGNAL(clicked()), this, SLOT(UnloadEffect2()));
    }
}
void EffectPump::LoadEffect3(int i) {
    if ((e3 = SelectionParser(i, effects_frame3, effects_layout3) )) {
        effects_layout3->removeItem(effects_layout3->itemAt(0));
        effects_list3->hide();
        e3->show();
        //QObject::connect(e3->close, SIGNAL(clicked()), this, SLOT(UnloadEffect3()));
    }
}

void EffectPump::UnloadEffect1() {
    if (!e1) return;
    
    //QObject::disconnect(e1->close, SIGNAL(clicked()), this, SLOT(UnloadEffect1()));
    delete e1;
    e1 = NULL;
    effects_layout1->addWidget(effects_list1);
    effects_list1->setCurrentIndex(0);
    effects_list1->show();
}
void EffectPump::UnloadEffect2() {
    if (!e2) return;
    
    //QObject::disconnect(e2->close, SIGNAL(clicked()), this, SLOT(UnloadEffect2()));
    delete e2;
    e2 = NULL;
    effects_layout2->addWidget(effects_list2);
    effects_list2->setCurrentIndex(0);
    effects_list2->show();
}
void EffectPump::UnloadEffect3() {
    if (!e3) return;
    
    //QObject::disconnect(e3->close, SIGNAL(clicked()), this, SLOT(UnloadEffect3()));
    delete e3;
    e3 = NULL;
    effects_layout3->addWidget(effects_list3);
    effects_list3->setCurrentIndex(0);
    effects_list3->show();
}

void EffectPump::UnloadAllEffects() {
    UnloadEffect1();
    UnloadEffect2();
    UnloadEffect3();
}
