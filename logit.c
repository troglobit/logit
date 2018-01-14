/*
 * Copyright (c) 2018  Joachim Nilsson <troglobit@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <getopt.h>
#include <stdio.h>
#include <string.h>
#define SYSLOG_NAMES
#include <syslog.h>

static void stdlog(int level, char *buf, size_t len)
{
	while ((fgets(buf, len, stdin)))
		syslog(level, "%s", buf);
}

static int parse_prio(char *arg, int *f, int *l)
{
	char *ptr;

	ptr = strchr(arg, '.');
	if (ptr) {
		*ptr++ = 0;

		for (int i = 0; facilitynames[i].c_name; i++) {
			if (!strcmp(facilitynames[i].c_name, arg)) {
				*f = facilitynames[i].c_val;
				break;
			}
		}

		arg = ptr;
	}

	for (int i = 0; prioritynames[i].c_name; i++) {
		if (!strcmp(prioritynames[i].c_name, arg)) {
			*l = prioritynames[i].c_val;
			break;
		}
	}

	return 0;
}

static int usage(int code)
{
	fprintf(stderr, "Usage: logit [OPTIONS] [MESSAGE]\n"
		"\n"
		"Write MESSAGE (or stdin) to syslog or file, with logrotate\n"
		"\n"
		"  -h       This help text\n"
		"  -s       Log to stderr as well as the system log\n"
		"  -t TAG   Log using the specified tag (defaults to user name)\n"
		"  -p PRIO  Priority (numeric or facility.level pair)\n"
		);

	return code;
}

int main(int argc, char *argv[])
{
	int c;
	int facility = LOG_USER;
	int level = LOG_INFO;
	int log_opts = LOG_NOWAIT;
	char *ident = NULL, buf[512] = "";

	while ((c = getopt(argc, argv, "hp:st:")) != EOF) {
		switch (c) {
		case 'h':
			return usage(0);

		case 'p':
			if (parse_prio(optarg, &facility, &level))
				return usage(1);
			break;

		case 's':
			log_opts |= LOG_PERROR;
			break;

		case 't':
			ident = optarg;
			break;

		default:
			return usage(1);
		}
	}

	openlog(ident, log_opts, facility);

	if (optind < argc) {
		size_t pos = 0, len = sizeof(buf);

		while (optind < argc) {
			size_t bytes;

			bytes = snprintf(&buf[pos], len, "%s ", argv[optind++]);
			pos += bytes;
			len -= bytes;
		}

		syslog(facility | level, "%s", buf);
	} else
		stdlog(level, buf, sizeof(buf));

	closelog();

	return 0;
}
