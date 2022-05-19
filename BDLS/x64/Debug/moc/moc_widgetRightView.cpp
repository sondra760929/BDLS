/****************************************************************************
** Meta object code from reading C++ file 'widgetRightView.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.3.0)
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
#error "This file was generated using the moc from 6.3.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_widgetRightView_t {
    const uint offsetsAndSize[62];
    char stringdata0[520];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_widgetRightView_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_widgetRightView_t qt_meta_stringdata_widgetRightView = {
    {
QT_MOC_LITERAL(0, 15), // "widgetRightView"
QT_MOC_LITERAL(16, 17), // "fullScreenChanged"
QT_MOC_LITERAL(34, 0), // ""
QT_MOC_LITERAL(35, 10), // "fullScreen"
QT_MOC_LITERAL(46, 16), // "bookmarkSelected"
QT_MOC_LITERAL(63, 11), // "QModelIndex"
QT_MOC_LITERAL(75, 5), // "index"
QT_MOC_LITERAL(81, 12), // "pageSelected"
QT_MOC_LITERAL(94, 4), // "page"
QT_MOC_LITERAL(99, 23), // "on_actionQuit_triggered"
QT_MOC_LITERAL(123, 24), // "on_actionAbout_triggered"
QT_MOC_LITERAL(148, 27), // "on_actionAbout_Qt_triggered"
QT_MOC_LITERAL(176, 26), // "on_actionZoom_In_triggered"
QT_MOC_LITERAL(203, 27), // "on_actionZoom_Out_triggered"
QT_MOC_LITERAL(231, 32), // "on_actionPrevious_Page_triggered"
QT_MOC_LITERAL(264, 28), // "on_actionNext_Page_triggered"
QT_MOC_LITERAL(293, 29), // "on_actionContinuous_triggered"
QT_MOC_LITERAL(323, 15), // "durationChanged"
QT_MOC_LITERAL(339, 8), // "duration"
QT_MOC_LITERAL(348, 15), // "positionChanged"
QT_MOC_LITERAL(364, 8), // "progress"
QT_MOC_LITERAL(373, 15), // "metaDataChanged"
QT_MOC_LITERAL(389, 4), // "seek"
QT_MOC_LITERAL(394, 8), // "mseconds"
QT_MOC_LITERAL(403, 13), // "statusChanged"
QT_MOC_LITERAL(417, 25), // "QMediaPlayer::MediaStatus"
QT_MOC_LITERAL(443, 6), // "status"
QT_MOC_LITERAL(450, 17), // "bufferingProgress"
QT_MOC_LITERAL(468, 21), // "videoAvailableChanged"
QT_MOC_LITERAL(490, 9), // "available"
QT_MOC_LITERAL(500, 19) // "displayErrorMessage"

    },
    "widgetRightView\0fullScreenChanged\0\0"
    "fullScreen\0bookmarkSelected\0QModelIndex\0"
    "index\0pageSelected\0page\0on_actionQuit_triggered\0"
    "on_actionAbout_triggered\0"
    "on_actionAbout_Qt_triggered\0"
    "on_actionZoom_In_triggered\0"
    "on_actionZoom_Out_triggered\0"
    "on_actionPrevious_Page_triggered\0"
    "on_actionNext_Page_triggered\0"
    "on_actionContinuous_triggered\0"
    "durationChanged\0duration\0positionChanged\0"
    "progress\0metaDataChanged\0seek\0mseconds\0"
    "statusChanged\0QMediaPlayer::MediaStatus\0"
    "status\0bufferingProgress\0videoAvailableChanged\0"
    "available\0displayErrorMessage"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_widgetRightView[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      19,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,  128,    2, 0x06,    1 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       4,    1,  131,    2, 0x08,    3 /* Private */,
       7,    1,  134,    2, 0x08,    5 /* Private */,
       9,    0,  137,    2, 0x08,    7 /* Private */,
      10,    0,  138,    2, 0x08,    8 /* Private */,
      11,    0,  139,    2, 0x08,    9 /* Private */,
      12,    0,  140,    2, 0x08,   10 /* Private */,
      13,    0,  141,    2, 0x08,   11 /* Private */,
      14,    0,  142,    2, 0x08,   12 /* Private */,
      15,    0,  143,    2, 0x08,   13 /* Private */,
      16,    0,  144,    2, 0x08,   14 /* Private */,
      17,    1,  145,    2, 0x08,   15 /* Private */,
      19,    1,  148,    2, 0x08,   17 /* Private */,
      21,    0,  151,    2, 0x08,   19 /* Private */,
      22,    1,  152,    2, 0x08,   20 /* Private */,
      24,    1,  155,    2, 0x08,   22 /* Private */,
      27,    1,  158,    2, 0x08,   24 /* Private */,
      28,    1,  161,    2, 0x08,   26 /* Private */,
      30,    0,  164,    2, 0x08,   28 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::LongLong,   18,
    QMetaType::Void, QMetaType::LongLong,   20,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   23,
    QMetaType::Void, 0x80000000 | 25,   26,
    QMetaType::Void, QMetaType::Float,   20,
    QMetaType::Void, QMetaType::Bool,   29,
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
        case 1: _t->bookmarkSelected((*reinterpret_cast< std::add_pointer_t<QModelIndex>>(_a[1]))); break;
        case 2: _t->pageSelected((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 3: _t->on_actionQuit_triggered(); break;
        case 4: _t->on_actionAbout_triggered(); break;
        case 5: _t->on_actionAbout_Qt_triggered(); break;
        case 6: _t->on_actionZoom_In_triggered(); break;
        case 7: _t->on_actionZoom_Out_triggered(); break;
        case 8: _t->on_actionPrevious_Page_triggered(); break;
        case 9: _t->on_actionNext_Page_triggered(); break;
        case 10: _t->on_actionContinuous_triggered(); break;
        case 11: _t->durationChanged((*reinterpret_cast< std::add_pointer_t<qint64>>(_a[1]))); break;
        case 12: _t->positionChanged((*reinterpret_cast< std::add_pointer_t<qint64>>(_a[1]))); break;
        case 13: _t->metaDataChanged(); break;
        case 14: _t->seek((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 15: _t->statusChanged((*reinterpret_cast< std::add_pointer_t<QMediaPlayer::MediaStatus>>(_a[1]))); break;
        case 16: _t->bufferingProgress((*reinterpret_cast< std::add_pointer_t<float>>(_a[1]))); break;
        case 17: _t->videoAvailableChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 18: _t->displayErrorMessage(); break;
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
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QModelIndex &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<qint64, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<qint64, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QMediaPlayer::MediaStatus, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<float, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


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
        if (_id < 19)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 19)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 19;
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
