#include "utils.h"

class CurlGlobalStateGuard
{
public:
    CurlGlobalStateGuard() { curl_global_init(CURL_GLOBAL_DEFAULT); }
    ~CurlGlobalStateGuard() { curl_global_cleanup(); }
};
static CurlGlobalStateGuard handle_curl_state;

EasyHandle CreateEasyHandle()
{
    auto curl = EasyHandle(curl_easy_init(), &curl_easy_cleanup);
    if (!curl)
    {
        throw std::runtime_error("Failed creating CURL easy object");
    }
    return curl;
}

int DownloaderImage::Init() {
    /*
     * At this step, we set options for easy handles.
     * To add links to the files that need to be downloaded, we set the CURLOPT_URL option:
     */
    curl_easy_setopt(m_handle.get(), CURLOPT_URL, "https://protei.ru/themes/custom/aga/favicon.ico");

    /*
     * Next, we need to deal with SSL connections.
     * To simplify our tutorial, we can tell libcurl not to verify SSL connections by setting the CURLOPT_SSL_VERIFYPEER
     * and CURLOPT_SSL_VERIFYHOST options to 0:
     */
    m_set_ssl(m_handle.get());

    /*
     * By default, curl will print downloaded data to the console, which is useful for testing purposes.
     * To change this behavior, we can redefine the CURLOPT_WRITEFUNCTION option and change it to write to a file:
     */

    m_save_to_file(m_handle.get());

    /* Perform the request, res will get the return code */
    auto res = curl_easy_perform(m_handle.get());
    /* Check for errors */
    if (res != CURLE_OK)
    {
        std::cerr << "curl_easy_perform() failed:" <<
                  curl_easy_strerror(res) << std::endl;
        return -1;
    }
    return 0;
}

void DownloaderImage::m_save_to_file(CURL *curl) {
    static std::ofstream file("../downloaded_image.ico", std::ios::binary);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, DownloaderImage::write_to_file);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, reinterpret_cast<void*>(&file));
}

void DownloaderImage::m_set_ssl(CURL *curl) {
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
}

DownloaderImage::DownloaderImage(): m_handle(CreateEasyHandle()) { //is it RAII?

}

size_t DownloaderImage::write_to_file(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    auto file = reinterpret_cast<std::ofstream*>(userp);
    file->write(reinterpret_cast<const char*>(contents), realsize);
    return realsize;
}



