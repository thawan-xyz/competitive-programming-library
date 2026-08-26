from datetime import date, timedelta

# Convert 'HH:MM:SS' string to total seconds since midnight
def time_to_seconds(time_str: str) -> int:
    h, m, s = map(int, time_str.split(':'))
    return h * 3600 + m * 60 + s

# Convert total seconds back to 'HH:MM:SS' format
def seconds_to_time(seconds: int) -> str:
    h = seconds // 3600
    m = (seconds % 3600) // 60
    s = seconds % 60
    return f"{h:02d}:{m:02d}:{s:02d}"

# Fast parse 'YYYY-MM-DD' directly into integers
def parse_date(date_str: str) -> tuple:
    y, m, d = map(int, date_str.split('-'))
    return y, m, d

# Check if a given date is Saturday or Sunday
def is_weekend(year: int, month: int, day: int) -> bool:
    # weekday() returns 0 for Monday up to 6 for Sunday
    return date(year, month, day).weekday() >= 5

# Get the new (year, month, day) after adding x days
def add_days(year: int, month: int, day: int, x_days: int) -> tuple:
    new_date = date(year, month, day) + timedelta(days=x_days)
    return new_date.year, new_date.month, new_date.day

# Calculate the exact number of days between two dates
def days_between(y1: int, m1: int, d1: int, y2: int, m2: int, d2: int) -> int:
    date1 = date(y1, m1, d1)
    date2 = date(y2, m2, d2)
    return (date2 - date1).days

# Fast check if a year is a leap year (pure math, no imports)
def is_leap_year(year: int) -> bool:
    return (year % 4 == 0 and year % 100 != 0) or (year % 400 == 0)
