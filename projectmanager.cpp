#include "projectmanager.h"

ProjectManager::ProjectManager(QObject *parent)
    : QObject(parent), m_hasUnsavedChanges(false)
{
    m_model = new QStandardItemModel(this);
    m_model->setHorizontalHeaderLabels(QStringList() << "项目结构");
}

ProjectManager::~ProjectManager()
{
}

bool ProjectManager::hasUnsavedChanges() const
{
    return m_hasUnsavedChanges;
}

void ProjectManager::newProject()
{
    m_currentProjectPath.clear();
    m_hasUnsavedChanges = false;
    // Add initialization code for a new project
}

void ProjectManager::loadProject(const QString &path)
{
    m_currentProjectPath = path;
    m_hasUnsavedChanges = false;
    // Add code to load project from file
}

void ProjectManager::saveProject(const QString &path)
{
    m_currentProjectPath = path;
    m_hasUnsavedChanges = false;
    // Add code to save project to file
}

void ProjectManager::setUnsavedChanges(bool unsaved)
{
    m_hasUnsavedChanges = unsaved;
}

QString ProjectManager::currentProjectPath() const
{
    return m_currentProjectPath;
}

QStandardItemModel* ProjectManager::projectModel()
{
    return m_model;
}

void ProjectManager::renameProject(const QString &newName)
{
    if (m_model->rowCount() > 0) {
        QStandardItem *rootItem = m_model->item(0);
        rootItem->setText(newName);
        m_hasUnsavedChanges = true;
    }
}