#include <QtGui>
#include "ClockWindow.h"

ClockWindow::ClockWindow()
{
  createActions();
  createTrayIcon();

  connect(
    m_trayIcon,
    SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
    this,
    SLOT(iconActivate(QSystemTrayIcon::ActivationReason)));

  setIcon();

  m_trayIcon->show();

  m_ticks = 0;

  m_timerId = startTimer(500);
}

void ClockWindow::setVisible(bool visible)
{
  QDialog::setVisible(false);
}

void ClockWindow::closeEvent(QCloseEvent *event)
{
  ;
}

float ClockWindow::getBeatTime()
{
  QDateTime currentDate = QDateTime::currentDateTime().toUTC();

  QTime currTime = currentDate.time();

  currTime.addSecs(3600);

  unsigned int secs = (currTime.hour() * 3600) + (currTime.minute() * 60) + currTime.second() + 3600;

  //double beats = floor(secs / 86.4);
  double beats = secs / 86.4;

  if (beats > 1000)
    beats -= 1000;

  if (beats < 0)
    beats += 1000;

  return beats;
}

void ClockWindow::timerEvent(QTimerEvent *event)
{
  if (event->timerId() == m_timerId)
  {
    m_trayIcon->setToolTip(tr("@%1").arg(getBeatTime()));
  }
}

void ClockWindow::setIcon()
{
  m_trayIcon->setIcon(QIcon(":/images/tray.jpg"));
}

void ClockWindow::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
  ;
}

void ClockWindow::createActions()
{
  m_quitAction = new QAction(tr("&Quit"), this);
  connect(m_quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
}

void ClockWindow::createTrayIcon()
{
  m_trayIconMenu = new QMenu(this);

  m_trayIconMenu->addAction(m_quitAction);

  m_trayIcon = new QSystemTrayIcon(this);
  m_trayIcon->setContextMenu(m_trayIconMenu);
}
