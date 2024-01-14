#include "utils/fetch_image.hpp"

#include <curl/curl.h>
#include <cstring>

struct MemoryStruct {
  uint8_t *memory;
  size_t size;
};
 
static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
  size_t realsize = size * nmemb;
  struct MemoryStruct *mem = (struct MemoryStruct *)userp;
 
  uint8_t *ptr = (uint8_t*)realloc(mem->memory, mem->size + realsize + 1);
  if(!ptr) {
    /* out of memory! */
    return 0;
  }
 
  mem->memory = ptr;
  memcpy(&(mem->memory[mem->size]), contents, realsize);
  mem->size += realsize;
  mem->memory[mem->size] = 0;
 
  return realsize;
}

void clean_buffer(void* buffer){
    free(buffer);
}

Glib::RefPtr<Gdk::Texture> fetch_image(const std::string &url){
    MemoryStruct chunk = {(uint8_t*)malloc(1), 0};

    CURL* curl_handle = curl_easy_init(); // TODO work out how to reuse
    curl_easy_setopt(curl_handle, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&chunk);
    curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");

    auto res = curl_easy_perform(curl_handle);
 
    if(res != CURLE_OK) {
        // Oh no, probably throw something
    }

    GBytes* bytes = g_bytes_new_with_free_func(chunk.memory, chunk.size, &clean_buffer, chunk.memory);
    return Gdk::Texture::create_from_bytes(Glib::wrap(bytes));
}
