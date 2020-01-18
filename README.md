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

After the project will build, need to set up a task in Task Scheduler. Example task located in 

`script/alarm_task_example.xml`

You can import that in Task scheduler, but do not forget to set up security options like on the screenshot

![task_setup_1](https://raw.githubusercontent.com/rostyslavnikitin/Alarm/master/files/task_setup_1.png)

you can specify run a program with arguments like in this task example, just add alarm.exe to the path and provide an absolute path to WAV sound what do you want to play with this alarm program.

Another way it specifies command and arguments in a separated .bat file. The example also located in 
`scripts/alarm.bat`
