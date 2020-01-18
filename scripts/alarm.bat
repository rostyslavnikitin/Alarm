@echo %off
Pushd "<alarm directory CHANGE_THIS!!!>"
:: -r - repeats
:: -t - steps
:: -v - max volume

alarm.exe -r 3 -f "alarm.wav"  -t 120 -v 15
