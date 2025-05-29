/*
 * @Description: 
 * @Version: 1.0
 * @Autor: PhodonZou
 * @Date: 2025-05-07 11:48:40
 * @LastEditors: PhodonZou
 * @LastEditTime: 2025-05-07 19:20:55
 */
#ifndef COMPONENTMANAGER_H
#define COMPONENTMANAGER_H

#include <QObject>
#include <QString>
#include <QList>
#include <QStandardItem>
#include "dimodule.h"  // 添加DI模块头文件
#include "domodule.h"  // 添加DO模块头文件
#include "hostmodule.h"  // 添加主机模块头文件

// 组件信息结构体
struct ComponentInfo {
    QString name;
    QString type;
    QString description;
    int level;
    QString iconPath;
};

class ComponentManager : public QObject
{
    Q_OBJECT

public:
    explicit ComponentManager(QObject *parent = nullptr);
    ~ComponentManager();

    void showAddComponentDialog();
    void showConfigureComponentDialog(QStandardItem *item = nullptr);
    void showDeleteComponentDialog(QStandardItem *item);
    void showMoveComponentDialog(QStandardItem *item);
    void moveComponentUp(QStandardItem *item);
    void moveComponentDown(QStandardItem *item);
    // 添加DI模块配置对话框
    void showDIModuleConfigDialog(QStandardItem *item);
    
    // 添加DO模块配置对话框
    void showDOModuleConfigDialog(QStandardItem *item);
    // 添加主机模块配置对话框
    void showHostModuleConfigDialog(QStandardItem *item);
    QList<ComponentInfo> getComponentTypes() const;

signals:
    void componentAdded(const ComponentInfo &component);
    void componentDeleted(QStandardItem *item);
    void componentMoved(QStandardItem *item, QStandardItem *newParent);
    void componentOrderChanged(QStandardItem *item, bool moveUp);

private:
    void initializeComponentTypes();
    QList<ComponentInfo> m_componentTypes;
    
    // 添加DI模块实例
    DIModule *m_diModule;
    
    // 添加DO模块实例
    DOModule *m_doModule;
    
    // 移除单一的主机模块实例
    // HostModule *m_hostModule;
    
    // 添加主机模块映射，每个组件项对应一个独立的主机模块实例
    QMap<QStandardItem*, HostModule*> m_hostModules;
    
    // 添加辅助方法
    HostModule* getOrCreateHostModule(QStandardItem *item);
    void removeHostModule(QStandardItem *item);
};

#endif // COMPONENTMANAGER_H
