#include <stdio.h>
#include <string.h>
#include "strmap.h"

#define CAP 2048 /* 2048 domainname-ipaddr key-value pairs*/
#define USAGE \
	"Usage: %s FILE\n\n" \
	"FILE line format: IPv4-address domain-name\n"

int
main(int argc, char *argv[])
{
	FILE *fp;
	StrMap *map;
	char ipaddr[16];
	char domainname[256];
	int i = 0;
	int linecnt = 0;

	if (argc != 2) {
		fprintf(stderr, USAGE, argv[0]);

		return 1 << 0;
	}

	if ((fp = fopen(argv[1], "r")) == NULL) {
		fprintf(stderr, "ERROR: failed to open '%s'\n", argv[1]);

		return 1 << 1;
	}

	map = sm_new(CAP);
	while (linecnt < CAP &&
           fscanf(fp, "%s", (i == 0) ? ipaddr : domainname) != EOF) {
		if (i == 0) {
			i = 1;
		} else {
			sm_put(map, domainname, ipaddr);
			i = 0;
		}
		linecnt++;
	}

	while (fgets(domainname, sizeof(domainname), stdin) != NULL) {
		domainname[strcspn(domainname, "\n")] = '\0';

		if (sm_exists(map, domainname)) {
			sm_get(map, domainname, ipaddr, sizeof(ipaddr));
			printf("%s\n", ipaddr);
		}
	}

	fclose(fp);
	sm_delete(map);

	return 0;
}
