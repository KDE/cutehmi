/*
 * Copyright © 2008-2014 Stéphane Raimbault <stephane.raimbault@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the BSD License.
 *
 * Modified by Michal Policht.
 *
 * This Source Code Form is "Incompatible With Secondary Licenses", as
 * defined by the Mozilla Public License, v. 2.0.
 */

#include <stdio.h>
#ifndef _MSC_VER
#include <unistd.h>
#endif
#include <stdlib.h>
#include <errno.h>

#include <modbus.h>

int main(void)
{
	printf("Modbus server\n");

	int s = -1;
	modbus_t *ctx;
	modbus_mapping_t *mb_mapping;

	printf("Creating new context\n");
	ctx = modbus_new_tcp("127.0.0.1", 1502);
	/* modbus_set_debug(ctx, TRUE); */

	printf("Setting new mapping\n");
	mb_mapping = modbus_mapping_new(500, 500, 500, 500);
	if (mb_mapping == NULL) {
		fprintf(stderr, "Failed to allocate the mapping: %s\n",
				modbus_strerror(errno));
		modbus_free(ctx);
		return -1;
	}

	s = modbus_tcp_listen(ctx, 10);
	modbus_tcp_accept(ctx, &s);

	printf("Listening for requests\n");

	for (;;) {
		uint8_t query[MODBUS_TCP_MAX_ADU_LENGTH];
		int rc;

		rc = modbus_receive(ctx, query);
		if (rc > 0) {
			/* rc is the query size */
			printf("Query received...\n");
			int delay = 1;
			printf("Waiting %d second(s) to simulate latency\n", delay);
			sleep(delay);
			printf("Replying...\n");
			modbus_reply(ctx, query, rc, mb_mapping);
		} else if (rc == -1) {
			/* Connection closed by the client or error */
			break;
		}
	}

	printf("Quit the loop: %s\n", modbus_strerror(errno));

	if (s != -1) {
		close(s);
	}

	modbus_mapping_free(mb_mapping);
	modbus_close(ctx);
	modbus_free(ctx);

	return 0;
}
