#pragma once

#include <QObject>

class LogController : public QObject{
  Q_OBJECT
  Q_PROPERTY(bool loginActive READ loginActive WRITE setLoginActive NOTIFY loginActiveChanged)
public:
  bool loginActive() const;

  Q_INVOKABLE void setLoginActive(bool loginActive);

  signals:
  void loginActiveChanged();

  private:
  bool m_loginActive;
};
