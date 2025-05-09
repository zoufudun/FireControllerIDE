/****************************************************************************
** Meta object code from reading C++ file 'domoduleconfigdialog.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../domoduleconfigdialog.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'domoduleconfigdialog.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN20DOModuleConfigDialogE_t {};
} // unnamed namespace

template <> constexpr inline auto DOModuleConfigDialog::qt_create_metaobjectdata<qt_meta_tag_ZN20DOModuleConfigDialogE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "DOModuleConfigDialog",
        "onChannelCountChanged",
        "",
        "index",
        "onBitVariableChanged",
        "row",
        "column",
        "saveConfiguration",
        "onChannelSelectionChanged"
    };

    QtMocHelpers::UintData qt_methods {
        // Slot 'onChannelCountChanged'
        QtMocHelpers::SlotData<void(int)>(1, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 3 },
        }}),
        // Slot 'onBitVariableChanged'
        QtMocHelpers::SlotData<void(int, int)>(4, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 5 }, { QMetaType::Int, 6 },
        }}),
        // Slot 'saveConfiguration'
        QtMocHelpers::SlotData<void()>(7, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onChannelSelectionChanged'
        QtMocHelpers::SlotData<void(int)>(8, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 3 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<DOModuleConfigDialog, qt_meta_tag_ZN20DOModuleConfigDialogE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject DOModuleConfigDialog::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN20DOModuleConfigDialogE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN20DOModuleConfigDialogE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN20DOModuleConfigDialogE_t>.metaTypes,
    nullptr
} };

void DOModuleConfigDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<DOModuleConfigDialog *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->onChannelCountChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 1: _t->onBitVariableChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 2: _t->saveConfiguration(); break;
        case 3: _t->onChannelSelectionChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject *DOModuleConfigDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DOModuleConfigDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN20DOModuleConfigDialogE_t>.strings))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int DOModuleConfigDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
