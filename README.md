Команды для запуска проекта<br>
1.Соберите докер файл с помощью команды docker build -t echo-server .  <br>
2.Запустите сервер внутри контейнера: docker run -d -p 81:81 echo-server<br>
3.Кидайте запросы на сервер с помощью команды telnet localhost 81, если протокол telnet не установлен, зайдите в командную строку от имени администратора и введите <br> dism /online /Enable-Feature /FeatureName:TelnetClient<br>
4.Если после подключения через telnet localhost 81 вы не можете кидать запросы в формате строки, а на сервер сразу улетает только первый написанный вами символ, <br> то нажмите сочетание Cntrl+], введите команду sen YourRequest <br>
5.Посмотрите id вашего контейнера с помощью команды docker ps и скопируйте его<br>
6.Остановите работу в контейнере командой docker stop your_id<br>
7.Удалите подключение командой docker rm your_id
