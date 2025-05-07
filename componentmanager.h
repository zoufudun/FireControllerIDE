#ifndef COMPONENTMANAGER_H
#define COMPONENTMANAGER_H

#include <QObject>
#include <QList>
#include <QString>
#include <QStandardItem>

// 组件信息结构
struct ComponentInfo {
    QString name;        // 组件名称
    QString type;        // 组件类型
    QString description; // 组件描述
    int level;           // 组件层级 (1: 主机模块, 2: 其他模块)
};

class ComponentManager : public QObject
{
    Q_OBJECT

public:
    explicit ComponentManager(QObject *parent = nullptr);
    ~ComponentManager();

    void showAddComponentDialog();
    void showConfigureComponentDialog();
    void showDeleteComponentDialog(QStandardItem *item); // 添加删除组件的对话框
    void showMoveComponentDialog(QStandardItem *item);   // 添加移动组件的对话框
    QList<ComponentInfo> getComponentTypes() const;

signals:
    void componentAdded(const ComponentInfo &component);
    void componentDeleted(QStandardItem *item);          // 添加组件删除信号
    void componentMoved(QStandardItem *item, QStandardItem *newParent); // 添加组件移动信号

private:
    void initializeComponentTypes();
    QList<ComponentInfo> m_componentTypes;
};

#endif // COMPONENTMANAGER_H
