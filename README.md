logit - a tiny logger replacement
=================================

`logit` is a replacement for `logger(1)`.  It supports the same options
as the BusyBox version, but not all options from its systemd or sysklogd
cousins.

`logit` is bundled with [Finit][] for systems with a standard syslogd
but without a proper logrotate daemon.

Its purpose is to redirect the output of programs that do not support
`syslog(3)` to syslog or a file, with automatic log rotation.


Usage
-----

```
Usage: logit [OPTIONS] [MESSAGE]

Write MESSAGE (or stdin) to syslog, or file (with logrotate)

  -h       This help text
  -p PRIO  Priority (numeric or facility.level pair)
  -t TAG   Log using the specified tag (defaults to user name)
  -s       Log to stderr as well as the system log

  -f FILE  File to write log messages to, instead of syslog
  -n SIZE  Number of bytes before rotating, default: 200 kB
  -r NUM   Number of rotated files to keep, default: 5
```


Origin
------

Developed primarily for [Finit][] but can be used by anyone.  The code
is very simple and comes available for free under the very liberal MIT
license.

[Finit]: https://github.com/troglobit/finit
