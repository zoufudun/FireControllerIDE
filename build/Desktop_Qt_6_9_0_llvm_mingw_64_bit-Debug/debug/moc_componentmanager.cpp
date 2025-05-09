/****************************************************************************
** Meta object code from reading C++ file 'componentmanager.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../componentmanager.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'componentmanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.9.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN16ComponentManagerE_t {};
} // unnamed namespace

template <> constexpr inline auto ComponentManager::qt_create_metaobjectdata<qt_meta_tag_ZN16ComponentManagerE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
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

    QtMocHelpers::UintData qt_methods {
        // Signal 'componentAdded'
        QtMocHelpers::SignalData<void(const ComponentInfo &)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 },
        }}),
        // Signal 'componentDeleted'
        QtMocHelpers::SignalData<void(QStandardItem *)>(5, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 6, 7 },
        }}),
        // Signal 'componentMoved'
        QtMocHelpers::SignalData<void(QStandardItem *, QStandardItem *)>(8, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 6, 7 }, { 0x80000000 | 6, 9 },
        }}),
        // Signal 'componentOrderChanged'
        QtMocHelpers::SignalData<void(QStandardItem *, bool)>(10, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 6, 7 }, { QMetaType::Bool, 11 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<ComponentManager, qt_meta_tag_ZN16ComponentManagerE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject ComponentManager::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN16ComponentManagerE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN16ComponentManagerE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN16ComponentManagerE_t>.metaTypes,
    nullptr
} };

void ComponentManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<ComponentManager *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->componentAdded((*reinterpret_cast< std::add_pointer_t<ComponentInfo>>(_a[1]))); break;
        case 1: _t->componentDeleted((*reinterpret_cast< std::add_pointer_t<QStandardItem*>>(_a[1]))); break;
        case 2: _t->componentMoved((*reinterpret_cast< std::add_pointer_t<QStandardItem*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QStandardItem*>>(_a[2]))); break;
        case 3: _t->componentOrderChanged((*reinterpret_cast< std::add_pointer_t<QStandardItem*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[2]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (ComponentManager::*)(const ComponentInfo & )>(_a, &ComponentManager::componentAdded, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (ComponentManager::*)(QStandardItem * )>(_a, &ComponentManager::componentDeleted, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (ComponentManager::*)(QStandardItem * , QStandardItem * )>(_a, &ComponentManager::componentMoved, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (ComponentManager::*)(QStandardItem * , bool )>(_a, &ComponentManager::componentOrderChanged, 3))
            return;
    }
}

const QMetaObject *ComponentManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ComponentManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN16ComponentManagerE_t>.strings))
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
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void ComponentManager::componentAdded(const ComponentInfo & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}

// SIGNAL 1
void ComponentManager::componentDeleted(QStandardItem * _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1);
}

// SIGNAL 2
void ComponentManager::componentMoved(QStandardItem * _t1, QStandardItem * _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1, _t2);
}

// SIGNAL 3
void ComponentManager::componentOrderChanged(QStandardItem * _t1, bool _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 3, nullptr, _t1, _t2);
}
QT_WARNING_POP
