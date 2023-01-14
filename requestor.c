/*****************************************************************************
 *                                  _   _ ____  _
 *  Project                     ___| | | |  _ \| |
 *                             / __| | | | |_) | |
 *                            | (__| |_| |  _ <| |___
 *                             \___|\___/|_| \_\_____|
 *
 */
#include <stdio.h>
#include <curl/curl.h>

#define OK		0
#define INIT_ERR	1
#define REQ_ERR		2

#define URL		"http://192.168.45.128:8000"

int main(void)
{
  CURL *curl;
  CURLcode res;
  curl = curl_easy_init();
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, URL);
    res = curl_easy_perform(curl);
    if (res != CURLM_OK) {
	    return REQ_ERR;
    }
    /* always cleanup */
    curl_easy_cleanup(curl);
  } else {
	  return INIT_ERR;
  }
  return OK;
}

