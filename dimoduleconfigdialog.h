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
    QComboBox *m_channelSelectCombo;  // 通道选择下拉框
    QTableWidget *m_bitTable;         // 使用单个表格替代多个选项卡
    QPushButton *m_saveButton;
    QPushButton *m_cancelButton;
    int m_currentChannelIndex;        // 当前选中的通道索引
};

#endif // DIMODULECONFIGDIALOG_H
