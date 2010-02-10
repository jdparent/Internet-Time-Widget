#include <QtGui>
#include "AboutWindow.h"

AboutWindow::AboutWindow()
{
  // Setup Labels and Buttons
  m_appName = new QLabel("<h2>Internet Time Widget</h2>");
  m_description =
    new QLabel(tr("A System Tray application that displays the current Internet Time"));
  m_creator = new QLabel("Created by <a href='mailto:jeff.parent@gmail.com'>Jeff Parent</a>");
  m_version = new QLabel(tr("Version 0.0.1"));

  m_okButton = new QPushButton(tr("OK"));

  // Connect OK button with closing of the Dialog
  connect(m_okButton, SIGNAL(clicked()), this, SLOT(close()));

  // Layout window
  QVBoxLayout *layout = new QVBoxLayout;

  layout->addWidget(m_appName, 0, Qt::AlignHCenter);
  layout->addWidget(m_description, 0, Qt::AlignHCenter);
  layout->addWidget(m_creator, 0, Qt::AlignHCenter);
  layout->addWidget(m_version, 0, Qt::AlignHCenter);
  layout->addWidget(m_okButton, 0, Qt::AlignHCenter);

  setLayout(layout);

  setWindowTitle(tr("About"));
  setFixedHeight(sizeHint().height());
}
