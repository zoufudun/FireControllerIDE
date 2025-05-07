/****************************************************************************
** Meta object code from reading C++ file 'componentmanager.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../componentmanager.h"
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'componentmanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
namespace {
struct qt_meta_stringdata_ComponentManager_t {
    uint offsetsAndSizes[24];
    char stringdata0[17];
    char stringdata1[15];
    char stringdata2[1];
    char stringdata3[14];
    char stringdata4[10];
    char stringdata5[17];
    char stringdata6[15];
    char stringdata7[5];
    char stringdata8[15];
    char stringdata9[10];
    char stringdata10[22];
    char stringdata11[7];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_ComponentManager_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_ComponentManager_t qt_meta_stringdata_ComponentManager = {
    {
        QT_MOC_LITERAL(0, 16),  // "ComponentManager"
        QT_MOC_LITERAL(17, 14),  // "componentAdded"
        QT_MOC_LITERAL(32, 0),  // ""
        QT_MOC_LITERAL(33, 13),  // "ComponentInfo"
        QT_MOC_LITERAL(47, 9),  // "component"
        QT_MOC_LITERAL(57, 16),  // "componentDeleted"
        QT_MOC_LITERAL(74, 14),  // "QStandardItem*"
        QT_MOC_LITERAL(89, 4),  // "item"
        QT_MOC_LITERAL(94, 14),  // "componentMoved"
        QT_MOC_LITERAL(109, 9),  // "newParent"
        QT_MOC_LITERAL(119, 21),  // "componentOrderChanged"
        QT_MOC_LITERAL(141, 6)   // "moveUp"
    },
    "ComponentManager",
    "componentAdded",
    "",
    "ComponentInfo",
    "component",
    "componentDeleted",
    "QStandardItem*",
    "item",
    "componentMoved",
    "newParent",
    "componentOrderChanged",
    "moveUp"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_ComponentManager[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   38,    2, 0x06,    1 /* Public */,
       5,    1,   41,    2, 0x06,    3 /* Public */,
       8,    2,   44,    2, 0x06,    5 /* Public */,
      10,    2,   49,    2, 0x06,    8 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 6, 0x80000000 | 6,    7,    9,
    QMetaType::Void, 0x80000000 | 6, QMetaType::Bool,    7,   11,

       0        // eod
};

Q_CONSTINIT const QMetaObject ComponentManager::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_ComponentManager.offsetsAndSizes,
    qt_meta_data_ComponentManager,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_ComponentManager_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<ComponentManager, std::true_type>,
        // method 'componentAdded'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const ComponentInfo &, std::false_type>,
        // method 'componentDeleted'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QStandardItem *, std::false_type>,
        // method 'componentMoved'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QStandardItem *, std::false_type>,
        QtPrivate::TypeAndForceComplete<QStandardItem *, std::false_type>,
        // method 'componentOrderChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QStandardItem *, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>
    >,
    nullptr
} };

void ComponentManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ComponentManager *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->componentAdded((*reinterpret_cast< std::add_pointer_t<ComponentInfo>>(_a[1]))); break;
        case 1: _t->componentDeleted((*reinterpret_cast< std::add_pointer_t<QStandardItem*>>(_a[1]))); break;
        case 2: _t->componentMoved((*reinterpret_cast< std::add_pointer_t<QStandardItem*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QStandardItem*>>(_a[2]))); break;
        case 3: _t->componentOrderChanged((*reinterpret_cast< std::add_pointer_t<QStandardItem*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ComponentManager::*)(const ComponentInfo & );
            if (_t _q_method = &ComponentManager::componentAdded; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ComponentManager::*)(QStandardItem * );
            if (_t _q_method = &ComponentManager::componentDeleted; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ComponentManager::*)(QStandardItem * , QStandardItem * );
            if (_t _q_method = &ComponentManager::componentMoved; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ComponentManager::*)(QStandardItem * , bool );
            if (_t _q_method = &ComponentManager::componentOrderChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject *ComponentManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ComponentManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ComponentManager.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ComponentManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void ComponentManager::componentAdded(const ComponentInfo & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ComponentManager::componentDeleted(QStandardItem * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ComponentManager::componentMoved(QStandardItem * _t1, QStandardItem * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ComponentManager::componentOrderChanged(QStandardItem * _t1, bool _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
