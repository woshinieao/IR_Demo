/****************************************************************************
** Meta object code from reading C++ file 'playwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "playwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'playwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_FrameRcvThread_t {
    QByteArrayData data[5];
    char stringdata0[40];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FrameRcvThread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FrameRcvThread_t qt_meta_stringdata_FrameRcvThread = {
    {
QT_MOC_LITERAL(0, 0, 14), // "FrameRcvThread"
QT_MOC_LITERAL(1, 15, 9), // "FrameRecv"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 6), // "Frame*"
QT_MOC_LITERAL(4, 33, 6) // "pframe"

    },
    "FrameRcvThread\0FrameRecv\0\0Frame*\0"
    "pframe"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FrameRcvThread[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   19,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Int, 0x80000000 | 3,    4,

       0        // eod
};

void FrameRcvThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FrameRcvThread *_t = static_cast<FrameRcvThread *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: { int _r = _t->FrameRecv((*reinterpret_cast< Frame*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObject FrameRcvThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_FrameRcvThread.data,
      qt_meta_data_FrameRcvThread,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *FrameRcvThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FrameRcvThread::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_FrameRcvThread.stringdata0))
        return static_cast<void*>(const_cast< FrameRcvThread*>(this));
    return QThread::qt_metacast(_clname);
}

int FrameRcvThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
struct qt_meta_stringdata_PlayWidget_t {
    QByteArrayData data[10];
    char stringdata0[75];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PlayWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PlayWidget_t qt_meta_stringdata_PlayWidget = {
    {
QT_MOC_LITERAL(0, 0, 10), // "PlayWidget"
QT_MOC_LITERAL(1, 11, 8), // "sigFrame"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 6), // "Frame*"
QT_MOC_LITERAL(4, 28, 6), // "pframe"
QT_MOC_LITERAL(5, 35, 4), // "Play"
QT_MOC_LITERAL(6, 40, 4), // "Stop"
QT_MOC_LITERAL(7, 45, 10), // "paintEvent"
QT_MOC_LITERAL(8, 56, 12), // "QPaintEvent*"
QT_MOC_LITERAL(9, 69, 5) // "event"

    },
    "PlayWidget\0sigFrame\0\0Frame*\0pframe\0"
    "Play\0Stop\0paintEvent\0QPaintEvent*\0"
    "event"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PlayWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   37,    2, 0x0a /* Public */,
       6,    0,   38,    2, 0x0a /* Public */,
       7,    1,   39,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Void, 0x80000000 | 8,    9,

       0        // eod
};

void PlayWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PlayWidget *_t = static_cast<PlayWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sigFrame((*reinterpret_cast< Frame*(*)>(_a[1]))); break;
        case 1: { int _r = _t->Play();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 2: { int _r = _t->Stop();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 3: _t->paintEvent((*reinterpret_cast< QPaintEvent*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (PlayWidget::*_t)(Frame * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PlayWidget::sigFrame)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject PlayWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_PlayWidget.data,
      qt_meta_data_PlayWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *PlayWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PlayWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_PlayWidget.stringdata0))
        return static_cast<void*>(const_cast< PlayWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int PlayWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void PlayWidget::sigFrame(Frame * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
