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

/* cURL status constants */

#define OK        0
#define INIT_ERR  0
#define REQ_ERR   0



/* Internal Functions */

/*CURL modes, mutually exclusive, select one*/

void curl_get(char *url, CURL *curl, CURLcode res) {
  curl = curl_easy_init();
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, url);
    /*GET is default mode, no special options necessary*/
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    res = curl_easy_perform(curl);
    if(res != CURLE_OK) {
      fprint(stderr, "[CURL] Could not complete: %s\n", curl_easy_strerror(res));
    }
    if(res == CURLE_OK) {
      long response_code;
      curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
    }
    curl_easy_cleanup(curl);
  }
}

void curl_post() {
  curl = curl_easy_init();
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, url);
    /*POST mode options*/
    curl_easy_setopt(curl, CURLOPT_POST, 1L);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, curl_message);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)strlen(curl_message));
    res = curl_easy_perform(curl);
    if(res != CURLE_OK) {
      fprint(stderr, "[CURL] Could not complete: %s\n", curl_easy_strerror(res));
    }
    if(res == CURLE_OK) {
      long response_code;
      curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
    }
    curl_easy_cleanup(curl);
}

void curl_put() {
  curl = curl_easy_init();
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, url);
    /*PUT mode options*/
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, curl_message);
    res = curl_easy_perform(curl);
    if(res != CURLE_OK) {
      fprint(stderr, "[CURL] Could not complete: %s\n", curl_easy_strerror(res));
    }
    if(res == CURLE_OK) {
      long response_code;
      curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
    }
    curl_easy_cleanup(curl);
  }
}

void curl_delete() {
  curl = curl_easy_init();
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, url);
    /*DELETE mode options*/
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, curl_message);
    res = curl_easy_perform(curl);
    if(res != CURLE_OK) {
      fprint(stderr, "[CURL] Could not complete: %s\n", curl_easy_strerror(res));
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

  c = getopt_long(argc, argv, "gopdu:hv", long_options, &long_index);
  while ((c != -1) {
    switch (c) {
    case 'g':
      do_get = 1;
      break;
    case 'o':
      do_post = 1;
      break;
    case 'p':
      do_put = 1;
      break;
    case 'd':
      do_delete = 1;
      break;
    case 'u':
      arguments.c = atoi(optarg);
      break;
    case 'h':
      arguments.c = atoi(optarg);
      break;
    case 'v':
      arguments.c = atoi(optarg);
      break;
    default:
      print_usage();
      printf("?? getopt.h returned error code 0%o ??\n", c)
      exit(EXIT_FAILURE);
    }
  }

  if (arguments.a == -1 || arguments.b == -1 || arguments.c == -1) {
    print_usage();
    exit(EXIT_FAILURE);
  }

  if (arguments.area){
    arguments.area = (arguments.a*arguments.b)/2;
    printf("Area: %d\n", arguments.area);
  }

  if (arguments.perimeter) {
    arguments.perimeter = arguments.a + arguments.b + arguments.c;
    printf("Perimeter: %d\n", arguments.perimeter);
  }

  return 0;
}
