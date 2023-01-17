/*************************
* _               _
*| |             | |
*| |__   __ _  __| |
*| '_ \ / _` |/ _` |
*| |_) | (_| | (_| |
*|_.__/ \__,_|\__,_|
*      _____  __
*     |  _  |/ _|
*  ___| |/' | |_ ___  ___
* / __|  /| |  _/ _ \/ _ \
*| (__\ |_/ / ||  __/  __/
* \___|\___/|_| \___|\___|
*
************************/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h> /*someimtes required if unistd.h alone doesn't work*/
#include <curl/curl.h>
#include <string.h>

/* cURL status constants */

#define OK        0
#define INIT_ERR  0
#define REQ_ERR   0

//#define URL       "http://192.168.1.1:8000"

//char *url, *curl_message;
//CURL *curl;
//CURLcode res;

/* Internal Functions */

/*CURL modes, mutually exclusive, select one*/

void curl_get(char *url, CURL *curl, CURLcode res) {
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, url);
    /*GET is default mode, no special options necessary*/
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    res = curl_easy_perform(curl);
    if(res != CURLE_OK) {
      fprintf(stderr, "[CURL] Could not complete: %s\n", curl_easy_strerror(res));
    }
    if(res == CURLE_OK) {
      long response_code;
      curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
    }
    curl_easy_cleanup(curl);
  }
}

void curl_post(char *url,char *message, CURL *curl, CURLcode res) {
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, url);
    /*POST mode options*/
    curl_easy_setopt(curl, CURLOPT_POST, 1L);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, message);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)strlen(message));
    res = curl_easy_perform(curl);
    if(res != CURLE_OK) {
      fprintf(stderr, "[CURL] Could not complete: %s\n", curl_easy_strerror(res));
    }
    if(res == CURLE_OK) {
      long response_code;
      curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
    }
    curl_easy_cleanup(curl);
  }
}

void curl_put(char *url,char *message, CURL *curl, CURLcode res ) {
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, url);
    /*PUT mode options*/
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, message);
    res = curl_easy_perform(curl);
    if(res != CURLE_OK) {
      fprintf(stderr, "[CURL] Could not complete: %s\n", curl_easy_strerror(res));
    }
    if(res == CURLE_OK) {
      long response_code;
      curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
    }
    curl_easy_cleanup(curl);
  }
}

void curl_delete(char *url, char *message, CURL *curl, CURLcode res) {
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, url);
    /*DELETE mode options*/
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, message);
    res = curl_easy_perform(curl);
    if(res != CURLE_OK) {
      fprintf(stderr, "[CURL] Could not complete: %s\n", curl_easy_strerror(res));
    }
    if(res == CURLE_OK) {
      long response_code;
      curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
    }
    curl_easy_cleanup(curl);
  }
}

/* Other functions, non-curl */

void hw_help() {
  printf("HELP MESSAGE HERE\n");
}

void hw_usage() {
  printf("USAGE MESSAGE HERE\n");
}

void hw_version() {
  printf("VERSION MESSAGE HERE\n");
}

/* Strucure for command line arguments */
/*struct arguments
 {
   int a;
   int b;
   int c;
   int area;
   int perimeter;
 };
*/

/************************************/

int main(int argc, char **argv) {
  int long_index=0;
  /* struct arguments arguments; */

  /* Default values.
  arguments.get = -1;
  arguments.post = -1;
  arguments.put = -1;
  arguments.delete = -1;
  arguments.url = 0;
  arguments.help = 0;
  arguments.version = 0;
  arguments.data = 0;
  */

  int gflag = 0;
  int oflag = 0;
  int pflag = 0;
  int dflag = 0;
  
  int c;
  char *message;
  char *url = NULL;

  CURL *curl;
  CURLcode res;

  curl = curl_easy_init();

  static struct option long_options[] = {
    {"get",      required_argument,       0,    'g'},
    {"post",     required_argument,       0,    'o'},
    {"put",      required_argument,       0,    'p'},
    {"delete",   required_argument,       0,    'd'},
    {"url",      required_argument,       0,    'u'},
    {"help",     no_argument,             0,    'h'},
    {"version",  no_argument,             0,    'v'},
    {0,          0 ,                      0,     0 }
  };

//c = getopt_long(argc, argv, "gopdu:hv", long_options, &long_index);
  while ((c = getopt_long(argc, argv, "gopdu:hv", long_options, &long_index)) != -1){	  
    switch (c) {
    case 'g':
      gflag = 1;
      break;
    case 'o':
      oflag = 1;
      break;
    case 'p':
      pflag = 1;
      break;
    case 'd':
      dflag = 1;
      break;
    case 'u':
      url = optarg;
      printf("option u with value '%s'\n", url);
      break;
    case 'h':
      printf("option h chosen\n");
      break;
    case 'v':
      printf("option v chosen\n");
      break;
    case '?':
      printf("Unknown option: %c\n", optopt);
    default:
      hw_usage();
      printf("?? getopt.h returned error code 0%o ??\n", c);
      exit(EXIT_FAILURE);
    }
  }

if (gflag){
	curl_get(url, curl, res);
	printf("running curl_get\n");
}
if (oflag){
	curl_post(url, message, curl, res);
	printf("running curl_post\n");
}
if (pflag){
	curl_put(url, message, curl, res);
	printf("running curl_put\n");
}
if (dflag){
	curl_delete(url, message, curl, res);
	printf("running curl_delete\n");
}

  return 0;
}
