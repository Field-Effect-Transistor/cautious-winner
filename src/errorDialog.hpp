#pragma once

#include <QDialog>
#include <QLabel>
#include <QHBoxLayout>
#include <QPushButton>

class errorDialog : public QDialog {
    Q_OBJECT

protected:
    QVBoxLayout* layout;
    QLabel* label;
    QPushButton* okButton;
    
public:
    explicit errorDialog(const QString& msg, QWidget* parent = nullptr);
    ~errorDialog();
};