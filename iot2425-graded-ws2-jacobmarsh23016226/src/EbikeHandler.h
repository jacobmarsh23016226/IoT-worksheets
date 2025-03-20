#pragma once

#ifndef EBIKEHANDLER_H
#define EBIKEHANDLER_H


#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/JSON/Array.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>


// Handles requests to the /ebikes endpoint
class EBikeHandler : public Poco::Net::HTTPRequestHandler {
    public:
        explicit EBikeHandler(Poco::JSON::Array::Ptr& ebikes);
        void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) override;
    
    private:
        Poco::JSON::Array::Ptr& _ebikes; // Shared eBike data
    };
    
    // Serves static files (e.g., map.html)
    class FileHandler : public Poco::Net::HTTPRequestHandler {
    public:
        explicit FileHandler(const std::string& filePath);
        void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) override;
    
    private:
        std::string _filePath;
    };
    
    // Maps requests to the appropriate handler
    class RequestHandlerFactory : public Poco::Net::HTTPRequestHandlerFactory {
    public:
        explicit RequestHandlerFactory(Poco::JSON::Array::Ptr& ebikes);
        Poco::Net::HTTPRequestHandler* createRequestHandler(const Poco::Net::HTTPServerRequest& request) override;
    
    private:
        Poco::JSON::Array::Ptr& _ebikes;
    };
    
    #endif // EBIKEHANDLER_H