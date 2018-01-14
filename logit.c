#include <stdio.h>
#include <syslog.h>

int main(void)
{
	char buf[512];

	while ((fgets(buf, sizeof(buf), stdin)))
		syslog(LOG_USER | LOG_INFO, "%s", buf);

	return 0;
}
