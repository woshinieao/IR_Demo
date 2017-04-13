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
struct qt_meta_stringdata_TemperatureThread_t {
    QByteArrayData data[1];
    char stringdata0[18];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TemperatureThread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TemperatureThread_t qt_meta_stringdata_TemperatureThread = {
    {
QT_MOC_LITERAL(0, 0, 17) // "TemperatureThread"

    },
    "TemperatureThread"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TemperatureThread[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void TemperatureThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject TemperatureThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_TemperatureThread.data,
      qt_meta_data_TemperatureThread,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TemperatureThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TemperatureThread::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TemperatureThread.stringdata0))
        return static_cast<void*>(const_cast< TemperatureThread*>(this));
    return QThread::qt_metacast(_clname);
}

int TemperatureThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
struct qt_meta_stringdata_PlayWidget_t {
    QByteArrayData data[45];
    char stringdata0[427];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PlayWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PlayWidget_t qt_meta_stringdata_PlayWidget = {
    {
QT_MOC_LITERAL(0, 0, 10), // "PlayWidget"
QT_MOC_LITERAL(1, 11, 4), // "Play"
QT_MOC_LITERAL(2, 16, 0), // ""
QT_MOC_LITERAL(3, 17, 4), // "Stop"
QT_MOC_LITERAL(4, 22, 11), // "FrameHeader"
QT_MOC_LITERAL(5, 34, 12), // "FramePalette"
QT_MOC_LITERAL(6, 47, 5), // "index"
QT_MOC_LITERAL(7, 53, 12), // "FrameConvert"
QT_MOC_LITERAL(8, 66, 9), // "FrameRecv"
QT_MOC_LITERAL(9, 76, 6), // "Frame*"
QT_MOC_LITERAL(10, 83, 6), // "pframe"
QT_MOC_LITERAL(11, 90, 10), // "TimeSecond"
QT_MOC_LITERAL(12, 101, 15), // "TimeSecondTTTTT"
QT_MOC_LITERAL(13, 117, 10), // "ContrlMode"
QT_MOC_LITERAL(14, 128, 11), // "GrapPicture"
QT_MOC_LITERAL(15, 140, 16), // "PointTemperature"
QT_MOC_LITERAL(16, 157, 8), // "DrawRect"
QT_MOC_LITERAL(17, 166, 8), // "SaveRect"
QT_MOC_LITERAL(18, 175, 9), // "CleanRect"
QT_MOC_LITERAL(19, 185, 12), // "SetHistParam"
QT_MOC_LITERAL(20, 198, 6), // "Param1"
QT_MOC_LITERAL(21, 205, 6), // "Param2"
QT_MOC_LITERAL(22, 212, 6), // "Param3"
QT_MOC_LITERAL(23, 219, 6), // "Param4"
QT_MOC_LITERAL(24, 226, 6), // "Param5"
QT_MOC_LITERAL(25, 233, 9), // "Histogram"
QT_MOC_LITERAL(26, 243, 7), // "UINT16*"
QT_MOC_LITERAL(27, 251, 1), // "p"
QT_MOC_LITERAL(28, 253, 6), // "UINT16"
QT_MOC_LITERAL(29, 260, 6), // "u16Max"
QT_MOC_LITERAL(30, 267, 6), // "u16Min"
QT_MOC_LITERAL(31, 274, 8), // "u16Width"
QT_MOC_LITERAL(32, 283, 8), // "u16Hight"
QT_MOC_LITERAL(33, 292, 7), // "QuanMax"
QT_MOC_LITERAL(34, 300, 7), // "QuanMin"
QT_MOC_LITERAL(35, 308, 6), // "NrBins"
QT_MOC_LITERAL(36, 315, 9), // "u16Param4"
QT_MOC_LITERAL(37, 325, 9), // "u16Param5"
QT_MOC_LITERAL(38, 335, 15), // "mousePressEvent"
QT_MOC_LITERAL(39, 351, 12), // "QMouseEvent*"
QT_MOC_LITERAL(40, 364, 5), // "event"
QT_MOC_LITERAL(41, 370, 14), // "mouseMoveEvent"
QT_MOC_LITERAL(42, 385, 17), // "mouseReleaseEvent"
QT_MOC_LITERAL(43, 403, 10), // "paintEvent"
QT_MOC_LITERAL(44, 414, 12) // "QPaintEvent*"

    },
    "PlayWidget\0Play\0\0Stop\0FrameHeader\0"
    "FramePalette\0index\0FrameConvert\0"
    "FrameRecv\0Frame*\0pframe\0TimeSecond\0"
    "TimeSecondTTTTT\0ContrlMode\0GrapPicture\0"
    "PointTemperature\0DrawRect\0SaveRect\0"
    "CleanRect\0SetHistParam\0Param1\0Param2\0"
    "Param3\0Param4\0Param5\0Histogram\0UINT16*\0"
    "p\0UINT16\0u16Max\0u16Min\0u16Width\0"
    "u16Hight\0QuanMax\0QuanMin\0NrBins\0"
    "u16Param4\0u16Param5\0mousePressEvent\0"
    "QMouseEvent*\0event\0mouseMoveEvent\0"
    "mouseReleaseEvent\0paintEvent\0QPaintEvent*"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PlayWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      20,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  114,    2, 0x0a /* Public */,
       3,    0,  115,    2, 0x0a /* Public */,
       4,    0,  116,    2, 0x0a /* Public */,
       5,    1,  117,    2, 0x0a /* Public */,
       7,    0,  120,    2, 0x0a /* Public */,
       8,    1,  121,    2, 0x0a /* Public */,
      11,    0,  124,    2, 0x0a /* Public */,
      12,    0,  125,    2, 0x0a /* Public */,
      13,    1,  126,    2, 0x0a /* Public */,
      14,    0,  129,    2, 0x0a /* Public */,
      15,    0,  130,    2, 0x0a /* Public */,
      16,    0,  131,    2, 0x0a /* Public */,
      17,    0,  132,    2, 0x0a /* Public */,
      18,    0,  133,    2, 0x0a /* Public */,
      19,    5,  134,    2, 0x0a /* Public */,
      25,   10,  145,    2, 0x0a /* Public */,
      38,    1,  166,    2, 0x0a /* Public */,
      41,    1,  169,    2, 0x0a /* Public */,
      42,    1,  172,    2, 0x0a /* Public */,
      43,    1,  175,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int, QMetaType::Int,    6,
    QMetaType::Int,
    QMetaType::Int, 0x80000000 | 9,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Int, QMetaType::Int,    2,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int, QMetaType::Short, QMetaType::Short, QMetaType::Short, QMetaType::Short, QMetaType::Short,   20,   21,   22,   23,   24,
    QMetaType::Int, 0x80000000 | 26, 0x80000000 | 28, 0x80000000 | 28, 0x80000000 | 28, 0x80000000 | 28, 0x80000000 | 26, 0x80000000 | 26, 0x80000000 | 26, 0x80000000 | 28, 0x80000000 | 28,   27,   29,   30,   31,   32,   33,   34,   35,   36,   37,
    QMetaType::Void, 0x80000000 | 39,   40,
    QMetaType::Void, 0x80000000 | 39,   40,
    QMetaType::Void, 0x80000000 | 39,   40,
    QMetaType::Void, 0x80000000 | 44,   40,

       0        // eod
};

void PlayWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PlayWidget *_t = static_cast<PlayWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: { int _r = _t->Play();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 1: { int _r = _t->Stop();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 2: { int _r = _t->FrameHeader();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 3: { int _r = _t->FramePalette((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 4: { int _r = _t->FrameConvert();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 5: { int _r = _t->FrameRecv((*reinterpret_cast< Frame*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 6: _t->TimeSecond(); break;
        case 7: _t->TimeSecondTTTTT(); break;
        case 8: { int _r = _t->ContrlMode((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 9: { int _r = _t->GrapPicture();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 10: { int _r = _t->PointTemperature();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 11: { int _r = _t->DrawRect();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 12: { int _r = _t->SaveRect();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 13: { int _r = _t->CleanRect();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 14: { int _r = _t->SetHistParam((*reinterpret_cast< short(*)>(_a[1])),(*reinterpret_cast< short(*)>(_a[2])),(*reinterpret_cast< short(*)>(_a[3])),(*reinterpret_cast< short(*)>(_a[4])),(*reinterpret_cast< short(*)>(_a[5])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 15: { int _r = _t->Histogram((*reinterpret_cast< UINT16*(*)>(_a[1])),(*reinterpret_cast< UINT16(*)>(_a[2])),(*reinterpret_cast< UINT16(*)>(_a[3])),(*reinterpret_cast< UINT16(*)>(_a[4])),(*reinterpret_cast< UINT16(*)>(_a[5])),(*reinterpret_cast< UINT16*(*)>(_a[6])),(*reinterpret_cast< UINT16*(*)>(_a[7])),(*reinterpret_cast< UINT16*(*)>(_a[8])),(*reinterpret_cast< UINT16(*)>(_a[9])),(*reinterpret_cast< UINT16(*)>(_a[10])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 16: _t->mousePressEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 17: _t->mouseMoveEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 18: _t->mouseReleaseEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 19: _t->paintEvent((*reinterpret_cast< QPaintEvent*(*)>(_a[1]))); break;
        default: ;
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
        if (_id < 20)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 20;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 20)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 20;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
