#include "mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QListWidget>
#include <QTreeWidget>
#include <QStandardItemModel>
#include <QStatusBar>
#include <QInputDialog> // 添加此头文件
#include <QMenu>        // 添加此头文件

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    projectManager = new ProjectManager(this);
    componentManager = new ComponentManager(this);
    
    setupUI();
    createActions();
    createMenus();
    createToolbars();
    createDockWindows();
    
    setWindowTitle(tr("Controller IDE"));
    setMinimumSize(800, 600);
    
    // 连接组件添加信号
    connect(componentManager, &ComponentManager::componentAdded, 
            this, &MainWindow::onComponentAdded);
    
    // 连接组件删除信号
    connect(componentManager, &ComponentManager::componentDeleted,
            this, &MainWindow::onComponentDeleted);
    
    // 连接组件移动信号
    connect(componentManager, &ComponentManager::componentMoved,
            this, &MainWindow::onComponentMoved);
}

MainWindow::~MainWindow()
{
}

void MainWindow::setupUI()
{
    // 中央编辑区域可以根据需要添加
    setCentralWidget(new QWidget());
}

void MainWindow::createActions()
{
    newProjectAction = new QAction(tr("新建项目"), this);
    connect(newProjectAction, &QAction::triggered, this, &MainWindow::newProject);
    
    openProjectAction = new QAction(tr("打开项目"), this);
    connect(openProjectAction, &QAction::triggered, this, &MainWindow::openProject);
    
    saveProjectAction = new QAction(tr("保存项目"), this);
    connect(saveProjectAction, &QAction::triggered, this, &MainWindow::saveProject);
    
    saveAsProjectAction = new QAction(tr("项目另存为"), this);
    connect(saveAsProjectAction, &QAction::triggered, this, &MainWindow::saveProjectAs);
    
    addComponentAction = new QAction(tr("添加组件"), this);
    connect(addComponentAction, &QAction::triggered, this, &MainWindow::addComponent);
    
    configureComponentAction = new QAction(tr("配置组件"), this);
    connect(configureComponentAction, &QAction::triggered, this, &MainWindow::configureComponent);
    
    exitAction = new QAction(tr("退出"), this);
    connect(exitAction, &QAction::triggered, this, &QWidget::close);
    
    renameProjectAction = new QAction(tr("重命名项目"), this);
    connect(renameProjectAction, &QAction::triggered, this, &MainWindow::renameProject);
    
    deleteComponentAction = new QAction(tr("删除组件"), this);
    connect(deleteComponentAction, &QAction::triggered, this, &MainWindow::deleteComponent);
    
    moveComponentAction = new QAction(tr("移动组件"), this);
    connect(moveComponentAction, &QAction::triggered, this, &MainWindow::moveComponent);
}

void MainWindow::createMenus()
{
    QMenu *fileMenu = menuBar()->addMenu(tr("文件"));
    fileMenu->addAction(newProjectAction);
    fileMenu->addAction(openProjectAction);
    fileMenu->addAction(saveProjectAction);
    fileMenu->addAction(saveAsProjectAction);
    fileMenu->addAction(renameProjectAction); // 添加重命名项目菜单项
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);
    
    QMenu *componentMenu = menuBar()->addMenu(tr("组件"));
    componentMenu->addAction(addComponentAction);
    componentMenu->addAction(deleteComponentAction); // 添加删除组件菜单项
    componentMenu->addAction(moveComponentAction);   // 添加移动组件菜单项
    componentMenu->addAction(configureComponentAction);
}

void MainWindow::createToolbars()
{
    QToolBar *fileToolBar = addToolBar(tr("文件"));
    fileToolBar->addAction(newProjectAction);
    fileToolBar->addAction(openProjectAction);
    fileToolBar->addAction(saveProjectAction);
    fileToolBar->addAction(renameProjectAction); // 添加重命名项目工具栏按钮
    
    QToolBar *componentToolBar = addToolBar(tr("组件"));
    componentToolBar->addAction(addComponentAction);
    componentToolBar->addAction(deleteComponentAction); // 添加删除组件工具栏按钮
    componentToolBar->addAction(moveComponentAction);   // 添加移动组件工具栏按钮
    componentToolBar->addAction(configureComponentAction);
}

void MainWindow::createDockWindows()
{
    // 项目树视图
    projectDock = new QDockWidget(tr("项目"), this);
    projectDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    projectTreeView = new QTreeView(projectDock);
    
    // 为项目树视图添加上下文菜单
    projectTreeView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(projectTreeView, &QTreeView::customContextMenuRequested, 
            this, &MainWindow::showProjectContextMenu);
    
    projectDock->setWidget(projectTreeView);
    addDockWidget(Qt::LeftDockWidgetArea, projectDock);
    
    // 组件列表
    componentDock = new QDockWidget(tr("组件库"), this);
    componentDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    QListWidget *componentList = new QListWidget(componentDock);
    componentDock->setWidget(componentList);
    addDockWidget(Qt::LeftDockWidgetArea, componentDock);
    
    // 属性编辑器
    propertiesDock = new QDockWidget(tr("属性"), this);
    propertiesDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    QTreeWidget *propertiesTree = new QTreeWidget(propertiesDock);
    propertiesDock->setWidget(propertiesTree);
    addDockWidget(Qt::RightDockWidgetArea, propertiesDock);
}

void MainWindow::newProject()
{
    if (projectManager->hasUnsavedChanges()) {
        QMessageBox::StandardButton reply = QMessageBox::question(
            this, tr("保存更改"), tr("是否保存当前项目的更改?"),
            QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel
        );
        
        if (reply == QMessageBox::Yes) {
            saveProject();
        } else if (reply == QMessageBox::Cancel) {
            return;
        }
    }
    
    projectManager->newProject();
}

void MainWindow::openProject()
{
    if (projectManager->hasUnsavedChanges()) {
        QMessageBox::StandardButton reply = QMessageBox::question(
            this, tr("保存更改"), tr("是否保存当前项目的更改?"),
            QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel
        );
        
        if (reply == QMessageBox::Yes) {
            saveProject();
        } else if (reply == QMessageBox::Cancel) {
            return;
        }
    }
    
    QString fileName = QFileDialog::getOpenFileName(
        this, tr("打开项目"), "", tr("XML 项目文件 (*.xml)")
    );
    
    if (!fileName.isEmpty()) {
        projectManager->loadProject(fileName);
    }
}

void MainWindow::saveProject()
{
    if (projectManager->currentProjectPath().isEmpty()) {
        saveProjectAs();
    } else {
        projectManager->saveProject(projectManager->currentProjectPath());
    }
}

void MainWindow::saveProjectAs()
{
    QString fileName = QFileDialog::getSaveFileName(
        this, tr("保存项目"), "", tr("XML 项目文件 (*.xml)")
    );
    
    if (!fileName.isEmpty()) {
        projectManager->saveProject(fileName);
    }
}

void MainWindow::addComponent()
{
    componentManager->showAddComponentDialog();
}

void MainWindow::configureComponent()
{
    // 显示组件配置对话框
    componentManager->showConfigureComponentDialog();
}

// 添加组件处理函数
void MainWindow::onComponentAdded(const ComponentInfo &component)
{
    // 获取项目树视图的模型
    QStandardItemModel *model = projectManager->projectModel();
    if (!model) {
        return;
    }
    
    // 如果项目为空，创建一个根节点
    if (model->rowCount() == 0) {
        QStandardItem *rootItem = new QStandardItem("新项目");
        model->appendRow(rootItem);
    }
    
    // 获取当前选中的项
    QModelIndex selectedIndex = projectTreeView->currentIndex();
    QStandardItem *parentItem = nullptr;
    
    if (selectedIndex.isValid()) {
        parentItem = model->itemFromIndex(selectedIndex);
    } else {
        parentItem = model->item(0); // 根节点
    }
    
    // 根据组件层级添加到项目树中
    if (component.level == 1) {
        // 第一层级 - 主机模块
        // 如果选中的是根节点，直接添加到根节点下
        // 如果选中的不是根节点，添加到根节点下
        QStandardItem *rootItem = model->item(0);
        QStandardItem *item = new QStandardItem(component.name);
        item->setData(component.type, Qt::UserRole);
        rootItem->appendRow(item);
    } else if (component.level == 2) {
        // 第二层级 - 其他模块，需要添加到主机模块下
        // 查找主机模块
        QStandardItem *hostItem = nullptr;
        
        // 如果选中的是主机模块，直接添加到主机模块下
        if (parentItem && parentItem->data(Qt::UserRole).toString() == "HostModule") {
            hostItem = parentItem;
        } else {
            // 否则查找主机模块
            QStandardItem *rootItem = model->item(0);
            for (int i = 0; i < rootItem->rowCount(); ++i) {
                QStandardItem *child = rootItem->child(i);
                if (child->data(Qt::UserRole).toString() == "HostModule") {
                    hostItem = child;
                    break;
                }
            }
        }
        
        if (!hostItem) {
            // 如果没有主机模块，先创建一个
            QMessageBox::warning(this, "添加组件", "请先添加主机模块！");
            return;
        }
        
        QStandardItem *item = new QStandardItem(component.name);
        item->setData(component.type, Qt::UserRole);
        hostItem->appendRow(item);
    }
    
    // 设置项目树视图的模型
    projectTreeView->setModel(model);
    projectTreeView->expandAll();
    
    // 标记项目有未保存的更改
    projectManager->setUnsavedChanges(true);
    
    statusBar()->showMessage(QString("已添加组件: %1").arg(component.name), 3000);
}

void MainWindow::renameProject()
{
    bool ok;
    QString newName = QInputDialog::getText(this, tr("重命名项目"),
                                           tr("项目名称:"), QLineEdit::Normal,
                                           projectManager->projectModel()->item(0)->text(), &ok);
    if (ok && !newName.isEmpty()) {
        projectManager->renameProject(newName);
        statusBar()->showMessage(tr("项目已重命名为: %1").arg(newName), 3000);
    }
}

void MainWindow::deleteComponent()
{
    QModelIndex currentIndex = projectTreeView->currentIndex();
    if (currentIndex.isValid() && currentIndex.parent().isValid()) {
        QStandardItem *item = projectManager->projectModel()->itemFromIndex(currentIndex);
        componentManager->showDeleteComponentDialog(item);
    } else {
        QMessageBox::warning(this, tr("删除组件"), tr("请先选择要删除的组件"));
    }
}

void MainWindow::moveComponent()
{
    QModelIndex currentIndex = projectTreeView->currentIndex();
    if (currentIndex.isValid() && currentIndex.parent().isValid()) {
        QStandardItem *item = projectManager->projectModel()->itemFromIndex(currentIndex);
        componentManager->showMoveComponentDialog(item);
    } else {
        QMessageBox::warning(this, tr("移动组件"), tr("请先选择要移动的组件"));
    }
}

void MainWindow::onComponentDeleted(QStandardItem *item)
{
    if (item) {
        QStandardItem *parentItem = item->parent();
        if (parentItem) {
            // 从父项中移除该项
            parentItem->removeRow(item->row());
            
            projectManager->setUnsavedChanges(true);
            statusBar()->showMessage(tr("组件已删除"), 3000);
        }
    }
}

void MainWindow::onComponentMoved(QStandardItem *item, QStandardItem *newParent)
{
    if (item && newParent) {
        QStandardItem *oldParent = item->parent();
        if (oldParent) {
            // 创建一个新的项，复制原项的数据
            QStandardItem *newItem = new QStandardItem(item->text());
            newItem->setData(item->data(Qt::UserRole), Qt::UserRole);
            
            // 从原位置移除
            oldParent->removeRow(item->row());
            
            // 添加到新位置
            newParent->appendRow(newItem);
            
            projectManager->setUnsavedChanges(true);
            statusBar()->showMessage(tr("组件已移动: %1").arg(item->text()), 3000);
        }
    }
}

void MainWindow::showProjectContextMenu(const QPoint &pos)
{
    QModelIndex index = projectTreeView->indexAt(pos);
    if (index.isValid()) {
        QMenu contextMenu(this);
        
        // 如果是根节点，添加重命名项目选项
        if (!index.parent().isValid()) {
            QAction *renameAction = new QAction(tr("重命名项目"), this);
            connect(renameAction, &QAction::triggered, this, &MainWindow::renameProject);
            contextMenu.addAction(renameAction);
            contextMenu.addSeparator();
        }
        
        // 添加组件选项
        QAction *addAction = new QAction(tr("添加组件"), this);
        connect(addAction, &QAction::triggered, this, &MainWindow::addComponent);
        contextMenu.addAction(addAction);
        
        // 如果不是根节点，添加组件配置和删除选项
        if (index.parent().isValid()) {
            QAction *configureAction = new QAction(tr("配置组件"), this);
            connect(configureAction, &QAction::triggered, this, [this]() {
                QModelIndex currentIndex = projectTreeView->currentIndex();
                if (currentIndex.isValid()) {
                    QStandardItem *item = projectManager->projectModel()->itemFromIndex(currentIndex);
                    componentManager->showConfigureComponentDialog();
                }
            });
            contextMenu.addAction(configureAction);
            
            QAction *deleteAction = new QAction(tr("删除组件"), this);
            connect(deleteAction, &QAction::triggered, this, [this]() {
                QModelIndex currentIndex = projectTreeView->currentIndex();
                if (currentIndex.isValid()) {
                    QStandardItem *item = projectManager->projectModel()->itemFromIndex(currentIndex);
                    componentManager->showDeleteComponentDialog(item);
                }
            });
            contextMenu.addAction(deleteAction);
            
            QAction *moveAction = new QAction(tr("移动组件"), this);
            connect(moveAction, &QAction::triggered, this, [this]() {
                QModelIndex currentIndex = projectTreeView->currentIndex();
                if (currentIndex.isValid()) {
                    QStandardItem *item = projectManager->projectModel()->itemFromIndex(currentIndex);
                    componentManager->showMoveComponentDialog(item);
                }
            });
            contextMenu.addAction(moveAction);
        }
        
        // 显示上下文菜单
        contextMenu.exec(projectTreeView->viewport()->mapToGlobal(pos));
    }
}