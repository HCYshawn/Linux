#include <curl/curl.h>
#include <iostream>

int main() {
  curl_version_info_data *version_info = curl_version_info(CURLVERSION_NOW);

  std::cout << "Curl Demo Version: 1.0.0" << std::endl;
  std::cout << "Curl Library Version: " << version_info->version << std::endl;
  std::cout << "Curl SSL Version: " << version_info->ssl_version << std::endl;
  std::cout << "Curl Protocols: " << version_info->protocols[0] << std::endl;
  return 0;
}
