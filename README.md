# logquickview
A simple project to view log files

This is (probably) going to be build using Electorn

- Select a directory (add as treeview)
- Open logfile
- Show as excel sheet. Allow to change autoselected format
- Filter if desired
- Remote implementation?
- Preselect common logs
- Dropdown to save different logs
- Ability to unzip gzipped logs

e.g.
nginx access.log
```
x.x.x.x - - [04/May/2020:18:52:42 +0000] "GET / HTTP/1.1" 200 2731 "https://myURL" "Note"
x.x.x.x - - [04/May/2020:18:52:42 +0000] "GET /static/xxx.css HTTP/1.1" 304 0 "https://myURL" "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/81.0.4044.129 Safari/537.36"
x.x.x.x - - [04/May/2020:18:52:43 +0000] "GET /static/xxx.js HTTP/1.1" 200 2951 "https://myURL" "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/81.0.4044.129 Safari/537.36"
```
postfix:
```
May  4 18:05:42 ip-xxx postfix/smtpd[10933]: disconnect from unknown[x.x.x.x] commands=0/0
May  4 18:09:02 ip-xxx postfix/anvil[10935]: statistics: max connection rate 1/60s for (smtp:x.x.x.x) at May  4 18:05:41
May  4 18:09:02 ip-xxx postfix/anvil[10935]: statistics: max connection count 1 for (smtp:x.x.x.x) at May  4 18:05:41
May  4 18:09:02 ip-xxx postfix/anvil[10935]: statistics: max cache size 1 at May  4 18:05:41
```

Format should be autoselected
postfix uses "{month} {day} {hourutc}:{minute}:{second} {hostname} {who}/{what}

## Remote implementation
This should be EASY because many other things are terrible
e.g. select ssh key. Select remote IP. Enter pw if requested. 
