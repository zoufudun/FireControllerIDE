#include "componentmanager.h"
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QDialogButtonBox>
#include <QLineEdit>
#include <QTreeView>     // 添加此头文件
#include <QStandardItem> // 添加此头文件

ComponentManager::ComponentManager(QObject *parent)
    : QObject(parent)
{
    // 初始化组件类型列表
    initializeComponentTypes();
}

ComponentManager::~ComponentManager()
{
}

void ComponentManager::initializeComponentTypes()
{
    // 定义组件类型及其层级关系
    // 第一层级 - 主机模块
    ComponentInfo hostModule;
    hostModule.name = "主机模块";
    hostModule.type = "HostModule";
    hostModule.description = "控制器主机模块";
    hostModule.level = 1;
    m_componentTypes.append(hostModule);
    
    // 第二层级 - 其他模块
    QStringList secondLevelModules = {
        "回路模块", "DI模块", "DO模块", "AI模块", "继电器模块", "通信模块"
    };
    
    for (const QString &moduleName : secondLevelModules) {
        ComponentInfo module;
        module.name = moduleName;
        QString typeStr = moduleName;
        module.type = typeStr.replace("模块", "Module");
        module.description = QString("%1，连接到主机模块").arg(moduleName);
        module.level = 2;
        m_componentTypes.append(module);
    }
}

void ComponentManager::showAddComponentDialog()
{
    QDialog dialog;
    dialog.setWindowTitle("添加组件");
    dialog.setMinimumWidth(400);
    
    QVBoxLayout *layout = new QVBoxLayout(&dialog);
    
    QLabel *label = new QLabel("选择要添加的组件类型:");
    layout->addWidget(label);
    
    QListWidget *componentList = new QListWidget(&dialog);
    for (const ComponentInfo &component : m_componentTypes) {
        QListWidgetItem *item = new QListWidgetItem(component.name);
        item->setToolTip(component.description);
        item->setData(Qt::UserRole, component.type);
        item->setData(Qt::UserRole + 1, component.level);
        componentList->addItem(item);
    }
    layout->addWidget(componentList);
    
    // 添加组件命名输入框
    QHBoxLayout *nameLayout = new QHBoxLayout();
    QLabel *nameLabel = new QLabel("组件名称:");
    QLineEdit *nameEdit = new QLineEdit();
    nameLayout->addWidget(nameLabel);
    nameLayout->addWidget(nameEdit);
    layout->addLayout(nameLayout);
    
    // 当选择组件时，自动填充默认名称
    connect(componentList, &QListWidget::currentItemChanged, [nameEdit, componentList](QListWidgetItem *current, QListWidgetItem *) {
        if (current) {
            nameEdit->setText(current->text());
            nameEdit->selectAll();
        }
    });
    
    QDialogButtonBox *buttonBox = new QDialogButtonBox(
        QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dialog);
    layout->addWidget(buttonBox);
    
    connect(buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);
    
    // 如果没有选择组件，禁用确定按钮
    QPushButton *okButton = buttonBox->button(QDialogButtonBox::Ok);
    okButton->setEnabled(false);
    connect(componentList, &QListWidget::currentItemChanged, [okButton](QListWidgetItem *current, QListWidgetItem *) {
        okButton->setEnabled(current != nullptr);
    });
    
    if (dialog.exec() == QDialog::Accepted) {
        QListWidgetItem *selectedItem = componentList->currentItem();
        if (selectedItem) {
            QString componentName = nameEdit->text().trimmed();
            if (componentName.isEmpty()) {
                componentName = selectedItem->text();
            }
            
            QString componentType = selectedItem->data(Qt::UserRole).toString();
            int componentLevel = selectedItem->data(Qt::UserRole + 1).toInt();
            
            // 创建组件信息并发送信号
            ComponentInfo component;
            component.name = componentName;
            component.type = componentType;
            component.level = componentLevel;
            
            // 查找完整的组件信息
            for (const ComponentInfo &info : m_componentTypes) {
                if (info.type == componentType) {
                    component.description = info.description;
                    break;
                }
            }
            
            emit componentAdded(component);
        }
    }
}

void ComponentManager::showConfigureComponentDialog()
{
    // 实现组件配置对话框
    QMessageBox::information(nullptr, "配置组件", "组件配置功能将在后续版本中实现");
}

void ComponentManager::showDeleteComponentDialog(QStandardItem *item)
{
    if (!item) {
        return;
    }
    
    QMessageBox msgBox;
    msgBox.setWindowTitle("删除组件");
    msgBox.setText(QString("确定要删除组件 \"%1\" 吗?").arg(item->text()));
    msgBox.setInformativeText("此操作不可撤销。");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);
    
    if (msgBox.exec() == QMessageBox::Yes) {
        emit componentDeleted(item);
    }
}

void ComponentManager::showMoveComponentDialog(QStandardItem *item)
{
    if (!item) {
        return;
    }
    
    QDialog dialog;
    dialog.setWindowTitle("移动组件");
    dialog.setMinimumWidth(400);
    
    QVBoxLayout *layout = new QVBoxLayout(&dialog);
    
    QLabel *label = new QLabel(QString("选择 \"%1\" 的新位置:").arg(item->text()));
    layout->addWidget(label);
    
    // 获取项目模型
    QStandardItemModel *model = qobject_cast<QStandardItemModel*>(item->model());
    if (!model) {
        return;
    }
    
    // 创建树形视图显示可能的目标位置
    QTreeView *treeView = new QTreeView(&dialog);
    treeView->setModel(model);
    treeView->expandAll();
    layout->addWidget(treeView);
    
    QDialogButtonBox *buttonBox = new QDialogButtonBox(
        QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dialog);
    layout->addWidget(buttonBox);
    
    connect(buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);
    
    if (dialog.exec() == QDialog::Accepted) {
        QModelIndex selectedIndex = treeView->currentIndex();
        if (selectedIndex.isValid()) {
            QStandardItem *targetItem = model->itemFromIndex(selectedIndex);
            if (targetItem && targetItem != item) {
                emit componentMoved(item, targetItem);
            }
        }
    }
}

QList<ComponentInfo> ComponentManager::getComponentTypes() const
{
    return m_componentTypes;
}