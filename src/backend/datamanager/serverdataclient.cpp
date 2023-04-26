#include "serverdataclient.h"
#include "directobjsmanagers/overallmanager.h"

void ServerDataClient::setAdditionalParameters(const QString &key, int value)
{
    setAdditionalParameters(key, QString::number(value));
}

void ServerDataClient::setAdditionalParameters(const QString &key, const QString &value)
{
    additionalParams += QString("&%1=%2").arg(key, value);
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
        //        groupFilterString += separator + OverallManagerMethods::codeTypeToQString(it.key()) + "="
        //                             + OverallManagerMethods::codeTypeToQString(it.value());
    }
}
void ServerDataClient::clearFilters()
{
    groupFilterString.clear();
}
