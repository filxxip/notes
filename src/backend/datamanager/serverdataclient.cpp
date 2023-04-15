#include "serverdataclient.h"
//#include <curlpp/Easy.hpp>
#include <curl/curl.h>
void ServerDataClient::setAdditionalParameters(const QString &params)
{
    additionalParams = params;
}
void ServerDataClient::update(const Path &url) const
{
    //    curlpp::Easy request;
    //    request.setOpt<curlpp::options::Url>(url.toStdString());
    //    request.setOpt<curlpp::options::PostFields>(additionalParams.toStdString());
    //    request.perform();
    //    additionalParams.clear();
}
void ServerDataClient::remove(const Path &url) const
{
    //    curlpp::Easy request;
    //    request.setOpt<curlpp::options::Url>(url.toStdString());
    //    request.setOpt<curlpp::options::CustomRequest>("DELETE");
    //    request.perform();
}
void ServerDataClient::add(const Path &) const {}
std::optional<json> ServerDataClient::get(const Path &) const
{
    return {};
}
