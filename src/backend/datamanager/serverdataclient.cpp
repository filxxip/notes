#include "serverdataclient.h"
#include "directobjsmanagers/overallmanager.h"

#include <QObject>

namespace {

constexpr char NOT_SUPPORTED_MESSAGE[] = "This type is not supported";

const auto DATE_TIME_SYNTAX = QStringLiteral("%1-%2-%3-%4-%5-%6");
const auto ADDED_PARMS_SYNTAX = QStringLiteral("&%1=%2");

template<typename T>
QString codeTypeToQString(const T &object)
{
    throw UndefinedDataException(NOT_SUPPORTED_MESSAGE);
}

template<>
QString codeTypeToQString<QDateTime>(const QDateTime &object)
{
    auto date = object.date();
    auto time = object.time();
    return DATE_TIME_SYNTAX.arg(date.year())
        .arg(date.month())
        .arg(date.day())
        .arg(time.hour())
        .arg(time.minute())
        .arg(time.second());
}

template<>
QString codeTypeToQString<QString>(const QString &object)
{
    return object;
}
template<>
QString codeTypeToQString<int>(const int &object)
{
    return QString::number(object);
}

template<>
QString codeTypeToQString<std::string>(const std::string &object)
{
    return QString::fromStdString(object);
}

template<>
QString codeTypeToQString<json>(const json &object)
{
    switch (object.type()) {
    case json::value_t::number_integer: {
        return codeTypeToQString<int>(object.get<int>());
    }
    case json::value_t::string: {
        return codeTypeToQString<std::string>(object.get<std::string>());
    }
    }
    throw UndefinedDataException(NOT_SUPPORTED_MESSAGE); //nie dziala dla dat niestety
}
} // namespace

void ServerDataClient::setAdditionalParameters(json parameters)
{
    for (const auto &[key, value] : parameters.items()) {
        if (value.is_boolean()) {
            additionalParams += ADDED_PARMS_SYNTAX.arg(QString::fromStdString(key),
                                                       value.get<bool>() ? "true" : "false");
            continue;
        }
        if (value.is_number_integer()) {
            additionalParams += ADDED_PARMS_SYNTAX.arg(QString::fromStdString(key),
                                                       QString::number(value.get<int>()));
            continue;
        }
        if (value.is_string()) {
            additionalParams += ADDED_PARMS_SYNTAX.arg(QString::fromStdString(key),
                                                       QString::fromStdString(
                                                           value.get<std::string>()));
            continue;
        }
    }
}

void ServerDataClient::initRequest(const Path &url, QString mode) const
{
    request.setOpt<curlpp::options::Url>(url.getFullPath().toStdString());
    request.setOpt<curlpp::options::CustomRequest>(mode.toStdString());
}

void ServerDataClient::performRequest() const
{
    request.perform();
    request.reset();
}

void ServerDataClient::addParamsToRequest() const
{
    request.setOpt<curlpp::options::PostFields>(additionalParams.toStdString());
    additionalParams.clear();
}

void ServerDataClient::update(const Path &url)
{
    initRequest(url, QVariant::fromValue(Operations::DatabaseOperation::PATCH).toString());
    addParamsToRequest();
    performRequest();
}
void ServerDataClient::remove(const Path &url)
{
    initRequest(url, QVariant::fromValue(Operations::DatabaseOperation::DELETE).toString());
    performRequest();
}
void ServerDataClient::add(const Path &url)
{
    initRequest(url, QVariant::fromValue(Operations::DatabaseOperation::POST).toString());
    addParamsToRequest();
    performRequest();
}
std::optional<json> ServerDataClient::get(const Path &url) const
{
    initRequest(url, QVariant::fromValue(Operations::DatabaseOperation::GET).toString());
    std::stringstream response;
    curlpp::options::WriteStream writeStream(&response);
    request.setOpt(writeStream);
    performRequest();
    return json::parse(response.str());
}

std::optional<json> ServerDataClient::getGroup(const Path &path) const
{
    return get(UrlPath(path.getRelativePath() + groupFilterString));
}

void ServerDataClient::setGroupFilter(const json &genson)
{
    QString separator = groupFilterString.isEmpty() ? "?" : "&";
    for (auto it = std::begin(genson); it != std::end(genson); ++it) {
        groupFilterString += separator + codeTypeToQString(it.key()) + "="
                             + codeTypeToQString(it.value());
    }
}
void ServerDataClient::clearFilters()
{
    groupFilterString.clear();
}

bool ServerDataClient::isValid() const //:( -> my only idea
{
    try {
        get(UrlPath(""));
        return true;
    } catch (curlpp::RuntimeError &e) {
        qDebug() << e.what();
    } catch (curlpp::LogicError &e) {
        qDebug() << e.what();
    }

    return false;
}
