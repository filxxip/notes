#include "serverdataclient.h"
#include "directobjsmanagers/overallmanager.h"

namespace {

template<typename T>
QString codeTypeToQString(const T &object)
{
    throw UndefinedDataException("This type is not supported");
}

template<>
QString codeTypeToQString<QDateTime>(const QDateTime &object)
{
    auto date = object.date();
    auto time = object.time();
    return QString("%1-%2-%3-%4-%5-%6")
        .arg(date.year())
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
    throw UndefinedDataException("This type is not supported"); //nie dziala dla dat niestety
}
} // namespace

void ServerDataClient::setAdditionalParameters(json parameters)
{
    for (const auto &[key, value] : parameters.items()) {
        if (value.is_boolean()) {
            additionalParams += QString("&%1=%2").arg(QString::fromStdString(key),
                                                      value.get<bool>() ? "true" : "false");
            continue;
        }
        if (value.is_number_integer()) {
            additionalParams += QString("&%1=%2").arg(QString::fromStdString(key),
                                                      QString::number(value.get<int>()));
            continue;
        }
        if (value.is_string()) {
            additionalParams += QString("&%1=%2").arg(QString::fromStdString(key),
                                                      QString::fromStdString(
                                                          value.get<std::string>()));
            continue;
        }
    }
}

void ServerDataClient::initRequest(const Path &url, std::string mode) const
{
    request.setOpt<curlpp::options::Url>(url.getFullPath().toStdString());
    request.setOpt<curlpp::options::CustomRequest>(mode);
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
    initRequest(url, "PATCH");
    addParamsToRequest();
    performRequest();
}
void ServerDataClient::remove(const Path &url)
{
    initRequest(url, "DELETE");
    performRequest();
}
void ServerDataClient::add(const Path &url)
{
    initRequest(url, "POST");
    addParamsToRequest();
    performRequest();
}
std::optional<json> ServerDataClient::get(const Path &url) const
{
    initRequest(
        url,
        "GET"); //tu cos dziwnego z tym Get, wiem ze nie musi go byc ale dajac post np nie ma to znaczenia
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
    for (auto it = genson.begin(); it != genson.end(); ++it) {
        groupFilterString += separator + codeTypeToQString(it.key()) + "="
                             + codeTypeToQString(it.value());
    }
}
void ServerDataClient::clearFilters()
{
    groupFilterString.clear();
}
