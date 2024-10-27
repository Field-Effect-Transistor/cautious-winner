#include "errorDialog.hpp"

errorDialog::errorDialog(const QString& msg, QWidget* parent) : QDialog(parent) {
    layout = new QVBoxLayout(this);
    label = new QLabel(msg, this);
    okButton = new QPushButton("Ok", this);
    layout->addWidget(label);
    layout->addWidget(okButton);
    layout->setAlignment(label, Qt::AlignCenter);
    layout->setAlignment(okButton, Qt::AlignCenter);
    layout->setContentsMargins(10, 10, 10, 10);
    setLayout(layout);
    setWindowTitle("Error");
    setFixedSize(200, 100);
    connect(okButton, &QPushButton::clicked, this, &QDialog::accept);
}

errorDialog::~errorDialog() {}