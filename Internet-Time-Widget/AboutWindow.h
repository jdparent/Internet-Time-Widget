#ifndef ABOUTWINDOW_H
#define ABOUTWINDOW_H

#include <QDialog>

class QLabel;
class QPushButton;

class AboutWindow : public QDialog
{
Q_OBJECT
public:
    AboutWindow();

signals:

public slots:

private:
    QLabel *m_appName;
    QLabel *m_description;
    QLabel *m_creator;
    QLabel *m_version;
    QPushButton *m_okButton;
};

#endif // ABOUTWINDOW_H
