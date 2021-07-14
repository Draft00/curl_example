#ifndef CURL_EXAMPLE_UTILS_H
#define CURL_EXAMPLE_UTILS_H

#include <curl/curl.h>
#include <memory>
#include <iostream>
#include <fstream>

/*
 * To perform synchronous downloads, we need to use libcurl’s easy interface.
 * We start with creating a curl easy handle for setting connection options and transferring data.
 */
using EasyHandle = std::unique_ptr<CURL, decltype(&curl_easy_cleanup)>;
EasyHandle CreateEasyHandle();

class ImageDownloader{

public:
    int Init();
    void SetURL_FilePath(std::string set_URL, std::string set_FilePath);
    ImageDownloader();
    static size_t write_to_file(void* contents, size_t size, size_t nmemb, void* userp);

private:
    EasyHandle m_handle;
    std::ofstream m_file;
    std::string m_URL;
    std::string m_file_path;
    void m_set_ssl();
    void m_save_to_file();
};

#endif //CURL_EXAMPLE_UTILS_H
