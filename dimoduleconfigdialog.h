#ifndef DIMODULECONFIGDIALOG_H
#define DIMODULECONFIGDIALOG_H

#include <QDialog>
#include <QComboBox>
#include <QTabWidget>
#include <QTableWidget>
#include <QPushButton>
#include "dimodule.h"

class DIModuleConfigDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit DIModuleConfigDialog(DIModule *module, QWidget *parent = nullptr);
    ~DIModuleConfigDialog();
    
private slots:
    void onChannelCountChanged(int index);
    void onBitVariableChanged(int row, int column);
    void saveConfiguration();
    void onChannelSelectionChanged(int index);
    
private:
    void setupUI();
    void updateChannelTabs();
    void updateBitTable(int channelIndex);
    
    DIModule *m_module;
    QComboBox *m_channelCountCombo;
    QComboBox *m_channelSelectCombo;
    //QTabWidget *m_channelTabs;
    QTableWidget *m_bitTable;
    //QVector<QTableWidget*> m_bitTables;
    
    QPushButton *m_saveButton;
    QPushButton *m_cancelButton;
    int m_currentChannelIndex; // 通道数量
};

#endif // DIMODULECONFIGDIALOG_H
