#ifndef THEMEMANAGER_H
#define THEMEMANAGER_H

#include <QObject>
#include <QString>
#include <QMap>

class ThemeManager : public QObject
{
    Q_OBJECT

public:
    explicit ThemeManager(QObject *parent = nullptr);
    ~ThemeManager();

    enum Theme {
        Default,
        AtomOne,
        SolarizedLight
    };

    void applyTheme(Theme theme);
    QString getThemeStyleSheet(Theme theme) const;
    QStringList getAvailableThemes() const;

private:
    QMap<Theme, QString> m_themeStyleSheets;
    QMap<Theme, QString> m_themeFilePaths;
    Theme m_currentTheme;

    void initializeThemes();
    QString loadStyleSheetFromFile(const QString &filePath) const;
};

#endif // THEMEMANAGER_H
