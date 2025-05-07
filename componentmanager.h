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
#include <QList>
#include <QString>
#include <QStandardItem>

// 组件信息结构体
struct ComponentInfo {
    QString name;        // 组件名称
    QString type;        // 组件类型
    QString description; // 组件描述
    int level;           // 组件层级 (1: 主机模块, 2: 其他模块)
    QString iconPath;    // 组件图标路径
};

class ComponentManager : public QObject
{
    Q_OBJECT

public:
    explicit ComponentManager(QObject *parent = nullptr);
    ~ComponentManager();

    // 显示添加组件对话框
    void showAddComponentDialog();
    
    // 显示配置组件对话框
    void showConfigureComponentDialog();
    
    // 显示删除组件对话框
    void showDeleteComponentDialog(QStandardItem *item);
    
    // 显示移动组件对话框
    void showMoveComponentDialog(QStandardItem *item);
    
    // 移动组件顺序
    void moveComponentUp(QStandardItem *item);
    void moveComponentDown(QStandardItem *item);
    QList<ComponentInfo> getComponentTypes() const;

signals:
    // 组件添加信号
    void componentAdded(const ComponentInfo &component);
    
    // 组件删除信号
    void componentDeleted(QStandardItem *item);
    
    // 组件移动信号
    void componentMoved(QStandardItem *item, QStandardItem *newParent);
    
    // 组件顺序变更信号
    void componentOrderChanged(QStandardItem *item, bool moveUp);

private:
    // 组件类型列表
    QList<ComponentInfo> m_componentTypes;
    
    // 初始化组件类型
    void initializeComponentTypes();
};

#endif // COMPONENTMANAGER_H
