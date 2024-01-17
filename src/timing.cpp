// #define ARDUINO
#ifndef ARDUINO

#include <stdio.h>
#include <string.h>
#include <time.h>
#define ESP_LOGD(_, ...) \
  printf(__VA_ARGS__);   \
  printf("\n")
#define ESP_LOGI(_, ...) \
  printf(__VA_ARGS__);   \
  printf("\n")
#endif

#ifndef ARDUINO

int main() {
  struct tm new_stamp = {0};
  // SET start current time (start) for test
  new_stamp.tm_isdst = -1;
  new_stamp.tm_hour = 1;
  new_stamp.tm_min = 41;
  new_stamp.tm_mday = 27;
  new_stamp.tm_year = 2023 - 1900;
  new_stamp.tm_mon = 3 - 1;

  const time_t init_time = mktime(&new_stamp);  //  OR time(NULL);
  // SET start last activated for test
  new_stamp.tm_isdst = -1;
  new_stamp.tm_hour = 1;
  new_stamp.tm_min = 41;
  new_stamp.tm_mday = 27;
  new_stamp.tm_year = 2023 - 1900;
  new_stamp.tm_mon = 3 - 1;

  time_t last_timestamp_l = mktime(&new_stamp);
  ;  // id(last_timestamp);
  printf("Last time: %s", ctime(&last_timestamp_l));
  new_stamp = {0};

  int feed_day_interval_mock = 1;  // id(feed_day_interval).state;
  int feed_num_per_day_mock = 10;  // id(feed_num_per_day).state;
  int feed_start_time_hr = 23;     // atoi(feed_start_l.substr(0, 2).c_str());
  int feed_start_time_min = 59;    // atoi(feed_start_l.substr(3, 2).c_str());
  int feed_end_time_hr = 00;       // atoi(feed_end_l.substr(0, 2).c_str());
  int feed_end_time_min = 00;      // atoi(feed_end_l.substr(3, 2).c_str());

  const int interval = 1;  // warp seconds
  for (time_t warp_time = 0; warp_time < (60LL * 60 * 24 * 15);
       warp_time += interval) {
    auto time_now = init_time + warp_time;  // id(sntptime).now();

#else
struct tm new_stamp = {0};

auto time_obj = id(sntptime).now();
auto time_now = time_obj.timestamp;
int feed_day_interval_mock = id(feed_day_interval).state;
int feed_num_per_day_mock = id(feed_num_per_day).state;
auto feed_start_l = id(feed_first_time).state;
int feed_start_time_hr = atoi(feed_start_l.substr(0, 2).c_str());
int feed_start_time_min = atoi(feed_start_l.substr(3, 2).c_str());
auto feed_end_l = id(feed_last_time).state;
int feed_end_time_hr = atoi(feed_end_l.substr(0, 2).c_str());
int feed_end_time_min = atoi(feed_end_l.substr(3, 2).c_str());
time_t last_timestamp_l = id(last_timestamp);
#endif

    localtime_r(&last_timestamp_l, &new_stamp);
    new_stamp.tm_min = 0;
    new_stamp.tm_hour = 0;
    new_stamp.tm_sec = 0;
    new_stamp.tm_isdst = -1;

    time_t start_day_last_time = mktime(&new_stamp);

    int feed_day_interval_l = feed_day_interval_mock;

    int num_days_ago = (time_now - start_day_last_time) / (60LL * 60 * 24);
    ESP_LOGD("main", "last time was %s (%d days ago)",
             strtok(ctime(&time_now), "\n"), num_days_ago);

    new_stamp.tm_sec = 0;
    new_stamp.tm_min = feed_start_time_min;
    new_stamp.tm_hour = feed_start_time_hr;
    new_stamp.tm_isdst = -1;
#ifndef ARDUINO
    struct tm* curtime = localtime(&time_now);
    new_stamp.tm_year = curtime->tm_year;  // time.year - 1900;
    new_stamp.tm_mon = curtime->tm_mon;    // time.month - 1;
    new_stamp.tm_mday = curtime->tm_mday;  // time.day_of_month;
#else
new_stamp.tm_year = time_obj.year - 1900;
new_stamp.tm_mon = time_obj.month - 1;
new_stamp.tm_mday = time_obj.day_of_month;
#endif
    time_t first_of_day = mktime(&new_stamp);

    new_stamp.tm_min = feed_end_time_min;
    new_stamp.tm_hour = feed_end_time_hr;
    new_stamp.tm_isdst = -1;

    time_t end_of_day = mktime(&new_stamp);

    int feed_num_per_day_l = feed_num_per_day_mock;
    time_t steps = feed_num_per_day_l > 1
                       ? (end_of_day - first_of_day) / (feed_num_per_day_l - 1)
                       : 0;

    int found_idx = -1;

    if (time_now >= first_of_day) {
      if (last_timestamp_l < first_of_day) {
        if (num_days_ago >= feed_day_interval_l) found_idx = 0;

      } else if (steps > 0) {
        time_t last_slice = (last_timestamp_l - first_of_day) / steps;
        time_t current_slice = (time_now - first_of_day) / steps;
        int valid = 1;
        valid *= last_slice < feed_num_per_day_l;
        valid *= current_slice < feed_num_per_day_l;
        valid *= last_slice < current_slice;
        valid *= current_slice >= 0;
        if (valid) {
          found_idx = current_slice;
        }
      }
    }
    if (found_idx >= 0) {
      // get ordinal suffix
      int n = found_idx + 1;
      const char* suffix = "th";  // default = th

      if (1 <= n % 10 && n % 10 <= 3) {  // 1st, 2nd, 3rd

        if (n % 100 < 10 || n % 100 > 20) {  // 11th-13th
          suffix = (n % 10 == 1) ? "st" : (n % 10 == 2) ? "nd" : "rd";
        }
      }
      const char* cur_time_str = strtok(ctime(&time_now), "\n");
      ESP_LOGI("main", "Go feed for %2d%s timeslot at %s", found_idx + 1,
               suffix, cur_time_str);
#ifndef ARDUINO
      last_timestamp_l = time_now;
#else
      id(last_timestamp) = time_now;
      id(feeder_trigger).press();
      id(last_update_str).publish_state(cur_time_str);
#endif
    }
#ifndef ARDUINO
  }
}
#endif