#ifndef HOSTMODULECONFIGDIALOG_H
#define HOSTMODULECONFIGDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QSpinBox>
#include <QComboBox>
#include <QCheckBox>
#include <QTextEdit>
#include <QPushButton>
#include <QLabel>
#include "hostmodule.h"

class HostModuleConfigDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit HostModuleConfigDialog(HostModule *module, QWidget *parent = nullptr);
    ~HostModuleConfigDialog();
    
private slots:
    void onProtocolChanged(int index);
    void onDhcpToggled(bool enabled);
    void onTestConnection();
    void saveConfiguration();
    void validateInput();
    
private:
    void setupUI();
    void loadConfiguration();
    void updateNetworkFields(bool enabled);
    
    HostModule *m_module;
    
    // 基本信息
    QLineEdit *m_hostNameEdit;
    QTextEdit *m_descriptionEdit;
    
    // 网络配置
    QCheckBox *m_dhcpCheckBox;
    QLineEdit *m_ipAddressEdit;
    QLineEdit *m_subnetMaskEdit;
    QLineEdit *m_gatewayEdit;
    
    // 通信配置
    QComboBox *m_protocolCombo;
    QSpinBox *m_portSpinBox;
    
    // 按钮
    QPushButton *m_testButton;
    QPushButton *m_saveButton;
    QPushButton *m_cancelButton;
    
    // 状态标签
    QLabel *m_statusLabel;
};

#endif // HOSTMODULECONFIGDIALOG_H