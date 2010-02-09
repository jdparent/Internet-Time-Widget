#ifndef CLOCKWINDOW_H
#define CLOCKWINDOW_H

#include <QSystemTrayIcon>
#include <QDialog>

class ClockWindow : public QDialog
{
  Q_OBJECT

public:
  ClockWindow();

  void setVisible(bool visible);

  float getBeatTime();

protected:
  void closeEvent(QCloseEvent *event);
  void timerEvent(QTimerEvent *event);

private slots:
  void setIcon();
  void iconActivated(QSystemTrayIcon::ActivationReason reason);

private:
  void createActions();
  void createTrayIcon();

  QAction *m_quitAction;

  QSystemTrayIcon *m_trayIcon;
  QMenu *m_trayIconMenu;

  int m_timerId;
  int m_ticks;
};

#endif // CLOCKWINDOW_H
