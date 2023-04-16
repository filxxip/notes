#include "serverdataclient.h"
#include <curl/curl.h>
#include <curlpp/Easy.hpp>
#include <sstream>
void ServerDataClient::setAdditionalParameters(const QString &params)
{
    additionalParams = params;
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

void ServerDataClient::update(const Path &url) const
{
    initRequest(url, "PATCH");
    addParamsToRequest();
    performRequest();
}
void ServerDataClient::remove(const Path &url) const
{
    initRequest(url, "DELETE");
    performRequest();
}
void ServerDataClient::add(const Path &url) const
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
