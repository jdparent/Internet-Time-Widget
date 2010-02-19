#ifndef CLOCKWINDOW_H
#define CLOCKWINDOW_H

#include <QSystemTrayIcon>
#include <QDialog>
#include <QLCDNumber>

#include "AboutWindow.h"

QT_BEGIN_NAMESPACE
class QAction;
class QLCDNumber;
class QMenu;
QT_END_NAMESPACE

class ClockWindow : public QDialog
{
  Q_OBJECT

public:
  ClockWindow();

  void setVisible(bool visible);

  float getBeatTime();
  QString getBeatTimeString(bool full = false);

protected:
  void closeEvent(QCloseEvent *event);
  void timerEvent(QTimerEvent *event);

private slots:
  void iconActivated(QSystemTrayIcon::ActivationReason reason);

private:
  void createActions();
  void createTrayIcon();

  QAction *m_aboutAction;
  QAction *m_restoreAction;
  QAction *m_quitAction;

  QLabel *m_beatTime;

  QSystemTrayIcon *m_trayIcon;
  QMenu *m_trayIconMenu;

  AboutWindow *m_aboutWindow;

  int m_timerId;
};

#endif // CLOCKWINDOW_H
