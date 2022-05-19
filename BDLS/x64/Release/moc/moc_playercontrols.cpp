/****************************************************************************
** Meta object code from reading C++ file 'playercontrols.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../playercontrols.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'playercontrols.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PlayerControls_t {
    const uint offsetsAndSize[48];
    char stringdata0[248];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_PlayerControls_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_PlayerControls_t qt_meta_stringdata_PlayerControls = {
    {
QT_MOC_LITERAL(0, 14), // "PlayerControls"
QT_MOC_LITERAL(15, 4), // "play"
QT_MOC_LITERAL(20, 0), // ""
QT_MOC_LITERAL(21, 5), // "pause"
QT_MOC_LITERAL(27, 4), // "stop"
QT_MOC_LITERAL(32, 4), // "next"
QT_MOC_LITERAL(37, 8), // "previous"
QT_MOC_LITERAL(46, 12), // "changeVolume"
QT_MOC_LITERAL(59, 6), // "volume"
QT_MOC_LITERAL(66, 12), // "changeMuting"
QT_MOC_LITERAL(79, 6), // "muting"
QT_MOC_LITERAL(86, 10), // "changeRate"
QT_MOC_LITERAL(97, 4), // "rate"
QT_MOC_LITERAL(102, 8), // "setState"
QT_MOC_LITERAL(111, 27), // "QMediaPlayer::PlaybackState"
QT_MOC_LITERAL(139, 5), // "state"
QT_MOC_LITERAL(145, 9), // "setVolume"
QT_MOC_LITERAL(155, 8), // "setMuted"
QT_MOC_LITERAL(164, 5), // "muted"
QT_MOC_LITERAL(170, 15), // "setPlaybackRate"
QT_MOC_LITERAL(186, 11), // "playClicked"
QT_MOC_LITERAL(198, 11), // "muteClicked"
QT_MOC_LITERAL(210, 10), // "updateRate"
QT_MOC_LITERAL(221, 26) // "onVolumeSliderValueChanged"

    },
    "PlayerControls\0play\0\0pause\0stop\0next\0"
    "previous\0changeVolume\0volume\0changeMuting\0"
    "muting\0changeRate\0rate\0setState\0"
    "QMediaPlayer::PlaybackState\0state\0"
    "setVolume\0setMuted\0muted\0setPlaybackRate\0"
    "playClicked\0muteClicked\0updateRate\0"
    "onVolumeSliderValueChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PlayerControls[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  110,    2, 0x06,    1 /* Public */,
       3,    0,  111,    2, 0x06,    2 /* Public */,
       4,    0,  112,    2, 0x06,    3 /* Public */,
       5,    0,  113,    2, 0x06,    4 /* Public */,
       6,    0,  114,    2, 0x06,    5 /* Public */,
       7,    1,  115,    2, 0x06,    6 /* Public */,
       9,    1,  118,    2, 0x06,    8 /* Public */,
      11,    1,  121,    2, 0x06,   10 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      13,    1,  124,    2, 0x0a,   12 /* Public */,
      16,    1,  127,    2, 0x0a,   14 /* Public */,
      17,    1,  130,    2, 0x0a,   16 /* Public */,
      19,    1,  133,    2, 0x0a,   18 /* Public */,
      20,    0,  136,    2, 0x08,   20 /* Private */,
      21,    0,  137,    2, 0x08,   21 /* Private */,
      22,    0,  138,    2, 0x08,   22 /* Private */,
      23,    0,  139,    2, 0x08,   23 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Float,    8,
    QMetaType::Void, QMetaType::Bool,   10,
    QMetaType::Void, QMetaType::QReal,   12,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 14,   15,
    QMetaType::Void, QMetaType::Float,    8,
    QMetaType::Void, QMetaType::Bool,   18,
    QMetaType::Void, QMetaType::Float,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void PlayerControls::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PlayerControls *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->play(); break;
        case 1: _t->pause(); break;
        case 2: _t->stop(); break;
        case 3: _t->next(); break;
        case 4: _t->previous(); break;
        case 5: _t->changeVolume((*reinterpret_cast< std::add_pointer_t<float>>(_a[1]))); break;
        case 6: _t->changeMuting((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 7: _t->changeRate((*reinterpret_cast< std::add_pointer_t<qreal>>(_a[1]))); break;
        case 8: _t->setState((*reinterpret_cast< std::add_pointer_t<QMediaPlayer::PlaybackState>>(_a[1]))); break;
        case 9: _t->setVolume((*reinterpret_cast< std::add_pointer_t<float>>(_a[1]))); break;
        case 10: _t->setMuted((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 11: _t->setPlaybackRate((*reinterpret_cast< std::add_pointer_t<float>>(_a[1]))); break;
        case 12: _t->playClicked(); break;
        case 13: _t->muteClicked(); break;
        case 14: _t->updateRate(); break;
        case 15: _t->onVolumeSliderValueChanged(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (PlayerControls::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PlayerControls::play)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (PlayerControls::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PlayerControls::pause)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (PlayerControls::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PlayerControls::stop)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (PlayerControls::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PlayerControls::next)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (PlayerControls::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PlayerControls::previous)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (PlayerControls::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PlayerControls::changeVolume)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (PlayerControls::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PlayerControls::changeMuting)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (PlayerControls::*)(qreal );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PlayerControls::changeRate)) {
                *result = 7;
                return;
            }
        }
    }
}

const QMetaObject PlayerControls::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_PlayerControls.offsetsAndSize,
    qt_meta_data_PlayerControls,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_PlayerControls_t
, QtPrivate::TypeAndForceComplete<PlayerControls, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<float, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<qreal, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QMediaPlayer::PlaybackState, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<float, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<float, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *PlayerControls::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PlayerControls::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PlayerControls.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int PlayerControls::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void PlayerControls::play()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void PlayerControls::pause()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void PlayerControls::stop()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void PlayerControls::next()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void PlayerControls::previous()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void PlayerControls::changeVolume(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void PlayerControls::changeMuting(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void PlayerControls::changeRate(qreal _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
