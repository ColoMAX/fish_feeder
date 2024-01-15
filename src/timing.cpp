// #define ARDUINO
#ifndef ARDUINO

#include <stdio.h>
#include <string.h>
#include <time.h>
#define ESP_LOGD(_, ...) \
  printf(__VA_ARGS__);   \
  printf("\n")

int main() {
  struct tm new_stamp = {0};
  const time_t init_time = time(NULL);
  // start last activated
  new_stamp.tm_isdst = -1;
  new_stamp.tm_hour = 1;
  new_stamp.tm_min = 41;
  new_stamp.tm_mday = 13;
  new_stamp.tm_year = 2024 - 1900;
  new_stamp.tm_mon = 1 - 1;

  time_t last_timestamp_l = mktime(&new_stamp);
  ;  // id(last_timestamp);
  printf("Last time: %s", ctime(&last_timestamp_l));
  new_stamp = {0};

  int feed_day_interval_mock = 7;  // id(feed_day_interval).state;
  int feed_num_per_day_mock = 1;   // id(feed_num_per_day).state;
  int feed_start_time_hr = 1;      // atoi(feed_start_l.substr(0, 2).c_str());
  int feed_start_time_min = 00;    // atoi(feed_start_l.substr(3, 2).c_str());
  int feed_end_time_hr = 23;       // atoi(feed_end_l.substr(0, 2).c_str());
  int feed_end_time_min = 10;      // atoi(feed_end_l.substr(3, 2).c_str());
  for (time_t warp_time = 0; warp_time < (60LL * 60 * 24 * 15);
       warp_time += 60 * 60) {
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
    time_t start_day_last_time = mktime(&new_stamp);

    int feed_day_interval_l = feed_day_interval_mock;
    // ESP_LOGD("main", "Check feed time, %lld, %lld, %lld : %d, %lld",
    //          (long long)last_timestamp_l, (long long)start_day_last_time,
    //          (long long)time_now, feed_day_interval_l,
    //          60LL * 60 * 24 * feed_day_interval_l);

    int num_days_ago = (time_now - start_day_last_time) / (60LL * 60 * 24);
    new_stamp.tm_sec = 0;
    new_stamp.tm_min = feed_start_time_min;
    new_stamp.tm_hour = feed_start_time_hr;
    new_stamp.tm_isdst = -1;
#ifndef ARDUINO
    new_stamp.tm_year = localtime(&time_now)->tm_year;  // time.year - 1900;
    new_stamp.tm_mon = localtime(&time_now)->tm_mon;    // time.month - 1;
    new_stamp.tm_mday = localtime(&time_now)->tm_mday;  // time.day_of_month;
#else
new_stamp.tm_year = time_obj.year - 1900;
new_stamp.tm_mon = time_obj.month - 1;
new_stamp.tm_mday = time_obj.day_of_month;
#endif
    time_t first_of_day = mktime(&new_stamp);

    new_stamp.tm_min = feed_end_time_min;
    new_stamp.tm_hour = feed_end_time_hr;

    time_t end_of_day = mktime(&new_stamp);

    // time_t end_day_stamp =
    //     first_of_day +
    //     ((24 - feed_start_time_hr) * 60 + (60 - feed_start_time_min)) * 60;

    int feed_num_per_day_l = feed_num_per_day_mock;
    time_t steps = feed_num_per_day_l > 1
                       ? (end_of_day - first_of_day) / (feed_num_per_day_l - 1)
                       : 0;
#if 0
    ESP_LOGD("main", "Check feed time start:\nSettings: ::Now: %s",
             strtok(ctime(&time_now), "\n"));
    ESP_LOGD("main",
             "\tFirst of day (%02d:%02d): "
             "%s",
             feed_start_time_hr, feed_start_time_min,
             strtok(ctime(&first_of_day), "\n"));
    ESP_LOGD("main",
             "\tLast of "
             "day (%02d:%02d): %s",
             feed_end_time_hr, feed_end_time_min,
             strtok(ctime(&end_of_day), "\n"));
    ESP_LOGD("main", "\tLast feed (%d days ago): %s", num_days_ago,
             strtok(ctime(&last_timestamp_l), "\n"));
#endif
    int found_idx = -1;
    time_t feed_moment;
    for (int i = 0; i < feed_num_per_day_l; ++i) {
      feed_moment = first_of_day + i * steps;

      if ((time_now >= feed_moment) && (last_timestamp_l < feed_moment)) {
        found_idx = i;
        break;
      }
      // if (i % 8 == 0) yield();
    }
#if 0
    ESP_LOGD("main", "Result of search %d: %s", found_idx, strtok(ctime(&feed_moment),"\n"));
#endif
    if (found_idx > 0 ||
        ((found_idx == 0) && (num_days_ago == feed_day_interval_l))) {
      ESP_LOGD("main", "Go feed for %dth time at %s", found_idx + 1,
               strtok(ctime(&time_now), "\n"));
#ifndef ARDUINO
      last_timestamp_l = time_now;
#else
  id(last_timestamp) = time_now;
  id(feeder_trigger).press();
#endif
    }
#ifndef ARDUINO
  }
}
#endif