#ifndef PROJECTMANAGER_H
#define PROJECTMANAGER_H

#include <QObject>
#include <QString>
#include <QStandardItemModel>

class ProjectManager : public QObject
{
    Q_OBJECT

public:
    explicit ProjectManager(QObject *parent = nullptr);
    ~ProjectManager();
    
    bool hasUnsavedChanges() const;
    void setUnsavedChanges(bool unsaved);
    QString currentProjectPath() const;
    
    void newProject();
    void loadProject(const QString &path);
    void saveProject(const QString &path);
    void renameProject(const QString &newName); // 添加重命名项目的方法
    
    QStandardItemModel* projectModel();
    
private:
    QStandardItemModel *m_model;
    QString m_currentProjectPath;
    bool m_hasUnsavedChanges;
};

#endif // PROJECTMANAGER_H
