#include <QtGui>
#include "ClockWindow.h"

ClockWindow::ClockWindow()
{
  m_aboutWindow = new AboutWindow();

  createActions();
  createTrayIcon();

  QVBoxLayout *mainLayout = new QVBoxLayout;
  m_lcd = new QLCDNumber(6);
  m_lcd->setSegmentStyle(QLCDNumber::Flat);
  mainLayout->addWidget(m_lcd);
  setLayout(mainLayout);
  setWindowTitle(tr("Internet Time"));
  setFixedHeight(sizeHint().height());

  m_trayIcon->show();

  m_timerId = startTimer(500);
}

void ClockWindow::setVisible(bool visible)
{
  QDialog::setVisible(visible);
}

void ClockWindow::closeEvent(QCloseEvent *event)
{
  if (m_trayIcon->isVisible())
  {
    hide();
    event->ignore();
  }
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
    float beats = getBeatTime();

    m_trayIcon->setToolTip(tr("@%1").arg(beats));
    m_lcd->display((double)beats);
  }
}

void ClockWindow::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
  switch (reason)
  {
    case QSystemTrayIcon::DoubleClick:
    {
      show();
      break;
    }
    default:
    {
      break;
    }
  }
}

void ClockWindow::createActions()
{
  m_aboutAction = new QAction(tr("&About"), this);
  m_restoreAction = new QAction(tr("&Restore"), this);
  m_quitAction = new QAction(tr("&Quit"), this);

  connect(m_quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
  connect(m_restoreAction, SIGNAL(triggered()), this, SLOT(show()));
  connect(m_aboutAction, SIGNAL(triggered()), m_aboutWindow, SLOT(show()));
}

void ClockWindow::createTrayIcon()
{
  m_trayIconMenu = new QMenu(this);

  m_trayIconMenu->addAction(m_aboutAction);
  m_trayIconMenu->addAction(m_restoreAction);
  m_trayIconMenu->addSeparator();
  m_trayIconMenu->addAction(m_quitAction);

  m_trayIcon = new QSystemTrayIcon(this);
  m_trayIcon->setContextMenu(m_trayIconMenu);

  m_trayIcon->setIcon(QIcon(":/images/tray.jpg"));

  connect(
    m_trayIcon,
    SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
    this,
    SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
}
