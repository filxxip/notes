#include "log_controller.h"

bool LogController::loginActive() const {
        return m_loginActive;
    }

void LogController::setLoginActive(bool loginActive) {
    if (m_loginActive != loginActive) {
        m_loginActive = loginActive;
        emit loginActiveChanged();
    }
}
