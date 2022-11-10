#ifndef DATETIME_H

  #define DATETIME_H

  #ifndef _INC_STDLIB
    #include <stdlib.h>
  #endif

  int __dt_CommonYearMonths[] = {
    31, 28, 31,
    30, 31, 30,
    31, 31, 30,
    31, 30, 31,
  };

  int __dt_LeapYearMonths[] = {
    31, 29, 31,
    30, 31, 30,
    31, 31, 30,
    31, 30, 31,
  };

  /*
  Checks if the provided year is a leap year.
  */
  char dt_is_leap_year(unsigned short year) {
    if (year % 4 == 0) {
      if (year % 100 == 0) {
        return year % 400 == 0;
      }
      return 1;
    }
    return 0;
  }

  int* __dt_get_months(unsigned short year) {
    return dt_is_leap_year(year) ? __dt_LeapYearMonths : __dt_CommonYearMonths;
  }

  /*
  The base unit of time is one second.
  */
  #define DT_MINUTE ((size_t) 60)

  /*
  The base unit of time is one second.
  */
  #define DT_HOUR ((size_t) 3600)

  /*
  The base unit of time is one second.
  */
  #define DT_DAY ((size_t) 86400)

  #define DT_EPOCH_YEAR 1900
  #define DT_EPOCH_MONTH 1
  #define DT_EPOCH_DAY 1

  /*
  A structure containing datetime information.
  Contains year, month, day, hour, minute second information.
  */
  struct datetime {
    unsigned short year;
    unsigned char month;
    unsigned char day;
    unsigned char hour;
    unsigned char minute;
    unsigned char second;
  };

  /*
  A structure containing date information.
  Contains year, month and day information.
  */
  struct date {
    unsigned short year;
    unsigned char month;
    unsigned char day;
  };

  /*
  Generate a new datetime instance from a timestamp in UTC+0.
  The time epoch is set to the 1st of January 1900.
  */
  struct datetime dt_datetime_from_seconds(size_t seconds) {

    struct datetime dt;
    dt.year = DT_EPOCH_YEAR;
    dt.month = DT_EPOCH_MONTH;
    dt.day = DT_EPOCH_DAY;

    size_t day_total = seconds / DT_DAY;
    size_t second_total = seconds % DT_DAY;
    int *months = __dt_get_months(dt.year);

    dt.hour = second_total / DT_HOUR;
    dt.minute = (second_total - dt.hour * DT_HOUR) / DT_MINUTE;
    dt.second = second_total - (dt.hour * DT_HOUR) - (dt.minute * DT_MINUTE);

    while (day_total--) {
      dt.day += 1;
      if (dt.day == months[dt.month - 1] + 1) {
        dt.day = 1;
        dt.month += 1;
        if (dt.month == 13) {
          dt.month = 1;
          dt.year += 1;
          months = __dt_get_months(dt.year);
        }
      }
    }

    return dt;
  }

  /*
  Generate a new date instance from a timestamp in UTC+0.
  The time epoch is set to the 1st of January 1900.
  */
  struct date dt_date_from_seconds(size_t seconds) {

    struct date dt;
    dt.year = DT_EPOCH_YEAR;
    dt.month = DT_EPOCH_MONTH;
    dt.day = DT_EPOCH_DAY;

    size_t day_total = seconds / DT_DAY;
    int *months = __dt_get_months(DT_EPOCH_YEAR);

    while (day_total--) {
      dt.day += 1;
      if (dt.day == months[dt.month - 1] + 1) {
        dt.day = 1;
        dt.month += 1;
        if (dt.month == 13) {
          dt.month = 1;
          dt.year += 1;
          months = __dt_get_months(dt.year);
        }
      }
    }

    return dt;
  }

  /*
  Add seconds to a datetime. Returns a new datetime instance.
  */
  struct datetime dt_datetime_add_seconds(struct datetime *d, size_t seconds) {

    struct datetime dt;
    dt.year = d->year;
    dt.month = d->month;
    dt.day = d->day;
    dt.hour = d->hour;
    dt.minute = d->minute;
    dt.second = d->second;

    size_t day_total = seconds / DT_DAY;
    size_t second_total = seconds % DT_DAY;
    int *months = __dt_get_months(dt.year);

    size_t hour = second_total / DT_HOUR;
    size_t minute = (second_total - hour * DT_HOUR) / DT_MINUTE;
    size_t second = second_total - (hour * DT_HOUR) - (minute * DT_MINUTE);

    dt.hour += hour;
    dt.minute += minute;
    dt.second += second;

    while (day_total--) {
      dt.day += 1;
      if (dt.day == months[dt.month - 1] + 1) {
        dt.day = 1;
        dt.month += 1;
        if (dt.month == 13) {
          dt.month = 1;
          dt.year += 1;
          months = __dt_get_months(dt.year);
        }
      }
    }

    return dt;
  }

  /*
  Add seconds to a datetime. Returns a new datetime instance.
  */
  struct date dt_date_add_seconds(struct datetime *d, size_t seconds) {

    struct date dt;
    dt.year = d->year;
    dt.month = d->month;
    dt.day = d->day;

    size_t day_total = seconds / DT_DAY;
    int *months = __dt_get_months(dt.year);

    while (day_total--) {
      dt.day += 1;
      if (dt.day == months[dt.month - 1] + 1) {
        dt.day = 1;
        dt.month += 1;
        if (dt.month == 13) {
          dt.month = 1;
          dt.year += 1;
          months = __dt_get_months(dt.year);
        }
      }
    }

    return dt;
  }

#endif