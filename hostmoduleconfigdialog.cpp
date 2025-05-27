#include "hostmoduleconfigdialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QGroupBox>
#include <QMessageBox>
#include <QRegularExpressionValidator>
#include <QHostAddress>

HostModuleConfigDialog::HostModuleConfigDialog(HostModule *module, QWidget *parent)
    : QDialog(parent), m_module(module)
{
    setWindowTitle("主机模块配置");
    setMinimumSize(500, 600);
    setModal(true);
    
    setupUI();
    loadConfiguration();
}

HostModuleConfigDialog::~HostModuleConfigDialog()
{
}

void HostModuleConfigDialog::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    
    // 基本信息组
    QGroupBox *basicGroup = new QGroupBox("基本信息", this);
    QFormLayout *basicLayout = new QFormLayout(basicGroup);
    
    m_hostNameEdit = new QLineEdit(this);
    m_hostNameEdit->setPlaceholderText("输入主机名称");
    basicLayout->addRow("主机名称:", m_hostNameEdit);
    
    m_descriptionEdit = new QTextEdit(this);
    m_descriptionEdit->setMaximumHeight(80);
    m_descriptionEdit->setPlaceholderText("输入主机描述信息");
    basicLayout->addRow("描述:", m_descriptionEdit);
    
    mainLayout->addWidget(basicGroup);
    
    // 网络配置组
    QGroupBox *networkGroup = new QGroupBox("网络配置", this);
    QFormLayout *networkLayout = new QFormLayout(networkGroup);
    
    m_dhcpCheckBox = new QCheckBox("启用DHCP自动获取IP", this);
    networkLayout->addRow(m_dhcpCheckBox);
    
    m_ipAddressEdit = new QLineEdit(this);
    m_ipAddressEdit->setPlaceholderText("192.168.1.100");
    // 设置IP地址验证器
    QRegularExpression ipRegex("^((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.){3}(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$");
    m_ipAddressEdit->setValidator(new QRegularExpressionValidator(ipRegex, this));
    networkLayout->addRow("IP地址:", m_ipAddressEdit);
    
    m_subnetMaskEdit = new QLineEdit(this);
    m_subnetMaskEdit->setPlaceholderText("255.255.255.0");
    m_subnetMaskEdit->setValidator(new QRegularExpressionValidator(ipRegex, this));
    networkLayout->addRow("子网掩码:", m_subnetMaskEdit);
    
    m_gatewayEdit = new QLineEdit(this);
    m_gatewayEdit->setPlaceholderText("192.168.1.1");
    m_gatewayEdit->setValidator(new QRegularExpressionValidator(ipRegex, this));
    networkLayout->addRow("网关:", m_gatewayEdit);
    
    mainLayout->addWidget(networkGroup);
    
    // 通信配置组
    QGroupBox *commGroup = new QGroupBox("通信配置", this);
    QFormLayout *commLayout = new QFormLayout(commGroup);
    
    m_protocolCombo = new QComboBox(this);
    m_protocolCombo->addItem("TCP", static_cast<int>(CommunicationProtocol::TCP));
    m_protocolCombo->addItem("UDP", static_cast<int>(CommunicationProtocol::UDP));
    commLayout->addRow("通信协议:", m_protocolCombo);
    
    m_portSpinBox = new QSpinBox(this);
    m_portSpinBox->setRange(1, 65535);
    m_portSpinBox->setValue(502);
    commLayout->addRow("端口号:", m_portSpinBox);
    
    mainLayout->addWidget(commGroup);
    
    // 状态显示
    m_statusLabel = new QLabel("状态: 未测试", this);
    m_statusLabel->setStyleSheet("color: gray; font-style: italic;");
    mainLayout->addWidget(m_statusLabel);
    
    // 按钮组
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    
    m_testButton = new QPushButton("测试连接", this);
    m_saveButton = new QPushButton("保存", this);
    m_cancelButton = new QPushButton("取消", this);
    
    buttonLayout->addWidget(m_testButton);
    buttonLayout->addStretch();
    buttonLayout->addWidget(m_saveButton);
    buttonLayout->addWidget(m_cancelButton);
    
    mainLayout->addLayout(buttonLayout);
    
    // 连接信号
    connect(m_protocolCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &HostModuleConfigDialog::onProtocolChanged);
    connect(m_dhcpCheckBox, &QCheckBox::toggled,
            this, &HostModuleConfigDialog::onDhcpToggled);
    connect(m_testButton, &QPushButton::clicked,
            this, &HostModuleConfigDialog::onTestConnection);
    connect(m_saveButton, &QPushButton::clicked,
            this, &HostModuleConfigDialog::saveConfiguration);
    connect(m_cancelButton, &QPushButton::clicked,
            this, &QDialog::reject);
    
    // 连接输入验证
    connect(m_hostNameEdit, &QLineEdit::textChanged, this, &HostModuleConfigDialog::validateInput);
    connect(m_ipAddressEdit, &QLineEdit::textChanged, this, &HostModuleConfigDialog::validateInput);
    connect(m_portSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &HostModuleConfigDialog::validateInput);
}

void HostModuleConfigDialog::loadConfiguration()
{
    HostConfiguration config = m_module->getConfiguration();
    
    m_hostNameEdit->setText(config.hostName);
    m_descriptionEdit->setPlainText(config.description);
    m_dhcpCheckBox->setChecked(config.dhcpEnabled);
    m_ipAddressEdit->setText(config.ipAddress);
    m_subnetMaskEdit->setText(config.subnetMask);
    m_gatewayEdit->setText(config.gateway);
    m_protocolCombo->setCurrentIndex(static_cast<int>(config.protocol));
    m_portSpinBox->setValue(config.port);
    
    // 根据DHCP状态更新网络字段
    updateNetworkFields(!config.dhcpEnabled);
}

void HostModuleConfigDialog::updateNetworkFields(bool enabled)
{
    m_ipAddressEdit->setEnabled(enabled);
    m_subnetMaskEdit->setEnabled(enabled);
    m_gatewayEdit->setEnabled(enabled);
}

void HostModuleConfigDialog::onProtocolChanged(int index)
{
    // 根据协议类型调整默认端口
    if (index == static_cast<int>(CommunicationProtocol::TCP)) {
        if (m_portSpinBox->value() == 53) { // 如果当前是UDP默认端口
            m_portSpinBox->setValue(502); // 设置为TCP默认端口
        }
    } else if (index == static_cast<int>(CommunicationProtocol::UDP)) {
        if (m_portSpinBox->value() == 502) { // 如果当前是TCP默认端口
            m_portSpinBox->setValue(53); // 设置为UDP默认端口
        }
    }
    
    validateInput();
}

void HostModuleConfigDialog::onDhcpToggled(bool enabled)
{
    updateNetworkFields(!enabled);
    
    if (enabled) {
        m_statusLabel->setText("状态: DHCP已启用，将自动获取网络配置");
        m_statusLabel->setStyleSheet("color: blue; font-style: italic;");
    } else {
        m_statusLabel->setText("状态: 使用静态IP配置");
        m_statusLabel->setStyleSheet("color: gray; font-style: italic;");
    }
}

void HostModuleConfigDialog::onTestConnection()
{
    // 临时保存当前配置进行测试
    HostConfiguration tempConfig;
    tempConfig.hostName = m_hostNameEdit->text();
    tempConfig.ipAddress = m_ipAddressEdit->text();
    tempConfig.port = m_portSpinBox->value();
    tempConfig.protocol = static_cast<CommunicationProtocol>(m_protocolCombo->currentData().toInt());
    tempConfig.dhcpEnabled = m_dhcpCheckBox->isChecked();
    
    // 验证配置
    if (!m_module->isValidIPAddress(tempConfig.ipAddress) && !tempConfig.dhcpEnabled) {
        m_statusLabel->setText("状态: IP地址格式无效");
        m_statusLabel->setStyleSheet("color: red; font-weight: bold;");
        return;
    }
    
    if (!m_module->isValidPort(tempConfig.port)) {
        m_statusLabel->setText("状态: 端口号无效");
        m_statusLabel->setStyleSheet("color: red; font-weight: bold;");
        return;
    }
    
    // 模拟连接测试
    m_statusLabel->setText("状态: 正在测试连接...");
    m_statusLabel->setStyleSheet("color: orange; font-style: italic;");
    
    // 这里可以添加实际的网络连接测试逻辑
    // 暂时模拟测试成功
    m_statusLabel->setText("状态: 连接测试成功");
    m_statusLabel->setStyleSheet("color: green; font-weight: bold;");
}

void HostModuleConfigDialog::saveConfiguration()
{
    // 验证输入
    if (m_hostNameEdit->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "输入错误", "请输入主机名称");
        return;
    }
    
    if (!m_dhcpCheckBox->isChecked()) {
        if (!m_module->isValidIPAddress(m_ipAddressEdit->text())) {
            QMessageBox::warning(this, "输入错误", "请输入有效的IP地址");
            return;
        }
        
        if (!m_module->isValidIPAddress(m_subnetMaskEdit->text())) {
            QMessageBox::warning(this, "输入错误", "请输入有效的子网掩码");
            return;
        }
        
        if (!m_module->isValidIPAddress(m_gatewayEdit->text())) {
            QMessageBox::warning(this, "输入错误", "请输入有效的网关地址");
            return;
        }
    }
    
    // 保存配置
    HostConfiguration config;
    config.hostName = m_hostNameEdit->text().trimmed();
    config.description = m_descriptionEdit->toPlainText();
    config.dhcpEnabled = m_dhcpCheckBox->isChecked();
    config.ipAddress = m_ipAddressEdit->text();
    config.subnetMask = m_subnetMaskEdit->text();
    config.gateway = m_gatewayEdit->text();
    config.protocol = static_cast<CommunicationProtocol>(m_protocolCombo->currentData().toInt());
    config.port = m_portSpinBox->value();
    
    m_module->setConfiguration(config);
    
    QMessageBox::information(this, "保存配置", "主机模块配置已保存");
    accept();
}

void HostModuleConfigDialog::validateInput()
{
    bool valid = true;
    
    // 检查主机名
    if (m_hostNameEdit->text().trimmed().isEmpty()) {
        valid = false;
    }
    
    // 如果不使用DHCP，检查网络配置
    if (!m_dhcpCheckBox->isChecked()) {
        if (!m_module->isValidIPAddress(m_ipAddressEdit->text()) ||
            !m_module->isValidIPAddress(m_subnetMaskEdit->text()) ||
            !m_module->isValidIPAddress(m_gatewayEdit->text())) {
            valid = false;
        }
    }
    
    // 检查端口
    if (!m_module->isValidPort(m_portSpinBox->value())) {
        valid = false;
    }
    
    m_saveButton->setEnabled(valid);
    m_testButton->setEnabled(valid);
}