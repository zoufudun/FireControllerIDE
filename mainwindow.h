#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeView>
#include <QDockWidget>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include "projectmanager.h"
#include "componentmanager.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void newProject();
    void openProject();
    void saveProject();
    void saveProjectAs();
    void renameProject();           // 添加重命名项目的槽函数
    void addComponent();
    void deleteComponent();         // 添加删除组件的槽函数
    void moveComponent();           // 添加移动组件的槽函数
    void configureComponent();
    void onComponentAdded(const ComponentInfo &component);
    void onComponentDeleted(QStandardItem *item);
    void onComponentMoved(QStandardItem *item, QStandardItem *newParent);
    void showProjectContextMenu(const QPoint &pos);

private:
    void setupUI();
    void createActions();
    void createMenus();
    void createToolbars();
    void createDockWindows();

    QTreeView *projectTreeView;
    QDockWidget *projectDock;
    QDockWidget *componentDock;
    QDockWidget *propertiesDock;

    ProjectManager *projectManager;
    ComponentManager *componentManager;

    // Actions
    QAction *newProjectAction;
    QAction *openProjectAction;
    QAction *saveProjectAction;
    QAction *saveAsProjectAction;
    QAction *renameProjectAction;   // 添加重命名项目的动作
    QAction *addComponentAction;
    QAction *deleteComponentAction; // 添加删除组件的动作
    QAction *moveComponentAction;   // 添加移动组件的动作
    QAction *configureComponentAction;
    QAction *exitAction;
};

#endif // MAINWINDOW_H