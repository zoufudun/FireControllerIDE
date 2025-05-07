#include "thememanager.h"
#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QDir>

ThemeManager::ThemeManager(QObject *parent)
    : QObject(parent), m_currentTheme(Default)
{
    initializeThemes();
}

ThemeManager::~ThemeManager()
{
}

void ThemeManager::initializeThemes()
{
    // 设置主题文件路径
    m_themeFilePaths[Default] = "themes/default.qss";
    m_themeFilePaths[AtomOne] = "themes/atom_one.qss";
    m_themeFilePaths[SolarizedLight] = "themes/solarized_light.qss";

    // 加载主题样式表
    for (auto it = m_themeFilePaths.begin(); it != m_themeFilePaths.end(); ++it) {
        m_themeStyleSheets[it.key()] = loadStyleSheetFromFile(it.value());
    }
}

QString ThemeManager::loadStyleSheetFromFile(const QString &filePath) const
{
    QFile file(filePath);
    if (!file.exists()) {
        // 如果文件不存在，尝试从资源中加载
        file.setFileName(":" + filePath);
    }

    QString styleSheet;
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        styleSheet = stream.readAll();
        file.close();
    }

    return styleSheet;
}

void ThemeManager::applyTheme(Theme theme)
{
    if (m_themeStyleSheets.contains(theme)) {
        qApp->setStyleSheet(m_themeStyleSheets[theme]);
        m_currentTheme = theme;
    }
}

QString ThemeManager::getThemeStyleSheet(Theme theme) const
{
    return m_themeStyleSheets.value(theme, "");
}

QStringList ThemeManager::getAvailableThemes() const
{
    QStringList themes;
    themes << "默认主题" << "ATOM ONE" << "Solarized Light";
    return themes;
}
