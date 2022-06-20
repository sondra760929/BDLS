/****************************************************************************
** Meta object code from reading C++ file 'widgetRightView.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../widgetRightView.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'widgetRightView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_widgetRightView_t {
    const uint offsetsAndSize[36];
    char stringdata0[243];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_widgetRightView_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_widgetRightView_t qt_meta_stringdata_widgetRightView = {
    {
QT_MOC_LITERAL(0, 15), // "widgetRightView"
QT_MOC_LITERAL(16, 17), // "fullScreenChanged"
QT_MOC_LITERAL(34, 0), // ""
QT_MOC_LITERAL(35, 10), // "fullScreen"
QT_MOC_LITERAL(46, 15), // "durationChanged"
QT_MOC_LITERAL(62, 8), // "duration"
QT_MOC_LITERAL(71, 15), // "positionChanged"
QT_MOC_LITERAL(87, 8), // "progress"
QT_MOC_LITERAL(96, 15), // "metaDataChanged"
QT_MOC_LITERAL(112, 4), // "seek"
QT_MOC_LITERAL(117, 8), // "mseconds"
QT_MOC_LITERAL(126, 13), // "statusChanged"
QT_MOC_LITERAL(140, 25), // "QMediaPlayer::MediaStatus"
QT_MOC_LITERAL(166, 6), // "status"
QT_MOC_LITERAL(173, 17), // "bufferingProgress"
QT_MOC_LITERAL(191, 21), // "videoAvailableChanged"
QT_MOC_LITERAL(213, 9), // "available"
QT_MOC_LITERAL(223, 19) // "displayErrorMessage"

    },
    "widgetRightView\0fullScreenChanged\0\0"
    "fullScreen\0durationChanged\0duration\0"
    "positionChanged\0progress\0metaDataChanged\0"
    "seek\0mseconds\0statusChanged\0"
    "QMediaPlayer::MediaStatus\0status\0"
    "bufferingProgress\0videoAvailableChanged\0"
    "available\0displayErrorMessage"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_widgetRightView[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   68,    2, 0x06,    1 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       4,    1,   71,    2, 0x08,    3 /* Private */,
       6,    1,   74,    2, 0x08,    5 /* Private */,
       8,    0,   77,    2, 0x08,    7 /* Private */,
       9,    1,   78,    2, 0x08,    8 /* Private */,
      11,    1,   81,    2, 0x08,   10 /* Private */,
      14,    1,   84,    2, 0x08,   12 /* Private */,
      15,    1,   87,    2, 0x08,   14 /* Private */,
      17,    0,   90,    2, 0x08,   16 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::LongLong,    5,
    QMetaType::Void, QMetaType::LongLong,    7,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void, QMetaType::Float,    7,
    QMetaType::Void, QMetaType::Bool,   16,
    QMetaType::Void,

       0        // eod
};

void widgetRightView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<widgetRightView *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->fullScreenChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 1: _t->durationChanged((*reinterpret_cast< std::add_pointer_t<qint64>>(_a[1]))); break;
        case 2: _t->positionChanged((*reinterpret_cast< std::add_pointer_t<qint64>>(_a[1]))); break;
        case 3: _t->metaDataChanged(); break;
        case 4: _t->seek((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 5: _t->statusChanged((*reinterpret_cast< std::add_pointer_t<QMediaPlayer::MediaStatus>>(_a[1]))); break;
        case 6: _t->bufferingProgress((*reinterpret_cast< std::add_pointer_t<float>>(_a[1]))); break;
        case 7: _t->videoAvailableChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 8: _t->displayErrorMessage(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (widgetRightView::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&widgetRightView::fullScreenChanged)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject widgetRightView::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_widgetRightView.offsetsAndSize,
    qt_meta_data_widgetRightView,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_widgetRightView_t
, QtPrivate::TypeAndForceComplete<widgetRightView, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<qint64, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<qint64, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QMediaPlayer::MediaStatus, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<float, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *widgetRightView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *widgetRightView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_widgetRightView.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int widgetRightView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void widgetRightView::fullScreenChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
