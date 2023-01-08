# Quantcast_task
## Task description

Given a cookie log file in the following format:

cookie,timestamp 

AtY0laUfhglK3lC7,2018-12-09T14:19:00+00:00 

SAZuXPGUrfbcn5UA,2018-12-09T10:13:00+00:00 

5UAVanZf6UtGyKVS,2018-12-09T07:25:00+00:00 

AtY0laUfhglK3lC7,2018-12-09T06:19:00+00:00

process the log file and return the most active cookie for specified day. 



## Command line

./most_active_cookie cookie_log.csv -d 2018-12-09 

,where the second argument is the file path of the cookie data and the last is the string format of a specific day.



## Implementation

Use STL map to store the cookie frequency during a specific day, and output the most active ones.



## Sanity Check

Check whether the format of the command line is correct, including the count of the arguments and whether the given file exists.







