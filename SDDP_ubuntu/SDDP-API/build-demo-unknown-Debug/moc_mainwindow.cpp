/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../demo/mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,
      37,   11,   11,   11, 0x08,
      57,   11,   11,   11, 0x08,
      78,   11,   11,   11, 0x08,
     105,   11,   11,   11, 0x08,
     129,   11,   11,   11, 0x08,
     160,   11,   11,   11, 0x08,
     185,   11,   11,   11, 0x08,
     217,   11,   11,   11, 0x08,
     249,   11,   11,   11, 0x08,
     277,   11,   11,   11, 0x08,
     305,   11,   11,   11, 0x08,
     333,   11,   11,   11, 0x08,
     361,   11,   11,   11, 0x08,
     389,   11,   11,   11, 0x08,
     417,   11,   11,   11, 0x08,
     445,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0on_self_button_clicked()\0"
    "statusTimerUpDate()\0sysDataTimerUpDate()\0"
    "on_manual_button_clicked()\0"
    "on_pushButton_clicked()\0"
    "on_steerEnableButton_clicked()\0"
    "on_InitSButton_clicked()\0"
    "on_unintServiceButton_clicked()\0"
    "on_steerDisableButton_clicked()\0"
    "on_steerAddButton_clicked()\0"
    "on_steerSubButton_clicked()\0"
    "on_steerSetButton_clicked()\0"
    "on_setNGearButton_clicked()\0"
    "on_setDGearButton_clicked()\0"
    "on_setRGearButton_clicked()\0"
    "on_setPGearButton_clicked()\0"
    "on_pushButton_18_clicked()\0"
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->on_self_button_clicked(); break;
        case 1: _t->statusTimerUpDate(); break;
        case 2: _t->sysDataTimerUpDate(); break;
        case 3: _t->on_manual_button_clicked(); break;
        case 4: _t->on_pushButton_clicked(); break;
        case 5: _t->on_steerEnableButton_clicked(); break;
        case 6: _t->on_InitSButton_clicked(); break;
        case 7: _t->on_unintServiceButton_clicked(); break;
        case 8: _t->on_steerDisableButton_clicked(); break;
        case 9: _t->on_steerAddButton_clicked(); break;
        case 10: _t->on_steerSubButton_clicked(); break;
        case 11: _t->on_steerSetButton_clicked(); break;
        case 12: _t->on_setNGearButton_clicked(); break;
        case 13: _t->on_setDGearButton_clicked(); break;
        case 14: _t->on_setRGearButton_clicked(); break;
        case 15: _t->on_setPGearButton_clicked(); break;
        case 16: _t->on_pushButton_18_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData MainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
