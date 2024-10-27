#include "guestWidget.hpp"

guestWidget::guestWidget(QWidget *parent) : QWidget(parent) {
    try {
        layout = new QBoxLayout(QBoxLayout::TopToBottom, this);
        inputBoxLayout = new QBoxLayout(QBoxLayout::TopToBottom);
        buttonBoxLayout = new QBoxLayout(QBoxLayout::TopToBottom);

        inputGB = new QGroupBox(this);
        buttonGB = new QGroupBox(this);

        guestLoginBtn = new QPushButton("Guest login", this);
        retBtn = new QPushButton("Return", this);

        // inputs
        emailIn = new QLineEdit(this);
        emailIn->setAlignment(Qt::AlignLeft);
        emailIn->setPlaceholderText("email");

        licenseIn = new QLineEdit(this);
        licenseIn->setAlignment(Qt::AlignLeft);
        licenseIn->setPlaceholderText("license plate");

        // Arrange input fields
        inputBoxLayout->addWidget(emailIn);
        inputBoxLayout->addWidget(licenseIn);
        inputGB->setLayout(inputBoxLayout);
        inputGB->setMinimumWidth(300);

        // Arrange buttons
        buttonBoxLayout->addWidget(guestLoginBtn);
        buttonBoxLayout->addWidget(retBtn);
        buttonGB->setLayout(buttonBoxLayout);
        buttonGB->setMinimumWidth(300);

        // Set layout and alignment
        layout->addWidget(inputGB);
        layout->addWidget(buttonGB);
        layout->setAlignment(inputGB, Qt::AlignHCenter | Qt::AlignTop);
        layout->setAlignment(buttonGB, Qt::AlignHCenter | Qt::AlignTop);
        //setLayout(layout);
        setWindowTitle("Guest login");
    } catch (const std::bad_alloc& e) {
        qCritical() << "Memory allocation failed:" << e.what();
        QMessageBox::critical(this, "Error", "Failed to initialize UI due to memory allocation error.");
    } catch (const std::exception& e) {
        qCritical() << "Exception occurred:" << e.what();
        QMessageBox::critical(this, "Error", "An error occurred during widget initialization.");
    } catch (...) {
        qCritical() << "An unknown error occurred during widget initialization.";
        QMessageBox::critical(this, "Error", "An unknown error occurred.");
    }
}

guestWidget::~guestWidget() {}
