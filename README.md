# Alarm

This is the Alarm application for Windows. This application created for softly wakeup people, who love to snooze their alarm and continue sleeping. 
The main advantage of this alarm program is impossible to snooze the alarm. 
For stop, the alarm signal user should kill the alarm process. He can make it by an already written script which contains the command

`taskkill /f /im alarm.exe`

or manually in Task Manager.
But before kill the process user should log in to the system, so make sure what your password have enough strength,
but not very hard to write fast while the user is sleepy.

Volume can't be turned off by interaction with a computer, because the program will check and set the correct sound volume for an exact time interval.
Of course, the user still able to physically turn off the external sound system, but notebooks don't have that vulnerability.

For the build this project you need BOOST, so install BOOST 
and make sure do you have set a `BOOST_ROOT` variable.